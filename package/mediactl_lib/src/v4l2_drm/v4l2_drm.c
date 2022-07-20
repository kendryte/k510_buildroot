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

/* v4l2_test */
#include <asm-generic/errno-base.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <pthread.h>
//#include <atomic.h>

#include <linux/videodev2.h>

#include "drm/k510_drm.h"
#include "media_ctl.h"
#include "k510_drm.h"
#include <semaphore.h>

static bool done = false;
static char 	*video_cfg_file = "video_drm.cfg";

#define FORCED_WIDTH  1080//1920
#define FORCED_HEIGHT 1920//1080
#define FORCED_FORMAT V4L2_PIX_FMT_YUV420 //V4L2_PIX_FMT_NV12 //
#define FORCED_FIELD  V4L2_FIELD_ANY
#define VIDEO_NAME    "/dev/video3"
static int verbose = 0;

static int isp_ae_status = 0;
//static int r_2k_status = 0;

#define pr_debug(fmt, arg...) \
    if (verbose) fprintf(stderr, fmt, ##arg)

#define CLEAR(x) memset(&(x), 0, sizeof(x)) //相当于CLEAR(x) =memset(&(x), 0, sizeof(x))

enum io_method {                           //枚举，即只能取其中的一个值。也是一种数据结构
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
};

struct buffer {
	unsigned int index;
    void   *start;
    size_t  length;                    //size_t =unsigned int 用来表示sizeof的
	int dbuf_fd; //drm
};

//char            dev_name[50];         //用来保存设备名
//static int              fd = -1;
//struct buffer          *buffers;
//static unsigned int     n_buffers;
//unsigned int width;
//unsigned int height;

struct camera_info
{
    int fd;
    char video_name[50];
    struct drm_size size;
    struct buffer  *buffers;
    unsigned int  n_buffers;
    unsigned int  buffer_start;
};

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t frame_mutex[2] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
static struct v4l2_buffer out_buffer[2];
sem_t frame_sem[2];
int cam_fd[2];
unsigned int drm_vsync = 0;
/*******************************************************************
*
********************************************************************/
static void errno_exit(const char *s)
{
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

static int xioctl(int fh, int request, void *arg)
{
    int r;

    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
}

int readframe(int fd, struct v4l2_buffer* vbuf) {
    memset(vbuf, 0, sizeof(struct v4l2_buffer));
    vbuf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vbuf->memory = V4L2_MEMORY_DMABUF;
    return xioctl(fd, VIDIOC_DQBUF, vbuf);
}

/**
 * @brief 
 * 
 * @param camera 
 */
static int stop_capturing(struct camera_info *camera)
{
    enum v4l2_buf_type type;
    int fd = camera->fd;

    printf("%s: %d called!\n", __func__,fd);
    pthread_mutex_lock(&mutex);
    if(fd)
    {
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;        
        if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
        {
            pthread_mutex_unlock(&mutex);
            //  errno_exit("VIDIOC_STREAMOFF");
            printf("%s:VIDIOC_STREAMOFF failed!\n",__func__);
            return -1;
        }        
    }
    pthread_mutex_unlock(&mutex);
    printf("%s: end!\n", __func__);
    return 0;
}
/**
 * @brief 
 * 
 * @param camera 
 */
static int start_capturing(struct camera_info *camera)
{
    unsigned int i;
    enum v4l2_buf_type type;
    int err;
    int fd = camera->fd;
    unsigned int n_buffers = camera->n_buffers;
    struct buffer  *buffers = camera->buffers;

    pr_debug("%s: called!\n", __func__);

    pr_debug("\tn_buffers: %d\n", n_buffers);

    for (i = 0; i < n_buffers; ++i) {        
        struct v4l2_buffer buf;
        pr_debug("\ti: %d\n", i);

        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_DMABUF;//drm //V4L2_MEMORY_MMAP;
        buf.index = i;
        buf.m.fd = buffers[i].dbuf_fd; //drm
        buf.length = buffers[i].length;

        pr_debug("\tbuf.index: %d\n", buf.index);
        //printf("\tbuf.index: %d,buf.m.fd %d,buf.length %d\n",buf.index,buf.m.fd,buf.length);
        // err == xioctl(fd, VIDIOC_QBUF, &buf);
        err = ioctl(fd, VIDIOC_QBUF, &buf);
        if (err < 0) {
            //errno_exit(".\n");
            return err;
        }
    }

    pr_debug("\terr: %d\n", err);
    pr_debug("Before STREAMON\n");
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
    {
        //errno_exit("VIDIOC_STREAMON");
        return -1;
    }        
    pr_debug("After STREAMON\n");
    return 0;
}
/**
 * @brief 
 * 
 * @param camera 
 * @param drm_bufs 
 */
static void uninit_device(struct camera_info *camera,struct drm_buffer *drm_bufs)
{
    unsigned int i;

    pr_debug("%s: called!\n", __func__);
    pthread_mutex_lock(&mutex);

    if(NULL != camera->buffers)
    {
        free(camera->buffers);
    }
    pthread_mutex_unlock(&mutex);
}
/**
 * @brief 
 * 
 * @param camera 
 */
static int init_mmap(struct camera_info *camera,struct drm_buffer *drm_bufs)  //（3）
{
    struct v4l2_requestbuffers req;
    int fd = camera->fd;
    struct buffer *buffers; 
    unsigned int     n_buffers;  
    char  dev_name[50];
    pr_debug("%s: called!\n", __func__);
    sprintf(&dev_name[0],"%s",&camera->video_name[0]);
    int ret = 0;
    CLEAR(req);

    req.count = BUFFERS_COUNT;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_DMABUF;//V4L2_MEMORY_MMAP; //drm

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support "
                 "memory mapping\n", dev_name);
            //exit(EXIT_FAILURE);
            return -errno;
        } else {
            //errno_exit("VIDIOC_REQBUFS");
            return -1;
        }
    }
    pr_debug("\treq.count: %d\n", req.count);
    pr_debug("\treq.type: %d\n", req.type);
    pr_debug("\treq.memory: %d\n", req.memory);
    pr_debug("\n");

    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n",
             dev_name);
        //exit(EXIT_FAILURE);
        return -1;
    }

    buffers = calloc(req.count, sizeof(*buffers));

    if (!buffers) {
        fprintf(stderr, "Out of memory\n");
        //exit(EXIT_FAILURE);
        return -1;
    }

	for(uint32_t i = 0; i < req.count; i++)
	{
		buffers[i].start = drm_bufs[i].map;//  buf_drm[i].vaddr;
		buffers[i].length = drm_bufs[i].size;
		buffers[i].dbuf_fd = drm_bufs[i].dbuf_fd;
	}
	n_buffers = req.count;
    //
    camera->buffers = buffers;
    camera->n_buffers = n_buffers;
    printf("%s:n_buffers(%d),buffers(%p)\n",__func__,camera->n_buffers,camera->buffers);
    return ret;
}
/**
 * @brief 
 * 
 * @param camera 
 * @param drm_bufs 
 */
