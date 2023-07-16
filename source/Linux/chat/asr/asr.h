#ifndef ASR_H
#define ASR_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "curl/curl.h"
#include "../json/json/json.h"
#include <fstream>
#include "common.h"

using namespace std;

typedef enum {
    PCM,
    JSON
} Post_Format_Type;

class ASR 
{
public:
    ASR();
    ~ASR();
    

    
    static string txt_result;
    string access_token_result;

    Post_Format_Type postFormat;
    RETURN_CODE getResponse();
    RETURN_CODE speech_get_token(string &token);

    /* 存储serverapi地址 */
    string serverApiUrl;

    /* 最终需要的assess token */
    string accessToken;

        /* 填写网页上申请的appkey 如 g_api_key="g8eBUMSokVB1BHGmgxxxxxx" */
    const string api_key = "你的api-key";

    /* 填写网页上申请的APP SECRET 如 $secretKey="94dc99566550d87f8fa8ece112xxxxx" */
    const string secret_key = "iDVRr7e0Lo4o5ssXOD6lGRYxE7pYOty2";

    /* 获取token的接口*/
    const string token_org = "http://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id="+api_key+"&client_secret="+secret_key;

    /* 百度服务器API接口，发送语音可返回识别结果 */
    const string server_api = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=1234567&token=";
};

#endif // !ASR_H
