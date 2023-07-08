#include "TXT_Viewer.h"
#include <iostream>
#include <memory.h>
#include <signal.h>
#include <unistd.h>
#include "mqtt-client.h"
#include "freetype_draw.h"
#include <termios.h>
#include <fcntl.h>
#include <iconv.h>
#include <queue>
#include <mutex>

using namespace std;

std::string ui_txt; 
char ui_txt_flag = 0;
std::wstring ui_wtxt;

std::queue<std::wstring> message_queue;
std::mutex message_mutex;


/**
 * @brief 退出
 * 
 */
static int global_done = false;
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
    // printf("     topic: %s\n", topicName);
    // printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    ui_txt = (char *)message->payload;
    ui_txt_flag = true;
    
    char *txt;
    wchar_t *wtxt;
    txt = (char *)(ui_txt+"\n").c_str();
    // printf("%s",txt);
    // for(int i =0 ; i< strlen(txt) ; i++) {
    //     printf("\\x%02X",txt[i]);
    // }


    size_t in_len = strlen(txt);
    size_t out_len = in_len * sizeof(wchar_t);
    // printf("\nin_len=%d, out_len=%d\n",in_len, out_len);
    wchar_t *out_str = (wchar_t *)calloc(out_len,1);

    iconv_t cd = iconv_open("wchar_t","UTF-8");
    if(cd == (iconv_t)-1) {
        printf("iconv open failed !\n");
    }

    //转化函数会改变指针，我们重新建一个变量
    char * in_buf = txt;
    char *out_buf = (char *)out_str;

    if(iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == (size_t)-1) {
        printf("iconv failed !\n");
    }

    // printf("inbuf=%s, inlen=%d, outbuf=%ls, outlen=%d",txt,in_len,out_str,out_len);
    ui_wtxt = out_str; 
    // std::unique_lock<std::mutex> lock(message_mutex);
    // message_queue.push(ui_wtxt);  //添加消息
    txtViewer.printf(&txtViewer, (wchar_t *)ui_wtxt.c_str());

    // free(wtxt);
    iconv_close(cd);
    free(out_str);

    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    ui_txt_flag = false;

    return 1;
}

int nb_get_wchar(wchar_t &c)
{
    int result = -1;
    struct termios old_tio, new_tio;
    int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if(tcgetattr(STDIN_FILENO, &old_tio) == 0) {
        new_tio = old_tio;
        new_tio.c_lflag &= ~(ICANON | ECHO);
        if(tcsetattr(STDIN_FILENO, TCSANOW, &new_tio) == 0) {
            fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);
            wchar_t c1 = getwchar();
            if(c1 != EOF) {
                c = c1;
                result = 0;
            }
            fcntl(STDIN_FILENO, F_SETFL, old_flags);
            tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        }
        
    }
    
    return result;
}

int main(int argc, char **argv)
{

    if (signal(SIGINT, catch_sig) == SIG_ERR)
        printf("Failed to set SIGINT handler");
    
    MQTTCLIENT *mqttClient = new MQTTCLIENT();
    mqttClient->subscribe("/test/ui",msgarrvd);

    freetype_test_init();
    // freetype_test_draw();
    
    

    txtViewer_init(&txtViewer,1024,0,0,CONSOLE_PRINT);


    while(!global_done)
    {
        
        // wchar_t c;
        // if(nb_get_wchar(c) != -1)
        // {
        //     txtViewer.input_updata = true;
        //     txtViewer.getchar = c;
        //     printf("wchar: %lc\n",c);
        // }
        while(ui_txt_flag == true)
        {
            // ui_txt_flag = false;
            // std::unique_lock<std::mutex> lock(message_mutex);
            // while(!message_queue.empty()) {
            //     std::wstring ui_txt = message_queue.front();
                // txtViewer.printf(&txtViewer, (wchar_t *)ui_wtxt.c_str());
            //     message_queue.pop();
            // }
        }

        txtViewer.run(&txtViewer);
        
        freetype_fill_screen();
        freetype_clean_screen();
    }

    freetype_test_close();
    
    free(mqttClient);
    return 0;
}



