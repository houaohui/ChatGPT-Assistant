#ifndef TIME_H
#define TIME_H
#include <cstdint>
class Time 
{
public:
    Time();
    ~Time();
    int64_t time_cnt;
    void restart();
    int has_pass(int s);

};


#endif