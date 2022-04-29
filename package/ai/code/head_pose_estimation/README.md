# 1 简介

头部态角估计，可得到图像或视频中的每个人脸的roll/yaw/pitch。

roll代表了人头歪的程度；

yaw代表了人头左右旋转的程度；

pitch代表了人头低头抬头的程度。

# 2 应用使用说明

./head_pose_estimation <fd_kmodel> <fd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <hpe_kmodel> <hpe_net_len> <hpe_out_height> <hpe_out_width> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

fd_kmodel：人脸检测使用的kmodel文件路径

fd_net_len：人脸检测使用的模型的输入分辨率，fd_net_len*fd_net_len

valid_width：ISP送给AI计算的图像输入宽度，与fd_net_len一致

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：人脸检测的阈值

nms_thresh：人脸检测的非极大值抑制的阈值

hpe_kmodel：头部姿态角估计使用的kmodel文件路径

hpe_net_len：头部姿态角估计使用的模型的输入分辨率，hpe_net_len*hpe_net_len

hpe_out_height：头部姿态角估计使用的模型的输出高度

hpe_out_width：头部姿态角估计使用的模型的输出宽度

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）