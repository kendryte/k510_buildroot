################################################################################
#
# write_read_file
#
################################################################################
WRITE_READ_FILE_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
WRITE_READ_FILE_SITE = $(WRITE_READ_FILE_LOCAL_PATH)/src
WRITE_READ_FILE_SITE_METHOD = local


define WRITE_READ_FILE_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define WRITE_READ_FILE_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/write_read_file.out $(TARGET_DIR)/app/write_read_file/write_read_file
endef

$(eval $(generic-package))
