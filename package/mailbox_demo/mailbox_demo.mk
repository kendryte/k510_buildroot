  ################################################################################
  #
  # mailbox_demo
  #
  ################################################################################

MAILBOX_DEMO_SITE = $(BR2_EXTERNAL_K510_PATH)/package/mailbox_demo/src
MAILBOX_DEMO_SITE_METHOD = local
 
MAILBOX_DEMO_DEPENDENCIES += dsp_scheduler
 
define MAILBOX_DEMO_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef
 
define MAILBOX_DEMO_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/mailbox_async $(TARGET_DIR)/app/mailbox_demo/mailbox_async
    $(INSTALL) -D -m 0755 $(@D)/mailbox_poll $(TARGET_DIR)/app/mailbox_demo/mailbox_poll
    $(INSTALL) -D -m 0755 $(@D)/cpu2dsp_task_demo $(TARGET_DIR)/app/mailbox_demo/cpu2dsp_task_demo
endef
 
$(eval $(generic-package))
