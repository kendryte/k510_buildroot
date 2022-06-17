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

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>

#include <linux/videodev2.h>

//#include "list.h"
//#include "tools.h"
#include "v4l2.h"

#ifndef V4L2_BUF_FLAG_ERROR
#define V4L2_BUF_FLAG_ERROR	0x0040
#endif

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
/* -----------------------------------------------------------------------------
 * Formats enumeration
 *-----------------------------------------------------------------------------*/
/**
 * @brief 
 * 
 * @param dev 
 * @param format 
 * @param frame 
 * @return int 
 */
static int
v4l2_enum_frame_intervals(struct v4l2_device *dev, struct v4l2_format_desc *format,
	struct v4l2_frame_desc *frame)
{
	struct v4l2_ival_desc *ival;
	unsigned int i;
	int ret;
	printf("%s: start\n", __func__);
	for (i = 0; ; ++i) {
		struct v4l2_frmivalenum ivalenum;

		memset(&ivalenum, 0, sizeof ivalenum);
		ivalenum.index = i;
		ivalenum.pixel_format = format->pixelformat;
		ivalenum.width = frame->min_width;
		ivalenum.height = frame->min_height;
		ret = ioctl(dev->fd, VIDIOC_ENUM_FRAMEINTERVALS, &ivalenum);
		if (ret < 0)
			break;

		if (i != ivalenum.index)
			printf("Warning: driver returned wrong ival index "
				"%u.\n", ivalenum.index);
		if (format->pixelformat != ivalenum.pixel_format)
			printf("Warning: driver returned wrong ival pixel "
				"format %08x.\n", ivalenum.pixel_format);
		if (frame->min_width != ivalenum.width)
			printf("Warning: driver returned wrong ival width "
				"%u.\n", ivalenum.width);
		if (frame->min_height != ivalenum.height)
			printf("Warning: driver returned wrong ival height "
				"%u.\n", ivalenum.height);

		ival = malloc(sizeof *ival);
		if (ival == NULL)
			return -ENOMEM;

		memset(ival, 0, sizeof *ival);

		switch (ivalenum.type) {
		case V4L2_FRMIVAL_TYPE_DISCRETE:
			ival->min = ivalenum.discrete;
			ival->max = ivalenum.discrete;
			ival->step.numerator = 1;
			ival->step.denominator = 1;
			break;

		case V4L2_FRMIVAL_TYPE_STEPWISE:
			ival->min = ivalenum.stepwise.min;
			ival->max = ivalenum.stepwise.max;
			ival->step = ivalenum.stepwise.step;
			break;

		default:
			printf("Error: driver returned invalid frame ival "
				"type %u\n", ivalenum.type);
			return -EINVAL;
		}

		list_append(&frame->ivals, &ival->list);
	}

	return 0;
}
/**
 * @brief 
 * 
 * @param dev 
 * @param format 
 * @return int 
 */
static int
v4l2_enum_frame_sizes(struct v4l2_device *dev, struct v4l2_format_desc *format)
{
	struct v4l2_frame_desc *frame;
	unsigned int i;
	int ret;
	printf("%s: start\n", __func__);
	for (i = 0; ; ++i) {
		struct v4l2_frmsizeenum frmenum;

		memset(&frmenum, 0, sizeof frmenum);
		frmenum.index = i;
		frmenum.pixel_format = format->pixelformat;

		ret = ioctl(dev->fd, VIDIOC_ENUM_FRAMESIZES, &frmenum);
		if (ret < 0)
			break;

		if (i != frmenum.index)
			printf("Warning: driver returned wrong frame index "
				"%u.\n", frmenum.index);
		if (format->pixelformat != frmenum.pixel_format)
			printf("Warning: driver returned wrong frame pixel "
				"format %08x.\n", frmenum.pixel_format);

		frame = malloc(sizeof *frame);
		if (frame == NULL)
			return -ENOMEM;

		memset(frame, 0, sizeof *frame);

		list_init(&frame->ivals);
		frame->step_width = 1;
		frame->step_height = 1;

		switch (frmenum.type) {
		case V4L2_FRMSIZE_TYPE_DISCRETE:
			frame->min_width = frmenum.discrete.width;
			frame->min_height = frmenum.discrete.height;
			frame->max_width = frmenum.discrete.width;
			frame->max_height = frmenum.discrete.height;
			break;

		case V4L2_FRMSIZE_TYPE_STEPWISE:
			frame->step_width = frmenum.stepwise.step_width;
			frame->step_height = frmenum.stepwise.step_height;
		case V4L2_FRMSIZE_TYPE_CONTINUOUS:
			frame->min_width = frmenum.stepwise.min_width;
			frame->min_height = frmenum.stepwise.min_height;
			frame->max_width = frmenum.stepwise.max_width;
			frame->max_height = frmenum.stepwise.max_height;
			break;

		default:
			printf("Error: driver returned invalid frame size "
				"type %u\n", frmenum.type);
			return -EINVAL;
		}

		list_append(&format->frames, &frame->list);

		ret = v4l2_enum_frame_intervals(dev, format, frame);
		if (ret < 0)
			return ret;
	}

	return 0;
}
/**
 * @brief 
 * 
 * @param dev 
 * @return int 
 */
