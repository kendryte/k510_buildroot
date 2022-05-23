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
#ifndef _ISP_DS_REG_DEF_H_
#define _ISP_DS_REG_DEF_H_
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

typedef struct
{
    volatile U_ISP_DS_INPUT_SIZE                ISP_DS_INPUT_SIZE;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF00       ISP_DS_OSD_RGB2YUV_COEFF00;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF01       ISP_DS_OSD_RGB2YUV_COEFF01;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF02       ISP_DS_OSD_RGB2YUV_COEFF02;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF03       ISP_DS_OSD_RGB2YUV_COEFF03;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF10       ISP_DS_OSD_RGB2YUV_COEFF10;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF11       ISP_DS_OSD_RGB2YUV_COEFF11;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF12       ISP_DS_OSD_RGB2YUV_COEFF12;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF13       ISP_DS_OSD_RGB2YUV_COEFF13;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF20       ISP_DS_OSD_RGB2YUV_COEFF20;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF21       ISP_DS_OSD_RGB2YUV_COEFF21;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF22       ISP_DS_OSD_RGB2YUV_COEFF22;
    volatile U_ISP_DS_OSD_RGB2YUV_COEFF23       ISP_DS_OSD_RGB2YUV_COEFF23;
    volatile unsigned int                       reserved0[3];
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF00       ISP_DS_OSD_YUV2RGB_COEFF00;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF01       ISP_DS_OSD_YUV2RGB_COEFF01;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF02       ISP_DS_OSD_YUV2RGB_COEFF02;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF03       ISP_DS_OSD_YUV2RGB_COEFF03;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF10       ISP_DS_OSD_YUV2RGB_COEFF10;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF11       ISP_DS_OSD_YUV2RGB_COEFF11;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF12       ISP_DS_OSD_YUV2RGB_COEFF12;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF13       ISP_DS_OSD_YUV2RGB_COEFF13;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF20       ISP_DS_OSD_YUV2RGB_COEFF20;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF21       ISP_DS_OSD_YUV2RGB_COEFF21;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF22       ISP_DS_OSD_YUV2RGB_COEFF22;
    volatile U_ISP_DS_OSD_YUV2RGB_COEFF23       ISP_DS_OSD_YUV2RGB_COEFF23;
    volatile unsigned int                       reserved1[4];
    volatile U_ISP_DS0_VSCALE_PARM              ISP_DS0_VSCALE_PARM;
    volatile U_ISP_DS0_HSCALE_PARM              ISP_DS0_HSCALE_PARM;
    volatile U_ISP_DS0_SIZE                     ISP_DS0_SIZE;
    volatile U_ISP_DS0_FORMAT                   ISP_DS0_FORMAT;
    volatile unsigned int                       reserved2[12];
    volatile U_ISP_DS0_OSD0_INFO                ISP_DS0_OSD0_INFO;
    volatile U_ISP_DS0_OSD0_SIZE                ISP_DS0_OSD0_SIZE;
    volatile U_ISP_DS0_OSD0_BUF_ADDR0           ISP_DS0_OSD0_BUF_ADDR0;
    volatile U_ISP_DS0_OSD0_ALPHA_BUF_ADDR0     ISP_DS0_OSD0_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS0_OSD0_BUF_ADDR1           ISP_DS0_OSD0_BUF_ADDR1;
    volatile U_ISP_DS0_OSD0_ALPHA_BUF_ADDR1     ISP_DS0_OSD0_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS0_OSD0_DMA_CTL             ISP_DS0_OSD0_DMA_CTL;
    volatile U_ISP_DS0_OSD0_STRIDE              ISP_DS0_OSD0_STRIDE;
    volatile U_ISP_DS0_OSD0_X_RANGE             ISP_DS0_OSD0_X_RANGE;
    volatile U_ISP_DS0_OSD0_Y_RANGE             ISP_DS0_OSD0_Y_RANGE;
    volatile unsigned int                       reserved3[6];
    volatile U_ISP_DS0_OSD1_INFO                ISP_DS0_OSD1_INFO;
    volatile U_ISP_DS0_OSD1_SIZE                ISP_DS0_OSD1_SIZE;
    volatile U_ISP_DS0_OSD1_BUF_ADDR0           ISP_DS0_OSD1_BUF_ADDR0;
    volatile U_ISP_DS0_OSD1_ALPHA_BUF_ADDR0     ISP_DS0_OSD1_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS0_OSD1_BUF_ADDR1           ISP_DS0_OSD1_BUF_ADDR1;
    volatile U_ISP_DS0_OSD1_ALPHA_BUF_ADDR1     ISP_DS0_OSD1_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS0_OSD1_DMA_CTL             ISP_DS0_OSD1_DMA_CTL;
    volatile U_ISP_DS0_OSD1_STRIDE              ISP_DS0_OSD1_STRIDE;
    volatile U_ISP_DS0_OSD1_X_RANGE             ISP_DS0_OSD1_X_RANGE;
    volatile U_ISP_DS0_OSD1_Y_RANGE             ISP_DS0_OSD1_Y_RANGE;
    volatile unsigned int                       reserved4[6];
    volatile U_ISP_DS0_OSD2_INFO                ISP_DS0_OSD2_INFO;
    volatile U_ISP_DS0_OSD2_SIZE                ISP_DS0_OSD2_SIZE;
    volatile U_ISP_DS0_OSD2_BUF_ADDR0           ISP_DS0_OSD2_BUF_ADDR0;
    volatile U_ISP_DS0_OSD2_ALPHA_BUF_ADDR0     ISP_DS0_OSD2_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS0_OSD2_BUF_ADDR1           ISP_DS0_OSD2_BUF_ADDR1;
    volatile U_ISP_DS0_OSD2_ALPHA_BUF_ADDR1     ISP_DS0_OSD2_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS0_OSD2_DMA_CTL             ISP_DS0_OSD2_DMA_CTL;
    volatile U_ISP_DS0_OSD2_STRIDE              ISP_DS0_OSD2_STRIDE;
    volatile U_ISP_DS0_OSD2_X_RANGE             ISP_DS0_OSD2_X_RANGE;
    volatile U_ISP_DS0_OSD2_Y_RANGE             ISP_DS0_OSD2_Y_RANGE;
    volatile unsigned int                       reserved5[6];
    volatile U_ISP_DS1_VSCALE_PARM              ISP_DS1_VSCALE_PARM;
    volatile U_ISP_DS1_HSCALE_PARM              ISP_DS1_HSCALE_PARM;
    volatile U_ISP_DS1_SIZE                     ISP_DS1_SIZE;
    volatile U_ISP_DS1_FORMAT                   ISP_DS1_FORMAT;
    volatile unsigned int                       reserved6[12];
    volatile U_ISP_DS1_OSD0_INFO                ISP_DS1_OSD0_INFO;
    volatile U_ISP_DS1_OSD0_SIZE                ISP_DS1_OSD0_SIZE;
    volatile U_ISP_DS1_OSD0_BUF_ADDR0           ISP_DS1_OSD0_BUF_ADDR0;
    volatile U_ISP_DS1_OSD0_ALPHA_BUF_ADDR0     ISP_DS1_OSD0_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS1_OSD0_BUF_ADDR1           ISP_DS1_OSD0_BUF_ADDR1;
    volatile U_ISP_DS1_OSD0_ALPHA_BUF_ADDR1     ISP_DS1_OSD0_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS1_OSD0_DMA_CTL             ISP_DS1_OSD0_DMA_CTL;
    volatile U_ISP_DS1_OSD0_STRIDE              ISP_DS1_OSD0_STRIDE;
    volatile U_ISP_DS1_OSD0_X_RANGE             ISP_DS1_OSD0_X_RANGE;
    volatile U_ISP_DS1_OSD0_Y_RANGE             ISP_DS1_OSD0_Y_RANGE;
    volatile unsigned int                       reserved7[6];
    volatile U_ISP_DS1_OSD1_INFO                ISP_DS1_OSD1_INFO;
    volatile U_ISP_DS1_OSD1_SIZE                ISP_DS1_OSD1_SIZE;
    volatile U_ISP_DS1_OSD1_BUF_ADDR0           ISP_DS1_OSD1_BUF_ADDR0;
    volatile U_ISP_DS1_OSD1_ALPHA_BUF_ADDR0     ISP_DS1_OSD1_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS1_OSD1_BUF_ADDR1           ISP_DS1_OSD1_BUF_ADDR1;
    volatile U_ISP_DS1_OSD1_ALPHA_BUF_ADDR1     ISP_DS1_OSD1_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS1_OSD1_DMA_CTL             ISP_DS1_OSD1_DMA_CTL;
    volatile U_ISP_DS1_OSD1_STRIDE              ISP_DS1_OSD1_STRIDE;
    volatile U_ISP_DS1_OSD1_X_RANGE             ISP_DS1_OSD1_X_RANGE;
    volatile U_ISP_DS1_OSD1_Y_RANGE             ISP_DS1_OSD1_Y_RANGE;
    volatile unsigned int                       reserved8[6];
    volatile U_ISP_DS1_OSD2_INFO                ISP_DS1_OSD2_INFO;
    volatile U_ISP_DS1_OSD2_SIZE                ISP_DS1_OSD2_SIZE;
    volatile U_ISP_DS1_OSD2_BUF_ADDR0           ISP_DS1_OSD2_BUF_ADDR0;
    volatile U_ISP_DS1_OSD2_ALPHA_BUF_ADDR0     ISP_DS1_OSD2_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS1_OSD2_BUF_ADDR1           ISP_DS1_OSD2_BUF_ADDR1;
    volatile U_ISP_DS1_OSD2_ALPHA_BUF_ADDR1     ISP_DS1_OSD2_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS1_OSD2_DMA_CTL             ISP_DS1_OSD2_DMA_CTL;
    volatile U_ISP_DS1_OSD2_STRIDE              ISP_DS1_OSD2_STRIDE;
    volatile U_ISP_DS1_OSD2_X_RANGE             ISP_DS1_OSD2_X_RANGE;
    volatile U_ISP_DS1_OSD2_Y_RANGE             ISP_DS1_OSD2_Y_RANGE;
    volatile unsigned int                       reserved9[6];
    volatile U_ISP_DS2_VSCALE_PARM              ISP_DS2_VSCALE_PARM;
    volatile U_ISP_DS2_HSCALE_PARM              ISP_DS2_HSCALE_PARM;
    volatile U_ISP_DS2_SIZE                     ISP_DS2_SIZE;
    volatile U_ISP_DS2_FORMAT                   ISP_DS2_FORMAT;
    volatile unsigned int                       reserved10[12];
    volatile U_ISP_DS2_OSD0_INFO                ISP_DS2_OSD0_INFO;
    volatile U_ISP_DS2_OSD0_SIZE                ISP_DS2_OSD0_SIZE;
    volatile U_ISP_DS2_OSD0_BUF_ADDR0           ISP_DS2_OSD0_BUF_ADDR0;
    volatile U_ISP_DS2_OSD0_ALPHA_BUF_ADDR0     ISP_DS2_OSD0_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS2_OSD0_BUF_ADDR1           ISP_DS2_OSD0_BUF_ADDR1;
    volatile U_ISP_DS2_OSD0_ALPHA_BUF_ADDR1     ISP_DS2_OSD0_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS2_OSD0_DMA_CTL             ISP_DS2_OSD0_DMA_CTL;
    volatile U_ISP_DS2_OSD0_STRIDE              ISP_DS2_OSD0_STRIDE;
    volatile U_ISP_DS2_OSD0_X_RANGE             ISP_DS2_OSD0_X_RANGE;
    volatile U_ISP_DS2_OSD0_Y_RANGE             ISP_DS2_OSD0_Y_RANGE;
    volatile unsigned int                       reserved11[6];
    volatile U_ISP_DS2_OSD1_INFO                ISP_DS2_OSD1_INFO;
    volatile U_ISP_DS2_OSD1_SIZE                ISP_DS2_OSD1_SIZE;
    volatile U_ISP_DS2_OSD1_BUF_ADDR0           ISP_DS2_OSD1_BUF_ADDR0;
    volatile U_ISP_DS2_OSD1_ALPHA_BUF_ADDR0     ISP_DS2_OSD1_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS2_OSD1_BUF_ADDR1           ISP_DS2_OSD1_BUF_ADDR1;
    volatile U_ISP_DS2_OSD1_ALPHA_BUF_ADDR1     ISP_DS2_OSD1_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS2_OSD1_DMA_CTL             ISP_DS2_OSD1_DMA_CTL;
    volatile U_ISP_DS2_OSD1_STRIDE              ISP_DS2_OSD1_STRIDE;
    volatile U_ISP_DS2_OSD1_X_RANGE             ISP_DS2_OSD1_X_RANGE;
    volatile U_ISP_DS2_OSD1_Y_RANGE             ISP_DS2_OSD1_Y_RANGE;
    volatile unsigned int                        reserved12[6];
    volatile U_ISP_DS2_OSD2_INFO                ISP_DS2_OSD2_INFO;
    volatile U_ISP_DS2_OSD2_SIZE                ISP_DS2_OSD2_SIZE;
    volatile U_ISP_DS2_OSD2_BUF_ADDR0           ISP_DS2_OSD2_BUF_ADDR0;
    volatile U_ISP_DS2_OSD2_ALPHA_BUF_ADDR0     ISP_DS2_OSD2_ALPHA_BUF_ADDR0;
    volatile U_ISP_DS2_OSD2_BUF_ADDR1           ISP_DS2_OSD2_BUF_ADDR1;
    volatile U_ISP_DS2_OSD2_ALPHA_BUF_ADDR1     ISP_DS2_OSD2_ALPHA_BUF_ADDR1;
    volatile U_ISP_DS2_OSD2_DMA_CTL             ISP_DS2_OSD2_DMA_CTL;
    volatile U_ISP_DS2_OSD2_STRIDE              ISP_DS2_OSD2_STRIDE;
    volatile U_ISP_DS2_OSD2_X_RANGE             ISP_DS2_OSD2_X_RANGE;
    volatile U_ISP_DS2_OSD2_Y_RANGE             ISP_DS2_OSD2_Y_RANGE;
    volatile unsigned int                       reserved13[102]; //[38]
    volatile unsigned int                       ISP_HSCALE_COFF_0_BASE[256];
    volatile unsigned int                       ISP_HSCALE_COFF_1_BASE[256];
    volatile unsigned int                       ISP_HSCALE_COFF_2_BASE[256];
    volatile unsigned int                       ISP_VSCALE_COFF_BASE[128];
} S_ISP_DS_REGS_TYPE;

int ISP_DS_DRV_SET_DsInputSize(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff00(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff01(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff02(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff03(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff10(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff11(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff12(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff13(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff20(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff21(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff22(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff23(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff00(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff01(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff02(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff03(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff10(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff11(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff12(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff13(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff20(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff21(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff22(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff23(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);

//
int ISP_DS_DRV_SET_Ds0VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Format(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);

int ISP_DS_DRV_SET_Ds0Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds0Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds0Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds0Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds1VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Format(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds1Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds1Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds1Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds1Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds2VscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2HscaleParm(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Format(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds2Osd0Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd0YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds2Osd1Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd1YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//
int ISP_DS_DRV_SET_Ds2Osd2Info(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2Size(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2BufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2AlphaBufAddr0(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2BufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2AlphaBufAddr1(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2DmaCtl(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2Stride(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2XRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
int ISP_DS_DRV_SET_Ds2Osd2YRange(S_ISP_DS_REGS_TYPE *pstRegs, unsigned int uData);
//debug
int ISP_DS_DRV_GET_DsRegsVal(S_ISP_DS_REGS_TYPE *pstRegs);
#endif  /*_ISP_DS_REG_DEF_H_*/
