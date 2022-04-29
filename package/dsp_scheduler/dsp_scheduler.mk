################################################################################
#
# dsp scheduler
#
################################################################################

DSP_SCHEDULER_SITE = $(BR2_EXTERNAL_K510_PATH)/package/dsp_scheduler/src
DSP_SCHEDULER_SITE_METHOD = local
DSP_SCHEDULER_INSTALL_STAGING = YES

FIRMWARE_BUILD_OPS= ARCH=riscv  PATH=$(BR2_EXTERNAL_K510_PATH)/toolchain/nds64le-elf-mculib-v5d/bin:${PATH} \
		BR2_TARGET_EVB_FIRMWARE_LOAD_ADD=$(BR2_TARGET_EVB_FIRMWARE_LOAD_ADD)

DSP_SCHEDULER_DEPENDENCIES += audio3a_lib
DSP_SCHEDULER_DEPENDENCIES += k510_evb_test

define DSP_SCHEDULER_BUILD_CMDS
	BR2_PACKAGE_DSP_SCHEDULER_AUDIO3A_TASK=$(BR2_PACKAGE_DSP_SCHEDULER_AUDIO3A_TASK) $(TARGET_MAKE_ENV) $(FIRMWARE_BUILD_OPS) $(MAKE) -C $(@D)
endef

define DSP_SCHEDULER_INSTALL_STAGING_CMDS
	cp -rf $(@D)/dsp_tasks.h $(STAGING_DIR)/usr/include/dsp_tasks.h
endef

define DSP_SCHEDULER_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/scheduler.bin $(TARGET_DIR)/app/dsp_scheduler/scheduler.bin
endef

$(eval $(generic-package))
