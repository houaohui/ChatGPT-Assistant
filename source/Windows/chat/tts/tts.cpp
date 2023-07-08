#include "tts.h"
#include "tts_common.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "curl\curl.h"
#include "../json/json/json.h"
#include <fstream>

using namespace std;

TTS::TTS(/* args */)
{
    //获取token
    RETURN_CODE res = RETURN_OK;
    res = speech_get_token(accessToken);
    if (res != RETURN_OK) {
        cout << "Error: " << res << endl;
        return;
    } else {
        cout << "tts Token is: " << accessToken << endl;
    }

    char params[100];

    // 发音人选择, 基础音库：0为度小美，1为度小宇，3为度逍遥，4为度丫丫，
    // 精品音库：5为度小娇，103为度米朵，106为度博文，110为度小童，111为度小萌，默认为度小美 
    int per = 0;
    // 语速，取值0-9，默认为5中语速
    int spd = 6;
    // #音调，取值0-9，默认为5中语调
    int pit = 5;
    // #音量，取值0-9，默认为5中音量
    int vol = 5;
    // 下载的文件格式, 3：mp3(default) 4： pcm-16k 5： pcm-8k 6. wav
	int aue = 6;
	// aue对应的格式，format
	const char formats[4][4] = {"mp3", "pcm", "pcm", "wav"};
	format = formats[aue - 3];
    std::cout << "formats:"  << format << std::endl;

	char params_pattern[] = "ctp=1&lan=zh&cuid=%s&per=%d&spd=%d&pit=%d&vol=%d&aue=%d&tok=";
    snprintf(params, sizeof(params), params_pattern , cuid.c_str(),
             per, spd, pit, vol, aue);
    params_url  += params; 
    params_url  += accessToken;
    cout << "parames_url: " << params_url << endl;
}

TTS::~TTS()
{
}

/**
 * @brief 获取token函数
 * 
 * @param token 
 * @return RETURN_CODE 
 */
RETURN_CODE TTS::speech_get_token(string &token)
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

/**
 * @brief 请求语音转文字
 * 
 * @param txt 要转换的文字
 * @return RETURN_CODE 
 */
RETURN_CODE TTS::getResponse(std::string txt)
{
    RETURN_CODE ret = RETURN_OK;
    CURL *curl;
    curl = curl_easy_init(); // 需要释放

    // char *textemp = curl_easy_escape(curl, txt.c_str(), txt.length()); // 需要释放
	// char *tex = curl_easy_escape(curl, textemp, strlen(textemp)); // 需要释放
	// curl_free(textemp);
    // string tex_str = tex;
    // string posturl = "tex=" + tex_str + "&" + params_url;
    // curl_free(tex);

    string posturl = "tex=" + txt + "&" + params_url;
    cout << "POST " << posturl <<endl;
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_URL, API_TTS_URL.c_str());

    //post content
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, posturl.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, posturl.length()); // 音频数据长度
    //call back
    struct http_result result = {1, (char *)this->format.c_str() ,NULL};
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback); // 检查头部
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &result);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);  // 需要释放
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    CURLcode res_curl = curl_easy_perform(curl);

    if (res_curl != CURLE_OK) {
        // curl 失败
        cout << "perform curl error:"<<  curl_easy_strerror(res_curl);
        ret = RETURN_ERROR;
    }
	if (result.fp != NULL) {
		fclose(result.fp);
	}
    curl_easy_cleanup(curl);
    play();
    return ret;
}

void TTS::play()
{
    system("sox result.wav ../1s.wav resul.wav");
    system("sox resul.wav -t waveaudio default -q");
    cout << "play ok"<< endl;
}
