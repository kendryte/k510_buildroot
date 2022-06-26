#!/bin/sh
STR="UUID"
FIND_FILE=online
while true
do
    sleep 60
    ag=`ps -ef | grep ffmpeg | grep -v grep | wc -l`
    if  [ "$ag" -ne  0 ]
    then
    rm $FIND_FILE
    wget http://web-loadbalancer-436179122.cn-north-1.elb.amazonaws.com.cn/videostreams/online
    if [ `grep -c "$STR" $FIND_FILE` -eq '0' ];then
    killall -9 ffmpeg
    fi
    fi
done