/* Example of simple PocketSphinx speech segmentation.
 *
 * MIT license (c) 2022, see LICENSE for more information.
 *
 * Author: David Huggins-Daines <dhdaines@gmail.com>
 */
/**
 * @example live.c
 * @brief Speech recognition with live audio input and endpointing.
 *
 * This file shows how to use PocketSphinx in conjunction with `sox`
 * to detect and recognize speech from the default audio input device.
 *
 * This file shows how to use PocketSphinx to recognize a single input
 * file.  To compile it, assuming you have built the library as in
 * \ref unix_install "these directions", you can run:
 *
 *     cmake --build build --target live
 *
 * Alternately, if PocketSphinx is installed system-wide, you can run:
 *
 *     gcc -o live live.c $(pkg-config --libs --cflags pocketsphinx)
 *
 *
 */
#include <pocketsphinx.h>
#include <signal.h>
#include <winnls.h>
#include <math.h>

static int global_done = 0;
static void
catch_sig(int signum)
{
    (void)signum;
    global_done = 1;
}

static FILE *
popen_sox(int sample_rate)
{
    char *soxcmd;
    int len;
    FILE *sox;
    #define SOXCMD "sox -q -r %d -c 1 -b 16 -e signed-integer -t waveaudio default -t raw -"
    len = snprintf(NULL, 0, SOXCMD, sample_rate);
    if ((soxcmd = malloc(len + 1)) == NULL)
        E_FATAL_SYSTEM("Failed to allocate string");
    if (snprintf(soxcmd, len + 1, SOXCMD, sample_rate) != len)
        E_FATAL_SYSTEM("snprintf() failed");
    // Replaced "popen" with "_popen"
    if ((sox = _popen(soxcmd, "rb")) == NULL)
        E_FATAL_SYSTEM("Failed to popen(%s)", soxcmd);
    free(soxcmd);

    return sox;
}

#define frame_volume_size 30
#define volume_ok        9000
/** 
 * 获取所有振幅之平均值 计算db (振幅最大值 2^16-1 = 65535 最大值是 96.32db) 
 * 16 bit == 2字节 == short int 
 * 无符号16bit：96.32=20*lg(65535); 
 * 
 * @param pcmdata 转换成char类型，才可以按字节操作 
 * @param size pcmdata的大小 
 * @return 
 */  
int getPcmDB(const short *pcmdata, size_t size) {
    int db = 0;  
    short value = 0;  
    double sum = 0;  
    for(int i = 0; i < size; i += 1)  
    {  
        memcpy(&value, pcmdata+i, 2); //获取2个字节的大小（值）  
        sum += abs(value); //绝对值求和  
    }
    sum = sum / (size / 1); //求平均值（2个字节表示一个振幅，所以振幅个数为：size/2个）  
    if(sum > 0) 
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

    int db = getPcmDB(pcmdata,len);
    if(db > max_volume)
        max_volume = db;
    printf("volume db: %.5d max: %.5d len:%d\r", db,max_volume,len);
    return db;
}

int
main(int argc, char *argv[])
{
    ps_decoder_t *decoder;
    ps_config_t *config;
    ps_endpointer_t *ep;
    FILE *sox;
    short *frame;
    size_t frame_size;

    (void)argc; (void)argv;
    // SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");
    config = ps_config_init(NULL);
    ps_default_search_args(config);
    if ((decoder = ps_init(config)) == NULL)
        E_FATAL("PocketSphinx decoder init failed\n");

    if ((ep = ps_endpointer_init(0, 0.0, 0, 0, 0)) == NULL)
        E_FATAL("PocketSphinx endpointer init failed\n");
    sox = popen_sox(ps_endpointer_sample_rate(ep));
    //
    frame_size = ps_endpointer_frame_size(ep);
    printf("frame_size :%d\n", frame_size);
    if ((frame = malloc(frame_size * sizeof(frame[0]))) == NULL)
        E_FATAL_SYSTEM("Failed to allocate frame");
    if (signal(SIGINT, catch_sig) == SIG_ERR)
        E_FATAL_SYSTEM("Failed to set SIGINT handler");
    while (!global_done) {
        static int start_flag = 0;
        const int16 *speech;
        int prev_in_speech = ps_endpointer_in_speech(ep);
        
        size_t len, end_samples;
        // if (start_flag)
        if ((len = fread(frame, sizeof(frame[0]),
                         frame_size, sox)) != frame_size) {
            if (len > 0) {
                speech = ps_endpointer_end_stream(ep, frame,
                                                  frame_size,
                                                  &end_samples);
            }
            else
                break;
        } else {

            int volume_flag = (get_volume(frame,frame_volume_size) > volume_ok);
            if(volume_flag && !start_flag)
                start_flag = 1;
            if(start_flag)
                speech = ps_endpointer_process(ep, frame);
        }
        if (speech != NULL && start_flag) {
            const char *hyp;
            if (!prev_in_speech) {
                fprintf(stderr, "Speech start at %.2f\n",
                        ps_endpointer_speech_start(ep));
                ps_start_utt(decoder);
            }
            if (ps_process_raw(decoder, speech, frame_size, FALSE, FALSE) < 0)
                E_FATAL("ps_process_raw() failed\n");
            // if ((hyp = ps_get_hyp(decoder, NULL)) != NULL)
            //     fprintf(stderr, "PARTIAL RESULT: %s\n", hyp);
            if (!ps_endpointer_in_speech(ep)) {
                fprintf(stderr, "Speech end at %.2f\n",
                        ps_endpointer_speech_end(ep));
                ps_end_utt(decoder);
                if ((hyp = ps_get_hyp(decoder, NULL)) != NULL)
                    printf("%s\n", hyp);
                start_flag =0;
            }
        }
    }
    free(frame);
    if (pclose(sox) < 0)
        E_ERROR_SYSTEM("Failed to pclose(sox)");
    ps_endpointer_free(ep);
    ps_free(decoder);
    ps_config_free(config);
        
    return 0;
}
