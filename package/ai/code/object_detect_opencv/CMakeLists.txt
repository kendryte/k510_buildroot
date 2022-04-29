set(SRC main.cc cv2_utils.cc object_detect.cc ../drm/k510_drm.c)
set(bin object_detect_opencv)
set(script data/bf16.sh data/uint8.sh)
set(input data/imx219_0.conf data/imx219_1.conf data/video.conf)

include_directories ("../drm")

add_executable(${bin} ${SRC})
target_link_libraries(${bin} nncase.runtime nncase.rt_modules.k510)
target_link_libraries(${bin} opencv_core opencv_imgcodecs opencv_imgproc opencv_videoio mediactl drm pthread)

install(TARGETS ${bin} DESTINATION object_detect_opencv)
install(PROGRAMS ${script} DESTINATION object_detect_opencv)
install(PROGRAMS ${input} DESTINATION object_detect_opencv)
