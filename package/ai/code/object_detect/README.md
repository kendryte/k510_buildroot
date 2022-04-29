# 1 简介

目标检测采用了YOLOV5，使用该应用，可得到图像或视频中属于以下标签的目标的检测框。

​    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck",
​     "boat", "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
​     "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe",
​     "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard",
​     "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle",
​     "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
​     "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake",
​     "chair", "couch", "potted plant", "bed", "dining table", "toilet", "tv", "laptop",
​     "mouse", "remote", "keyboard", "cell phone", "microwave", "oven", "toaster", "sink",
​     "refrigerator", "book", "clock", "vase", "scissors", "teddy bear", "hair drier", "toothbrush"

# 2 应用使用说明

./object_detect <kmodel> <net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

kmodel：目标检测使用的kmodel文件路径

net_len：目标检测使用的模型的输入分辨率，net_len*net_len

valid_width：ISP送给AI计算的图像输入宽度，与net_len一致

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

obj_thresh：目标检测的阈值

nms_thresh：目标检测的非极大值抑制的阈值

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）