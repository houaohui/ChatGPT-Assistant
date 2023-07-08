#include <WiFi.h>
#include "PubSubClient.h"
#include "Ticker.h"

/* 使用0.96寸的OLED屏幕需要使用包含这个头文件 */
#include "SSD1306Wire.h"
/* 设置oled屏幕的相关信息 */  //有一些引脚接口不支持I2C 
const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
#define SDA_PIN 4                       // io4 
#define SCL_PIN 5                       // io5
/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */
SSD1306Wire oled(I2C_ADDR, SDA_PIN, SCL_PIN);

int state_led_contrl = 0;

const int led =18; //灯的接口

//#define WIFI_SSID        "1"//替换自己的WIFI
//#define WIFI_PASSWD      "111aaa222"//替换自己的WIFI
const char *ssid = "16s"; //wifi名称
const char *password = "87654321";//wifi密码

const char *mqtt_server = "183.230.40.39"; //onenet 的 IP地址
const int port = 6002;                     //端口号

#define mqtt_devid "1087771502" //设备ID
#define mqtt_pubid "606372"        //产品ID
#define mqtt_password "kongdiao" //鉴权信息

WiFiClient espClient;           //创建一个WIFI连接客户端
PubSubClient mqttClient(espClient);  //
PubSubClient client(espClient); // 创建一个PubSub客户端, 传入创建的WIFI客户端

char msg_buf[200];               //发送信息缓冲区
char msgJson[80]; //要发送的json格式的数据
unsigned short json_len = 0;                      //json长度

//信息模板
char dataTemplate[] = "{\"temp\":%.2f,\"switch\":%d}";  //  temp humi要与onenet相对应
Ticker tim1; //定时器,用来循环上传数据
//测试屏幕显示
void drawRect(void) {
  for (int16_t i=0; i<oled.getHeight()/2; i+=2) {
    oled.drawRect(i, i, oled.getWidth()-2*i, oled.getHeight()-2*i);
    oled.display();
    delay(50);
  }
}

void init_Wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
   {
        Serial.println("正在连接中----\n");
        delay(500);
    }
    Serial.println("WIFI已连接\n");
    Serial.println(WiFi.localIP());
}


void post_close_switch()
{
  if (client.connected())
  {
    snprintf(msgJson,80,dataTemplate,25.0,0); 
    json_len = strlen(msgJson);                   //msgJson的长度
    msg_buf[0] = char(0x03);                       //要发送的数据必须按照ONENET的要求发送, 根据要求,数据第一位是3
    msg_buf[1] = char(json_len >> 8);              //数据第二位是要发送的数据长度的高八位
    msg_buf[2] = char(json_len & 0xff);            //数据第三位是要发送数据的长度的低八位
    memcpy(msg_buf + 3, msgJson, strlen(msgJson)); //从msg_buf的第四位开始,放入要传的数据msgJson
    msg_buf[3 + strlen(msgJson)] = 0;              //添加一个0作为最后一位, 这样要发送的msg_buf准备好了

    Serial.print("public the data:");
    Serial.print(msgJson);
    client.publish("$dp", (uint8_t *)msg_buf, 3+strlen(msgJson));
    //发送数据到主题
    delay(1000);
    
  }
}
//收到主题下发的回调, 注意这个回调要实现三个形参 1:topic 主题, 2: payload: 传递过来的信息 3: length: 长度
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
 
  if ((char)payload[0] == '0') {
    state_led_contrl=0;
  }
  if ((char)payload[0] == '1') {
    state_led_contrl=1;
  }

}
void clientReconnect()
{
  while (!client.connected()) //再重连客户端
  {
    Serial.print("reconnect MQTT...");
    if (client.connect(mqtt_devid, mqtt_pubid, mqtt_password))
    {
      Serial.print("connected");
    }
    else
    {
      Serial.print("failed");
      Serial.print(client.state());
      Serial.print("try again in 5 sec");
     delay(5000);
    }
  }
}

void setup() {
   
  Serial.begin(115200);
  pinMode(led,OUTPUT);//输出

  init_Wifi();   //调用函数连接WIFI
  Serial.print(F("test!"));
    /*  oled屏幕初始化 */
 oled.init();
 oled.flipScreenVertically();          // 设置屏幕翻转
 oled.setContrast(255);                // 设置屏幕亮度
 drawRect();                           // 测试屏幕显示
 oled.clear(); oled.display();         // 清除屏幕                                      
  client.setServer(mqtt_server, port);                   //设置客户端连接的服务器,连接Onenet服务器, 使用6002端口
  client.connect(mqtt_devid, mqtt_pubid, mqtt_password); //客户端连接到指定的产品的指定设备.同时输入鉴权信息
  if (client.connected())
  {
    Serial.print("OneNet is connected!");//判断以下是不是连好了.
  }
  client.setCallback(callback); //订阅命令下发主题
  // tim1.attach(5, post_close_switch);                            //定时每5秒调用一次发送数据函数sendTempAndHumi
  post_close_switch(); //开机关闭电灯
}

void loop() {
  oled.clear(); 
  oled.setFont(ArialMT_Plain_24);       // 设置字体
  if(state_led_contrl == 0) {
      oled.drawString(0,0, "off"); // 将要显示的字母写入缓存
  } else {
    oled.drawString(0,0, "on" ); // 将要显示的字母写入缓存
  }
  oled.display();         



  if (!WiFi.isConnected()) //先看WIFI是否还在连接
  {
    init_Wifi();
  }
  if (!client.connected()) //如果客户端没连接ONENET, 重新连接
  {
    clientReconnect();
    delay(100);
  }
  
  client.loop(); //客户端循环检测


}
