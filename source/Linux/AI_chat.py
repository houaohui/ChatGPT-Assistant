import requests
import json
import time
from paho.mqtt import client as mqtt_client

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
    if input_str == "new chat":
        messages.clear()
        # messages.append({"role": "system", "content": "你是一个有用的助手"})
        return
    messages.append({"role": "user", "content":input_str})
    text = chatWithAi(messages)
    if text == "error":
        publish(client, topic_A, "我好像出了点问题,再试一下")
        return
    text = text.replace("\n","")
    messages.append({"role": "assistant", "content":text})
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

def get_access_token():
    # client id = App Key, client_secret = Secret Key
    client_id = 'IWbWEEYwzwfsns8rgoHNjNk8'
    client_secret = 'u2GBGz5och3IDiPVp49GFQijZD1HOCUm'
    url = f"https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id={client_id}&client_secret={client_secret}"
    
    payload = ""
    headers = {
        'Content-Type': 'application/json',
        'Accept': 'application/json'
    }
    
    response = requests.request("POST", url, headers=headers, data=payload)
    json_data = response.json()
     # 格式化打印
    # formatted_data = json.dumps(json_data, indent=4)
    # print(formatted_data)
    # print(response.text)
    access_tokens = json_data['access_token']
    # print(access_tokens)
    return access_tokens


# 调用百度文心一言
def chatWithAi(prompt):
    url = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/eb-instant?access_token=" + access_token

    data = {
        "messages": prompt,
    }


    headers = {
        'Content-Type': 'application/json'
    }

    response = requests.request("POST", url, headers=headers, json=data, allow_redirects=False)
    json_data = response.json()
    
    print("/////////////////")
    # 格式化打印
    # formatted_data = json.dumps(json_data, indent=4)
    # print(formatted_data)
    
    # 检查字典中是否存在 error 键
    if "error" in json_data:
        print("出现错误！！！")
        return "error"
    if "error_code" in json_data:
        print("出现错误！！！")
        return "error"
    # result_txt = json_data['choices'][0]['message']['content']
    result_txt = json_data['result']
    return result_txt

# 对话内容 全局变量
# messages=[{"role": "system", "content": "你是一个有用的助手"}]
messages=[]
access_token = get_access_token()

if __name__ == '__main__':
    client = connect_mqtt()
    client.loop_start()
    # 订阅问题
    subscribe(client, topic_Q)
    while True:
        # input_str = input("you: ")
        # if str == 'q':
        #     break
        # messages.append({"role": "user", "content":input_str})
        # text = chatWithAi(messages)
        # text = text.replace("\n","")
        # print("AI: " + text)
        # messages.append({"role": "assistant", "content":text})
        # print(messages)

        time.sleep(1)