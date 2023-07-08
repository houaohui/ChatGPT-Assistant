#ifndef AUDIO_REC_H
#define AUDIO_REC_H

#include "../src/offline_wkup.h"

class AudioRec {
public:
    AudioRec(OL_WKUP *ol_wkup);
    ~AudioRec();
    static int start_record;
    static int slient_flag;
    static OL_WKUP *ol_wkup;
    void record();
};


#endif