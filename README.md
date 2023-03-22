[![Gitee repository](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
[![GitHub release](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

* [English](README.md)
* [简体中文](docs/README.zh-Hans.md)

# K510 SDK

Kendryte K510 is the second generation of AI edge-side inference chips launched by Canaan, which provides high-performance image and speech processing capabilities for AI applications. The K510 is equipped with the self-developed second-generation neural network processor KPU2.0, which adopts the original computing data flow technology, that increases the computing power by 3 times compared with the previous generation and reduces power consumption. Integrated with the latest generation of image processor ISP. It supports TOF depth camera access, 2D/3D noise reduction, wide dynamic range (WDR), hardware 3A, and other complete functions. The 3D ISPs support depth camera TOF sensors, and can be widely used in different application fields such as unmanned aerial vehicles, high-definition aerial photography, professional cameras, video conferencing, intelligent robots, educational STEAM, and automatic assisted driving.

K510 SDK is a software development kit provided by Canaan for K510 chip application development. Its default configuration is based on K510 CRB (customer reference platform). The warehouse content includes the toolchain software, PC toolkit, Linux code, bootloader, bbl, buildroot build system software, and related hardware resource documents that users may use in the development with K510 chip. Users can customize and change development according to their own needs based on this set of software code base, and finally build and compile the image file used for deployment.

## Descriptions of material content and links to reference resources

| No | Link address | illustrate  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | The code compiles the working directory |
|2|[docs/](https://github.com/kendryte/k510_docs)| K510 system compilation and application development documentation; Hardware resource introduction documentation
|3|[package/](/package/)| Provide Linux system peripheral development application examples; Various AI demo application source code  |
|4|[Canaan Kendryte](https://canaan-creative.com/product/勘智k510)|Canaan Kendryte official website|
|5|[Developer community](https://canaan-creative.com/developer)|Canaan Kendryte Forum
|6|[Demo video](https://space.bilibili.com/677429436)|K510 development board out-of-the-box video and multiple AI application demonstration videos|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 Board Kit Online Purchase Link|
|8|Instant communication|  Community Mutual Aid QQ Group: 790699378</br>Telegram: nncase community |

## Introduction to the K510 CRB Developer Suite

K510 CRB-KIT is a developer suite based on the K510 chip development, which adopts a hierarchical design, based on the K510 core module, with rich peripherals and easy to expand. It supports USB 2.0 OTG+PHY, Gigabit Ethernet port, 3xSDIO, 3xSPI and other high-speed communication interfaces. In addition, it supports 4xUART, GPIO, I2C and I2S and other low-speed communication interfaces. It is simple to use, informative and can help customers quickly achieve creative evaluation and product prototype verification. It shortens the product design cycle.
![Canaan-board .png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB front photo </center>

![image-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
 <center>K510 system block diagram</center>  

![image-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
 <center>K510 core board module diagram</center>  

## Getting started with K510 software development

### Set up a software development environment

K510 software development is based on a Linux environment. Users need to prepare a host with a Linux operating system for software compilation and deployment, and if you are working under Windows, it is recommended to install Windows WSL for software development work.

### Source code download

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### Start Docker

* user mode(not require root privileges)

   ```sh
   sh k510_buildroot/tools/docker/run_k510_docker_user.sh
   ```

   _**Note:**_ This mode requires the Docker daemon to run in rootless mode, the following are simplified steps (only need to execute it once, for the detailed process, please refer to [docker rootless](https://docs.docker.com/engine/security/rootless/#install)):

   ```sh
   dockerd-rootless-setuptool.sh install
   ```

   If `dockerd-rootless-setuptool.sh` is not present, you may need to install the `docker-ce-rootless-extras` package manually:

   ```sh
   sudo apt-get install docker-ce-rootless-extras
   ```

* root mode(require root privileges)

   ```sh
   sh k510_buildroot/tools/docker/run_k510_docker.sh
   ```

### Compile the code base

After entering the docker environment, enter the following command to compile the system.

```sh
make dl
make
```

`make dl`Optional step to speed up source code downloads.
The first new system takes a long time to compile, so be patient (time is related to the performance of the host CPU and the speed of network downloads).

### Flash the image file

The K510 supports sdcard and eMMC boot modes, and users can switch between different boot modes by changing the settings of the SW1 pull switch on the open board.  
The factory default is to boot from emmc. For ease of development, it is recommended that you prepare a TF card and switch the code switch to the SD card boot mode, and then consider curing the image file into emmc.  
Whether you work on Linux or Windows, you can download [the Etcher](https://www.balena.io/etcher/) tool to burn the compiled image file (k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img) to your TF card.
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### Power-on operation

Confirm that the SW1 switch is selected in SD card boot mode, insert the burned TF card into the open board card slot, and then unplug the power switch K1 to the ON position, and The system should power up.. You will see the screen display the CANAAN logo screen. If you have a connected serial port, you can see the boot log output in the serial port.
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### Change the default startup program

By default, the system automatically runs the sample program (v4l2_drm.out) under path /app/mediactl_lib. You can also manually change the configuration program to run other demo programs instead. Here's how to change it:

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## Contribution Guide

If you are interested in this project and would like feedback on a problem or submit code, please refer to [CONSOLIDATING](.github/CONTRIBUTING.md)

## Contact us

Canaan Inc.  
URL:[canaan-creative.com](https://canaan-creative.com)  
Business Enquiries:[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)

**Translation Disclaimer**  
For the convenience of customers, Canaan uses an AI translator to translate text into multiple languages, which may contain errors. We do not guarantee the accuracy, reliability or timeliness of the translations provided. Canaan shall not be liable for any loss or damage caused by reliance on the accuracy or reliability of the translated information. If there is a content difference between the translations in different languages, the Chinese Simplified version shall prevail.

If you would like to report a translation error or inaccuracy, please feel free to contact us by mail.
