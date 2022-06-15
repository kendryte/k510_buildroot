################################################################################
#
# live555
#
################################################################################

LIVE555_CANAAN_VERSION = 2022.01.17
LIVE555_CANAAN_SOURCE = live.$(LIVE555_CANAAN_VERSION).tar.gz
LIVE555_CANAAN_SITE = http://download.videolan.org/pub/contrib/live555
# There is a COPYING file with the GPL-3.0 license text, but none of
# the source files appear to be released under GPL-3.0, and the
# project web site says it's licensed under the LGPL:
# http://live555.com/liveMedia/faq.html#copyright-and-license
LIVE555_CANAAN_LICENSE = LGPL-3.0+
LIVE555_CANAAN_LICENSE_FILES = COPYING.LESSER
LIVE555_CANAAN_INSTALL_STAGING = YES

LIVE555_CANAAN_CFLAGS = $(TARGET_CFLAGS)

ifeq ($(BR2_STATIC_LIBS),y)
LIVE555_CANAAN_CONFIG_TARGET = linux
LIVE555_CANAAN_LIBRARY_LINK = $(TARGET_AR) cr
else
LIVE555_CANAAN_CONFIG_TARGET = linux-with-shared-libraries
LIVE555_CANAAN_LIBRARY_LINK = $(TARGET_CC) -o
LIVE555_CANAAN_CFLAGS += -fPIC
endif

ifndef ($(BR2_ENABLE_LOCALE),y)
LIVE555_CANAAN_CFLAGS += -DLOCALE_NOT_USED
endif

define GENERATE_MAKEFILE
	cp $(LIVE555_CANAAN_PKGDIR)src/config.riscv64 $(LIVE555_CANAAN_SRCDIR)
	(cd $(@D) && \
	./genMakefiles riscv64 \
	)
endef

LIVE555_CANAAN_POST_EXTRACT_HOOKS += GENERATE_MAKEFILE

define LIVE555_CANAAN_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) all
endef

define LIVE555_CANAAN_INSTALL_STAGING_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) DESTDIR=$(STAGING_DIR) -C $(@D) install
endef


define LIVE555_CANAAN_INSTALL_STAGING_CMDS
	cp -rf $(@D)/liblive555.a  $(STAGING_DIR)/lib64/lp64d/liblive555.a
	cp -rf $(@D)/testProgs/VideoStreamer.hh  $(STAGING_DIR)/usr/include
	cp -rf $(@D)/testProgs/IRtspServer.h  $(STAGING_DIR)/usr/include
endef

$(eval $(generic-package))
