/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <nncase/runtime/host_runtime_tensor.h>
#include <nncase/runtime/interpreter.h>
#include <nncase/runtime/runtime_tensor.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utils/logger.hpp>

#include "cv2_utils.h"
#include "string.h"
#include <signal.h>
#include "retinaface.h"

/*  进程优先级  */
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <thread>
#include <mutex>
/* 申请物理内存 */
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <atomic>
#include<vector>

#include "k510_drm.h"
#include "media_ctl.h"
#include <linux/videodev2.h>

#define PROFILING 0

struct video_info dev_info[2];
static char *video_cfg_file = "video.conf";
#define SELECT_TIMEOUT		2000

std::mutex mtx;

uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv, *fbuf_argb;
int obj_cnt, obj_point[2];
cv::Point point[2][32][5];//用于清空上一帧AI计算的OSD层的显示[2个buffer交替][最多显示32个对象][5点坐标]
char *kmodel_name;

std::atomic<bool> quit(true);

void fun_sig(int sig)
{
    if(sig == SIGINT)
    {
        quit.store(false);
    }
}

void ai_worker()
{
    float obj_thresh = 0.5;
    float nms_thresh = 0.2;
    uint32_t valid_width = dev_info[0].video_width[3];
    uint32_t valid_height = dev_info[0].video_height[3];
    retinaface rf(obj_thresh, nms_thresh);

    rf.load_model(kmodel_name);

	rf.prepare_memory();

    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, valid_width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, valid_height);
    capture.set(cv::CAP_PROP_FOURCC, dev_info[0].video_out_format[3] ? V4L2_PIX_FMT_ARGB32 : V4L2_PIX_FMT_RGB24);
    mtx.unlock();
    cv::Mat osd_img;

    while(quit.load()) 
    {
        bool ret = false;
        ScopedTiming st("total");
        mtx.lock();
        ret = capture.read(osd_img);
        mtx.unlock();
        if(ret == false)
        {
            quit.store(false);
            continue; // 
        }

        for (int r = 0; r < valid_height; r++)
        {
            for (int c = 0; c < valid_width; c++)
            {
                int index = (r * valid_width + c) * 4;

                *(rf.virtual_addr_input[0] + valid_width*r + c) = *((uint8_t *)osd_img.data + index + 3); //blue
                *(rf.virtual_addr_input[0] + valid_width*valid_width + valid_width*r + c) = *((uint8_t *)osd_img.data + index + 2); //green
                *(rf.virtual_addr_input[0] + valid_width*valid_width*2 + valid_width*r + c) = *((uint8_t *)osd_img.data + index + 1); //red
            }
        } 

        rf.set_input(0);

        rf.set_output();

        {
#if PROFILING
            ScopedTiming st("run");
#endif
            rf.run();
        }
        rf.post_process();
        
        cv::Mat img_argb;
        std::vector<box_t> valid_box;
        std::vector<landmarks_t> valid_landmarks;
        rf.get_final_box(valid_box, valid_landmarks);

        {
#if PROFILING
            ScopedTiming st("display clear");
#endif
            fbuf_argb = &drm_dev.drm_bufs_argb[drm_bufs_argb_index];
            img_argb = cv::Mat(DRM_INPUT_HEIGHT, DRM_INPUT_WIDTH, CV_8UC4, (uint8_t *)fbuf_argb->map);

            for(int i=0; i<obj_point[drm_bufs_argb_index]; i++)
            {
                for (uint32_t ll = 0; ll < 5; ll++)
                {
                    //对上一帧写的数据设置透明，也就是清空之前的显示。
                    //直接memset清空整个OSD层太花时间。
                    cv::circle(img_argb, point[drm_bufs_argb_index][i][ll], 4, cv::Scalar(0, 0, 255, 0), -1);
                }
            }
            for(int i=0; i<obj_cnt; i++)
            {
                struct vo_draw_frame frame;
                frame.crtc_id = drm_dev.crtc_id;
                frame.draw_en = 0;
                frame.frame_num = i;
                draw_frame(&frame);
            }
        }

        {
#if PROFILING
            ScopedTiming st("draw frame");
#endif
            obj_cnt = 0;
            for (auto b : valid_box)
            {
                if (obj_cnt < 32)
                {
                    struct vo_draw_frame frame;
                    frame.crtc_id = drm_dev.crtc_id;
                    frame.draw_en = 1;
                    frame.frame_num = obj_cnt;
                    frame.line_x_start = (b.x * RETINAFACE_FIX_SIZE - b.w * RETINAFACE_FIX_SIZE / 2)*DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH;
                    frame.line_y_start = (b.y * RETINAFACE_FIX_SIZE - b.h * RETINAFACE_FIX_SIZE / 2)*DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT+DRM_OFFSET_HEIGHT;
                    frame.line_y_start = frame.line_y_start < DRM_OFFSET_HEIGHT ? DRM_OFFSET_HEIGHT : frame.line_y_start;
                    frame.line_x_end = (b.x * RETINAFACE_FIX_SIZE + b.w * RETINAFACE_FIX_SIZE / 2)*DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH;
                    frame.line_y_end = (b.y * RETINAFACE_FIX_SIZE + b.h * RETINAFACE_FIX_SIZE / 2)*DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT+DRM_OFFSET_HEIGHT;
                    frame.line_y_end = frame.line_y_end > (DRM_OFFSET_HEIGHT+DRM_INPUT_HEIGHT) ? (DRM_OFFSET_HEIGHT+DRM_INPUT_HEIGHT) : frame.line_y_end;
                    draw_frame(&frame);
                }
                obj_cnt += 1;
            }
        }
        printf("obj_cnt = %d \n", obj_cnt);
        {
#if PROFILING
            ScopedTiming st("draw point");
#endif
            obj_point[drm_bufs_argb_index] = 0;
            for (auto l : valid_landmarks)
            {
                for (uint32_t ll = 0; ll < 5; ll++)
                {
                    if (obj_point[drm_bufs_argb_index] < 32)
                    {
                        uint32_t x0 = l.points[2 * ll + 0] * RETINAFACE_FIX_SIZE * DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH;
                        uint32_t y0 = l.points[2 * ll + 1] * RETINAFACE_FIX_SIZE * DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT;

                        cv::circle(img_argb, cv::Point(x0, y0), 4, cv::Scalar(0, 0, 255, 255), -1);
                        point[drm_bufs_argb_index][obj_point[drm_bufs_argb_index]][ll] =  cv::Point(x0, y0);
                    }
                }
                obj_point[drm_bufs_argb_index] += 1;
            }
        }
        drm_bufs_argb_index = !drm_bufs_argb_index;
    }

    mtx.lock();
    capture.release();
    mtx.unlock();
    for(int i=0; i<obj_cnt; i++)
    {
        struct vo_draw_frame frame;
        frame.crtc_id = drm_dev.crtc_id;
        frame.draw_en = 0;
        frame.frame_num = i;
        draw_frame(&frame);
    }
}

