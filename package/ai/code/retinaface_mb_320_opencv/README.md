# release_isp_retinaface_mb_320_nncase


最新的kmodel为kendryte_uint8_crop_to_broadcast_and_binary_tiling.kmodel

在config.h中

##### #define USER_ALLOC_BUFFER       1

程序分配输入输出连续的物理内存，不用nncase自动生成

##### #define USE_CACHE_FLUSH           0

置1使用cache flush的方式，置0使用BIT33的方式。

##### #define LIBRUNTIME_SYNC_CACHE_FLUSH         1
runtime 的sync 使用 cache flush

##### #define KMODEL_STACKVM_OUPUT_ERR    1
kmodel中stackvm记录的output顺序不一致, 如果后续case修复后，要置为0

##### #define NNCASE_SCOPEDTIMING     1

判断使用哪个runtime库，如果使用库里的scopedtiming函数，则置1。否则置0。

##### #define USE_UINT8_MODEL         1
判断使用哪个模型，如果使用uint8的模型，则置1。 bf32的模型则置0。


目前还存在的问题:
正常情况下自定义output，interp_fd.run()中k510 postprocess_outputs不会花销太多时间。但是目前并不正常，发现是因为interp_fd.output_tensor(i，有问题，目前需要AI软件组解决。
