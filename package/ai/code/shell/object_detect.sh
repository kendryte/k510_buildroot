#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./object_detect ../kmodel/kmodel_release/object_detect/yolov5s_320/yolov5s_320_sigmoid_bf16_with_preprocess_output_nhwc.kmodel 320 240 320 0.5 0.45 ./video_object_detect_320.conf  1 0 None
# cd ../exe && ./object_detect ../kmodel/kmodel_release/object_detect/yolov5s_640/yolov5s_640_sigmoid_bf16_with_preprocess_output_nhwc.kmodel 640 480 640 0.5 0.45 ./video_object_detect_640.conf  1 0 None