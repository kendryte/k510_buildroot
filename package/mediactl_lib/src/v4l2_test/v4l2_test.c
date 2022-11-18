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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <linux/videodev2.h>

#include "media_ctl.h"

#define FORCED_WIDTH  1920
#define FORCED_HEIGHT 1080
#define FORCED_FORMAT V4L2_PIX_FMT_YUV420
#define FORCED_FIELD  V4L2_FIELD_ANY

static int verbose = 0;
#define pr_debug(fmt, arg...) \
    if (verbose) fprintf(stderr, fmt, ##arg)

#define CLEAR(x) memset(&(x), 0, sizeof(x)) //相当于CLEAR(x) =memset(&(x), 0, sizeof(x))

enum io_method {                           //枚举，即只能取其中的一个值。也是一种数据结构
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
};

struct buffer {
    void   *start;
    size_t  length;                    //size_t =unsigned int 用来表示sizeof的
};

static char            *dev_name;         //用来保存设备名
static enum io_method   io = IO_METHOD_MMAP;
static int              fd = -1;
struct buffer          *buffers;
static unsigned int     n_buffers;
static int        out_buf;
static int              force_format;
static int              frame_count = 50;
static char             *video_name="/root/data/video.yuv";
FILE *fp; //保存视频
//static unsigned int width;
//static unsigned int height;

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

static void process_image(const void *p, int size)
{
    pr_debug("%s: called! size %d\n", __func__, size);
         //采集视频
        fwrite(p,size,1,fp);//如果要查看采集视频的格式，在linux下可以通过安装v4l-utils,然后执行v4l2-ctl --all来查看视频采集的相关信息
            // 保存为一张张图片
      /*     FILE *fp;
    static int num = 1;
    char picture_name[20];

    sprintf(picture_name,"picture%d.jpg",num ++);

    if((fp = fopen(picture_name,"w")) == NULL)
    {
        perror("Fail to fopen");
        exit(EXIT_FAILURE);
    }

    fwrite(p,size,1,fp);
    usleep(500);

    fclose(fp);
                                 */

              // 打印到标准输出
    /*if (out_buf)
        fwrite(p, size, 1, stdout);

    fflush(stderr);
    fprintf(stderr, ".");
    fflush(stdout);
                           */


}

static int read_frame(void)
{
    struct v4l2_buffer buf;
    unsigned int i;

    pr_debug("%s: called!\n", __func__);

    switch (io) {
    case IO_METHOD_READ:

        break;

    case IO_METHOD_MMAP:
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
            switch (errno) {
            case EAGAIN:
                return 0;

            case EIO:
                /* Could ignore EIO, see spec. */

                /* fall through */

            default:
                errno_exit("VIDIOC_DQBUF");
            }
        }

        assert(buf.index < n_buffers);

        process_image(buffers[buf.index].start, buf.bytesused);

        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            errno_exit("VIDIOC_QBUF");
        break;

    case IO_METHOD_USERPTR:

        break;
    }

    return 1;
}

static void mainloop(void)
{
    unsigned int count;

    pr_debug("%s: called!\n", __func__);

    count = frame_count;

    while (count-- > 0) {
        for (;;) {
            fd_set fds;
            struct timeval tv;
            int r;

            FD_ZERO(&fds);
            FD_SET(fd, &fds);

            /* Timeout. */
            tv.tv_sec = 2;
            tv.tv_usec = 0;

            r = select(fd + 1, &fds, NULL, NULL, &tv);

            if (-1 == r) {
                if (EINTR == errno)
                    continue;
                errno_exit("select");
            }

            if (0 == r) {
                fprintf(stderr, "select timeout\n");
                exit(EXIT_FAILURE);
            }

            if (read_frame())
                break;
            /* EAGAIN - continue select loop. */
        }
    }
}

static void stop_capturing(void)
{
    enum v4l2_buf_type type;

    pr_debug("%s: called!\n", __func__);

    switch (io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;

    case IO_METHOD_MMAP: //会执行下面的
    case IO_METHOD_USERPTR:
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
            errno_exit("VIDIOC_STREAMOFF");
        break;
    }
}

