#ifndef __TIMER_H__
#define __TIMER_H__
#include <cstdint>
#include <sys/time.h>

class Timer 
{
public:
    Timer();
    ~Timer();
    struct timeval tv_now;
    struct timeval tv_last;
    void restart();
    int has_pass(time_t s);

};

#endif
