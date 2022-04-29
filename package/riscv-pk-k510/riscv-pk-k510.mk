################################################################################
#
# riscv-pk
#
################################################################################

RISCV_PK_K510_VERSION = 1e666d6c5dbab220d2ca57fbd9bec49702599b75
RISCV_PK_K510_SITE = https://github.com/kendryte/k510_BBL.git
RISCV_PK_K510_SITE_METHOD = git

RISCV_PK_K510_LICENSE = BSD-3-Clause
RISCV_PK_K510_LICENSE_FILES = LICENSE
RISCV_PK_K510_SUBDIR = build
RISCV_PK_K510_INSTALL_IMAGES = YES

define RISCV_PK_K510_CONFIGURE_CMDS
	mkdir -p $(@D)/build
	(cd $(@D)/build; \
		$(TARGET_CONFIGURE_OPTS) ../configure \
		--host=$(GNU_TARGET_NAME) \
		--with-payload=$(BINARIES_DIR)/vmlinux \
	)
endef

define RISCV_PK_K510_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/build bbl
endef

define RISCV_PK_K510_INSTALL_IMAGES_CMDS
	$(INSTALL) -D -m 0755 $(@D)/build/bbl $(BINARIES_DIR)/bbl.elf
	$(TARGET_OBJCOPY) -O binary $(@D)/build/bbl $(BINARIES_DIR)/bbl.bin
	$(BUILD_DIR)/uboot-$(BR2_TARGET_UBOOT_VERSION)/tools/mkimage -A riscv -O linux -T kernel -C none -a 0x0000 -e 0x0000 -d $(BINARIES_DIR)/bbl.bin $(BINARIES_DIR)/bootm-bbl.img
endef

$(eval $(generic-package))