static int init_device(struct camera_info *camera,struct drm_buffer *drm_bufs) //static表示次函数只能在本文件中调用
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;
    int fd = camera->fd;
    char dev_name[50];
    unsigned int width = camera->size.width;
    unsigned int height = camera->size.height;
    int ret = 0;

    sprintf(&dev_name[0],"%s",&camera->video_name[0]);

    pr_debug("%s: called!\n", __func__);
    printf("%s:width(%d),height(%d)\n",__func__,width,height);
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        pthread_mutex_unlock(&mutex);
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n",
                 dev_name);
            //exit(EXIT_FAILURE);
            return -errno;
        } else {
            //errno_exit("VIDIOC_QUERYCAP");
            return -1;
        }
    }

    pr_debug("\tdriver: %s\n"
         "\tcard: %s \n"
         "\tbus_info: %s\n",
            cap.driver, cap.card, cap.bus_info);
    pr_debug("\tversion: %u.%u.%u\n",
            (cap.version >> 16) & 0xFF,
            (cap.version >> 8) & 0xFF,
            cap.version & 0xFF);
    pr_debug("\tcapabilities: 0x%08x\n", cap.capabilities);

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf(stderr, "%s is no video capture device\n",
             dev_name);
        //exit(EXIT_FAILURE);
        return -1;
    }

    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    fmt.fmt.pix.width       = width;//FORCED_WIDTH;
    fmt.fmt.pix.height      = height;//FORCED_HEIGHT;
    fmt.fmt.pix.pixelformat = FORCED_FORMAT;
    fmt.fmt.pix.field       = FORCED_FIELD;

    pr_debug("\tfmt.fmt.pix.pixelformat: %c,%c,%c,%c\n",
            fmt.fmt.pix.pixelformat & 0xFF,
            (fmt.fmt.pix.pixelformat >> 8) & 0xFF,
            (fmt.fmt.pix.pixelformat >> 16) & 0xFF,
            (fmt.fmt.pix.pixelformat >> 24) & 0xFF
            );
    pr_debug("\n");

    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
    {
        //errno_exit("VIDIOC_S_FMT");
        return -errno; 
    }    
    /* Note VIDIOC_S_FMT may change width and height. */

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    ret = init_mmap(camera,drm_bufs);

    return ret;
}
/**
 * @brief 
 * 
 * @param camera 
 */
