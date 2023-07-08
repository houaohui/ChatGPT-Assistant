//
// Created by fu on 3/2/18.
// 定义常量
//
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <iostream>

// libcurl 返回回调
size_t onWriteData(void * buffer, size_t size, size_t nmemb, void * userp)
{
    std::string * str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size * nmemb);
    return nmemb;
}