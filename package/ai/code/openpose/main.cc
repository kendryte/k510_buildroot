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


#include "openpose.h"
#include "cv2_utils.h"
#include "pafprocess.h"
#include "buf_mgt.h"
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
using namespace rapidjson;

extern int CocoColors[][3];
extern int CocoRenders[][2];

#define SELECT_TIMEOUT		2000

struct video_info dev_info[2];
std::mutex mtx;
uint8_t drm_bufs_index = 0;
uint8_t drm_bufs_argb_index = 0;
struct drm_buffer *fbuf_yuv;
int obj_cnt;
std::vector<cv::Point> points_to_clear[DRM_BUFFERS_COUNT];
std::vector<cv::Point> lines_to_clear[DRM_BUFFERS_COUNT];

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

static bool judge_in_range(std::vector<uint32_t> v, uint32_t index)
{
	for (auto vi : v)
	{
		if (vi == index)
		{
			return true;
		}
	}
	return false;
}

void ai_worker(ai_worker_args ai_args)
{
    // parse ai worker agrs
    char* kmodel_path = ai_args.kmodel_path;  // openpose kmodel path
    int net_width = gnne_input_width;  // openpose kmodel input size is net_height * net_width
    int net_height = gnne_input_height;
    int valid_width = gnne_valid_width;  // isp ds2 input width, should be the same with definition in video config
    int valid_height = gnne_valid_height;  // isp ds2 input height, should be the same with definition in video config
    int is_rgb = ai_args.is_rgb;  // isp ds2 input format, RGB or BGR, RGB now
    int enable_profile = ai_args.enable_profile;  // wether enable time counting
    std::string dump_img_dir = ai_args.dump_img_dir;  // where to dump image 
    int offset_channel = net_width * net_height;  // ds2 channel offset
    int enable_dump_image = (dump_img_dir != "None");
    openpose op(net_height, net_width);
    op.load_model(kmodel_path);  // load kmodel
	op.prepare_memory();  // memory allocation
    
    /****fixed operation for video operation****/
    mtx.lock();
    cv::VideoCapture capture;
	capture.open(5);
    // video setting
    capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, net_width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, net_height);
    // RRRRRR....GGGGGGG....BBBBBB, CHW
    capture.set(cv::CAP_PROP_FOURCC, V4L2_PIX_FMT_RGB24);
    mtx.unlock();


    int frame_cnt = 0;

    // define cv::Mat for ai input
    // padding offset is 0, padding is at last
    cv::Mat rgb24_img_for_ai(net_height, net_width, CV_8UC3, op.virtual_addr_input[0]);
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
        if(enable_dump_image)
        {
            cv::Mat ori_img_R = cv::Mat(valid_height, valid_width, CV_8UC1, op.virtual_addr_input[0]);
            cv::Mat ori_img_G = cv::Mat(valid_height, valid_width, CV_8UC1, op.virtual_addr_input[0] + offset_channel);
            cv::Mat ori_img_B = cv::Mat(valid_height, valid_width, CV_8UC1, op.virtual_addr_input[0] + offset_channel * 2);
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
        
        op.set_input(0);
        op.set_output();

        {
            ScopedTiming st("op run", enable_profile);
            op.run();
        }
        
        {
            ScopedTiming st("op get output", enable_profile);
            op.get_output();
        }

        {
            ScopedTiming st("op post process", enable_profile);
            op.post_process();
        }

        {
            ScopedTiming st("paf process", enable_profile);
            process_paf(net_height / 2, net_width / 2, OUTPUT_CHANNELS_0, op.foutput, net_height / 2, net_width / 2, OUTPUT_CHANNELS_0, op.output_0, net_height / 2, net_width / 2, OUTPUT_CHANNELS_1, op.output_1);
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
                cv::circle(img_argb, points_to_clear[index][cc], 8, cv::Scalar(0, 0, 0, 0), -1);
            }

            for (uint32_t cc = 0; cc < lines_to_clear[index].size() / 2; cc++)
            {          
                cv::line(img_argb, lines_to_clear[index][2 * cc], lines_to_clear[index][2 * cc + 1], cv::Scalar(0, 0, 0, 0), 4);
            }
        }

        {
            ScopedTiming st("draw point", enable_profile);
            uint32_t human_cnts = get_num_humans();
            float x, y, score, human_score;
            obj_cnt = 0;
            points_to_clear[index].clear();
            lines_to_clear[index].clear();
            for (uint32_t human_id = 0; human_id < human_cnts; human_id++)
            {
                std::vector<uint32_t> human_keys;
                std::vector<point_t> human_points;
                point_t keypoint;
                for (uint32_t part_idx = 0; part_idx < 18; part_idx++)
                {
                    int c_idx = get_part_cid(human_id, part_idx);
                    if (c_idx < 0)
                    {
                        continue;
                    }
                    keypoint.x = (float)get_part_x(c_idx) / (net_width / 2);
                    keypoint.y = (float)get_part_y(c_idx) / (net_height / 2);
                    keypoint.prob = get_part_score(c_idx);
                    human_keys.push_back(part_idx);
                    human_points.push_back(keypoint);
                }
                int _cnt = 0;
                for (uint32_t part_idx = 0; part_idx < 18; part_idx++)
                {
                    _cnt = 0;
                    std::vector<cv::Point> centers;
                    for (uint32_t part_idx = 0; part_idx < 18; part_idx++)
                    {
                        if (judge_in_range(human_keys, part_idx))
                        {
                            centers.push_back(cv::Point(int(human_points[_cnt].x * screen_width + 0.5), int(human_points[_cnt].y * screen_height + 0.5)));
                            cv::circle(img_argb, cv::Point(int(human_points[_cnt].x *screen_width + 0.5), int(human_points[_cnt].y * screen_height + 0.5)), 8, cv::Scalar(CocoColors[part_idx][0], CocoColors[part_idx][1], CocoColors[part_idx][2], 255), -1);
                            points_to_clear[index].push_back(cv::Point(int(human_points[_cnt].x *screen_width + 0.5), int(human_points[_cnt].y * screen_height + 0.5)));
                            _cnt++;
                        }
                        else 
                        {
                            centers.push_back(cv::Point(0, 0));
                        }
                    }
                    for (uint32_t part_idx = 0; part_idx < 17; part_idx++)
                    {
                        uint32_t first_index = CocoRenders[part_idx][0];
                        uint32_t second_index = CocoRenders[part_idx][1];
                        if (judge_in_range(human_keys, first_index) && judge_in_range(human_keys, second_index))
                        {
                            cv::line(img_argb, centers[first_index], centers[second_index], cv::Scalar(CocoColors[part_idx][0], CocoColors[part_idx][1], CocoColors[part_idx][2], 255), 4);
                            lines_to_clear[index].push_back(centers[first_index]);
                            lines_to_clear[index].push_back(centers[second_index]);
                        }
                    }
                    centers.clear();
                }
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
        video5_width = 432;
        video5_height = 368;
    } else if (screen_width == 1080 && screen_height == 1920) {
        sensor0_cfg_file = "imx219_1080x1920_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 432;
        video5_height = 368;
    } else if (screen_width == 1280 && screen_height == 720) {
        sensor0_cfg_file = "imx219_0.conf";
        video3_width = screen_width;
        video3_height = screen_height;
        video5_width = 432;
        video5_height = 368;
    } else {
        return -1;
    }
    // update video config
    gnne_input_width = 432;
    gnne_input_height = 368;
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
    if (argc < 10)
    {
        std::cerr << "Usage: " << argv[0] << " <kmodel> <net_width> <net_height> <valid_width> <valid_height> <video_config> <is_rgb> <enable_profile> <dump_image_dir>" << std::endl;
        return -1;
    }
    // parse args for ai worker
    ai_worker_args ai_args;
    ai_args.kmodel_path = argv[1];
    ai_args.net_width = atoi(argv[2]);
    ai_args.net_height = atoi(argv[3]);
    ai_args.valid_width = atoi(argv[4]);
    ai_args.valid_height = atoi(argv[5]);
    video_cfg_file = argv[6];
    ai_args.is_rgb = atoi(argv[7]);
    ai_args.enable_profile = atoi(argv[8]);
    int enable_profile = atoi(argv[8]);
    ai_args.dump_img_dir = argv[9];

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