static void close_device(struct camera_info *camera)
{
    pr_debug("%s: called!\n", __func__);

    pthread_mutex_lock(&mutex);
    if(camera->fd)
    {
        if (-1 == close(camera->fd))
        {
            pthread_mutex_unlock(&mutex);
            errno_exit("close");
        }     
        camera->fd = -1; 
    }
#if 0
    if(drm_dev.fd &&(drm_dev.camera_num == 1) )
    {
        drm_exit(); 
    } 
    else
    {
        drm_dev.camera_num--;
    }   
#endif
    pthread_mutex_unlock(&mutex);  
}
/**
 * @brief 
 * 
 * @param camera 
 */
static void open_device(struct camera_info *camera)//
{
    struct stat st;
    int fd;
    char dev_name[50];
    sprintf(&dev_name[0],"%s",&camera->video_name[0]); 
    printf("%s: dev_name %s called!\n", __func__,&dev_name[0]);//_func_表示此时在那个函数里面

    if (-1 == stat(dev_name, &st)) {//获取文件信息
        fprintf(stderr, "Cannot identify '%s': %d, %s\n",
             dev_name, errno, strerror(errno));
        exit(EXIT_FAILURE);//非正常退出 EXIT_FAILURE=1， EXIT_SUCCSES=0 正常退出
    }

    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", dev_name);
        exit(EXIT_FAILURE);
    }

    fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);//非阻塞模式打开文件

    if (-1 == fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n",
             dev_name, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    camera->fd = fd;
    printf("%s:fd (%d) open\n",__func__,fd);
}
/**
 * @brief 
 * 
 * @param fp 
 * @param argc 
 * @param argv 
 */
static void usage(FILE *fp, int argc, char **argv)
{
    fprintf(fp,
         "Usage: %s [options]\n\n"
         "Version 1.3\n"
         "Options:\n"
         "-f | --device cfg name   Video device cfg name [%s]\n"
         "-h | --help          Print this message\n"
         "-v | --verbose       Verbose output\n"
         "",
         argv[0], video_cfg_file);
}

static const char short_options[] = "f:e:hv";// 短选项 ：表示带参数

