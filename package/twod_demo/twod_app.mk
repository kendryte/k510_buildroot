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
    $(INSTALL) -D -m 0755 $(@D)/twod-scaler-overlay-osd-app $(TARGET_DIR)/app/twod_app/twod-scaler-overlay-osd-app
    $(INSTALL) -D -m 0755 $(@D)/twod-osd2yuv-app $(TARGET_DIR)/app/twod_app/twod-osd2yuv-app
    $(INSTALL) -D -m 0755 $(@D)/twod-scaler-output-rgb888-app $(TARGET_DIR)/app/twod_app/twod-scaler-output-rgb888-app
    $(INSTALL) -D -m 0755 $(@D)/canaan_logo_320x240.argb $(TARGET_DIR)/app/twod_app/canaan_logo_320x240.argb
endef
 
$(eval $(generic-package))
