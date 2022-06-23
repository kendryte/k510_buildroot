#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./object_detect_demo ../kmodel/kmodel_compile/object_detect_demo/od_uint8.kmodel 0
