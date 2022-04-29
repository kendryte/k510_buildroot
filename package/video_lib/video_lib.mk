################################################################################
#
# video_lib
#
################################################################################

VIDEO_LIB_SITE = $(BR2_EXTERNAL_K510_PATH)/package/video_lib/src
VIDEO_LIB_SITE_METHOD = local
VIDEO_LIB_INSTALL_STAGING = YES


define VIDEO_LIB_BUILD_CMDS
	$(TARGET_MAKE_ENV) VIDEO_LIB_PATH=$(@D) $(MAKE) -C $(@D) libvideo.so
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/testlib/ all
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/testlib_n/ all
endef

define VIDEO_LIB_INSTALL_STAGING_CMDS
	#cp -rf $(@D)/nncase_linux_runtime/include/* $(STAGING_DIR)/usr/include/
	#cp -rf $(@D)/include/* $(STAGING_DIR)/usr/include/
	cp -rf $(@D)/isp_video.h $(STAGING_DIR)/usr/include/
	cp -rf $(@D)/libvideo.so  $(STAGING_DIR)/lib64/lp64d/libvideo.so
endef

define VIDEO_LIB_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libvideo.so $(TARGET_DIR)/lib64/lp64d/libvideo.so
	#$(INSTALL) -D -m 0755 $(@D)/testlib/test_videolib $(TARGET_DIR)/video_lib/test_videolib
	#$(INSTALL) -D -m 0755 $(@D)/testlib_n/test_videolib_n $(TARGET_DIR)/video_lib/test_videolib_n
	#$(INSTALL) -D -m 0755 $(@D)/testlib_n/test_dualcamera $(TARGET_DIR)/app/video_lib/test_dualcamera
	#$(INSTALL) -D -m 0755 $(@D)/testlib_n/test_scamera $(TARGET_DIR)/app/video_lib/test_scamera
	#$(INSTALL) -D -m 0755 $(@D)/testlib_n/tunning_server_hdmi $(TARGET_DIR)/video_lib/tunning_server_hdmi
	#$(INSTALL) -D -m 0755 $(@D)/testlib_n/tunning_server_dsi $(TARGET_DIR)/app/video_lib/tunning_server_dsi
	#$(INSTALL) -D -m 0755 $(BR2_EXTERNAL_K510_PATH)/package/video_lib/*.argb $(TARGET_DIR)/app/video_lib/
	#$(INSTALL) -D -m 0755 $(BR2_EXTERNAL_K510_PATH)/package/video_lib/*.yuv $(TARGET_DIR)/app/video_lib/
endef

$(eval $(generic-package))
