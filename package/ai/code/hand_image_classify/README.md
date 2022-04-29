# 1 简介

指尖指定区域识别主要包含3个流程，手掌检测+手掌关键点检测+图像识别。其中，手掌检测使用了512x512分辨率的 tiny-yolov3;手掌关键点检测使用了256x256分辨率的squeezenet1.1;图像识别使用了基于imagenet训练出来的mobilenetv2。通过手部关键点检测，利用两个食指尖，框定待识别区域。利用imagenet分类模型，确定待识别区域。

# 2 应用使用说明

./hand_image_classify <hd_kmodel> <hd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <hld_kmodel> <hld_net_len> <hld_num> <iclass_kmodel> <iclass_net_len> <iclass_num> <iclass_labels> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

​    各参数释义如下：

hd_kmodel：手掌检测使用的kmodel文件路径

hd_net_len：手掌检测使用的模型的输入分辨率，hd_net_len*hd_net_len

valid_width：ISP送给AI计算的图像输入宽度，与hd_net_len一致

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：手掌检测的阈值

nms_thresh：手掌检测的非极大值抑制的阈值

hld_kmodel：手掌关键点使用的kmodel文件路径

hld_net_len：手掌关键点的模型的输入分辨率，hld_net_len*hld_net_len

hld_num：手掌关键点点数

iclass_kmodel：图像分类使用的kmodel文件路径

iclass_net_len：图像分类的模型的输入分辨率，iclass_net_len*iclass_net_len

iclass_num：图像分类的类别数

iclass_labels：图像分类的类别文件

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）