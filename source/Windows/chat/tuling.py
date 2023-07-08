from paho.mqtt import client as mqtt_client
import time
import requests
import json
import sys

topic_A = "/test/answer"
topic_Q = "/test/question"



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
        publish(client, topic_A, "我好像出了点问题,再试一下")
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


def chatWithAi(prompt):
    url = "http://openapi.turingapi.com/openapi/api/v2"

    data = {
        "reqType": 0,
        "perception": {
            "inputText": {
                "text": prompt,
            },
            # "selfInfo": {
            #     "location": {
            #         "city": city,
            #         "province": province,
            #         "street": street,
            #     },
            # },
        },
        "userInfo": {
            "apiKey": "bcced6c3eae34dcb8315601612284c78",
            "userId": "00010001",
        },

    }

    headers = {
        "Content-Type":"application/json"
    }

    response = requests.request(
        "POST", url, headers=headers, json=data, allow_redirects=False)
    json_data = response.json()
    print(json_data)
    # 格式化打印
    formatted_data = json.dumps(json_data, indent=4)
    print(formatted_data)

    if json_data['intent']['code'] > 0 and json_data['intent']['code'] < 9000:
        return "error"
     
    result_json = json_data['results']
    result_txt = ""
    for res in result_json:
        if "text" == res['resultType'] :
            result_txt = res['values']['text']
    
    return result_txt


if __name__ == "__main__":

    client = connect_mqtt()
    client.loop_start()
    # 订阅问题
    subscribe(client, topic_Q)
    while (True):
        input_str = input("you: ")
        if str == 'q':
            break
        text = chatWithAi(input_str)
        print("AI: " + text)


        time.sleep(1)