static void start_capturing(void)
{
    unsigned int i;
    enum v4l2_buf_type type;
    int err;

    pr_debug("%s: called!\n", __func__);

    pr_debug("\tn_buffers: %d\n", n_buffers);

    switch (io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;

    case IO_METHOD_MMAP:
        for (i = 0; i < n_buffers; ++i) {
            struct v4l2_buffer buf;

            pr_debug("\ti: %d\n", i);

            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;

            pr_debug("\tbuf.index: %d\n", buf.index);

            err = xioctl(fd, VIDIOC_QBUF, &buf);
            pr_debug("\terr: %d\n", err);

            if (-1 == err)
                errno_exit("VIDIOC_QBUF");

            pr_debug("\tbuffer queued!\n");
        }

        pr_debug("Before STREAMON\n");
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
            errno_exit("VIDIOC_STREAMON");
        pr_debug("After STREAMON\n");
        break;

    case IO_METHOD_USERPTR:

        break;
    }
}

static void uninit_device(void)
{
    unsigned int i;

    pr_debug("%s: called!\n", __func__);

    switch (io) {
    case IO_METHOD_READ:
        free(buffers[0].start);
        break;

    case IO_METHOD_MMAP:
        for (i = 0; i < n_buffers; ++i)
            if (-1 == munmap(buffers[i].start, buffers[i].length))
                errno_exit("munmap");
        break;

    case IO_METHOD_USERPTR:
        for (i = 0; i < n_buffers; ++i)
            free(buffers[i].start);
        break;
    }

    free(buffers);
}

static void init_read(unsigned int buffer_size)
{
    pr_debug("%s: called!\n", __func__);

    buffers = calloc(1, sizeof(*buffers));

    if (!buffers) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    buffers[0].length = buffer_size;
    buffers[0].start = malloc(buffer_size);

    if (!buffers[0].start) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
}

static void init_mmap(void)  //（3）
{
    struct v4l2_requestbuffers req;

    pr_debug("%s: called!\n", __func__);

    CLEAR(req);

    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support "
                 "memory mapping\n", dev_name);
            exit(EXIT_FAILURE);
        } else {
            errno_exit("VIDIOC_REQBUFS");
        }
    }
    pr_debug("\treq.count: %d\n", req.count);
    pr_debug("\treq.type: %d\n", req.type);
    pr_debug("\treq.memory: %d\n", req.memory);
    pr_debug("\n");


    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n",
             dev_name);
        exit(EXIT_FAILURE);
    }

    buffers = calloc(req.count, sizeof(*buffers));

    if (!buffers) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = n_buffers;

        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
            errno_exit("VIDIOC_QUERYBUF");

        pr_debug("\tbuf.index: %d\n", buf.index);
        pr_debug("\tbuf.type: %d\n", buf.type);
        pr_debug("\tbuf.bytesused: %d\n", buf.bytesused);
        pr_debug("\tbuf.flags: %d\n", buf.flags);
        pr_debug("\tbuf.field: %d\n", buf.field);
        pr_debug("\tbuf.timestamp.tv_sec: %ld\n", (long) buf.timestamp.tv_sec);
        pr_debug("\tbuf.timestamp.tv_usec: %ld\n", (long) buf.timestamp.tv_usec);
        pr_debug("\tbuf.timecode.type: %d\n", buf.timecode.type);
        pr_debug("\tbuf.timecode.flags: %d\n", buf.timecode.flags);
        pr_debug("\tbuf.timecode.frames: %d\n", buf.timecode.frames);
        pr_debug("\tbuf.timecode.seconds: %d\n", buf.timecode.seconds);
        pr_debug("\tbuf.timecode.minutes: %d\n", buf.timecode.minutes);
        pr_debug("\tbuf.timecode.hours: %d\n", buf.timecode.hours);
        pr_debug("\tbuf.timecode.userbits: %d,%d,%d,%d\n",
                buf.timecode.userbits[0],
                buf.timecode.userbits[1],
                buf.timecode.userbits[2],
                buf.timecode.userbits[3]);
        pr_debug("\tbuf.sequence: %d\n", buf.sequence);
        pr_debug("\tbuf.memory: %d\n", buf.memory);
        pr_debug("\tbuf.m.offset: %d\n", buf.m.offset);
        pr_debug("\tbuf.length: %d\n", buf.length);
        //pr_debug("\tbuf.input: %d\n", buf.input);
        pr_debug("\n");

        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start =
            mmap(NULL /* start anywhere */,
                  buf.length,
                  PROT_READ | PROT_WRITE /* required */,
                  MAP_SHARED /* recommended */,
                  fd, buf.m.offset);

        if (MAP_FAILED == buffers[n_buffers].start)
            errno_exit("mmap");
    }
}


