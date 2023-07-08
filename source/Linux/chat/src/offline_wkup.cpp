

#include "pocketsphinx.h"
#include <signal.h>
// #include <winnls.h>
#include <math.h>
#include <string.h>
#include "offline_wkup.h"
#include "../audiorecorder/audio_rec.h"
#include "../mqtt-client/mqtt-client.h"

int OL_WKUP::awake = 0;
Time OL_WKUP::timer_2;

extern MQTTCLIENT *mqttClient;

static FILE *
popen_sox(int sample_rate)
{
    char *soxcmd;
    int len;
    FILE *sox;
#define SOXCMD "sox -q -r %d -c 1 -b 16 -e signed-integer -d -t raw -"
    len = snprintf(NULL, 0, SOXCMD, sample_rate);
    if ((soxcmd = (char *)malloc(len + 1)) == NULL)
        E_FATAL_SYSTEM("Failed to allocate string");
    if (snprintf(soxcmd, len + 1, SOXCMD, sample_rate) != len)
        E_FATAL_SYSTEM("snprintf() failed");
    // Replaced "popen" with "_popen"
    if ((sox = popen(soxcmd, "r")) == NULL)
        E_FATAL_SYSTEM("Failed to popen(%s)", soxcmd);
    free(soxcmd);

    return sox;
}

/**
 * 获取所有振幅之平均值 计算db (振幅最大值 2^16-1 = 65535 最大值是 96.32db)
 * 16 bit == 2字节 == short int
 * 无符号16bit：96.32=20*lg(65535);
 *
 * @param pcmdata 转换成char类型，才可以按字节操作
 * @param size pcmdata的大小
 * @return
 */
int getPcmDB(const short *pcmdata, size_t size)
{
    int db = 0;
    short value = 0;
    double sum = 0;
    for (int i = 0; i < size; i += 1)
    {
        memcpy(&value, pcmdata + i, 2); // 获取2个字节的大小（值）
        sum += abs(value);              // 绝对值求和
    }
    sum = sum / (size / 1); // 求平均值（2个字节表示一个振幅，所以振幅个数为：size/2个）
    if (sum > 0)
    {
        db = (int)((sum));
    }
    return db;
}
//
int max_volume;
int get_volume(const short *pcmdata, size_t size)
{
    size_t len = size;

    int db = getPcmDB(pcmdata, len);
    if (db > max_volume)
        max_volume = db;
    // printf("volume db: %.5d max: %.5d len:%d\r", db,max_volume,len);
    return db;
}

OL_WKUP::OL_WKUP()
{
    config = ps_config_init(NULL);
    ps_default_search_args(config);
    if ((decoder = ps_init(config)) == NULL)
        E_FATAL("PocketSphinx decoder init failed\n");

    if ((ep = ps_endpointer_init(0, 0.0, PS_VAD_LOOSE, 0, 0)) == NULL)
        E_FATAL("PocketSphinx endpointer init failed\n");

    sox = popen_sox(ps_endpointer_sample_rate(ep));
    //
    frame_size = ps_endpointer_frame_size(ep);
    printf("frame_size :%d\n", frame_size);
    if ((frame = (short *)malloc(frame_size * sizeof(frame[0]))) == NULL)
        E_FATAL_SYSTEM("Failed to allocate frame");
}

void OL_WKUP::deal_volume_flag(const short *pcmdata)
{
    int volume = get_volume(pcmdata, frame_volume_size);
    // 检测静音
    if (volume < 2000)
    {
        if (timer_2.has_pass(1) && !AudioRec::slient_flag)
        {
            AudioRec::slient_flag = 1;
            AudioRec::start_record = 0;
            // printf("volume %d slient %d rec %d \n", volume, AudioRec::slient_flag, AudioRec::start_record);
        }
    }
    else
    {
        AudioRec::slient_flag = 0;
        timer_2.restart();
    }
    // 检测语音
    if (volume > volume_ok)
    {
        timer.restart();
        if (!AudioRec::start_record)
        {
            AudioRec::start_record = 1;
            AudioRec::slient_flag = 0;
            // printf("volume %d slient %d rec %d \n", volume, AudioRec::slient_flag, AudioRec::start_record);
        }
    }
    else
    {
        if (AudioRec::start_record && timer.has_pass(1))
        {
            // printf("...........");
            AudioRec::start_record = 0;
        }
    }
    // printf("volume %d slient %d rec %d \r", volume, AudioRec::slient_flag, AudioRec::start_record);
}

