#include "time.h"
#include <iostream>

Time::Time()
{

}
Time::~Time()
{

}

void Time::restart()
{
    time_cnt = time(0);
}

int Time::has_pass(int s)
{
    
    int64_t t = time(0) - time_cnt;
    
    return (t > s);
}