#include "asr.h"
#include <iostream>
#include <memory.h>
#include "tts.h"
#include "mqtt-client.h"
#include "offline_wkup.h"
#include "../audiorecorder/audio_rec.h"

using namespace std;

static int answer_flag=0;
std::string answer_txt; 
int continuous_dialog_flag = 0;

/**
 * @brief 退出
 * 
 */
static int global_done = 0;
static void catch_sig(int signum)
{
    (void)signum;
    global_done = 1;
}
/**
 * @brief MQTT回调函数
 * 
 * @param context 
 * @param topicName 
 * @param topicLen 
 * @param message 
 * @return int 
 */
static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    answer_txt = (char *)message->payload;
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    answer_flag = 1;
    return 1;
}

int main(int argc, char **argv)
{
    string payload = "hello world";
    SetConsoleOutputCP(CP_UTF8);

    if (signal(SIGINT, catch_sig) == SIG_ERR)
        E_FATAL_SYSTEM("Failed to set SIGINT handler");
    
    ASR *asr = new ASR();
    TTS *tts = new TTS();
    MQTTCLIENT *mqttClient = new MQTTCLIENT();
    OL_WKUP *ol_wkup = new OL_WKUP();
    AudioRec *audioRec = new AudioRec(ol_wkup);
    //
    mqttClient->subscribe("/test/answer",msgarrvd);
    
    tts->getResponse("你好,我叫小C,请问你有什么需要帮助的吗？");

    while(!global_done)
    {
        if(continuous_dialog_flag)
        {
            ol_wkup->awake = 1;
        }

        ol_wkup->run();
        if(ol_wkup->awake)
        {
            if(!continuous_dialog_flag)
                tts->getResponse("我在，你说");
            audioRec->record();
            asr->getResponse();
            //

            if (continuous_dialog_flag && (strstr(ASR::txt_result.c_str(), "闭连续对话") != NULL || strstr(ASR::txt_result.c_str(), "出连续对话")))
            {
                continuous_dialog_flag = 0;
                tts->getResponse("连续对话已关闭");
                answer_flag = 0;
                ol_wkup->awake = 0;
                continue;
            }

            if (!continuous_dialog_flag && strstr(ASR::txt_result.c_str(), "启连续对话") != NULL)
            {
                continuous_dialog_flag = 1;
                tts->getResponse("连续对话已开启");
                audioRec->record();
                asr->getResponse();
            }

            if (strstr(ASR::txt_result.c_str(), "清空对话") != NULL || strstr(ASR::txt_result.c_str(), "新对话") != NULL)
            {
                tts->getResponse("已清空历史对话");
                std::string str = "new chat";
                mqttClient->publish("/test/question",str);
                continue;
            }

            if (strstr(ASR::txt_result.c_str(), "退出") != NULL)
            {
                tts->getResponse("我要退出了，再见");
                Sleep(1);
                return 0;
            }

            if (strstr(ASR::txt_result.c_str(), "打开空调") != NULL)
            {
                std::string str = "1";
                tts->getResponse("好的,将为你打开空调");
                mqttClient->publish("/test/ctrl",str);
                while(answer_flag == 0) {
                // answer_flag = 0;
                }
                tts->getResponse(answer_txt);
                answer_flag = 0;
                ol_wkup->awake = 0;
                continue;
            }
            if (strstr(ASR::txt_result.c_str(), "关闭空调") != NULL)
            {
                std::string str = "0";
                tts->getResponse("好的，将为你关闭空调");
                mqttClient->publish("/test/ctrl",str);
                while(answer_flag == 0) {
                // answer_flag = 0;
                }
                tts->getResponse(answer_txt);
                answer_flag = 0;
                ol_wkup->awake = 0;
                continue;
            }
            
            mqttClient->publish("/test/question",ASR::txt_result);
            while(answer_flag == 0) {
                // answer_flag = 0;
            }
            if(answer_txt.length() <= 1)
                answer_txt = " ";
            tts->getResponse(answer_txt);
            answer_flag = 0;
            ol_wkup->awake = 0;
        }
    }
    
    // system("pause");

    free(asr);
    free(tts);
    free(mqttClient);
    free(ol_wkup);
    return 0;
}