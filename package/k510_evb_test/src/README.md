## 使用方法

1、set env:

`
export ARCH=riscv
export CROSS_COMPILE=riscv64-linux-
export PATH=/opt/Andestech/AndeSight_STD_v323/toolchains/nds64le-elf-mculib-v5d/bin:$PATH
`

2、`make
`
make TARGET=test/hello_world
`
> `make TARGET=test/hello_world MODE=evblp3`

## make 参数

TARGET: test case的目录

EXDIR: 设备驱动或其它需要编译的目录

MODE:

    evblp4: EVBLP4 板子（默认），自动添加宏定义 _EVBLP4
    evblp3：EVBLP3板子，自动添加宏定义 _EVBLP3
    simu：用于仿真，自动添加宏定义 _SIMU
    fpga：FPGA板子，自动添加宏定义 _FPGA

CROSS_COMPILE：指定交叉编译工具，默认为riscv64-unknown-elf-，所以需要设置PATH指定toolchain

    CROSS_COMPILE=/opt/riscv64-unknown-elf/bin/riscv64-unknown-elf-
    或者
    export PATH=/opt/riscv64-unknown-elf/bin:$PATH

DEBUG：默认为1，使用-O0 -g3，如果需要优化则 DEBUG=0

DDR: DDR=1 使用lds/k510_ddr.ld 链接脚本，把程序链接到DDR空间。默认使用lds/K510.ld，程序链接到SRAM0空间。

LDTAR:

    ddr: 使用lds/k510_ddr.ld 链接脚本，把程序链接到DDR空间。与DDR=1相同。
    sram1:使用lds/k510_sram1.ld 链接脚本，把程序链接到SRAM1(0x80100000-0x80180000)空间。
    poweron: 使用lds/k510_wakeup.ld 链接脚本，把程序链接到常上电(0x80000000-0x80020000)空间。
    默认使用lds/K510.ld，程序链接到SRAM0空间。

LDSCRIPT: 指定链接脚本

SIM_DDR: 仿真时DDR初始化的开关，如果使用真实DDR则 SIM_DDR=1, 默认使用DDR VIP。

--

make的参数都可以通过设置环境变量来固定。比如

make MODE=fpga

先设置环境变量 export MODE=fpga

以后直接make就可以，相当于 make MODE=fpga

## 例子

make TARGET=test/hello_world MODE=evblp3 EXDIR=“test/device_driver/emac_phy” LDTAR=ddr

TARGET=test/hello_world：要编译的目标是test/hello_world，即编译生成hello_world.elf文件

MODE=evblp3：使用的EVBLP3板子。

EXDIR=“test/device_driver/emac_phy”：除编译目标目录和BSP目录的文件外，还要编译test/device_driver/emac_phy目录里的文件。多个目录的话中间用空格隔开。

LDTAR=ddr：链接到DDR空间。

## 参考
https://doc.b-bug.org/pages/viewpage.action?pageId=39420030
