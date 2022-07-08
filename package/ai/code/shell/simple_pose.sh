#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./simple_pose ../kmodel/kmodel_release/object_detect/yolov5s_320/yolov5s_320_sigmoid_bf16_with_preprocess_output_nhwc.kmodel 320 240 320 0.5 0.45 ../kmodel/kmodel_release/person_pose/simplepose/deploy_modify_bf16_with_preprocess.kmodel 256 192 0.2 ./video_object_detect_320.conf 1 0 None