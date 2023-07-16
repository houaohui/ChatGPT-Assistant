
#include <iostream>
#include "timer.h"
#include <sys/time.h>

Timer::Timer()
{

}
Timer::~Timer()
{

}

void Timer::restart()
{
    gettimeofday(&this->tv_now,NULL);
    this->tv_last = this->tv_now;
}

int Timer::has_pass(time_t s)
{
    gettimeofday(&this->tv_now,NULL);
    

    long seconds = this->tv_now.tv_sec - this->tv_last.tv_sec;
    long microseconds = this->tv_now.tv_usec - this->tv_last.tv_usec;

    int ret = (seconds * 1000) + (microseconds/1000);

    if (ret > s * 1000) {
        printf("time %u:%u\n",tv_now.tv_sec,tv_now.tv_usec);
        printf("time %u:%u\n",tv_last.tv_sec,tv_last.tv_usec);
    }
    return (ret > s * 1000);
}
