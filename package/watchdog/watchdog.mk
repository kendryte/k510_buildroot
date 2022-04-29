################################################################################
#
# watchdog
#
################################################################################
WATCHDOG_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
WATCHDOG_SITE = $(WATCHDOG_LOCAL_PATH)/src
WATCHDOG_SITE_METHOD = local


define WATCHDOG_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define WATCHDOG_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/watchdog.out $(TARGET_DIR)/app/watchdog/watchdog
endef

$(eval $(generic-package))