void OL_WKUP::run()
{
    static int start_flag = 0;
    const int16 *speech;
    // int prev_in_speech = ps_endpointer_in_speech(ep);

    size_t len, end_samples;

    if ((len = fread(frame, sizeof(frame[0]),
                     frame_size, sox)) != frame_size)
    {
        if (len > 0)
        {
            speech = ps_endpointer_end_stream(ep, frame,
                                              frame_size,
                                              &end_samples);
            printf("read len is not enough\n");
        }
        else
            return;
    }
    else
    {
        // 与音量有关的标志位
        deal_volume_flag(frame);

        if (AudioRec::start_record && !start_flag && !awake) {
            //printf("sssssssstart\n\n");
            start_flag = 1;
        }
            
        //if (start_flag && !awake)
        //    speech = ps_endpointer_process(ep, frame);

    }
    if (start_flag && !awake)
    {
        const char *hyp;
        static int utt_start_flag = 0;
        static int utt_end_flag = 1;
        static int qiangzhi_shibei_flag = 0;

        char publish_flag = 0;
        std::string str = "";

        if (AudioRec::start_record && !utt_start_flag)
        {
            publish_flag = 1;
            str = str + "语音开始";
            // mqttClient->publish("/test/ui",str);
            // printf("Speech start\n");
            utt_start_flag = 1;
            utt_end_flag = 0;
            qiangzhi_shibei_flag = 0;
            AudioRec::slient_flag = 0;
            timer_3.restart();
            ps_start_utt(decoder);
        }

        
        //两秒后强制识别
        if(!qiangzhi_shibei_flag && !utt_end_flag && utt_start_flag && timer_3.has_pass(1))
        {
            qiangzhi_shibei_flag = 1;
            // printf("强制识别\n");
            // printf("force identification\n");
        }


        if (ps_process_raw(decoder, frame, frame_size, FALSE, FALSE) < 0)
            E_FATAL("ps_process_raw() failed\n");
        //if ((hyp = ps_get_hyp(decoder, NULL)) != NULL)
        //    fprintf(stderr, "PARTIAL RESULT: %s\n", hyp);
        if (((AudioRec::slient_flag && !utt_end_flag) || qiangzhi_shibei_flag) && utt_start_flag)
        {

            ps_end_utt(decoder);
            if ((hyp = ps_get_hyp(decoder, NULL)) != NULL) {
                // printf("%s\n", hyp);
                if(publish_flag)
                    str = str + "\n" + hyp;
                else
                    str = str + hyp;
                publish_flag = 1;
                // mqttClient->publish("/test/ui",str);
            }

            if(publish_flag)
                str = "--" + str + "--\n" + "语音结束";
            else
                str = str + "语音结束";
            publish_flag = 1;
            
            // printf("Speech end\n");
            start_flag = 0;
            utt_start_flag = 0;
            utt_end_flag = 1;
            qiangzhi_shibei_flag = 0;
            if (strstr(hyp, "CHELSEA") != NULL)
            {
                awake = 1;
                utt_start_flag = 0;
                qiangzhi_shibei_flag = 0;
                start_flag = 0;

                if(publish_flag)
                    str = str + "\n" +  "唤醒!";
                else
                    str = str +  "唤醒!";
                publish_flag = 1;
                // printf("awake !\n");
            }
        }
        if(publish_flag)
            mqttClient->publish("/test/ui",str);
    }
}

OL_WKUP::~OL_WKUP()
{
    free(frame);
    if (pclose(sox) < 0)
        E_ERROR_SYSTEM("Failed to pclose(sox)");
    ps_endpointer_free(ep);
    ps_free(decoder);
    ps_config_free(config);
}
