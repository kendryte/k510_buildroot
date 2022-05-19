################################################################################
#
# librtmp
#
################################################################################

# LIBRTMP_VERSION = 2.3
# LIBRTMP_SOURCE = rtmpdump-$(LIBRTMP_VERSION).tgz
# LIBRTMP_SITE = http://rtmpdump.mplayerhq.hu/download
# LIBRTMP_INSTALL_STAGING = YES

#LIBRTMP_VERSION_FULL = f1b83c10d8beb43fcc70a6e88cf4325499f25857
#LIBRTMP_VERSION_HEAD = f1b83c1
LIBRTMP_VERSION_FULL = fa8646daeb19dfd12c181f7d19de708d623704c0
LIBRTMP_VERSION_HEAD = fa8646daeb19dfd12c181f7d19de708d623704c0
LIBRTMP_SOURCE = rtmpdump-$(LIBRTMP_VERSION_HEAD).tar.gz
LIBRTMP_SITE = https://git.ffmpeg.org/gitweb/rtmpdump.git/snapshot/$(LIBRTMP_VERSION_FULL).tar.gz
LIBRTMP_INSTALL_STAGING = YES

LIBRTMP_LICENSE = GPLv2

LIBRTMP_CONF_ENV += CFLAGS="$(LIBRTMP_CFLAGS)"
LIBRTMP_CONF_OPTS += $(call qstrip,$(BR2_PACKAGE_LIBRTMP_EXTRACONF))

LIBRTMP_DEPENDENCIES += libopenssl

LIBRTMP_MAKE_ENV = $(TOPDIR)/../toolchain/nds64le-linux-glibc-v5d/bin:$(BUILD_DIR)/hostt/bin:$(BUILD_DIR)/host/sbin
LIBRTMP_MAKE = $(BUILD_DIR)/linux-custom/tools/perf/tests/make

define LIBRTMP_BUILD_CMDS
	# # $(TARGET_MAKE_ENV) $(MAKE) CROSS_COMPILE=riscv64-linux- INC+=-I../../toolchain/nds64le-linux-glibc-v5d/include DESTDIR=$(TARGET_DIR) PREFIX= -C $(@D) install
	# # $(TARGET_MAKE_ENV) $(MAKE) INC+=-I../../toolchain/nds64le-linux-glibc-v5d/include DESTDIR=$(TARGET_DIR) PREFIX= -C $(@D) install
	# $(TARGET_MAKE_ENV) $(MAKE) INC+=-I../../toolchain/nds64le-linux-glibc-v5d/include DESTDIR=$(@) PREFIX= -C $(@D) install
	# # $(TARGET_MAKE_ENV) $(MAKE) INC=-I$(BR2_TOOLCHAIN_EXTERNAL_PATH)/include DESTDIR=$(TARGET_DIR) PREFIX=/usr/local -C $(@D) install
	# $(TARGET_MAKE_ENV) $(MAKE) CROSS_COMPILE=riscv64-unknown-linux- INC+=-I$(BR2_TOOLCHAIN_EXTERNAL_PATH)/include  INC+=-I$(HOST_DIR)/include DESTDIR=$(@) PREFIX= -C $(@D) install
	# $(TARGET_MAKE_ENV) $(MAKE) PATH=$(PATH):$(TOPDIR)/../toolchain/nds64le-linux-glibc-v5d/bin CROSS_COMPILE=riscv64-unknown-linux- INC+=-I$(TOPDIR)/../toolchain/nds64le-linux-glibc-v5d/include  INC+=-I$(STAGING_DIR)/usr/include DESTDIR=$(STAGING_DIR) XDEF=-DNO_SSL PREFIX= -C $(@D) install
	$(TARGET_MAKE_ENV) $(MAKE) CROSS_COMPILE=riscv64-linux- INC+=-I$(TOPDIR)/../toolchain/nds64le-linux-glibc-v5d/include  INC+=-I$(STAGING_DIR)/usr/include DESTDIR=$(STAGING_DIR) XDEF=-DNO_SSL PREFIX= -C $(@D) install
endef


define LIBRTMP_INSTALL_TARGET_CMDS
	# $(INSTALL) -D -m 0755 $(@D)/librtmp/librtmp.a $(TARGET_DIR)/librtmp/librtmp.a
	# $(INSTALL) -D -m 0755 $(@D)/librtmp/librtmp.so $(TARGET_DIR)/librtmp/librtmp.so
	# $(INSTALL) -D -m 0755 $(@D)/librtmp/librtmp.so.1 $(TARGET_DIR)/librtmp/librtmp.so.1
	# $(INSTALL) -D -m 0755 $(@D)/*.h $(TARGET_DIR)/usr/include/librtmp
	# $(INSTALL) -D -m 0755 $(@D)/librtmp/*.h $(TARGET_DIR)/usr/include/librtmp/librtmp

endef

define LIBRTMP_INSTALL_STAGING_CMDS
	cp -rf $(@D)/librtmp/librtmp.a $(STAGING_DIR)/lib64/lp64d/librtmp.a
	cp -rf $(@D)/librtmp/librtmp.so $(STAGING_DIR)/lib64/lp64d/librtmp.so
	cp -rf $(@D)/librtmp/librtmp.so.1 $(STAGING_DIR)/lib64/lp64d/librtmp.so.0
	rm -rf $(STAGING_DIR)/usr/include/librtmp
	mkdir $(STAGING_DIR)/usr/include/librtmp
	mkdir $(STAGING_DIR)/usr/include/librtmp/librtmp
	cp -rf $(@D)/*.h $(STAGING_DIR)/usr/include/librtmp
	cp -rf $(@D)/librtmp/*.h $(STAGING_DIR)/usr/include/librtmp/librtmp
endef

# define LIBRTMP_CONFIGURE_CMDS

# endef

# $(eval $(autotools-package))
$(eval $(generic-package))
