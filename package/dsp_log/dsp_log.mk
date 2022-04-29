  ################################################################################
  #
  # dsp_log
  #
  ################################################################################

 DSP_LOG_SITE = $(BR2_EXTERNAL_K510_PATH)/package/dsp_log/src
 DSP_LOG_SITE_METHOD = local
 
 
 define DSP_LOG_BUILD_CMDS
     $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
 endef
 
 define DSP_LOG_INSTALL_TARGET_CMDS
     $(INSTALL) -D -m 0755 $(@D)/dsp_log $(TARGET_DIR)/app/dsp_log/dsp_log
 endef
 
 $(eval $(generic-package))

