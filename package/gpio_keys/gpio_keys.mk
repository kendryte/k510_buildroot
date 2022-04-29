################################################################################
#
# gpio_keys_test
#
################################################################################
GPIO_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
GPIO_KEYS_SITE = $(GPIO_LOCAL_PATH)/src
GPIO_KEYS_SITE_METHOD = local

define GPIO_KEYS_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)
endef

define GPIO_KEYS_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/gpio_keys $(TARGET_DIR)/app/gpio_keys/gpio_keys
endef

$(eval $(generic-package))
