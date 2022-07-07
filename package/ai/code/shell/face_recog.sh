#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./face_recog ../kmodel/kmodel_release/face_detect/mb_rf320/retinaface_mobile0.25_320_bf16_swapRB_with_preprocess.kmodel 320 240 320 0.95 0.2 ../kmodel/kmodel_release/face_recog/mbfacenet/model-y1_bf16_with_preprocess.kmodel  112 128 100 78 ./video_object_detect_320.conf  1 0 None