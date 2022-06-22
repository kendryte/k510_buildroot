set(SRC main.cc cv2_utils.cc ../common/v4l2.c object_detect.cc ../common/k510_drm.c)
set(bin object_detect_v4l2)
set(script ../shell/object_detect_v4l2_bf16.sh ../shell/object_detect_v4l2_uint8.sh)
set(input ../imx219_0.conf ../imx219_1.conf ../video_192x320.conf)

add_definitions(-DFULL_SCREEN)

include_directories ("../common")

add_executable(${bin} ${SRC})
target_link_libraries(${bin} nncase.runtime nncase.rt_modules.k510)
target_link_libraries(${bin} opencv_core opencv_imgcodecs opencv_imgproc  mediactl drm pthread)

install(TARGETS ${bin} DESTINATION exe)
install(PROGRAMS ${script} DESTINATION shell)
install(PROGRAMS ${input} DESTINATION exe)
