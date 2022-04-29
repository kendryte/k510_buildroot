################################################################################
#
# drm_demo
#
################################################################################
DRM_DEMO_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
DRM_DEMO_SITE = $(DRM_DEMO_LOCAL_PATH)/src
DRM_DEMO_SITE_METHOD = local

DRM_DEMO_DEPENDENCIES += libdisp libdrm opencv4
DRM_DEMO_CFLAGS = $(TARGET_CFLAGS) -I$(STAGING_DIR)/usr/include/libdrm -I$(STAGING_DIR)/usr/include/opencv4 -I$(STAGING_DIR)/usr/include
DRM_DEMO_LDFLAGS = -L$(STAGING_DIR)/lib64/lp64d -ldisp -L$(STAGING_DIR)/usr/lib -ldrm -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

define DRM_DEMO_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) CFLAG="$(DRM_DEMO_CFLAGS)" LDFLAG="$(DRM_DEMO_LDFLAGS)" all
endef

define DRM_DEMO_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/drm_demo $(TARGET_DIR)/app/drm_demo/drm_demo
endef

$(eval $(generic-package))
