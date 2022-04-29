set(SRC main.cc cv2_utils.cc anchors_320.cc retinaface.cc ../drm/k510_drm.c)
set(bin retinaface_mb_320_opencv)
set(script data/bf16.sh data/uint8.sh)
set(input data/imx219_0.conf data/imx219_1.conf data/video.conf)

include_directories ("../drm")
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

install(TARGETS ${bin} DESTINATION retinaface_mb_320_opencv)
install(PROGRAMS ${script} DESTINATION retinaface_mb_320_opencv)
install(PROGRAMS ${input} DESTINATION retinaface_mb_320_opencv)
