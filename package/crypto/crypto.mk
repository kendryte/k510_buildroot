################################################################################
#
# crypto
#
################################################################################
CRYPTO_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
CRYPTO_SITE = $(CRYPTO_LOCAL_PATH)/src
CRYPTO_SITE_METHOD = local


define CRYPTO_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define CRYPTO_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/crypto.out $(TARGET_DIR)/app/crypto/crypto
endef

$(eval $(generic-package))
