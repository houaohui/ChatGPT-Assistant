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
#include <sys/time.h>


using namespace std;


std::deque<std::wstring> myQueue;
std::mutex mtx;

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

static float cpuUsage = 0;

// cpu 使用统计线程
void* getCpuUsage(void* arg) {
    while (!global_done) {

        FILE* file = fopen("/proc/stat", "r");
        if (file == NULL) {
            perror("Error opening /proc/stat");
            exit(1);
        }

        char line[128];
        unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
        unsigned long long prev_idle, prev_total, total_diff, idle_diff;

        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
                prev_idle = idle;
                prev_total = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
                break;
            }
        }
        fclose(file);

        // Do some work that you want to measure CPU usage for.
        sleep(2);

        // After the work is done, read /proc/stat again.
        file = fopen("/proc/stat", "r");
        if (file == NULL) {
            perror("Error opening /proc/stat");
            exit(1);
        }

        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice) == 10) {
                total_diff = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice - prev_total;
                idle_diff = idle - prev_idle;
                double cpu_usage = 100.0 * (1.0 - (double)idle_diff / total_diff);
                // printf("CPU Usage: %.2f%%\n", cpu_usage);
                cpuUsage = cpu_usage;
                break;
            }
        }
        fclose(file);
    }

    return NULL;
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
    std::string ui_txt = (char *)message->payload;

    // 将字符串连接并转换
    std::string concatenatedStr = ui_txt + "\n";

    size_t in_len = concatenatedStr.length();

    size_t out_len = in_len * sizeof(wchar_t);

    // 分配输出缓冲区的内存并初始化为零
    wchar_t *out_str = (wchar_t *)calloc(out_len, 1);

    iconv_t cd = iconv_open("wchar_t","UTF-8");
    if(cd == (iconv_t)-1) {
        printf("iconv open failed !\n");
    }

    //转化
    std::wstring ui_wtxt;
    char * in_buf = (char *)concatenatedStr.c_str();
    char *out_buf = (char *)out_str;

    if(iconv(cd, &in_buf, &in_len, &out_buf, &out_len) == (size_t)-1) {
        // 转化失败
        printf("iconv failed!\n");
        wchar_t buffer[50];
        // 使用swprintf进行格式化
        swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"iconv %d:%d\n", in_len, out_len);

        ui_wtxt = buffer;
    } else {
        // 转化成功
        ui_wtxt = out_str; 
    }

    if (!ui_wtxt.empty())
    {
        std::lock_guard<std::mutex> lock(mtx);
        myQueue.push_back(ui_wtxt);
    }

   
    // free(wtxt);
    iconv_close(cd);
    free(out_str);

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}


/**
 * @brief 控制帧率刷新函数
 * 
 * @param frameRate 设定帧率
 */
void updateFrame(int frameRate) {
    struct timeval currentTime, lastTime;
    long long frameTimeMicros = 1000000 / frameRate;

    gettimeofday(&lastTime, NULL);

    do {
        gettimeofday(&currentTime, NULL);

        long long elapsedTimeMicros = (currentTime.tv_sec - lastTime.tv_sec) * 1000000 +
            (currentTime.tv_usec - lastTime.tv_usec);

        if (elapsedTimeMicros < frameTimeMicros) {
            long long sleepTimeMicros = frameTimeMicros - elapsedTimeMicros;
            usleep(sleepTimeMicros); // 睡眠以控制帧率
        }

  
        // 刷新屏幕
        do{
            std::lock_guard<std::mutex> lock(mtx);
            if (!myQueue.empty()) {
                std::wstring &new_wtxt = myQueue.back(); // 只读取队列的末尾数据
                txtViewer.printf(&txtViewer, (wchar_t *)new_wtxt.c_str());
                myQueue.pop_back();    // 只删除队列的末尾数据
            }
        } while(0);

        // 解析
        txtViewer.run(&txtViewer);
        
        freetype_show_cpu_usage(cpuUsage);
        freetype_fill_screen();
        freetype_clean_screen();

        gettimeofday(&lastTime, NULL);

    } while(0);
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

    pthread_t thread;
    if (pthread_create(&thread, NULL, getCpuUsage, NULL) != 0) {
        perror("Error creating thread");
        return 1;
    }  

    #define FRAME_RATE  (45)

    while(!global_done)
    {
        updateFrame(FRAME_RATE);
    }


    freetype_test_close();
    
    delete mqttClient;
    return 0;
}



