# K510 APP



## 一、详细描述

* [K510 SDK应用程序说明 ](https://github.com/kendryte/k510_docs/tree/v1.5/zh/K510_SDK_Application_Guides.md)



## 二、开机设置

任一个应用程序都可以设置为开机自动运行，有两种方式可实现，以单摄应用 test_scamer为例。



**方式一** ：修改 k510_buildroot

进入[k510_buildroot/board/canaan/k510/k510_rootfs_skeleton/etc/init.d](../board/canaan/k510/k510_rootfs_skeleton/etc/init.d) 文件夹，打开 [rc.sysinit](../board/canaan/k510/k510_rootfs_skeleton/etc/init.d/rc.sysinit) 文件，在文件的末尾加上如下内容使单摄应用后台运行。

``` sh
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
```

完成以上修改后重新编译整个镜像，生成的镜像在运行时将自动启动 v4l2_drm 应用程序。



**方式二** : 修改启动脚本

若镜像已经烧录到设备上，可通过shell进入设备的如下目录：

```
/etc/init.d
```

打开rc.sysinit文件，在文件的末尾加上如下内容：

``` sh
cd /app/mediactl_lib/
./v4l2_drm.out -f video_drm_1080x1920.conf &
cd /
```

完成以上修改后保存，设备上电重新启动，将自动运行 v4l2_drm 应用程序。



**注意**：在设备默认启动一个应用后，若需要运行其它的应用程序，建议先把默认启动的应用程序关掉。以设备上默认已开启 v4l2_drm 应用程序为例，输入以下命令关闭应用。

``` sh
killall -2 v4l2_drm.out
```



## 三、联系我们



**<font face="黑体"  size=3>[北京嘉楠捷思信息技术有限公司](www.canaan-creative.com)</font>** 
网址：canaan-creative.com
商务垂询：salesAI@canaan-creative.com





<div style="page-break-after:always"></div>

