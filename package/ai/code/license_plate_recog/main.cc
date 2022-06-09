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


#include "retinalpd.h"
#include "lprnet.h"
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
    char* lpd_kmodel_path = ai_args.lpd_kmodel_path;  // license detection kmodel path
    int lpd_net_len = ai_args.lpd_net_len;  // license detection kmodel input size is lpd_net_len * lpd_net_len
    int valid_width = ai_args.valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = ai_args.valid_height;  // isp ds2 input height, should be the same with definition in video config
    float obj_thresh = ai_args.obj_thresh;  // license detection thresh
    float nms_thresh = ai_args.nms_thresh;  // license detection nms thresh
    char* lpr_kmodel_path = ai_args.lpr_kmodel_path;  // license recognization kmodel path
    int lpr_net_height = ai_args.lpr_net_height;  // license recognization kmodel input size is lpr_net_height * lpr_net_width
    int lpr_net_width = ai_args.lpr_net_width;  // license recognization
    int lpr_num  = ai_args.lpr_num;  //     
    int char_num = ai_args.char_num;  // 
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = valid_width * valid_width;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    retinalpd lpd(lpd_net_len, obj_thresh, nms_thresh);
    lpd.load_model(lpd_kmodel_path);  // load kmodel
	lpd.prepare_memory();  // memory allocation
    lprnet lpr(lpr_net_height, lpr_net_width, char_num, lpr_num);
    lpr.load_model(lpr_kmodel_path);  // load kmodel
	lpr.prepare_memory();  // memory allocation
    cv::Mat cropped_R;
    cv::Mat cropped_G;
    cv::Mat cropped_B;
    box_t cropped_box;
    std::string pred_str;   
    
    cv::Mat lpr_img_R = cv::Mat(lpr_net_height, lpr_net_width, CV_8UC1, lpr.virtual_addr_input[0]);
    cv::Mat lpr_img_G = cv::Mat(lpr_net_height, lpr_net_width, CV_8UC1, lpr.virtual_addr_input[0] + lpr_net_height * lpr_net_width);
    cv::Mat lpr_img_B = cv::Mat(lpr_net_height, lpr_net_width, CV_8UC1, lpr.virtual_addr_input[0] + lpr_net_height * lpr_net_width * 2);

    /****fixed operation for video operation****/
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    // video setting
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, lpd_net_len);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, lpd_net_len);
    // RRRRRR....GGGGGGG....BBBBBB, CHW
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_RGB24);
    mtx.unlock();


    int frame_cnt = 0;
    // define cv::Mat for ai input
    // padding offset is 0, padding is at last
    cv::Mat rgb24_img_for_ai(lpd_net_len, lpd_net_len, CV_8UC3, lpd.virtual_addr_input[0]);
    // define cv::Mat for post process
    cv::Mat ori_img_R = cv::Mat(valid_height, valid_width, CV_8UC1, lpd.virtual_addr_input[0]);
    cv::Mat ori_img_G = cv::Mat(valid_height, valid_width, CV_8UC1, lpd.virtual_addr_input[0] + valid_width * valid_width);
    cv::Mat ori_img_B = cv::Mat(valid_height, valid_width, CV_8UC1, lpd.virtual_addr_input[0] + valid_width * valid_width * 2);
    frame_coordinate_info frame_coordinate;
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
            memset(lpd.virtual_addr_input[0] + (valid_height * valid_width), PADDING_R, (valid_width - valid_height) * valid_width);
            // G
            memset(lpd.virtual_addr_input[0] + offset_channel + (valid_height * valid_width), PADDING_G, (valid_width - valid_height) * valid_width);
            // B
            memset(lpd.virtual_addr_input[0] + offset_channel * 2 + (valid_height * valid_width), PADDING_B, (valid_width - valid_height) * valid_width);
        }
        else
        { 
            // B
            memset(lpd.virtual_addr_input[0] + (valid_height * valid_width), PADDING_B, (valid_width - valid_height) * valid_width);
            // G
            memset(lpd.virtual_addr_input[0] + offset_channel + (valid_height * valid_width), PADDING_G, (valid_width - valid_height) * valid_width);
            // R
            memset(lpd.virtual_addr_input[0] + offset_channel * 2 + (valid_height * valid_width), PADDING_R, (valid_width - valid_height) * valid_width);
        
        }
        if(enable_dump_image)
        {
            std::vector<cv::Mat>ori_imgparts(3);
            ori_imgparts.clear();
            ori_imgparts.push_back(ori_img_B);
            ori_imgparts.push_back(ori_img_G);
            ori_imgparts.push_back(ori_img_R);
            cv::Mat ori_img;
            cv::merge(ori_imgparts, ori_img);
            std::string ori_img_out_path = dump_img_dir + "/ori_img_" + std::to_string(frame_cnt) + ".jpg";
            cv::imwrite(ori_img_out_path, ori_img);
        }
        lpd.set_input(0);
        lpd.set_output();
        lpr.set_input(0);
        lpr.set_output();

        {
            ScopedTiming st("lpd run", enable_profile);
            lpd.run();
        }
        
        {
            ScopedTiming st("post process", enable_profile);
            lpd.post_process();
        }

        std::vector<box_t> valid_box;
        std::vector<landmarks_t> valid_landmarks;
        {
            ScopedTiming st("get final box", enable_profile);
            lpd.get_final_box(valid_box, valid_landmarks);
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
            ScopedTiming st("run license recognization and draw osd", enable_profile);
            obj_cnt = 0;
            for (auto l : valid_landmarks)
            {
                {
                    ScopedTiming st("lpr process", enable_profile);
                    cropped_box = get_box_from_landmarks(ori_img_R, valid_width, valid_height, l.points, 4);
                    lpr.set_valid_box(cropped_box, ori_img_R); 
                    cropped_R = lpr.crop_image(ori_img_R);
                    cropped_G = lpr.crop_image(ori_img_G);
                    cropped_B = lpr.crop_image(ori_img_B);
                    // cv::flip(cropped_R, cropped_R, 1);
                    // cv::flip(cropped_G, cropped_G, 1);
                    // cv::flip(cropped_B, cropped_B, 1);
                    lpr.get_perspective_matrix(l, ori_img_R, valid_width, valid_height);
                    lpr.perspective_image(cropped_R, lpr_img_R);
                    lpr.perspective_image(cropped_G, lpr_img_G);
                    lpr.perspective_image(cropped_B, lpr_img_B);
                }        
                {
                    ScopedTiming st("lpr run", enable_profile);
                    lpr.run();
                }  
                {
                    ScopedTiming st("lpr postprocess", enable_profile);
                    pred_str = lpr.postprocess();
                }   
                
                frame_coordinate = get_frame_coord(valid_box[obj_cnt], valid_width, valid_height);                
                int x0 = frame_coordinate.startx + 30;
                int y0 = frame_coordinate.starty - OFFSET_Y - 20;
                x0 = std::max(0, std::min(x0, DRM_INPUT_WIDTH));
                y0 = std::max(0, std::min(y0, DRM_INPUT_HEIGHT));
                cv::putText(img_argb, pred_str, cv::Point(x0, y0), cv::FONT_HERSHEY_COMPLEX, 1.2, cv::Scalar(255, 0, 0, 255), 2, 8, 0);              
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
                    std::vector<cv::Mat>perspective_imgparts(3);                  
                    perspective_imgparts.clear();
                    perspective_imgparts.push_back(lpr_img_B);
                    perspective_imgparts.push_back(lpr_img_G);          
                    perspective_imgparts.push_back(lpr_img_R);
                    cv::Mat perspective_img;
                    cv::merge(perspective_imgparts, perspective_img);
                    std::string perspective_image_out_path = dump_img_dir + "/perspective_" + std::to_string(frame_cnt) + "_" + std::to_string(obj_cnt) + ".jpg";
                    cv::imwrite(perspective_image_out_path, perspective_img); 
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
    if (argc < 16)
    {
        std::cerr << "Usage: " << argv[0] << " <lpd_kmodel> <lpd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <lpr_kmodel> <lpr_net_height> <lpr_net_width> <lpr_num> <char_num> <video_config> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
        return -1;
    }
    // parse args for ai worker
    ai_worker_args ai_args;
    ai_args.lpd_kmodel_path = argv[1];
    ai_args.lpd_net_len = atoi(argv[2]);
    ai_args.valid_width = atoi(argv[3]);
    ai_args.valid_height = atoi(argv[4]);
    if(ai_args.valid_height > ai_args.valid_width)
    {
        std::cerr << "You should set width bigger than height" << std::endl;
                std::abort();
    }
    if(ai_args.valid_width != ai_args.lpd_net_len)
    {
        std::cerr << "We won't resize image for gnne input, so valid_width should be equal to net_len" << std::endl;
                std::abort();
    }
    ai_args.obj_thresh = atof(argv[5]);
    ai_args.nms_thresh = atof(argv[6]);
    ai_args.lpr_kmodel_path = argv[7];
    ai_args.lpr_net_height = atoi(argv[8]);
    ai_args.lpr_net_width = atoi(argv[9]);
    ai_args.lpr_num = atoi(argv[10]);
    ai_args.char_num = atoi(argv[11]);
    char* video_cfg_file = argv[12];
    ai_args.is_rgb = atoi(argv[13]);
    ai_args.enable_profile = atoi(argv[14]);
    int enable_profile = atoi(argv[14]);
    ai_args.dump_img_dir = argv[15];

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
