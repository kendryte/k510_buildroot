#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./person_detect ../kmodel/kmodel_release/person_detect/scrfd/scrfd_person_2.5g_fixed_input_size_simplify_bf16_with_preprocess.kmodel 640 480 640 480 0.3 0.2 ./video_object_detect_640x480.conf 1 0 None