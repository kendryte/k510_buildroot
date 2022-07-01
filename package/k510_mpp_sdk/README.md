# k510_mpp_sdk

k510_mpp_sdk is a set of interfaces for media process for k510


# complie
1. git clone mpp_sdk to k510_buildroot/packages.
2. cp k510_mpp_sdk/compile_mpp.sh ../k510_crb_lp3_v1_2_defconfig
3. ./compile_mpp.sh, NOTE: the path in compile_mpp.sh is my path, you should make it yours.



# test
1. copy the executable program sample_xxx to k510 board
    for example: cp sample_vi /app/mpp_sample
                 cp sample_vps /app/mpp_sample
                 cp sample_venc /app/mpp_sample
                 cp sample_vo /app/mpp_sample
                 cp sample_vio /app/mpp_sample

2. copy the mpp lib to k510 board
    for example: cp libmppsys.so /lib64/lpd64
                 cp libmppvi.so /lib64/lpd64
                 cp libmppvps.so /lib64/lpd64
                 cp libmppvenc.so /lib64/lpd64
                 cp libmppvo.so /lib64/lpd64

3. copy source data and config file
    for example: cp akiyo_cif_nv12.yuv /app/mpp_sample
                 cp test_1080x1920_10.yuv /app/sample
                 cp vi_device.conf /app/sample
                 cp imx219_0.conf /app/sample
                 cp imx219_1.conf /app/sample

4. run sample_vi:

    ./sample_vi

5. run sample_vps:

    scale: ./sample_vps -i ./akiyo_cif_nv12.yuv -type scale -inFmt nv12 -inputW 352 -inputH 288 -o output.yuv -outFmt nv12 -outputW 1920 -outputH 1080

    rotation: ./sample_vps -i ./akiyo_cif_nv12.yuv -type rotation -inFmt nv12 -inputW 352 -inputH 288 -o output.yuv -outFmt nv12 -outputW 288 -outputH 352

6. run sample_venc:

    ./sample_venc -t h264 -n 1 -w 352 -h 288 -p high -l 42 -i ./akiyo_cif_nv12.yuv -o output.264 -fmt nv12 -rc cbr -fps 30 -qp 25 -goplen 30 -bitrate 3000000

7. run sample_vo: (display 1080x1920 base frame and a 880x500 layer frame)

    ./sample_vo -i ./test_1080x1920_10.yuv -inFmt nv12 -inputW 1080 -inputH 1920
    
8. run sample_vio (VI ---> VPS ---> VO,  pipeline)

    ./sample_vio -inFmt nv12 -vpsType scale -vpsOutputW 1088 -vpsOutputH 1920

9. run sample_stream (VI ---> VPS ---> VENC ---> push stream,  pipeline, you can pull the stream by vlc to  play rtsp://10.100.229.104:8554/sampleStream. NOTE: 10.100.229.104 is my ip)

    ./sample_stream -vpsType scale -vpsOutputW 1088 -vpsOutputH 1920

10. run sample_facedetect (VI ---> AI(face detect) ---> VO, pipeline)

    ./sample_facedetect -kmodel ./retinaface_mobile0.25_320_bf16_swapRB_with_preprocess.kmodel -netLen 320 -detectW 320 -detectH 240 -objThr 0.5 -nmsThr 0.2


# set loglevel

export ENC_LOG_LEVEL=x(0,1,2,3)
0: ERROR
1: WARNING
2: INFO
3: DEBUG