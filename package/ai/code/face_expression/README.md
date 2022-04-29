# 1 简介

人脸表情识别采用了人脸表情分类的方式，使用该应用可得到图像或视频中的每个人脸属于以下表情的概率。

"Neutral", "Happy", "Sad", "Surprise", "Fear", "Disgust", "Anger", "Contempt"。

# 2 应用使用说明

./face_expression <fd_kmodel> <fd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <fe_kmodel> <fe_net_len> <fe_num> <thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

fd_kmodel：人脸检测使用的kmodel文件路径

fd_net_len：人脸检测使用的模型的输入分辨率，fd_net_len*fd_net_len

valid_width：ISP送给AI计算的图像输入宽度，与fd_net_len一致,

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：人脸检测的阈值

nms_thresh：人脸检测的非极大值抑制的阈值

fe_kmodel：人脸表情特征提取使用的kmodel文件路径

fe_net_len：人脸表情特征提取的模型的输入分辨率，fe_net_len*fe_net_len

fe_num：人脸表情特征分类后的个数

thresh：人脸表情识别阈值

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）