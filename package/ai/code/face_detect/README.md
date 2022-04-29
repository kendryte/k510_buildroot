# 1 简介

人脸检测采用了retina-face网络结构，backbone选取0.25-mobilenet。使用该应用，可得到图像或视频中的每个人脸检测框以及每个人脸的左眼球/右眼球/鼻尖/左嘴角/右嘴角五个landmark。

# 2 应用使用说明

./face_detect <kmodel> <net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

kmodel：人脸检测使用的kmodel文件路径

net_len：人脸检测使用的模型的输入分辨率，net_len*net_len

valid_width：ISP送给AI计算的图像输入宽度，与net_len一致

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：人脸检测的阈值

nms_thresh：人脸检测的非极大值抑制的阈值

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）