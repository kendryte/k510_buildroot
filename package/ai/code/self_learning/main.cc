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
#include "v4l2.h"


#include "gerecorg.h"
#include "cv2_utils.h"
#include "key.h"
#include "hal_key.h"
#include "buf_mgt.h"
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
using namespace rapidjson;

#define SELECT_TIMEOUT		2000

struct video_info dev_info[2];
std::mutex mtx;
std::mutex mtx_key;
volatile int key_values = KEY_NONE;
int pressed_key = KEY_NONE;
uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv;
int obj_cnt;
std::vector<cv::Point> points_to_clear[DRM_BUFFERS_COUNT];
std::vector<std::string> strs_to_clear[DRM_BUFFERS_COUNT];

#define AUTO_ADAPT_CONFIG_FILE "auto.conf"
static uint32_t screen_width, screen_height;
static uint32_t gnne_input_width, gnne_input_height;
static uint32_t gnne_valid_width, gnne_valid_height;
static char *video_cfg_file;
static buf_mgt_t buf_mgt;

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
    int valid_width = gnne_valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = gnne_valid_height;  // isp ds2 input height, should be the same with definition in video config
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
        uint64_t index;
        {
            buf_mgt_writer_get(&buf_mgt, (void **)&index);
            ScopedTiming st("display clear", enable_profile);
            struct drm_buffer *fbuf_argb = &drm_dev.drm_bufs_argb[index];
            img_argb = cv::Mat(screen_height, screen_width, CV_8UC4, (uint8_t *)fbuf_argb->map);

            for (uint32_t cc = 0; cc < points_to_clear[index].size(); cc++)
            {          
                cv::putText(img_argb, strs_to_clear[index][cc], points_to_clear[index][cc], cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 0, 0, 0), 2, 8, 0);
            }
        }

        {
            ScopedTiming st("draw osd", enable_profile);
            obj_cnt = 0;
            points_to_clear[index].clear();
            strs_to_clear[index].clear();
            for (int i=0; i<1; i++)
            {
                struct vo_draw_frame frame;
                frame.crtc_id = drm_dev.crtc_id;
                frame.draw_en = 1;
                frame.frame_num = obj_cnt;
                int x1 = (1 - MARGIN) * screen_width;
				int x0 = (MARGIN) * screen_width;
				int y0 = screen_height / 2  - ((1 - 2 * MARGIN) * screen_width) / 2;
				int y1 = screen_height / 2  + ((1 - 2 * MARGIN) * screen_width) / 2;
				x1 = std::max(0, std::min(x1, (int)screen_width));
				x0 = std::max(0, std::min(x0, (int)screen_width));
				y0 = std::max(0, std::min(y0, (int)screen_height));
				y1 = std::max(0, std::min(y1, (int)screen_height));
				frame.line_x_start = x0;
				frame.line_x_end = x1;
				frame.line_y_start = y0;
				frame.line_y_end = y1;
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
                        int x0 = std::max(0, std::min(int(MARGIN * screen_width), (int)screen_width));
                        int y0 = std::max(0, std::min(int(MARGIN * screen_height) + 60, (int)screen_height));
                        cv::putText(img_argb, text, cv::Point(x0, y0), cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(255, 0, 0, 255), 2, 8, 0);
                        points_to_clear[index].push_back(cv::Point(x0, y0));
                        strs_to_clear[index].push_back(text);
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
            for (uint32_t i = obj_cnt; i < 32; i++) {
                struct vo_draw_frame frame;
                frame.crtc_id = drm_dev.crtc_id;
                frame.draw_en = 0;
                frame.frame_num = i;
                draw_frame(&frame);
            }
        }
        frame_cnt += 1;
        buf_mgt_writer_put(&buf_mgt, (void *)index);
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

static int video_stop(struct v4l2_device *vdev)
{
	int ret;

	ret = v4l2_stream_off(vdev);
	if (ret < 0) {
		printf("error: failed to stop video stream: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	return 0;
}

static void video_cleanup(struct v4l2_device *vdev)
{
	if (vdev) {
		v4l2_free_buffers(vdev);
		v4l2_close(vdev);
	}
}

static int process_ds0_image(struct v4l2_device *vdev,unsigned int width,unsigned int height)
{
	struct v4l2_video_buffer buffer;
	int ret;
    static struct v4l2_video_buffer old_buffer;
    static int screen_init_flag = 0;

    mtx.lock();
	ret = v4l2_dequeue_buffer(vdev, &buffer);
	if (ret < 0) {
		printf("error: unable to dequeue buffer: %s (%d)\n",
			strerror(-ret), ret);
        mtx.unlock();
		return ret;
	}
    mtx.unlock();
	if (buffer.error) {
		printf("warning: error in dequeued buffer, skipping\n");
		return 0;
	}

    fbuf_yuv = &drm_dev.drm_bufs[buffer.index];

    if (drm_dev.req)
        drm_wait_vsync();
    uint64_t index;
    if (buf_mgt_display_get(&buf_mgt, (void **)&index) != 0)
        index = 0;
    struct drm_buffer *fbuf_argb = &drm_dev.drm_bufs_argb[index];
    if (drm_dmabuf_set_plane(fbuf_yuv, fbuf_argb)) {
        std::cerr << "Flush fail \n";
        return 1;
    }

    if(screen_init_flag) {
        fbuf_yuv = &drm_dev.drm_bufs[old_buffer.index];
        old_buffer.mem = fbuf_yuv->map;
        old_buffer.size = fbuf_yuv->size;
        mtx.lock();
        ret = v4l2_queue_buffer(vdev, &old_buffer);
        if (ret < 0) {
            printf("error: unable to requeue buffer: %s (%d)\n",
                strerror(-ret), ret);
            mtx.unlock();
            return ret;
        }
        mtx.unlock();
    }
    else {
        screen_init_flag = 1;
    }

    old_buffer = buffer;

	return 0;
}


void display_worker(int enable_profile)
{
    int ret;
    struct v4l2_device *vdev;
    struct v4l2_pix_format format;
    fd_set fds;
    struct v4l2_video_buffer buffer;
	unsigned int i;

    mtx.lock();
    vdev = v4l2_open(dev_info[0].video_name[1]);
    if (vdev == NULL) {
		printf("error: unable to open video capture device %s\n",
			dev_info[0].video_name[1]);
        mtx.unlock();
		goto display_cleanup;
	}

	memset(&format, 0, sizeof format);
	format.pixelformat = dev_info[0].video_out_format[1] ? V4L2_PIX_FMT_NV12 : V4L2_PIX_FMT_NV16;
	format.width = dev_info[0].video_width[1];
	format.height = dev_info[0].video_height[1];

	ret = v4l2_set_format(vdev, &format);
	if (ret < 0)
	{
		printf("%s:v4l2_set_format error\n",__func__);
        mtx.unlock();
		goto display_cleanup;
	}

	ret = v4l2_alloc_buffers(vdev, V4L2_MEMORY_USERPTR, DRM_BUFFERS_COUNT);
	if (ret < 0)
	{
		printf("%s:v4l2_alloc_buffers error\n",__func__);
        mtx.unlock();
		goto display_cleanup;
	}

	FD_ZERO(&fds);
	FD_SET(vdev->fd, &fds);

	for (i = 0; i < vdev->nbufs; ++i) {
		buffer.index = i;
        fbuf_yuv = &drm_dev.drm_bufs[buffer.index];
        buffer.mem = fbuf_yuv->map;
        buffer.size = fbuf_yuv->size;

		ret = v4l2_queue_buffer(vdev, &buffer);
		if (ret < 0) {
			printf("error: unable to queue buffer %u\n", i);
            mtx.unlock();
			goto display_cleanup;
		}	
	}

	ret = v4l2_stream_on(vdev);
	if (ret < 0) {
		printf("%s error: failed to start video stream: %s (%d)\n", __func__,
			strerror(-ret), ret);
        mtx.unlock();
		goto display_cleanup;
	}
    mtx.unlock();

    while(quit.load()) {
		struct timeval timeout;
		fd_set rfds;

		timeout.tv_sec = SELECT_TIMEOUT / 1000;
		timeout.tv_usec = (SELECT_TIMEOUT % 1000) * 1000;
		rfds = fds;

		ret = select(vdev->fd + 1, &rfds, NULL, NULL, &timeout);
		if (ret < 0) {
			if (errno == EINTR)
				continue;

			printf("error: select failed with %d\n", errno);
			goto display_cleanup;
		}
		if (ret == 0) {
			printf("error: select timeout\n");
			goto display_cleanup;
		}
        process_ds0_image(vdev, format.width, format.height);
    }

display_cleanup:
    mtx.lock();
    video_stop(vdev);
	video_cleanup(vdev);
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

int video_resolution_adaptation(void)
{
    // open input file
    FILE *fp = fopen(video_cfg_file, "rb");
    if (fp == NULL) {
        printf("open %s file error\n", video_cfg_file);
        return -1;
    }
    // parse
    char buff[4096];
    FileReadStream frs(fp, buff, sizeof(buff));
    Document root;
    root.ParseStream(frs);
    fclose(fp);
    if (root.HasParseError()) {
        printf("parse file error\n");
        return -1;
    }
    // default disable all
    Pointer("/sensor0/~1dev~1video2/video2_used").Set(root, 0);
    Pointer("/sensor0/~1dev~1video3/video3_used").Set(root, 1);
    Pointer("/sensor0/~1dev~1video4/video4_used").Set(root, 0);
    Pointer("/sensor0/~1dev~1video5/video5_used").Set(root, 1);
    Pointer("/sensor1/~1dev~1video6/video6_used").Set(root, 0);
    Pointer("/sensor1/~1dev~1video7/video7_used").Set(root, 0);
    Pointer("/sensor1/~1dev~1video8/video8_used").Set(root, 0);
    Pointer("/sensor1/~1dev~1video9/video9_used").Set(root, 0);

    char *sensor0_cfg_file = NULL;
    uint32_t sensor0_total_width;
    uint32_t sensor0_total_height;
    uint32_t sensor0_active_width;
    uint32_t sensor0_active_height;
    uint32_t video3_width;
    uint32_t video3_height;
    uint32_t video5_width;
    uint32_t video5_height;

#define SENSOR_1920x1080_TIMING(x) \
    do {\
        sensor0_total_width = 3476;\
        sensor0_total_height = 1166;\
        sensor0_active_width = 1920;\
        sensor0_active_height = 1080;\
    } while(0)

#define SENSOR_1080x1920_TIMING(x) \
    do {\
        sensor0_total_width = 3453;\
        sensor0_total_height = 1979;\
        sensor0_active_width = 1088;\
        sensor0_active_height = 1920;\
    } while(0)

    if (screen_width == 1920 && screen_height == 1080) {
        sensor0_cfg_file = "imx219_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 640;
        video5_height = 480;
    } else if (screen_width == 1080 && screen_height == 1920) {
        sensor0_cfg_file = "imx219_1080x1920_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 480;
        video5_height = 640;
    } else if (screen_width == 1280 && screen_height == 720) {
        sensor0_cfg_file = "imx219_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 640;
        video5_height = 480;
    } else {
        return -1;
    }
    // update video config
    gnne_input_width = video5_width;
    gnne_input_height = video5_height;
    gnne_valid_width = video5_width;
    gnne_valid_height = video5_height;
    if (strcmp(sensor0_cfg_file, "imx219_0.conf") == 0)
        SENSOR_1920x1080_TIMING(0);
    else if (strcmp(sensor0_cfg_file, "imx219_1080x1920_0.conf") == 0)
        SENSOR_1080x1920_TIMING(0);
    else
        return -1;
    Pointer("/sensor0/sensor0_total_size/sensor0_total_width").Set(root, sensor0_total_width);
    Pointer("/sensor0/sensor0_total_size/sensor0_total_height").Set(root, sensor0_total_height);
    Pointer("/sensor0/sensor0_active_size/sensor0_active_width").Set(root, sensor0_active_width);
    Pointer("/sensor0/sensor0_active_size/sensor0_active_height").Set(root, sensor0_active_height);
    Pointer("/sensor0/~1dev~1video2/video2_width").Set(root, sensor0_active_width);
    Pointer("/sensor0/~1dev~1video2/video2_height").Set(root, sensor0_active_height);
    Pointer("/sensor0/~1dev~1video2/video2_out_format").Set(root, 1);
    Pointer("/sensor0/~1dev~1video3/video3_width").Set(root, video3_width);
    Pointer("/sensor0/~1dev~1video3/video3_height").Set(root, video3_height);
    Pointer("/sensor0/~1dev~1video3/video3_out_format").Set(root, 1);
    Pointer("/sensor0/~1dev~1video5/video5_width").Set(root, video5_width);
    Pointer("/sensor0/~1dev~1video5/video5_height").Set(root, gnne_input_height);
    Pointer("/sensor0/~1dev~1video5/video5_pitch").Set(root, gnne_input_width);
    Pointer("/sensor0/~1dev~1video5/video5_height_r").Set(root, video5_height);
    Pointer("/sensor0/~1dev~1video5/video5_out_format").Set(root, 0);
    // create output file
    video_cfg_file = AUTO_ADAPT_CONFIG_FILE;
    fp = fopen(video_cfg_file, "wb");
    if (fp == NULL) {
        printf("open %s file error\n", video_cfg_file);
        return -1;
    }
    // generate
    FileWriteStream fws(fp, buff, sizeof(buff));
    Writer<FileWriteStream> writer(fws);
    root.Accept(writer);
    fclose(fp);

    return 0;
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
    video_cfg_file = argv[8];
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

    // get screen resolution
    if (drm_get_resolution(NULL, &screen_width, &screen_height) < 0) {
        printf("get resolution error!\n");
        return -1;
    }
    printf("screen resolution: %dx%d\n", screen_width, screen_height);
    if (video_resolution_adaptation() < 0) {
        printf("resolution not support!\n");
        return -1;
    }

    for (uint32_t i = 0; i < DRM_BUFFERS_COUNT; i++)
        buf_mgt_reader_put(&buf_mgt, (void *)i);

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