static void init_device(unsigned int width,unsigned int height) //static表示次函数只能在本文件中调用
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;

    pr_debug("%s: called!\n", __func__);

    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n",
                 dev_name);
            exit(EXIT_FAILURE);
        } else {
            errno_exit("VIDIOC_QUERYCAP");
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
        exit(EXIT_FAILURE);
    }




    /* Select video input, video standard and tune here. */


    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
        pr_debug("\tcropcap.type: %d\n", cropcap.type);
        pr_debug("\tcropcap.bounds.left: %d\n", cropcap.bounds.left);
        pr_debug("\tcropcap.bounds.top: %d\n", cropcap.bounds.top);
        pr_debug("\tcropcap.bounds.width: %d\n", cropcap.bounds.width);
        pr_debug("\tcropcap.bounds.height: %d\n", cropcap.bounds.height);

        pr_debug("\tcropcap.defrect.left: %d\n", cropcap.defrect.left);
        pr_debug("\tcropcap.defrect.top: %d\n", cropcap.defrect.top);
        pr_debug("\tcropcap.defrect.width: %d\n", cropcap.defrect.width);
        pr_debug("\tcropcap.defrect.height: %d\n", cropcap.defrect.height);

        pr_debug("\tcropcap.pixelaspect.numerator: %d\n", cropcap.pixelaspect.numerator);
        pr_debug("\tcropcap.pixelaspect.denominator: %d\n", cropcap.pixelaspect.denominator);
        pr_debug("\n");

        CLEAR(crop);
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
            switch (errno) {
            case EINVAL:
                /* Cropping not supported. */
                break;
            default:
                /* Errors ignored. */
                pr_debug("\tcropping not supported\n");
                break;
            }
        }
    } else {
        /* Errors ignored. */
    }


    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (force_format) {
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
            errno_exit("VIDIOC_S_FMT");

        /* Note VIDIOC_S_FMT may change width and height. */
    } else {
        /* Preserve original settings as set by v4l2-ctl for example */
        if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
            errno_exit("VIDIOC_G_FMT");

        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        pr_debug("\tfmt.fmt.pix.pixelformat: %c,%c,%c,%c\n",
                fmt.fmt.pix.pixelformat & 0xFF,
                (fmt.fmt.pix.pixelformat >> 8) & 0xFF,
                (fmt.fmt.pix.pixelformat >> 16) & 0xFF,
                (fmt.fmt.pix.pixelformat >> 24) & 0xFF
                );

    }

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    switch (io) {
    case IO_METHOD_READ:
        init_read(fmt.fmt.pix.sizeimage);
        break;

    case IO_METHOD_MMAP:
        init_mmap();
        break;

    case IO_METHOD_USERPTR:

        break;
    }
}

static void close_device(void)
{
    pr_debug("%s: called!\n", __func__);

    if (-1 == close(fd))
        errno_exit("close");

    fd = -1;
}

static void open_device(void)//
{
    struct stat st;

    pr_debug("%s: called!\n", __func__);//_func_表示此时在那个函数里面

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
}

static void usage(FILE *fp, int argc, char **argv)
{
    fprintf(fp,
         "Usage: %s [options]\n\n"
         "Version 1.3\n"
         "Options:\n"
         "-d | --device name   Video device name [%s]\n"
         "-h | --help          Print this message\n"
         "-m | --mmap          Use memory mapped buffers [default]\n"
         "-r | --read          Use read() calls\n"
         "-u | --userp         Use application allocated buffers\n"
         "-o | --output        Outputs stream to stdout\n"
         "-f | --format        Force format to 640x480 YUYV\n"
         "-c | --count         Number of frames to grab [%i]\n"
         "-v | --verbose       Verbose output\n"
         "-O | --output file   Output file full path[%s]\n"
         "-a | --anti-clicker-enable (0: all disable | 1: f 2k enable | 2: r 2k enable | 3: f&r 2k enable)\n"
         "-x | --ae sw/hw select (default 0: sw ae | 1: hw ae)\n"
         "-l | --adaptive enable (0: disable | 1: enable, default: enable)\n"
         "",
         argv[0], dev_name, frame_count, video_name);
}

