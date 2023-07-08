from paho.mqtt import client as mqtt_client
import time
import requests
import json
import sys




# 连接mqtt服务器


def connect_mqtt():
    # 服务器信息
    broker = '127.0.0.1'
    port = 1883
    # 客户端id
    client_id = 'chat-gpt'

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
    text = chatWithAi(input_str)
    if text == "error":
        
        return
    text = text.replace("\n", "")
    publish(client, topic_A, text)

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


if __name__ == "__main__":

    client = connect_mqtt()
    client.loop_start()
    # 订阅问题
    # subscribe(client, topic_Q)
    while (True):
        input_str = input("you: ")
        if str == 'q':
            break
        txt = "我好像出了点问题,再试一下\n"
        data = txt.encode("utf-8")
        publish(client, "/test/ui", data)
        time.sleep(1)
