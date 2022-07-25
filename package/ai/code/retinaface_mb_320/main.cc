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
#include "v4l2.h"
#include "buf_mgt.h"
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
using namespace rapidjson;

#define PROFILING 0

struct video_info dev_info[2];
static char *video_cfg_file = "video_192x320.conf";
#define SELECT_TIMEOUT		2000

std::mutex mtx;

uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv;
int obj_cnt, obj_point[DRM_BUFFERS_COUNT];
cv::Point point[DRM_BUFFERS_COUNT][32][5];//用于清空上一帧AI计算的OSD层的显示[2个buffer交替][最多显示32个对象][5点坐标]
char *kmodel_name;
int display_ds2;

#define AUTO_ADAPT_CONFIG_FILE "auto.conf"
static uint32_t screen_width, screen_height;
static uint32_t gnne_input_width, gnne_input_height;
static uint32_t gnne_valid_width, gnne_valid_height;
static buf_mgt_t buf_mgt;

std::atomic<bool> quit(true);

void fun_sig(int sig)
{
    if(sig == SIGINT)
    {
        quit.store(false);
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

void ai_worker()
{
    float obj_thresh = 0.5;
    float nms_thresh = 0.2;
    int offset_channel = gnne_input_width * gnne_input_height;

    retinaface rf(obj_thresh, nms_thresh);

    rf.load_model(kmodel_name);

	rf.prepare_memory();

    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, gnne_input_width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, gnne_input_height);
    capture.set(cv::CAP_PROP_FOURCC, dev_info[0].video_out_format[3] ? V4L2_PIX_FMT_ARGB32 : V4L2_PIX_FMT_RGB24);
    mtx.unlock();
    cv::Mat rgb24_img_for_ai(RETINAFACE_FIX_SIZE, RETINAFACE_FIX_SIZE, CV_8UC3, rf.virtual_addr_input[0]);

    while(quit.load()) 
    {
        bool ret = false;
        ScopedTiming st("total");
        mtx.lock();
        ret = capture.read(rgb24_img_for_ai);
        mtx.unlock();
        if(ret == false)
        {
            quit.store(false);
            continue; // 
        }
        uint64_t index;
        buf_mgt_writer_get(&buf_mgt, (void **)&index);
        struct drm_buffer *fbuf_argb = &drm_dev.drm_bufs_argb[index];
        cv::Mat img_argb = cv::Mat(screen_height, screen_width, CV_8UC4, (uint8_t *)fbuf_argb->map);
        //padding
        uint8_t *r_addr, *g_addr, *b_addr;
        r_addr = (uint8_t *)rf.virtual_addr_input[0];
        g_addr = (uint8_t *)rf.virtual_addr_input[0] + offset_channel;
        b_addr = (uint8_t *)rf.virtual_addr_input[0] + offset_channel * 2;
        if (gnne_valid_width < gnne_input_width) {
            uint32_t padding = gnne_input_width - gnne_valid_width;
            for (int row = 0; row < gnne_valid_height; row++) {
                uint32_t offset = row * gnne_input_width + gnne_valid_width;
                memset(r_addr + offset, R_MEAN, padding);
                memset(g_addr + offset, G_MEAN, padding);
                memset(b_addr + offset, B_MEAN, padding);
            }
        }
        if (gnne_valid_height < gnne_input_height) {
            uint32_t padding = (gnne_input_height - gnne_valid_height) * gnne_input_width;
            uint32_t offset = gnne_valid_height * gnne_input_width;
            memset(r_addr + offset, R_MEAN, padding);
            memset(g_addr + offset, G_MEAN, padding);
            memset(b_addr + offset, B_MEAN, padding);
        }
        if(display_ds2)
        {
            cv::Mat ds2_bgra(RETINAFACE_FIX_SIZE, RETINAFACE_FIX_SIZE, CV_8UC4);

            cv::Mat channel[3];
            channel[2] = cv::Mat(RETINAFACE_FIX_SIZE, RETINAFACE_FIX_SIZE, CV_8UC1, rf.virtual_addr_input[0]); //R
            channel[1] = cv::Mat(RETINAFACE_FIX_SIZE, RETINAFACE_FIX_SIZE, CV_8UC1, rf.virtual_addr_input[0] + offset_channel); //G
            channel[0] = cv::Mat(RETINAFACE_FIX_SIZE, RETINAFACE_FIX_SIZE, CV_8UC1, rf.virtual_addr_input[0] + offset_channel*2);  //B

            cv::Mat ds2_img = cv::Mat(RETINAFACE_FIX_SIZE, RETINAFACE_FIX_SIZE, CV_8UC3);
            merge(channel, 3, ds2_img);

            cv::cvtColor(ds2_img, ds2_bgra, cv::COLOR_BGR2BGRA); 

            // static int frame_cnt = 0;
            // if(frame_cnt++ % 10 == 1){
            // 	std::string img_out_path = "./img_" + std::to_string(frame_cnt) + ".bmp";
            // 	cv::imwrite(img_out_path, ds2_bgra);
            // }

            cv::Mat ds2_roi=img_argb(cv::Rect(0,0,ds2_bgra.cols,ds2_bgra.rows));
            ds2_bgra.copyTo(ds2_roi);
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

        std::vector<box_t> valid_box;
        std::vector<landmarks_t> valid_landmarks;
        rf.get_final_box(valid_box, valid_landmarks);

        {
#if PROFILING
            ScopedTiming st("display clear");
#endif

            for(int i=0; i<obj_point[index]; i++)
            {
                for (uint32_t ll = 0; ll < 5; ll++)
                {
                    //对上一帧写的数据设置透明，也就是清空之前的显示。
                    //直接memset清空整个OSD层太花时间。
                    cv::circle(img_argb, point[index][i][ll], 4, cv::Scalar(0, 0, 0, 0), -1);
                }
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
                    frame.line_x_start = (b.x * RETINAFACE_FIX_SIZE - b.w * RETINAFACE_FIX_SIZE / 2) * screen_width / gnne_valid_width;
                    frame.line_y_start = (b.y * RETINAFACE_FIX_SIZE - b.h * RETINAFACE_FIX_SIZE / 2) * screen_height / gnne_valid_height;
                    frame.line_x_end = (b.x * RETINAFACE_FIX_SIZE + b.w * RETINAFACE_FIX_SIZE / 2) * screen_width / gnne_valid_width;
                    frame.line_y_end = (b.y * RETINAFACE_FIX_SIZE + b.h * RETINAFACE_FIX_SIZE / 2) * screen_height / gnne_valid_height;
                    frame.line_x_end = frame.line_x_end > screen_width ? screen_width : frame.line_x_end;
                    frame.line_y_end = frame.line_y_end > screen_height ? screen_height : frame.line_y_end;
                    draw_frame(&frame);
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
        printf("obj_cnt = %d \n", obj_cnt);
        {
#if PROFILING
            ScopedTiming st("draw point");
#endif
            obj_point[index] = 0;
            for (auto l : valid_landmarks)
            {
                for (uint32_t ll = 0; ll < 5; ll++)
                {
                    if (obj_point[index] < 32)
                    {
                        uint32_t x0 = l.points[2 * ll + 0] * RETINAFACE_FIX_SIZE * screen_width / gnne_valid_width;
                        uint32_t y0 = l.points[2 * ll + 1] * RETINAFACE_FIX_SIZE * screen_height / gnne_valid_height;

                        cv::circle(img_argb, cv::Point(x0, y0), 4, cv::Scalar(0, 0, 255, 255), -1);
                        point[index][obj_point[index]][ll] =  cv::Point(x0, y0);
                    }
                }
                obj_point[index] += 1;
            }
        }
        buf_mgt_writer_put(&buf_mgt, (void *)index);
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

void display_worker()
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
    printf("format: %d,%d\n", format.width, format.height);

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
        video5_height = 192;
    } else if (screen_width == 1080 && screen_height == 1920) {
        sensor0_cfg_file = "imx219_1080x1920_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 192;
        video5_height = 320;
    } else if (screen_width == 1280 && screen_height == 720) {
        sensor0_cfg_file = "imx219_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 320;
        video5_height = 192;
    } else {
        return -1;
    }
    // update video config
    gnne_input_width = RETINAFACE_FIX_SIZE;
    gnne_input_height = RETINAFACE_FIX_SIZE;
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
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <.kmodel> <display_ds2>" << std::endl;
        return -1;
    }

    kmodel_name = argv[1];
    display_ds2 = atoi(argv[2]);

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
    mediactl_exit();  
    return 0;
}