################################################################################
#
# client
#
################################################################################
CLIENT_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
CLIENT_SITE = $(CLIENT_LOCAL_PATH)/src
CLIENT_SITE_METHOD = local


define CLIENT_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define CLIENT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/client.out $(TARGET_DIR)/app/client/client
endef

$(eval $(generic-package))
