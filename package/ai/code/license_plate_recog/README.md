# 1 简介

车牌识别的整体流程实际上包含了车牌检测+车牌识别两个流程。车牌检测采用了retinanet，车牌识别采用了lprnet。使用该应用，可得到图像或视频中的每个车牌的内容。

# 2 应用使用说明

./license_plate_recog <lpd_kmodel> <lpd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <lpr_kmodel> <lpr_net_height> <lpr_net_width> <lpr_num> <char_num> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

lpd_kmodel：车牌检测使用的kmodel文件路径

lpd_net_len：车牌检测使用的模型的输入分辨率，lpd_net_len*lpd_net_len

valid_width：ISP送给AI计算的图像输入宽度，与lpd_net_len一致, 

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：车牌检测的阈值

nms_thresh：车牌检测的非极大值抑制的阈值

lpr_kmodel：车牌识别使用的kmodel文件路径

lpr_net_height：车牌识别的模型的输入高度

lpr_net_width： 车牌识别的模型的输入宽度

lpr_num：车牌识别的模型的输出个数

char_num：车牌识别的总字符个数

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）