# 1 简介

人体关键点检测主要有两种检测方式，一个是自上而下，一种是自下而上。本应用采用了自上而下的模型采用了YOLOV5S进行人体检测，然后使用simplepose进行关键点回归。使用该应用，可得到图像或视频中的每个人体的17个关键点。

# 2 应用使用说明

./simple_pose <body_kmodel> <body_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <pose_kmodel> <pose_height> <pose_width> <pose_thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

body_kmodel：人体检测使用的kmodel文件路径

body_net_len：人体检测使用的模型的输入分辨率，body_net_len*body_net_len

valid_width：ISP送给AI计算的图像输入宽度，与body_net_len一致

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：人体检测的阈值

nms_thresh：人体检测的非极大值抑制的阈值

pose_kmodel：关键点检测使用的kmodel文件路径

pose_height：关键点检测使用的模型的输入高度

pose_width：关键点检测使用的模型的输入宽度

pose_thresh：关键点检测使用的阈值

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）