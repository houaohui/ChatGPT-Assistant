/**
 * @file mqtt-client.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "mqtt-client.h"
#include <iostream>
using namespace std;





MQTTCLIENT::MQTTCLIENT()
{
    this->conn_opts = MQTTClient_connectOptions_initializer;
    this->pubmsg = MQTTClient_message_initializer;
    int rc;

    cout << "Connecting..." << endl;
    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        cout << "Failed to create client, return code: " << rc << endl;
    }

    if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) 
        != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        return;
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        cout << "Failed to connect, return code: " << rc << endl;
    }
    else
    {
        cout << "Connecting... successfully" << endl;
    }
}

MQTTCLIENT::~MQTTCLIENT()
{
    int rc;
    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
    	printf("Failed to disconnect, return code %d\n", rc);
    MQTTClient_destroy(&client);
}
/**
 * @brief 发布主题消息
 * 
 * @param topic 
 * @param payload 
 */
void MQTTCLIENT::publish(std::string topic, std::string &payload)
{
    int rc;
    pubmsg.payload = (char *)payload.c_str();
    pubmsg.payloadlen = payload.length();
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    if ((rc = MQTTClient_publishMessage(client, topic.c_str(), &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }

    // printf("Publishing  on topic %s for client with ClientID: %s\n",
    //         topic.c_str(), CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    // printf("Message with delivery token %d delivered\n", token);
}

/**
 * @brief 订阅消息
 * 
 * @param topic 
 */
void MQTTCLIENT::subscribe(std::string topic)
{
    int rc;
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", topic.c_str(), CLIENTID, QOS);
    if ((rc = MQTTClient_subscribe(client, topic.c_str(), QOS)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to subscribe, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }
}
/**
 * @brief 带有重写回调的订阅
 * 
 * @param topic 
 * @param msgarrvd 
 */
void MQTTCLIENT::subscribe(std::string topic,MQTTClient_messageArrived* msgarrvd)
{
    int rc;
    if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) 
        != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        return;
    }

    printf("Subscribing to topic %s for client %s using QoS%d\n"
           , topic.c_str(), CLIENTID, QOS);
    if ((rc = MQTTClient_subscribe(client, topic.c_str(), QOS)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to subscribe, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }
}
/**
 * @brief 取消订阅消息
 * 
 * @param topic 
 */
void MQTTCLIENT::unsubscribe(std::string topic)
{
    int rc;
    if ((rc = MQTTClient_unsubscribe(client, topic.c_str())) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to unsubscribe, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
}