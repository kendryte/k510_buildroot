#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./self_learning 480 640 ../kmodel/kmodel_release/self_learning/learning/mb-1.0_bf16_swapRB_with_preprocess_input_nchw.kmodel 224 1024 100 90 ./video_object_detect_480x640.conf  1 0 None