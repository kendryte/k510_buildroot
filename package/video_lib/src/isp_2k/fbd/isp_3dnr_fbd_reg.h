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

/*
 * isp_fbd_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifndef _ISP_FBD_REG_DEF_H_
#define _ISP_FBD_REG_DEF_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_en                        : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 3   ; /* [3 ..1 ]  */
        unsigned int    fbd_format_cfg                : 1   ; /* [4 ]      */
        unsigned int    reserved1                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_input_height              : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    fbd_input_width               : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_INPUT_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_y_data_buf_base0          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_Y_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_y_data_buf_base1          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_Y_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_y_data_stride             : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_Y_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_y_head_buf_base0          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_Y_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_y_head_buf_base1          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_Y_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_y_head_stride             : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_Y_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_uv_data_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_UV_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_uv_data_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_UV_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_uv_data_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_UV_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_uv_head_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_UV_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_uv_head_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_UV_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_uv_head_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_UV_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_yl_data_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_YL_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_yl_data_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_YL_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_yl_data_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_YL_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_yl_head_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_YL_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_yl_head_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_YL_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fbd_yl_head_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_FBD_YL_HEAD_LINE_STRIDE;

//
#define  ISP_FBD_CTL     				(0x00)
#define  ISP_FBD_INPUT_SIZE     		(0x04)

#define  ISP_FBD_Y_DATA_BUF_BASE0     	(0x20)
#define  ISP_FBD_Y_DATA_BUF_BASE1     	(0x24)
#define  ISP_FBD_Y_DATA_LINE_STRIDE    (0x28)
#define  ISP_FBD_Y_HEAD_BUF_BASE0     	(0x2C)
#define  ISP_FBD_Y_HEAD_BUF_BASE1     	(0x30)
#define  ISP_FBD_Y_HEAD_LINE_STRIDE    (0x34)
#define  ISP_FBD_UV_DATA_BUF_BASE0     (0x38)
#define  ISP_FBD_UV_DATA_BUF_BASE1     (0x3C)
#define  ISP_FBD_UV_DATA_LINE_STRIDE   (0x40)
#define  ISP_FBD_UV_HEAD_BUF_BASE0     (0x44)
#define  ISP_FBD_UV_HEAD_BUF_BASE1     (0x48)
#define  ISP_FBD_UV_HEAD_LINE_STRIDE   (0x4C)
#define  ISP_FBD_YL_DATA_BUF_BASE0     (0x50)
#define  ISP_FBD_YL_DATA_BUF_BASE1     (0x54)
#define  ISP_FBD_YL_DATA_LINE_STRIDE   (0x58)
#define  ISP_FBD_YL_HEAD_BUF_BASE0     (0x5C)
#define  ISP_FBD_YL_HEAD_BUF_BASE1     (0x60)
#define  ISP_FBD_YL_HEAD_LINE_STRIDE   (0x64)

#endif  /*_ISP_FBD_REG_DEF_H_*/

