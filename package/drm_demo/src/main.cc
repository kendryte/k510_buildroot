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
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "disp.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#define DRM_DEV_NAME_DEFAULT "/dev/dri/card0"

static struct drm_dev drm_dev;
static uint32_t screen_width, screen_height;
#define DRM_BUF_COUNT 7
static struct plane_cfg {
	bool enable;
	bool valid;
	Scalar color;
	struct drm_buffer buf;
} plane_cfg[DRM_BUF_COUNT] = {
	{ 1,
	  0,
	  Scalar(0xFF, 0xFF, 0xFF, 0xFF),
	  { 0, 0, 1080, 1920, DRM_FORMAT_NV12, 8 } },
	{ 1,
	  0,
	  Scalar(0x00, 0xFF, 0x00, 0xFF),
	  { 100, 150, 880, 500, DRM_FORMAT_NV12, 8 } },
	{ 1,
	  0,
	  Scalar(0x00, 0xFF, 0x00, 0xFF),
	  { 100, 750, 880, 500, DRM_FORMAT_NV12, 8 } },
	{ 1,
	  0,
	  Scalar(0x00, 0xFF, 0x00, 0xFF),
	  { 100, 1350, 880, 500, DRM_FORMAT_NV12, 8 } },
	{ 1,
	  0,
	  Scalar(0x00, 0x00, 0xFF, 0x10),
	  { 200, 300, 680, 300, DRM_FORMAT_ARGB8888, 32 } },
	{ 1,
	  0,
	  Scalar(0x00, 0x00, 0xFF, 0x80),
	  { 200, 900, 680, 300, DRM_FORMAT_ARGB8888, 32 } },
	{ 1,
	  0,
	  Scalar(0x00, 0x00, 0xFF, 0xFF),
	  { 200, 1500, 680, 300, DRM_FORMAT_ARGB8888, 32 } }
};
static bool stop = false;

static void putText_center(Mat &img, const String &text, Point offset,
			   int fontFace, double fontScale, Scalar color,
			   int thickness, int line_type)
{
	int baseline;
	Size size =
		getTextSize(text, fontFace, fontScale, thickness, &baseline);
	Point origin(offset.x, offset.y + size.height + baseline);
	if (origin.x == -1)
		origin.x = (img.cols - size.width) / 2;
	if (origin.y == -1)
		origin.y = (img.rows - size.height) / 2;
	putText(img, text, origin, fontFace, fontScale, color, thickness,
		line_type);
}

static void cvtRGB2NV12(Mat src, Mat &dst)
{
	Mat yu12, u, v, uv, nv12;
	int rows = src.rows;
	cvtColor(src, yu12, COLOR_BGR2YUV_I420);
	u = yu12.rowRange(rows, rows + rows / 4);
	v = yu12.rowRange(rows + rows / 4, rows + rows / 2);
	u = u.reshape(0, u.total());
	v = v.reshape(0, v.total());
	hconcat(u, v, uv);
	uv = uv.reshape(0, rows / 2);
	vconcat(yu12.rowRange(0, rows), uv, nv12);
	dst = dst.reshape(1, rows * 3);
	nv12.copyTo(dst.rowRange(0, nv12.rows));
}

static int alloc_drm_buff(void)
{
	int fd = drm_dev.fd;

	for (int i = 0; i < DRM_BUF_COUNT; i++) {
		if (!plane_cfg[i].enable)
			continue;
		if (drm_create_fb(fd, &plane_cfg[i].buf)) {
			fprintf(stderr, "couldn't create buffer %u\n", i);
			return -1;
		}
		plane_cfg[i].valid = 1;
	}

	return 0;
}

static void free_drm_buff(void)
{
	int fd = drm_dev.fd;

	for (int i = 0; i < DRM_BUF_COUNT; i++) {
		if (!plane_cfg[i].enable || !plane_cfg[i].valid)
			continue;
		drm_destroy_fb(fd, &plane_cfg[i].buf);
		plane_cfg[i].valid = 0;
	}
}

static int plane_config(struct drm_dev *dev)
{
	drmModeAtomicReq *req;
	struct drm_object *obj;
	struct drm_buffer *buf;
	uint32_t flags;
	int ret;

	if ((ret = drmModeCreatePropertyBlob(dev->fd, &dev->mode,
					     sizeof(dev->mode),
					     &dev->mode_blob_id)) != 0) {
		fprintf(stderr, "couldn't create a blob property\n");
		return ret;
	}

	req = drmModeAtomicAlloc();
	/* set id of the CRTC id that the connector is using */
	obj = &dev->conn;
	if ((ret = drm_set_object_property(req, obj, "CRTC_ID", dev->crtc_id)) <
	    0)
		goto err;

	/* set the mode id of the CRTC; this property receives the id of a blob
	 * property that holds the struct that actually contains the mode info */
	obj = &dev->crtc;
	if ((ret = drm_set_object_property(req, obj, "MODE_ID",
					   dev->mode_blob_id)) < 0)
		goto err;

	/* set the CRTC object as active */
	if ((ret = drm_set_object_property(req, obj, "ACTIVE", 1)) < 0)
		goto err;

	/* set properties of the plane related to the CRTC and the framebuffer */
	for (int i = 0; i < DRM_BUF_COUNT; i++) {
		if (!plane_cfg[i].enable || !plane_cfg[i].valid)
			continue;
		obj = &dev->planes[i];
		buf = &plane_cfg[i].buf;
		if ((ret = drm_set_object_property(req, obj, "FB_ID",
						   buf->fb)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "CRTC_ID",
						   dev->crtc_id)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "SRC_X", 0)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "SRC_Y", 0)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "SRC_W",
						   buf->width << 16)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "SRC_H",
						   buf->height << 16)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "CRTC_X",
						   buf->offset_x)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "CRTC_Y",
						   buf->offset_y)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "CRTC_W",
						   buf->width)) < 0)
			goto err;
		if ((ret = drm_set_object_property(req, obj, "CRTC_H",
						   buf->height)) < 0)
			goto err;
	}

	flags = DRM_MODE_ATOMIC_TEST_ONLY | DRM_MODE_ATOMIC_ALLOW_MODESET;
	if ((ret = drmModeAtomicCommit(dev->fd, req, flags, NULL)) < 0) {
		fprintf(stderr, "test-only atomic commit failed, %d\n", errno);
		goto err;
	}

	flags = DRM_MODE_ATOMIC_ALLOW_MODESET;
	if ((ret = drmModeAtomicCommit(dev->fd, req, flags, NULL)) < 0) {
		fprintf(stderr, "atomic commit failed, %d\n", errno);
		goto err;
	}
