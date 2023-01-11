set(SRC main.cc cv2_utils.cc anchors_320.cc anchors_640.cc retinaface.cc pfld.cc ../common/k510_drm.c ../common/v4l2.c ../common/buf_mgt.cc)
set(bin face_landmarks)
set(script ../shell/face_landmarks.sh)
set(input ../imx219_0.conf ../imx219_1.conf ../video_object_detect_320.conf ../video_object_detect_640.conf)

add_definitions(-DFULL_SCREEN)

include_directories ("../common")
include_directories(${DEMO_ROOT}/riscv64/include)
include_directories(${DEMO_ROOT}/riscv64/opencv_4.5.1/include/opencv4)
include_directories(${DEMO_ROOT}/riscv64/video_zt)


link_directories(${DEMO_ROOT}/riscv64/lib/)
link_directories(${DEMO_ROOT}/riscv64/opencv_4.5.1/lib)
link_directories(${DEMO_ROOT}/riscv64/video_zt)

add_executable(${bin} ${SRC})
target_link_libraries(${bin} mediactl drm pthread)
target_link_libraries(${bin} nncase.runtime nncase.rt_modules.k510)
target_link_libraries(${bin} opencv_core opencv_imgcodecs opencv_imgproc opencv_videoio)

install(TARGETS ${bin} DESTINATION exe)
install(PROGRAMS ${script} DESTINATION shell)
install(PROGRAMS ${input} DESTINATION exe)
