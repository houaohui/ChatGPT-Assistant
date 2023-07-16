Orangepi zero平台，基于ChatGPT的语音助手
1，支持离线唤醒
2，支持连续对话
3，可控制联网设备（不成熟）
4，实时显示对话文字（不稳定）

#安装py库：（部分库没有验证安装名称，写此文档时凭记忆，可根据.py文件里面的库安装）
pip3 install openai （好像没用到）
pip3 install request  (不一定对)
pip3 install pahomqtt
等...

#mqtt服务器
sudo apt install mosquitto

#音频处理工具
sudo apt install sox

#开机加载驱动模块
vi /etc/rc.local
insmod /root/st7789/fbtft/fbtft.ko
insmod /root/st7789/fbtft/fb_st7789v.ko

#设置程序运行环境变量
vi /etc/profile
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root
export POCKETSPHINX_PATH=/root/model
export AUDIODEV=hw:0,0
export AUDIODRIVER=alsa


#启用getty自动登录root服务:
systemctl edit getty@tty1.service
输入以下内容并保存更改：
[Service]
ExecStart=
ExecStart=-/sbin/agetty --autologin root --noclear %I $TERM
运行以下命令重新加载systemd配置：
systemctl daemon-reload
运行以下命令重新启动getty服务：
systemctl restart getty@tty1.service
重新启动你的设备，它应该现在会自动登录到指定的root用户。

#设置用户登录启动脚本
vi ~/.bashrc
/root/chat-boot.sh  //开机或者登录root账户会自动运行chat-boot.sh脚本，如果3秒内按下键盘会终止启动所有进程

# 加载设备树插件
cd st7789/normal/
orangepi-add-overlay normal_spi_st7789.dts

# 按照驱动和驱动配置文件里面的图，填写/boot/orangepiEnv.txt


#文件说明：
chat-boot.sh  启动脚本
key.txt       训练唤醒词的文本，上传到网站可以生成一些文件，替换掉对应的的模型文件即可
make.txt    软件库的编译方式

#程序运行root目录需要包含以下文件：
.
├── 16k.wav  #录音文件
├── 1s.wav    #一秒静音文件（必要）
├── chat        #主进程 （必要）
├── chat-boot.sh   #启动脚本（必要）
├── chat-gpt-mqtt-client3.py #调用gpt对话的进程（必要）
├── chat_ui  #文字输出界面进程（必要）
├── libcrypto.so #交叉编译动态链接库（必要）
├── libcrypto.so.3 #交叉编译软链接（必要）
├── libfreetype.so.6 #交叉编译软链接（必要）
├── libssl.so #交叉编译动态链接库（必要）
├── libssl.so.3 #交叉编译软链接（必要）
├── model #pocketsphinx语音模型文件（必要）
│   └── en-us
│       ├── cmudict-en-us.dict
│       ├── en-us
│       │   ├── feat.params
│       │   ├── mdef
│       │   ├── means
│       │   ├── noisedict
│       │   ├── README
│       │   ├── sendump
│       │   ├── transition_matrices
│       │   └── variances
│       └── en-us.lm.bin
├── mosquitto-repo.gpg.key
├── msyh.ttc #字体文件（必要）
├── onenet.py #联网设备控制进程（必要）
├── result.wav #百度tts自动生成
├── resul.wav #经过拼接处理的语音
├── st7789 #显示屏驱动文件（必要）
│   ├── fb-test-app #测试fb设备的应用层软件
│   ├── fbtft #（必要）
│   │   ├── fb_st7789v.ko
│   │   └── fbtft.ko
│   └── normal
│       ├── normal_spi_st7789.dts #（必要）
├── teng.ttf  #字体文件（必要）
├── test.py #测试chat_ui显示的进程
└── tuling.py #连接图灵机器人的进程（可替换chatgpt进程）

#请使用自己注册的API谢谢！！！
