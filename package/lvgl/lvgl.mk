################################################################################
#
# lvgl
#
################################################################################
LVGL_VERSION = v8.2.0
LVGL_SOURCE = $(LVGL_VERSION).tar.gz
LVGL_SITE = https://github.com/lvgl/lvgl/archive/refs/tags

LVGL_DEPENDENCIES += libdisp libdrm
LVGL_CFLAGS = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include/libdrm -I$(STAGING_DIR)/usr/include
LVGL_LDFLAGS = -L$(STAGING_DIR)/lib64/lp64d -ldisp -L$(STAGING_DIR)/usr/lib -ldrm

define LVGL_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) CFLAG="$(LVGL_CFLAGS)" LDFLAG="$(LVGL_LDFLAGS)" all
endef

define LVGL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/lvgl $(TARGET_DIR)/app/lvgl/lvgl
endef

$(eval $(generic-package))