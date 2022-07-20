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
#include <fcntl.h>
#include <termios.h>
#include "v4l2.h"

#include "retinaface.h"
#include "insightface.h"
#include "key.h"
#include "cv2_utils.h"
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
std::mutex key_mtx;
int key_values = KEY_NONE;
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
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
void ai_worker(ai_worker_args ai_args)
{
    // parse ai worker agrs
    char* fd_kmodel_path = ai_args.fd_kmodel_path;  // face detection kmodel path
    int fd_net_len = gnne_input_width;  // face detection kmodel input size is fd_net_len * fd_net_len
    int valid_width = gnne_valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = gnne_valid_height;  // isp ds2 input height, should be the same with definition in video config
    float obj_thresh = ai_args.obj_thresh;  // face detection thresh
    float nms_thresh = ai_args.nms_thresh;  // face detection nms thresh
    char* fe_kmodel_path = ai_args.fe_kmodel_path;  // face recognization kmodel path
    int fe_net_len = ai_args.fe_net_len;  // face recognization kmodel input size is fe_net_len * fe_net_len
    int fe_num = ai_args.fe_num;  // face recognization number
    int max_register_face  = ai_args.max_register_face;  // max register face number    
    int valid_register_face = 0;
    int out_loop_cnts = valid_register_face;
    float thresh = ai_args.thresh;  // face recognization thresh
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = fd_net_len * fd_net_len;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    retinaface rf(fd_net_len, obj_thresh, nms_thresh);
    rf.load_model(fd_kmodel_path);  // load kmodel
	rf.prepare_memory();  // memory allocation
    insightface fsight(fe_net_len, fe_num, max_register_face, thresh);
    fsight.load_model(fe_kmodel_path);  // load kmodel
	fsight.prepare_memory();  // memory allocation
    
    cv::Mat fe_img_R = cv::Mat(fe_net_len, fe_net_len, CV_8UC1, fsight.virtual_addr_input[0]);
    cv::Mat fe_img_G = cv::Mat(fe_net_len, fe_net_len, CV_8UC1, fsight.virtual_addr_input[0] + fe_net_len * fe_net_len);
    cv::Mat fe_img_B = cv::Mat(fe_net_len, fe_net_len, CV_8UC1, fsight.virtual_addr_input[0] + fe_net_len * fe_net_len * 2);
    
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
    cv::Mat ori_img_R = cv::Mat(fd_net_len, fd_net_len, CV_8UC1, rf.virtual_addr_input[0]);
    cv::Mat ori_img_G = cv::Mat(fd_net_len, fd_net_len, CV_8UC1, rf.virtual_addr_input[0] + fd_net_len * fd_net_len);
    cv::Mat ori_img_B = cv::Mat(fd_net_len, fd_net_len, CV_8UC1, rf.virtual_addr_input[0] + fd_net_len * fd_net_len * 2);
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
        //padding
        uint8_t *r_addr, *g_addr, *b_addr;
        g_addr = (uint8_t *)rf.virtual_addr_input[0] + offset_channel;
        r_addr = is_rgb ? g_addr - offset_channel : g_addr + offset_channel;
        b_addr = is_rgb ? g_addr + offset_channel : g_addr - offset_channel;
        if (gnne_valid_width < gnne_input_width) {
            uint32_t padding = gnne_input_width - gnne_valid_width;
            for (int row = 0; row < gnne_valid_height; row++) {
                uint32_t offset = row * gnne_input_width + gnne_valid_width;
                memset(r_addr + offset, PADDING_R, padding);
                memset(g_addr + offset, PADDING_G, padding);
                memset(b_addr + offset, PADDING_B, padding);
            }
        }
        if (gnne_valid_height < gnne_input_height) {
            uint32_t padding = (gnne_input_height - gnne_valid_height) * gnne_input_width;
            uint32_t offset = gnne_valid_height * gnne_input_width;
            memset(r_addr + offset, PADDING_R, padding);
            memset(g_addr + offset, PADDING_G, padding);
            memset(b_addr + offset, PADDING_B, padding);
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
        fsight.set_input(0);
        fsight.set_output();

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
        uint64_t index;
        {
            buf_mgt_writer_get(&buf_mgt, (void **)&index);
            ScopedTiming st("display clear", enable_profile);
            struct drm_buffer *fbuf_argb = &drm_dev.drm_bufs_argb[index];
            img_argb = cv::Mat(screen_height, screen_width, CV_8UC4, (uint8_t *)fbuf_argb->map);

            for (uint32_t cc = 0; cc < points_to_clear[index].size(); cc++)
            {          
                cv::putText(img_argb, strs_to_clear[index][cc], points_to_clear[index][cc], cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 0, 0), 2, 8, 0);
            }
        }
        
        {
            ScopedTiming st("run face recognization and draw osd", enable_profile);
            obj_cnt = 0;
            points_to_clear[index].clear();
            strs_to_clear[index].clear();
            for (auto l : valid_landmarks)
            {   
                {
                    ScopedTiming st("fe process", enable_profile);
                    fsight.get_affine_matrix(l, ori_img_R, valid_width, valid_height);
                    fsight.affine_image(ori_img_R, fe_img_R);
                    fsight.affine_image(ori_img_G, fe_img_G);
                    fsight.affine_image(ori_img_B, fe_img_B);
                }           
                {
                    ScopedTiming st("fe run", enable_profile);
                    fsight.run();
                }             
                float *insight_fe = reinterpret_cast<float *>(fsight.virtual_addr_output);    
                uint32_t score_index = 0;
			    float score_max = 0;
                {
                    ScopedTiming st("fe post process", enable_profile);
                    if(out_loop_cnts >= max_register_face)
                    {
                        out_loop_cnts = max_register_face;
                    }
                    else
                    {
                        out_loop_cnts = valid_register_face;
                    }

                    pressed_key = key_values;

                    if(pressed_key == KEY_NEXT)
                    { 
                        std::cout << "Please Enter Your Name to Register: " << std::endl;
                        int valid_index = valid_register_face % max_register_face;
                        memcpy(fsight.embs + valid_index * fe_num, insight_fe, sizeof(float) * fe_num);
                        std::string name;
                        getline(std::cin, name);
                        fsight.names.push_back(name);
                        valid_register_face += 1;
                        key_values = 0;
                    }
                    else if (pressed_key == KEY_OK)
                    {
                        std::cout << "clearing..." << std::endl;
                        fsight.names.clear();
                        valid_register_face = 0;
                        out_loop_cnts = valid_register_face;
                        std::cout << "clear Done!" << std::endl;
                        key_values = 0;
                    }                
                    score_index = fsight.calulate_score(insight_fe, fsight.embs, out_loop_cnts, &score_max);
                }                
                      
                if (obj_cnt < 32)
                {
                    box_t b = valid_box[obj_cnt];   
                    struct vo_draw_frame frame;
                    frame.crtc_id = drm_dev.crtc_id;
                    frame.draw_en = 1;
                    frame.frame_num = obj_cnt;                    
                    int x1 = (b.x + b.w / 2) * screen_width * fd_net_len / valid_width;
                    int x0 = (b.x - b.w / 2) * screen_width * fd_net_len / valid_width;
                    int y0 = (b.y - b.h / 2) * screen_height * fd_net_len / valid_height;
                    int y1 = (b.y + b.h / 2) * screen_height * fd_net_len / valid_height;
                    x1 = std::max(0, std::min(x1, (int)screen_width));
                    x0 = std::max(0, std::min(x0, (int)screen_width));
                    y0 = std::max(0, std::min(y0, (int)screen_height));
                    y1 = std::max(0, std::min(y1, (int)screen_height));
                    frame.line_x_start = x0;
                    frame.line_x_end = x1;
                    frame.line_y_start = y0;
                    frame.line_y_end = y1;
                    draw_frame(&frame);

                    if(score_max >= thresh)
                    {
                        // std::string text = std::to_string(score_index) + ":" + std::to_string(round(score_max * 100) / 100.0);
                        std::string text = fsight.names[valid_register_face / max_register_face * max_register_face + score_index] + ":" + std::to_string(round(score_max * 100) / 100.0).substr(0,4);
                        int x0 = std::max(0, std::min(int((b.x - b.w / 2) * fd_net_len / valid_width * screen_width), (int)screen_width));
                        int y0 = std::max(0, std::min(int((b.y - b.h / 2) * fd_net_len / valid_height * screen_height) + 60, (int)screen_height));
                        cv::putText(img_argb, text, cv::Point(x0, y0), cv::FONT_HERSHEY_COMPLEX, 2, cv::Scalar(255, 0, 0, 255), 2, 8, 0);
                        points_to_clear[index].push_back(cv::Point(x0, y0));
                        strs_to_clear[index].push_back(text);
                    }         
                }
                if(enable_dump_image)
                {
                    std::vector<cv::Mat>affined_imgparts(3);
                    affined_imgparts.clear();
                    affined_imgparts.push_back(fe_img_B);
                    affined_imgparts.push_back(fe_img_G);
                    affined_imgparts.push_back(fe_img_R); 
                    cv::Mat affined_img;
                    cv::merge(affined_imgparts, affined_img);
                    std::string affined_img_out_path = dump_img_dir + "/affined_" + std::to_string(frame_cnt) + "_" + std::to_string(obj_cnt) + ".jpg";
                    cv::imwrite(affined_img_out_path, affined_img); 
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
    system("killall -9 face_recog");
    mtx.unlock();
}

void Get_KeyValue(void)
{
    while(quit.load())
    {
        key_values = key_get();
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
        video5_width = 320;
        video5_height = 240;
    } else if (screen_width == 1080 && screen_height == 1920) {
        sensor0_cfg_file = "imx219_1080x1920_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 240;
        video5_height = 320;
    } else if (screen_width == 1280 && screen_height == 720) {
        sensor0_cfg_file = "imx219_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 320;
        video5_height = 240;
    } else {
        return -1;
    }
    // update video config
    gnne_input_width = 320;
    gnne_input_height = 320;
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
    if (argc < 16)
    {
        std::cerr << "Usage: " << argv[0] << " <fd_kmodel> <fd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <fe_kmodel> <fe_net_len> <fe_num> <max_register_face> <thresh> <video_config> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
        return -1;
    }
    // parse args for ai worker
    ai_worker_args ai_args;
    ai_args.fd_kmodel_path = argv[1];
    ai_args.fd_net_len = atoi(argv[2]);
    ai_args.valid_width = atoi(argv[3]);
    ai_args.valid_height = atoi(argv[4]);
    ai_args.obj_thresh = atof(argv[5]);
    ai_args.nms_thresh = atof(argv[6]);
    ai_args.fe_kmodel_path = argv[7];
    ai_args.fe_net_len = atoi(argv[8]);
    ai_args.fe_num = atoi(argv[9]);
    ai_args.max_register_face = atoi(argv[10]);
    ai_args.thresh = atof(argv[11]);
    video_cfg_file = argv[12];
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
    thread_key.join();

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
