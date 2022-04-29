################################################################################
#
# tinymembench
#
################################################################################

RISCV_TINYMEMBENCH_VERSION = a2cf6d7e382e3aea1eb39173174d9fa28cad15f3
RISCV_TINYMEMBENCH_SITE = https://github.com/ssvb/tinymembench.git
RISCV_TINYMEMBENCH_SITE_METHOD = git
RISCV_TINYMEMBENCH_LICENSE = MIT
RISCV_TINYMEMBENCH_LICENSE_FILES = LICENSE

define RISCV_TINYMEMBENCH_BUILD_CMDS
	$(TARGET_CONFIGURE_OPTS) $(MAKE) -C $(@D)
endef

define RISCV_TINYMEMBENCH_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 -D $(@D)/tinymembench \
		$(TARGET_DIR)/usr/bin/tinymembench
endef

$(eval $(generic-package))
