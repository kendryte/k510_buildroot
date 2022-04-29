################################################################################
#
# alsa_demo
#
################################################################################

ALSA_DEMO_SITE = $(BR2_EXTERNAL_K510_PATH)/package/alsa_demo/src
ALSA_DEMO_SITE_METHOD = local
ALSA_DEMO_INSTALL_STAGING = YES

ALSA_DEMO_DEPENDENCIES += alsa-lib

define ALSA_DEMO_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define ALSA_DEMO_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/alsa_demo $(TARGET_DIR)/app/alsa_demo/alsa_demo
endef

$(eval $(generic-package))
