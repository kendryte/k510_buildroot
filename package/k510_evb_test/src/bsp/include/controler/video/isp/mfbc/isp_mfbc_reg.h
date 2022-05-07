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
#ifndef _ISP_MFBC_REG_DEF_H_
#define _ISP_MFBC_REG_DEF_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_input_height              : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    mfbc_input_width               : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_INPUT_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_out_format_cfg            : 1   ; /* [0 ]      */
        unsigned int    reserved0                      : 31  ; /* [31..1 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_OUT_FORMAT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_data_buf_base0          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_data_buf_base1          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_data_stride             : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_data_wr_blen            : 5   ; /* [4 ..0 ]  */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_DATA_WR_BLEN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_head_buf_base0          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_head_buf_base1          : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_head_stride             : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_y_head_wr_blen            : 5   ; /* [4 ..0 ]  */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_Y_HEAD_WR_BLEN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_data_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_data_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_data_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_data_wr_blen           : 5   ; /* [4 ..0 ]  */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_DATA_WR_BLEN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_head_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_head_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_head_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_uv_head_wr_blen           : 5   ; /* [4 ..0 ]  */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_UV_HEAD_WR_BLEN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_data_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_DATA_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_data_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_DATA_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_data_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_DATA_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_data_wr_blen           : 5   ; /* [4 ..0 ]  */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_DATA_WR_BLEN;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_head_buf_base0         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_HEAD_BUF_BASE0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_head_buf_base1         : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_HEAD_BUF_BASE1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_head_stride            : 15  ; /* [14..0 ]  */
        unsigned int    reserved0                      : 17  ; /* [31..15]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_HEAD_LINE_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mfbc_yl_head_wr_blen           : 5   ; /* [4 ..0 ]  */
        unsigned int    reserved0                      : 27  ; /* [31..5 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_MFBC_YL_HEAD_WR_BLEN;

typedef struct
{
    volatile U_ISP_MFBC_INPUT_SIZE              ISP_MFBC_INPUT_SIZE;
    volatile U_ISP_MFBC_OUT_FORMAT              ISP_MFBC_OUT_FORMAT;
    volatile unsigned int                       reserved0[14];
    volatile U_ISP_MFBC_Y_DATA_BUF_BASE0        ISP_MFBC_Y_DATA_BUF_BASE0;
    volatile U_ISP_MFBC_Y_DATA_BUF_BASE1        ISP_MFBC_Y_DATA_BUF_BASE1;
    volatile U_ISP_MFBC_Y_DATA_LINE_STRIDE      ISP_MFBC_Y_DATA_LINE_STRIDE;
    volatile U_ISP_MFBC_Y_DATA_WR_BLEN          ISP_MFBC_Y_DATA_WR_BLEN;
    volatile unsigned int                       reserved1[12];
    volatile U_ISP_MFBC_Y_HEAD_BUF_BASE0        ISP_MFBC_Y_HEAD_BUF_BASE0;
    volatile U_ISP_MFBC_Y_HEAD_BUF_BASE1        ISP_MFBC_Y_HEAD_BUF_BASE1;
    volatile U_ISP_MFBC_Y_HEAD_LINE_STRIDE      ISP_MFBC_Y_HEAD_LINE_STRIDE;
    volatile U_ISP_MFBC_Y_HEAD_WR_BLEN          ISP_MFBC_Y_HEAD_WR_BLEN;
    volatile unsigned int                       reserved2[12];
    volatile U_ISP_MFBC_UV_DATA_BUF_BASE0       ISP_MFBC_UV_DATA_BUF_BASE0;
    volatile U_ISP_MFBC_UV_DATA_BUF_BASE1       ISP_MFBC_UV_DATA_BUF_BASE1;
    volatile U_ISP_MFBC_UV_DATA_LINE_STRIDE     ISP_MFBC_UV_DATA_LINE_STRIDE;
    volatile U_ISP_MFBC_UV_DATA_WR_BLEN         ISP_MFBC_UV_DATA_WR_BLEN;
    volatile unsigned int                       reserved3[12];
    volatile U_ISP_MFBC_UV_HEAD_BUF_BASE0       ISP_MFBC_UV_HEAD_BUF_BASE0;
    volatile U_ISP_MFBC_UV_HEAD_BUF_BASE1       ISP_MFBC_UV_HEAD_BUF_BASE1;
    volatile U_ISP_MFBC_UV_HEAD_LINE_STRIDE     ISP_MFBC_UV_HEAD_LINE_STRIDE;
    volatile U_ISP_MFBC_UV_HEAD_WR_BLEN         ISP_MFBC_UV_HEAD_WR_BLEN;
    volatile unsigned int                       reserved4[12];
    volatile U_ISP_MFBC_YL_DATA_BUF_BASE0       ISP_MFBC_YL_DATA_BUF_BASE0;
    volatile U_ISP_MFBC_YL_DATA_BUF_BASE1       ISP_MFBC_YL_DATA_BUF_BASE1;
    volatile U_ISP_MFBC_YL_DATA_LINE_STRIDE     ISP_MFBC_YL_DATA_LINE_STRIDE;
    volatile U_ISP_MFBC_YL_DATA_WR_BLEN         ISP_MFBC_YL_DATA_WR_BLEN;
    volatile unsigned int                       reserved5[12];
    volatile U_ISP_MFBC_YL_HEAD_BUF_BASE0       ISP_MFBC_YL_HEAD_BUF_BASE0;
    volatile U_ISP_MFBC_YL_HEAD_BUF_BASE1       ISP_MFBC_YL_HEAD_BUF_BASE1;
    volatile U_ISP_MFBC_YL_HEAD_LINE_STRIDE     ISP_MFBC_YL_HEAD_LINE_STRIDE;
    volatile U_ISP_MFBC_YL_HEAD_WR_BLEN         ISP_MFBC_YL_HEAD_WR_BLEN;
    volatile unsigned int                       reserved6[12];
} S_ISP_MFBC_REGS_TYPE;

/*driver function*/
int ISP_MFBC_DRV_SET_MfbcInputSize(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcInputSize(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcOutFormat(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcOutFormat(S_ISP_MFBC_REGS_TYPE *pstRegs);
//Y data
int ISP_MFBC_DRV_SET_MfbcYDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs);
//Y header
int ISP_MFBC_DRV_SET_MfbcYHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs);
//UV data
int ISP_MFBC_DRV_SET_MfbcUvDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcUvDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcUvDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcUvDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs);
//UV header
int ISP_MFBC_DRV_SET_MfbcUvHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcUvHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcUvHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcUvHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcUvHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs);
//YL data
int ISP_MFBC_DRV_SET_MfbcYlDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlDataBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYlDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlDataBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYlDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlDataLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYlDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlDataWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs);
//YL header
int ISP_MFBC_DRV_SET_MfbcYlHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlHeadBufBase0(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYlHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlHeadBufBase1(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYlHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlHeadLineStride(S_ISP_MFBC_REGS_TYPE *pstRegs);
int ISP_MFBC_DRV_SET_MfbcYlHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_MFBC_DRV_GET_MfbcYlHeadWrBlen(S_ISP_MFBC_REGS_TYPE *pstRegs);
//debug
int ISP_MFBC_DRV_GET_MfbcRegsVal(S_ISP_MFBC_REGS_TYPE *pstRegs);
#endif /*_ISP_MFBC_REG_DEF_H_*/

