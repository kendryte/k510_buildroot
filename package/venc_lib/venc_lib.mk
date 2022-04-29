################################################################################
#
# video encode lib
#
################################################################################

VENC_LIB_SITE = $(BR2_EXTERNAL_K510_PATH)/package/venc_lib/src
VENC_LIB_SITE_METHOD = local
VENC_LIB_INSTALL_STAGING = YES

define VENC_LIB_BUILD_CMDS
	
endef

define VENC_LIB_INSTALL_STAGING_CMDS
	cp -rf $(@D)/libvenc.so $(STAGING_DIR)/lib64/lp64d/libvenc.so
	cp -rf $(@D)/enc_interface.h $(STAGING_DIR)/usr/include/enc_interface.h
endef

define VENC_LIB_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libvenc.so $(TARGET_DIR)/lib64/lp64d/libvenc.so
endef

$(eval $(generic-package))
