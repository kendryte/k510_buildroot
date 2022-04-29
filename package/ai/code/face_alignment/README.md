# 1 简介

人脸对齐，可得到图像或视频中的每个人脸估计出来的depth或者pncc信息。

# 2 应用使用说明

./face_alignment <fd_kmodel> <fd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <fk_kmodel> <fk_net_len> <fk_num> <nme_thresh> <max_loop> <fa_kmodel> <fa_net_len> <fa_num> <depth_or_pncc> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

fd_kmodel：人脸检测使用的kmodel文件路径

fd_net_len：人脸检测使用的模型的输入分辨率，fd_net_len*fd_net_len

valid_width：ISP送给AI计算的图像输入宽度，与fd_net_len一致

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：人脸检测的阈值

nms_thresh：人脸检测的非极大值抑制的阈值

fk_kmodel：人脸关键点检测使用的kmodel文件路径

fk_net_len：人脸关键点检测的模型的输入分辨率，fk_net_len*fk_net_len

nme_thresh：一帧图像前后两次人脸关键点检测误差阈值

max_loop：一帧图像最多进行人脸关键点检测次数

fa_kmodel：人脸对齐使用的kmodel文件路径

fa_net_len：人脸对齐的模型输入分辨率，fa_net_len*fa_net_len

fa_num：人脸对齐的模型输出的点数

depth_or_pncc：估计depth信息或pncc信息

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）