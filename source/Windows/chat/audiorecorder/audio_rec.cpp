#include "audio_rec.h"
#include <iostream>
#include <thread>
#include "../src/time.h"
#include <windows.h>
#include <atomic>
// #include <sox.h>

int AudioRec::start_record = 0;

int AudioRec::slient_flag = 1;

OL_WKUP * AudioRec::ol_wkup;//这样也有声明作用，其他文件可以用

AudioRec::AudioRec(OL_WKUP *ol_wkup)
{
    this->ol_wkup = ol_wkup;
}
AudioRec::~AudioRec()
{
}

#pragma pack(push, 1)
typedef struct
{
    char chunkId[4]={'R','I','F','F'};    // "RIFF"
    uint32_t chunkSize; // 文件总大小 - 8
    char format[4]={'W','A','V','E'};     // "WAVE"

    char subchunk1Id[4]={'f','m','t',' '};    // "fmt "
    uint32_t subchunk1Size = 16; // fmt 子块大小
    uint16_t audioFormat = 1;   // 编码方式（一般为 1 表示 PCM）
    uint16_t numChannels = 1;   // 声道数
    uint32_t sampleRate = 16000;    // 采样率
    uint32_t byteRate = 32000;      // 数据传输速率（每秒字节数）
    uint16_t blockAlign = 2;    // 块对齐（每个采样帧占用的字节数）
    uint16_t bitsPerSample = 16 ; // 每个样本的位数

    char subchunk2Id[4]={'d','a','t','a'};    // "data"
    uint32_t subchunk2Size; // 音频数据大小
} WAV_HEADER;
#pragma pack(pop)



// 声明一个原子布尔类型的标志变量
std::atomic_bool running = true;
// 录音线程
void thread_record(FILE *sox)
{
    int buffer_size = 1024;
    std::string filename = "16k.wav";

    FILE *fp = fopen(filename.c_str(), "wb+");
    if (fp == nullptr)
    {
        std::cerr << "Failed to start recording" << std::endl;
        return;
    }

    // 重新清零检测
    std::cout << "请说话" << std::endl;
    AudioRec::start_record = 0;

    // 等待重启录音
    while (!AudioRec::start_record)
    {
        AudioRec::ol_wkup->run();
    }

    AudioRec::slient_flag = 0;
    OL_WKUP::timer_2.restart();

    while (running)
    {
        short data[buffer_size];
        size_t size = fread(data, sizeof(short), buffer_size, sox);
        fwrite(data, sizeof(short), size, fp);
        // fwrite(ptr, size, nmemb, result->fp);

        // 检测音量处理标志位
        AudioRec::ol_wkup->deal_volume_flag(data);

        printf("recordering\n");
        if (AudioRec::slient_flag)
        {
            running = false;
        }
    }

    fseek(fp, 0, SEEK_END);
    long data_size = ftell(fp) - sizeof(WAV_HEADER);
    fseek(fp, 0, SEEK_SET);

    // Update the header fields with the data size
    WAV_HEADER header;
    // fread(&header, sizeof(header), 1, fp);
    header.chunkSize = data_size + sizeof(WAV_HEADER) - 8;
    header.subchunk2Size = data_size;
    fwrite(&header, sizeof(header), 1, fp);

    // Close the file
    fclose(fp);
    std::cout << "WAV header added successfully" << std::endl;
    running = true;
}

// void thread_record()
// {
//     while (running)
//     {
//         system("sox -q -b 16 -r 16000 -c 1  -t waveaudio -d 16k.wav");
//         std::cout << "a" << std::endl;
//     }
// }

void AudioRec::record()
{

    //等待背景音变小
    AudioRec::slient_flag = 0;
    OL_WKUP::timer_2.restart();
    while(!AudioRec::slient_flag)
    {
        this->ol_wkup->run();
    }

    // 创建新线程
    std::thread t(thread_record, AudioRec::ol_wkup->sox);
    t.join();
    // t.detach();

  
    
    

    // int flag_rec_end = 1;

    // while (flag_rec_end)
    // {
    //     // 检测音量
    //     this->ol_wkup->run();

    //     printf("recordering\n");
    //     if (!AudioRec::start_record)
    //     {
    //         // if (t.joinable())
    //         {
    //             // pthread_kill(t.native_handle(), SIGINT);
    //             // GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
    //             flag_rec_end = 0;
    //             running = false;
    //             printf("recorder finished\n");
    //         }
    //     }
    // }

    // // 等待子线程结束
    // t.join();
    std::cout << "record finished!" << std::endl;
}