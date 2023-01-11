set(SRC main.cc anchors_320.cc retinaface.cc ../common/k510_drm.c cv2_utils.cc ../common/v4l2.c ../common/buf_mgt.cc)
set(bin retinaface_mb_320)
set(script ../shell/retinaface_mb_320_bf16.sh ../shell/retinaface_mb_320_uint8.sh)
set(input ../imx219_0.conf ../imx219_1.conf ../video_192x320.conf)

add_definitions(-DFULL_SCREEN)

include_directories ("../common")
#include_directories(${DEMO_ROOT}/riscv64/nncase_linux_runtime/include)
#include_directories(${DEMO_ROOT}/riscv64/include)
#include_directories(${PROJECT_SOURCE_DIR}/release_isp_retinaface_mb_320_nncase)
#include_directories(${DEMO_ROOT}/riscv64/opencv_4.5.1/include/opencv4)
#
#link_directories(${DEMO_ROOT}/riscv64/nncase_linux_runtime/lib/)
## link_directories(${SDK_ROOT}/riscv64/lib/)
#link_directories(${DEMO_ROOT}/riscv64/opencv_4.5.1/lib)
#link_directories(${PROJECT_SOURCE_DIR}/release_isp_retinaface_mb_320_nncase)

add_executable(${bin} ${SRC})
target_link_libraries(${bin} nncase.runtime nncase.rt_modules.k510)
target_link_libraries(${bin} opencv_core opencv_imgcodecs opencv_imgproc opencv_videoio mediactl drm pthread)
#target_link_libraries(${bin} video)

install(TARGETS ${bin} DESTINATION exe)
install(PROGRAMS ${script} DESTINATION shell)
install(PROGRAMS ${input} DESTINATION exe)
