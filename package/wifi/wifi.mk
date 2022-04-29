################################################################################
#
# wifi_test
#
################################################################################
WIFI_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
WIFI_SITE = $(WIFI_LOCAL_PATH)/src
WIFI_SITE_METHOD = local


define WIFI_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define WIFI_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/wifi $(TARGET_DIR)/app/wifi/wifi
endef

$(eval $(generic-package))