static const struct option //长选项
long_options[] = {
    { "device_cfg name", required_argument, NULL, 'f' },
    { "ae config", required_argument, NULL, 'e' },
    { "help",   no_argument,       NULL, 'h' },
    { "verbose", no_argument,      NULL, 'v' },
    { 0, 0, 0, 0 }
};

/* end */
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
 * @param signo 
 */
void sighand(int signo) 
{ 
    pthread_t  tid = pthread_self(); 
   
    printf("Thread %lu in signal handler/n", tid); 
    return; 
}

int init_isp(struct camera_info *camera) {
    int ret = 0;
    open_device(camera);
    ret = init_device(camera, &drm_dev.drm_bufs[camera->buffer_start]); //BUFFERS_COUNT
    if(ret < 0) {
        uninit_device(camera, &drm_dev.drm_bufs[camera->buffer_start]);//BUFFERS_COUNT
        close_device(camera);
        return ret;
    }

    ret = start_capturing(camera);
    if(ret < 0) {
        stop_capturing(camera);
        uninit_device(camera,&drm_dev.drm_bufs[camera->buffer_start]);//BUFFERS_COUNT
        close_device(camera);
    }
    return ret;
}
void deinit_isp(struct camera_info *camera) {
    stop_capturing(camera);
    uninit_device(camera, &drm_dev.drm_bufs[camera->buffer_start]); //0
    close_device(camera);
}
/**
 * @brief 
 * 
 */
static void cfg_noc_prior(void)
{
    system("devmem 0x970E00f4 32 0x00000000");
    system("devmem 0x970E00f8 32 0x00000000");
    system("devmem 0x970E00fc 32 0x0fffff00");
    system("devmem 0x970E0100 32 0x00000000");
    system("devmem 0x970E0104 32 0x00000000");
}

/**
 * @brief 
 * 
 * @param __attribute__ 
 * @param __attribute__ 
 * @return int 
 */
