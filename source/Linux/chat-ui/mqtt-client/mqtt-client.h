/**
 * @file mqtt-client.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "../paho-mqtt-c-1.3.12/include/MQTTClient.h"

#define ADDRESS     "127.0.0.1:1883"
#define CLIENTID    "chat_ui"
#define QOS         0
#define TIMEOUT     10000L

class MQTTCLIENT
{
public:
    MQTTCLIENT();
    ~MQTTCLIENT();

    void publish(std::string topic, std::string &payload);
    void subscribe(std::string topic);
    void subscribe(std::string topic,MQTTClient_messageArrived* msgarrvd);
    void unsubscribe(std::string topic);

    //消息送达
    static void delivered(void *context, MQTTClient_deliveryToken dt)
    {
        printf("Message with token value %d delivery confirmed\n", dt);
        // token = dt;
    }
    //消息接收回调
    static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
    {
        printf("Message arrived\n");
        printf("     topic: %s\n", topicName);
        printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
        return 1;
    }

    //断开连接回调
    static void connlost(void *context, char *cause)
    {
        printf("\nConnection lost\n");
        printf("     cause: %s\n", cause);
    }

    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

};


#endif // MQTT_CLIENT_H
