################################################################################
#
# opencv4
#
################################################################################

OPENCV4_VERSION = 4.5.2
OPENCV4_SITE = $(call github,opencv,opencv,$(OPENCV4_VERSION))
OPENCV4_INSTALL_STAGING = YES
OPENCV4_LICENSE = BSD-3-Clause
OPENCV4_LICENSE_FILES = LICENSE
OPENCV4_SUPPORTS_IN_SOURCE_BUILD = NO

OPENCV4_CONTRIB_SITE = https://github.com/opencv/opencv_contrib/archive/refs/tags
OPENCV4_CONTRIB_SOURCE = $(OPENCV4_VERSION).tar.gz
OPENCV4_EXTRA_DOWNLOADS = $(OPENCV4_CONTRIB_SITE)/$(OPENCV4_CONTRIB_SOURCE)

define OPENCV4_CONTRIB_EXTRACT
        $(call suitable-extractor,$(OPENCV4_CONTRIB_SOURCE)) $(OPENCV4_DL_DIR)/$(OPENCV4_CONTRIB_SOURCE) | \
        $(TAR) --strip-components=1 -C $(@D) $(TAR_OPTIONS) -
endef
OPENCV4_POST_EXTRACT_HOOKS += OPENCV4_CONTRIB_EXTRACT


OPENCV4_CXXFLAGS = $(TARGET_CXXFLAGS)
OPENCV4_CFLAGS = $(TARGET_CFLAGS)

# Uses __atomic_fetch_add_4
ifeq ($(BR2_TOOLCHAIN_HAS_LIBATOMIC),y)
OPENCV4_CXXFLAGS += -latomic
endif

# Fix c++11 build with missing std::exception_ptr
ifeq ($(BR2_TOOLCHAIN_HAS_GCC_BUG_64735),y)
OPENCV4_CXXFLAGS += -DCV__EXCEPTION_PTR=0
endif

ifeq ($(BR2_TOOLCHAIN_HAS_GCC_BUG_68485),y)
OPENCV4_CXXFLAGS += -O0
endif

OPENCV4_CXXFLAGS += -march=rv64imafdc
OPENCV4_CFLAGS += -march=rv64imafdc

# OpenCV component options
OPENCV4_CONF_OPTS += \
	-DCMAKE_CXX_FLAGS="$(OPENCV4_CXXFLAGS) -O3" \
	-DCMAKE_C_FLAGS="$(OPENCV4_CFLAGS) -O3" \
	-DBUILD_opencv_python3=ON

OPENCV4_CONF_ENV += PKG_CONFIG_PATH=$(TARGET_DIR)/usr/local/lib/pkgconfig

OPENCV4_DEPENDENCIES += host-pkgconf zlib ffmpeg_canaan

# Installation hooks:
define OPENCV4_CLEAN_INSTALL_LICENSE
	$(RM) -fr $(TARGET_DIR)/usr/share/licenses/opencv3
endef
OPENCV4_POST_INSTALL_TARGET_HOOKS += OPENCV4_CLEAN_INSTALL_LICENSE

define OPENCV4_CLEAN_INSTALL_CMAKE
	$(RM) -f $(TARGET_DIR)/usr/share/OpenCV/OpenCV*.cmake
endef
OPENCV4_POST_INSTALL_TARGET_HOOKS += OPENCV4_CLEAN_INSTALL_CMAKE

define OPENCV4_CLEAN_INSTALL_VALGRIND
	$(RM) -f $(TARGET_DIR)/usr/share/OpenCV/valgrind*
endef
OPENCV4_POST_INSTALL_TARGET_HOOKS += OPENCV4_CLEAN_INSTALL_VALGRIND

ifneq ($(BR2_PACKAGE_OPENCV4_INSTALL_DATA),y)
define OPENCV4_CLEAN_INSTALL_DATA
	$(RM) -fr $(TARGET_DIR)/usr/share/OpenCV/haarcascades \
		$(TARGET_DIR)/usr/share/OpenCV/lbpcascades
endef
OPENCV4_POST_INSTALL_TARGET_HOOKS += OPENCV4_CLEAN_INSTALL_DATA
endif

$(eval $(cmake-package))
