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
 * isp_ds_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifndef _ISP_DS_REG_H_
#define _ISP_DS_REG_H_
/*
* DS Control 
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    input_frame_height             : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    input_frame_width              : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_INPUT_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff00            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF00;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff01            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF01;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff02            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF02;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff03            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF03;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff10            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF10;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff11            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF11;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff12            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF12;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff13            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF13;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff20            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF20;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff21            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF21;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff22            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF22;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_rgb2yuv_coeff23            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_RGB2YUV_COEFF23;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff           : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff00            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF00;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff01            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF01;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff02            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF02;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff03            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF03;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff10            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF10;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff11            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF11;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff12            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF12;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff13            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF13;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff20            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF20;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff21            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF21;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff22            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF22;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    osd_yuv2rgb_coeff23            : 12  ; /* [11..0 ]  */
        unsigned int    reserved0                      : 20  ; /* [31..12]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS_OSD_YUV2RGB_COEFF23;
/*Output Channel0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_vscale_dstep               : 16  ; /* [15..0 ]  */
        unsigned int    ds0_vscale_pstep               : 8   ; /* [23..16]  */
        unsigned int    ds0_vscale_filter_en           : 1   ; /* [24]      */
        unsigned int    reserved0                      : 3   ; /* [27..25]  */
        unsigned int    ds0_scale_en                   : 1   ; /* [28]      */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_VSCALE_PARM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_hscale_dstep               : 16  ; /* [15..0 ]  */
        unsigned int    ds0_hscale_pstep               : 8   ; /* [23..16]  */
        unsigned int    ds0_hscale_filter_en           : 1   ; /* [24]      */
        unsigned int    reserved0                      : 7   ; /* [31..25]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_HSCALE_PARM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_frm_output_height          : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    ds0_frm_output_width           : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_out_rgb_mode               : 3   ; /* [2 ..0 ]  */
        unsigned int    reserved0                      : 1   ; /* [3 ]      */
        unsigned int    ds0_out_rgb_en                 : 1   ; /* [4 ]      */
        unsigned int    reserved1                      : 3   ; /* [7 ..5 ]  */
        unsigned int    ds0_out_yuv_mode               : 1   ; /* [8 ]      */
        unsigned int    reserved2                      : 3   ; /* [11..9 ]  */
        unsigned int    ds0_out_uv_swap                : 1   ; /* [12]      */
        unsigned int    reserved3                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_FORMAT;
/*
*Output Channel0 OSD0
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds0_osd0_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds0_osd0_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_width               : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd0_height                : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds0_osd0_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds0_osd0_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds0_osd0_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds0_osd0_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds0_osd0_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds0_osd0_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */        
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd0_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd0_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd0_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd0_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD0_Y_RANGE;
/*
*Output Channel0 OSD1
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds0_osd1_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds0_osd1_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_width               : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd1_height                : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds0_osd1_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds0_osd1_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds0_osd1_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds0_osd1_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds0_osd1_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds0_osd1_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */ 
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd1_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd1_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd1_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd1_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD1_Y_RANGE;
/*
*Output Channel0 OSD2
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds0_osd2_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds0_osd2_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_width               : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd2_height                : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds0_osd2_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds0_osd2_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds0_osd2_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds0_osd2_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds0_osd2_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds0_osd2_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */  

    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd2_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd2_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds0_osd2_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds0_osd2_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS0_OSD2_Y_RANGE;
/*
* Output Channel1
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_vscale_dstep               : 16  ; /* [15..0 ]  */
        unsigned int    ds1_vscale_pstep               : 8   ; /* [23..16]  */
        unsigned int    ds1_vscale_filter_en           : 1   ; /* [24]      */
        unsigned int    reserved0                      : 3   ; /* [27..25]  */
        unsigned int    ds1_scale_en                   : 1   ; /* [28]      */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_VSCALE_PARM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_hscale_dstep               : 16  ; /* [15..0 ]  */
        unsigned int    ds1_hscale_pstep               : 8   ; /* [23..16]  */
        unsigned int    ds1_hscale_filter_en           : 1   ; /* [24]      */
        unsigned int    reserved0                      : 7   ; /* [31..25]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_HSCALE_PARM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_frm_output_height          : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    ds1_frm_output_width           : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_out_rgb_mode               : 3   ; /* [2 ..0 ]  */
        unsigned int    reserved0                      : 1   ; /* [3 ]      */
        unsigned int    ds1_out_rgb_en                 : 1   ; /* [4 ]      */
        unsigned int    reserved1                      : 3   ; /* [7 ..5 ]  */
        unsigned int    ds1_out_yuv_mode               : 1   ; /* [8 ]      */
        unsigned int    reserved2                      : 3   ; /* [11..9 ]  */
        unsigned int    ds1_out_uv_swap                : 1   ; /* [12]      */
        unsigned int    reserved3                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_FORMAT;
