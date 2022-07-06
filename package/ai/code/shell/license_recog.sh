#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./license_plate_recog ../kmodel/kmodel_release/license_detect/mb_rf320/LPD_320_bf16_swapRB_with_preprocess.kmodel   320 320 320 0.3 0.2 ../kmodel/kmodel_release/license_recorg/lprnet/LPR_bf16_swapRB_out_nhwc_with_preprocess.kmodel   24 94 18 76 ./video_object_detect_320x320.conf   1 0 None