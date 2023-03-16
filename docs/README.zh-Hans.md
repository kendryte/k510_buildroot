[![Gitee repository](https://img.shields.io/badge/gitee-repository-blue?logo=gitee&style=plastic)](https://gitee.com/kendryte/k510_buildroot)
[![GitHub release](https://img.shields.io/github/v/release/kendryte/k510_buildroot?color=brightgreen&display_name=tag&logo=github&style=plastic)](https://github.com/kendryte/k510_buildroot/releases)

* [English](../README.md)
* [简体中文](README.zh-Hans.md)
  
# K510 SDK

勘智K510是嘉楠公司推出的第二代AI边缘侧推理芯片，它为AI应用提供了高性能的图像及语音处理能力。K510搭载自主研发的第二代神经网络处理器KPU2.0， 采用独创计算数据流技术，算力较上一代提升3倍同时降低功耗。集成最新一代图像处理器ISP，支持TOF深度相机接入，支持2D/3D降噪、宽动态范围（WDR）、硬件3A等完备功能。3D ISP支持深度摄像头TOF sensor。可广泛应用于无人机、高清航拍、专业相机、视频会议、智能机器人、教育STEAM、自动辅助驾驶等不同应用领域。

K510 SDK是嘉楠公司提供的用于K510芯片应用研发的软件开发资料包，它的默认配置基于K510 CRB(客户参考平台)，仓库内容包括用户在使用 K510 芯片进行开发中可能用到的工具链软件、PC工具包、Linux代码、bootloader、bbl、buildroot构建系统软件及相关的硬件资源文档。用户可以基于本套软件代码库，根据自己的需求进行定制更改开发，最终构建并编译生成部署使用的镜像文件。

## 资料内容说明和参考资源链接

| No | 链接地址 | 说明  |
| :----: | ---- |  ------------------------------------------------------------ |
|1| / | 代码编译工作目录 |
|2|[docs/](https://github.com/kendryte/k510_docs)| K510系统编译及应用开发文档；硬件资源介绍文档
|3|[package/](/package/)| 提供Linux系统外设开发应用示例；各种AI 演示应用源代码  |
|4|[嘉楠勘智](https://canaan-creative.com/product/勘智k510)|嘉楠勘智官网|
|5|[开发者社区](https://canaan-creative.com/developer)|嘉楠勘智论坛
|6|[演示视频](https://space.bilibili.com/677429436)|K510开发板开箱视频及多个 AI 应用展示视频|
|7|[K510 CRB-KIT](https://item.taobao.com/item.htm?spm=a230r.1.14.1.22714815bDh5ei&id=673510674381&ns=1&abbucket=0&mt=)|K510 开发板套装在线购买链接|
|8|即时沟通|  社区互助 QQ 群：790699378</br>Telegram：nncase community |

## K510 CRB 开发者套装介绍

K510 CRB-KIT是基于K510芯片研发的开发者套装，它采用分级设计，以K510核心模组为基础，外设丰富，便于扩展。 支持USB 2.0 OTG+PHY、千兆以太网口、3xSDIO、3xSPI等高速通信接口，支持4xUART、GPIO、I2C和I2S等低速通信接口。使用简单、资料丰富、能够帮助客户快速实现创意评估、产品原型验证，缩短产品设计周期。
![canaan-board.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/canaan-board.png)
<center>K510 CRB 正面照 </center>

![image-hw_1_3.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_1_3.png)
<center>K510系统框图</center>  

![image-hw_3_1.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/hw_crb_v1_2/image-hw_3_1.png)
<center>K510核心板模组图</center>  

## K510 软件开发入门

### 建立软件开发环境

K510 软件开发基于 Linux 环境。用户需要准备一台装有 Linux 操作系统的主机用于软件编译及部署，如果您工作在 windows 下，推荐安装 Windows WSL 以便进行软件开发工作。

### 源代码下载

```sh
git clone https://github.com/kendryte/k510_buildroot.git
```

### 启动docker

* 用户模式(不需要root权限)

   ```sh
   sh k510_buildroot/tools/docker/run_k510_docker_user.sh
   ```

   _**注意:**_ 该模式需要Docker守护程序以rootless模式运行，以下为简化步骤(只需执行一次，详细过程请参考[docker rootless](https://docs.docker.com/engine/security/rootless/#install)):

   ```sh
   dockerd-rootless-setuptool.sh install
   ```

   如果`dockerd-rootless-setuptool.sh`命令不存在，需要联系管理员安装软件包`docker-ce-rootless-extras`:

   ```sh
   sudo apt-get install docker-ce-rootless-extras
   ```

* root模式(需要root权限)

   ```sh
   sh k510_buildroot/tools/docker/run_k510_docker.sh
   ```

### 编译代码库

进入docker环境后，输入如下命令进行系统编译。

```sh
make dl
make
```

`make dl`为可选步骤，用于加速源码下载。
第一次全新系统编译时间较长，请耐心等待（时间和主机CPU的性能和网络下载速度相关）。

### 烧写镜像文件

K510 支持sdcard和eMMC启动方式，用户可以通过改变开板上SW1拔码开关的设置切换不同启动模式。  
出厂默认为从emmc启动。为方便开发，建议您准备一张TF卡，并将拔码开关切换至SD卡启动模式，后续可考虑将镜像文件固化至emmc中。  
无论您工作在 Linux 还是 Windows系统下， 均可下载 [Etcher](https://www.balena.io/etcher/) 工具，将编译生成的镜像文件（k510_buildroot/k510_crb_lp3_v1_2_defconfig/image/sysimage-sdcard.img）烧录至 TF 卡中。
![balenaetcher.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/balenaetcher.png)

### 上电运行

确认SW1开关选择在SD卡启动模式下，将烧录完成的TF卡插入进开板板卡槽中，然后将电源开关K1拔到ON位置，系统可上电。您会看到屏幕显示 CANAAN logo 画面，如果您有接好串口，可在串口中看到启动日志输出。
![k510_boot.png](https://github.com/kendryte/k510_docs/raw/v1.5/zh/images/quick_start/k510_boot.png)

### 更改默认启动程序

默认情况下，系统开机会自动运行 /app/mediactl_lib 路径下的示例程序(v4l2_drm.out)。你也可以手动更改配置程序，改成运行其它演示程序。更改方法如下：

```sh
vi /etc/init.d/rc.sysinit
修改以下位置
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
改为你想运行的 APP，例如改成人脸检测演示应用，可以改成：
/app/ai/shell/face_detect.sh &
```

## 贡献指南

如果您对本项目感兴趣，想要反馈问题或提交代码，请参考[CONTRIBUTING](.github/CONTRIBUTING.md)

## 联系我们

北京嘉楠捷思信息技术有限公司  
网址：[canaan-creative.com](https://canaan-creative.com)  
商务垂询：[salesAI@canaan-creative.com](mailto:salesAI@canaan-creative.com)
