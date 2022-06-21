################################################################################
#
# aws_iot_test
#
################################################################################
AWS_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
AWS_IOT_TEST_SITE = $(AWS_LOCAL_PATH)/subscribe_publish_sample
AWS_IOT_TEST_SITE_METHOD = local
FILE=$(AWS_LOCAL_PATH)/subscribe_publish_sample


define AWS_IOT_TEST_COMPILE_MODEL
	cp $(FILE)/certs $(TARGET_DIR)/app/aws_iot_test/certs -R
 	cp $(FILE)/external_libs $(TARGET_DIR)/app/aws_iot_test/external_libs -R
 	cp $(FILE)/platform $(TARGET_DIR)/app/aws_iot_test/platform -R
	cp $(FILE)/src $(TARGET_DIR)/app/aws_iot_test/src -R
endef



define AWS_IOT_TEST_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/aws_iot_test $(TARGET_DIR)/app/aws_iot_test/aws_iot_test
	$(INSTALL) -D -m 0755 $(@D)/checkprocess.sh $(TARGET_DIR)/app/aws_iot_test/checkprocess.sh
endef

AWS_IOT_TEST_POST_INSTALL_TARGET_HOOKS += AWS_IOT_TEST_COMPILE_MODEL

define AWS_IOT_TEST_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

$(eval $(generic-package))