void display_worker()
{
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(3);
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, (DRM_INPUT_WIDTH+15)/16*16);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, DRM_INPUT_HEIGHT);
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_NV12);
    mtx.unlock();
    while(quit.load()) {
        drm_bufs_index = !drm_bufs_index;
        fbuf_yuv = &drm_dev.drm_bufs[drm_bufs_index];
        cv::Mat org_img(DRM_INPUT_HEIGHT*3/2, (DRM_INPUT_WIDTH+15)/16*16, CV_8UC1, fbuf_yuv->map);
        {
            bool ret = false;
#if PROFILING
            ScopedTiming st("capture read");
#endif
            mtx.lock();
            ret = capture.read(org_img);
            mtx.unlock();
            if(ret == false)
            {
                quit.store(false);
                continue; // 
            }
        }

        if (drm_dev.req)
            drm_wait_vsync();
        fbuf_argb = &drm_dev.drm_bufs_argb[!drm_bufs_argb_index];
        if (drm_dmabuf_set_plane(fbuf_yuv, fbuf_argb)) {
            std::cerr << "Flush fail \n";
            goto exit;
        }
    }
exit:
    printf("%s ==========release \n", __func__);
    mtx.lock();
    capture.release();
    mtx.unlock();
}

int main(int argc, char *argv[])
{
    std::cout << "case " << argv[0] << " build " << __DATE__ << " " << __TIME__ << std::endl;
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <.kmodel>" << std::endl;
        return -1;
    }

    kmodel_name = argv[1];

    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = fun_sig;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    if(drm_init())
        return -1;

    if(mediactl_init(video_cfg_file, &dev_info[0]))
        return -1;

    std::thread thread_ds0(display_worker);
    std::thread thread_ds2(ai_worker);

    thread_ds0.join();
    thread_ds2.join();

    for(int i = 0; i < DRM_BUFFERS_COUNT; i++) {
        drm_destory_dumb(&drm_dev.drm_bufs[i]);
    }
    for(int i = 0; i < DRM_BUFFERS_COUNT; i++) {
        drm_destory_dumb(&drm_dev.drm_bufs_argb[i]);
    }
    
    return 0;
}