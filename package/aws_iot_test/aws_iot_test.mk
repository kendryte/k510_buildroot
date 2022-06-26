################################################################################
#
# aws_iot_test
#
################################################################################
AWS_LOCAL_PATH:= $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
AWS_IOT_TEST_SITE = $(AWS_LOCAL_PATH)
AWS_IOT_TEST_SITE_METHOD = file

FILE=$(AWS_LOCAL_PATH)/subscribe_publish_sample

AWS_IOT_TEST_DATA_SITE = https://github.com/Mbed-TLS/mbedtls/archive/refs/tags/mbedtls-2.11.0.tar.gz
AWS_IOT_TEST_SOURCE = subscribe_publish_sample.tar

# MBEDTLS_DIR_S = $(AWS_LOCAL_PATH)/subscribe_publish_sample/external_libs/

AWS_IOT_TEST_EXTRA_DOWNLOADS = $(call qstrip,$(AWS_IOT_TEST_DATA_SITE))


AWS_IOT_TEST_PRE_DOWNLOAD_HOOKS = ai_iot_test_pre_download_hooks_tar_code
define ai_iot_test_pre_download_hooks_tar_code
	rm -rf $(AWS_LOCAL_PATH)/subscribe_publish_sample.tar;
	tar -cf $(AWS_LOCAL_PATH)/subscribe_publish_sample.tar -C$(AWS_LOCAL_PATH) subscribe_publish_sample
endef

AWS_IOT_TEST_POST_EXTRACT_HOOKS = AWS_IOT_TEST_POST_EXTRACT_HOOKS_DATA

define AWS_IOT_TEST_POST_EXTRACT_HOOKS_DATA
	rm -rf $(AWS_LOCAL_PATH)/subscribe_publish_sample.tar;
	tar -zvxf $(AWS_IOT_TEST_DL_DIR)/mbedtls-2.11.0.tar.gz -C $(AWS_IOT_TEST_DIR)/external_libs	
endef


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
