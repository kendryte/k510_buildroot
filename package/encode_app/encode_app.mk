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
	$(INSTALL) -D -m 0755 $(@D)/video_sample_1080x1920.conf $(TARGET_DIR)/app/encode_app/video_sample_1080x1920.conf
	$(INSTALL) -D -m 0755 $(@D)/video_sample_720p60.conf $(TARGET_DIR)/app/encode_app/video_sample_720p60.conf
	$(INSTALL) -D -m 0755 $(@D)/video_sample_vga480p75.conf $(TARGET_DIR)/app/encode_app/video_sample_vga480p75.conf
	$(INSTALL) -D -m 0755 $(@D)/imx219_0.conf $(TARGET_DIR)/app/encode_app/imx219_0.conf
	$(INSTALL) -D -m 0755 $(@D)/imx219_1.conf $(TARGET_DIR)/app/encode_app/imx219_1.conf
	$(INSTALL) -D -m 0755 $(@D)/imx219_1080x1920_0.conf $(TARGET_DIR)/app/encode_app/imx219_1080x1920_0.conf
	$(INSTALL) -D -m 0755 $(@D)/imx219_1080x1920_1.conf $(TARGET_DIR)/app/encode_app/imx219_1080x1920_1.conf
	$(INSTALL) -D -m 0755 $(@D)/roi_1920x1080.conf $(TARGET_DIR)/app/encode_app/roi_1920x1080.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_0.conf $(TARGET_DIR)/app/encode_app/imx385_0.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_video_1920x1080.conf $(TARGET_DIR)/app/encode_app/imx385_video_1920x1080.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_normal.conf $(TARGET_DIR)/app/encode_app/imx385_normal.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_2frame.conf $(TARGET_DIR)/app/encode_app/imx385_2frame.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_3frame.conf $(TARGET_DIR)/app/encode_app/imx385_3frame.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_video_1920x1080_normal.conf $(TARGET_DIR)/app/encode_app/imx385_video_1920x1080_normal.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_video_1920x1080_2frame.conf $(TARGET_DIR)/app/encode_app/imx385_video_1920x1080_2frame.conf
	$(INSTALL) -D -m 0755 $(@D)/imx385_video_1920x1080_3frame.conf $(TARGET_DIR)/app/encode_app/imx385_video_1920x1080_3frame.conf
	$(INSTALL) -D -m 0755 $(@D)/gc2053.conf $(TARGET_DIR)/app/encode_app/gc2053.conf
	$(INSTALL) -D -m 0755 $(@D)/gc2093.conf $(TARGET_DIR)/app/encode_app/gc2093.conf
	$(INSTALL) -D -m 0755 $(@D)/video_drm_gc2093_gc2053_isp_mux.conf $(TARGET_DIR)/app/encode_app/video_drm_gc2093_gc2053_isp_mux.conf
endef

$(eval $(generic-package))
