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
  File Name     : kd_vo.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include <drm_fourcc.h>
#include "kd_vo.h"
#include "k510_drm.h"
#include "kd_vo_log.h"

#define MAX_VO_DEV_NUM 2
#define MAX_VO_LAYER_NUM 7
#define VO_DEVICE_NAME "/dev/dri/card0"

#define DRM_KENDRYTE_DRAW_FRAME         0x00

#define DRM_IOCTL_KENDRYTE_DRAW_FRAME   DRM_IOWR(DRM_COMMAND_BASE + \
                DRM_KENDRYTE_DRAW_FRAME, struct vo_draw_frame)

typedef struct kdVO_DRM_OBJ_S
{
    drmModeObjectProperties     *props;
	drmModePropertyRes          **props_info;
    KD_U32                      u32ObjId;
} VO_DRM_OBJ_S;

typedef struct kdVO_FRAME_BUFFER_S
{
    KD_S32      s32OffsetX;
	KD_S32      s32OffsetY;
	KD_U32      u32Width;
	KD_U32      u32Height;
	KD_U32      u32Fourcc;
	KD_U32      u32Bpp;
	KD_U32      u32Pitch;
	KD_U32      u32Size;
	KD_U32      u32Handle;
	KD_U32      u32Fb;
	KD_S32      s32DmaBufFd;
	KD_VOID     *pMap;
} VO_FRAME_BUFFER_S;

typedef struct kdVO_HANDLE_S
{
    KD_CHAR             devName[128];
    KD_U32              u32Width;
    KD_U32              u32Height;
    PIXEL_FORMAT_E      enPixelFormat;
    KD_S32              s32DevFd;
    KD_U32              u32ConnId;
    KD_U32              u32EncId;
    KD_U32              u32CrtcId;
    KD_U32              u32CrtcIdx;
    drmModeModeInfo     mode;
    KD_U32              u32ModeBlobId;
    VO_DRM_OBJ_S        stConn;
    VO_DRM_OBJ_S        stCrtc;
    VO_DRM_OBJ_S        *pstPlanes;
    KD_U32              *pu32PlanesId;
    KD_U32              u32PlaneCount;
    bool                bFlipPending;
    bool                bCleanup;
    KD_U32              u32LayerCount;
} VO_HANDLE_S;

typedef struct kdVO_LAYER_HANDLE_S
{
    PIXEL_FORMAT_E      enPixFmt;
    KD_U32              u32LayerPicWidth;
    KD_U32              u32LayerPicHeight;
    VO_FRAME_BUFFER_S   stFrameBuf;
} VO_LAYER_HANDLE_S;

static VO_HANDLE_S *pVoHandle[MAX_VO_DEV_NUM] = {NULL};
static VO_LAYER_HANDLE_S *pVoLayerHandle[MAX_VO_LAYER_NUM] = {NULL};

static KD_S32 findDrmCrtc(VO_DEV VoDev, drmModeRes *res, drmModeConnector *conn)
{
    drmModeEncoder *enc;

    if (conn->encoder_id)
		enc = drmModeGetEncoder(pVoHandle[VoDev]->s32DevFd, conn->encoder_id);
	else
		enc = NULL;

    if (enc)
    {
		if (enc->crtc_id > 0)
        {
			pVoHandle[VoDev]->u32ConnId = conn->connector_id;
			pVoHandle[VoDev]->u32EncId = enc->encoder_id;
			pVoHandle[VoDev]->u32CrtcId = enc->crtc_id;
			for (int i = 0; i < res->count_crtcs; ++i)
            {
				if (pVoHandle[VoDev]->u32CrtcId == res->crtcs[i])
                {
					pVoHandle[VoDev]->u32CrtcIdx = i;
					break;
				}
			}
			drmModeFreeEncoder(enc);
			return 0;
		}
		drmModeFreeEncoder(enc);
	}

    for (int i = 0; i < conn->count_encoders; ++i)
    {
        enc = drmModeGetEncoder(pVoHandle[VoDev]->s32DevFd, conn->encoders[i]);
		if (!enc) {
			KD_VO_LOG_DEBUG("%s: cannot retrieve encoder\n", __func__);
			continue;
		}

        for (int j = 0; j < res->count_crtcs; ++j)
        {
            if (!(enc->possible_crtcs & (1 << j)))
				continue;

            if (res->crtcs[j] > 0) {
				pVoHandle[VoDev]->u32ConnId = conn->connector_id;
				pVoHandle[VoDev]->u32EncId = enc->encoder_id;
				pVoHandle[VoDev]->u32CrtcId = res->crtcs[j];
				pVoHandle[VoDev]->u32CrtcIdx = j;
				drmModeFreeEncoder(enc);
				return 0;
			}
        }
        drmModeFreeEncoder(enc);
    }

    return -1;
}

