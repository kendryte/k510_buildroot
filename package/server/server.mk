################################################################################
#
# server
#
################################################################################
SERVER_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
SERVER_SITE = $(SERVER_LOCAL_PATH)/src
SERVER_SITE_METHOD = local


define SERVER_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define SERVER_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/server.out $(TARGET_DIR)/app/server/server
endef

$(eval $(generic-package))
