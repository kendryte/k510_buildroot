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

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>             /* getopt_long() */
#include <pthread.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>

#include <linux/media.h>
#include <linux/types.h>
#include <linux/v4l2-mediabus.h>
#include <linux/v4l2-subdev.h>
#include <linux/videodev2.h>

#include "media_ctl.h"
#include "v4l2.h"

#define TOTAL_WIDTH 	3448 //0x0d78
#define TOTAL_HEIGHT 	2200 //0x0898
#define ACTIVE_WIDTH 	1920 //1080
#define ACTIVE_HEIGHT 	1080 //1920
#define VIDEO_WIDTH 	1920 //1080
#define VIDEO_HEIGHT 	1080 //1920

#define BUFFERS_COUNT	4
#define VIDEO_NAME1      "/dev/video2"
#define VIDEO_NAME2      "/dev/video6"

#define bool	_Bool
#define	true	1
#define	false	0

//
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/*************************************************************************
 *
*************************************************************************/
/**
 * @brief
 *
 * @param vdev
 * @return int
 */
static int video_setup(struct v4l2_device *vdev,struct v4l2_pix_format *format)
{
	//struct v4l2_pix_format format;
	int ret;
	printf("%s:start\n",__func__);
	/* Set the capture format on the VI output video node. */
	//memset(&format, 0, sizeof format);
	//format.pixelformat = pixelformat;//V4L2_PIX_FMT_NV12;//V4L2_PIX_FMT_SRGGB10;//V4L2_PIX_FMT_NV12;//V4L2_PIX_FMT_SGRBG10;
	//format.width = width;
	//format.height = height;
	printf("%s:v4l2_subdev_set_format format_out width:(%d),height:(%d),pixelformat(0x%x)\n",__func__,format->width,format->height,format->pixelformat);

	ret = v4l2_set_format(vdev,format);
	if (ret < 0)
	{
		printf("%s:v4l2_set_format error\n",__func__);
		return ret;
	}

	/* Allocate video buffers. */
	ret = v4l2_alloc_buffers(vdev, V4L2_MEMORY_MMAP, BUFFERS_COUNT);//V4L2_MEMORY_USERPTR, V4L2_MEMORY_MMAP
	if (ret < 0)
	{
		printf("%s:v4l2_alloc_buffers error\n",__func__);
		return ret;
	}
	printf("%s: dev->nbufs %urequested.\n", __func__,vdev->nbufs);

	return 0;
}
/**
 * @brief
 *
 * @param vdev
 * @return int
 */