static KD_S32 findDrmPlane(VO_DEV VoDev)
{
    drmModePlaneResPtr plane_res;
	KD_U32 plane_count = 0;

    plane_res = drmModeGetPlaneResources(pVoHandle[VoDev]->s32DevFd);
	if (!plane_res) {
		KD_VO_LOG_DEBUG("%s: drmModeGetPlaneResources failed\n", __func__);
		return -1;
	}

    pVoHandle[VoDev]->pu32PlanesId = (KD_U32 *)malloc(plane_res->count_planes * sizeof(KD_U32));

    for (int i = 0; i < plane_res->count_planes; i++)
    {
        int plane_id = plane_res->planes[i];
		drmModePlanePtr plane = drmModeGetPlane(pVoHandle[VoDev]->s32DevFd, plane_id);
		if (!plane) {
			KD_VO_LOG_DEBUG("%s: drmModeGetPlane(%u) failed.\n", __func__);
			continue;
		}

        if (plane->possible_crtcs & (1 << pVoHandle[VoDev]->u32CrtcIdx)) {
			pVoHandle[VoDev]->pu32PlanesId[plane_count] = plane_id;
			plane_count++;
		}
		drmModeFreePlane(plane);
    }

    drmModeFreePlaneResources(plane_res);

    pVoHandle[VoDev]->u32PlaneCount = plane_count;
    if (plane_count)
		return 0;

    free(pVoHandle[VoDev]->pu32PlanesId);
	pVoHandle[VoDev]->pu32PlanesId = NULL;
	KD_VO_LOG_DEBUG("%s: vo couldn't find a plane\n");

	return -1;
}

static KD_VOID getDrmObjectProperties(int fd, VO_DRM_OBJ_S *obj, uint32_t type)
{
    const char *type_str;
	unsigned int i;

	obj->props = drmModeObjectGetProperties(fd, obj->u32ObjId, type);
	if (!obj->props) {
		switch (type) {
		case DRM_MODE_OBJECT_CONNECTOR:
			type_str = "connector";
			break;
		case DRM_MODE_OBJECT_PLANE:
			type_str = "plane";
			break;
		case DRM_MODE_OBJECT_CRTC:
			type_str = "CRTC";
			break;
		default:
			type_str = "unknown type";
			break;
		}

		return;
	}

	obj->props_info = (drmModePropertyRes **)calloc(obj->props->count_props, sizeof(obj->props_info));

	for (i = 0; i < obj->props->count_props; i++)
		obj->props_info[i] = drmModeGetProperty(fd, obj->props->props[i]);
}

static KD_VOID finiDrmObject(VO_DRM_OBJ_S *pstObj)
{
    if (!pstObj->props)
		return;
	for (int i = 0; i < pstObj->props->count_props; i++)
		drmModeFreeProperty(pstObj->props_info[i]);
	free(pstObj->props_info);
	drmModeFreeObjectProperties(pstObj->props);
	pstObj->props = NULL;
}

