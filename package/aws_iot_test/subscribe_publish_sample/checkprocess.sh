#!/bin/sh
while true
tcpdump port 1935 > /dev/null 2>&1 & 
do
    ps  -ef | grep ffmpeg | grep -v grep
    if  [ $? - ne  0 ]
    then
    continue
    else
    ffmpeg -f v4l2 -s 1920x1080 -isp 1 -buf_type 2 -r 30 -i /dev/video3 -vcodec libk510_h264 -idr_freq 25 -an -f flv $1
    fi
done
