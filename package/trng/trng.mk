################################################################################
#
# trng
#
################################################################################
TRNG_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
TRNG_SITE = $(TRNG_LOCAL_PATH)/src
TRNG_SITE_METHOD = local


define TRNG_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define TRNG_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/trng.out $(TARGET_DIR)/app/trng/trng
endef

$(eval $(generic-package))
