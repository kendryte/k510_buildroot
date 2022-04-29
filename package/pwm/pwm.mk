################################################################################
#
# pwm
#
################################################################################
PWM_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
PWM_SITE = $(PWM_LOCAL_PATH)/src
PWM_SITE_METHOD = local


define PWM_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define PWM_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/pwm.out $(TARGET_DIR)/app/pwm/pwm
endef

$(eval $(generic-package))
