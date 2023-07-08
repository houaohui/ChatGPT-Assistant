#include "asr.h"
#include "common.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "curl\curl.h"
#include "../json/json/json.h"
#include <fstream>

string ASR::txt_result;

ASR::ASR()
{

    postFormat = PCM;
    // 获取token
    RETURN_CODE res = RETURN_OK;
    res = speech_get_token(accessToken);
    if (res != RETURN_OK) {
        cout << "Error: " << res << endl;
    } else {
        cout << "Token is: " << accessToken << endl;
    }
    
}

// 从fp读取文件内容，长度保存在content_len
char *read_file_data(FILE *fp, int *content_len) {
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    *content_len = len;
    char *data = (char *) malloc(len);
    if (data == NULL) {
        fprintf(stderr, "malloc size %d failed", len);
        exit(11);
    }
    fread(data, 1, len, fp);
    return data;

}

RETURN_CODE ASR::getResponse()
{
    string result;
    RETURN_CODE ret = RETURN_OK;
    CURLcode res = CURLE_OK;
    CURL *curl;

    int content_len = 0;
    const char * filename = "16k.wav";
    FILE *file= fopen(filename, "r");
    if (file == NULL) {
        //文件不存在
        perror("file open error!\n");
        return ERROR_ASR_FILE_NOT_EXIST;
    }
    char *audio_data = read_file_data(file, &content_len); // 读取文件， 需要释放

    string server_url = server_api + accessToken;
    cout << "server url is: " << server_url << endl;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, server_url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;


        if (this->postFormat == PCM) {
            headers = curl_slist_append(headers, "Content-Type: audio/pcm;rate=16000");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, audio_data); // 音频数据
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, content_len); // 音频数据长度

        } else if (this->postFormat == JSON) {
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "Accept: application/json");
            const char *data = "{\"format\":\"pcm\",\"rate\":16000,\"channel\":1,\"token\":\"\"}";
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        }

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
        //请求信息
        res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            Json::Reader reader;
            Json::Value root;
            if (reader.parse(result, root))
            {
                // cout << "get response: "<< result << endl;
                cout << "get response: "<< result << endl;
                txt_result = root["result"][0].asString();
                cout << "txt_result: " << txt_result << endl;
                // token = root["access_token"].asString();
            }
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            ret = RETURN_ERROR;
        }
    }

    //关闭文件
    if (file != NULL) {
        fclose(file);
    }

    curl_easy_cleanup(curl);
    return ret;
}


RETURN_CODE ASR::speech_get_token(string &token)
{
    //获取Assess token
    CURLcode res = CURLE_OK;
    RETURN_CODE ret = RETURN_OK;
    CURL *curl = curl_easy_init();
    if(curl) {

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, token_org.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        // 打印详情
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Accept: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        const char *data = "";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &token);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
        res = curl_easy_perform(curl);
        if(res == CURLE_OK)
        {
            Json::Reader reader;
            Json::Value root;
            if (reader.parse(token, root))
            {
                cout << "find token!"<< endl;
                // cout << "token is: " << root["access_token"].asString();
                token = root["access_token"].asString();
            }
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            ret = RETURN_ERROR;
        }
       
    }
    curl_easy_cleanup(curl);
    return ret;
}

ASR::~ASR()
{
    // curl_easy_cleanup(curl);
}



