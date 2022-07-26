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
#include "k510_drm.h"

#  define DRM_CARD          "/dev/dri/card0"
#  define DRM_CONNECTOR_ID  -1  /* -1 for the first connected one */
#  define LV_COLOR_DEPTH 8

#define DRM_KENDRYTE_DRAW_FRAME         0x00

#define DRM_IOCTL_KENDRYTE_DRAW_FRAME   DRM_IOWR(DRM_COMMAND_BASE + \
                DRM_KENDRYTE_DRAW_FRAME, struct vo_draw_frame)

#define DBG_TAG "drm"

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define print(msg, ...)	fprintf(stderr, msg, ##__VA_ARGS__);
#define err(msg, ...)  print("error: " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) print(msg "\n", ##__VA_ARGS__)
#define dbg(msg, ...)  {}  //print(msg "\n", ##__VA_ARGS__) //print(DBG_TAG ": " msg "\n", ##__VA_ARGS__)


#if LV_COLOR_DEPTH == 32
#define DRM_FOURCC   DRM_FORMAT_ARGB8888  //DRM_FORMAT_NV12
#elif LV_COLOR_DEPTH == 8
#define DRM_FOURCC DRM_FORMAT_NV12
#else
#error LV_COLOR_DEPTH not supported
#endif

struct  drm_dev drm_dev;

int draw_frame(struct vo_draw_frame *frame)
{
	return drmIoctl(drm_dev.fd, DRM_IOCTL_KENDRYTE_DRAW_FRAME, frame);
}

static uint32_t get_plane_property_id(const char *name)
{
	uint32_t i;

	dbg("Find plane property: %s", name);

	for (i = 0; i < drm_dev.count_plane_props; ++i)
		if (!strcmp(drm_dev.plane_props[i]->name, name))
			return drm_dev.plane_props[i]->prop_id;

	dbg("Unknown plane property: %s", name);

	return 0;
}

static uint32_t get_crtc_property_id(const char *name)
{
	uint32_t i;

	dbg("Find crtc property: %s", name);

	for (i = 0; i < drm_dev.count_crtc_props; ++i)
		if (!strcmp(drm_dev.crtc_props[i]->name, name))
			return drm_dev.crtc_props[i]->prop_id;

	dbg("Unknown crtc property: %s", name);

	return 0;
}

static uint32_t get_conn_property_id(const char *name)
{
	uint32_t i;

	dbg("Find conn property: %s", name);

	for (i = 0; i < drm_dev.count_conn_props; ++i)
		if (!strcmp(drm_dev.conn_props[i]->name, name))
			return drm_dev.conn_props[i]->prop_id;

	dbg("Unknown conn property: %s", name);

	return 0;
}

static void page_flip_handler(int fd, unsigned int sequence, unsigned int tv_sec,
			      unsigned int tv_usec, void *user_data)
{
	dbg("flip");
}

static int drm_get_plane_props(void)
{
	uint32_t i;

	drmModeObjectPropertiesPtr props = drmModeObjectGetProperties(drm_dev.fd, drm_dev.plane_id,
								      DRM_MODE_OBJECT_PLANE);
	if (!props) {
		err("drmModeObjectGetProperties failed");
		return -1;
	}
	dbg("Found %u plane props", props->count_props);
	drm_dev.count_plane_props = props->count_props;
	for (i = 0; i < props->count_props; i++) {
		drm_dev.plane_props[i] = drmModeGetProperty(drm_dev.fd, props->props[i]);
		dbg("Added plane prop %u:%s", drm_dev.plane_props[i]->prop_id, drm_dev.plane_props[i]->name);
	}
	drmModeFreeObjectProperties(props);

	return 0;
}

static int drm_get_crtc_props(void)
{
	uint32_t i;

	drmModeObjectPropertiesPtr props = drmModeObjectGetProperties(drm_dev.fd, drm_dev.crtc_id,
								      DRM_MODE_OBJECT_CRTC);
	if (!props) {
		err("drmModeObjectGetProperties failed");
		return -1;
	}
	dbg("Found %u crtc props", props->count_props);
	drm_dev.count_crtc_props = props->count_props;
	for (i = 0; i < props->count_props; i++) {
		drm_dev.crtc_props[i] = drmModeGetProperty(drm_dev.fd, props->props[i]);
		dbg("Added crtc prop %u:%s", drm_dev.crtc_props[i]->prop_id, drm_dev.crtc_props[i]->name);
	}
	drmModeFreeObjectProperties(props);

	return 0;
}

static int drm_get_conn_props(void)
{
	uint32_t i;

	drmModeObjectPropertiesPtr props = drmModeObjectGetProperties(drm_dev.fd, drm_dev.conn_id,
								      DRM_MODE_OBJECT_CONNECTOR);
	if (!props) {
		err("drmModeObjectGetProperties failed");
		return -1;
	}
	dbg("Found %u connector props", props->count_props);
	drm_dev.count_conn_props = props->count_props;
	for (i = 0; i < props->count_props; i++) {
		drm_dev.conn_props[i] = drmModeGetProperty(drm_dev.fd, props->props[i]);
		dbg("Added connector prop %u:%s", drm_dev.conn_props[i]->prop_id, drm_dev.conn_props[i]->name);
	}
	drmModeFreeObjectProperties(props);

	return 0;
}

static int drm_add_plane_property(const char *name, uint64_t value)
{
	int ret;
	uint32_t prop_id = get_plane_property_id(name);

	if (!prop_id) {
		err("Couldn't find plane prop %s", name);
		return -1;
	}

	ret = drmModeAtomicAddProperty(drm_dev.req, drm_dev.plane_id, get_plane_property_id(name), value);
	if (ret < 0) {
		err("drmModeAtomicAddProperty (%s:%" PRIu64 ") failed: %d", name, value, ret);
		return ret;
	}

	return 0;
}

static int drm_add_plane2_property(const char *name, uint64_t value)
{
	int ret;
	uint32_t prop_id = get_plane_property_id(name);

	if (!prop_id) {
		printf("Couldn't find plane prop %s", name);
		return -1;
	}

	ret = drmModeAtomicAddProperty(drm_dev.req, drm_dev.plane_id2, get_plane_property_id(name), value);
	if (ret < 0) {
		printf("drmModeAtomicAddProperty (%s:%" PRIu64 ") failed: %d", name, value, ret);
		return ret;
	}

	return 0;
}
static int drm_add_crtc_property(const char *name, uint64_t value)
{
	int ret;
	uint32_t prop_id = get_crtc_property_id(name);

	if (!prop_id) {
		err("Couldn't find crtc prop %s", name);
		return -1;
	}

	ret = drmModeAtomicAddProperty(drm_dev.req, drm_dev.crtc_id, get_crtc_property_id(name), value);
	if (ret < 0) {
		err("drmModeAtomicAddProperty (%s:%" PRIu64 ") failed: %d", name, value, ret);
		return ret;
	}

	return 0;
}

static int drm_add_conn_property(const char *name, uint64_t value)
{
	int ret;
	uint32_t prop_id = get_conn_property_id(name);

	if (!prop_id) {
		err("Couldn't find conn prop %s", name);
		return -1;
	}

	ret = drmModeAtomicAddProperty(drm_dev.req, drm_dev.conn_id, get_conn_property_id(name), value);
	if (ret < 0) {
		err("drmModeAtomicAddProperty (%s:%" PRIu64 ") failed: %d", name, value, ret);
		return ret;
	}

	return 0;
}

int drm_dmabuf_set_plane(struct drm_buffer *buf, struct drm_buffer *buf1)
{
	int ret;
	static int first = 1;
	uint32_t flags = DRM_MODE_PAGE_FLIP_EVENT;

	drm_dev.req = drmModeAtomicAlloc();

	/* On first Atomic commit, do a modeset */
	if (first) {
		drm_add_conn_property("CRTC_ID", drm_dev.crtc_id);

		drm_add_crtc_property("MODE_ID", drm_dev.blob_id);
		drm_add_crtc_property("ACTIVE", 1);

		flags |= DRM_MODE_ATOMIC_ALLOW_MODESET;

		first = 0;
	}


	drm_add_plane_property("FB_ID", buf->fb_handle);
	drm_add_plane_property("CRTC_ID", drm_dev.crtc_id);
	drm_add_plane_property("SRC_X", 0);
	drm_add_plane_property("SRC_Y", 0);
	drm_add_plane_property("SRC_W", drm_dev.width << 16);
	drm_add_plane_property("SRC_H", drm_dev.height << 16);
	drm_add_plane_property("CRTC_X", 0);
	drm_add_plane_property("CRTC_Y", 0);
	drm_add_plane_property("CRTC_W", drm_dev.width);
	drm_add_plane_property("CRTC_H", drm_dev.height);

#if 1
	// two plane 
	drm_add_plane2_property("FB_ID", buf1->fb_handle);
	drm_add_plane2_property("CRTC_ID", drm_dev.crtc_id);
	drm_add_plane2_property("SRC_X", 0);
	drm_add_plane2_property("SRC_Y", 0);
	drm_add_plane2_property("SRC_W", drm_dev.width << 16);
	drm_add_plane2_property("SRC_H", drm_dev.height << 16);
	drm_add_plane2_property("CRTC_X", 0);
	drm_add_plane2_property("CRTC_Y", 0);
	drm_add_plane2_property("CRTC_W", drm_dev.width);
	drm_add_plane2_property("CRTC_H", drm_dev.height);

#endif
	ret = drmModeAtomicCommit(drm_dev.fd, drm_dev.req, flags, NULL);
	if (ret) {
		printf("drmModeAtomicCommit failed: %s", strerror(errno));
		drmModeAtomicFree(drm_dev.req);
		return ret;
	}
	return 0;
}

static int find_plane(unsigned int fourcc, uint32_t *plane_id, uint32_t crtc_id, uint32_t crtc_idx)
{
	drmModePlaneResPtr planes;
	drmModePlanePtr plane;
	unsigned int i;
	unsigned int j;
	int ret = 0;
	unsigned int format = fourcc;

	planes = drmModeGetPlaneResources(drm_dev.fd);
	if (!planes) {
		err("drmModeGetPlaneResources failed");
		return -1;
	}

	dbg("drm: found planes %u", planes->count_planes);

	for (i = 0; i < planes->count_planes; ++i) {
		plane = drmModeGetPlane(drm_dev.fd, planes->planes[i]);
		if (!plane) {
			err("drmModeGetPlane failed: %s", strerror(errno));
			break;
		}

		if (!(plane->possible_crtcs & (1 << crtc_idx))) {
			drmModeFreePlane(plane);
			continue;
		}

		for (j = 0; j < plane->count_formats; ++j) {
			if (plane->formats[j] == format)
				break;
		}

		if (j == plane->count_formats) {
			drmModeFreePlane(plane);
			continue;
		}

		*plane_id = plane->plane_id;
		drmModeFreePlane(plane);

		dbg("found plane %d", *plane_id);
		break;
	}

	if (i == planes->count_planes)
		ret = -1;

	drmModeFreePlaneResources(planes);

	return ret;
}

static int drm_find_connector(void)
{
	drmModeConnector *conn = NULL;
	drmModeEncoder *enc = NULL;
	drmModeRes *res;
	int i;

	if ((res = drmModeGetResources(drm_dev.fd)) == NULL) {
		err("drmModeGetResources() failed");
		return -1;
	}

	if (res->count_crtcs <= 0) {
		err("no Crtcs");
		goto free_res;
	}

	/* find all available connectors */
	for (i = 0; i < res->count_connectors; i++) {
		conn = drmModeGetConnector(drm_dev.fd, res->connectors[i]);
		if (!conn)
			continue;

#if DRM_CONNECTOR_ID >= 0
		if (conn->connector_id != DRM_CONNECTOR_ID) {
			drmModeFreeConnector(conn);
			continue;
		}
#endif

		if (conn->connection == DRM_MODE_CONNECTED) {
			dbg("drm: connector %d: connected", conn->connector_id);
		} else if (conn->connection == DRM_MODE_DISCONNECTED) {
			dbg("drm: connector %d: disconnected", conn->connector_id);
		} else if (conn->connection == DRM_MODE_UNKNOWNCONNECTION) {
			dbg("drm: connector %d: unknownconnection", conn->connector_id);
		} else {
			dbg("drm: connector %d: unknown", conn->connector_id);
		}

		if (conn->connection == DRM_MODE_CONNECTED && conn->count_modes > 0)
			break;

		drmModeFreeConnector(conn);
		conn = NULL;
	};

	if (!conn) {
		err("suitable connector not found");
		goto free_res;
	}

	drm_dev.conn_id = conn->connector_id;
	dbg("conn_id: %d", drm_dev.conn_id);
	drm_dev.mmWidth = conn->mmWidth;
	drm_dev.mmHeight = conn->mmHeight;

	memcpy(&drm_dev.mode, &conn->modes[0], sizeof(drmModeModeInfo));

	if (drmModeCreatePropertyBlob(drm_dev.fd, &drm_dev.mode, sizeof(drm_dev.mode),
				      &drm_dev.blob_id)) {
		err("error creating mode blob");
		goto free_res;
	}

	drm_dev.width = drm_dev.mode.hdisplay;
	drm_dev.height = drm_dev.mode.vdisplay;

	for (i = 0 ; i < res->count_encoders; i++) {
		enc = drmModeGetEncoder(drm_dev.fd, res->encoders[i]);
		if (!enc)
			continue;

		dbg("enc%d enc_id %d conn enc_id %d", i, enc->encoder_id, conn->encoder_id);

		if (enc->encoder_id == conn->encoder_id)
			break;

		drmModeFreeEncoder(enc);
		enc = NULL;
	}

	if (enc) {
		drm_dev.enc_id = enc->encoder_id;
		dbg("enc_id: %d", drm_dev.enc_id);
		drm_dev.crtc_id = enc->crtc_id;
		dbg("crtc_id: %d", drm_dev.crtc_id);
		drmModeFreeEncoder(enc);
	} else {
		/* Encoder hasn't been associated yet, look it up */
		for (i = 0; i < conn->count_encoders; i++) {
			int crtc, crtc_id = -1;

			enc = drmModeGetEncoder(drm_dev.fd, conn->encoders[i]);
			if (!enc)
				continue;

			for (crtc = 0 ; crtc < res->count_crtcs; crtc++) {
				uint32_t crtc_mask = 1 << crtc;

				crtc_id = res->crtcs[crtc];

				dbg("enc_id %d crtc%d id %d mask %x possible %x", enc->encoder_id, crtc, crtc_id, crtc_mask, enc->possible_crtcs);

				if (enc->possible_crtcs & crtc_mask)
					break;
			}

			if (crtc_id > 0) {
				drm_dev.enc_id = enc->encoder_id;
				dbg("enc_id: %d", drm_dev.enc_id);
				drm_dev.crtc_id = crtc_id;
				dbg("crtc_id: %d", drm_dev.crtc_id);
				break;
			}

			drmModeFreeEncoder(enc);
			enc = NULL;
		}

		if (!enc) {
			err("suitable encoder not found");
			goto free_res;
		}

		drmModeFreeEncoder(enc);
	}

	drm_dev.crtc_idx = -1;

	for (i = 0; i < res->count_crtcs; ++i) {
		if (drm_dev.crtc_id == res->crtcs[i]) {
			drm_dev.crtc_idx = i;
			break;
		}
	}

	if (drm_dev.crtc_idx == -1) {
		err("drm: CRTC not found");
		goto free_res;
	}

	dbg("crtc_idx: %d", drm_dev.crtc_idx);

	return 0;

free_res:
	drmModeFreeResources(res);

	return -1;
}

static int drm_open(const char *path)
{
	int fd, flags;
	uint64_t has_dumb;
	int ret;

	fd = open(path, O_RDWR);
	if (fd < 0) {
		err("cannot open \"%s\"", path);
		return -1;
	}

	/* set FD_CLOEXEC flag */
	if ((flags = fcntl(fd, F_GETFD)) < 0 ||
	     fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0) {
		err("fcntl FD_CLOEXEC failed");
		goto err;
	}

	/* check capability */
	ret = drmGetCap(fd, DRM_CAP_DUMB_BUFFER, &has_dumb);
	if (ret < 0 || has_dumb == 0) {
		err("drmGetCap DRM_CAP_DUMB_BUFFER failed or \"%s\" doesn't have dumb "
		    "buffer", path);
		goto err;
	}

	return fd;
err:
	close(fd);
	return -1;
}

static int drm_setup(unsigned int fourcc)
{
	int ret;
	const char *device_path = NULL;
	uint32_t argb = DRM_FORMAT_ARGB8888;
	uint32_t yuv = DRM_FORMAT_NV12;

	device_path = getenv("DRM_CARD");
	if (!device_path)
		device_path = DRM_CARD;

	drm_dev.fd = drm_open(device_path);
	if (drm_dev.fd < 0)
		return -1;

	ret = drmSetClientCap(drm_dev.fd, DRM_CLIENT_CAP_ATOMIC, 1);
	if (ret) {
		err("No atomic modesetting support: %s", strerror(errno));
		goto err;
	}

	ret = drm_find_connector();
	if (ret) {
		err("available drm devices not found");
		goto err;
	}

	ret = find_plane(yuv, &drm_dev.plane_id, drm_dev.crtc_id, drm_dev.crtc_idx);
	if (ret) {
		err("Cannot find plane");
		goto err;
	}

	ret = find_plane(argb, &drm_dev.plane_id2, drm_dev.crtc_id, drm_dev.crtc_idx);
	if (ret) {
		err("Cannot find plane");
		goto err;
	}

	drm_dev.plane = drmModeGetPlane(drm_dev.fd, drm_dev.plane_id);
	if (!drm_dev.plane) {
		err("Cannot get plane");
		goto err;
	}

	drm_dev.crtc = drmModeGetCrtc(drm_dev.fd, drm_dev.crtc_id);
	if (!drm_dev.crtc) {
		err("Cannot get crtc");
		goto err;
	}

	drm_dev.conn = drmModeGetConnector(drm_dev.fd, drm_dev.conn_id);
	if (!drm_dev.conn) {
		err("Cannot get connector");
		goto err;
	}

	ret = drm_get_plane_props();
	if (ret) {
		err("Cannot get plane props");
		goto err;
	}

	ret = drm_get_crtc_props();
	if (ret) {
		err("Cannot get crtc props");
		goto err;
	}

	ret = drm_get_conn_props();
	if (ret) {
		err("Cannot get connector props");
		goto err;
	}

	drm_dev.drm_event_ctx.version = DRM_EVENT_CONTEXT_VERSION;
	drm_dev.drm_event_ctx.page_flip_handler = page_flip_handler;
	drm_dev.fourcc = fourcc;

	info("drm: Found plane_id: %u connector_id: %d crtc_id: %d",
		drm_dev.plane_id, drm_dev.conn_id, drm_dev.crtc_id);

	info("drm: %dx%d (%dmm X% dmm) pixel format %c%c%c%c",
	     drm_dev.width, drm_dev.height, drm_dev.mmWidth, drm_dev.mmHeight,
	     (fourcc>>0)&0xff, (fourcc>>8)&0xff, (fourcc>>16)&0xff, (fourcc>>24)&0xff);

	return 0;

err:
	close(drm_dev.fd);
	return -1;
}

static int drm_allocate_dumb_argb(struct drm_buffer *buf)
{
	struct drm_mode_create_dumb creq;
	struct drm_mode_map_dumb mreq;
	uint32_t handles[4] = {0}, pitches[4] = {0}, offsets[4] = {0};
	uint32_t argb = DRM_FORMAT_ARGB8888;
	int ret;

	/* create dumb buffer */
	memset(&creq, 0, sizeof(creq));
	creq.width = (drm_dev.width+15)/16*16;
	creq.height = drm_dev.height;  //* 4;
	creq.bpp = 32;  //8

	ret = drmIoctl(drm_dev.fd, DRM_IOCTL_MODE_CREATE_DUMB, &creq);
	if (ret < 0) {
		err("DRM_IOCTL_MODE_CREATE_DUMB ARGB fail");
		return -1;
	}

	buf->handle = creq.handle;
	buf->pitch = creq.pitch;
	dbg("pitch %d", buf->pitch);
	buf->size = creq.size;
	dbg("size %d", buf->size);

	/* prepare buffer for memory mapping */
	memset(&mreq, 0, sizeof(mreq));
	mreq.handle = creq.handle;
	ret = drmIoctl(drm_dev.fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
	if (ret) {
		err("DRM_IOCTL_MODE_MAP_DUMB fail");
		return -1;
	}

	buf->offset = mreq.offset;

	/* perform actual memory mapping */
	buf->map = mmap(0, creq.size, PROT_READ | PROT_WRITE, MAP_SHARED, drm_dev.fd, mreq.offset);
	if (buf->map == MAP_FAILED) {
		err("mmap fail");
		return -1;
	}

	/* clear the framebuffer to 0 (= full transparency in ARGB8888) */
	memset(buf->map, 0, creq.size);

#if 1
	/* create framebuffer object for the dumb-buffer */
	handles[0] = creq.handle;
	pitches[0] = creq.pitch;
	offsets[0] = 0;
#else
	offsets[0] = 0;
	handles[0] = creq.handle;
	pitches[0] = creq.pitch;
	pitches[1] = pitches[0];
	offsets[1] = pitches[0] * drm_dev.height;
	handles[1] = creq.handle;
#endif
	ret = drmModeAddFB2(drm_dev.fd, drm_dev.width, drm_dev.height, argb,
			    handles, pitches, offsets, &buf->fb_handle, 0);
	if (ret) {
		err("drmModeAddFB fail");
		return -1;
	}

	return 0;
}

static int drm_allocate_dumb(struct drm_buffer *buf)
{
	struct drm_mode_create_dumb creq;
	struct drm_mode_map_dumb mreq;
	uint32_t handles[4] = {0}, pitches[4] = {0}, offsets[4] = {0};
	int ret;

	/* create dumb buffer */
	memset(&creq, 0, sizeof(creq));
	
	creq.width = (drm_dev.width+15)/16*16;
#if LV_COLOR_DEPTH == 32
	creq.height = drm_dev.height;  //* 4;
	creq.bpp = LV_COLOR_DEPTH;  //8
#elif LV_COLOR_DEPTH == 8
    creq.height = drm_dev.height * 3 / 2;
	creq.bpp = LV_COLOR_DEPTH;  //8
#endif
	ret = drmIoctl(drm_dev.fd, DRM_IOCTL_MODE_CREATE_DUMB, &creq);
	if (ret < 0) {
		err("DRM_IOCTL_MODE_CREATE_DUMB fail");
		return -1;
	}

	buf->handle = creq.handle;
	buf->pitch = creq.pitch;
	dbg("pitch %d", buf->pitch);
	buf->size = creq.size;
	dbg("size %d", buf->size);

	/* get drm fd */
	int ret_dbuf;
	struct drm_prime_handle prime;
	memset(&prime, 0, sizeof prime);
	prime.handle = buf->handle;
	ret_dbuf = ioctl(drm_dev.fd, DRM_IOCTL_PRIME_HANDLE_TO_FD, &prime);
	if(ret_dbuf)
	{
		printf("PRIME_HANDLE_TO_FD failed");
		while(1);
	}
	// printf("dbuf_fd = %d\n", prime.fd);
	buf->dbuf_fd = prime.fd;

	/* prepare buffer for memory mapping */
	memset(&mreq, 0, sizeof(mreq));
	mreq.handle = creq.handle;
	ret_dbuf = drmIoctl(drm_dev.fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
	if (ret_dbuf) {
		err("DRM_IOCTL_MODE_MAP_DUMB fail");
		return -1;
	}

	buf->offset = mreq.offset;

	/* perform actual memory mapping */
	buf->map = mmap(0, creq.size, PROT_READ | PROT_WRITE, MAP_SHARED, drm_dev.fd, mreq.offset);
	if (buf->map == MAP_FAILED) {
		err("mmap fail");
		return -1;
	}

	/* clear the framebuffer to 0 (= full transparency in ARGB8888) */
	memset(buf->map, 0, creq.size);

#if LV_COLOR_DEPTH == 32
	/* create framebuffer object for the dumb-buffer */
	handles[0] = creq.handle;
	pitches[0] = creq.pitch;
	offsets[0] = 0;
#elif LV_COLOR_DEPTH == 8
	offsets[0] = 0;
	handles[0] = creq.handle;
	pitches[0] = creq.pitch;
	pitches[1] = pitches[0];
	offsets[1] = pitches[0] * drm_dev.height;
	handles[1] = creq.handle;
#endif
	ret = drmModeAddFB2(drm_dev.fd, drm_dev.width, drm_dev.height, drm_dev.fourcc,
			    handles, pitches, offsets, &buf->fb_handle, 0);
	if (ret) {
		err("drmModeAddFB fail");
		return -1;
	}

	return 0;
}

void drm_destory_dumb(struct drm_buffer *buf)
{
	struct drm_mode_destroy_dumb destroy = {};

	drmModeRmFB(drm_dev.fd, buf->fb_handle);

	munmap(buf->map, buf->size);

	destroy.handle = buf->handle;

	drmIoctl(drm_dev.fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy);
}

static int drm_setup_buffers(void)
{
	int ret;
#if 0
	/* Allocate DUMB buffers */
	ret = drm_allocate_dumb(&drm_dev.drm_bufs[0]);
	if (ret)
		return ret;

	ret = drm_allocate_dumb(&drm_dev.drm_bufs[1]);
	if (ret)
		return ret;
#else
	for(uint32_t i = 0; i < DRM_BUFFERS_COUNT; i++)
	{
		ret = drm_allocate_dumb(&drm_dev.drm_bufs[i]);
		if (ret)
		{
			printf("ERR: drm alloc buffer err\n");
			return ret;
		}
	}
	for(uint32_t i = 0; i < DRM_BUFFERS_COUNT; i++)
	{
		ret = drm_allocate_dumb_argb(&drm_dev.drm_bufs_argb[i]);
		if (ret)
		{
			printf("ERR: drm alloc buffer err\n");
			return ret;
		}
	}
	// ret = drm_allocate_dumb(&drm_dev.drm_bufs_show);
	// if (ret)
	// {
	// 	printf("ERR: drm alloc buffer err\n");
	// 	return ret;
	// }
#endif
	printf("----------------drm_setup_buffers --------------------------------- \n");
	/* Set buffering handling */
	drm_dev.cur_bufs[0] = NULL;
	drm_dev.cur_bufs[1] = &drm_dev.drm_bufs[0];

	return 0;
}

void drm_wait_vsync(void)
{
	int ret;
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(drm_dev.fd, &fds);

	do {
		ret = select(drm_dev.fd + 1, &fds, NULL, NULL, NULL);
	} while (ret == -1 && errno == EINTR);

	if (ret < 0) {
		err("select failed: %s", strerror(errno));
		drmModeAtomicFree(drm_dev.req);
		drm_dev.req = NULL;
		return;
	}

	if (FD_ISSET(drm_dev.fd, &fds))
		drmHandleEvent(drm_dev.fd, &drm_dev.drm_event_ctx);

	drmModeAtomicFree(drm_dev.req);
	drm_dev.req = NULL;
}

void drm_get_sizes(int16_t *width, int16_t *height, uint32_t *dpi)
{
	if (width)
		*width = drm_dev.width;

	if (height)
		*height = drm_dev.height;

	if (dpi && drm_dev.mmWidth)
		*dpi = DIV_ROUND_UP(drm_dev.width * 25400, drm_dev.mmWidth * 1000);
}

int  drm_init(void)
{
	int ret;

	ret = drm_setup(DRM_FOURCC);
	if (ret) {
		close(drm_dev.fd);
		drm_dev.fd = -1;
		return ret;
	}

	ret = drm_setup_buffers();
	if (ret) {
		err("DRM buffer allocation failed");
		close(drm_dev.fd);
		drm_dev.fd = -1;
		return ret;
	}
	return 0;
}

void drm_exit(void)
{
	close(drm_dev.fd);
	drm_dev.fd = -1;
}

// static int terminate = 1;

// static void sigint_handler(int arg)
// {
// 	terminate = 0;
// }

int drm_get_resolution(struct drm_dev *dev, uint32_t *width, uint32_t *height)
{
	int ret = drm_setup(DRM_FOURCC);
	if (ret) {
		close(drm_dev.fd);
		drm_dev.fd = -1;
		return ret;
	}
	*width = drm_dev.mode.hdisplay;
	*height = drm_dev.mode.vdisplay;
	close(drm_dev.fd);
	// fix draw frame
	char cmd[64];
	uint32_t val = ((*width - 1) & 0xFFF) | (((*height - 1) & 0xFFF) << 16) | (1UL << 15);
	snprintf(cmd, sizeof(cmd), "devmem 0x92700780 32 0x%08x", val);
	system(cmd);

	return 0;
}

/* drm code end */