static KD_S32 getDrmObjects(VO_DEV VoDev)
{
    KD_S32 fd = pVoHandle[VoDev]->s32DevFd;

    VO_DRM_OBJ_S *conn = &pVoHandle[VoDev]->stConn;
	VO_DRM_OBJ_S *crtc = &pVoHandle[VoDev]->stCrtc;
	VO_DRM_OBJ_S *plane;

    conn->u32ObjId = pVoHandle[VoDev]->u32ConnId;
	getDrmObjectProperties(fd, conn, DRM_MODE_OBJECT_CONNECTOR);
	if (!conn->props)
		goto out_conn;

    crtc->u32ObjId = pVoHandle[VoDev]->u32CrtcId;
	getDrmObjectProperties(fd, crtc, DRM_MODE_OBJECT_CRTC);
	if (!crtc->props)
		goto out_crtc;

    pVoHandle[VoDev]->pstPlanes = (VO_DRM_OBJ_S *)calloc(pVoHandle[VoDev]->u32PlaneCount, sizeof(VO_DRM_OBJ_S));
	for (int i = 0; i < pVoHandle[VoDev]->u32PlaneCount; i++)
    {
		plane = &pVoHandle[VoDev]->pstPlanes[i];
		plane->u32ObjId = pVoHandle[VoDev]->pu32PlanesId[i];
		getDrmObjectProperties(fd, plane, DRM_MODE_OBJECT_PLANE);
		if (!plane->props)
			goto out_plane;
	}

    return 0;

out_plane:
	for (int i = 0; i < pVoHandle[VoDev]->u32PlaneCount; i++) {
		if (pVoHandle[VoDev]->pstPlanes[i].props)
			finiDrmObject(&pVoHandle[VoDev]->pstPlanes[i]);
	}
	free(pVoHandle[VoDev]->pstPlanes);
	pVoHandle[VoDev]->pstPlanes = NULL;
	finiDrmObject(crtc);
out_crtc:
	finiDrmObject(conn);
out_conn:
	KD_VO_LOG_DEBUG("vo cannot get objects properties\n");
	return -1;
}

static KD_S32 findDrmConnector(VO_DEV VoDev)
{
    bool find = false;
    int ret;

    drmModeRes          *res;
    drmModeConnector    *conn;

    res = drmModeGetResources(pVoHandle[VoDev]->s32DevFd);
    if (!res)
    {
        KD_VO_LOG_DEBUG("%s: vo get resources failed.\n", __func__);
        return KD_FAILURE;
    }

    for (int i = 0; i < res->count_connectors; ++i)
    {
        conn = drmModeGetConnector(pVoHandle[VoDev]->s32DevFd, res->connectors[i]);
        if (!conn)
        {
            KD_VO_LOG_DEBUG("%s: vo get connector invalid.\n", __func__);
            continue;
        }

        if (conn->connection != DRM_MODE_CONNECTED)
        {
            KD_VO_LOG_DEBUG("%s: vo get connector unused.\n", __func__);
            goto next;
        }

        if (conn->count_modes == 0) {
			KD_VO_LOG_DEBUG("%s: vo no valid mode for connector %u\n", __func__, conn->connector_id);
			goto next;
		}

        memcpy(&pVoHandle[VoDev]->mode, &conn->modes[0], sizeof(pVoHandle[VoDev]->mode));

        if (findDrmCrtc(VoDev, res, conn))
            goto next;

        if (findDrmPlane(VoDev))
            goto next;

        if (getDrmObjects(VoDev)) {
			free(pVoHandle[VoDev]->pu32PlanesId);
			pVoHandle[VoDev]->pu32PlanesId = NULL;
			goto next;
		}

        find = true;

next:
		drmModeFreeConnector(conn);
		if (find)
			break;
    }

    if (!find)
		KD_VO_LOG_DEBUG("%s: vo couldn't create any outputs.\n", __func__);
	/* free resources again */
	drmModeFreeResources(res);
	return 0;
}

static KD_VOID freeDrmBuf(VO_DEV VoDev)
{
    finiDrmObject(&pVoHandle[VoDev]->stConn);
	finiDrmObject(&pVoHandle[VoDev]->stCrtc);
	if (pVoHandle[VoDev]->pstPlanes) {
		for (int i = 0; i < pVoHandle[VoDev]->u32PlaneCount; i++) {
			if (pVoHandle[VoDev]->pstPlanes[i].props)
				finiDrmObject(&pVoHandle[VoDev]->pstPlanes[i]);
		}
		free(pVoHandle[VoDev]->pstPlanes);
		pVoHandle[VoDev]->pstPlanes = NULL;
	}

    drmModeDestroyPropertyBlob(pVoHandle[VoDev]->s32DevFd, pVoHandle[VoDev]->u32ModeBlobId);

    free(pVoHandle[VoDev]->pu32PlanesId);
	close(pVoHandle[VoDev]->s32DevFd);

    return;
}

