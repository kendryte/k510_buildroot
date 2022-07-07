#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./hand_image_classify ../kmodel/kmodel_release/hand_pose_x/detect/tinyYOLOV3_bf16_with_preprocess.kmodel  512 400 512 0.35 0.4 ../kmodel/kmodel_release/hand_pose_x/hand_landmark/squeezenet1_1_bf16_swapRB_with_preprocess.kmodel   256 21 ../kmodel/kmodel_release/hand_pose_x/classify/mbv2_bf16_swapRB_with_preprocess.kmodel   224 1000 ../kmodel/kmodel_release/hand_pose_x/classify/labels_1000.txt ./video_object_detect_512.conf  1 0 None