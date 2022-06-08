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


#include "retinaface.h"
#include "pfld.h"
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
    char* fd_kmodel_path = ai_args.fd_kmodel_path;  // face detection kmodel path
    int fd_net_len = ai_args.fd_net_len;  // face detection kmodel input size is fd_net_len * fd_net_len
    int valid_width = ai_args.valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = ai_args.valid_height;  // isp ds2 input height, should be the same with definition in video config
    float obj_thresh = ai_args.obj_thresh;  // face detection thresh
    float nms_thresh = ai_args.nms_thresh;  // face detection nms thresh
    char* fk_kmodel_path = ai_args.fk_kmodel_path;  // face landmarks kmodel path
    int fk_net_len = ai_args.fk_net_len;  // face landmarks kmodel input size is fk_net_len * fk_net_len
    int fk_num = ai_args.fk_num;  // face landmarks number, now 106
    float nme_thresh = ai_args.nme_thresh;  // face landmarks nme thresh
    int max_loop = ai_args.max_loop;  // face landmarks max loop times for one frame
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = valid_width * valid_width;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    retinaface rf(fd_net_len, obj_thresh, nms_thresh);
    rf.load_model(fd_kmodel_path);  // load kmodel
	rf.prepare_memory();  // memory allocation
    pfld fld(fk_net_len, fk_num);
    fld.load_model(fk_kmodel_path);  // load kmodel
    fld.prepare_memory();  // memory allocation
    float *lst_landmarks = new float[2 * fk_num];
    float *cur_landmarks;
    cv::Mat cropped_R;
    cv::Mat cropped_G;
    cv::Mat cropped_B;
    box_t cropped_box;
    cv::Mat fk_img_R = cv::Mat(fk_net_len, fk_net_len, CV_8UC1, fld.virtual_addr_input[0]);
    cv::Mat fk_img_G = cv::Mat(fk_net_len, fk_net_len, CV_8UC1, fld.virtual_addr_input[0] + fk_net_len * fk_net_len);
    cv::Mat fk_img_B = cv::Mat(fk_net_len, fk_net_len, CV_8UC1, fld.virtual_addr_input[0] + fk_net_len * fk_net_len * 2);
    
    /****fixed operation for video operation****/
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    // video setting
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, fd_net_len);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, fd_net_len);
    // RRRRRR....GGGGGGG....BBBBBB, CHW
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_RGB24);
    mtx.unlock();


    int frame_cnt = 0;

    // define cv::Mat for ai input
    // padding offset is 0, padding is at last
    cv::Mat rgb24_img_for_ai(fd_net_len, fd_net_len, CV_8UC3, rf.virtual_addr_input[0]);
    // define cv::Mat for post process
    cv::Mat ori_img_R = cv::Mat(valid_height, valid_width, CV_8UC1, rf.virtual_addr_input[0]);
    cv::Mat ori_img_G = cv::Mat(valid_height, valid_width, CV_8UC1, rf.virtual_addr_input[0] + valid_width * valid_width);
    cv::Mat ori_img_B = cv::Mat(valid_height, valid_width, CV_8UC1, rf.virtual_addr_input[0] + valid_width * valid_width * 2);
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
            memset(rf.virtual_addr_input[0] + (valid_height * valid_width), PADDING_R, (valid_width - valid_height) * valid_width);
            // G
            memset(rf.virtual_addr_input[0] + offset_channel + (valid_height * valid_width), PADDING_G, (valid_width - valid_height) * valid_width);
            // B
            memset(rf.virtual_addr_input[0] + offset_channel * 2 + (valid_height * valid_width), PADDING_B, (valid_width - valid_height) * valid_width);
        }
        else
        { 
            // B
            memset(rf.virtual_addr_input[0] + (valid_height * valid_width), PADDING_B, (valid_width - valid_height) * valid_width);
            // G
            memset(rf.virtual_addr_input[0] + offset_channel + (valid_height * valid_width), PADDING_G, (valid_width - valid_height) * valid_width);
            // R
            memset(rf.virtual_addr_input[0] + offset_channel * 2 + (valid_height * valid_width), PADDING_R, (valid_width - valid_height) * valid_width);
        
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
        
        rf.set_input(0);
        rf.set_output();
        fld.set_input(0);
        fld.set_output();

        {
            ScopedTiming st("fd run", enable_profile);
            rf.run();
        }
        
        {
            ScopedTiming st("post process", enable_profile);
            rf.post_process();
        }

        std::vector<box_t> valid_box;
        std::vector<landmarks_t> valid_landmarks;
        {
            ScopedTiming st("get final box", enable_profile);
            rf.get_final_box(valid_box, valid_landmarks);
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
            ScopedTiming st("run face landmark and draw osd", enable_profile);
            obj_cnt = 0;
            for (auto b : valid_box)
            {
                cropped_box = get_enlarged_box(b, valid_width, valid_height, ori_img_R);
                {
                    ScopedTiming st("fk process", enable_profile);
                    fld.set_valid_box(cropped_box, ori_img_R);
                }
                cropped_R = fld.crop_image(ori_img_R);
                cv::resize(cropped_R, fk_img_R, cv::Size(fk_net_len, fk_net_len), cv::INTER_AREA);
                cropped_G = fld.crop_image(ori_img_G);
                cv::resize(cropped_G, fk_img_G, cv::Size(fk_net_len, fk_net_len), cv::INTER_AREA);
                cropped_B = fld.crop_image(ori_img_B);
                cv::resize(cropped_B, fk_img_B, cv::Size(fk_net_len, fk_net_len), cv::INTER_AREA);              
                {
                    ScopedTiming st("fk run", enable_profile);
                    fld.run();
                }
                cur_landmarks = reinterpret_cast<float *>(fld.virtual_addr_output);
                for(uint32_t kk = 0; kk < fk_num; kk++)
                {
                    lst_landmarks[2 * kk + 0] = -1 * cur_landmarks[2 * kk + 0];
                    lst_landmarks[2 * kk + 1] = -1 * cur_landmarks[2 * kk + 1];
                }
                int cnt_landmarks = 0;
                float nme = fld.cal_erros(lst_landmarks, cur_landmarks);
                while(nme > nme_thresh && cnt_landmarks < max_loop)
                {
                    cnt_landmarks += 1;
                    cur_landmarks = reinterpret_cast<float *>(fld.virtual_addr_output);
                    memcpy(lst_landmarks, cur_landmarks, 2 * fk_num * sizeof(float));
                    cropped_box = get_box_from_landmarks(fld.valid_box, cur_landmarks, fk_num);
                    {
                        ScopedTiming st("fk process", enable_profile);
                        fld.set_valid_box(cropped_box, ori_img_R);
                    }
                    cropped_R = fld.crop_image(ori_img_R);
                    cv::resize(cropped_R, fk_img_R, cv::Size(fk_net_len, fk_net_len), cv::INTER_AREA);
                    cropped_G = fld.crop_image(ori_img_G);
                    cv::resize(cropped_G, fk_img_G, cv::Size(fk_net_len, fk_net_len), cv::INTER_AREA);
                    cropped_B = fld.crop_image(ori_img_B);
                    cv::resize(cropped_B, fk_img_B, cv::Size(fk_net_len, fk_net_len), cv::INTER_AREA);
                    {
                        ScopedTiming st("fk run", enable_profile);
                        fld.run();
                    }
                    cur_landmarks = reinterpret_cast<float *>(fld.virtual_addr_output);
                    nme = fld.cal_erros(lst_landmarks, cur_landmarks);                    
                }       
                cur_landmarks = reinterpret_cast<float *>(fld.virtual_addr_output);
                if (obj_cnt < 32)
                {
                    struct vo_draw_frame frame;
                    frame.crtc_id = drm_dev.crtc_id;
                    frame.draw_en = 1;
                    frame.frame_num = obj_cnt;
                    int x1 = (b.x + b.w / 2) * DRM_INPUT_WIDTH;
                    int x0 = (b.x - b.w / 2) * DRM_INPUT_WIDTH;
                    int y0 = (b.y - b.h / 2) * DRM_INPUT_HEIGHT * valid_width / valid_height;
                    int y1 = (b.y + b.h / 2) * DRM_INPUT_HEIGHT * valid_width / valid_height;
                    x1 = std::max(0, std::min(x1, DRM_INPUT_WIDTH));
                    x0 = std::max(0, std::min(x0, DRM_INPUT_WIDTH));
                    y0 = std::max(0, std::min(y0, DRM_INPUT_HEIGHT));
                    y1 = std::max(0, std::min(y1, DRM_INPUT_HEIGHT));
                    frame.line_x_start = x0;
                    frame.line_x_end = x1;
                    frame.line_y_start = y0 + DRM_OFFSET_HEIGHT;
                    frame.line_y_end = y1 + DRM_OFFSET_HEIGHT;
                    draw_frame(&frame);

                    landmarks_t l = valid_landmarks[obj_cnt];
                    for (uint32_t ll = 0; ll < 5; ll++)
                    {
                        int32_t x0 = l.points[2 * ll + 0] * DRM_INPUT_WIDTH;
                        int32_t y0 = l.points[2 * ll + 1] * valid_width / valid_height * DRM_INPUT_HEIGHT;
                        cv::circle(img_argb, cv::Point(x0, y0), 8, cv::Scalar(0, 0, 255, 255), -1);  
                    }

                    for (uint32_t ll = 0; ll < fk_num; ll++)
                    {                        
                        int32_t x0 = (cur_landmarks[2 * ll + 0] * fld.valid_box.w + fld.valid_box.x) / ori_img_R.cols * DRM_INPUT_WIDTH;
                        int32_t y0 = (cur_landmarks[2 * ll + 1] * fld.valid_box.h + fld.valid_box.y) / ori_img_R.rows * DRM_INPUT_HEIGHT;
                        cv::circle(img_argb, cv::Point(x0, y0), 4, cv::Scalar(255, 0, 0, 255), -1);
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
                    resized_imgparts.push_back(fk_img_B);
                    resized_imgparts.push_back(fk_img_G);          
                    resized_imgparts.push_back(fk_img_R);
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
    delete[] lst_landmarks;
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
        std::cerr << "Face landmarks by pfld Usage: " << argv[0] << " <fd_kmodel> <fd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <fk_kmodel> <fk_net_len> <fk_num> <nme_thresh> <max_loop> <video_config> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
        return -1;
    }
    // parse args for ai worker
    ai_worker_args ai_args;
    ai_args.fd_kmodel_path = argv[1];
    ai_args.fd_net_len = atoi(argv[2]);
    ai_args.valid_width = atoi(argv[3]);
    ai_args.valid_height = atoi(argv[4]);
    if(ai_args.valid_height > ai_args.valid_width)
    {
        std::cerr << "You should set width bigger than height" << std::endl;
                std::abort();
    }
    if(ai_args.valid_width != ai_args.fd_net_len)
    {
        std::cerr << "We won't resize image for gnne input, so valid_width should be equal to net_len" << std::endl;
                std::abort();
    }
    ai_args.obj_thresh = atof(argv[5]);
    ai_args.nms_thresh = atof(argv[6]);
    ai_args.fk_kmodel_path = argv[7];
    ai_args.fk_net_len = atoi(argv[8]);
    ai_args.fk_num = atoi(argv[9]);
    ai_args.nme_thresh = atof(argv[10]);
    ai_args.max_loop = atoi(argv[11]);
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
