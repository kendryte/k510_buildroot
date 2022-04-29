# 1 简介

人体关键点检测主要有两种检测方式，一个是自上而下，一种是自下而上。本应用采用了自下而上的模型openpose。使用该应用，可得到图像或视频中的每个人体的17个关键点。

# 2 应用使用说明

./openpose <kmodel> <net_width> <net_height> <valid_width> <valid_height> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

​    各参数释义如下：

kmodel：人体关键点检测使用的kmodel文件路径

net_width：人体关键点检测使用的模型的输入宽度

net_height：人体关键点检测使用的模型的输入高度

valid_width：ISP送给AI计算的图像输入宽度，与net_width一致, 

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）