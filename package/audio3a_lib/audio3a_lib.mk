################################################################################
#
# audio3a lib
#
################################################################################

AUDIO3A_LIB_SITE = $(BR2_EXTERNAL_K510_PATH)/package/audio3a_lib/src
AUDIO3A_LIB_SITE_METHOD = local
AUDIO3A_LIB_INSTALL_STAGING = YES

FIRMWARE_BUILD_OPS= ARCH=riscv  PATH=$(BR2_EXTERNAL_K510_PATH)/toolchain/nds64le-elf-mculib-v5d/bin:${PATH} \
		BR2_TARGET_EVB_FIRMWARE_LOAD_ADD=$(BR2_TARGET_EVB_FIRMWARE_LOAD_ADD)

define AUDIO3A_LIB_BUILD_CMDS
	$(TARGET_MAKE_ENV) AUDIO3A_LIB_PATH=$(@D) $(MAKE) -C $(@D) TARGET=libaudio3a.so
	$(TARGET_MAKE_ENV) AUDIO3A_LIB_PATH=$(@D) $(FIRMWARE_BUILD_OPS) $(MAKE) -C $(@D) TARGET=libaudio3a.a
endef

define AUDIO3A_LIB_INSTALL_STAGING_CMDS
	cp -rf $(@D)/libaudio3a.so $(STAGING_DIR)/lib64/lp64d/libaudio3a.so
	cp -rf $(@D)/libaudio3a.a $(STAGING_DIR)/lib64/lp64d/libaudio3a.a
	rm -rf $(STAGING_DIR)/usr/include/audio3a
	mkdir $(STAGING_DIR)/usr/include/audio3a
	cp -rf $(@D)/include/* $(STAGING_DIR)/usr/include/audio3a
	# cp -rf $(@D)/include/audio3a.h $(STAGING_DIR)/usr/include/audio3a
endef

define AUDIO3A_LIB_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libaudio3a.so $(TARGET_DIR)/lib64/lp64d/libaudio3a.so
endef

$(eval $(generic-package))
