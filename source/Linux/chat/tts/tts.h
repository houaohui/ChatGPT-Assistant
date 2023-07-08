#ifndef TTS_H
#define TTS_H

#include <iostream>
#include "tts_common.h"


class TTS
{
private:
    /* data */
public:
    TTS(/* args */);
    ~TTS();
    std::string txt_result;
    std::string access_token_result;

    RETURN_CODE getResponse(std::string txt);
    // 获得token
    RETURN_CODE speech_get_token(std::string &token);

    void play();

    /* 存储serverapi地址 */
    std::string serverApiUrl;

    /* 最终需要的assess token */
    std::string accessToken;

    // aue对应的格式，format
	std::string format;
    // {"mp3", "pcm", "pcm", "wav"};

    std::string cuid = "1234567";

    std::string params_url;

    /* 填写网页上申请的appkey 如 g_api_key="g8eBUMSokVB1BHGmgxxxxxx" */
    const std::string api_key = "TCAeRVjcQVCfOeE5V0IM5pfiw";

    /* 填写网页上申请的APP SECRET 如 $secretKey="94dc99566550d87f8fa8ece112xxxxx" */
    const std::string secret_key = "iDVRr7e0Lo4o5ssdXOD6lGRYxE7pYOty2";

    /* 获取token的接口*/
    const std::string token_org = "http://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id="+api_key+"&client_secret="+secret_key;

    /* 百度服务器API接口，发送语音可返回识别结果 */
    const std::string API_TTS_URL = "http://tsn.baidu.com/text2audio";

};


#endif // !TTS_H