BR2_VERSION		= 2020.02.11


RED=\e[1;31m
NC=\e[0m

SHELL=/bin/bash

BRW_ROOT	= $(PWD)
BRW_SITE	= https://buildroot.org/downloads/buildroot-$(BR2_VERSION).tar.gz
BRW_FILE	= $(BR2_DL_DIR)/buildroot-$(BR2_VERSION).tar.gz
BRW_DIR		= $(BRW_ROOT)/buildroot-$(BR2_VERSION)
BRW_PATCH_DIR	= $(BRW_ROOT)/patches

TOOLCHAIN_DIR	= $(BRW_ROOT)/toolchain
TOOLCHAIN_NAME	= nds64le-linux-glibc-v5d
TOOLCHAIN_DIR_SITE =https://github.com/andestech/Andes-Development-Kit/releases/download/ast-v3_2_1-release-linux

TOOLCHAIN_NAME_MCU	= nds64le-elf-mculib-v5d
TOOLCHAIN_MCU_DIR_SITE =https://github.com/andestech/Andes-Development-Kit/releases/download/ast-v3_2_3-release-linux

#DEMO_DIR	= $(BRW_ROOT)/demo
#ROOTFS_OVERLAY_PATH	= $(BRW_ROOT)/board/canaan/k510/rootfs_overlay



CONF ?= "k510_crb_lp3_v1_2_defconfig"
O ?= $(CONF)
BR2_DL_DIR ?= $(BRW_ROOT)/dl

define DOWNLOAD
	set -e;\
	if [ ! -d $(BR2_DL_DIR) ]; then \
		if [ -f pkg-download/dl.tar.gz ]; then  \
			tar -zxf pkg-download/dl.tar.gz || { echo -e "\n\nfile pkg-download/dl.tar.gz is error,please delete .\n";exit 1; }  ; \
		fi;	\
		mkdir -p $(BR2_DL_DIR); \
	fi; \
	if [ ! -f $(BRW_FILE) ]; then \
		wget -c $(BRW_SITE) -O $(BRW_FILE); \
	fi; \


endef

define COPYFILES
	set -e; \
	if [ ! -d $(BRW_DIR) ]; then \
		tar --no-same-owner -zxf $(BRW_FILE) -C $(BRW_ROOT); \
		if [ "'ls $(BRW_PATCH_DIR)/*.patch'" != "" ]; then \
			$(BRW_DIR)/support/scripts/apply-patches.sh $(BRW_DIR) $(BRW_PATCH_DIR); \
		fi; \
	fi; \

	if [ ! -d $(TOOLCHAIN_DIR)/$(TOOLCHAIN_NAME) ]; then \
		tar --no-same-owner -xf $(TOOLCHAIN_DIR)/$(TOOLCHAIN_NAME).txz -C $(TOOLCHAIN_DIR); \
	fi; \

	[ -d $(TOOLCHAIN_DIR)/$(TOOLCHAIN_NAME_MCU) ] || tar --no-same-owner -xf $(TOOLCHAIN_DIR)/$(TOOLCHAIN_NAME_MCU).txz -C $(TOOLCHAIN_DIR);
	
endef

define CLEAN
	set -e; \
	cd $(BRW_ROOT); \
	rm -rf $(CONF); \
	rm -rf $(BRW_DIR); \

endef





.PHONY: all
all .DEFAULT: down_toolchain
	@$(call DOWNLOAD)
	@$(call COPYFILES)
	make -C $(BRW_DIR) $(CONF) O=$(BRW_ROOT)/$(O) BR2_EXTERNAL=$(BRW_ROOT)
	make -C $(BRW_ROOT)/$(O)

.PHONY: source
source:
	@$(call DOWNLOAD)
	@$(call COPYFILES)
	make -C $(BRW_DIR) $(CONF) O=$(BRW_ROOT)/$(O) BR2_EXTERNAL=$(BRW_ROOT)
	make -C $(BRW_ROOT)/$(O) source

.PHONY: menuconfig
menuconfig:
	make -C $(BRW_ROOT)/$(O) menuconfig

.PHONY: build
build:
	make -C $(BRW_ROOT)/$(O)

.PHONY: savedefconfig
savedefconfig:
	make -C $(BRW_ROOT)/$(O) savedefconfig

.PHONY: clean
clean:
	@$(call CLEAN)

.PHONY:down_toolchain dl


dl:
	rm -rf pkg-download/dl.tar.gz;
	wget -c  https://kendryte-download.canaan-creative.com/k510/package/dl/v1.0.0/dl.tar.gz  -O pkg-download/dl.tar.gz;
	tar -zxf pkg-download/dl.tar.gz;
	mkdir -p  dl/ai/; wget -c https://kendryte-download.canaan-creative.com/k510/package/ai/v1.0.0/ai_kmodel_data.tar.xz  -O dl/ai/ai_kmodel_data.tar.xz;
	(set -xe;   NNCASE_VER=v1.9.0 ;\
		NNCASE_SITE=https://kendryte-download.canaan-creative.com/k510/nncase/release;\
		NNCASE_PIP_VD=1.9.0.20230322		; \
		NNCASE_PIP_K510_VD=1.9.0.20230323 ;\
		mkdir -p dl/nncase_linux_runtime;  cd dl/nncase_linux_runtime;		\
		wget -c $${NNCASE_SITE}/$${NNCASE_VER}/nncaseruntime-k510-$${NNCASE_VER}.tgz  ; \
		wget -c $${NNCASE_SITE}/$${NNCASE_VER}/nncase-$${NNCASE_PIP_VD}-cp310-cp310-manylinux_2_24_x86_64.whl; \
		wget -c $${NNCASE_SITE}/$${NNCASE_VER}/nncase-$${NNCASE_PIP_VD}-cp37-cp37m-manylinux_2_24_x86_64.whl;\
		wget -c $${NNCASE_SITE}/$${NNCASE_VER}/nncase-$${NNCASE_PIP_VD}-cp38-cp38-manylinux_2_24_x86_64.whl;\
		wget -c $${NNCASE_SITE}/$${NNCASE_VER}/nncase-$${NNCASE_PIP_VD}-cp39-cp39-manylinux_2_24_x86_64.whl; \
		wget -c $${NNCASE_SITE}/$${NNCASE_VER}/nncase_k510-$${NNCASE_PIP_K510_VD}-py2.py3-none-manylinux_2_24_x86_64.whl; \
	)
	
	

	
down_toolchain:
	if [ ! -f toolchain/$(TOOLCHAIN_NAME).txz ] ||  [ "c87c87089fe2f0445a94054e8ae7b947" !=  "$(shell md5sum toolchain/$(TOOLCHAIN_NAME).txz | cut -d' ' -f1 )" ]; then \
		rm -rf toolchain/$(TOOLCHAIN_NAME)* ;\
		wget -c $(TOOLCHAIN_DIR_SITE)/$(TOOLCHAIN_NAME).txz  -O toolchain/$(TOOLCHAIN_NAME).txz;\
		tar --no-same-owner -xf $(TOOLCHAIN_DIR)/$(TOOLCHAIN_NAME).txz -C $(TOOLCHAIN_DIR);\
	fi; 
	if [ ! -f toolchain/$(TOOLCHAIN_NAME_MCU).txz ] || [ "d2dcf2729c2e6b654c4be197c2c75987" !=  "$(shell md5sum  toolchain/$(TOOLCHAIN_NAME_MCU).txz | cut -d' ' -f1 )" ]; then\
		rm -rf toolchain/$(TOOLCHAIN_NAME_MCU)* ;\
		wget -c $(TOOLCHAIN_MCU_DIR_SITE)/$(TOOLCHAIN_NAME_MCU).txz -O toolchain/$(TOOLCHAIN_NAME_MCU).txz;\
		tar --no-same-owner -xf $(TOOLCHAIN_DIR)/$(TOOLCHAIN_NAME_MCU).txz -C $(TOOLCHAIN_DIR);\
	fi;

#mkfs.ext4 -d  $${dir}  $(BR2_DL_DIR)/debian_rootfs.ext4 3G;
		
#update_debian: SHELL=/bin/bash
debian:
	@[ -f ${CONF}/images/sysimage-sdcard.img ] || { echo "please first use 'make CONF=${CONF}'  command build sdk!"; exit 1; }  
	echo "please change to  root user or sudo -s make update_debian"
	(set -xe; dir=debian; debian_tar=$(shell pwd)/board/canaan/k510/debian.tar.gz; rm -rf  $${dir} $${debian_tar}; \
	wget http://ftp.cn.debian.org/debian/pool/main/d/debian-ports-archive-keyring/debian-ports-archive-keyring_2022.02.15_all.deb;\
	dpkg -i debian-ports-archive-keyring_2022.02.15_all.deb;rm -rf debian-ports-archive-keyring_2022.02.15_all.deb;\
		debootstrap --arch=riscv64 --keyring /usr/share/keyrings/debian-ports-archive-keyring.gpg \
			--include=debian-ports-archive-keyring unstable  $${dir}  http://deb.debian.org/debian-ports;	\
		chroot $${dir}	 apt-get update;  chroot $${dir}	 apt-get install -y  ntpdate libgomp1 libatomic1; \
		echo "root:root" | chroot $${dir}  chpasswd;\
		chroot "$$dir" adduser --gecos "Debian user,,," --disabled-password debian ;\
		echo "debian:debian" | chroot $$dir chpasswd;\
		echo "debian" > $${dir}/etc/hostname;\
		echo -e '#!/bin/bash -e \nntpdate ntp.aliyun.com\n'   >$${dir}/etc/rc.local; chmod +x $${dir}/etc/rc.local; \
		echo -e "auto lo\niface lo inet loopback\n\n\nauto eth0\niface eth0 inet dhcp \n" > $${dir}/etc/network/interfaces;\
		chroot $${dir} rm -rf /etc/localtime  ; chroot $${dir}   ln -s /usr/share/zoneinfo/Asia/Shanghai  /etc/localtime ;\
		rsync -a --ignore-times --chmod=u=rwX,go=rX  board/canaan/k510/debian_rootfs_overlay/  $${dir}; \
		chroot $${dir} systemctl enable rootfs_fsck;\
		tar -cjf  $${debian_tar}  $${dir}	; chmod a+rw  $${debian_tar};rm -rf  $${dir};\
		echo "file is  $${debian_tar} ";\
		export CONF=${CONF} ; ./board/canaan/k510/debian.sh ;\
		echo "debian image is ${CONF}/images/sysimage-sdcard-debian.img";\
	)
update_debian_from_last_version:
	(set -xe; dir=debian; debian_tar=$(shell pwd)/board/canaan/k510/debian.tar.gz; rm -rf $${dir}; tar -xf $${debian_tar};  \
	rsync -a --ignore-times --chmod=u=rwX,go=rX  board/canaan/k510/debian_rootfs_overlay/  $${dir}; \
		chroot $${dir} systemctl enable rootfs_fsck;\
	rm -rf  $${debian_tar}; tar -cjf  $${debian_tar}  $${dir}	; chmod a+rw  $${debian_tar};\
	)
help:
	@echo "debian---generate debian image,note:need root privileged "
	@echo "source---down all code "
	@echo "build---only build"
	@echo "all---default,example:make CONF=k510_crb_lp3_v1_2_defconfig"
