################################################################################
#
# dsp_app_new
#
################################################################################

DSP_APP_NEW_SITE = $(BR2_EXTERNAL_K510_PATH)/package/dsp_app_new/src
DSP_APP_NEW_SITE_METHOD = local
#FIRMWARE_SRC=$(@D)/k510_evb_test_firmware_src
#FIRMWARE_BUILD_OPS= ARCH=riscv  PATH=$(BR2_EXTERNAL_K510_PATH)/toolchain/nds64le-elf-mculib-v5d/bin:${PATH}


define DSP_APP_NEW_BUILD_CMDS
	BR2_TARGET_EVB_FIRMWARE_LOAD_ADD=$(BR2_TARGET_EVB_FIRMWARE_LOAD_ADD) $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
	
endef

define DSP_APP_NEW_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/dsp_app_new.out $(TARGET_DIR)/app/dsp_app_new/dsp_app	
endef

$(eval $(generic-package))
