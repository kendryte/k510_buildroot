################################################################################
#
# rtc_demo
#
################################################################################

RTC_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
RTC_SITE = $(RTC_LOCAL_PATH)/src
RTC_SITE_METHOD = local


define RTC_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define RTC_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/rtc.out $(TARGET_DIR)/app/rtc/rtc
endef

$(eval $(generic-package))
