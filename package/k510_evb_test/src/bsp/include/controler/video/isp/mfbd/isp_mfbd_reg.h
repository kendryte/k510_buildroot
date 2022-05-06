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
#ifndef _ISP_MFBD_REG_DEF_H_
#define _ISP_MFBD_REG_DEF_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_en                        : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 3   ; /* [3 ..1 ]  */
        unsigned int    mfbd_format_cfg                : 1   ; /* [4 ]      */
        unsigned int    reserved1                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_input_height              : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    mfbd_input_width               : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_INPUT_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_y_data_buf_base0          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_Y_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_y_data_buf_base1          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_Y_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_y_data_stride             : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_Y_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_y_head_buf_base0          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_Y_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_y_head_buf_base1          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_Y_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_y_head_stride             : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_Y_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_uv_data_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_UV_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_uv_data_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_UV_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_uv_data_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_UV_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_uv_head_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_UV_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_uv_head_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_UV_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_uv_head_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_UV_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_yl_data_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_YL_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_yl_data_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_YL_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_yl_data_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_YL_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_yl_head_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_YL_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_yl_head_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_YL_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbd_yl_head_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBD_YL_HEAD_LINE_STRIDE;

typedef struct
{
    volatile U_ISP_MFBD_CTL                     ISP_MFBD_CTL;
    volatile U_ISP_MFBD_INPUT_SIZE              ISP_MFBD_INPUT_SIZE;
    volatile unsigned int                       reserved0[6];
    volatile U_ISP_MFBD_Y_DATA_BUF_BASE0        ISP_MFBD_Y_DATA_BUF_BASE0;
    volatile U_ISP_MFBD_Y_DATA_BUF_BASE1        ISP_MFBD_Y_DATA_BUF_BASE1;
    volatile U_ISP_MFBD_Y_DATA_LINE_STRIDE      ISP_MFBD_Y_DATA_LINE_STRIDE;
    volatile U_ISP_MFBD_Y_HEAD_BUF_BASE0        ISP_MFBD_Y_HEAD_BUF_BASE0;
    volatile U_ISP_MFBD_Y_HEAD_BUF_BASE1        ISP_MFBD_Y_HEAD_BUF_BASE1;
    volatile U_ISP_MFBD_Y_HEAD_LINE_STRIDE      ISP_MFBD_Y_HEAD_LINE_STRIDE;
    volatile U_ISP_MFBD_UV_DATA_BUF_BASE0       ISP_MFBD_UV_DATA_BUF_BASE0;
    volatile U_ISP_MFBD_UV_DATA_BUF_BASE1       ISP_MFBD_UV_DATA_BUF_BASE1;
    volatile U_ISP_MFBD_UV_DATA_LINE_STRIDE     ISP_MFBD_UV_DATA_LINE_STRIDE;
    volatile U_ISP_MFBD_UV_HEAD_BUF_BASE0       ISP_MFBD_UV_HEAD_BUF_BASE0;
    volatile U_ISP_MFBD_UV_HEAD_BUF_BASE1       ISP_MFBD_UV_HEAD_BUF_BASE1;
    volatile U_ISP_MFBD_UV_HEAD_LINE_STRIDE     ISP_MFBD_UV_HEAD_LINE_STRIDE;
    volatile U_ISP_MFBD_YL_DATA_BUF_BASE0       ISP_MFBD_YL_DATA_BUF_BASE0;
    volatile U_ISP_MFBD_YL_DATA_BUF_BASE1       ISP_MFBD_YL_DATA_BUF_BASE1;
    volatile U_ISP_MFBD_YL_DATA_LINE_STRIDE     ISP_MFBD_YL_DATA_LINE_STRIDE;
    volatile U_ISP_MFBD_YL_HEAD_BUF_BASE0       ISP_MFBD_YL_HEAD_BUF_BASE0;
    volatile U_ISP_MFBD_YL_HEAD_BUF_BASE1       ISP_MFBD_YL_HEAD_BUF_BASE1;
    volatile U_ISP_MFBD_YL_HEAD_LINE_STRIDE     ISP_MFBD_YL_HEAD_LINE_STRIDE;
    volatile unsigned int                       reserved1[6];
} S_ISP_MFBD_REGS_TYPE;

/*driver function*/
int ISP_MFBD_DRV_SET_MfbdCtl(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdCtl(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdInputSize(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdInputSize(S_ISP_MFBD_REGS_TYPE *pstRegs);
//Y data
int ISP_MFBD_DRV_SET_MfbdYDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
//Y header
//int ISP_MFBD_DRV_SET_MfbdYlHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
//int ISP_MFBD_DRV_GET_MfbdYlHeadStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
//UV data
int ISP_MFBD_DRV_SET_MfbdUvDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdUvDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdUvDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdUvDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdUvDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdUvDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
//UV header
int ISP_MFBD_DRV_SET_MfbdUvHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdUvHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdUvHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdUvHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdUvHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdUvHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
//YL data
int ISP_MFBD_DRV_SET_MfbdYlDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYlDataBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYlDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYlDataBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYlDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYlDataLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
//YL header
int ISP_MFBD_DRV_SET_MfbdYlHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYlHeadBufBase0(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYlHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYlHeadBufBase1(S_ISP_MFBD_REGS_TYPE *pstRegs);
int ISP_MFBD_DRV_SET_MfbdYlHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBD_DRV_GET_MfbdYlHeadLineStride(S_ISP_MFBD_REGS_TYPE *pstRegs);
//debug
int ISP_MFBD_DRV_GET_MfbdRegsVal(S_ISP_MFBD_REGS_TYPE *pstRegs);
#endif  /*_ISP_MFBD_REG_DEF_H_*/

