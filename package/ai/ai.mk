################################################################################
#
# ai
#
################################################################################
AI_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
AI_SITE = $(AI_LOCAL_PATH)
AI_SOURCE = code.tar

AI_SITE_METHOD = file
AI_KMODEL_DATA_VERSION = v1.0.0
AI_KMODEL_DATA_SITE = https://kendryte-download.canaan-creative.com/k510/package/ai/$(AI_KMODEL_DATA_VERSION)/ai_kmodel_data.tar.xz
AI_EXTRA_DOWNLOADS = $(call qstrip,$(AI_KMODEL_DATA_SITE))
MODEL=$(AI_DIR)/ai_kmodel_data/kmodel_release

AI_PRE_DOWNLOAD_HOOKS = ai_pre_download_hooks_tar_code
define ai_pre_download_hooks_tar_code
	rm -rf $(AI_LOCAL_PATH)/code.tar;
	tar -cf $(AI_LOCAL_PATH)/code.tar -C$(AI_LOCAL_PATH) code
endef

AI_POST_EXTRACT_HOOKS = AI_POST_EXTRACT_HOOKS_KMODEL_DATA
define AI_POST_EXTRACT_HOOKS_KMODEL_DATA
	rm -rf $(AI_DL_DIR)/$(AI_SOURCE);
	rm -rf $(AI_LOCAL_PATH)/code.tar;
	tar -xf $(AI_DL_DIR)/ai_kmodel_data.tar.xz -C $(AI_DIR)
endef
AI_CXXFLAGS = $(TARGET_CXXFLAGS)
AI_CFLAGS = $(TARGET_CFLAGS)

AI_CONF_OPTS += \
        -DCMAKE_CXX_FLAGS="$(AI_CXXFLAGS) -I$(STAGING_DIR)/usr/include/opencv4 -I$(STAGING_DIR)/usr/include/libdrm" \
        -DCMAKE_C_FLAGS="$(AI_CFLAGS) -I$(STAGING_DIR)/usr/include/opencv4 -I$(STAGING_DIR)/usr/include/libdrm -I$(STAGING_DIR)/usr/include" \
	-DCMAKE_INSTALL_PREFIX="/app/ai"


AI_DEPENDENCIES += mediactl_lib nncase_linux_runtime opencv4 libdrm

define AI_COMPILE_MODEL
	mkdir -p $(TARGET_DIR)/app/ai/kmodel
	cp -r $(@D)/ai_kmodel_data/kmodel_release   $(TARGET_DIR)/app/ai/kmodel/
	cp -r $(@D)/ai_kmodel_data/data $(TARGET_DIR)/app/ai/
	#tar -xf $(AI_DL_DIR)/kmodel.tar.xz -C  $(TARGET_DIR)/app/ai

	#demo7
	mkdir -p $(TARGET_DIR)/app/ai/kmodel/kmodel_compile/object_detect_demo
	cd $(@D) && /usr/bin/python3 object_detect_demo/od_onnx.py --quant_type uint8 --model ai_kmodel_data/model_file/object_detect/yolov5sFocus_320x3.onnx
	cp $(@D)/od.kmodel $(TARGET_DIR)/app/ai/kmodel/kmodel_compile/object_detect_demo/od_uint8.kmodel
	cd $(@D) && /usr/bin/python3 object_detect_demo/od_onnx.py --quant_type bf16 --model ai_kmodel_data/model_file/object_detect/yolov5sFocus_320x3.onnx
	cp $(@D)/od.kmodel $(TARGET_DIR)/app/ai/kmodel/kmodel_compile/object_detect_demo/od_bf16.kmodel
	
	#demo1
	mkdir -p $(TARGET_DIR)/app/ai/kmodel/kmodel_compile/retinaface_mb_320
	cd $(@D) && /usr/bin/python3 retinaface_mb_320/rf_onnx.py --quant_type uint8 --model ai_kmodel_data/model_file/retinaface/retinaface_mobile0.25_320.onnx
	cp $(@D)/rf.kmodel $(TARGET_DIR)/app/ai/kmodel/kmodel_compile/retinaface_mb_320/rf_uint8.kmodel
	cd $(@D) && /usr/bin/python3 retinaface_mb_320/rf_onnx.py --quant_type bf16 --model ai_kmodel_data/model_file/retinaface/retinaface_mobile0.25_320.onnx
	cp $(@D)/rf.kmodel $(TARGET_DIR)/app/ai/kmodel/kmodel_compile/retinaface_mb_320/rf_bf16.kmodel
endef

AI_POST_INSTALL_TARGET_HOOKS += AI_COMPILE_MODEL

$(eval $(cmake-package))
