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

#include "string.h"
#include <signal.h>
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


#include "object_detect.h"
#include "simple_pose.h"
#include "cv2_utils.h"


struct video_info dev_info[2];
std::mutex mtx;
uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv, *fbuf_argb;
int obj_cnt;

std::atomic<bool> quit(true);

void fun_sig(int sig)
{
    if(sig == SIGINT)
    {
        quit.store(false);
    }
}

void ai_worker(ai_worker_args ai_args)
{
    // parse ai worker agrs
    char* body_kmodel_path = ai_args.body_kmodel_path;  // object detection kmodel path
    int body_net_len = ai_args.body_net_len;  // object detection kmodel input size is net_len * net_len
    int valid_width = ai_args.valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = ai_args.valid_height;  // isp ds2 input height, should be the same with definition in video config
    float obj_thresh = ai_args.obj_thresh;  // object detection thresh
    float nms_thresh = ai_args.nms_thresh;  // object detection nms thresh
    char* pose_kmodel_path = ai_args.pose_kmodel_path;  // simple pose kmodel path
    int pose_height = ai_args.pose_height;  // simple pose kmodel input size is pose_height * pose_width
    int pose_width = ai_args.pose_width;
    float pose_thresh = ai_args.pose_thresh;
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = valid_width * valid_width;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    objectDetect od(obj_thresh, nms_thresh, body_net_len, {valid_width, valid_height});
    od.load_model(body_kmodel_path);  // load kmodel
	od.prepare_memory();  // memory allocation
    spose spo(pose_height, pose_width, pose_thresh);
    spo.load_model(pose_kmodel_path);  // load kmodel
	spo.prepare_memory();  // memory allocation
    
    /****fixed operation for video operation****/
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    // video setting
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, body_net_len);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, body_net_len );
    // RRRRRR....GGGGGGG....BBBBBB, CHW
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_RGB24);
    mtx.unlock();


    int frame_cnt = 0;

    // define cv::Mat for ai input
    // padding offset is (valid_width - valid_height) / 2 * valid_width
    cv::Mat rgb24_img_for_ai(body_net_len, body_net_len, CV_8UC3, od.virtual_addr_input[0] + (valid_width - valid_height) / 2 * valid_width);
    // define cv::Mat for post process
    cv::Mat ori_img_R = cv::Mat(valid_height, valid_width, CV_8UC1, od.virtual_addr_input[0] + (valid_width - valid_height) / 2 * valid_width);
    cv::Mat ori_img_G = cv::Mat(valid_height, valid_width, CV_8UC1, od.virtual_addr_input[0] + (valid_width - valid_height) / 2 * valid_width + valid_width * valid_width);
    cv::Mat ori_img_B = cv::Mat(valid_height, valid_width, CV_8UC1, od.virtual_addr_input[0] + (valid_width - valid_height) / 2 * valid_width + valid_width * valid_width * 2);
    
    cv::Mat spo_img_R = cv::Mat(pose_height, pose_width, CV_8UC1, spo.virtual_addr_input[0]);
    cv::Mat spo_img_G = cv::Mat(pose_height, pose_width, CV_8UC1, spo.virtual_addr_input[0] + pose_height * pose_width);
    cv::Mat spo_img_B = cv::Mat(pose_height, pose_width, CV_8UC1, spo.virtual_addr_input[0] + pose_height * pose_width * 2);

    cv::Mat cropped_R;
    cv::Mat cropped_G;
    cv::Mat cropped_B;
    BoxInfo cropped_box;
    while(quit.load()) 
    {
        bool ret = false;
        ScopedTiming st("total", 1);
        mtx.lock();
        ret = capture.read(rgb24_img_for_ai);
        mtx.unlock();
        if(ret == false)
        {
            quit.store(false);
            continue; // 
        }
        //拷贝图像的同时修改padding方式，默认读出的图像是最后做padding，修改为前后做padding
        if(is_rgb)
        {
            // R
            memset(od.virtual_addr_input[0], PADDING_R, (valid_width - valid_height) / 2 * valid_width);
            memset(od.virtual_addr_input[0] + ((valid_width - valid_height) / 2 + valid_height) * valid_width, PADDING_R, (valid_width - (valid_width - valid_height) / 2 - valid_height) * valid_width);
            // G
            memset(od.virtual_addr_input[0] + offset_channel, PADDING_G, (valid_width - valid_height) / 2 * valid_width);
            memset(od.virtual_addr_input[0] + offset_channel + ((valid_width - valid_height) / 2 + valid_height) * valid_width, PADDING_G, (valid_width - (valid_width - valid_height) / 2 - valid_height) * valid_width);
            // B
            memset(od.virtual_addr_input[0] + offset_channel * 2, PADDING_B, (valid_width - valid_height) / 2 * valid_width);
            memset(od.virtual_addr_input[0] + offset_channel * 2 + ((valid_width - valid_height) / 2 + valid_height) * valid_width, PADDING_B, (valid_width - (valid_width - valid_height) / 2 - valid_height) * valid_width);    
        }
        else
        {
            // B
            memset(od.virtual_addr_input[0], PADDING_B, (valid_width - valid_height) / 2 * valid_width);
            memset(od.virtual_addr_input[0] + ((valid_width - valid_height) / 2 + valid_height) * valid_width, PADDING_B, (valid_width - (valid_width - valid_height) / 2 - valid_height) * valid_width);
            // G
            memset(od.virtual_addr_input[0] + offset_channel, PADDING_G, (valid_width - valid_height) / 2 * valid_width);
            memset(od.virtual_addr_input[0] + offset_channel + ((valid_width - valid_height) / 2 + valid_height) * valid_width, PADDING_G, (valid_width - (valid_width - valid_height) / 2 - valid_height) * valid_width);
            // R
            memset(od.virtual_addr_input[0] + offset_channel * 2, PADDING_R, (valid_width - valid_height) / 2 * valid_width);
            memset(od.virtual_addr_input[0] + offset_channel * 2 + ((valid_width - valid_height) / 2 + valid_height) * valid_width, PADDING_R, (valid_width - (valid_width - valid_height) / 2 - valid_height) * valid_width);
            
        }
        if(enable_dump_image)
        {
            cv::Mat padding_img_R = cv::Mat(valid_width, valid_width, CV_8UC1, od.virtual_addr_input[0]);
            cv::Mat padding_img_G = cv::Mat(valid_width, valid_width, CV_8UC1, od.virtual_addr_input[0] + offset_channel);
            cv::Mat padding_img_B = cv::Mat(valid_width, valid_width, CV_8UC1, od.virtual_addr_input[0] + offset_channel * 2);
            std::vector<cv::Mat>padding_imgparts(3);
            padding_imgparts.clear();
            padding_imgparts.push_back(padding_img_B);
            padding_imgparts.push_back(padding_img_G);
            padding_imgparts.push_back(padding_img_R);
            cv::Mat padding_img;
            cv::merge(padding_imgparts, padding_img);
            std::string padding_img_out_path = dump_img_dir + "/padding_img_" + std::to_string(frame_cnt) + ".jpg";
            cv::imwrite(padding_img_out_path, padding_img);
        }
        
        od.set_input(0);
        od.set_output();
        spo.set_input(0);
        spo.set_output();

        {
            ScopedTiming st("od run", enable_profile);
            od.run();
        }

        {
            ScopedTiming st("od get output", enable_profile);
            od.get_output();
        }
        std::vector<BoxInfo> result;
        {
            ScopedTiming st("post process", enable_profile);
            od.post_process(result);
        }

        /****fixed operation for display clear****/
        cv::Mat img_argb;
        {
            ScopedTiming st("display clear", enable_profile);
            fbuf_argb = &drm_dev.drm_bufs_argb[drm_bufs_argb_index];
            img_argb = cv::Mat(DRM_INPUT_HEIGHT, DRM_INPUT_WIDTH, CV_8UC4, (uint8_t *)fbuf_argb->map);

            for(uint32_t i = 0; i < 32; i++)
            {
                if(i == 0)
                {
                    img_argb.setTo(cv::Scalar(0, 0, 0, 0));
                }
                struct vo_draw_frame frame;
                frame.crtc_id = drm_dev.crtc_id;
                frame.draw_en = 0;
                frame.frame_num = i;
                draw_frame(&frame);
            }
        }

        {
            ScopedTiming st("draw osd", enable_profile);
            obj_cnt = 0;
            for (auto r : result)
            {
                if (obj_cnt < 32)
                {
                    struct vo_draw_frame frame;
                    frame.crtc_id = drm_dev.crtc_id;
                    frame.draw_en = 1;
                    frame.frame_num = obj_cnt;
                    int x1 = r.x2 * DRM_INPUT_WIDTH / valid_width;
                    int x0 = r.x1 * DRM_INPUT_WIDTH / valid_width;
                    int y0 = r.y1 * DRM_INPUT_HEIGHT / valid_height;
                    int y1 = r.y2 * DRM_INPUT_HEIGHT / valid_height;
                    x1 = std::max(0, std::min(x1, DRM_INPUT_WIDTH));
                    x0 = std::max(0, std::min(x0, DRM_INPUT_WIDTH));
                    y0 = std::max(0, std::min(y0, DRM_INPUT_HEIGHT));
                    y1 = std::max(0, std::min(y1, DRM_INPUT_HEIGHT));
                    frame.line_x_start = x0;
                    frame.line_x_end = x1;
                    frame.line_y_start = y0 + DRM_OFFSET_HEIGHT;
                    frame.line_y_end = y1 + DRM_OFFSET_HEIGHT;
                    draw_frame(&frame);
                
                    cv::Point origin;
                    origin.x = (int)(r.x1 * DRM_INPUT_WIDTH / valid_width);
                    origin.y = (int)(r.y1 * DRM_INPUT_HEIGHT / valid_height + 10);
                    std::string text = od.labels[r.label] + ":" + std::to_string(round(r.score * 100) / 100.0).substr(0,4);
                    cv::putText(img_argb, text, origin, cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 0, 255, 255), 1, 8, 0);
                }
                cropped_box = get_enlarged_box(r, ori_img_R);
                {
                    ScopedTiming st("spose process", enable_profile);
                    spo.set_valid_box(cropped_box, ori_img_R);
                }
                cropped_R = spo.crop_image(ori_img_R);
                cv::resize(cropped_R, spo_img_R, cv::Size(pose_width, pose_height), cv::INTER_AREA);
                cropped_G = spo.crop_image(ori_img_G);
                cv::resize(cropped_G, spo_img_G, cv::Size(pose_width, pose_height), cv::INTER_AREA);
                cropped_B = spo.crop_image(ori_img_B);
                cv::resize(cropped_B, spo_img_B, cv::Size(pose_width, pose_height), cv::INTER_AREA);              
                {
                    ScopedTiming st("spose run", enable_profile);
                    spo.run();
                }
                {
                    ScopedTiming st("spose post process", enable_profile);
                    spo.post_process();
                    draw_pose(valid_height, valid_width, img_argb, spo.keypoints, spo.thresh);
                }
                if(enable_dump_image)
                {   
                    std::vector<cv::Mat>cropped_imgparts(3);                  
                    cropped_imgparts.clear();
                    cropped_imgparts.push_back(cropped_B);
                    cropped_imgparts.push_back(cropped_G);
                    cropped_imgparts.push_back(cropped_R); 
                    cv::Mat cropped_img;
                    cv::merge(cropped_imgparts, cropped_img);
                    std::string cropped_image_out_path = dump_img_dir + "/cropped_" + std::to_string(frame_cnt) + "_" + std::to_string(obj_cnt) + ".jpg";
                    cv::imwrite(cropped_image_out_path, cropped_img); 
                    std::vector<cv::Mat>resized_imgparts(3);
                    resized_imgparts.clear();
                    resized_imgparts.push_back(spo_img_B);
                    resized_imgparts.push_back(spo_img_G);          
                    resized_imgparts.push_back(spo_img_R);
                    cv::Mat resized_img;
                    cv::merge(resized_imgparts, resized_img);
                    std::string resized_image_out_path = dump_img_dir + "/resized_" + std::to_string(frame_cnt) + "_" + std::to_string(obj_cnt) + ".jpg";
                    cv::imwrite(resized_image_out_path, resized_img); 
                }
                obj_cnt += 1;
            }
        }
        frame_cnt += 1;
        drm_bufs_argb_index = !drm_bufs_argb_index;
    }
    
    /****fixed operation for capture release and display clear****/
    printf("%s ==========release \n", __func__);
    mtx.lock();
    capture.release();
    mtx.unlock();
    for(uint32_t i = 0; i < 32; i++)
    {
        struct vo_draw_frame frame;
        frame.crtc_id = drm_dev.crtc_id;
        frame.draw_en = 0;
        frame.frame_num = i;
        draw_frame(&frame);
    }
}

