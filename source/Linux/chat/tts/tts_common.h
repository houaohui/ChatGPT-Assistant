#ifndef TTS_COMMON_H
#define TTS_COMMON_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "../asr/common.h"

struct http_result {
    int has_error;
	char *format; // 音频的格式，aue参数设置
    FILE *fp; // 保存结果的文件
};

size_t header_callback(char *buffer, size_t size, size_t nitems, struct http_result *result);

size_t writefunc_data(void *ptr, size_t size, size_t nmemb, struct http_result *result);


#endif //SPEECH_C_DEMO_COMMON_H
