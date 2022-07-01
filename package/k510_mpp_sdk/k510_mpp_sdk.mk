################################################################################
#
#k510_mpp_sdk
#
################################################################################

K510_MPP_SDK_SITE = $(BR2_EXTERNAL_K510_PATH)/package/k510_mpp_sdk/src
K510_MPP_SDK_SITE_METHOD = local
K510_MPP_SDK_INSTALL_STAGING = YES

define K510_MPP_SDK_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_lib/mpp_sys_lib
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_lib/mpp_vi_lib
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_lib/mpp_vps_lib
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_lib/mpp_venc_lib
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_lib/mpp_vo_lib

	cp -rf $(@D)/mpp_lib/mpp_common/kd_common.h $(STAGING_DIR)/usr/include/kd_common.h
	cp -rf $(@D)/mpp_lib/mpp_sys_lib/kd_sys.h $(STAGING_DIR)/usr/include/kd_sys.h
	cp -rf $(@D)/mpp_lib/mpp_vi_lib/kd_vi.h $(STAGING_DIR)/usr/include/kd_vi.h
	cp -rf $(@D)/mpp_lib/mpp_vps_lib/kd_vps.h $(STAGING_DIR)/usr/include/kd_vps.h
	cp -rf $(@D)/mpp_lib/mpp_venc_lib/kd_venc.h $(STAGING_DIR)/usr/include/kd_venc.h
	cp -rf $(@D)/mpp_lib/mpp_vo_lib/kd_vo.h $(STAGING_DIR)/usr/include/kd_vo.h

	cp -rf $(@D)/mpp_lib/mpp_sys_lib/libmppsys.so $(STAGING_DIR)/lib64/lp64d/libmppsys.so
	cp -rf $(@D)/mpp_lib/mpp_vi_lib/libmppvi.so $(STAGING_DIR)/lib64/lp64d/libmppvi.so
	cp -rf $(@D)/mpp_lib/mpp_vps_lib/libmppvps.so $(STAGING_DIR)/lib64/lp64d/libmppvps.so
	cp -rf $(@D)/mpp_lib/mpp_venc_lib/libmppvenc.so $(STAGING_DIR)/lib64/lp64d/libmppvenc.so
	cp -rf $(@D)/mpp_lib/mpp_vo_lib/libmppvo.so $(STAGING_DIR)/lib64/lp64d/libmppvo.so

	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_vi_sample
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_vps_sample
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_venc_sample
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_vo_sample
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_vio_sample
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_stream_sample
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/mpp_sample/mpp_facedetect_sample
endef

define K510_MPP_SDK_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/mpp_lib/mpp_sys_lib/libmppsys.so $(TARGET_DIR)/lib64/lp64d/libmppsys.so
	$(INSTALL) -D -m 0755 $(@D)/mpp_lib/mpp_vi_lib/libmppvi.so $(TARGET_DIR)/lib64/lp64d/libmppvi.so
	$(INSTALL) -D -m 0755 $(@D)/mpp_lib/mpp_vps_lib/libmppvps.so $(TARGET_DIR)/lib64/lp64d/libmppvps.so
	$(INSTALL) -D -m 0755 $(@D)/mpp_lib/mpp_venc_lib/libmppvenc.so $(TARGET_DIR)/lib64/lp64d/libmppvenc.so
	$(INSTALL) -D -m 0755 $(@D)/mpp_lib/mpp_vo_lib/libmppvo.so $(TARGET_DIR)/lib64/lp64d/libmppvo.so

	mkdir -p $(TARGET_DIR)/app/mpp_sample/ai_sample

	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_vi_sample/conf/* $(TARGET_DIR)/app/mpp_sample/
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_vi_sample/sample_vi $(TARGET_DIR)/app/mpp_sample/sample_vi
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_vps_sample/sample_vps $(TARGET_DIR)/app/mpp_sample/sample_vps
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_venc_sample/sample_venc $(TARGET_DIR)/app/mpp_sample/sample_venc
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_venc_sample/data/*yuv $(TARGET_DIR)/app/mpp_sample
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_vo_sample/sample_vo $(TARGET_DIR)/app/mpp_sample/sample_vo
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_vio_sample/sample_vio $(TARGET_DIR)/app/mpp_sample/sample_vio
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_stream_sample/sample_stream $(TARGET_DIR)/app/mpp_sample/sample_stream
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_facedetect_sample/sample_facedetect $(TARGET_DIR)/app/mpp_sample/ai_sample/sample_facedetect
	$(INSTALL) -D -m 0755 $(@D)/mpp_sample/mpp_facedetect_sample/ai_conf/* $(TARGET_DIR)/app/mpp_sample/ai_sample/
endef

$(eval $(generic-package))