int main(int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__)))
{
    struct video_info dev_info[2];
    struct camera_info camera[2];
    int i = 0;
    int camera_num = 0;
	struct sigaction actions;
	pthread_t f2k_pid,r2k_pid,drm_pid;

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
        case 'e': 
            isp_ae_status = atol(optarg);//dev_name = ;
            break;

        case 'f':
            video_cfg_file = optarg;//dev_name = optarg;
            break;

        case 'h':
            usage(stdout, argc, argv);
            exit(EXIT_SUCCESS);

        case 'v':
            verbose = 1;
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
    signal(SIGTERM, sigint_handler);
    //
    memset(&actions, 0, sizeof(actions)); 
    sigemptyset(&actions.sa_mask); /* 将参数set信号集初始化并清空 */ 
    actions.sa_flags = 0; 
    actions.sa_handler = sighand;   
    /* 设置SIGALRM的处理函数 */ 
    sigaction(SIGALRM,&actions,NULL); 
    //
    cfg_noc_prior();
    //media
    if(mediactl_init(video_cfg_file,&dev_info[0]))
        return -1;
    //drm
    printf("%s:dev_info[0].video_used(%d)\n",__func__,dev_info[0].video_used);
    if( 1 == dev_info[0].video_used )
    {
        for(i = 0;i < 3;i++)
        {
            if(1 == dev_info[0].enable[i])
            {
                sprintf(&camera[0].video_name[0],"%s",dev_info[0].video_name[i]);
                camera[0].size.width = dev_info[0].video_width[i];
                camera[0].size.height = dev_info[0].video_height[i];
                camera[0].buffer_start = 0;
                camera_num++;
            }
        }        
    }
    //
    printf("%s:dev_info[1].video_used(%d)\n",__func__,dev_info[1].video_used);
    if( 1 == dev_info[1].video_used )
    {
        for(i = 0;i < 3;i++)
        {
            if(1 == dev_info[1].enable[i])
            {
                sprintf(&camera[1].video_name[0],"%s",dev_info[1].video_name[i]);
                camera[1].size.width = dev_info[1].video_width[i];
                camera[1].size.height = dev_info[1].video_height[i];
                camera[1].buffer_start = BUFFERS_COUNT;
                camera_num++;
            }
        }        
    }
    //
    if(( 0 == dev_info[0].video_used ) && ( 1 == dev_info[1].video_used ))
    {
        camera[1].buffer_start = 0;//BUFFERS_COUNT;
    }
    // don't know why
    // camera[0].size.width = 1080;
    // camera[0].size.height = 1920;

    printf("%s:size[0].width is %d size[0].height is %d,size[1].width is %d size[1].height is %d,camera_num(%d)\n",__func__,camera[0].size.width,camera[0].size.height,camera[1].size.width,camera[1].size.height,camera_num);
    struct drm_size size[2];

    size[0].width = 1080;
    size[0].height = 1920;  
    size[1].width = 1080;
    size[1].height = 1920;

    if((1 == dev_info[0].video_used)&&(1 == dev_info[1].video_used))
    {
        size[0].src_offset_w = 0;
        size[0].src_offset_h = 200;
        size[0].crtc_offset_w = 0;
        size[0].crtc_offset_h = 200;  
        size[1].src_offset_w = 0;
        size[1].src_offset_h = 1000;
        size[1].crtc_offset_w = 0;
        size[1].crtc_offset_h = 1000;
    }
    else
    {
        size[0].src_offset_w = 0;
        size[0].src_offset_h = 0;
        size[0].crtc_offset_w = 0;
        size[0].crtc_offset_h = 0;  
        size[1].src_offset_w = 0;
        size[1].src_offset_h = 0;
        size[1].crtc_offset_w = 0;
        size[1].crtc_offset_h = 0;
    }

    drm_reset();
    if(drm_init(&size[0])){
        mediactl_exit();
        return -1;
    }

    drm_dev.camera_num = camera_num;
    struct camera_info* used_cam;

	if(dev_info[0].video_used) {
		if (init_isp(&camera[0]) < 0) {
			goto cleanup;
		}
        used_cam = &camera[0];
	}
	if(dev_info[1].video_used) {
		if (init_isp(&camera[1]) < 0) {
            goto cleanup;
		}
        used_cam = &camera[1];
	}

    if (dev_info[0].video_used && dev_info[1].video_used) {
        struct drm_buffer *fbuf1 = &drm_dev.drm_bufs[0];
        struct drm_buffer *fbuf2 = &drm_dev.drm_bufs[BUFFERS_COUNT];
        for (int i = 0; i < BUFFERS_COUNT; i++) {
            fbuf1[i].width = camera[0].size.width;
            fbuf1[i].height = camera[0].size.height;
            fbuf2[i].width = camera[1].size.width;
            fbuf2[i].height = camera[1].size.height; 
        }
    } else {
        struct drm_buffer *fbuf = &drm_dev.drm_bufs[0];
        for (int i = 0; i < BUFFERS_COUNT; i++) {
            fbuf[i].width = used_cam->size.width;
            fbuf[i].height = used_cam->size.height;
        }
    }
	fprintf(stderr, "start\n");

    fd_set fds, fds_with_drm;
    int max_fd = -1, max_fd_with_drm;
    unsigned bit_mask = 0, bit_mask_w;
    struct v4l2_buffer vbuf[2][2];
    unsigned vbuf_ptr[2] = {0, 0};
    FD_ZERO(&fds);

    // setup
    for (int i = 0; i < 2; i++) {
        if (dev_info[i].video_used) {
            FD_SET(camera[i].fd, &fds);
            max_fd = max_fd > camera[i].fd ? max_fd : camera[i].fd;
            bit_mask |= (1U << i);
        }
    }

    struct timeval tv = {
        .tv_sec = 5,
        .tv_usec = 0
    };
    // fill double buffer
    for (unsigned j = 0; j < 2; j++) {
        bit_mask_w = bit_mask;
        do {
            fd_set rfds = fds;
            int r = select(max_fd + 1, &rfds, NULL, NULL, &tv);
            if (r > 0) {
                for (unsigned i = 0; i < 2; i++) {
                    if (dev_info[i].video_used && FD_ISSET(camera[i].fd, &rfds)) {
                        if (readframe(camera[i].fd, &vbuf[j][i]) == -1) {
                            if (errno == EAGAIN) {
                                continue;
                            }
                            // error
                            perror("readframe() error");
                            goto cleanup;
                        }
                        #define DEBUG_VBUF_IDX 0
                        #if DEBUG_VBUF_IDX
                        fprintf(stderr, "> %d\n", vbuf[j][i].index);
                        #endif
                        // FIXME: should be (1U << (i - 1))
                        //if(isp_ae_status & (i + 1)) {
                        //    mediactl_set_ae(ISP_F2K_PIPELINE + i);
                        //}
                        bit_mask_w &= ~(1U << i);
                    }
                }
            } else if (r == 0) {
                // timeout
                fprintf(stderr, "camera select() timeout at line %d\n", __LINE__);
                goto cleanup;
            } else {
                // error
                perror("camera select() error");
                goto cleanup;
            }
        } while (bit_mask_w);
    }

    // display vbuf[0]
    if(dev_info[0].video_used && dev_info[1].video_used) {
        if (drm_dmabuf_set_2plane(
                &drm_dev.drm_bufs[vbuf[0][0].index],
                &drm_dev.drm_bufs[vbuf[0][1].index + BUFFERS_COUNT])) {
            printf("Flush fail\n");
            goto cleanup;
        }
    } 
    else if(dev_info[0].video_used) { 
        if (drm_dmabuf_set_plane(&drm_dev.drm_bufs[vbuf[0][0].index])) {
            printf("Flush fail\n");
            goto cleanup;
        }
    } else if(dev_info[1].video_used) {
        if (drm_dmabuf_set_plane(&drm_dev.drm_bufs[vbuf[0][1].index])) {
            printf("Flush fail\n");
            goto cleanup;
        }
    }
    // flip
    for (unsigned i = 0; i < 2; i++) {
        vbuf_ptr[i] ^= 1;
    }

    fds_with_drm = fds;
    FD_SET(drm_dev.fd, &fds_with_drm);
    max_fd_with_drm = max_fd > drm_dev.fd ? max_fd : drm_dev.fd;
    max_fd += 1;
    max_fd_with_drm += 1;
    bit_mask |= 0b100;
    fprintf(stderr, "start drm\n");
    #if DEBUG_VBUF_IDX
    unsigned used_index[2] = {vbuf[0][0].index, vbuf[0][1].index};
    #endif
    while (!done) {
        fd_set rfds = fds_with_drm;
        unsigned need_flip[2] = {0, 0};
        bit_mask_w = bit_mask;
        static uint32_t frame_counter = 0;
        frame_counter += 1;
        // FIXME
        do {
            tv.tv_sec = 5; // ???? if not, select() will timeout
            tv.tv_usec = 0;
            fd_set rrfds = rfds;
            int r = select(max_fd_with_drm, &rrfds, NULL, NULL, &tv);
            if (r > 0) {
                // camera
                for (unsigned i = 0; i < 2; i++) {
                    if (dev_info[i].video_used && FD_ISSET(camera[i].fd, &rrfds)) {
                        // QBUF last frame
                        #if DEBUG_VBUF_IDX
                        fprintf(stderr, "< %d\n", vbuf[vbuf_ptr[i]][i].index);
                        #endif
                        if (xioctl(camera[i].fd, VIDIOC_QBUF, &vbuf[vbuf_ptr[i]][i]) < 0) {
                            perror("camera VIDIOC_QBUF");
                            goto cleanup;
                        }
                        // DQBUF
                        if (readframe(camera[i].fd, &vbuf[vbuf_ptr[i]][i]) == 0) {
                            #if DEBUG_VBUF_IDX
                            fprintf(stderr, "> %d\n", vbuf[vbuf_ptr[i]][i].index);
                            #endif
                            //if(isp_ae_status & (i + 1)) {
                            //    mediactl_set_ae(ISP_F2K_PIPELINE + i);
                            //}
                            if (need_flip[i]) {
                                // frame droped
                                static uint32_t drop_frame_counter[2] = {0, 0};
                                pr_debug("camera %d drop a frame in %d frames\n", i, frame_counter - drop_frame_counter[i]);
                                drop_frame_counter[i] = frame_counter;
                            }
                            need_flip[i] = 1;
                            bit_mask_w &= ~(1 << i);
                        } else if (errno != EAGAIN) {
                            perror("camera DQBUF");
                            goto cleanup;
                        }
                    }
                }

                // drm
                if (FD_ISSET(drm_dev.fd, &rrfds)) {
                    drmHandleEvent(drm_dev.fd, &drm_dev.drm_event_ctx);
                    drmModeAtomicFree(drm_dev.req);
                    drm_dev.req = NULL;
                    bit_mask_w &= ~0b100;
                }
            } else if (r < 0) {
                if (errno == EINTR) {
                    continue;
                }
                perror("drm+cam select() error");
                goto cleanup;
            } else {
                fprintf(stderr, "drm+cam select() timeout, exit\n");
                goto cleanup;
            }
            if (done) {
                goto cleanup;
            }
        } while (bit_mask_w);
        if (done) {
            goto cleanup;
        }

        // fps stat
#define DEBUG_FPS 0
#if DEBUG_FPS
        static unsigned frames = 0;
        static uint32_t tm = 0;
        static unsigned last_tm_frame = 0;
        static unsigned fps = 0;
        frames += 1;
        if (time(NULL) - tm) {
            fps = frames - last_tm_frame;
            last_tm_frame = frames;
            tm = time(NULL);
        }
        fprintf(stderr, "display #%u\tfps: %u\tindex: %u\t%u\r", frames, fps, vbuf[vbuf_ptr[0]][0].index, vbuf[vbuf_ptr[1]][1].index);
#endif

        #if DEBUG_VBUF_IDX
        used_index[0] = vbuf[vbuf_ptr[0]][0].index;
        used_index[1] = vbuf[vbuf_ptr[1]][1].index;
        #endif

        // display
        if(dev_info[0].video_used && dev_info[1].video_used) {
            if (drm_dmabuf_set_2plane(
                    &drm_dev.drm_bufs[vbuf[vbuf_ptr[0]][0].index],
                    &drm_dev.drm_bufs[vbuf[vbuf_ptr[1]][1].index + BUFFERS_COUNT])) {
                printf("Flush fail\n");
                break;
            }
        } 
        else if(dev_info[0].video_used) { 
            if (drm_dmabuf_set_plane(&drm_dev.drm_bufs[vbuf[vbuf_ptr[0]][0].index])) {
                printf("Flush fail\n");
                break;
            }
        } else if(dev_info[1].video_used) {
            if (drm_dmabuf_set_plane(&drm_dev.drm_bufs[vbuf[vbuf_ptr[1]][1].index])) {
                printf("Flush fail\n");
                break;
            }
        }

        // FIXME: always flip
        for (unsigned i = 0; i < 2; i++) {
            vbuf_ptr[i] ^= 1;
        }
    }
cleanup:
    if(drm_dev.fd) {
        fprintf(stderr, "drm_exit\n");
        drm_exit(); 
    }
    if(dev_info[0].video_used) {
        deinit_isp(&camera[0]);
    }
    if(dev_info[1].video_used) {
        deinit_isp(&camera[1]);
    }
    mediactl_exit();
    return 0;
}
