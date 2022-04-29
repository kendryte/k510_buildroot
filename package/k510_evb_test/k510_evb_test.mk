################################################################################
#
# dsp_app_new
#
################################################################################

K510_EVB_TEST_SITE = $(BR2_EXTERNAL_K510_PATH)/package/k510_evb_test/src
K510_EVB_TEST_SITE_METHOD = local
K510_EVB_TEST_INSTALL_STAGING = YES

FIRMWARE_BUILD_OPS= ARCH=riscv  PATH=$(BR2_EXTERNAL_K510_PATH)/toolchain/nds64le-elf-mculib-v5d/bin:${PATH} \
		BR2_TARGET_EVB_FIRMWARE_LOAD_ADD=$(BR2_TARGET_EVB_FIRMWARE_LOAD_ADD)

define K510_EVB_TEST_BUILD_CMDS
	$(if $(BR2_TARGET_K510_EVB_TEST_FFT_FIRMWARE),\
		$(FIRMWARE_BUILD_OPS) $(MAKE) -C $(@D)  MODE=evblp3 TARGET=test/fft )
	
	$(if $(BR2_TARGET_K510_EVB_TEST_MAILBOX_FIRMWARE),\
		$(FIRMWARE_BUILD_OPS) $(MAKE) -C $(@D)  MODE=evblp3 TARGET=test/mailbox_demo )

	$(if $(BR2_TARGET_K510_EVB_TEST_SIMD_UMUL8_FIRMWARE),\
		$(FIRMWARE_BUILD_OPS) $(MAKE) -C $(@D)  MODE=evblp3 TARGET=test/simd_umul8_demo )
	
	$(FIRMWARE_BUILD_OPS) $(MAKE) -C $(@D)  MODE=evblp3 BSP=libbsp.a
endef

define K510_EVB_TEST_INSTALL_STAGING_CMDS
	cp -rf $(@D)/libbsp.a $(STAGING_DIR)/lib64/lp64d/libbsp.a
	cp -rf $(@D)/bsp/include $(STAGING_DIR)/usr/include/bsp
	cp -rf $(@D)/bsp/utils $(STAGING_DIR)/usr/include/bsp
endef

define K510_EVB_TEST_INSTALL_TARGET_CMDS
	#$(INSTALL) -D -m 0755 $(@D)/dsp_app_new.out $(TARGET_DIR)/app/dsp_app_new/dsp_app
	$(if $(BR2_TARGET_K510_EVB_TEST_FFT_FIRMWARE), \
		$(INSTALL) -D -m 0755 $(@D)/test/fft/fft.bin  $(TARGET_DIR)/app/dsp_app_new/fft.bin )
	$(if $(BR2_TARGET_K510_EVB_TEST_MAILBOX_FIRMWARE), \
		$(INSTALL) -D -m 0755 $(@D)/test/mailbox_demo/mailbox_demo.bin  $(TARGET_DIR)/app/dsp_app_new/mailbox_demo.bin )

	$(if $(BR2_TARGET_K510_EVB_TEST_SIMD_UMUL8_FIRMWARE), \
		$(INSTALL) -D -m 0755 $(@D)/test/simd_umul8_demo/simd_umul8_demo.bin  $(TARGET_DIR)/app/dsp_app_new/simd_umul8_demo.bin )

endef


$(eval $(generic-package))
