#!/bin/sh
#set -x
#echo "$0 $# is $*"
if [ "$1" = "eth0" ]; then 
	if [ "$2" = "up" ]; then 
		ifdown  eth0;
		ifup  eth0;	
	else
		ifconfig eth0 0.0.0.0
	fi;
fi
#/usr/sbin/ifplugd   -n -p  -I -i eth0 -r /etc/network/ifplug.sh &