err:
	drmModeAtomicFree(req);

	return ret;
}

static void draw_pic(void)
{
	for (int i = 0; i < DRM_BUF_COUNT; i++) {
		if (!plane_cfg[i].enable)
			continue;
		struct drm_buffer *buf = &plane_cfg[i].buf;
		Mat img;
		if (plane_cfg[i].buf.fourcc == DRM_FORMAT_NV12)
			img = Mat(buf->height, buf->width, CV_8UC(3));
		else if (plane_cfg[i].buf.fourcc == DRM_FORMAT_ARGB8888)
			img = Mat(buf->height, buf->width, CV_8UC(4),
				  plane_cfg[i].buf.map);
		img.setTo(plane_cfg[i].color);
		char str[128];
		snprintf(str, 128, "layer %d", i);
		putText_center(img, str, Point(-1, 0), FONT_HERSHEY_COMPLEX, screen_height * 0.002,
			       Scalar(0, 0, 0, 0), 2, LINE_8);
		if (plane_cfg[i].buf.fourcc == DRM_FORMAT_NV12) {
			Mat img_dst = Mat(buf->height, buf->width, CV_8UC(3),
					  plane_cfg[i].buf.map);
			cvtRGB2NV12(img, img_dst);
		}
	}
}

static int video_resolution_adaptation(void)
{
	plane_cfg[0].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width, 3);
	plane_cfg[0].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height, 2);
	plane_cfg[0].buf.offset_x = 0;
	plane_cfg[0].buf.offset_y = 0;

	plane_cfg[1].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width * 80 / 100, 3);
	plane_cfg[1].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height * 26 / 100, 2);
	plane_cfg[1].buf.offset_x = (screen_width - plane_cfg[1].buf.width) / 2;
	plane_cfg[1].buf.offset_y = screen_height * 10 / 100;

	plane_cfg[2].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width * 80 / 100, 3);
	plane_cfg[2].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height * 26 / 100, 2);
	plane_cfg[2].buf.offset_x = (screen_width - plane_cfg[2].buf.width) / 2;
	plane_cfg[2].buf.offset_y = screen_height * 40 / 100;

	plane_cfg[3].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width * 80 / 100, 3);
	plane_cfg[3].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height * 26 / 100, 2);
	plane_cfg[3].buf.offset_x = (screen_width - plane_cfg[3].buf.width) / 2;
	plane_cfg[3].buf.offset_y = screen_height * 70 / 100;

	plane_cfg[4].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width * 60 / 100, 3);
	plane_cfg[4].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height * 15 / 100, 2);
	plane_cfg[4].buf.offset_x = (screen_width - plane_cfg[4].buf.width) / 2;
	plane_cfg[4].buf.offset_y = screen_height * 20 / 100;

	plane_cfg[5].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width * 60 / 100, 3);
	plane_cfg[5].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height * 15 / 100, 2);
	plane_cfg[5].buf.offset_x = (screen_width - plane_cfg[5].buf.width) / 2;
	plane_cfg[5].buf.offset_y = screen_height * 50 / 100;

	plane_cfg[6].buf.width = ALIGNED_UP_POWER_OF_TWO(screen_width * 60 / 100, 3);
	plane_cfg[6].buf.height = ALIGNED_DOWN_POWER_OF_TWO(screen_height * 15 / 100, 2);
	plane_cfg[6].buf.offset_x = (screen_width - plane_cfg[6].buf.width) / 2;
	plane_cfg[6].buf.offset_y = screen_height * 80 / 100;

	return 0;
}

static int display_init(void)
{
	if (drm_dev_setup(&drm_dev, DRM_DEV_NAME_DEFAULT))
		return -1;

	drm_get_resolution(&drm_dev, &screen_width, &screen_height);
	printf("screen resolution: %dx%d\n", screen_width, screen_height);

	if (video_resolution_adaptation() < 0) {
		printf("resolution not support!\n");
		return -1;
	}

	if (alloc_drm_buff()) {
		drm_dev_cleanup(&drm_dev);
		return -1;
	}

	draw_pic();

	if (plane_config(&drm_dev)) {
		free_drm_buff();
		drm_dev_cleanup(&drm_dev);
		return -1;
	}

	return 0;
}

static void display_deinit(void)
{
	free_drm_buff();
	drm_dev_cleanup(&drm_dev);
}

static void fun_sigint(int sig)
{
	stop = true;
}

int main(int argc, char **argv)
{
	printf("case %s build %s %s\n", argv[0], __DATE__, __TIME__);
	signal(SIGINT, fun_sigint);
	if (display_init())
		return -1;
	while (1) {
		sleep(100);
		if (stop)
			break;
	}
	display_deinit();
	return 0;
}