static int v4l2_enum_formats(struct v4l2_device *dev)
{
	struct v4l2_format_desc *format;
	unsigned int i;
	int ret;
	printf("%s: dev->fd %d start\n", __func__,dev->fd);
	for (i = 0; ; ++i) {
		struct v4l2_fmtdesc fmtenum;

		memset(&fmtenum, 0, sizeof fmtenum);
		fmtenum.index = i;
		fmtenum.type = dev->type;

		ret = ioctl(dev->fd, VIDIOC_ENUM_FMT, &fmtenum);
		if (ret < 0)
			break;

		if (i != fmtenum.index)
			printf("Warning: driver returned wrong format index "
				"%u.\n", fmtenum.index);
		if (dev->type != fmtenum.type)
			printf("Warning: driver returned wrong format type "
				"%u.\n", fmtenum.type);

		format = malloc(sizeof *format);
		if (format == NULL)
			return -ENOMEM;

		memset(format, 0, sizeof *format);

		list_init(&format->frames);
		format->pixelformat = fmtenum.pixelformat;

		list_append(&dev->formats, &format->list);

		ret = v4l2_enum_frame_sizes(dev, format);
		if (ret < 0)
			return ret;
	}

	return 0;
}
/* -----------------------------------------------------------------------------
 * Open/close
 *-----------------------------------------------------------------------------*/

struct v4l2_device *v4l2_open(const char *devname)
{
	struct v4l2_device *dev;
	struct v4l2_capability cap;
	int ret;
    printf("%s: start\n", __func__);
	dev = malloc(sizeof *dev);
	if (dev == NULL)
		return NULL;

	memset(dev, 0, sizeof *dev);
	dev->fd = -1;
	dev->buffers = NULL;
	list_init(&dev->formats);

	dev->fd = open(devname, O_RDWR | O_NONBLOCK);
	if (dev->fd < 0) {
		printf("Error opening device %s: %d.\n", devname, errno);
		v4l2_close(dev);
		return NULL;
	}

	memset(&cap, 0, sizeof cap);
	ret = ioctl(dev->fd, VIDIOC_QUERYCAP, &cap);
	if (ret < 0) {
		printf("Error opening device %s: unable to query "
			"device.\n", devname);
		v4l2_close(dev);
		return NULL;
	}
	printf("%s: VIDIOC_QUERYCAP 0x%x\n", __func__,cap.capabilities);
	
	//if (cap.capabilities & V4L2_CAP_VIDEO_OUTPUT_MPLANE)
	//	dev->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
		dev->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	else if (cap.capabilities & V4L2_CAP_VIDEO_OUTPUT)
		dev->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	else {
		printf("Error opening device %s: neither video capture "
			"nor video output supported.\n", devname);
		v4l2_close(dev);
		return NULL;
	}
	printf("%s: dev->type %d dev->fd %d\n", __func__, dev->type, dev->fd);
	
	ret = v4l2_enum_formats(dev);
	if (ret < 0) {
		printf("Error opening device %s: unable to enumerate "
			"formats.\n", devname);
		v4l2_close(dev);
		return NULL;
	}

	//struct v4l2_format fmt;
	//ioctl(dev->fd, VIDIOC_S_FMT, &fmt);

	printf("Device %s opened: %s (%s).\n", devname, cap.card, cap.bus_info);


	return dev;
}

