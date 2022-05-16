################################################################################
#
# encode_app
#
################################################################################

ENCODE_APP_SITE = $(BR2_EXTERNAL_K510_PATH)/package/encode_app/src
ENCODE_APP_SITE_METHOD = local

ENCODE_APP_DEPENDENCIES += video_lib
ENCODE_APP_DEPENDENCIES += live555_canaan
ENCODE_APP_DEPENDENCIES += venc_lib
ENCODE_APP_DEPENDENCIES += mediactl_lib
ENCODE_APP_DEPENDENCIES += alsa-lib

define ENCODE_APP_BUILD_CMDS
	BR2_TARGET_BOARD_TYPE=$(BR2_TARGET_BOARD_TYPE) $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) OBJ=encode_app
endef

define ENCODE_APP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/encode_app $(TARGET_DIR)/app/encode_app/encode_app
	$(INSTALL) -D -m 0755 $(@D)/video_sample.conf $(TARGET_DIR)/app/encode_app/video_sample.conf
	$(INSTALL) -D -m 0755 $(@D)/video_sample_720p60.conf $(TARGET_DIR)/app/encode_app/video_sample_720p60.conf
	$(INSTALL) -D -m 0755 $(@D)/video_sample_vga480p75.conf $(TARGET_DIR)/app/encode_app/video_sample_vga480p75.conf
	$(INSTALL) -D -m 0755 $(@D)/imx219_0.conf $(TARGET_DIR)/app/encode_app/imx219_0.conf
	$(INSTALL) -D -m 0755 $(@D)/imx219_1.conf $(TARGET_DIR)/app/encode_app/imx219_1.conf
	$(INSTALL) -D -m 0755 $(@D)/roi_1920x1080.conf $(TARGET_DIR)/app/encode_app/roi_1920x1080.conf
endef

$(eval $(generic-package))
