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

//#include "video/vo/vo.h"
#include "video/isp_com.h"
#include "video/video_subsystem_addr.h"
#include "video/vo/remap/vo_remap_reg.h"
#include "video/vo/remap/vo_remap_drv.h"

unsigned int  *reg_vo_remap_base;
#define VO_DRV_REMAP_REG_CTX(pstCtx)	pstCtx = (S_VO_REMAP_REGS_TYPE *)(reg_vo_remap_base)
/*
*
*/
int VO_DRV_DrawLine_Remap(void )
{
	reg_vo_remap_base          = (unsigned int *)VO_CONFIG_LINE_BASE; //BASE + 0x0600
	return 0;
}
#if 0
/*
*Area00
*/
static int VO_DRV_SetArea00(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea00_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea00_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea00_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area01
*/
static int VO_DRV_SetArea01(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea01_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea01_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea01_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area02
*/
static int VO_DRV_SetArea02(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea02_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea02_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea02_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area03
*/
static int VO_DRV_SetArea03(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea03_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea03_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea03_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area04
*/
static int VO_DRV_SetArea04(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea04_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea04_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea04_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area05
*/
static int VO_DRV_SetArea05(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea05_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea05_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea05_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area06
*/
static int VO_DRV_SetArea06(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea06_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea06_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea06_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area07
*/
static int VO_DRV_SetArea07(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea07_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea07_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea07_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area08
*/
static int VO_DRV_SetArea08(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea08_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea08_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea08_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area09
*/
static int VO_DRV_SetArea09(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea09_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea09_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea09_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area10
*/
static int VO_DRV_SetArea10(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea10_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea10_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea10_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area11
*/
static int VO_DRV_SetArea11(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea11_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea11_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea11_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area12
*/
static int VO_DRV_SetArea12(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea12_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea12_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea12_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area13
*/
static int VO_DRV_SetArea13(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea13_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea13_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea13_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area14
*/
static int VO_DRV_SetArea14(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea14_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea14_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea14_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area15
*/
static int VO_DRV_SetArea15(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea15_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea15_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea15_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area16
*/
static int VO_DRV_SetArea16(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea16_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea16_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea16_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area17
*/
static int VO_DRV_SetArea17(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea17_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea17_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea17_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area18
*/
static int VO_DRV_SetArea18(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea18_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea18_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea18_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area19
*/
static int VO_DRV_SetArea19(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea19_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea19_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea19_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area20
*/
static int VO_DRV_SetArea20(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea20_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea20_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea20_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area21
*/
static int VO_DRV_SetArea21(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea21_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea21_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea21_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area22
*/
static int VO_DRV_SetArea22(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea22_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea22_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea22_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area23
*/
static int VO_DRV_SetArea23(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea23_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea23_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea23_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area24
*/
static int VO_DRV_SetArea24(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea24_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea24_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea24_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area25
*/
static int VO_DRV_SetArea25(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea25_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea25_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea25_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area26
*/
static int VO_DRV_SetArea26(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea26_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea26_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea26_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area27
*/
static int VO_DRV_SetArea27(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea27_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea27_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea27_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area28
*/
static int VO_DRV_SetArea28(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea28_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea28_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea28_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area29
*/
static int VO_DRV_SetArea29(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea29_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea29_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea29_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area30
*/
static int VO_DRV_SetArea30(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea30_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea30_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea30_0(apstVoRemapReg, data_udata.u32);

    return 0;
}
/*
*Area31
*/
static int VO_DRV_SetArea31(VO_REMAP_CTRL_FILL_INFO_S *fillInfo)
{
    VO_CHECK_POINTER(fillInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
    info0_udata.bits.line_draw_en     = fillInfo->line_draw_en;
    info0_udata.bits.v_line_u_en      = fillInfo->v_line_u_en;
    info0_udata.bits.h_line_b_en      = fillInfo->h_line_b_en;
    info0_udata.bits.v_line_l_en      = fillInfo->v_line_l_en;
    info0_udata.bits.v_line_r_en      = fillInfo->v_line_r_en;
    info0_udata.bits.line_start_pos_x = fillInfo->line_start_pos_x;
    info0_udata.bits.line_draw_en     = fillInfo->line_end_pos_x;
		VO_REMAP_DRV_SET_CtrlFillInfoArea31_0(apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
    info1_udata.bits.line_start_pos_y = fillInfo->line_start_pos_y;
    info1_udata.bits.line_end_pos_y   = fillInfo->line_end_pos_y;
    info1_udata.bits.line_width_h     = fillInfo->line_width_h;
    info1_udata.bits.line_width_l     = fillInfo->line_width_l;
		VO_REMAP_DRV_SET_CtrlFillInfoArea31_1(apstVoRemapReg, info1_udata.u32);


    U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
    data_udata.bits.fill_value_y      = fillInfo->fill_value_y;
    data_udata.bits.fill_value_cb     = fillInfo->fill_value_cb;
    data_udata.bits.fill_value_cr     = fillInfo->fill_value_cr;
    data_udata.bits.fill_alpha        = fillInfo->fill_alpha;
		VO_REMAP_DRV_SET_CtrlFillDataArea31_0(apstVoRemapReg, data_udata.u32);

    return 0;
}

/*
*
*/
static REMAP_FUNC remap_func[32] =
{
    VO_DRV_SetArea00,
    VO_DRV_SetArea01,
    VO_DRV_SetArea02,
    VO_DRV_SetArea03,
    VO_DRV_SetArea04,
    VO_DRV_SetArea05,
    VO_DRV_SetArea06,
    VO_DRV_SetArea07,
    VO_DRV_SetArea08,
    VO_DRV_SetArea09,
    VO_DRV_SetArea10,
    VO_DRV_SetArea11,
    VO_DRV_SetArea12,
    VO_DRV_SetArea13,
    VO_DRV_SetArea14,
    VO_DRV_SetArea15,
    VO_DRV_SetArea16,
    VO_DRV_SetArea17,
    VO_DRV_SetArea18,
    VO_DRV_SetArea19,
    VO_DRV_SetArea20,
    VO_DRV_SetArea21,
    VO_DRV_SetArea22,
    VO_DRV_SetArea23,
    VO_DRV_SetArea24,
    VO_DRV_SetArea25,
    VO_DRV_SetArea26,
    VO_DRV_SetArea27,
    VO_DRV_SetArea28,
    VO_DRV_SetArea29,
    VO_DRV_SetArea30,
    VO_DRV_SetArea31,
};

/*
*
*/
int VO_DRV_SetRemap(VO_REMAP_INFO_S *voRemapInfo)
{
    VO_CHECK_POINTER(voRemapInfo);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);
    
    U_VO_REMAP_CTRL_FILL_CMD          cmd_udata;
    cmd_udata.bits.fill_en_rgb        = voRemapInfo->fillCmd.fill_en_rgb;
    cmd_udata.bits.fill_fill_en_yuv   = voRemapInfo->fillCmd.fill_fill_en_yuv;
    cmd_udata.bits.image_active_h     = voRemapInfo->fillCmd.image_active_h;
    cmd_udata.bits.image_active_v     = voRemapInfo->fillCmd.image_active_v;
    VO_REMAP_DRV_SET_CtrlFillCmd(apstVoRemapReg, cmd_udata.u32);

    for(int i = 0;i < 32; i++)
    {
      if( 1 == voRemapInfo->fillInfo[i].line_draw_en)
      {
          remap_func[i](&voRemapInfo->fillInfo[i]);
      }
    }

    return 0;
}
#endif
/*
*
*/
static VO_REMAP_FILL_FUNC remap_fill_func[VO_LINE_DRAW_AREA_MAX][VO_REMAP_FUNC_MAX] =
{
    {VO_REMAP_DRV_SET_CtrlFillInfoArea00_0,VO_REMAP_DRV_SET_CtrlFillInfoArea00_1,VO_REMAP_DRV_SET_CtrlFillDataArea00_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea01_0,VO_REMAP_DRV_SET_CtrlFillInfoArea01_1,VO_REMAP_DRV_SET_CtrlFillDataArea01_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea02_0,VO_REMAP_DRV_SET_CtrlFillInfoArea02_1,VO_REMAP_DRV_SET_CtrlFillDataArea02_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea03_0,VO_REMAP_DRV_SET_CtrlFillInfoArea03_1,VO_REMAP_DRV_SET_CtrlFillDataArea03_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea04_0,VO_REMAP_DRV_SET_CtrlFillInfoArea04_1,VO_REMAP_DRV_SET_CtrlFillDataArea04_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea05_0,VO_REMAP_DRV_SET_CtrlFillInfoArea05_1,VO_REMAP_DRV_SET_CtrlFillDataArea05_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea06_0,VO_REMAP_DRV_SET_CtrlFillInfoArea06_1,VO_REMAP_DRV_SET_CtrlFillDataArea06_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea07_0,VO_REMAP_DRV_SET_CtrlFillInfoArea07_1,VO_REMAP_DRV_SET_CtrlFillDataArea07_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea08_0,VO_REMAP_DRV_SET_CtrlFillInfoArea08_1,VO_REMAP_DRV_SET_CtrlFillDataArea08_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea09_0,VO_REMAP_DRV_SET_CtrlFillInfoArea09_1,VO_REMAP_DRV_SET_CtrlFillDataArea09_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea10_0,VO_REMAP_DRV_SET_CtrlFillInfoArea10_1,VO_REMAP_DRV_SET_CtrlFillDataArea10_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea11_0,VO_REMAP_DRV_SET_CtrlFillInfoArea11_1,VO_REMAP_DRV_SET_CtrlFillDataArea11_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea12_0,VO_REMAP_DRV_SET_CtrlFillInfoArea12_1,VO_REMAP_DRV_SET_CtrlFillDataArea12_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea13_0,VO_REMAP_DRV_SET_CtrlFillInfoArea13_1,VO_REMAP_DRV_SET_CtrlFillDataArea13_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea14_0,VO_REMAP_DRV_SET_CtrlFillInfoArea14_1,VO_REMAP_DRV_SET_CtrlFillDataArea14_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea15_0,VO_REMAP_DRV_SET_CtrlFillInfoArea15_1,VO_REMAP_DRV_SET_CtrlFillDataArea15_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea16_0,VO_REMAP_DRV_SET_CtrlFillInfoArea16_1,VO_REMAP_DRV_SET_CtrlFillDataArea16_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea17_0,VO_REMAP_DRV_SET_CtrlFillInfoArea17_1,VO_REMAP_DRV_SET_CtrlFillDataArea17_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea18_0,VO_REMAP_DRV_SET_CtrlFillInfoArea18_1,VO_REMAP_DRV_SET_CtrlFillDataArea18_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea19_0,VO_REMAP_DRV_SET_CtrlFillInfoArea19_1,VO_REMAP_DRV_SET_CtrlFillDataArea19_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea20_0,VO_REMAP_DRV_SET_CtrlFillInfoArea20_1,VO_REMAP_DRV_SET_CtrlFillDataArea20_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea21_0,VO_REMAP_DRV_SET_CtrlFillInfoArea21_1,VO_REMAP_DRV_SET_CtrlFillDataArea21_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea22_0,VO_REMAP_DRV_SET_CtrlFillInfoArea22_1,VO_REMAP_DRV_SET_CtrlFillDataArea22_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea23_0,VO_REMAP_DRV_SET_CtrlFillInfoArea23_1,VO_REMAP_DRV_SET_CtrlFillDataArea23_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea24_0,VO_REMAP_DRV_SET_CtrlFillInfoArea24_1,VO_REMAP_DRV_SET_CtrlFillDataArea24_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea25_0,VO_REMAP_DRV_SET_CtrlFillInfoArea25_1,VO_REMAP_DRV_SET_CtrlFillDataArea25_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea26_0,VO_REMAP_DRV_SET_CtrlFillInfoArea26_1,VO_REMAP_DRV_SET_CtrlFillDataArea26_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea27_0,VO_REMAP_DRV_SET_CtrlFillInfoArea27_1,VO_REMAP_DRV_SET_CtrlFillDataArea27_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea28_0,VO_REMAP_DRV_SET_CtrlFillInfoArea28_1,VO_REMAP_DRV_SET_CtrlFillDataArea28_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea29_0,VO_REMAP_DRV_SET_CtrlFillInfoArea29_1,VO_REMAP_DRV_SET_CtrlFillDataArea29_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea30_0,VO_REMAP_DRV_SET_CtrlFillInfoArea30_1,VO_REMAP_DRV_SET_CtrlFillDataArea30_0},
    {VO_REMAP_DRV_SET_CtrlFillInfoArea31_0,VO_REMAP_DRV_SET_CtrlFillInfoArea31_1,VO_REMAP_DRV_SET_CtrlFillDataArea31_0},
};
/*
*
*/
static int VO_DRV_REMAP_DrawLineSet(VO_DRV_LINE_DRAW_U DrawAreaNum,VO_REMAP_CTRL_FILL_CTL_S *fillCtl)
{
    VO_CHECK_POINTER(fillCtl);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    unsigned int ErrCode = 0;
    if(DrawAreaNum > VO_LINE_DRAW_AREA_31 || DrawAreaNum < VO_LINE_DRAW_AREA_0)
    {
        ErrCode = 1;
    }

    if( 1 == fillCtl->line_draw_en)
    {
        U_VO_REMAP_CTRL_FILL_INFO_AREA_0  info0_udata;
        info0_udata.bits.line_draw_en     = fillCtl->line_draw_en;
        info0_udata.bits.v_line_u_en      = fillCtl->v_line_u_en;
        info0_udata.bits.h_line_b_en      = fillCtl->h_line_b_en;
        info0_udata.bits.v_line_l_en      = fillCtl->v_line_l_en;
        info0_udata.bits.v_line_r_en      = fillCtl->v_line_r_en;
        info0_udata.bits.line_start_pos_x = fillCtl->line_start_pos_x;
        info0_udata.bits.line_draw_en     = fillCtl->line_end_pos_x;
		remap_fill_func[DrawAreaNum][VO_FILLINFO_0](apstVoRemapReg, info0_udata.u32);


		U_VO_REMAP_CTRL_FILL_INFO_AREA_1  info1_udata;
        info1_udata.bits.line_start_pos_y = fillCtl->line_start_pos_y;
        info1_udata.bits.line_end_pos_y   = fillCtl->line_end_pos_y;
        info1_udata.bits.line_width_h     = fillCtl->line_width_h;
        info1_udata.bits.line_width_l     = fillCtl->line_width_l;
		remap_fill_func[DrawAreaNum][VO_FILLINFO_1](apstVoRemapReg, info1_udata.u32);


        U_VO_REMAP_CTRL_FILL_DATA_AREA_0  data_udata;
        data_udata.bits.fill_value_y      = fillCtl->fill_value_y;
        data_udata.bits.fill_value_cb     = fillCtl->fill_value_cb;
        data_udata.bits.fill_value_cr     = fillCtl->fill_value_cr;
        data_udata.bits.fill_alpha        = fillCtl->fill_alpha;
		remap_fill_func[DrawAreaNum][VO_FILLDATA_0](apstVoRemapReg, data_udata.u32);
    }
    return ErrCode;
}
/*
*
*/
static int VO_DRV_SetFillCmd(VO_REMAP_CTRL_FILL_CMD_S *pstvoRemapCmd)
{
    VO_CHECK_POINTER(pstvoRemapCmd);

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);
    
    U_VO_REMAP_CTRL_FILL_CMD          cmd_udata;
    cmd_udata.bits.fill_en_rgb        = pstvoRemapCmd->fill_en_rgb;
    cmd_udata.bits.fill_fill_en_yuv   = pstvoRemapCmd->fill_fill_en_yuv;
    cmd_udata.bits.image_active_h     = pstvoRemapCmd->image_active_h;
    cmd_udata.bits.image_active_v     = pstvoRemapCmd->image_active_v;
    VO_REMAP_DRV_SET_CtrlFillCmd(apstVoRemapReg, cmd_udata.u32);

    return 0;
}
/*
*
*/
int VO_DRV_SetRemap(unsigned int DrawAreaNum,VO_REMAP_CTL_S *pstVoRemap) 
{
    VO_CHECK_POINTER(pstVoRemap);

    //unsigned int DrawAreaNum = 0; 
    VO_REMAP_CTRL_FILL_CTL_S *fillCtl = NULL;
    //for(DrawAreaNum = 0; DrawAreaNum < VO_LINE_DRAW_AREA_MAX; DrawAreaNum++)
    {
        fillCtl = &pstVoRemap->fillCtl[DrawAreaNum];
        VO_DRV_REMAP_DrawLineSet(DrawAreaNum,fillCtl);
    }
    
    VO_REMAP_CTRL_FILL_CMD_S *pstvoRemapCmd = &pstVoRemap->fillCmd;
    VO_DRV_SetFillCmd(pstvoRemapCmd);
    
    return 0;
}
/*
*DEBUG
*/
int VO_DRV_GetRemapRegsVal(void)
{

    S_VO_REMAP_REGS_TYPE *apstVoRemapReg = NULL;
    VO_DRV_REMAP_REG_CTX(apstVoRemapReg);

    VO_REMAP_DRV_GET_RemapRegsVal(apstVoRemapReg);

  	return 0;
}
