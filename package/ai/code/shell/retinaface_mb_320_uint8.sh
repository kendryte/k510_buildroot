#!/bin/sh

devmem 0x970E00fc 32 0x0fffff00
devmem 0x970E0100 32 0x000000ff
devmem 0x970E00f4 32 0x00550000

cd ../exe && ./retinaface_mb_320 ../kmodel/kmodel_compile/retinaface_mb_320/rf_uint8.kmodel 0

