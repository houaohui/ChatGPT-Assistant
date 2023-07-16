from paho.mqtt import client as mqtt_client
import time
import requests
import json
import sys

topic_C = "/test/ctrl"
topic_A = "/test/answer"



# 连接mqtt服务器


def connect_mqtt():
    # 服务器信息
    broker = '127.0.0.1'
    port = 1883
    # 客户端id
    client_id = 'one-net'

    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    # Set Connecting Client ID
    client = mqtt_client.Client(client_id)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

# 订阅回调函数


def on_message(client, userdata, msg):
    print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
    input_str = f"{msg.payload.decode()}"
    text = onenet_ctrl(input_str)
    if text == -1:
        publish(client, topic_A, "我好像出了点问题,再试一下")
        return
    publish(client, topic_A, "控制已完成")

# 订阅消息


def subscribe(client: mqtt_client, topic):
    client.subscribe(topic)
    client.on_message = on_message

# 发布消息


def publish(client, topic, msg):
    result = client.publish(topic, msg)
    # result: [0, 1]
    status = result[0]
    if status == 0:
        print(f"Send `{msg}` to topic `{topic}`")
    else:
        print(f"Failed to send message to topic {topic}")


def onenet_ctrl(prompt):
    
    url = "http://api.heclouds.com/devices/1087771502"

    headers = {
        "content-type":"application/json",
        "api-key" : "你的api-key"
    }

    response = requests.request("GET", url, headers=headers)
    
    
    json_data = response.json()
    # print(json_data)

    is_online = json_data['data']['online']
    print(f"online: {is_online}")

    if is_online == True :
        url = "http://api.heclouds.com/cmds?device_id=1087771502"

        data = prompt

        headers = {
            "content-type":"application/json",
            "api-key" : "你的api-key"
        }

        response = requests.request(
            "POST", url, headers=headers, data=data)
        json_data = response.json()
        print(json_data)
        return 0
    else :
        return -1
    


if __name__ == "__main__":

    client = connect_mqtt()
    client.loop_start()
    # 订阅问题
    subscribe(client, topic_C)
    while (True):
        input_str = input("enter text: ")
        if onenet_ctrl(input_str) == -1:
            print("devive not online!\n")
        time.sleep(1)
