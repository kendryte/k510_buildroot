################################################################################
#
# isp-tuningd
#
################################################################################
ISP_TUNINGD_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
ISP_TUNINGD_DIR_NAME := isp-tuningd
ISP_TUNINGD_APP_NAME := isp-tuningd

ISP_TUNINGD_SITE = $(ISP_TUNINGD_LOCAL_PATH)/src
ISP_TUNINGD_SITE_METHOD = local


define ISP_TUNINGD_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define ISP_TUNINGD_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/$(ISP_TUNINGD_DIR_NAME) $(TARGET_DIR)/app/mediactl_lib/$(ISP_TUNINGD_APP_NAME)
endef

$(eval $(generic-package))
