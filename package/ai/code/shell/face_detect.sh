#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./face_detect ../kmodel/kmodel_release/face_detect/mb_rf320/retinaface_mobile0.25_320_bf16_swapRB_with_preprocess.kmodel 320 240 320 0.5 0.2 video_object_detect_320.conf 1 0 None
# cd ../exe && ./face_detect ../kmodel/kmodel_release/face_detect/mb_rf640/retinaface_mobile0.25_640_bf16_swapRB_with_preprocess.kmodel 640 480 640 0.5 0.2 video_object_detect_640.conf 1 0 None