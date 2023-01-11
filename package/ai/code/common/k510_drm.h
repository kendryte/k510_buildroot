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

#define DRM_BUFFERS_COUNT		3
#ifdef FULL_SCREEN
#define DRM_INPUT_WIDTH	1080
#define DRM_INPUT_HEIGHT 1920
#define DRM_OFFSET_HEIGHT 0
#else
#define DRM_INPUT_WIDTH	1080
#define DRM_INPUT_HEIGHT 720
#define DRM_OFFSET_HEIGHT ((1920-DRM_INPUT_HEIGHT)/2)
#endif
struct drm_buffer {
	uint32_t handle;
	uint32_t pitch;
	uint32_t offset;
	unsigned long int size;
	void * map;
	uint32_t fb_handle;
	int    dbuf_fd;
};

struct drm_dev {
	int fd;
	uint32_t conn_id, enc_id, crtc_id, plane_id, plane_id2, crtc_idx;
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
	struct drm_buffer drm_bufs[DRM_BUFFERS_COUNT]; /* DUMB buffers */
	struct drm_buffer drm_bufs_argb[DRM_BUFFERS_COUNT]; /* DUMB buffers */
	struct drm_buffer drm_bufs_show; 
	struct drm_buffer *cur_bufs[DRM_BUFFERS_COUNT]; /* double buffering handling */
};

struct vo_draw_frame {
    uint32_t draw_en;
    uint32_t line_x_start;
    uint32_t line_y_start;

    uint32_t line_x_end;
    uint32_t line_y_end;

    uint32_t frame_num;

    uint32_t crtc_id;
};

extern struct  drm_dev drm_dev;
#if defined(__cplusplus)
extern "C" {
#endif
int draw_frame(struct vo_draw_frame *frame);
int drm_dmabuf_set_plane(struct drm_buffer *buf, struct drm_buffer *buf1);
void drm_wait_vsync(void);
int  drm_init(void);
void drm_destory_dumb(struct drm_buffer *buf);
void drm_exit(void);
int drm_get_resolution(struct drm_dev *dev, uint32_t *width, uint32_t *height);
#if defined(__cplusplus)
}
#endif
#endif