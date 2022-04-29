  ################################################################################
  #
  # twod app
  #
  ################################################################################

TWOD_DEMO_SITE = $(BR2_EXTERNAL_K510_PATH)/package/twod_demo/src
TWOD_DEMO_SITE_METHOD = local
 
#TWOD_DEMO_DEPENDENCIES += twod
 
define TWOD_DEMO_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) -C $(@D) all 
endef
 
define TWOD_DEMO_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/twod-rotation-app $(TARGET_DIR)/app/twod_app/twod-rotation-app
    $(INSTALL) -D -m 0755 $(@D)/twod-scaler-app $(TARGET_DIR)/app/twod_app/twod-scaler-app

endef
 
$(eval $(generic-package))
