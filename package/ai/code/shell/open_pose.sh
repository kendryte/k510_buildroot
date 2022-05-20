#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./openpose ../kmodel/kmodel_release/person_pose/openpose/hp_concat_new_bf16_swapRB_with_preprocess_input_nchw.kmodel 432 368 432 368 ./video_object_detect_432x368.conf 1 0 None