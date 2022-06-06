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
#include "object_detect.h"

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
int obj_cnt;
std::vector<BoxInfo> result0;
std::vector<BoxInfo> result1;
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
    float obj_thresh = 0.2;
    float nms_thresh = 0.45;
    uint32_t valid_width = dev_info[0].video_width[3];
    uint32_t valid_height = dev_info[0].video_height[3];
    objectDetect od(obj_thresh, nms_thresh);

    od.load_model(kmodel_name);

	od.prepare_memory();

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
        ScopedTiming st("total");
        mtx.lock();
        capture.read(osd_img); //ARGB
        mtx.unlock();

        for (int r = 0; r < valid_height; r++)
        {
            for (int c = 0; c < valid_width; c++)
            {
                int index = (r * valid_width + c) * 4;

                *(od.virtual_addr_input[0] +valid_width*40 + valid_width*r + c) = *((uint8_t *)osd_img.data + index + 3); //blue
                *(od.virtual_addr_input[0] +valid_width*40 + valid_width*valid_width + valid_width*r + c) = *((uint8_t *)osd_img.data + index + 2); //green
                *(od.virtual_addr_input[0] +valid_width*40 + valid_width*valid_width*2 + valid_width*r + c) = *((uint8_t *)osd_img.data + index + 1); //red
            }
        } 

        od.set_input(0);
        od.set_output();

        {
#if PROFILING
            ScopedTiming st("od run");
#endif
            od.run();
        }

        {
#if PROFILING
            ScopedTiming st("od get output");
#endif
            od.get_output();
        }
        std::vector<BoxInfo> result;
        {
#if PROFILING
            ScopedTiming st("post process");
#endif
            od.post_process(result);
        }

        cv::Mat img_argb;
        {
#if PROFILING
            ScopedTiming st("display clear");
#endif
            fbuf_argb = &drm_dev.drm_bufs_argb[drm_bufs_argb_index];
            img_argb = cv::Mat(DRM_INPUT_HEIGHT, DRM_INPUT_WIDTH, CV_8UC4, (uint8_t *)fbuf_argb->map);

            for (auto r : drm_bufs_argb_index?result1:result0)
            {
                cv::Point origin;
                origin.x = (int)(r.x1 * DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH);
                origin.y = (int)(r.y1 * DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT - 10);
                std::string text = od.labels[r.label] + ":" + std::to_string(round(r.score * 100) / 100.0);
                cv::putText(img_argb, text, origin, cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 0, 255, 0), 1, 8, 0);
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
            ScopedTiming st("draw osd");
#endif
            obj_cnt = 0;
            for (auto r : result)
            {
                if (obj_cnt < 32)
                {
                    struct vo_draw_frame frame;
                    frame.crtc_id = drm_dev.crtc_id;
                    frame.draw_en = 1;
                    frame.frame_num = obj_cnt;
                    frame.line_x_start = r.x1*DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH;
                    frame.line_y_start = r.y1*DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT+DRM_OFFSET_HEIGHT;
                    frame.line_y_start = frame.line_y_start < DRM_OFFSET_HEIGHT ? DRM_OFFSET_HEIGHT : frame.line_y_start;
                    frame.line_x_end = r.x2*DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH;
                    frame.line_y_end = r.y2*DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT+DRM_OFFSET_HEIGHT;
                    frame.line_y_end = frame.line_y_end > (DRM_OFFSET_HEIGHT+DRM_INPUT_HEIGHT) ? (DRM_OFFSET_HEIGHT+DRM_INPUT_HEIGHT) : frame.line_y_end;
                    draw_frame(&frame);
                
                    cv::Point origin;
                    origin.x = (int)(r.x1*DRM_INPUT_WIDTH/GNNE_INPUT_WIDTH);
                    origin.y = (int)(r.y1*DRM_INPUT_HEIGHT/GNNE_INPUT_HEIGHT - 10);
                    std::string text = od.labels[r.label] + ":" + std::to_string(round(r.score * 100) / 100.0);
                    cv::putText(img_argb, text, origin, cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 0, 255, 255), 1, 8, 0);
                }
                obj_cnt += 1;
            }
        }
        if(drm_bufs_argb_index)
            result1.assign(result.begin(), result.end());
        else
            result0.assign(result.begin(), result.end());
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
#if PROFILING
            ScopedTiming st("capture read");
#endif
            mtx.lock();
            capture.read(org_img);
            mtx.unlock();
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
        std::cerr << "Usage: " << argv[0] << " <.kmodel> <image_file>" << std::endl;
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