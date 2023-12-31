#ifndef OFFLINE_WKUP
#define OFFLINE_WKUP

#include "pocketsphinx.h"
#include "timer.h"

#define frame_volume_size 30
#define volume_ok 2500

class OL_WKUP
{
public:
    OL_WKUP();
    ~OL_WKUP();
    void run();
    void deal_volume_flag(const short *pcmdata);

    static int awake;

    ps_decoder_t *decoder;
    ps_config_t *config;
    ps_endpointer_t *ep;
    FILE *sox;
    short *frame;
    size_t frame_size;

    Timer timer;
    static Timer timer_2;
    Timer timer_3;
};


#endif 
