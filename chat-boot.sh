#!/bin/bash
# 检测网络连接
connected=0;
while [ $connected -eq 0 ]
do
	nmcli dev | grep disconnected > /dev/null
	if [ $? -eq 0 ];
	then
		echo Scanning wifi ...
	else
		connected=1;
		echo WIFI connected!
		echo input any character termination timeout 3s!
		read -s -r -t 3 -n 1 input
		echo "input: '$input'"
		if [[ $input == " " || $char == $'\n' ]]; then
			echo Terminated!
			exit 1
		fi
		if [ -z "$input" ];
		then
			echo Start chat process!
		else
			echo Terminated!
			exit 1
		fi
		#python3 /root/tuling.py 2>&1 &
		python3 /root/chat-gpt-mqtt-client3.py 2>&1 &
		sleep 1s
		python3 /root/onenet.py 2>&1 &
		sleep 1s
		/root/chat_ui > /dev/null 2>&1 &
		/root/chat > /dev/null 2>&1 &

	fi
	sleep 1s
done
