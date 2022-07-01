/* Copyright 2022 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
  File Name     : kd_vi.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <linux/videodev2.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "kd_vi.h"
#include "kd_vi_log.h"
#include "media_ctl.h"
#include "kd_vi_list.h"

#define MAX_VI_DEV_NUM 2
#define SENSOR_CONFIG "vi_device.conf"
#define BUFFERS_COUNT	4
#define CLEAR(x) memset(&(x), 0, sizeof(x))


struct v4l2_video_buffer
{
	unsigned int index;
	unsigned int size;
	unsigned int bytesused;
	bool error;
	void *mem;
};

struct v4l2_ival_desc {
	struct v4l2_fract min;
	struct v4l2_fract max;
	struct v4l2_fract step;

	struct list_entry list;
};

struct v4l2_frame_desc {
	unsigned int min_width;
	unsigned int min_height;
	unsigned int max_width;
	unsigned int max_height;
	unsigned int step_width;
	unsigned int step_height;

	struct list_entry list;
	struct list_entry ivals;
};

struct v4l2_format_desc {
	unsigned int pixelformat;

	struct list_entry list;
	struct list_entry frames;
};

struct v4l2_device
{
	int fd;

	enum v4l2_buf_type type;
	enum v4l2_memory memtype;

	struct list_entry formats;
	struct v4l2_pix_format format;

	unsigned int nbufs;
	struct v4l2_video_buffer *buffers;
};

typedef struct kdVI_HANDLE_S
{
    struct v4l2_buffer  stBuf;
    struct v4l2_device *vdev;
    struct v4l2_pix_format format;
    struct v4l2_video_buffer buffer;
    KD_S32              maxfd;
    fd_set              fds;
} VI_SUB_PIPE_HANDLE_S;

static VI_SUB_PIPE_HANDLE_S *pViSubPipeHandle[MAX_SUB_PIPE_NUM] = {NULL};
static struct video_info dev_info[2];

static KD_S32 xioctl(int fh, int request, void *arg)
{
    int r;

    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
}

static KD_VOID v4l2_close(struct v4l2_device *dev)
{
    struct v4l2_format_desc *format, *next_fmt;
	struct v4l2_frame_desc *frame, *next_frm;
	struct v4l2_ival_desc *ival, *next_ival;

    if (dev == NULL)
        return;

    list_for_each_entry_safe(format, next_fmt, &dev->formats, list)
    {
		list_for_each_entry_safe(frame, next_frm, &format->frames, list)
        {
			list_for_each_entry_safe(ival, next_ival, &frame->ivals, list)
            {
				free(ival);
			}
			free(frame);
		}
		free(format);
	}

    free(dev->buffers);
    close(dev->fd);
    free(dev);
}

static KD_S32 v4l2_enum_frame_intervals(struct v4l2_device *dev, struct v4l2_format_desc *format, struct v4l2_frame_desc *frame)
{
    struct v4l2_ival_desc *ival;
	unsigned int i;
	int ret;

    for (i = 0; ; ++i)
    {
        struct v4l2_frmivalenum ivalenum;

		memset(&ivalenum, 0, sizeof(ivalenum));
		ivalenum.index = i;
		ivalenum.pixel_format = format->pixelformat;
		ivalenum.width = frame->min_width;
		ivalenum.height = frame->min_height;
		ret = ioctl(dev->fd, VIDIOC_ENUM_FRAMEINTERVALS, &ivalenum);
		if (ret < 0)
            break;

        if (i != ivalenum.index)
			KD_VI_LOG_DEBUG("%s: driver returned wrong ival index.\n", __func__);
		if (format->pixelformat != ivalenum.pixel_format)
			KD_VI_LOG_DEBUG("%s: driver returned wrong ival pixel.\n", __func__);
		if (frame->min_width != ivalenum.width)
			KD_VI_LOG_DEBUG("%s: driver returned wrong ival width.\n", __func__);
		if (frame->min_height != ivalenum.height)
			KD_VI_LOG_DEBUG("%s: driver returned wrong ival height.\n", __func__);

        ival = malloc(sizeof(*ival));
		if (ival == NULL)
			return KD_FAILURE;

        memset(ival, 0, sizeof(*ival));

        switch (ivalenum.type)
        {
		    case V4L2_FRMIVAL_TYPE_DISCRETE:
            {
                ival->min = ivalenum.discrete;
			    ival->max = ivalenum.discrete;
			    ival->step.numerator = 1;
			    ival->step.denominator = 1;
			    break;
            }
		    case V4L2_FRMIVAL_TYPE_STEPWISE:
            {
                ival->min = ivalenum.stepwise.min;
			    ival->max = ivalenum.stepwise.max;
			    ival->step = ivalenum.stepwise.step;
			    break;
            }
		    default:
            {
                KD_VI_LOG_ERROR("%s: driver returned invalid frame ival.\n", __func__);
			    return KD_FAILURE;
            }
		}
        list_append(&frame->ivals, &ival->list);
    }

    return 0;
}

static KD_S32 v4l2_enum_frame_sizes(struct v4l2_device *dev, struct v4l2_format_desc *format)
{
    struct v4l2_frame_desc *frame;
    unsigned int i;
    int ret;

    for (i = 0; ; ++i)
    {
        struct v4l2_frmsizeenum frmenum;

        memset(&frmenum, 0, sizeof(frmenum));
        frmenum.index = i;
        frmenum.pixel_format = format->pixelformat;

        ret = ioctl(dev->fd, VIDIOC_ENUM_FRAMESIZES, &frmenum);
        if (ret < 0)
            break;
        
        if (i != frmenum.index)
        {
            KD_VI_LOG_DEBUG("%s: return wrong frame index.\n", __func__);
        }
        if (format->pixelformat != frmenum.pixel_format)
        {
            KD_VI_LOG_DEBUG("%s: return wrong frame pixel format.\n", __func__);
        }

        frame = malloc(sizeof(*frame));
        if (frame == NULL)
        {
            return KD_FAILURE;
        }

        memset(frame, 0, sizeof(*frame));

        list_init(&frame->ivals);
        frame->step_width = 1;
        frame->step_height = 1;

        switch (frmenum.type)
        {
            case V4L2_FRMSIZE_TYPE_DISCRETE:
            {
                frame->min_width = frmenum.discrete.width;
			    frame->min_height = frmenum.discrete.height;
			    frame->max_width = frmenum.discrete.width;
			    frame->max_height = frmenum.discrete.height;
			    break;
            }
            case V4L2_FRMSIZE_TYPE_STEPWISE:
            {
                frame->step_width = frmenum.stepwise.step_width;
			    frame->step_height = frmenum.stepwise.step_height;
                break;
            }
            case V4L2_FRMSIZE_TYPE_CONTINUOUS:
            {
                frame->min_width = frmenum.stepwise.min_width;
			    frame->min_height = frmenum.stepwise.min_height;
			    frame->max_width = frmenum.stepwise.max_width;
			    frame->max_height = frmenum.stepwise.max_height;
			    break;
            }
            default:
            {
                KD_VI_LOG_ERROR("%s: return invalid frame size.\n", __func__);
                return KD_FAILURE;
            }
        }

        list_append(&format->frames, &frame->list);

        ret = v4l2_enum_frame_intervals(dev, format, frame);
        if (ret < 0)
        {
            return ret;
        }
    }

    return 0;
}

static KD_S32 v4l2_enum_formats(struct v4l2_device *dev)
{
    struct v4l2_format_desc *format;
    KD_U32 i;
    int ret;

    for (i = 0; ; ++i)
    {
        struct v4l2_fmtdesc fmtenum;
        memset(&fmtenum, 0, sizeof(fmtenum));

        fmtenum.index = i;
        fmtenum.type = dev->type;

        ret = ioctl(dev->fd, VIDIOC_ENUM_FMT, &fmtenum);
        if (ret < 0)
        {
            break;
        }

        if (i != fmtenum.index)
        {
            KD_VI_LOG_DEBUG("%s: return wrong format index.\n", __func__);
        }
        if (dev->type != fmtenum.type)
        {
            KD_VI_LOG_DEBUG("%s: return wrong format type.\n", __func__);
        }

        format = malloc(sizeof(*format));
        if (format == NULL)
        {
            return KD_FAILURE;
        }

        memset(format, 0, sizeof(*format));

        list_init(&format->frames);
        format->pixelformat = fmtenum.pixelformat;

        list_append(&dev->formats, &format->list);

        ret = v4l2_enum_frame_sizes(dev, format);
        if (ret < 0)
        {
            return ret;
        }
    }

    return 0;
}

static struct v4l2_device *v4l2_open(const char *devname)
{
    struct v4l2_device *dev;
    struct v4l2_capability cap;
    int ret;

    dev = malloc(sizeof(*dev));
    if (dev == NULL)
    {
        KD_VI_LOG_ERROR("%s: open v4l2 failed.\n", __func__);
        return NULL;
    }

    memset(dev, 0, sizeof(*dev));
    dev->fd = -1;
    dev->buffers = NULL;
    list_init(&dev->formats);

    dev->fd = open(devname, O_RDWR | O_NONBLOCK);
    if (dev->fd < 0)
    {
        KD_VI_LOG_ERROR("%s: open vi device failed.\n", __func__);
        v4l2_close(dev);
        return NULL;
    }

    memset(&cap, 0, sizeof(cap));
    ret = ioctl(dev->fd, VIDIOC_QUERYCAP, &cap);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: unable to query cap.\n", __func__);
        v4l2_close(dev);
        return NULL;
    }

    if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
    {
        dev->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    }
    else if (cap.capabilities & V4L2_CAP_VIDEO_OUTPUT)
    {
        dev->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    }
    else
    {
        KD_VI_LOG_ERROR("%s: neither video capture nor video output.\n", __func__);
        v4l2_close(dev);
        return NULL;
    }

    ret = v4l2_enum_formats(dev);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: unable to enumerate formats.\n", __func__);
        v4l2_close(dev);
        return NULL;
    }

    return dev;
}

static KD_S32 v4l2_set_format(struct v4l2_device *dev, struct v4l2_pix_format *format)
{
	struct v4l2_format fmt;
	int ret;
	printf("%s: dev->type %d dev->fd %d  start\n", __func__,dev->type,dev->fd);
	memset(&fmt, 0, sizeof(fmt));
	fmt.type = dev->type;
	fmt.fmt.pix.width = format->width;
	fmt.fmt.pix.height = format->height;
	fmt.fmt.pix.pixelformat = format->pixelformat;
	fmt.fmt.pix.field = V4L2_FIELD_ANY;
	//fmt.fmt.pix_mp.num_planes = 2;

	ret = ioctl(dev->fd, VIDIOC_S_FMT, &fmt);
	if (ret < 0) {
		KD_VI_LOG_ERROR("%s: Unable to set format.\n", __func__);
		return -1;
	}

	dev->format = fmt.fmt.pix;
	*format = fmt.fmt.pix;

	return 0;
}

static KD_S32 v4l2_alloc_buffers(struct v4l2_device *dev, enum v4l2_memory memtype, unsigned int nbufs)
{
    struct v4l2_requestbuffers rb;
	struct v4l2_buffer buf;
	struct v4l2_video_buffer *buffers;
	struct v4l2_plane* planes_buffer;
	unsigned int i;
	int ret;
	unsigned int num_planes = 1;

    dev->memtype = memtype;
    memset(&rb, 0, sizeof(rb));
	rb.count = nbufs;
	rb.type = dev->type;
	rb.memory = dev->memtype;

    ret = ioctl(dev->fd, VIDIOC_REQBUFS, &rb);
	if (ret < 0) {
		KD_VI_LOG_ERROR("%s: Unable to request buffers: %d.\n", __func__);
		return -1;
	}

    buffers = malloc(rb.count * sizeof(buffers[0]));
	if (buffers == NULL)
		return -1;

    for (i = 0; i < rb.count; ++i)
    {
        memset(&buf, 0, sizeof(buf));
        buf.index = i;
		buf.type = dev->type;
		buf.memory = dev->memtype;

        ret = ioctl(dev->fd, VIDIOC_QUERYBUF, &buf);
		if (ret < 0) {
			KD_VI_LOG_ERROR("%s,Unable to query buffer.\n",__func__);
			return -1;
		}

        switch (dev->memtype)
        {
            case V4L2_MEMORY_MMAP:
            {
                buffers[i].mem = mmap(0,buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, dev->fd, buf.m.offset);
			    if (buffers[i].mem == MAP_FAILED)
                {
				    KD_VI_LOG_ERROR("%s: Unable to map buffer.\n", __func__);
				    return -1;
			    }
			    buffers[i].size = buf.length;
			    break;
            }
            case V4L2_MEMORY_USERPTR:
            {
                buffers[i].mem = NULL;
			    buffers[i].size = buf.length;
			    break;
            }
            default:
                break;
        }
    }

    dev->buffers = buffers;
    dev->nbufs = rb.count;

    return 0;
}

static KD_S32 video_setup(struct v4l2_device *vdev,struct v4l2_pix_format *format)
{
    int ret;
    ret = v4l2_set_format(vdev, format);
    if (ret < 0)
	{
		KD_VI_LOG_ERROR("%s:v4l2_set_format error\n",__func__);
		return ret;
	}

    ret = v4l2_alloc_buffers(vdev, V4L2_MEMORY_MMAP, BUFFERS_COUNT);//V4L2_MEMORY_USERPTR, V4L2_MEMORY_MMAP
	if (ret < 0)
	{
		KD_VI_LOG_ERROR("%s:v4l2_alloc_buffers error\n",__func__);
		return ret;
	}

    return 0;
}

static KD_S32 v4l2_free_buffers(struct v4l2_device *vdev)
{
    struct v4l2_requestbuffers rb;
	unsigned int i;
	int ret;

	if (vdev->nbufs == 0)
		return 0;

    if (vdev->memtype == V4L2_MEMORY_MMAP) {
		for (i = 0; i < vdev->nbufs; ++i) {
			ret = munmap(vdev->buffers[i].mem, vdev->buffers[i].size);
			if (ret < 0) {
				KD_VI_LOG_ERROR("%s: Unable to unmap buffer.\n", __func__);
				return -1;
			}
		}
	}

    memset(&rb, 0, sizeof rb);
	rb.count = 0;
	rb.type = vdev->type;
	rb.memory = vdev->memtype;

    ret = ioctl(vdev->fd, VIDIOC_REQBUFS, &rb);
	if (ret < 0) {
		KD_VI_LOG_ERROR("%s: Unable to release buffers.\n", __func__);
		return -1;
	}

    free(vdev->buffers);
	vdev->nbufs = 0;
	vdev->buffers = NULL;

    return 0;
}

static KD_VOID video_cleanup(struct v4l2_device *vdev)
{
    if (vdev)
    {
        v4l2_free_buffers(vdev);
        v4l2_close(vdev);
    }
}

static KD_S32 v4l2_queue_buffer(struct v4l2_device *dev, struct v4l2_video_buffer *buffer)
{
    struct v4l2_buffer buf;
	int ret;

	if (buffer->index >= dev->nbufs)
		return -1;

    memset(&buf, 0, sizeof(buf));
	buf.index = buffer->index;
	buf.type = dev->type;
	buf.memory = dev->memtype;

    if (dev->memtype == V4L2_MEMORY_USERPTR) {
		buf.m.userptr = (unsigned long)buffer->mem;
		buf.length = buffer->size;
	} else {
		buf.length = dev->buffers[buffer->index].size;
	}

    if (dev->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		buf.bytesused = buffer->bytesused;

	if (dev->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		buf.bytesused = buffer->bytesused;

	ret = ioctl(dev->fd, VIDIOC_QBUF, &buf);
	if (ret < 0) {
		KD_VI_LOG_ERROR("%s: Unable to queue buffer.\n", __func__);
		return -1;
	}

    return 0;
}

static KD_S32 v4l2_stream_on(struct v4l2_device *dev)
{
	int type = dev->type;
	int ret;

	ret = ioctl(dev->fd, VIDIOC_STREAMON, &type);
	if (ret < 0)
		return -1;

	return 0;
}

static KD_S32 v4l2_dequeue_buffer(struct v4l2_device *dev, struct v4l2_video_buffer *buffer)
{
    struct v4l2_buffer buf;
	int ret;

	memset(&buf, 0, sizeof(buf));
	buf.type = dev->type;
	buf.memory = dev->memtype;

    ret = ioctl(dev->fd, VIDIOC_DQBUF, &buf);
	if (ret < 0) {
		KD_VI_LOG_ERROR("%s: Unable to dequeue buffer.\n", __func__);
		return -1;
	}

    *buffer = dev->buffers[buf.index];
	buffer->index = buf.index;
	buffer->bytesused = buf.bytesused;
	buffer->error = !!(buf.flags & V4L2_BUF_FLAG_ERROR);

    return 0;
}

static KD_S32 getFrame(VI_PIPE ViPipe, VIDEO_FRAME_INFO_S *pstFrame, struct v4l2_device *vdev, struct v4l2_pix_format *format)
{
	int ret;

    memset(&pViSubPipeHandle[ViPipe]->buffer, 0, sizeof(struct v4l2_video_buffer));

	unsigned int width = format->width;
	unsigned int height = format->height;

    ret = v4l2_dequeue_buffer(vdev, &pViSubPipeHandle[ViPipe]->buffer);
	if (ret < 0) {
		KD_VI_LOG_ERROR("%s: unable to dequeue buffer.\n", __func__);
		return ret;
	}

    if (pViSubPipeHandle[ViPipe]->buffer.error) {
		KD_VI_LOG_ERROR("%s: error in dequeued buffer, skipping\n", __func__);
		return -1;
	}

    switch (format->pixelformat)
    {
        case V4L2_PIX_FMT_NV12:
        {
            pstFrame->enPixelFormat = PIXEL_FORMAT_NV12;
            break;
        }
        case V4L2_PIX_FMT_NV16:
        {
            pstFrame->enPixelFormat = PIXEL_FORMAT_YUV422SP;
            break;
        }
        case V4L2_PIX_FMT_ABGR32:
        {
            pstFrame->enPixelFormat = PIXEL_FORMAT_ARGB;
            break;
        }
        case V4L2_PIX_FMT_RGB24:
        {
            pstFrame->enPixelFormat = PIXEL_FORMAT_RGB888;
            break;
        }
        default:
        {
            KD_VI_LOG_ERROR("%s: sub pipe %d get frame not support pixformat.\n", __func__, ViPipe);
            return KD_FAILURE;
        }
    }

    pstFrame->u32Width = (width + 0xf) & (~0xf);
    pstFrame->u32Height = height;
    pstFrame->u64VirData = (KD_U64)pViSubPipeHandle[ViPipe]->buffer.mem;
    pstFrame->u32DataSize = pViSubPipeHandle[ViPipe]->buffer.bytesused;

    return 0;
}

static KD_S32 v4l2_stream_off(struct v4l2_device *dev)
{
    int type = dev->type;
	int ret;

	ret = ioctl(dev->fd, VIDIOC_STREAMOFF, &type);
	if (ret < 0)
		return -1;

	return 0;
}

KD_S32  KD_MPI_VI_Init()
{
    initLog();

    mediactl_init(SENSOR_CONFIG, &dev_info[0]);

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_GetDevAttr(VI_DEV ViDev, VI_DEV_ATTR_S *pstDevAttr)
{
    if (ViDev < 0 || ViDev >= MAX_VI_DEV_NUM)
    {
        KD_VI_LOG_ERROR("%s: the vi device number %d is out of range.\n", __func__, ViDev);
        return KD_FAILURE;
    }

    if (dev_info[ViDev].video_used)
    {
        for (int subIdx = 0; subIdx < MAX_SUB_PIPE_NUM; subIdx++)
        {
            pstDevAttr->subDevName[subIdx] = dev_info[ViDev].video_name[subIdx];
            pstDevAttr->u32SubDevEnabled[subIdx] = dev_info[ViDev].enable[subIdx];
            pstDevAttr->u32SubDevWidth[subIdx] = dev_info[ViDev].video_width[subIdx];
            pstDevAttr->u32SubDevHeight[subIdx] = dev_info[ViDev].video_height[subIdx];
            if (dev_info[ViDev].video_out_format[subIdx] == 1)
            {
                pstDevAttr->enSubDevPixFmt[subIdx] = PIXEL_FORMAT_NV12;
                if (subIdx == 3)
                {
                    pstDevAttr->enSubDevPixFmt[subIdx] = PIXEL_FORMAT_ARGB;
                }
            }
            else
            {
                pstDevAttr->enSubDevPixFmt[subIdx] = PIXEL_FORMAT_YUV422SP;
                if (subIdx == 3)
                {
                     pstDevAttr->enSubDevPixFmt[subIdx] = PIXEL_FORMAT_RGB888;
                }
            }
        }
    }
    else
    {
        KD_VI_LOG_ERROR("%s: the %d vi device is not enable.\n", __func__, ViDev);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_CreateSubPipe(VI_PIPE ViPipe, const VI_SUB_PIPE_ATTR_S *pstSubPipeAttr)
{
    if (ViPipe < 0 || ViPipe >= MAX_SUB_PIPE_NUM)
    {
        KD_VI_LOG_ERROR("%s: the vi sub device number %d is out of range.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    if (pViSubPipeHandle[ViPipe] == NULL)
    {
        pViSubPipeHandle[ViPipe] = (VI_SUB_PIPE_HANDLE_S *)calloc(1, sizeof(VI_SUB_PIPE_HANDLE_S));
        if (!pViSubPipeHandle[ViPipe])
        {
            KD_VI_LOG_ERROR("%s: the vi sub pipe %d handle createm failed.\n", __func__, ViPipe);
            return KD_FAILURE;
        }
    }

    pViSubPipeHandle[ViPipe]->vdev = v4l2_open(pstSubPipeAttr->subDevName);
    if (pViSubPipeHandle[ViPipe]->vdev == NULL)
    {
        KD_VI_LOG_ERROR("%s: the sub piple %d open failed.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    memset(&pViSubPipeHandle[ViPipe]->format, 0, sizeof(struct v4l2_pix_format));

    pViSubPipeHandle[ViPipe]->format.width = pstSubPipeAttr->u32Width;
    pViSubPipeHandle[ViPipe]->format.height = pstSubPipeAttr->u32Height;
    switch (pstSubPipeAttr->enPixFmt)
    {
        case PIXEL_FORMAT_NV12:
        {
            pViSubPipeHandle[ViPipe]->format.pixelformat = V4L2_PIX_FMT_NV12;
            break;
        }
        case PIXEL_FORMAT_YUV422SP:
        {
            pViSubPipeHandle[ViPipe]->format.pixelformat = V4L2_PIX_FMT_NV16;
            break;
        }
        case PIXEL_FORMAT_ARGB:
        {
            pViSubPipeHandle[ViPipe]->format.pixelformat = V4L2_PIX_FMT_ABGR32;
            break;
        }
        case PIXEL_FORMAT_RGB888:
        {
            pViSubPipeHandle[ViPipe]->format.pixelformat = V4L2_PIX_FMT_RGB24;
            break;
        }
        default:
        {
            KD_VI_LOG_ERROR("%s: sub pipe %d not support pixformat %d.\n", __func__, ViPipe, pstSubPipeAttr->enPixFmt);
            return KD_FAILURE;
        }
    }
    
    int ret = video_setup(pViSubPipeHandle[ViPipe]->vdev, &pViSubPipeHandle[ViPipe]->format);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: sub pipe %d set up failed.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    FD_ZERO(&pViSubPipeHandle[ViPipe]->fds);
    FD_SET(pViSubPipeHandle[ViPipe]->vdev->fd, &pViSubPipeHandle[ViPipe]->fds);

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_StartSubPipe(VI_PIPE ViPipe)
{
    if (ViPipe < 0 || ViPipe >= MAX_SUB_PIPE_NUM)
    {
        KD_VI_LOG_ERROR("%s: the vi sub pipe %d is out of range.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    int ret;
    struct v4l2_video_buffer buffer;
    for (int i = 0; i < pViSubPipeHandle[ViPipe]->vdev->nbufs; i++)
    {
        buffer.index = i;
        ret = v4l2_queue_buffer(pViSubPipeHandle[ViPipe]->vdev, &buffer);
        if (ret < 0)
        {
            KD_VI_LOG_ERROR("%s: sub pipe %d queue buffer failed.\n", __func__, ViPipe);
            return KD_FAILURE;
        }
    }

    ret = v4l2_stream_on(pViSubPipeHandle[ViPipe]->vdev);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: sub pipe %d start failed.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_GetSubPipeFrame(VI_PIPE ViPipe, VIDEO_FRAME_INFO_S *pstVideoFrame, KD_S32 s32MilliSec)
{
    if (ViPipe < 0 || ViPipe >= MAX_SUB_PIPE_NUM)
    {
        KD_VI_LOG_ERROR("%s: the vi sub pipe %d is out of range.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    if (pstVideoFrame == NULL)
    {
        KD_VI_LOG_ERROR("%s: video frame is null.\n", __func__);
        return KD_FAILURE;
    }

    fd_set rfds;
    struct timeval timeout;

    if (s32MilliSec <= 0)
    {
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
    }
    else
    {
        timeout.tv_sec = 0;
        timeout.tv_usec = s32MilliSec * 1000;
    }

    rfds = pViSubPipeHandle[ViPipe]->fds;
    int ret = select(pViSubPipeHandle[ViPipe]->vdev->fd + 1, &rfds, NULL, NULL, &timeout);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: sub pipe %d get frame failed.\n", __func__, ViPipe);
        return KD_FAILURE;
    }
    else if (0 == ret)
    {
        KD_VI_LOG_ERROR("%s: sub pipe %d get frame timeout.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    if (FD_ISSET(pViSubPipeHandle[ViPipe]->vdev->fd, &rfds))
    {
        ret = getFrame(ViPipe, pstVideoFrame, pViSubPipeHandle[ViPipe]->vdev, &pViSubPipeHandle[ViPipe]->format);
        if (ret < 0)
        {
            KD_VI_LOG_ERROR("%s: get frame failed.\n", __func__);
            return KD_FAILURE;
        }
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_ReleaseSubPipeFrame(VI_PIPE ViPipe, VIDEO_FRAME_INFO_S *pstVideoFrame)
{
    if (ViPipe < 0 || ViPipe >= MAX_SUB_PIPE_NUM)
    {
        KD_VI_LOG_ERROR("%s: the sub pipe %d is out of range.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    if (pstVideoFrame == NULL)
    {
        KD_VI_LOG_ERROR("%s: the frame is null.\n", __func__);
        return KD_FAILURE;
    }

    int ret;

    ret = v4l2_queue_buffer(pViSubPipeHandle[ViPipe]->vdev, &pViSubPipeHandle[ViPipe]->buffer);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: sub pipe %d release frame buffer failed.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_StopSubPipe(VI_PIPE ViPipe)
{
    if (ViPipe < 0 || ViPipe >= MAX_SUB_PIPE_NUM)
    {
        KD_VI_LOG_ERROR("%s: the vi sub pipe %d is out of range.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    int ret = v4l2_stream_off(pViSubPipeHandle[ViPipe]->vdev);
    if (ret < 0)
    {
        KD_VI_LOG_ERROR("%s: sub pipe %d stop failed.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_DestroySubPipe(VI_PIPE ViPipe)
{
    if (ViPipe < 0 || ViPipe >= MAX_SUB_PIPE_NUM)
    {
        KD_VI_LOG_ERROR("%s: the vi sub pipe %d is out of range.\n", __func__, ViPipe);
        return KD_FAILURE;
    }

    video_cleanup(pViSubPipeHandle[ViPipe]->vdev);

    if (pViSubPipeHandle[ViPipe])
    {
        free(pViSubPipeHandle[ViPipe]);
        pViSubPipeHandle[ViPipe] = NULL;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VI_Deinit()
{
    mediactl_exit();

    return KD_SUCCESS;
}