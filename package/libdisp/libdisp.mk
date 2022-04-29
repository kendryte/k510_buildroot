################################################################################
#
# libdisp
#
################################################################################
LIBDISP_SITE = $(BR2_EXTERNAL_K510_PATH)/package/libdisp/src
LIBDISP_SITE_METHOD = local
LIBDISP_INSTALL_STAGING = YES

LIBDISP_DEPENDENCIES = libdrm
LIBDISP_CFLAGS = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include/libdrm
LIBDISP_LDFLAGS = -L$(STAGING_DIR)/usr/lib -ldrm

define LIBDISP_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) CFLAG="$(LIBDISP_CFLAGS)" LDFLAG="$(LIBDISP_LDFLAGS)" all
endef

define LIBDISP_INSTALL_STAGING_CMDS
	cp -rf $(@D)/libdisp.so  $(STAGING_DIR)/lib64/lp64d/libdisp.so
	cp -rf $(@D)/disp.h $(STAGING_DIR)/usr/include/disp.h
endef

define LIBDISP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libdisp.so $(TARGET_DIR)/lib64/lp64d/libdisp.so
endef

$(eval $(generic-package))