static const char short_options[] = "d:hmruofc:vO:a:x:l:";// 短选项 ：表示带参数

static const struct option //长选项
long_options[] = {
    { "device", required_argument, NULL, 'd' },
    { "help",   no_argument,       NULL, 'h' },
    { "mmap",   no_argument,       NULL, 'm' },
    { "read",   no_argument,       NULL, 'r' },
    { "userp",  no_argument,       NULL, 'u' },
    { "output", no_argument,       NULL, 'o' },
    { "format", no_argument,       NULL, 'f' },
    { "count",  required_argument, NULL, 'c' },
    { "verbose", no_argument,      NULL, 'v' },
    { "ouput file",  required_argument, NULL, 'O' },
    { "anfi-flicker-enable", required_argument, NULL, 'a' },
    { "ae-select", required_argument, NULL, 'x' },
    { "adaptive", required_argument, NULL, 'l' },
    { 0, 0, 0, 0 }
};

/* end */

void set_isp_priority(void)
{
    /* set isp priority */
    system("devmem 0x970E00f4 32 0x00000000");
    system("devmem 0x970E00f8 32 0x00000000");
    system("devmem 0x970E00fc 32 0x0fffff00");
    system("devmem 0x970E0100 32 0x00000000");
    system("devmem 0x970E0104 32 0x00000000");
}

static char 	*video_cfg_file = "video_test.cfg";
int main(int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__)))
{
    dev_name = "/dev/video3";
    unsigned int width = FORCED_WIDTH;
    unsigned int height = FORCED_HEIGHT;
    struct video_info dev_info[2];

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

        case 'd':
            video_cfg_file = optarg;
            break;

        case 'h':
            usage(stdout, argc, argv);
            exit(EXIT_SUCCESS);

        case 'm':
            io = IO_METHOD_MMAP;
            break;

        case 'r':
            io = IO_METHOD_READ;
            break;

        case 'u':
            io = IO_METHOD_USERPTR;
            break;

        case 'o':
            out_buf++;
            break;

        case 'f':
            force_format++;
            break;

        case 'c':
            errno = 0;
            frame_count = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            break;

        case 'v':
            verbose = 1;
            break;
        case 'O':
            video_name = optarg;
            break;
        case 'a':
            anti_flicker_init(atoi(optarg));
            break;
        case 'l':
            adaptive_enable(atoi(optarg));
            break;
        default:
            usage(stderr, argc, argv);
            exit(EXIT_FAILURE);
        }
    }

    set_isp_priority();

    mediactl_init(video_cfg_file,&dev_info[0]);

    int i = 0;
    printf("%s:dev_info[0].video_used(%d)\n",__func__,dev_info[0].video_used);
    if( 1 == dev_info[0].video_used )
    {
        for(i = 0;i < 3;i++)
        {
            if(1 == dev_info[0].enable[0])
            {
                sprintf(dev_name,"%s",dev_info[0].video_name[i]);
                width = dev_info[0].video_width[i];
                height = dev_info[0].video_height[i];
            }
        }
    }
    //
    if( 1 == dev_info[1].video_used )
    {
        for(i = 0;i < 3;i++)
        {
            if(1 == dev_info[1].enable[0])
            {
                sprintf(dev_name,"%s",dev_info[1].video_name[i]);
                width = dev_info[1].video_width[i];
                height = dev_info[1].video_height[i];
            }
        }
    }

	if((fp = fopen(video_name,"wa+")) == NULL)
    {
        perror("Fail to fopen");
        exit(EXIT_FAILURE);
    }

    open_device();
    init_device(width,height);
    start_capturing();
    mainloop();
    stop_capturing();
    uninit_device();
    close_device();
    mediactl_exit();
    fprintf(stderr, "\n");
    return 0;
}