void v4l2_close(struct v4l2_device *dev)
{
	struct v4l2_format_desc *format, *next_fmt;
	struct v4l2_frame_desc *frame, *next_frm;
	struct v4l2_ival_desc *ival, *next_ival;
	printf("%s: start\n", __func__);
	if (dev == NULL)
		return;

	list_for_each_entry_safe(format, next_fmt, &dev->formats, list) {
		list_for_each_entry_safe(frame, next_frm, &format->frames, list) {
			list_for_each_entry_safe(ival, next_ival, &frame->ivals, list) {
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
/* -----------------------------------------------------------------------------
 * Controls
 *-----------------------------------------------------------------------------*/

int v4l2_get_control(struct v4l2_device *dev, unsigned int id, int32_t *value)
{
	struct v4l2_control ctrl;
	int ret;
	printf("%s: start\n", __func__);
	ctrl.id = id;

	ret = ioctl(dev->fd, VIDIOC_G_CTRL, &ctrl);
	if (ret < 0) {
		printf("unable to get control: %s (%d).\n",
			strerror(errno), errno);
		return -errno;
	}

	*value = ctrl.value;
	return 0;
}

int v4l2_set_control(struct v4l2_device *dev, unsigned int id, int32_t *value)
{
	struct v4l2_control ctrl;
	int ret;
	printf("%s: start\n", __func__);
	ctrl.id = id;
	ctrl.value = *value;

	ret = ioctl(dev->fd, VIDIOC_S_CTRL, &ctrl);
	if (ret < 0) {
		printf("unable to set control: %s (%d).\n",
			strerror(errno), errno);
		return -errno;
	}

	*value = ctrl.value;
	return 0;
}

/* -----------------------------------------------------------------------------
 * Formats and frame rates
 *-----------------------------------------------------------------------------*/

int v4l2_get_format(struct v4l2_device *dev, struct v4l2_pix_format *format)
{
	struct v4l2_format fmt;
	int ret;
	printf("%s: start\n", __func__);
	memset(&fmt, 0, sizeof fmt);
	fmt.type = dev->type;

	ret = ioctl(dev->fd, VIDIOC_G_FMT, &fmt);
	if (ret < 0) {
		printf("Unable to get format: %s (%d).\n", strerror(errno),
			errno);
		return -errno;
	}

	dev->format = fmt.fmt.pix;
	*format = fmt.fmt.pix;

	return 0;
}

int v4l2_set_format(struct v4l2_device *dev, struct v4l2_pix_format *format)
{
	struct v4l2_format fmt;
	int ret;
	printf("%s: dev->type %d dev->fd %d  start\n", __func__,dev->type,dev->fd);
	memset(&fmt, 0, sizeof fmt);
	fmt.type = dev->type;
	fmt.fmt.pix.width = format->width;
	fmt.fmt.pix.height = format->height;
	fmt.fmt.pix.pixelformat = format->pixelformat;
	fmt.fmt.pix.field = V4L2_FIELD_ANY;
	//fmt.fmt.pix_mp.num_planes = 2;

	ret = ioctl(dev->fd, VIDIOC_S_FMT, &fmt);
	if (ret < 0) {
		printf("Unable to set format: %s (%d).\n", strerror(errno),
			errno);
		return -errno;
	}

	dev->format = fmt.fmt.pix;
	*format = fmt.fmt.pix;

	return 0;
}

/* -----------------------------------------------------------------------------
 * Buffers management
 *-----------------------------------------------------------------------------*/

int v4l2_alloc_buffers(struct v4l2_device *dev, enum v4l2_memory memtype,
		       unsigned int nbufs)
{
	struct v4l2_requestbuffers rb;
	struct v4l2_buffer buf;
	struct v4l2_video_buffer *buffers;
	struct v4l2_plane* planes_buffer;
	unsigned int i;
	int ret;
	unsigned int num_planes = 1;//2;

	dev->memtype = memtype;

	memset(&rb, 0, sizeof rb);
	rb.count = nbufs;
	rb.type = dev->type;
	rb.memory = dev->memtype;

	ret = ioctl(dev->fd, VIDIOC_REQBUFS, &rb);
	if (ret < 0) {
		printf("Unable to request buffers: %d.\n", errno);
		return -errno;
	}

	printf("%u buffers requested.\n", rb.count);

	buffers = malloc(rb.count * sizeof buffers[0]);
	if (buffers == NULL)
		return -ENOMEM;

	/* planes_buffer 的大小要根据plane地个数*/
	//planes_buffer = calloc(num_planes, sizeof(*planes_buffer));
	
	/* Map the buffers. */
	for (i = 0; i < rb.count; ++i) {
		memset(&buf, 0, sizeof buf);
		//memset(planes_buffer, 0, sizeof(*planes_buffer));
		buf.index = i;
		buf.type = dev->type;
		buf.memory = dev->memtype;
		//buf.m.planes = planes_buffer;
		//buf.length = num_planes;
		ret = ioctl(dev->fd, VIDIOC_QUERYBUF, &buf);

		if (ret < 0) {
			printf("%s,Unable to query buffer %u (%d).ret(%d)\n",__func__,i, errno,ret);
			return -errno;
		}
		printf("%s:buf.length(%d),buf.m.offset (0x%x)\n",__func__,buf.length,buf.m.offset); //buf.length

		switch (dev->memtype) {
		case V4L2_MEMORY_MMAP:
			buffers[i].mem = mmap(0, buf.length, PROT_READ | PROT_WRITE,
					      MAP_SHARED, dev->fd, buf.m.offset);
			if (buffers[i].mem == MAP_FAILED) {
				printf("Unable to map buffer %u (%d) offset(0x%x)\n", i, errno, buf.m.offset);
				return -errno;
			}
			buffers[i].size = buf.length;
			printf("%s:Buffer %u mapped at address %p size %d.\n",__func__,i, buffers[i].mem, buffers[i].size);
			break;

		case V4L2_MEMORY_USERPTR:
			buffers[i].mem = NULL;
			buffers[i].size = buf.length;
			printf("Buffer %u allocated with no memory.\n", i);
			break;

		default:
			break;
		}

	}

	dev->buffers = buffers;
	dev->nbufs = rb.count;
	//printf("%s:%u buffers dev->nbufs %u requested.\n", __func__,rb.count,dev->nbufs);
	return 0;
}

int v4l2_free_buffers(struct v4l2_device *dev)
{
	struct v4l2_requestbuffers rb;
	unsigned int i;
	int ret;
	printf("%s: start\n", __func__);
	if (dev->nbufs == 0)
		return 0;

	if (dev->memtype == V4L2_MEMORY_MMAP) {
		for (i = 0; i < dev->nbufs; ++i) {
			ret = munmap(dev->buffers[i].mem, dev->buffers[i].size);
			if (ret < 0) {
				printf("Unable to unmap buffer %u (%d)\n", i, errno);
				return -errno;
			}
		}
	}

	memset(&rb, 0, sizeof rb);
	rb.count = 0;
	rb.type = dev->type;
	rb.memory = dev->memtype;

	ret = ioctl(dev->fd, VIDIOC_REQBUFS, &rb);
	if (ret < 0) {
		printf("Unable to release buffers: %d.\n", errno);
		return -errno;
	}

	free(dev->buffers);
	dev->nbufs = 0;
	dev->buffers = NULL;

	return 0;
}

int v4l2_dequeue_buffer(struct v4l2_device *dev, struct v4l2_video_buffer *buffer)
{
	struct v4l2_buffer buf;
	int ret;
	// printf("%s: start\n", __func__);
	memset(&buf, 0, sizeof buf);
	buf.type = dev->type;
	buf.memory = dev->memtype;

	ret = ioctl(dev->fd, VIDIOC_DQBUF, &buf);
	if (ret < 0) {
		printf("Unable to dequeue buffer (%d).\n", errno);
		return -errno;
	}

	*buffer = dev->buffers[buf.index];
	buffer->index = buf.index;
	buffer->bytesused = buf.bytesused;
	buffer->error = !!(buf.flags & V4L2_BUF_FLAG_ERROR);

	return 0;
}

int v4l2_queue_buffer(struct v4l2_device *dev, struct v4l2_video_buffer *buffer)
{
	struct v4l2_buffer buf;
	int ret;
	// printf("%s: start\n", __func__);
	if (buffer->index >= dev->nbufs)
		return -EINVAL;

	memset(&buf, 0, sizeof buf);
	buf.index = buffer->index;
	buf.type = dev->type;
	buf.memory = dev->memtype;
	// printf("buffer->mem = 0x%x %d %d\n", buffer->mem, dev->memtype, buffer->size);
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
		printf("Unable to queue buffer (%d).\n", errno);
		return -errno;
	}

	return 0;
}

/* -----------------------------------------------------------------------------
 * Stream management
 *-----------------------------------------------------------------------------*/

int v4l2_stream_on(struct v4l2_device *dev)
{
	int type = dev->type;
	int ret;
	printf("%s: start\n", __func__);
	ret = ioctl(dev->fd, VIDIOC_STREAMON, &type);
	if (ret < 0)
		return -errno;

	return 0;
}

int v4l2_stream_off(struct v4l2_device *dev)
{
	int type = dev->type;
	int ret;
	printf("%s: start\n", __func__);
	ret = ioctl(dev->fd, VIDIOC_STREAMOFF, &type);
	if (ret < 0)
		return -errno;

	return 0;
}