################################################################################
#
# ffmpeg
#
################################################################################

FFMPEG_CANAAN_VERSION = 4.4
FFMPEG_CANAAN_SOURCE = ffmpeg-$(FFMPEG_CANAAN_VERSION).tar.xz
FFMPEG_CANAAN_SITE = http://ffmpeg.org/releases
FFMPEG_CANAAN_INSTALL_STAGING = YES

FFMPEG_CANAAN_LICENSE = LGPL-2.1+, libjpeg license
FFMPEG_CANAAN_LICENSE_FILES = LICENSE.md COPYING.LGPLv2.1
ifeq ($(BR2_PACKAGE_FFMPEG_CANAAN_GPL),y)
FFMPEG_CANAAN_LICENSE += and GPL-2.0+
FFMPEG_CANAAN_LICENSE_FILES += COPYING.GPLv2
endif

FFMPEG_CANAAN_DEPENDENCIES += host-pkgconf
FFMPEG_CANAAN_DEPENDENCIES += video_lib
FFMPEG_CANAAN_DEPENDENCIES += venc_lib
FFMPEG_CANAAN_DEPENDENCIES += alsa-lib
FFMPEG_CANAAN_DEPENDENCIES += audio3a_lib
FFMPEG_CANAAN_DEPENDENCIES += mediactl_lib
FFMPEG_CANAAN_DEPENDENCIES += dsp_scheduler
FFMPEG_CANAAN_DEPENDENCIES += libzlib
FFMPEG_CANAAN_DEPENDENCIES += libopenssl
FFMPEG_CANAAN_DEPENDENCIES += librtmp


FFMPEG_CANAAN_CONF_ENV += CFLAGS="$(FFMPEG_CANAAN_CFLAGS)"
FFMPEG_CANAAN_CONF_OPTS += $(call qstrip,$(BR2_PACKAGE_FFMPEG_CANAAN_EXTRACONF))

# Override FFMPEG_CANAAN_CONFIGURE_CMDS: FFmpeg does not support --target and others
define FFMPEG_CANAAN_CONFIGURE_CMDS
	(cd $(FFMPEG_CANAAN_SRCDIR) && rm -rf config.cache && \
	$(TARGET_CONFIGURE_OPTS) \
	$(TARGET_CONFIGURE_ARGS) \
	$(FFMPEG_CANAAN_CONF_ENV) \
	./configure \
		--cross-prefix=riscv64-linux- \
		--enable-cross-compile \
		--target-os=linux \
		--cc=riscv64-linux-gcc \
		--arch=riscv64 \
		--extra-ldflags="-L./" \
		--extra-ldflags="-ldl" \
		--extra-ldflags="-Wl,-rpath ." \
		--enable-static \
		--enable-shared \
		--enable-pic \
		--extra-ldflags="-Wl,-Bsymbolic" \
		--enable-libk510_video \
		--enable-libk510_h264 \
		--enable-libk510_jpeg \
		--enable-alsa \
		--disable-autodetect \
		--disable-ffplay \
		--disable-ffprobe \
		--disable-doc \
		--enable-audio3a \
		--enable-indev=v4l2 \
		--enable-librtmp \
	)
endef

define FFMPEG_CANAAN_REMOVE_EXAMPLE_SRC_FILES
	rm -rf $(TARGET_DIR)/usr/share/ffmpeg/examples
	rm -rf $(TARGET_DIR)/usr/local/lib/libswscale.a
	rm -rf $(TARGET_DIR)/usr/local/lib/libavdevice.a
	rm -rf $(TARGET_DIR)/usr/local/lib/libavfilter.a
	rm -rf $(TARGET_DIR)/usr/local/lib/libavutil.a
	rm -rf $(TARGET_DIR)/usr/local/lib/libswresample.a
	rm -rf $(TARGET_DIR)/usr/local/lib/libavcodec.a
	rm -rf $(TARGET_DIR)/usr/local/lib/libavformat.a
endef
FFMPEG_CANAAN_POST_INSTALL_TARGET_HOOKS += FFMPEG_CANAAN_REMOVE_EXAMPLE_SRC_FILES

$(eval $(autotools-package))
