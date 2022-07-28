################################################################################
#
# mediactl_lib
#
################################################################################

MEDIACTL_LIB_SITE = $(BR2_EXTERNAL_K510_PATH)/package/mediactl_lib/src
MEDIACTL_LIB_SITE_METHOD = local
MEDIACTL_LIB_INSTALL_STAGING = YES
MEDIACTL_LIB_DEPENDENCIES += libdrm rapidjson

define MEDIACTL_LIB_BUILD_CMDS
	$(TARGET_MAKE_ENV) MEDIACTL_LIB_PATH=$(@D) $(MAKE) -C $(@D) libmediactl.so
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/v4l2_demo/ all
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/v4l2_drm/ all
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/v4l2_test/ all
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/v4l2_drm_isptool/ all
endef

define MEDIACTL_LIB_INSTALL_STAGING_CMDS
	cp -rf $(@D)/libmediactl.so  $(STAGING_DIR)/lib64/lp64d/libmediactl.so
	cp -rf $(@D)/media_ctl.h  $(STAGING_DIR)/usr/include
	cp -rf $(@D)/isp/cJSON.h  $(STAGING_DIR)/usr/include
endef

define MEDIACTL_LIB_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libmediactl.so $(TARGET_DIR)/lib64/lp64d/libmediactl.so
	mkdir $(TARGET_DIR)/app/mediactl_lib/ -p
	#$(INSTALL) -D -m 0755 $(@D)/v4l2_demo/v4l2-demo $(TARGET_DIR)/app/mediactl_lib/
	#$(INSTALL) -D -m 0755 $(@D)/v4l2_demo/*.conf $(TARGET_DIR)/app/mediactl_lib/
	$(INSTALL) -D -m 0755 $(@D)/v4l2_drm/v4l2_drm.out $(TARGET_DIR)/app/mediactl_lib/
	#$(INSTALL) -D -m 0755 $(@D)/v4l2_drm/video_drm*.conf $(TARGET_DIR)/app/mediactl_lib/
	#$(INSTALL) -D -m 0755 $(@D)/v4l2_drm/imx219_1080x1920_0.conf $(TARGET_DIR)/app/mediactl_lib/
	#$(INSTALL) -D -m 0755 $(@D)/v4l2_test/v4l2_test.out $(TARGET_DIR)/app/mediactl_lib/
	#$(INSTALL) -D -m 0755 $(@D)/v4l2_test/video_test.conf $(TARGET_DIR)/app/mediactl_lib/
	$(INSTALL) -D -m 0755 $(@D)/v4l2_drm_isptool/v4l2_drm_isptool.out $(TARGET_DIR)/app/mediactl_lib/
	$(INSTALL) -D -m 0755 $(@D)/config/*.conf $(TARGET_DIR)/app/mediactl_lib/
endef

$(eval $(generic-package))
