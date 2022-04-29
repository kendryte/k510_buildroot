################################################################################
#
# uart_test
#
################################################################################
UART_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
UART_SITE = $(UART_LOCAL_PATH)/src
UART_SITE_METHOD = local


define UART_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define UART_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/uart.out $(TARGET_DIR)/app/uart/uart
endef

$(eval $(generic-package))
