#!/bin/bash
set -x
#echo "wjxwwwwwwwwwwwwwwwwwjx"
mount -o remount,ro rootfs / ;
rootdev=$(cat /proc/cmdline  | sed  -n  "s#root=\(\/dev\/mmcblk[0-9]p[0-9]\).*#\1#p" );
fsck.ext2 -p  "${rootdev}"; 
mount -o remount,rw rootfs / ;
