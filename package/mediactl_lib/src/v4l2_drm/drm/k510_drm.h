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

#ifndef _K510_DRM_H
#define _K510_DRM_H
#include "drm.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm_fourcc.h>
#include <sys/ioctl.h>

#define BUFFERS_COUNT		5//10//4//6/3
#define BUFFERS_NUM			2

struct drm_size {
	uint32_t width;
	uint32_t height;
	uint32_t src_offset_w;
	uint32_t src_offset_h;
	uint32_t crtc_offset_w;
	uint32_t crtc_offset_h;
};

struct drm_buffer {
	uint32_t handle;
	uint32_t pitch;
	uint32_t offset;
	uint32_t width;
	uint32_t height;
	unsigned long int size;
	void * map;
	uint32_t fb_handle;
	int    dbuf_fd;
	uint32_t src_offset_w;
	uint32_t src_offset_h;
	uint32_t crtc_offset_w;
	uint32_t crtc_offset_h;
};

struct drm_dev {
	int fd;
	uint32_t conn_id, enc_id, crtc_id, plane_id, crtc_idx, plane_id2;
	uint32_t width, height;
	uint32_t mmWidth, mmHeight;
	uint32_t fourcc;
	drmModeModeInfo mode;
	uint32_t blob_id;
	drmModeCrtc *saved_crtc;
	drmModeAtomicReq *req;
	drmEventContext drm_event_ctx;
	drmModePlane *plane;
	drmModeCrtc *crtc;
	drmModeConnector *conn;
	uint32_t count_plane_props;
	uint32_t count_crtc_props;
	uint32_t count_conn_props;
	drmModePropertyPtr plane_props[128];
	drmModePropertyPtr crtc_props[128];
	drmModePropertyPtr conn_props[128];
	struct drm_buffer drm_bufs[BUFFERS_COUNT * BUFFERS_NUM]; /* DUMB buffers */
	struct drm_buffer drm_bufs_show;
	struct drm_buffer *cur_bufs[BUFFERS_COUNT * BUFFERS_NUM]; /* double buffering handling */
	uint32_t drm_plane_use[7];
	uint32_t camera_num;
};
extern struct  drm_dev drm_dev;

int drm_dmabuf_set_2plane(struct drm_buffer *buf,struct drm_buffer *buf2);
int drm_dmabuf_set_plane(struct drm_buffer *buf);
void drm_wait_vsync(void);
//void drm_init(void);
//void drm_init(uint32_t width, uint32_t height);
int drm_init(struct drm_size *size);

void drm_destory_dumb(struct drm_buffer *buf);
void drm_exit(void);
void drm_reset(void);
int drm_get_resolution(struct drm_dev *dev, uint32_t *width, uint32_t *height);
#endif
