
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <iostream>
#include "tts_common.h"

size_t onWriteData(void * buffer, size_t size, size_t nmemb, void * userp)
{
    std::string * str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size * nmemb);
    return nmemb;
}
const int MAX_HEADER_VALUE_LEN = 100;

static RETURN_CODE search_header(const char *buffer, size_t len, const char *key, char *value) {
    size_t len_key = strlen(key);
    char header_key[len_key + 1];
    header_key[len_key] = '\0';
    memcpy(header_key, buffer, len_key);
    if (strcasecmp(key, header_key) == 0 && (len - len_key) < MAX_HEADER_VALUE_LEN) {
        int len_value = len - len_key;
        value[len_value - 1] = '\0';
        memcpy(value, buffer + len_key + 1, len_value);
        return RETURN_OK;
    }
    return RETURN_FAIL;

}

size_t header_callback(char *buffer, size_t size, size_t nitems, struct http_result *result) {
    size_t len = size * nitems;
    char key[] = "Content-Type";
    char value[MAX_HEADER_VALUE_LEN];
    if (search_header(buffer, len, key, value) == RETURN_OK) {
        if (strstr(value, "audio/") != NULL) {
            result->has_error = 0;
        } else {
            fprintf(stderr, "Server return ERROR, %s : %s\n", key, value);

        }
    }
    return len;
}

size_t writefunc_data(void *ptr, size_t size, size_t nmemb, struct http_result *result) {
    char filename[11];
    snprintf(filename, 11, "result.%s", result->has_error ? "txt" : result->format);
    if (result->fp == NULL) {
        result->fp = fopen(filename, "wb+");
        if (result->fp == NULL) {
            // snprintf(g_demo_error_msg, BUFFER_ERROR_SIZE, "%s cannot be opened\n", filename);
            printf("error file write\n");
            return 0;
        }
        printf("Data will be write into %s in the current directory\n", filename);
    }
    // std::cout <<"size: " << size << "nmemb:"<<nmemb<< std::endl;
    return fwrite(ptr, size, nmemb, result->fp);
}