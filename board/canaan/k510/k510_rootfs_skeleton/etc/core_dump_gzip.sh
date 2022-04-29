#!/bin/sh
exec cat  - > /root/data/coredump/core-$1-$2-$3
#exec gzip - > /root/data/coredump/core-$1-$2-$3.gz