static int video_start(struct v4l2_device *vdev)
{
	struct v4l2_video_buffer buffer;
	unsigned int i;
	int ret;
	printf("%s:vdev->nbufs(%u) start\n",__func__,vdev->nbufs);
	/* Queue all buffers for video capture. */
	for (i = 0; i < vdev->nbufs; ++i) {
		buffer.index = i;

		ret = v4l2_queue_buffer(vdev, &buffer);
		if (ret < 0) {
			printf("error: unable to queue buffer %u\n", i);
			return -errno;
		}
	}

	/* Start video streaming. */
	ret = v4l2_stream_on(vdev);
	if (ret < 0) {
		printf("error: failed to start video stream: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	return 0;
}
/**
 * @brief
 *
 * @param vdev
 * @return int
 */
static int video_stop(struct v4l2_device *vdev)
{
	int ret;

	/* Stop video streaming. */
	ret = v4l2_stream_off(vdev);
	if (ret < 0) {
		printf("error: failed to stop video stream: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	return 0;
}
/**
 * @brief
 *
 * @param vdev
 */
static void video_cleanup(struct v4l2_device *vdev)
{
	if (vdev) {
		v4l2_free_buffers(vdev);
		v4l2_close(vdev);
	}
}
/*************************************************************************
 *
*************************************************************************/
#define SELECT_TIMEOUT		2000		/* in milliseconds */

static bool done = false;
static void sigint_handler(int signal __attribute__((__unused__)))
{
	/* Set the done flag to true when the user presses CTRL-C to interrupt
	 * the main loop.
	 */
	done = true;
}
/**
 * @brief
 *
 */
int img_cnt[8] = {0};
static int process_yuv_image(struct v4l2_device *vdev,char *video_name,struct v4l2_pix_format *format,unsigned int video_num)
{
	struct v4l2_video_buffer buffer;
	int ret;
	char filename[100];
	unsigned int width = format->width;
	unsigned int height = format->height;
	/* Dequeue the buffer */
	ret = v4l2_dequeue_buffer(vdev, &buffer);
	if (ret < 0) {
		printf("error: unable to dequeue buffer: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	if (buffer.error) {
		printf("warning: error in dequeued buffer, skipping\n");
		return 0;
	}

	if(img_cnt[video_num] < 20)
	{
		sprintf(filename,"./%s_%dx%d_nv12_%d.yuv",&video_name[5],((width+15)/16*16),height,img_cnt[video_num]);
		printf("%s:%s\n",__func__,filename);
		FILE *fd = fopen(filename, "wb");
		if(fd == NULL)
		{
	    	printf("open %s failure, errno %d\n",filename,errno);
	    	return -1;
		}
		printf("open %s success \n",filename);
		ret = fwrite(buffer.mem, ((width+15)/16*16)* height*3/2, 1, fd);    // 3110400 = 1080 * 1920 * 1.5
		if(ret <= 0)
		{
	    	printf("fwrite  picture_addr is failed ret is %d \n", ret);
	    	return ret;
		}
		fclose(fd);
	}
	img_cnt[video_num]++;
	/* Requeue the buffer */
	ret = v4l2_queue_buffer(vdev, &buffer);
	if (ret < 0) {
		printf("error: unable to requeue buffer: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	return 0;
}
/**
 * @brief
 *
 * @param vdev
 * @param video_name
 * @param format
 * @param video_num
 * @return int
 */
static int process_rgb_image(struct v4l2_device *vdev,char *video_name,struct v4l2_pix_format *format,unsigned int video_num)
{
	struct v4l2_video_buffer buffer;
	int ret;
	unsigned int width = format->width;
	unsigned int height = format->height;
	unsigned int pixelformat = format->pixelformat;
	char c;
	char filename[100];
	FILE *fd;
	//c = getchar();
	/* Dequeue the buffer */
	ret = v4l2_dequeue_buffer(vdev, &buffer);
	if (ret < 0) {
		printf("error: unable to dequeue buffer: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	if (buffer.error) {
		printf("warning: error in dequeued buffer, skipping\n");
		return 0;
	}
	//c = getchar();
	if(img_cnt[video_num] < 20)
	{
		if( pixelformat == V4L2_PIX_FMT_ARGB32)
		{
			sprintf(filename,"./%s_%dx%d_%d.argb",&video_name[5],((width+15)/16*16),height,img_cnt[video_num]);
			printf("%s:%s\n",__func__,filename);
			fd = fopen(filename, "wb");
			if(fd == NULL)
			{
	    		printf("open %s failure, errno %d\n",filename,errno);
	    		return -1;
			}
			printf("open %s success \n",filename);
			ret = fwrite(buffer.mem, ((width+15)/16*16)* height*4, 1, fd);
			if(ret <= 0)
			{
	    		printf("fwrite  picture_addr is failed ret is %d \n", ret);
	    		return ret;
			}
			fclose(fd);
		}
		else if(pixelformat == V4L2_PIX_FMT_RGB24)
		{
			sprintf(filename,"./%s_%dx%d_%d.rgb",&video_name[5],((width+15)/16*16),height,img_cnt[video_num]);
			printf("%s:%s\n",__func__,filename);
			fd = fopen(filename, "wb");
			if(fd == NULL)
			{
	    		printf("open %s failure, errno %d\n",filename,errno);
	    		return -1;
			}
			printf("open %s success \n",filename);

			ret = fwrite(buffer.mem,((width+15)/16*16)* height*3, 1, fd);
			if(ret <= 0)
			{
	    		printf("%s,fwrite  picture_addr is failed ret is %d \n", filename,ret);
	    		return ret;
			}
			fclose(fd);
		}

	}
	img_cnt[video_num]++;
	/* Requeue the buffer */
	ret = v4l2_queue_buffer(vdev, &buffer);
	if (ret < 0) {
		printf("error: unable to requeue buffer: %s (%d)\n",
			strerror(-ret), ret);
		return ret;
	}

	return 0;
}
/*****************************************************************************
 *
 *****************************************************************************/
static char 		   *video_cfg_file = NULL;
static int 			   verbose = 0;

static void usage(FILE *fp, int argc, char **argv)
{
    fprintf(fp,
         "Usage: %s [options]\n\n"
         "Version 1.3\n"
         "Options:\n"
         "-h | --help          Print this message\n"
         "-f | --video_cfg_file   video_cfg_filename [%s]\n"
         "-v | --verbose       Verbose output\n"
         "-a | --anti-clicker-enable (0: all disable | 1: f 2k enable | 2: r 2k enable | 3: f&r 2k enable)\n"
         "-x | --ae sw/hw select (default 0: sw ae | 1: hw ae)\n"
         "-l | --adaptive enable (0: disable | 1: enable, default: enable)\n"
         "",
         argv[0],video_cfg_file);
}

static const char short_options[] = "hf:va:x:l:";// 短选项 ：表示带参数

static const struct option //长选项
long_options[] = {
    { "video_cfg_file", required_argument, NULL, 'f' },
    { "help",   no_argument, 	   NULL, 'h' },
    { "verbose", no_argument,      NULL, 'v' },
    { "anfi-flicker-enable", required_argument, NULL, 'a' },
    { "ae-select", required_argument, NULL, 'x' },
    { "adaptive", required_argument, NULL, 'l' },
    { 0, 0, 0, 0 }
};
/**
 * @brief
 *
 * @param s
 */
static void errno_exit(const char *s)
{
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}
/**
 * @brief
 *
 * @param signo
 */
void sighand(int signo)
{
    pthread_t  tid = pthread_self();

    printf("Thread %lu in signal handler/n", tid);
    return;
}
/**
 * @brief
 *
 * @param info
 * @return void*
 */
void *run_f2k_video(void *info)
{
	struct timespec start, end;
	unsigned int count = 0;
	struct v4l2_device *vdev[4];
	int i = 0;
	int ret;
	int maxfd;
	float fps;
	fd_set fds;
	struct video_info *dev_info= (struct video_info *)info;
	struct v4l2_pix_format format[4];

	FD_ZERO(&fds);
	/* Open the video capture device, setup the format and allocate the
	 * buffers.
	 */
	for(i = 0; i < 4;i++)
	{
		if(dev_info->enable[i] == 1)
		{
			pthread_mutex_lock(&mutex);
			vdev[i] = v4l2_open(dev_info->video_name[i]);
			if (vdev[i] == NULL) {
				printf("error: unable to open video capture device %s\n",
					dev_info->video_name[i]);
				pthread_mutex_unlock(&mutex);
				goto cleanup_f2k;
			}
			printf("%s:vdev->fd %d\n",__func__,vdev[i]->fd);
			memset(&format[i], 0, sizeof(struct v4l2_pix_format));
			format[i].width = dev_info->video_width[i];//width;
			format[i].height = dev_info->video_height[i];//height;
			//
			if(dev_info->video_out_format[i] == 1)
			{
				format[i].pixelformat = V4L2_PIX_FMT_NV12;  //yuv420
				if(i == 3)
				{
					format[i].pixelformat = V4L2_PIX_FMT_ARGB32; //argb
				}
			}
			else
			{
				format[i].pixelformat = V4L2_PIX_FMT_NV16;  ////yuv422
				if(i == 3)
				{
					format[i].pixelformat = V4L2_PIX_FMT_RGB24; //s rgb
				}
			}

			ret = video_setup(vdev[i],&format[i]);
			if (ret < 0) {
				printf("%s:error: unable to setup video capture ret %d\n",__func__,ret);
				pthread_mutex_unlock(&mutex);
				goto cleanup_f2k;
			}
			printf("%s: dev->nbufs (%u)requested.\n", __func__,vdev[i]->nbufs);
			//
			ret = video_start(vdev[i]);
			if (ret < 0)
			{
				pthread_mutex_unlock(&mutex);
				goto cleanup_f2k;
			}
			pthread_mutex_unlock(&mutex);
			/* Store the f2k output device node file handle in the file descriptors
			 * set, to be used by select() in the main loop.
			 */
			FD_SET(vdev[i]->fd, &fds);
			if(vdev[i]->fd > maxfd ) maxfd = vdev[i]->fd;
			printf("%s:maxfd(%d)vdev[i]->fd(%d)\n",__func__,maxfd,vdev[i]->fd);
		}
	}
	//
	clock_gettime(CLOCK_MONOTONIC, &start);
	/* Main capture loop. Wait for a video buffer using select() and process
	 * it.
	 */
	//char c = getchar();
	while (!done) {
		printf("%s:select\n",__func__);
		struct timeval timeout;
		fd_set rfds;
		char c;
		timeout.tv_sec = SELECT_TIMEOUT / 1000;
		timeout.tv_usec = (SELECT_TIMEOUT % 1000) * 1000;
		rfds = fds;
		//c = getchar();
		ret = select(maxfd + 1, &rfds, NULL, NULL, &timeout);
		printf("%s:ret(%d)\n",__func__,ret);
		//c = getchar();
		if (ret < 0) {
			/* EINTR means that a signal has been received, continue
			 * to the next iteration in that case.
			 */
			if (errno == EINTR)
				continue;

			printf("error: select failed with %d\n", errno);
			goto cleanup_f2k;
		}
		if (ret == 0) {
			/* select() should never time out as the ISP is supposed
			 * to capture images continuously. A timeout is thus
			 * considered as a fatal error.
			 */
			printf("error: select timeout\n");
			goto cleanup_f2k;
		}
		//f2k dev
		for(i = 0;i <3;i++)
		{
			if(dev_info->enable[i] == 1)
			{
				if(FD_ISSET(vdev[i]->fd,&rfds))
				{
					pthread_mutex_lock(&mutex);
					process_yuv_image(vdev[i],dev_info->video_name[i],&format[i],i);
					pthread_mutex_unlock(&mutex);
				}
			}
		}
		//
		if(dev_info->enable[3] == 1)
		{
			if(FD_ISSET(vdev[3]->fd,&rfds))
			{
				pthread_mutex_lock(&mutex);
				process_rgb_image(vdev[3],dev_info->video_name[3],&format[3],3);
				pthread_mutex_unlock(&mutex);
			}
		}

		count++;
	}
	/* Print some statistics. */
	end.tv_sec -= start.tv_sec;
	end.tv_nsec -= start.tv_nsec;
	if (end.tv_nsec < 0) {
		end.tv_sec--;
		end.tv_nsec += 1000000000;
	}
	fps = count / (end.tv_sec + end.tv_nsec / 1000000000.0);

	printf("%u images processed in %lu.%06lu seconds (%f fps)\n", count,
	       end.tv_sec, end.tv_nsec / 1000, fps);

cleanup_f2k:
	for(i = 0; i < 4;i++)
	{
		if(dev_info->enable[i] == 1)
		{
			/* Stop the ISP. */
			pthread_mutex_lock(&mutex);
			video_stop(vdev[i]);
			pthread_mutex_unlock(&mutex);
		}
	}

	for(i = 0; i < 4;i++)
	{
		if(dev_info->enable[i] == 1)
		{
			pthread_mutex_lock(&mutex);
			video_cleanup(vdev[i]);
			pthread_mutex_unlock(&mutex);
		}
	}
}
/**
 * @brief
 *
 * @param info
 * @return void*
 */
void *run_r2k_video(void *info)
{
	struct timespec start, end;
	unsigned int count = 0;
	struct v4l2_device *vdev[4];
	int i = 0;
	int ret;
	int maxfd;
	float fps;
	fd_set fds;
	struct video_info *dev_info= (struct video_info *)info;
	struct v4l2_pix_format format[4];
	char c;
	FD_ZERO(&fds);
	/* Open the video capture device, setup the format and allocate the
	 * buffers.
	 */
	for(i = 0; i < 4;i++)
	{
		if(dev_info->enable[i] == 1)
		{
			pthread_mutex_lock(&mutex);
			vdev[i] = v4l2_open(dev_info->video_name[i]);
			if (vdev[i] == NULL) {
				printf("error: unable to open video capture device %s\n",
					dev_info->video_name[i]);
				pthread_mutex_unlock(&mutex);
				goto cleanup_r2k;
			}
			printf("%s:vdev->fd %d\n",__func__,vdev[i]->fd);
			//c = getchar();
			memset(&format[i], 0, sizeof(struct v4l2_pix_format));
			format[i].width = dev_info->video_width[i];//width;
			format[i].height = dev_info->video_height[i];//height;
			//
			if(dev_info->video_out_format[i] == 1)
			{
				format[i].pixelformat = V4L2_PIX_FMT_NV12;  //yuv420
				if(i == 3)
				{
					format[i].pixelformat = V4L2_PIX_FMT_ARGB32; //argb
				}
			}
			else
			{
				format[i].pixelformat = V4L2_PIX_FMT_NV16;  ////yuv422
				if(i == 3)
				{
					format[i].pixelformat = V4L2_PIX_FMT_RGB24; //s rgb
				}
			}
			//c = getchar();
			ret = video_setup(vdev[i],&format[i]);
			if (ret < 0) {
				printf("%s:error: unable to setup video capture ret %d\n",__func__,ret);
				pthread_mutex_unlock(&mutex);
				goto cleanup_r2k;
			}
			printf("%s: dev->nbufs (%u)requested.\n", __func__,vdev[i]->nbufs);
			//
			//c = getchar();
			ret = video_start(vdev[i]);
			if (ret < 0)
			{
				pthread_mutex_unlock(&mutex);
				goto cleanup_r2k;
			}
			pthread_mutex_unlock(&mutex);
			/* Store the f2k output device node file handle in the file descriptors
			 * set, to be used by select() in the main loop.
			 */
			FD_SET(vdev[i]->fd, &fds);
			if(vdev[i]->fd > maxfd ) maxfd = vdev[i]->fd;
		}
	}
	//
	clock_gettime(CLOCK_MONOTONIC, &start);
	/* Main capture loop. Wait for a video buffer using select() and process
	 * it.
	 */
	//char c = getchar();
	while (!done) {
		printf("%s:select\n",__func__);
		struct timeval timeout;
		fd_set rfds;
		char c;
		timeout.tv_sec = SELECT_TIMEOUT / 1000;
		timeout.tv_usec = (SELECT_TIMEOUT % 1000) * 1000;
		rfds = fds;
		//c = getchar();
		ret = select(maxfd + 1, &rfds, NULL, NULL, &timeout);
		//c = getchar();
		if (ret < 0) {
			/* EINTR means that a signal has been received, continue
			 * to the next iteration in that case.
			 */
			if (errno == EINTR)
				continue;

			printf("error: select failed with %d\n", errno);
			goto cleanup_r2k;
		}
		if (ret == 0) {
			/* select() should never time out as the ISP is supposed
			 * to capture images continuously. A timeout is thus
			 * considered as a fatal error.
			 */
			printf("error: select timeout\n");
			goto cleanup_r2k;
		}
		//
		for(i = 0;i <3;i++)
		{
			if(dev_info->enable[i] == 1)
			{
				if(FD_ISSET(vdev[i]->fd,&rfds))
				{
					pthread_mutex_lock(&mutex);
					process_yuv_image(vdev[i],dev_info->video_name[i],&format[i],i+4);
					pthread_mutex_unlock(&mutex);
				}
			}
		}
		//
		if(dev_info->enable[3] == 1)
		{
			if(FD_ISSET(vdev[3]->fd,&rfds))
			{
				pthread_mutex_lock(&mutex);
				process_rgb_image(vdev[3],dev_info->video_name[3],&format[3],7);
				pthread_mutex_unlock(&mutex);
			}
		}
		count++;
	}

	/* Print some statistics. */
	end.tv_sec -= start.tv_sec;
	end.tv_nsec -= start.tv_nsec;
	if (end.tv_nsec < 0) {
		end.tv_sec--;
		end.tv_nsec += 1000000000;
	}

	fps = count / (end.tv_sec + end.tv_nsec / 1000000000.0);

	printf("%u images processed in %lu.%06lu seconds (%f fps)\n", count,
	       end.tv_sec, end.tv_nsec / 1000, fps);

cleanup_r2k:
	for(i = 0; i < 4;i++)
	{
		if(dev_info->enable[i] == 1)
		{
			/* Stop the ISP. */
			pthread_mutex_lock(&mutex);
			video_stop(vdev[i]);
			pthread_mutex_unlock(&mutex);
		}
	}

	for(i = 0; i < 4;i++)
	{
		if(dev_info->enable[i] == 1)
		{
			pthread_mutex_lock(&mutex);
			video_cleanup(vdev[i]);
			pthread_mutex_unlock(&mutex);
		}
	}
}
/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__)))
{
	int exit_code = EXIT_SUCCESS;
	struct video_info dev_info[2];
	struct sigaction actions;
	pthread_t f2k_pid,r2k_pid;
	int ret;
	int rc;

	printf("%s:start\n",__func__);
    for (;;) {
        int idx;
        int c;
        c = getopt_long(argc, argv,
                short_options, long_options, &idx);

        if (-1 == c)
            break;

        switch (c) {
        case 0: /* getopt_long() flag */
            break;
        case 'f':
            video_cfg_file = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'a':
            anti_flicker_init(atoi(optarg));
            break;
        case 'x':
            ae_select_init(atoi(optarg));
            break;
        case 'l':
            adaptive_enable(atoi(optarg));
            break;
        default:
            usage(stderr, argc, argv);
            exit(EXIT_FAILURE);
        }
    }

	/* Register a signal handler for SIGINT, received when the user presses
	 * CTRL-C. This will allow the main loop to be interrupted, and resources
	 * to be freed cleanly.
	 */
	signal(SIGINT, sigint_handler);

	mediactl_init(video_cfg_file,&dev_info[0]);
	//
    memset(&actions, 0, sizeof(actions));
    sigemptyset(&actions.sa_mask); /* 将参数set信号集初始化并清空 */
    actions.sa_flags = 0;
    actions.sa_handler = sighand;
    /* 设置SIGALRM的处理函数 */
    sigaction(SIGALRM,&actions,NULL);

	if(dev_info[0].video_used == 1)
	{
		pthread_create(&f2k_pid,NULL,run_f2k_video,(void *)&dev_info[0]);
	}

	if( dev_info[1].video_used == 1)
	{
		pthread_create(&r2k_pid,NULL,run_r2k_video,(void *)&dev_info[1]);
		//run_r2k_video(&dev_info[1]);
	}

	if( dev_info[0].video_used == 1)
	{
		pthread_kill(f2k_pid, SIGALRM);
	}

	if( dev_info[1].video_used == 1)
	{
		pthread_kill(r2k_pid, SIGALRM);
	}

    printf("Wait for masked and unmasked threads to complete\n");
	if( dev_info[0].video_used == 1)
    {
		pthread_join(f2k_pid, NULL);
	}

	if( dev_info[1].video_used == 1)
	{
    	pthread_join(r2k_pid, NULL);
	}
	mediactl_exit();
	printf("Main completed/n");
	return exit_code;
}