static KD_S32 setDrmObjectProperty(drmModeAtomicReq *req, VO_DRM_OBJ_S *obj, const char *name, uint64_t value)
{
    uint32_t prop_id = 0;

	for (int i = 0; i < obj->props->count_props; i++) {
		if (!strcmp(obj->props_info[i]->name, name)) {
			prop_id = obj->props_info[i]->prop_id;
			break;
		}
	}

	if (prop_id == 0) {
		KD_VO_LOG_DEBUG("%s: no object property.\n", __func__);
		return -EINVAL;
	}

	return drmModeAtomicAddProperty(req, obj->u32ObjId, prop_id, value);
}

KD_S32  KD_MPI_VO_Init()
{
    initLog();

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_SetPubAttr(VO_DEV VoDev)
{
    if (VoDev < 0 || VoDev >= MAX_VO_DEV_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo device number %d is out of range.\n", __func__, VoDev);
        return KD_FAILURE;
    }

    if (!pVoHandle[VoDev])
    {
        pVoHandle[VoDev] = (VO_HANDLE_S *)calloc(1, sizeof(VO_HANDLE_S));
        if (!pVoHandle[VoDev])
        {
            KD_VO_LOG_ERROR("%s: the vo attributer set is failed.\n", __func__);
            return KD_FAILURE;
        }
    }

    if (VoDev == 0)
        strcpy(pVoHandle[VoDev]->devName, VO_DEVICE_NAME);

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_Enable(VO_DEV VoDev)
{
    KD_RET kdRet = KD_SUCCESS;
    drmModeAtomicReq *req;
    VO_DRM_OBJ_S *obj;
    KD_U64  u64Cap;

    if (VoDev < 0 || VoDev >= MAX_VO_DEV_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo device number %d is out of range.\n", __func__, VoDev);
        return KD_FAILURE;
    }

    if (pVoHandle[VoDev]->s32DevFd > 0)
    {
        KD_VO_LOG_ERROR("%S: the device has been enable.\n", __func__);
        return KD_SUCCESS;
    }

    pVoHandle[VoDev]->s32DevFd = open(pVoHandle[VoDev]->devName, O_RDWR | O_CLOEXEC);
    if (pVoHandle[VoDev]->s32DevFd < 0) {
		KD_VO_LOG_ERROR("%s: vo device enable failed.\n", __func__);
		return KD_FAILURE;
	}

    kdRet = drmSetClientCap(pVoHandle[VoDev]->s32DevFd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
    if (kdRet)
    {
        KD_VO_LOG_ERROR("%s: set vo cap failed.\n", __func__);
        close(pVoHandle[VoDev]->s32DevFd);
        return KD_FAILURE;
    }

    kdRet = drmSetClientCap(pVoHandle[VoDev]->s32DevFd, DRM_CLIENT_CAP_ATOMIC, 1);
    if (kdRet)
    {
        KD_VO_LOG_ERROR("%s: set vo cap failed.\n", __func__);
        close(pVoHandle[VoDev]->s32DevFd);
        return KD_FAILURE;
    }

    if (drmGetCap(pVoHandle[VoDev]->s32DevFd, DRM_CAP_DUMB_BUFFER, &u64Cap) < 0 || !u64Cap)
    {
        KD_VO_LOG_ERROR("%s: set vo get cap failed.\n", __func__);
        close(pVoHandle[VoDev]->s32DevFd);
        return KD_FAILURE;
    }

    if (drmGetCap(pVoHandle[VoDev]->s32DevFd, DRM_CAP_CRTC_IN_VBLANK_EVENT, &u64Cap) < 0 || !u64Cap)
    {
        KD_VO_LOG_ERROR("%s: set vo get cap failed.\n", __func__);
        close(pVoHandle[VoDev]->s32DevFd);
        return KD_FAILURE;
    }

    kdRet = findDrmConnector(VoDev);
    if (kdRet != KD_SUCCESS)
    {
        KD_VO_LOG_ERROR("%s: set vo find connector failed.\n", __func__);
        close(pVoHandle[VoDev]->s32DevFd);
        return KD_FAILURE;
    }

    kdRet = drmModeCreatePropertyBlob(pVoHandle[VoDev]->s32DevFd, &pVoHandle[VoDev]->mode,
					     sizeof(pVoHandle[VoDev]->mode),
					     &pVoHandle[VoDev]->u32ModeBlobId);
    if (kdRet != KD_SUCCESS)
    {
		KD_VO_LOG_ERROR("%s: couldn't create a blob property\n", __func__);
		return kdRet;
	}

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_EnableVideoLayer(VO_LAYER VoLayer, const VO_VIDEO_LAYER_ATTR_S *pstLayerAttr)
{
    if (VoLayer < 0 || VoLayer >= MAX_VO_LAYER_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo layer %d is out of range.\n", __func__, VoLayer);
        return KD_FAILURE;
    }

    if (pVoLayerHandle[VoLayer] == NULL)
    {
        pVoLayerHandle[VoLayer] = (VO_LAYER_HANDLE_S *)calloc(1, sizeof(VO_LAYER_HANDLE_S));
        if (!pVoLayerHandle[VoLayer])
        {
            KD_VO_LOG_ERROR("%s: the vo layer set is failed.\n", __func__);
            return KD_FAILURE;
        }
    }

    KD_S32 s32DevId = VoLayer / MAX_VO_LAYER_NUM;

    pVoLayerHandle[VoLayer]->enPixFmt = pstLayerAttr->enPixelFormat;
    pVoLayerHandle[VoLayer]->u32LayerPicWidth = pstLayerAttr->u32PicWidth;
    pVoLayerHandle[VoLayer]->u32LayerPicHeight = pstLayerAttr->u32PicHeight;

    struct drm_mode_create_dumb creq;
	struct drm_mode_destroy_dumb dreq;
	struct drm_mode_map_dumb mreq;
	struct drm_prime_handle prime;
    int ret;
	uint32_t handles[4] = { 0 }, pitches[4] = { 0 }, offsets[4] = { 0 };

    /* create dumb buffer */
	memset(&creq, 0, sizeof(creq));
    pVoLayerHandle[VoLayer]->stFrameBuf.u32Width = pVoLayerHandle[VoLayer]->u32LayerPicWidth;
    pVoLayerHandle[VoLayer]->stFrameBuf.u32Height = pVoLayerHandle[VoLayer]->u32LayerPicHeight;
    pVoLayerHandle[VoLayer]->stFrameBuf.s32OffsetX = pstLayerAttr->u32OffsetX;
    pVoLayerHandle[VoLayer]->stFrameBuf.s32OffsetY = pstLayerAttr->u32OffsetY;
    pVoLayerHandle[VoLayer]->stFrameBuf.u32Bpp = pstLayerAttr->u32Bpp;
	if (pstLayerAttr->enPixelFormat == PIXEL_FORMAT_NV12) 
    {
        pVoLayerHandle[VoLayer]->stFrameBuf.u32Fourcc = DRM_FORMAT_NV12;
		pVoLayerHandle[VoLayer]->stFrameBuf.u32Width = (pVoLayerHandle[VoLayer]->u32LayerPicWidth + 0xf) & (~0xful);
		creq.height = pVoLayerHandle[VoLayer]->u32LayerPicHeight * 3 / 2;
	}
    else if (pstLayerAttr->enPixelFormat == PIXEL_FORMAT_ARGB)
    {
        pVoLayerHandle[VoLayer]->stFrameBuf.u32Fourcc = DRM_FORMAT_ARGB8888;
		creq.height = pVoLayerHandle[VoLayer]->u32LayerPicHeight;
	}
    else if(pstLayerAttr->enPixelFormat == PIXEL_FORMAT_RGB888)
    {
        pVoLayerHandle[VoLayer]->stFrameBuf.u32Fourcc = DRM_FORMAT_RGB888;
		creq.height = pVoLayerHandle[VoLayer]->u32LayerPicHeight;
    }

    creq.width = pVoLayerHandle[VoLayer]->stFrameBuf.u32Width;
	creq.bpp = pstLayerAttr->u32Bpp;

    ret = drmIoctl(pVoHandle[s32DevId]->s32DevFd, DRM_IOCTL_MODE_CREATE_DUMB, &creq);
    if (ret < 0)
    {
        KD_VO_LOG_ERROR("%s: the vo framebuffer create failed. width = %d, height = %d\n", __func__, creq.width, creq.height);
        return KD_FAILURE;
    }

    pVoLayerHandle[VoLayer]->stFrameBuf.u32Size = creq.size;
    pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle = creq.handle;
    pVoLayerHandle[VoLayer]->stFrameBuf.u32Pitch = creq.pitch;

    if (pVoLayerHandle[VoLayer]->stFrameBuf.u32Fourcc == DRM_FORMAT_NV12)
    {
        handles[1] = pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle;
        pitches[1] = pVoLayerHandle[VoLayer]->stFrameBuf.u32Pitch;
        offsets[1] = pVoLayerHandle[VoLayer]->stFrameBuf.u32Pitch * pVoLayerHandle[VoLayer]->stFrameBuf.u32Height;
    }

    handles[0] = pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle;
    pitches[0] = pVoLayerHandle[VoLayer]->stFrameBuf.u32Pitch;
    offsets[0] = 0;

    ret = drmModeAddFB2(pVoHandle[s32DevId]->s32DevFd,
                        pVoLayerHandle[VoLayer]->stFrameBuf.u32Width,
                        pVoLayerHandle[VoLayer]->stFrameBuf.u32Height,
                        pVoLayerHandle[VoLayer]->stFrameBuf.u32Fourcc,
                        handles,
                        pitches,
                        offsets,
                        &pVoLayerHandle[VoLayer]->stFrameBuf.u32Fb,
                        0);
    if (ret)
    {
        KD_VO_LOG_ERROR("%s: the vo layer %d framebuffer create failed.\n", __func__, VoLayer);
        memset(&dreq, 0, sizeof(dreq));
        dreq.handle = pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle;
        drmIoctl(pVoHandle[s32DevId]->s32DevFd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);
        return KD_FAILURE;
    }

    memset(&mreq, 0, sizeof(mreq));
    mreq.handle = pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle;
	ret = drmIoctl(pVoHandle[s32DevId]->s32DevFd, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
	if (ret)
    {
        KD_VO_LOG_ERROR("%s: the vo framebuffer create failed.\n", __func__);
        return KD_FAILURE;
    }

    pVoLayerHandle[VoLayer]->stFrameBuf.pMap = mmap(0, pVoLayerHandle[VoLayer]->stFrameBuf.u32Size, PROT_READ | PROT_WRITE, MAP_SHARED, pVoHandle[s32DevId]->s32DevFd,
			mreq.offset);
	if (pVoLayerHandle[VoLayer]->stFrameBuf.pMap == MAP_FAILED) {
		KD_VO_LOG_ERROR("%s: the vo framebuffer create failed.\n", __func__);
		return KD_FAILURE;
	}

    memset(&prime, 0, sizeof(prime));
	prime.handle = pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle;
	ret = ioctl(pVoHandle[s32DevId]->s32DevFd, DRM_IOCTL_PRIME_HANDLE_TO_FD, &prime);
	if (ret) {
		KD_VO_LOG_ERROR("%s: the vo framebuffer create failed.\n", __func__);
		return KD_FAILURE;
	}

    pVoLayerHandle[VoLayer]->stFrameBuf.s32DmaBufFd = prime.fd;

    pVoHandle[s32DevId]->u32LayerCount++;

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_DisableVideoLayer(VO_LAYER VoLayer)
{
    if (VoLayer < 0 || VoLayer >= MAX_VO_LAYER_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo layer %d is out of range.\n", __func__, VoLayer);
        return KD_FAILURE;
    }

    KD_S32 s32DevId = VoLayer / MAX_VO_LAYER_NUM;
    struct drm_mode_destroy_dumb dreq;

    /* unmap buffer */
	munmap(pVoLayerHandle[VoLayer]->stFrameBuf.pMap, pVoLayerHandle[VoLayer]->stFrameBuf.u32Size);
    /* delete framebuffer */
    drmModeRmFB(pVoHandle[s32DevId]->s32DevFd, pVoLayerHandle[VoLayer]->stFrameBuf.u32Fb);

    /* delete dumb buffer */
	memset(&dreq, 0, sizeof(dreq));
	dreq.handle = pVoLayerHandle[VoLayer]->stFrameBuf.u32Handle;
	drmIoctl(pVoHandle[s32DevId]->s32DevFd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);

    if (pVoLayerHandle[VoLayer])
    {
        free(pVoLayerHandle[VoLayer]);
        pVoLayerHandle[VoLayer] = NULL;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_SendFrame(VO_LAYER VoLayer, VIDEO_FRAME_INFO_S *pstFrame)
{
    if (VoLayer < 0 || VoLayer >= MAX_VO_LAYER_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo layer number %d is out of range.\n", __func__, VoLayer);
        return KD_FAILURE;
    }

    if (pstFrame == NULL)
    {
        KD_VO_LOG_ERROR("%s: the pstFrame is null.\n", __func__);
        return KD_FAILURE;
    }

    if (pstFrame->enPixelFormat == PIXEL_FORMAT_NV12)
    {
        for (int i = 0; i < pstFrame->u32Height; i++)
        {
            memcpy(pVoLayerHandle[VoLayer]->stFrameBuf.pMap + i * pVoLayerHandle[VoLayer]->stFrameBuf.u32Width,
                (KD_U8 *)pstFrame->u64VirData + i * pstFrame->u32Width, pstFrame->u32Width);
        }
        for (int j = 0; j < pstFrame->u32Height/2; j++)
        {
            memcpy(pVoLayerHandle[VoLayer]->stFrameBuf.pMap + pVoLayerHandle[VoLayer]->stFrameBuf.u32Width * pVoLayerHandle[VoLayer]->stFrameBuf.u32Height + j * pVoLayerHandle[VoLayer]->stFrameBuf.u32Width,
                (KD_U8 *)pstFrame->u64VirData + pstFrame->u32Width * pstFrame->u32Height + j * pstFrame->u32Width, pstFrame->u32Width);
        }
    }
    else
    {
        memcpy(pVoLayerHandle[VoLayer]->stFrameBuf.pMap, (KD_VOID *)pstFrame->u64VirData, pstFrame->u32DataSize);
    }

	return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_SetDrawRect(VO_DEV VoDev, RECT_S *rect)
{
    if (VoDev < 0 || VoDev >= MAX_VO_DEV_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo device number %d is out of range.\n", __func__, VoDev);
        return KD_FAILURE;
    }

    int ret;
    struct vo_draw_frame frame;
    frame.crtc_id = pVoHandle[VoDev]->u32CrtcId;
    frame.draw_en = rect->u32Enable;
    frame.frame_num = rect->u32Index;
    frame.line_x_start = rect->u32Left;
    frame.line_x_end = rect->u32Right;
    frame.line_y_start = rect->u32Top;
    frame.line_y_end = rect->u32Bottom;

    if (ret = drmIoctl(pVoHandle[VoDev]->s32DevFd, DRM_IOCTL_KENDRYTE_DRAW_FRAME, &frame) < 0)
    {
        KD_VO_LOG_ERROR("%s: vo draw rect failed.\n", __func__);
        return KD_FAILURE;
    }

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_FrameLayerSync(VO_DEV VoDev)
{
    if (VoDev < 0 || VoDev >= MAX_VO_DEV_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo device number %d is out of range.\n", __func__, VoDev);
        return KD_FAILURE;
    }

    drmModeAtomicReq *req;
    VO_DRM_OBJ_S *obj;
	VO_FRAME_BUFFER_S *buf;
    KD_U32 flags;
    int ret;

    req = drmModeAtomicAlloc();
	/* set id of the CRTC id that the connector is using */
	obj = &pVoHandle[VoDev]->stConn;
	ret = setDrmObjectProperty(req, obj, "CRTC_ID", pVoHandle[VoDev]->u32CrtcId);
    if (ret < 0)
    {
        KD_VO_LOG_ERROR("%s: set crtc_id property failed.\n", __func__);
        drmModeAtomicFree(req);
        return KD_FAILURE;
    }

	obj = &pVoHandle[VoDev]->stCrtc;
	ret = setDrmObjectProperty(req, obj, "MODE_ID", pVoHandle[VoDev]->u32ModeBlobId);
    if (ret < 0)
    {
        KD_VO_LOG_ERROR("%s: set mode_id property failed.\n", __func__);
        drmModeAtomicFree(req);
        return KD_FAILURE;
    }

	ret = setDrmObjectProperty(req, obj, "ACTIVE", 1);
    if (ret < 0)
    {
        KD_VO_LOG_ERROR("%s: set active property failed.\n", __func__);
        drmModeAtomicFree(req);
        return KD_FAILURE;
    }

    KD_U32 u32LayerCount = pVoHandle[VoDev]->u32LayerCount;

    for (int i = 0; i < u32LayerCount; i++)
    {
        buf = &pVoLayerHandle[i]->stFrameBuf;
        if (buf->u32Fourcc == DRM_FORMAT_NV12)
        {
            obj = &pVoHandle[VoDev]->pstPlanes[i];
        }
        else
        {
            obj = &pVoHandle[VoDev]->pstPlanes[i + 4];
        }

        if ((ret = setDrmObjectProperty(req, obj, "FB_ID", buf->u32Fb)) < 0)
        {
            KD_VO_LOG_ERROR("%s: set FB_ID property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "CRTC_ID", pVoHandle[VoDev]->u32CrtcId)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set CRTC_ID property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "SRC_X", 0)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set SRC_X property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "SRC_Y", 0)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set SRC_Y property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "SRC_W", buf->u32Width << 16)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set SRC_W property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "SRC_H", buf->u32Height << 16)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set SRC_H property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "CRTC_X", buf->s32OffsetX)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set CRTC_X property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "CRTC_Y", buf->s32OffsetY)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set CRTC_Y property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "CRTC_W", buf->u32Width)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set CRTC_W property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }

	    if ((ret = setDrmObjectProperty(req, obj, "CRTC_H", buf->u32Height)) < 0)
		{
            KD_VO_LOG_ERROR("%s: set CRTC_H property failed.\n", __func__);
            drmModeAtomicFree(req);
            return KD_FAILURE;
        }
    }

    flags = DRM_MODE_ATOMIC_TEST_ONLY | DRM_MODE_ATOMIC_ALLOW_MODESET;
	if ((ret = drmModeAtomicCommit(pVoHandle[VoDev]->s32DevFd, req, flags, NULL)) < 0) {
		KD_VO_LOG_ERROR("%s: test-only atomic commit failed.\n", __func__);
		drmModeAtomicFree(req);
        return KD_FAILURE;
	}

	flags = DRM_MODE_ATOMIC_ALLOW_MODESET;
	if ((ret = drmModeAtomicCommit(pVoHandle[VoDev]->s32DevFd, req, flags, NULL)) < 0) {
		KD_VO_LOG_ERROR("%s: atomic commit failed.\n", __func__);
		drmModeAtomicFree(req);
        return KD_FAILURE;
	}

    return KD_SUCCESS;
}

KD_S32  KD_MPI_VO_Disable(VO_DEV VoDev)
{
    if (VoDev < 0 || VoDev >= MAX_VO_DEV_NUM)
    {
        KD_VO_LOG_ERROR("%s: the vo device number %d is out of range.\n", __func__, VoDev);
        return KD_FAILURE;
    }

    if (pVoHandle[VoDev]->s32DevFd > 0)
    {
        KD_VO_LOG_DEBUG("%s: the device has been enable.\n", __func__);
        return KD_SUCCESS;
    }

    freeDrmBuf(VoDev);

    if (pVoHandle[VoDev])
    {
        free(pVoHandle[VoDev]);
        pVoHandle[VoDev] = NULL;
    }
}

KD_S32  KD_MPI_VO_Deinit()
{
    return KD_SUCCESS;
}