/****fixed operation for display worker****/
void display_worker(int enable_profile)
{
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(3);
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, (DRM_INPUT_WIDTH + 15) / 16 * 16);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, DRM_INPUT_HEIGHT);
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_NV12);
    mtx.unlock();
    while(quit.load()) 
    {
        drm_bufs_index = !drm_bufs_index;
        fbuf_yuv = &drm_dev.drm_bufs[drm_bufs_index];
        cv::Mat org_img(DRM_INPUT_HEIGHT * 3 / 2, (DRM_INPUT_WIDTH + 15) / 16 * 16, CV_8UC1, fbuf_yuv->map);
        {
            bool ret = false;
            ScopedTiming st("capture read",enable_profile);
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
        if (drm_dmabuf_set_plane(fbuf_yuv, fbuf_argb)) 
        {
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
    if (argc < 15)
    {
        std::cerr << "Person pose by simple pose Usage: " << argv[0] << " <body_kmodel> <body_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <pose_kmodel> <pose_height> <pose_width> <pose_thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
        return -1;
    }
    // parse args for ai worker
    ai_worker_args ai_args;
    ai_args.body_kmodel_path = argv[1];
    ai_args.body_net_len = atoi(argv[2]);
    ai_args.valid_width = atoi(argv[3]);
    ai_args.valid_height = atoi(argv[4]);
    if(ai_args.valid_height > ai_args.valid_width)
    {
        std::cerr << "You should set width bigger than height" << std::endl;
                std::abort();
    }
    if(ai_args.valid_width != ai_args.body_net_len)
    {
        std::cerr << "We won't resize image for gnne input, so valid_width should be equal to net_len" << std::endl;
                std::abort();
    }
    ai_args.obj_thresh = atof(argv[5]);
    ai_args.nms_thresh = atof(argv[6]);
    ai_args.pose_kmodel_path = argv[7];    
    ai_args.pose_height = atoi(argv[8]);
    ai_args.pose_width = atoi(argv[9]);
    ai_args.pose_thresh = atof(argv[10]);
    char* video_cfg_file = argv[11];
    ai_args.is_rgb = atoi(argv[12]);
    ai_args.enable_profile = atoi(argv[13]);
    int enable_profile = atoi(argv[13]);
    ai_args.dump_img_dir = argv[14];

    /****fixed operation for ctrl+c****/
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = fun_sig;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);


    /****fixed operation for drm init****/
    if(drm_init())
        return -1;


    /****fixed operation for mediactl init****/
    if(mediactl_init(video_cfg_file, &dev_info[0]))
        return -1;


    // create thread for display
    std::thread thread_ds0(display_worker, enable_profile);
    // create thread for ai worker
    std::thread thread_ds2(ai_worker, ai_args);

    thread_ds0.join();
    thread_ds2.join();

    /****fixed operation for drm deinit****/
    for(uint32_t i = 0; i < DRM_BUFFERS_COUNT; i++) 
    {
        drm_destory_dumb(&drm_dev.drm_bufs[i]);
    }
    for(uint32_t i = 0; i < DRM_BUFFERS_COUNT; i++) 
    {
        drm_destory_dumb(&drm_dev.drm_bufs_argb[i]);
    }
	mediactl_exit();     
    return 0;
}
