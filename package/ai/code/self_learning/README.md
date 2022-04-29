# 1 简介

自学习借鉴的是KNN（k-Nearest Neighbors）的思想。该算法的思想是： 一个样本与数据集中的k个样本最相似， 如果这k个样本中的大多数属于某一个类别， 则该样本也属于这个类别。

# 2 应用使用说明

./self_learning <valid_width> <valid_height> <fe_kmodel> <fe_net_len> <fe_num> <max_register_obj> <thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>

各参数释义如下：

valid_width：ISP送给AI计算的图像输入宽度，与net_len一致, 

valid_height：ISP送给AI计算的图像输入高度，不大于valid_width

fe_kmodel：特征提取使用的kmodel文件路径

fe_net_len：特征提取的模型的输入分辨率，fe_net_len*fe_net_len

fe_num：特征提取的特征点数

max_register_obj：底库每类最多录入个数

thresh：人脸识别阈值

video_config: ISP相应配置文件

is_rgb：ISP送给AI计算的图像排布格式，RGB为1，BGR为0

enable_profile：是否打开耗时统计，1代表打开，0代表关闭

dump_image_dir：是否dump中间图像，None代表否，非None代表dump的图像路径，该路径需真实存在（提前创建好）