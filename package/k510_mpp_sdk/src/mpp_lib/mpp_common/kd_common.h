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
  File Name     : kd_common.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef __KD_COMMON_H__
#define __KD_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void            KD_VOID;
typedef unsigned char   KD_U8;
typedef unsigned short  KD_U16;
typedef unsigned int    KD_U32;
typedef int             KD_S32;
typedef unsigned long   KD_U64;
typedef char            KD_CHAR;
typedef float           KD_FLOAT;

#define KD_SUCCESS      0
#define KD_FAILURE      (-1)

#define KD_TRUE         1
#define KD_FALSE        0


typedef KD_S32          KD_RET;
typedef KD_S32          VENC_CHN;
typedef KD_S32          VI_DEV;
typedef KD_S32          VI_PIPE;
typedef KD_S32          VO_DEV;
typedef KD_S32          VO_LAYER;
typedef KD_S32          VPS_HANDLE;


typedef enum kdPIXEL_FORMAT_E
{
    PIXEL_FORMAT_Y = 0,
    PIXEL_FORMAT_NV12 = 1,
    PIXEL_FORMAT_YUV422SP = 2,
    PIXEL_FORMAT_YUV420 = 3,
    PIXEL_FORMAT_YUV400 = 4,
    PIXEL_FORMAT_RGB888 = 5,
    PIXEL_FORMAT_ARGB = 6,
    PIXEL_FORMAT_BUTT,
} PIXEL_FORMAT_E;

typedef struct kdVIDEO_FRAME_INFO_S
{
    PIXEL_FORMAT_E      enPixelFormat;
    KD_U32              u32Width;
    KD_U32              u32Height;
    KD_U64              u64PhyData;
    KD_U64              u64VirData;
    KD_U32              u32DataSize;
} VIDEO_FRAME_INFO_S;


#ifdef __cplusplus
}
#endif

#endif // __KD_COMMON_H__
