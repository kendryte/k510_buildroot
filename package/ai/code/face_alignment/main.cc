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


#include "retinaface.h"
#include "pfld.h"
#include "tddfa.h"
#include "cv2_utils.h"
#include "constant.h"
#include "depth_estimated.h"
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
using namespace rapidjson;

#define SELECT_TIMEOUT		2000

struct video_info dev_info[2];
std::mutex mtx;
uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv;
int obj_cnt;

#define AUTO_ADAPT_CONFIG_FILE "auto.conf"
static uint32_t screen_width, screen_height;
static uint32_t gnne_input_width, gnne_input_height;
static uint32_t gnne_valid_width, gnne_valid_height;
static char *video_cfg_file;

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
    int fd_net_len = gnne_input_width;  // face detection kmodel input size is fd_net_len * fd_net_len
    int valid_width = gnne_valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = gnne_valid_height;  // isp ds2 input height, should be the same with definition in video config
    float obj_thresh = ai_args.obj_thresh;  // face detection thresh
    float nms_thresh = ai_args.nms_thresh;  // face detection nms thresh
    char* fk_kmodel_path = ai_args.fk_kmodel_path;  // face landmarks kmodel path
    int fk_net_len = ai_args.fk_net_len;  // face landmarks kmodel input size is fk_net_len * fk_net_len
    int fk_num = ai_args.fk_num;  // face landmarks number, now 106
    float nme_thresh = ai_args.nme_thresh;  // face landmarks nme thresh
    int max_loop = ai_args.max_loop;  // face landmarks max loop times for one frame
    char* fa_kmodel_path = ai_args.fa_kmodel_path;  // face alignment kmodel path
    int fa_net_len = ai_args.fa_net_len;  // face alignment kmodel input size is fa_net_len * fa_net_len
    int fa_num = ai_args.fa_num;  // face alignment number, now 62
    int depth_or_pncc = ai_args.depth_or_pncc;  // depth show or pncc show
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = fd_net_len * fd_net_len;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    retinaface rf(fd_net_len, obj_thresh, nms_thresh);
    rf.load_model(fd_kmodel_path);  // load kmodel
	rf.prepare_memory();  // memory allocation
    pfld fld(fk_net_len, fk_num);
    fld.load_model(fk_kmodel_path);  // load kmodel
    fld.prepare_memory();  // memory allocation
    tddfa falign(fa_net_len, fa_num);
    falign.load_model(fa_kmodel_path);  // load kmodel
    falign.prepare_memory();  // memory allocation
    float *lst_landmarks = new float[2 * fk_num];
    float *cur_landmarks;
    cv::Mat cropped_R;
    cv::Mat cropped_G;
    cv::Mat cropped_B;
    box_t cropped_box;
    cv::Mat fk_img_R = cv::Mat(fk_net_len, fk_net_len, CV_8UC1, fld.virtual_addr_input[0]);
    cv::Mat fk_img_G = cv::Mat(fk_net_len, fk_net_len, CV_8UC1, fld.virtual_addr_input[0] + fk_net_len * fk_net_len);
    cv::Mat fk_img_B = cv::Mat(fk_net_len, fk_net_len, CV_8UC1, fld.virtual_addr_input[0] + fk_net_len * fk_net_len * 2);
    
    cv::Mat fa_img_R = cv::Mat(fa_net_len, fa_net_len, CV_8UC1, falign.virtual_addr_input[0]);
    cv::Mat fa_img_G = cv::Mat(fa_net_len, fa_net_len, CV_8UC1, falign.virtual_addr_input[0] + fa_net_len * fa_net_len);
    cv::Mat fa_img_B = cv::Mat(fa_net_len, fa_net_len, CV_8UC1, falign.virtual_addr_input[0] + fa_net_len * fa_net_len * 2);

    vector<float*> param_lst;
    vector<double*> roi_box_lst;
    const char* bin_path = "../data/face_alignment/constant.bin";
    constant_init(bin_path);
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
        fld.set_input(0);
        fld.set_output();
        falign.set_input(0);
        falign.set_output();

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
            struct drm_buffer *fbuf_argb = &drm_dev.drm_bufs_argb[drm_bufs_argb_index];
            img_argb = cv::Mat(screen_height, screen_width, CV_8UC4, (uint8_t *)fbuf_argb->map);
            
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
        float *falign_features = new float[(valid_box.size() + 1) * fa_num];
        double *falign_coords = new double[(valid_box.size() + 1) * 4];
        float* ver = new float[bfm_u_dim * 3];
        float* z = new float[bfm_u_dim * 3];
        {
            ScopedTiming st("run face landmark", enable_profile);
            obj_cnt = 0;
            for (auto b : valid_box)
            {
                cropped_box = get_enlarged_box(b, valid_width, valid_height, ori_img_R, 1.1);
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
                    cropped_box = get_box_from_landmarks(fld.valid_box, cur_landmarks, fk_num, 1.1);
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
                cropped_box = get_box_from_landmarks(fld.valid_box, cur_landmarks, fk_num, 1.0);
                {
                    ScopedTiming st("fa process", enable_profile);
                    falign.set_valid_box(cropped_box, ori_img_R);
                }
                cropped_R = falign.crop_image(ori_img_R);
                cv::resize(cropped_R, fa_img_R, cv::Size(fa_net_len, fa_net_len), cv::INTER_AREA);
                cropped_G = falign.crop_image(ori_img_G);
                cv::resize(cropped_G, fa_img_G, cv::Size(fa_net_len, fa_net_len), cv::INTER_AREA);
                cropped_B = falign.crop_image(ori_img_B);
                cv::resize(cropped_B, fa_img_B, cv::Size(fa_net_len, fa_net_len), cv::INTER_AREA);
                {
                    ScopedTiming st("fa run", enable_profile);
                    falign.run();
                }
                memcpy(falign_features + obj_cnt * fa_num, reinterpret_cast<float *>(falign.virtual_addr_output), sizeof(float) * fa_num);
                falign_coords[obj_cnt * 4 + 0] = static_cast<double>((falign.valid_box.x) / valid_width * screen_width);
                falign_coords[obj_cnt * 4 + 1] = static_cast<double>((falign.valid_box.y) / valid_height * screen_height);
                falign_coords[obj_cnt * 4 + 2] = static_cast<double>((falign.valid_box.x + falign.valid_box.w) / valid_width * screen_width);
                falign_coords[obj_cnt * 4 + 3] = static_cast<double>((falign.valid_box.y + falign.valid_box.h)  / valid_height * screen_height);
                if (obj_cnt < 32)
                {
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
        {
            ScopedTiming st("depth recon", enable_profile);
            param_lst.clear();
            roi_box_lst.clear();
            for (uint32_t _cnt = 0; _cnt < valid_box.size(); _cnt++)
            {
                param_lst.push_back(falign_features + _cnt * fa_num);
                roi_box_lst.push_back(falign_coords + _cnt * 4);             
            } 
            param_normalized(param_lst);
            vector<float*> ver_lst;
            for (uint32_t index = 0; index < param_lst.size(); index++)
            {
                float* pts3d = new float[3 * bfm_u_dim];
                ver_lst.push_back(pts3d);
            }
            recon_vers(ver_lst, param_lst, roi_box_lst);
            if(depth_or_pncc == 0)
			{
				get_depth(img_argb.data, ver, z, screen_height, screen_width, 3, ver_lst);
			}
			else
			{
                get_pncc(img_argb.data, ver, screen_height, screen_width, 3, ver_lst);
			}
            for (int index = 0; index < param_lst.size(); ++index)
            {
                delete[] ver_lst[index];
            }
        }         
        frame_cnt += 1;       
        delete[] falign_features;
        delete[] falign_coords;
        delete[] ver;
        delete[] z;    
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
    struct drm_buffer *fbuf_argb = &drm_dev.drm_bufs_argb[!drm_bufs_argb_index];
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
    if (argc < 20)
    {
        std::cerr << "Usage: " << argv[0] << " <fd_kmodel> <fd_net_len> <valid_width> <valid_height> <obj_thresh> <nms_thresh> <fk_kmodel> <fk_net_len> <fk_num> <nme_thresh> <max_loop> <fa_kmodel> <fa_net_len> <fa_num> <depth_or_pncc> <video_conf> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
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
    ai_args.fk_kmodel_path = argv[7];
    ai_args.fk_net_len = atoi(argv[8]);
    ai_args.fk_num = atoi(argv[9]);
    ai_args.nme_thresh = atof(argv[10]);
    ai_args.max_loop = atoi(argv[11]);
    ai_args.fa_kmodel_path = argv[12];
    ai_args.fa_net_len = atoi(argv[13]);
    ai_args.fa_num = atoi(argv[14]);
    ai_args.depth_or_pncc = atoi(argv[15]);
    video_cfg_file = argv[16];
    ai_args.is_rgb = atoi(argv[17]);
    ai_args.enable_profile = atoi(argv[18]);
    int enable_profile = atoi(argv[18]);
    ai_args.dump_img_dir = argv[19];

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
