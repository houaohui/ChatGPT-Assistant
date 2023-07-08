#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <iostream>
#include <string.h>

/**
 * @brief 函数返回值定义
 */
typedef enum RETURN_CODE {
    RETURN_OK = 0, // 返回正常
    RETURN_ERROR = 1, // 返回错误
    RETURN_FAIL = 2, // 返回失败
    ERROR_TOKEN_CURL = 13, // TOKEN CURL 调用错误
    ERROR_TOKEN_PARSE_ACCESS_TOKEN = 15,  // access_token字段在返回结果中不存在
    ERROR_TOKEN_PARSE_SCOPE = 16, // 解析scope字段，或者scope不存在
    ERROR_ASR_FILE_NOT_EXIST = 101, // 本地文件不存在
    ERROR_ASR_CURL = 102 // 识别 curl 错误
} RETURN_CODE;



/**
 * @see libcurl CURLOPT_WRITEFUNCTION
 *
 * @brief curl回调，http请求的结果在result中，注意需要释放free(*result);
 * @param ptr
 * @param size
 * @param nmemb
 * @param result 传入时必需是NULL， 使用后自行释放
 * @return
 */
size_t onWriteData(void * buffer, size_t size, size_t nmemb, void * userp);

#endif //SPEECH_C_DEMO_COMMON_H
