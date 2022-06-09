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


#include "gerecorg.h"
#include "cv2_utils.h"
#include "key.h"
#include "hal_key.h"

struct video_info dev_info[2];
std::mutex mtx;
std::mutex mtx_key;
volatile int key_values = KEY_NONE;
int pressed_key = KEY_NONE;
uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv, *fbuf_argb;
int obj_cnt;
bool dis_score = true;
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
    int valid_width = ai_args.valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = ai_args.valid_height;  // isp ds2 input height, should be the same with definition in video config
    char* fe_kmodel_path = ai_args.fe_kmodel_path;  // kmodel path
    int fe_net_len = ai_args.fe_net_len;  // kmodel input size is fe_net_len * fe_net_len
    int fe_num = ai_args.fe_num;  // kmodel output number
    int max_register_obj = ai_args.max_register_obj;  // max register    
    int valid_register_obj = 0;
    int out_loop_cnts = valid_register_obj;
    float thresh = ai_args.thresh;
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = valid_height * valid_width;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    gerecorg fsight(fe_net_len, fe_num, max_register_obj, thresh);
    fsight.load_model(fe_kmodel_path);  // load kmodel
	fsight.prepare_memory();  // memory allocation
    
    /****fixed operation for video operation****/
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    // video setting
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, valid_width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, valid_height);
    // RRRRRR....GGGGGGG....BBBBBB, CHW
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_RGB24);
    mtx.unlock();


    int frame_cnt = 0;

    // define cv::Mat for isp input
    uint8_t *p_src = new uint8_t[valid_height * valid_width * 3];
    cv::Mat rgb24_img_for_ai(valid_height, valid_width, CV_8UC3, p_src); 
    cv::Mat ori_img_R = cv::Mat(valid_height, valid_width, CV_8UC1, p_src);
    cv::Mat ori_img_G = cv::Mat(valid_height, valid_width, CV_8UC1, p_src + offset_channel);
    cv::Mat ori_img_B = cv::Mat(valid_height, valid_width, CV_8UC1, p_src + offset_channel * 2);
    // define cv::Mat for kmodel input
    cv::Mat fe_img_R = cv::Mat(fe_net_len, fe_net_len, CV_8UC1, fsight.virtual_addr_input[0]);
    cv::Mat fe_img_G = cv::Mat(fe_net_len, fe_net_len, CV_8UC1, fsight.virtual_addr_input[0] + fe_net_len * fe_net_len);
    cv::Mat fe_img_B = cv::Mat(fe_net_len, fe_net_len, CV_8UC1, fsight.virtual_addr_input[0] + fe_net_len * fe_net_len * 2);
    cv::Mat cropped_R;
    cv::Mat cropped_G;
    cv::Mat cropped_B;
    // key_init();
    bool enter_recorg = false;
    int cls_cnt = 0;
    int train_cnt = 0;
    while(quit.load()) 
    {
        bool ret = false;
        bool is_show = false;
        ScopedTiming st("total", 0);
        mtx.lock();
        ret = capture.read(rgb24_img_for_ai);
        mtx.unlock();
        if(ret == false)
        {
            quit.store(false);
            continue; // 
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
        
        fsight.set_input(0);
        fsight.set_output();

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
            for (int i=0; i<1; i++)
            {
                struct vo_draw_frame frame;
                frame.crtc_id = drm_dev.crtc_id;
                frame.draw_en = 1;
                frame.frame_num = obj_cnt;
                int x1 = DRM_INPUT_WIDTH / 2  + ((1 - 2 * MARGIN) * DRM_INPUT_HEIGHT) / 2;
				int x0 = DRM_INPUT_WIDTH / 2  - ((1 - 2 * MARGIN) * DRM_INPUT_HEIGHT) / 2;
				int y0 = (MARGIN) * DRM_INPUT_HEIGHT;
				int y1 = (1 - MARGIN) * DRM_INPUT_HEIGHT;
				x1 = std::max(0, std::min(x1, DRM_INPUT_WIDTH));
				x0 = std::max(0, std::min(x0, DRM_INPUT_WIDTH));
				y0 = std::max(0, std::min(y0, DRM_INPUT_HEIGHT));
				y1 = std::max(0, std::min(y1, DRM_INPUT_HEIGHT));
				frame.line_x_start = x0;
				frame.line_x_end = x1;
				frame.line_y_start = y0 + DRM_OFFSET_HEIGHT;
				frame.line_y_end = y1 + DRM_OFFSET_HEIGHT;
                draw_frame(&frame);
                {
                    ScopedTiming st("fe process", enable_profile);
                    cropped_R = fsight.crop_image(ori_img_R);
                    cv::resize(cropped_R, fe_img_R, cv::Size(fe_net_len, fe_net_len), cv::INTER_AREA);
                    cropped_G = fsight.crop_image(ori_img_G);
                    cv::resize(cropped_G, fe_img_G, cv::Size(fe_net_len, fe_net_len), cv::INTER_AREA);
                    cropped_B = fsight.crop_image(ori_img_B);
                    cv::resize(cropped_B, fe_img_B, cv::Size(fe_net_len, fe_net_len), cv::INTER_AREA);  
                }           
                {
                    ScopedTiming st("fe run", enable_profile);
                    fsight.run();
                }             
                float* insight_fe = reinterpret_cast<float *>(fsight.virtual_addr_output);
                uint32_t score_index = 0;
			    float score_max = 0;
                std::string cls_name;
                int first_time_to_remind_out = 0;
                while(1)
                {                
                    pressed_key = key_values;
                    if(pressed_key == KEY_NONE)
                    {
                        break;
                    }
                    if(pressed_key == KEY_NEXT)
                    {        
                        key_values = 0;                                
                        enter_recorg = false;
                        int first_time_to_remind_in = 0;
                        while(1)
                        {
                            pressed_key = key_values;
                            if(pressed_key == KEY_NEXT)
                            {
                                std::cout << "Pressed UP button!" << std::endl;
                                int valid_index = valid_register_obj % max_register_obj;
                                memcpy(fsight.embs + valid_index * fe_num, insight_fe, sizeof(float) * fe_num);
                                cls_name = "class_" + std::to_string(cls_cnt);
                                train_cnt += 1;
                                std::cout << cls_name << " : "  << train_cnt << std::endl;
                                fsight.names.push_back(cls_name);
                                valid_register_obj += 1;  
                                break;
                            }
                            else if(pressed_key == KEY_OK)
                            {
                                std::cout << "Pressed DOWN button!" << std::endl;
                                cls_cnt += 1;
                                train_cnt = 0;
                                cls_name = "class_" + std::to_string(cls_cnt);
                                std::cout << "switch to " << cls_name << std::endl;
                                break;
                            }
                            else
                            {
                                if(first_time_to_remind_in == 0)
                                {
                                    first_time_to_remind_in = 1;
                                    std::cout << "Please press UP or DOWN button, UP: confirm, DOWN: switch!" << std::endl;
                                }
                                
                            }
                            
                        }
                        key_values = 0;
                        pressed_key = 0;
                    }
                    else if (pressed_key == KEY_OK)
                    {
                        std::cout << "Pressed DOWN button!" << std::endl;
                        std::cout << "Enter recog!" << std::endl;
                        pressed_key = 0;
                        key_values = 0;
                        enter_recorg = true; 
                        break; 
                    }
                    else
                    {
                        if(first_time_to_remind_out == 0 && !enter_recorg)
                        {
                            first_time_to_remind_out = 1;
                            std::cout << "Please press UP or DOWN button, UP: record, DOWN: reocg!" << std::endl;
                        }
                    }
                    if(enter_recorg)
                    {
                        break;
                    }
                } 
                if(enter_recorg)
                {  
                    out_loop_cnts = valid_register_obj >= max_register_obj ? max_register_obj : valid_register_obj;          
                    score_index = fsight.calulate_score(insight_fe, fsight.embs, out_loop_cnts, &score_max);
                    if(score_max >= thresh)
                    {
                        // std::string text = std::to_string(score_index) + ":" + std::to_string(round(score_max * 100) / 100.0);
                        std::string text = fsight.names[valid_register_obj / max_register_obj * max_register_obj + score_index] + ":" + std::to_string(round(score_max * 100) / 100.0).substr(0,4);
                        int x0 = std::max(0, std::min(int(MARGIN * DRM_INPUT_WIDTH), DRM_INPUT_WIDTH));
                        int y0 = std::max(0, std::min(int(MARGIN * DRM_INPUT_HEIGHT) + 60, DRM_INPUT_HEIGHT));
                        cv::putText(img_argb, text, cv::Point(x0, y0), cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(255, 0, 0, 255), 2, 8, 0);
                    }
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
                    resized_imgparts.push_back(fe_img_B);
                    resized_imgparts.push_back(fe_img_G);          
                    resized_imgparts.push_back(fe_img_R);
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
        dis_score = true;
    }
    delete[] p_src;
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
    system("killall -9 self_learning");
    mtx.unlock();
}
void Get_KeyValue(void)
{
    int key_val = 0;
    while(quit.load())
    {
        key_val = key_get();
        if(key_val != 0)
        {          
            key_values = key_val;
        }        
    }
}
int main(int argc, char *argv[])
{
    std::cout << "case " << argv[0] << " build " << __DATE__ << " " << __TIME__ << std::endl;
    if (argc < 12)
    {
        std::cerr << "Usage: " << argv[0] << " <valid_width> <valid_height> <fe_kmodel> <fe_net_len> <fe_num> <max_register_obj> <thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
        return -1;
    }
    // parse args for ai worker
    ai_worker_args ai_args;
    ai_args.valid_width = atoi(argv[1]);
    ai_args.valid_height = atoi(argv[2]);
    ai_args.fe_kmodel_path = argv[3];
    ai_args.fe_net_len = atoi(argv[4]);
    ai_args.fe_num = atoi(argv[5]);
    ai_args.max_register_obj = atoi(argv[6]);
    ai_args.thresh = atof(argv[7]);
    char* video_cfg_file = argv[8];
    ai_args.is_rgb = atoi(argv[9]);
    ai_args.enable_profile = atoi(argv[10]);
    int enable_profile = atoi(argv[10]);
    ai_args.dump_img_dir = argv[11];

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
    std::thread thread_key(Get_KeyValue);

    thread_ds0.join();
    thread_ds2.join();
    // thread_key.join();
    thread_key.detach();
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