/*
*Output Channel1 OSD0
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds1_osd0_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds1_osd0_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_width                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd0_height                 : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds1_osd0_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds1_osd0_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds1_osd0_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds1_osd0_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds1_osd0_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds1_osd0_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */  

    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd0_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd0_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd0_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd0_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD0_Y_RANGE;
/*
*Output Channel1 OSD1
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds1_osd1_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds1_osd1_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_width                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd1_height                 : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds1_osd1_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds1_osd1_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds1_osd1_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds1_osd1_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds1_osd1_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds1_osd1_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */ 
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_osd_stride            : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd1_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd1_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd1_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd1_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD1_Y_RANGE;
/*
*Output Channel1 OSD2
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds1_osd2_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds1_osd2_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_width                 : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd2_height                : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds1_osd2_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds1_osd2_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds1_osd2_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds1_osd2_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds1_osd2_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds1_osd2_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */ 

    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd2_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd2_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds1_osd2_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds1_osd2_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS1_OSD2_Y_RANGE;
/*
*Output Channel2
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_vscale_dstep               : 16  ; /* [15..0 ]  */
        unsigned int    ds2_vscale_pstep               : 8   ; /* [23..16]  */
        unsigned int    ds2_vscale_filter_en           : 1   ; /* [24]      */
        unsigned int    reserved0                      : 3   ; /* [27..25]  */
        unsigned int    ds2_scale_en                   : 1   ; /* [28]      */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_VSCALE_PARM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_hscale_dstep               : 16  ; /* [15..0 ]  */
        unsigned int    ds2_hscale_pstep               : 8   ; /* [23..16]  */
        unsigned int    ds2_hscale_filter_en           : 1   ; /* [24]      */
        unsigned int    reserved0                      : 7   ; /* [31..25]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_HSCALE_PARM;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_frm_output_height          : 13  ; /* [12..0 ]  */
        unsigned int    reserved0                      : 3   ; /* [15..13]  */
        unsigned int    ds2_frm_output_width           : 13  ; /* [28..16]  */
        unsigned int    reserved1                      : 3   ; /* [31..29]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_SIZE;
/*
*Output Channel2 OSD0
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_out_rgb_mode               : 3   ; /* [2 ..0 ]  */
        unsigned int    reserved0                      : 1   ; /* [3 ]      */
        unsigned int    ds2_out_rgb_en                 : 1   ; /* [4 ]      */
        unsigned int    reserved1                      : 3   ; /* [7 ..5 ]  */
        unsigned int    ds2_out_yuv_mode               : 1   ; /* [8 ]      */
        unsigned int    reserved2                      : 3   ; /* [11..9 ]  */
        unsigned int    ds2_out_uv_swap                : 1   ; /* [12]      */
        unsigned int    reserved3                      : 19  ; /* [31..13]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_FORMAT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds2_osd0_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds2_osd0_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_width                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd0_height                 : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds2_osd0_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds2_osd0_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds2_osd0_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds2_osd0_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds2_osd0_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds2_osd0_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */ 
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd0_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd0_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd0_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd0_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD0_Y_RANGE;
/*
*Output Channel2 OSD1
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds2_osd1_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds2_osd1_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_width                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd1_height                 : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds2_osd1_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds2_osd1_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds2_osd1_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds2_osd1_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds2_osd1_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds2_osd1_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */ 
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_osd_stride            : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd1_osd_alpha_stride      : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd1_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd1_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd1_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD1_Y_RANGE;
/*
*Output Channel2 OSD2
*/
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_type                  : 4   ; /* [3 ..0 ]  */
        unsigned int    ds2_osd2_alpha_tpye            : 3   ; /* [6 ..4 ]  */
        unsigned int    reserved0                      : 9   ; /* [15..7 ]  */
        unsigned int    ds2_osd2_enable                : 1   ; /* [16 ]     */
        unsigned int    reserved1                      : 15  ; /* [31..17 ] */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_INFO;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_width                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd2_height                 : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_SIZE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_rgb_addr0             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_alpha_addr0           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_ALPHA_BUF_ADDR0;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_rgb_addr1             : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_alpha_addr1           : 32  ; /* [31..0 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_ALPHA_BUF_ADDR1;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_dma_request_length    : 4   ; /* [3 ..0 ]  */
        unsigned int    ds2_osd2_dma_map               : 2   ; /* [5 ..4 ]  */
        unsigned int    ds2_osd2_rgb_rev               : 1   ; /* [6 ]      */
        unsigned int    reserved0                      : 1   ; /* [7]       */
        unsigned int    ds2_osd2_global_alpha          : 8   ; /* [15 ..8 ] */
        unsigned int    ds2_osd2_swap_64               : 1   ; /* [16]      */
        unsigned int    reserved1                      : 3   ; /* [19..17 ] */
        unsigned int    ds2_osd2_outstanding_num       : 5   ; /* [24..20 ] */
        unsigned int    reserved2                      : 3   ; /* [27..25 ] */
        unsigned int    ds2_osd2_bd_limit_en           : 1   ; /* [28]      */
        unsigned int    reserved3                      : 3   ; /* [31..29 ] */ 
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_DMA_CTL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_stride                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd2_alpha_stride          : 16  ; /* [31..16]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_STRIDE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_stop_x                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd2_start_x               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_X_RANGE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ds2_osd2_stop_y                : 16  ; /* [15..0 ]  */
        unsigned int    ds2_osd2_start_y               : 16  ; /* [31..16 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_ISP_DS2_OSD2_Y_RANGE;

//
#define  ISP_DS_INPUT_SIZE     			(0x0000)
//RGB2YUV
#define  ISP_DS_OSD_RGB2YUV_COEFF00     (0x0004)
#define  ISP_DS_OSD_RGB2YUV_COEFF01     (0x0008)
#define  ISP_DS_OSD_RGB2YUV_COEFF02     (0x000C)
#define  ISP_DS_OSD_RGB2YUV_COEFF03     (0x0010)
#define  ISP_DS_OSD_RGB2YUV_COEFF10     (0x0014)
#define  ISP_DS_OSD_RGB2YUV_COEFF11     (0x0018)
#define  ISP_DS_OSD_RGB2YUV_COEFF12     (0x001C)
#define  ISP_DS_OSD_RGB2YUV_COEFF13     (0x0020)
#define  ISP_DS_OSD_RGB2YUV_COEFF20     (0x0024)
#define  ISP_DS_OSD_RGB2YUV_COEFF21     (0x0028)
#define  ISP_DS_OSD_RGB2YUV_COEFF22     (0x002C)
#define  ISP_DS_OSD_RGB2YUV_COEFF23     (0x0030)
//YUV2RGB
#define  ISP_DS_OSD_YUV2RGB_COEFF00     (0x0040)
#define  ISP_DS_OSD_YUV2RGB_COEFF01     (0x0044)
#define  ISP_DS_OSD_YUV2RGB_COEFF02     (0x0048)
#define  ISP_DS_OSD_YUV2RGB_COEFF03     (0x004C)
#define  ISP_DS_OSD_YUV2RGB_COEFF10     (0x0050)
#define  ISP_DS_OSD_YUV2RGB_COEFF11     (0x0054)
#define  ISP_DS_OSD_YUV2RGB_COEFF12     (0x0058)
#define  ISP_DS_OSD_YUV2RGB_COEFF13     (0x005C)
#define  ISP_DS_OSD_YUV2RGB_COEFF20     (0x0060)
#define  ISP_DS_OSD_YUV2RGB_COEFF21     (0x0064)
#define  ISP_DS_OSD_YUV2RGB_COEFF22     (0x0068)
#define  ISP_DS_OSD_YUV2RGB_COEFF23     (0x006C)
//DS0
#define  ISP_DS0_VSCALE_PARM     		(0x0080)
#define  ISP_DS0_HSCALE_PARM     		(0x0084)
#define  ISP_DS0_SIZE     				(0x0088)
#define  ISP_DS0_FORMAT     			(0x008C)
//DS0 OSD0
#define  ISP_DS0_OSD0_INFO     			(0x00C0)
#define  ISP_DS0_OSD0_SIZE     			(0x00C4)
#define  ISP_DS0_OSD0_BUF_ADDR0     	(0x00C8)
#define  ISP_DS0_OSD0_ALPHA_BUF_ADDR0   (0x00CC)
#define  ISP_DS0_OSD0_BUF_ADDR1     	(0x00D0)
#define  ISP_DS0_OSD0_ALPHA_BUF_ADDR1   (0x00D4)
#define  ISP_DS0_OSD0_DMA_CTL     		(0x00D8)
#define  ISP_DS0_OSD0_STRIDE     		(0x00DC)
#define  ISP_DS0_OSD0_X_RANGE     		(0x00E0)
#define  ISP_DS0_OSD0_Y_RANGE     		(0x00E4)
//DS0 OSD1
#define  ISP_DS0_OSD1_INFO     			(0x0100)
#define  ISP_DS0_OSD1_SIZE     			(0x0104)
#define  ISP_DS0_OSD1_BUF_ADDR0     	(0x0108)
#define  ISP_DS0_OSD1_ALPHA_BUF_ADDR0   (0x010C)
#define  ISP_DS0_OSD1_BUF_ADDR1     	(0x0110)
#define  ISP_DS0_OSD1_ALPHA_BUF_ADDR1   (0x0114)
#define  ISP_DS0_OSD1_DMA_CTL     		(0x0118)
#define  ISP_DS0_OSD1_STRIDE     		(0x011C)
#define  ISP_DS0_OSD1_X_RANGE    		(0x0120)
#define  ISP_DS0_OSD1_Y_RANGE    		(0x0124)
//DS0 OSD2
#define  ISP_DS0_OSD2_INFO     			(0x0140)
#define  ISP_DS0_OSD2_SIZE     			(0x0144)
#define  ISP_DS0_OSD2_BUF_ADDR0     	(0x0148)
#define  ISP_DS0_OSD2_ALPHA_BUF_ADDR0   (0x014C)
#define  ISP_DS0_OSD2_BUF_ADDR1     	(0x0150)
#define  ISP_DS0_OSD2_ALPHA_BUF_ADDR1   (0x0154)
#define  ISP_DS0_OSD2_DMA_CTL     		(0x0158)
#define  ISP_DS0_OSD2_STRIDE     		(0x015C)
#define  ISP_DS0_OSD2_X_RANGE     		(0x0160)
#define  ISP_DS0_OSD2_Y_RANGE     		(0x0164)
//DS1
#define  ISP_DS1_VSCALE_PARM     		(0x0180)
#define  ISP_DS1_HSCALE_PARM     		(0x0184)
#define  ISP_DS1_SIZE     				(0x0188)
#define  ISP_DS1_FORMAT     			(0x018C)
//DS1 0SD0
#define  ISP_DS1_OSD0_INFO     			(0x01C0)
#define  ISP_DS1_OSD0_SIZE     			(0x01C4)
#define  ISP_DS1_OSD0_BUF_ADDR0     	(0x01C8)
#define  ISP_DS1_OSD0_ALPHA_BUF_ADDR0   (0x01CC)
#define  ISP_DS1_OSD0_BUF_ADDR1     	(0x01D0)
#define  ISP_DS1_OSD0_ALPHA_BUF_ADDR1   (0x01D4)
#define  ISP_DS1_OSD0_DMA_CTL     		(0x01D8)
#define  ISP_DS1_OSD0_STRIDE     		(0x01DC)
#define  ISP_DS1_OSD0_X_RANGE     		(0x01E0)
#define  ISP_DS1_OSD0_Y_RANGE     		(0x01E4)
//DS1 0SD1
#define  ISP_DS1_OSD1_INFO     			(0x0200)
#define  ISP_DS1_OSD1_SIZE     			(0x0204)
#define  ISP_DS1_OSD1_BUF_ADDR0     	(0x0208)
#define  ISP_DS1_OSD1_ALPHA_BUF_ADDR0   (0x020C)
#define  ISP_DS1_OSD1_BUF_ADDR1     	(0x0210)
#define  ISP_DS1_OSD1_ALPHA_BUF_ADDR1   (0x0214)
#define  ISP_DS1_OSD1_DMA_CTL     		(0x0218)
#define  ISP_DS1_OSD1_STRIDE     		(0x021C)
#define  ISP_DS1_OSD1_X_RANGE     		(0x0220)
#define  ISP_DS1_OSD1_Y_RANGE     		(0x0224)
//DS1 0SD2
#define  ISP_DS1_OSD2_INFO     			(0x0240)
#define  ISP_DS1_OSD2_SIZE     			(0x0244)
#define  ISP_DS1_OSD2_BUF_ADDR0     	(0x0248)
#define  ISP_DS1_OSD2_ALPHA_BUF_ADDR0   (0x024C)
#define  ISP_DS1_OSD2_BUF_ADDR1     	(0x0250)
#define  ISP_DS1_OSD2_ALPHA_BUF_ADDR1   (0x0254)
#define  ISP_DS1_OSD2_DMA_CTL     		(0x0258)
#define  ISP_DS1_OSD2_STRIDE     		(0x025C)
#define  ISP_DS1_OSD2_X_RANGE     		(0x0260)
#define  ISP_DS1_OSD2_Y_RANGE     		(0x0264)
//DS2
#define  ISP_DS2_VSCALE_PARM     		(0x0280)
#define  ISP_DS2_HSCALE_PARM     		(0x0284)
#define  ISP_DS2_SIZE     				(0x0288)
#define  ISP_DS2_FORMAT     			(0x028C)
//DS2 OSD0
#define  ISP_DS2_OSD0_INFO    			(0x02C0)
#define  ISP_DS2_OSD0_SIZE    			(0x02C4)
#define  ISP_DS2_OSD0_BUF_ADDR0     	(0x02C8)
#define  ISP_DS2_OSD0_ALPHA_BUF_ADDR0   (0x02CC)
#define  ISP_DS2_OSD0_BUF_ADDR1     	(0x02D0)
#define  ISP_DS2_OSD0_ALPHA_BUF_ADDR1   (0x02D4)
#define  ISP_DS2_OSD0_DMA_CTL     		(0x02D8)
#define  ISP_DS2_OSD0_STRIDE     		(0x02DC)
#define  ISP_DS2_OSD0_X_RANGE     		(0x02E0)
#define  ISP_DS2_OSD0_Y_RANGE     		(0x02E4)
//DS2 OSD1
#define  ISP_DS2_OSD1_INFO    			(0x0300)
#define  ISP_DS2_OSD1_SIZE    			(0x0304)
#define  ISP_DS2_OSD1_BUF_ADDR0     	(0x0308)
#define  ISP_DS2_OSD1_ALPHA_BUF_ADDR0   (0x030C)
#define  ISP_DS2_OSD1_BUF_ADDR1     	(0x0310)
#define  ISP_DS2_OSD1_ALPHA_BUF_ADDR1   (0x0314)
#define  ISP_DS2_OSD1_DMA_CTL     		(0x0318)
#define  ISP_DS2_OSD1_STRIDE     		(0x031C)
#define  ISP_DS2_OSD1_X_RANGE     		(0x0320)
#define  ISP_DS2_OSD1_Y_RANGE     		(0x0324)
//DS2 OSD2
#define  ISP_DS2_OSD2_INFO     			(0x0340)
#define  ISP_DS2_OSD2_SIZE     			(0x0344)
#define  ISP_DS2_OSD2_BUF_ADDR0     	(0x0348)
#define  ISP_DS2_OSD2_ALPHA_BUF_ADDR0   (0x034C)
#define  ISP_DS2_OSD2_BUF_ADDR1     	(0x0350)
#define  ISP_DS2_OSD2_ALPHA_BUF_ADDR1   (0x0354)
#define  ISP_DS2_OSD2_DMA_CTL     		(0x0358)
#define  ISP_DS2_OSD2_STRIDE     		(0x035C)
#define  ISP_DS2_OSD2_X_RANGE     		(0x0360)
#define  ISP_DS2_OSD2_Y_RANGE     		(0x0364)
//DS TABLE
#define  ISP_HSCALE_COFF_0_BASE         (0x0500)  //256
#define  ISP_HSCALE_COFF_1_BASE         (0x0900) //256
#define  ISP_HSCALE_COFF_2_BASE         (0x0D00) //256
#define  ISP_VSCALE_COFF_BASE           (0x1100) //128

#endif  /*_ISP_DS_REG_H_*/
