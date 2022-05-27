#!/bin/bash
set -x
#${BUILD_DIR},
commitid="unkonwn"
last_tag="unkonwn"
git rev-parse --short HEAD  &&  commitid=$(git rev-parse --short HEAD) 
git describe --tags `git rev-list --tags --max-count=1` && last_tag=$(git describe --tags `git rev-list --tags --max-count=1`)

ver="${last_tag}-${commitid}-$(date "+%Y%m%d-%H%M%S%Z")-$(whoami)-$(hostname)"
echo -e "#############SDK VERSION######################################" >${TARGET_DIR}/etc/version/release_version
echo -e ${ver} >> ${TARGET_DIR}/etc/version/release_version
echo -e "##############################################################" >>${TARGET_DIR}/etc/version/release_version
exit 0


#############SDK VERSION######################################
#MX2_DEV_0158-6dc38754-20220428-115825CST-wangjianxin-MAGI-SYS-IRUEL-1
##############################################################

#############SDK VERSION######################################
#unkonwn-unkonwn-20220428-115730CST-wangjianxin-MAGI-SYS-IRUEL-1
##############################################################


