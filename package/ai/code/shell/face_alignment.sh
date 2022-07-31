#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./face_alignment   ../kmodel/kmodel_release/face_detect/mb_rf320/retinaface_mobile0.25_320_bf16_swapRB_with_preprocess.kmodel 320 240 320 0.95 0.2 ../kmodel/kmodel_release/face_landmarks/pfld_106/v3/v3_process_bf16_swapRB_with_preprocess.kmodel 112 106 0.00001 3 ../kmodel/kmodel_release/face_alignment/3ddfa_v2/mb1/mb1_120x120_bf16_swapRB_with_preprocess.kmodel   120 62 1 video_object_detect_320.conf 1 0 None
