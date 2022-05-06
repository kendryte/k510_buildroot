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
#include "video/isp_com.h"
#include "video/isp/ds/isp_ds_drv.h"
#include "video/isp/ds/isp_ds_reg.h"
//#include "video/isp/ds/isp_ds_calc.h"
#include <stdio.h>
#include <k510.h>

extern int ISP_2K_POST_V_Coef_TABLE[128];
extern int ISP_2K_POST_H_Coef_TABLE[192];
extern int ISP_2K_POST_V_Coef_Test_TABLE[128];
extern int ISP_2K_POST_H_Coef_Test_TABLE[192];
extern int ISP_2K_POST_V_Coef_Test2_TABLE[128];
extern int ISP_2K_POST_H_Coef_Test2_TABLE[192];
extern int ISP_2K_POST_V_Coef_Test3_TABLE[128];
extern int ISP_2K_POST_H_Coef_Test3_TABLE[192];

extern unsigned int  *reg_isp_2k_ds_base;
#define ISP_2K_DRV_DS_REG_CTX(pstCtx)	pstCtx = (S_ISP_DS_REGS_TYPE *)(reg_isp_2k_ds_base)
/*
* DS Control 
*/
int ISP_DRV_DS_SetInputSize(ISP_DS_INPUT_SIZE_S *pstInputSize)
{
	ISP_CHECK_POINTER(pstInputSize);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

	U_ISP_DS_INPUT_SIZE stInputSize;
	stInputSize.u32 = 0;
	stInputSize.bits.input_frame_height = pstInputSize->input_frame_height;
	stInputSize.bits.input_frame_width = pstInputSize->input_frame_width;	
	ISP_DS_DRV_SET_DsInputSize(apstIspDsReg, stInputSize.u32);
	return 0;
}

static int ISP_DRV_DS_SetRgb2YuvCoff(ISP_DS_OSD_RGB2YUV_COEFF_S *pstCoff)
{
    ISP_CHECK_POINTER(pstCoff);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
    ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

	U_ISP_DS_OSD_RGB2YUV_COEFF00 stCoff00;
	stCoff00.u32 = 0;
	stCoff00.bits.osd_rgb2yuv_coeff00 = pstCoff->osd_rgb2yuv_coeff00;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff00(apstIspDsReg, stCoff00.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF01 stCoff01;
	stCoff01.u32 = 0;
	stCoff01.bits.osd_rgb2yuv_coeff01 = pstCoff->osd_rgb2yuv_coeff01;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff01(apstIspDsReg, stCoff01.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF02 stCoff02;
	stCoff02.u32 = 0;
	stCoff02.bits.osd_rgb2yuv_coeff02 = pstCoff->osd_rgb2yuv_coeff02;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff02(apstIspDsReg, stCoff02.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF03 stCoff03;
	stCoff03.u32 = 0;
	stCoff03.bits.osd_rgb2yuv_coeff03 = pstCoff->osd_rgb2yuv_coeff03;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff03(apstIspDsReg, stCoff03.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF10 stCoff10;
	stCoff10.u32 = 0;
	stCoff10.bits.osd_rgb2yuv_coeff10 = pstCoff->osd_rgb2yuv_coeff10;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff10(apstIspDsReg, stCoff10.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF11 stCoff11;
	stCoff11.u32 = 0;
	stCoff11.bits.osd_rgb2yuv_coeff11 = pstCoff->osd_rgb2yuv_coeff11;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff11(apstIspDsReg, stCoff11.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF12 stCoff12;
	stCoff12.u32 = 0;
	stCoff12.bits.osd_rgb2yuv_coeff12 = pstCoff->osd_rgb2yuv_coeff12;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff12(apstIspDsReg, stCoff12.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF13 stCoff13;
	stCoff13.u32 = 0;
	stCoff13.bits.osd_rgb2yuv_coeff13 = pstCoff->osd_rgb2yuv_coeff13;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff13(apstIspDsReg, stCoff13.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF20 stCoff20;
	stCoff20.u32 = 0;
	stCoff20.bits.osd_rgb2yuv_coeff20 = pstCoff->osd_rgb2yuv_coeff20;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff20(apstIspDsReg, stCoff20.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF21 stCoff21;
	stCoff21.u32 = 0;
	stCoff21.bits.osd_rgb2yuv_coeff21 = pstCoff->osd_rgb2yuv_coeff21;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff21(apstIspDsReg, stCoff21.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF22 stCoff22;
	stCoff22.u32 = 0;
	stCoff22.bits.osd_rgb2yuv_coeff22 = pstCoff->osd_rgb2yuv_coeff22;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff22(apstIspDsReg, stCoff22.u32);

	U_ISP_DS_OSD_RGB2YUV_COEFF23 stCoff23;
	stCoff23.u32 = 0;
	stCoff23.bits.osd_rgb2yuv_coeff23 = pstCoff->osd_rgb2yuv_coeff23;
	ISP_DS_DRV_SET_DsOsdRgb2YuvCoeff23(apstIspDsReg, stCoff23.u32);
	return 0;
}

static int ISP_DRV_DS_SetYuv2RgbCoff(ISP_DS_OSD_YUV2RGB_COEFF_S *pstCoff)
{
	ISP_CHECK_POINTER(pstCoff);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

	U_ISP_DS_OSD_YUV2RGB_COEFF00 stCoff00;
	stCoff00.u32 = 0;
	stCoff00.bits.osd_yuv2rgb_coeff00 = pstCoff->osd_yuv2rgb_coeff00;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff00(apstIspDsReg, stCoff00.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF01 stCoff01;
	stCoff01.u32 = 0;
	stCoff01.bits.osd_yuv2rgb_coeff01 = pstCoff->osd_yuv2rgb_coeff01;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff01(apstIspDsReg, stCoff01.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF02 stCoff02;
	stCoff02.u32 = 0;
	stCoff02.bits.osd_yuv2rgb_coeff02 = pstCoff->osd_yuv2rgb_coeff02;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff02(apstIspDsReg, stCoff02.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF03 stCoff03;
	stCoff03.u32 = 0;
	stCoff03.bits.osd_yuv2rgb_coeff03 = pstCoff->osd_yuv2rgb_coeff03;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff03(apstIspDsReg, stCoff03.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF10 stCoff10;
	stCoff10.u32 = 0;
	stCoff10.bits.osd_yuv2rgb_coeff10 = pstCoff->osd_yuv2rgb_coeff10;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff10(apstIspDsReg, stCoff10.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF11 stCoff11;
	stCoff11.u32 = 0;
	stCoff11.bits.osd_yuv2rgb_coeff11 = pstCoff->osd_yuv2rgb_coeff11;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff11(apstIspDsReg, stCoff11.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF12 stCoff12;
	stCoff12.u32 = 0;
	stCoff12.bits.osd_yuv2rgb_coeff12 = pstCoff->osd_yuv2rgb_coeff12;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff12(apstIspDsReg, stCoff12.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF13 stCoff13;
	stCoff13.u32 = 0;
	stCoff13.bits.osd_yuv2rgb_coeff13 = pstCoff->osd_yuv2rgb_coeff13;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff13(apstIspDsReg, stCoff13.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF20 stCoff20;
	stCoff20.u32 = 0;
	stCoff20.bits.osd_yuv2rgb_coeff20 = pstCoff->osd_yuv2rgb_coeff20;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff20(apstIspDsReg, stCoff20.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF21 stCoff21;
	stCoff21.u32 = 0;
	stCoff21.bits.osd_yuv2rgb_coeff21 = pstCoff->osd_yuv2rgb_coeff21;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff21(apstIspDsReg, stCoff21.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF22 stCoff22;
	stCoff22.u32 = 0;
	stCoff22.bits.osd_yuv2rgb_coeff22 = pstCoff->osd_yuv2rgb_coeff22;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff22(apstIspDsReg, stCoff22.u32);

	U_ISP_DS_OSD_YUV2RGB_COEFF23 stCoff23;
	stCoff23.u32 = 0;
	stCoff23.bits.osd_yuv2rgb_coeff23 = pstCoff->osd_yuv2rgb_coeff23;
	ISP_DS_DRV_SET_DsOsdYuv2RgbCoeff23(apstIspDsReg, stCoff23.u32);
	return 0;
}

static int ISP_DRV_DS_SetHscaleParam(unsigned char u8Index, ISP_DS_HSCALE_PARM_S *pstHscale)
{
	ISP_CHECK_POINTER(pstHscale);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);


	if(u8Index == 0)
	{
        U_ISP_DS0_HSCALE_PARM stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_hscale_dstep = pstHscale->hscale_dstep;
		stDs0.bits.ds0_hscale_pstep = pstHscale->hscale_pstep;
		stDs0.bits.ds0_hscale_filter_en = pstHscale->hscale_filter_en;
		ISP_DS_DRV_SET_Ds0HscaleParm(apstIspDsReg, stDs0.u32);
	}
	
	if(u8Index == 1)
	{
	    U_ISP_DS1_HSCALE_PARM stDs1;	
		stDs1.u32 = 0;
		stDs1.bits.ds1_hscale_dstep = pstHscale->hscale_dstep;
		stDs1.bits.ds1_hscale_pstep = pstHscale->hscale_pstep;
		stDs1.bits.ds1_hscale_filter_en = pstHscale->hscale_filter_en;
		ISP_DS_DRV_SET_Ds1HscaleParm(apstIspDsReg, stDs1.u32);
	}
	
	if(u8Index == 2)
	{
        U_ISP_DS2_HSCALE_PARM stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_hscale_dstep = pstHscale->hscale_dstep;
		stDs2.bits.ds2_hscale_pstep = pstHscale->hscale_pstep;
		stDs2.bits.ds2_hscale_filter_en = pstHscale->hscale_filter_en;
		ISP_DS_DRV_SET_Ds2HscaleParm(apstIspDsReg, stDs2.u32);
	}
	return 0;
}

static int ISP_DRV_DS_SetVscaleParam(unsigned char u8Index, ISP_DS_VSCALE_PARM_S *pstVscale)
{
	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	U_ISP_DS0_VSCALE_PARM stDs0;
	U_ISP_DS1_VSCALE_PARM stDs1;
	U_ISP_DS2_VSCALE_PARM stDs2;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);
	ISP_CHECK_POINTER(pstVscale);

	if(u8Index == 0)
	{
		stDs0.u32 = 0;
		stDs0.bits.ds0_vscale_dstep = pstVscale->vscale_dstep;
		stDs0.bits.ds0_vscale_pstep = pstVscale->vscale_pstep;
		stDs0.bits.ds0_vscale_filter_en = pstVscale->vscale_filter_en;
		stDs0.bits.ds0_scale_en = pstVscale->scale_en;
		ISP_DS_DRV_SET_Ds0VscaleParm(apstIspDsReg, stDs0.u32);
	}
	
	if(u8Index == 1)
	{
		stDs1.u32 = 0;
		stDs1.bits.ds1_vscale_dstep = pstVscale->vscale_dstep;
		stDs1.bits.ds1_vscale_pstep = pstVscale->vscale_pstep;
		stDs1.bits.ds1_vscale_filter_en = pstVscale->vscale_filter_en;
		stDs1.bits.ds1_scale_en = pstVscale->scale_en;
		ISP_DS_DRV_SET_Ds1VscaleParm(apstIspDsReg, stDs1.u32);
	}
	
	if(u8Index == 2)
	{
		stDs2.u32 = 0;
		stDs2.bits.ds2_vscale_dstep = pstVscale->vscale_dstep;
		stDs2.bits.ds2_vscale_pstep = pstVscale->vscale_pstep;
		stDs2.bits.ds2_vscale_filter_en = pstVscale->vscale_filter_en;
		stDs2.bits.ds2_scale_en = pstVscale->scale_en;
		ISP_DS_DRV_SET_Ds2VscaleParm(apstIspDsReg, stDs2.u32);
	}
	return 0;
}

static int ISP_DRV_DS_SetOutputSize(unsigned char u8Index, ISP_DS_SIZE_S *pstSize)
{
	ISP_CHECK_POINTER(pstSize);
	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

	if(u8Index == 0)
	{
	    U_ISP_DS0_SIZE stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_frm_output_height = pstSize->frame_output_height;
		stDs0.bits.ds0_frm_output_width = pstSize->frame_output_width;
		ISP_DS_DRV_SET_Ds0Size(apstIspDsReg, stDs0.u32);
	}
	
	if(u8Index == 1)
	{
	    U_ISP_DS1_SIZE stDs1;
		stDs1.u32 = 0;
		stDs1.bits.ds1_frm_output_height = pstSize->frame_output_height;
		stDs1.bits.ds1_frm_output_width = pstSize->frame_output_width;
		ISP_DS_DRV_SET_Ds1Size(apstIspDsReg, stDs1.u32);
	}
	
	if(u8Index == 2)
	{
	    U_ISP_DS2_SIZE stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_frm_output_height = pstSize->frame_output_height;
		stDs2.bits.ds2_frm_output_width = pstSize->frame_output_width;
		ISP_DS_DRV_SET_Ds2Size(apstIspDsReg, stDs2.u32);
	}
	return 0;
}

static int ISP_DRV_DS_SetOutputFormat(unsigned char u8Index, ISP_DS_FORMAT_S *pstFormat)
{
    ISP_CHECK_POINTER(pstFormat);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

	if(u8Index == 0)
	{
	    U_ISP_DS0_FORMAT stDs0;
		stDs0.u32 = 0;
		stDs0.bits.ds0_out_rgb_mode = pstFormat->out_rgb_mode;
		stDs0.bits.ds0_out_rgb_en = pstFormat->out_rgb_en;
		stDs0.bits.ds0_out_yuv_mode = pstFormat->out_yuv_mode;
		stDs0.bits.ds0_out_uv_swap = pstFormat->out_uv_swap;
		ISP_DS_DRV_SET_Ds0Format(apstIspDsReg, stDs0.u32);
	}

	if(u8Index == 1)
	{
        U_ISP_DS1_FORMAT stDs1;
		stDs1.u32 = 1;
		stDs1.bits.ds1_out_rgb_mode = pstFormat->out_rgb_mode;
		stDs1.bits.ds1_out_rgb_en = pstFormat->out_rgb_en;
		stDs1.bits.ds1_out_yuv_mode = pstFormat->out_yuv_mode;
		stDs1.bits.ds1_out_uv_swap = pstFormat->out_uv_swap;
		ISP_DS_DRV_SET_Ds1Format(apstIspDsReg, stDs1.u32);
	}
	
	if(u8Index == 2)
	{
    	U_ISP_DS2_FORMAT stDs2;
		stDs2.u32 = 0;
		stDs2.bits.ds2_out_rgb_mode = pstFormat->out_rgb_mode;
		stDs2.bits.ds2_out_rgb_en = pstFormat->out_rgb_en;
		stDs2.bits.ds2_out_yuv_mode = pstFormat->out_yuv_mode;
		stDs2.bits.ds2_out_uv_swap = pstFormat->out_uv_swap;
		ISP_DS_DRV_SET_Ds2Format(apstIspDsReg, stDs2.u32);
	}
	return 0;
}

static int ISP_DRV_DS_SetDs0OsdAttr(unsigned char u8OsdIndex,ISP_DS_OSD_ATTR_S *pstOsdAttr)
{

	ISP_CHECK_POINTER(pstOsdAttr);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

    if(u8OsdIndex == 0)
    {
    	U_ISP_DS0_OSD0_INFO stOsd0Info;
        stOsd0Info.u32 = 0;
        stOsd0Info.bits.ds0_osd0_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd0Info.bits.ds0_osd0_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd0Info.bits.ds0_osd0_enable = pstOsdAttr->stOsdInfo.osd_enable;        
        ISP_DS_DRV_SET_Ds0Osd0Info(apstIspDsReg, stOsd0Info.u32);

    	U_ISP_DS0_OSD0_SIZE stOsd0Size;      
        stOsd0Size.u32 = 0;
        stOsd0Size.bits.ds0_osd0_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd0Size.bits.ds0_osd0_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds0Osd0Size(apstIspDsReg, stOsd0Size.u32);

    	U_ISP_DS0_OSD0_BUF_ADDR0 stOsd0Addr0;        
        stOsd0Addr0.u32 = 0;
        stOsd0Addr0.bits.ds0_osd0_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds0Osd0BufAddr0(apstIspDsReg, stOsd0Addr0.u32);

    	U_ISP_DS0_OSD0_BUF_ADDR1 stOsd0Addr1;  
        stOsd0Addr1.u32 = 0;
        stOsd0Addr1.bits.ds0_osd0_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        printf("stOsd0Addr1 =0x%x,osd_rgb_addr1 =0x%x\n",stOsd0Addr1.u32,pstOsdAttr->stOsdBuf.osd_rgb_addr1);
        ISP_DS_DRV_SET_Ds0Osd0BufAddr1(apstIspDsReg, stOsd0Addr1.u32);

    	U_ISP_DS0_OSD0_ALPHA_BUF_ADDR0 stOsd0AlphaAddr0;      
        stOsd0AlphaAddr0.u32 = 0;
        stOsd0AlphaAddr0.bits.ds0_osd0_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds0Osd0AlphaBufAddr0(apstIspDsReg, stOsd0AlphaAddr0.u32);

    	U_ISP_DS0_OSD0_ALPHA_BUF_ADDR1 stOsd0AlphaAddr1;
        stOsd0AlphaAddr1.u32 = 0;
        stOsd0AlphaAddr1.bits.ds0_osd0_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        printf("stOsd0Addr1 =0x%x,osd_alpha_addr1 =0x%x\n",stOsd0AlphaAddr1.u32,pstOsdAttr->stOsdBuf.osd_alpha_addr1);
        ISP_DS_DRV_SET_Ds0Osd0AlphaBufAddr1(apstIspDsReg, stOsd0AlphaAddr1.u32);

    	U_ISP_DS0_OSD0_DMA_CTL stOsd0DmaCtl;  
        stOsd0DmaCtl.u32 = 0;
        stOsd0DmaCtl.bits.ds0_osd0_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd0DmaCtl.bits.ds0_osd0_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd0DmaCtl.bits.ds0_osd0_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd0DmaCtl.bits.ds0_osd0_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd0DmaCtl.bits.ds0_osd0_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd0DmaCtl.bits.ds0_osd0_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd0DmaCtl.bits.ds0_osd0_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;
        ISP_DS_DRV_SET_Ds0Osd0DmaCtl(apstIspDsReg, stOsd0DmaCtl.u32);

    	U_ISP_DS0_OSD0_STRIDE stOsd0Stride;  
        stOsd0Stride.u32 = 0;
        stOsd0Stride.bits.ds0_osd0_stride = pstOsdAttr->stOsdBuf.osd_stride;
        stOsd0Stride.bits.ds0_osd0_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride;
        ISP_DS_DRV_SET_Ds0Osd0Stride(apstIspDsReg, stOsd0Stride.u32);

    	U_ISP_DS0_OSD0_X_RANGE stOsd0XRange;
        stOsd0XRange.u32 = 0;
        stOsd0XRange.bits.ds0_osd0_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd0XRange.bits.ds0_osd0_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds0Osd0XRange(apstIspDsReg, stOsd0XRange.u32);
        
    	U_ISP_DS0_OSD0_Y_RANGE stOsd0YRange;
        stOsd0YRange.u32 = 0;
        stOsd0YRange.bits.ds0_osd0_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd0YRange.bits.ds0_osd0_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;        
        ISP_DS_DRV_SET_Ds0Osd0YRange(apstIspDsReg, stOsd0YRange.u32);
    }

    
    if(u8OsdIndex == 1)
    {
    	U_ISP_DS0_OSD1_INFO stOsd1Info;
        stOsd1Info.u32 = 0;
        stOsd1Info.bits.ds0_osd1_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd1Info.bits.ds0_osd1_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd1Info.bits.ds0_osd1_enable = pstOsdAttr->stOsdInfo.osd_enable;        
        ISP_DS_DRV_SET_Ds0Osd1Info(apstIspDsReg, stOsd1Info.u32);

    	U_ISP_DS0_OSD1_SIZE stOsd1Size;  
        stOsd1Size.u32 = 0;
        stOsd1Size.bits.ds0_osd1_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd1Size.bits.ds0_osd1_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds0Osd1Size(apstIspDsReg, stOsd1Size.u32);

    	U_ISP_DS0_OSD1_BUF_ADDR0 stOsd1Addr0;   
        stOsd1Addr0.u32 = 0;
        stOsd1Addr0.bits.ds0_osd1_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds0Osd1BufAddr0(apstIspDsReg, stOsd1Addr0.u32);
        
        U_ISP_DS0_OSD1_BUF_ADDR1 stOsd1Addr1;
        stOsd1Addr1.u32 = 0;
        stOsd1Addr1.bits.ds0_osd1_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds0Osd1BufAddr1(apstIspDsReg, stOsd1Addr1.u32);

    	U_ISP_DS0_OSD1_ALPHA_BUF_ADDR0 stOsd1AlphaAddr0;   
        stOsd1AlphaAddr0.u32 = 0;
        stOsd1AlphaAddr0.bits.ds0_osd1_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds0Osd1AlphaBufAddr0(apstIspDsReg, stOsd1AlphaAddr0.u32);

    	U_ISP_DS0_OSD1_ALPHA_BUF_ADDR1 stOsd1AlphaAddr1;
        stOsd1AlphaAddr1.u32 = 0;
        stOsd1AlphaAddr1.bits.ds0_osd1_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds0Osd1AlphaBufAddr1(apstIspDsReg, stOsd1AlphaAddr1.u32);

    	U_ISP_DS0_OSD1_DMA_CTL stOsd1DmaCtl;   
        stOsd1DmaCtl.u32 = 0;
        stOsd1DmaCtl.bits.ds0_osd1_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd1DmaCtl.bits.ds0_osd1_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd1DmaCtl.bits.ds0_osd1_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds0_osd1_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd1DmaCtl.bits.ds0_osd1_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd1DmaCtl.bits.ds0_osd1_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd1DmaCtl.bits.ds0_osd1_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds0Osd1DmaCtl(apstIspDsReg, stOsd1DmaCtl.u32);
        
        U_ISP_DS0_OSD1_STRIDE stOsd1Stride;
        stOsd1Stride.u32 = 0;
        stOsd1Stride.bits.ds0_osd1_stride = pstOsdAttr->stOsdBuf.osd_stride;
        stOsd1Stride.bits.ds0_osd1_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride;
        ISP_DS_DRV_SET_Ds0Osd1Stride(apstIspDsReg, stOsd1Stride.u32);

	    U_ISP_DS0_OSD1_X_RANGE stOsd1XRange;
        stOsd1XRange.u32 = 0;
        stOsd1XRange.bits.ds0_osd1_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd1XRange.bits.ds0_osd1_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds0Osd1XRange(apstIspDsReg, stOsd1XRange.u32);
        
        U_ISP_DS0_OSD1_Y_RANGE stOsd1YRange;
        stOsd1YRange.u32 = 0;
        stOsd1YRange.bits.ds0_osd1_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd1YRange.bits.ds0_osd1_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds0Osd1YRange(apstIspDsReg, stOsd1YRange.u32);
    }
    
    if(u8OsdIndex == 2)
    {
    	U_ISP_DS0_OSD2_INFO stOsd2Info; 
        stOsd2Info.u32 = 0;
        stOsd2Info.bits.ds0_osd2_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd2Info.bits.ds0_osd2_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd2Info.bits.ds0_osd2_enable = pstOsdAttr->stOsdInfo.osd_enable;        
        ISP_DS_DRV_SET_Ds0Osd2Info(apstIspDsReg, stOsd2Info.u32);

    	U_ISP_DS0_OSD2_SIZE stOsd2Size; 
        stOsd2Size.u32 = 0;
        stOsd2Size.bits.ds0_osd2_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd2Size.bits.ds0_osd2_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds0Osd2Size(apstIspDsReg, stOsd2Size.u32);

    	U_ISP_DS0_OSD2_BUF_ADDR0 stOsd2Addr0;
        stOsd2Addr0.u32 = 0;
        stOsd2Addr0.bits.ds0_osd2_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds0Osd2BufAddr0(apstIspDsReg, stOsd2Addr0.u32);

        U_ISP_DS0_OSD2_BUF_ADDR1 stOsd2Addr1;
        stOsd2Addr1.u32 = 0;
        stOsd2Addr1.bits.ds0_osd2_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds0Osd2BufAddr1(apstIspDsReg, stOsd2Addr1.u32);

    	U_ISP_DS0_OSD2_ALPHA_BUF_ADDR0 stOsd2AlphaAddr0; 
        stOsd2AlphaAddr0.u32 = 0;
        stOsd2AlphaAddr0.bits.ds0_osd2_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds0Osd2AlphaBufAddr0(apstIspDsReg, stOsd2AlphaAddr0.u32);

    	U_ISP_DS0_OSD2_ALPHA_BUF_ADDR1 stOsd2AlphaAddr1;
        stOsd2AlphaAddr1.u32 = 0;
        stOsd2AlphaAddr1.bits.ds0_osd2_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds0Osd2AlphaBufAddr1(apstIspDsReg, stOsd2AlphaAddr1.u32);

    	U_ISP_DS0_OSD2_DMA_CTL stOsd2DmaCtl;
        stOsd2DmaCtl.u32 = 0;
        stOsd2DmaCtl.bits.ds0_osd2_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd2DmaCtl.bits.ds0_osd2_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd2DmaCtl.bits.ds0_osd2_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds0_osd2_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd2DmaCtl.bits.ds0_osd2_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd2DmaCtl.bits.ds0_osd2_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd2DmaCtl.bits.ds0_osd2_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds0Osd2DmaCtl(apstIspDsReg, stOsd2DmaCtl.u32);
        
    	U_ISP_DS0_OSD2_STRIDE stOsd2Stride;
        stOsd2Stride.u32 = 0;
        stOsd2Stride.bits.ds0_osd2_stride = pstOsdAttr->stOsdBuf.osd_stride;
        stOsd2Stride.bits.ds0_osd2_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride;
        ISP_DS_DRV_SET_Ds0Osd2Stride(apstIspDsReg, stOsd2Stride.u32);

	    U_ISP_DS0_OSD2_X_RANGE stOsd2XRange;
        stOsd2XRange.u32 = 0;
        stOsd2XRange.bits.ds0_osd2_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd2XRange.bits.ds0_osd2_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds0Osd2XRange(apstIspDsReg, stOsd2XRange.u32);
        
    	U_ISP_DS0_OSD2_Y_RANGE stOsd2YRange; 
        stOsd2YRange.u32 = 0;
        stOsd2YRange.bits.ds0_osd2_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd2YRange.bits.ds0_osd2_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds0Osd2YRange(apstIspDsReg, stOsd2YRange.u32);
    }
    
    return 0;
}

static int ISP_DRV_DS_SetDs1OsdAttr(unsigned char u8OsdIndex,ISP_DS_OSD_ATTR_S *pstOsdAttr)
{
	ISP_CHECK_POINTER(pstOsdAttr);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);
    
    if(u8OsdIndex == 0)
    {
    	U_ISP_DS1_OSD0_INFO stOsd0Info;
        stOsd0Info.u32 = 0;
        stOsd0Info.bits.ds1_osd0_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd0Info.bits.ds1_osd0_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd0Info.bits.ds1_osd0_enable = pstOsdAttr->stOsdInfo.osd_enable;
        ISP_DS_DRV_SET_Ds1Osd0Info(apstIspDsReg, stOsd0Info.u32);

    	U_ISP_DS1_OSD0_SIZE stOsd0Size;   
        stOsd0Size.u32 = 0;
        stOsd0Size.bits.ds1_osd0_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd0Size.bits.ds1_osd0_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds1Osd0Size(apstIspDsReg, stOsd0Size.u32);

    	U_ISP_DS1_OSD0_BUF_ADDR0 stOsd0Addr0; 
        stOsd0Addr0.u32 = 0;
        stOsd0Addr0.bits.ds1_osd0_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds1Osd0BufAddr0(apstIspDsReg, stOsd0Addr0.u32);

    	U_ISP_DS1_OSD0_BUF_ADDR1 stOsd0Addr1; 
        stOsd0Addr1.u32 = 0;
        stOsd0Addr1.bits.ds1_osd0_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds1Osd0BufAddr1(apstIspDsReg, stOsd0Addr1.u32);

        U_ISP_DS1_OSD0_ALPHA_BUF_ADDR0 stOsd0AlphaAddr0;    	
        stOsd0AlphaAddr0.u32 = 0;
        stOsd0AlphaAddr0.bits.ds1_osd0_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds1Osd0AlphaBufAddr0(apstIspDsReg, stOsd0AlphaAddr0.u32);

    	U_ISP_DS1_OSD0_ALPHA_BUF_ADDR1 stOsd0AlphaAddr1;
        stOsd0AlphaAddr1.u32 = 0;
        stOsd0AlphaAddr1.bits.ds1_osd0_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds1Osd0AlphaBufAddr1(apstIspDsReg, stOsd0AlphaAddr1.u32);

    	U_ISP_DS1_OSD0_DMA_CTL stOsd0DmaCtl;   
        stOsd0DmaCtl.u32 = 0;
        stOsd0DmaCtl.bits.ds1_osd0_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd0DmaCtl.bits.ds1_osd0_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd0DmaCtl.bits.ds1_osd0_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd0DmaCtl.bits.ds1_osd0_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd0DmaCtl.bits.ds1_osd0_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd0DmaCtl.bits.ds1_osd0_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd0DmaCtl.bits.ds1_osd0_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds1Osd0DmaCtl(apstIspDsReg, stOsd0DmaCtl.u32);
        
    	U_ISP_DS1_OSD0_STRIDE stOsd0Stride;
        stOsd0Stride.u32 = 0;
        stOsd0Stride.bits.ds1_osd0_stride = pstOsdAttr->stOsdBuf.osd_stride >> 3;
        stOsd0Stride.bits.ds1_osd0_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride >> 3;
        ISP_DS_DRV_SET_Ds1Osd0Stride(apstIspDsReg, stOsd0Stride.u32);

    	U_ISP_DS1_OSD0_X_RANGE stOsd0XRange;	
        stOsd0XRange.u32 = 0;
        stOsd0XRange.bits.ds1_osd0_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd0XRange.bits.ds1_osd0_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds1Osd0XRange(apstIspDsReg, stOsd0XRange.u32);
        
        U_ISP_DS1_OSD0_Y_RANGE stOsd0YRange;
        stOsd0YRange.u32 = 0;
        stOsd0YRange.bits.ds1_osd0_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd0YRange.bits.ds1_osd0_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds1Osd0YRange(apstIspDsReg, stOsd0YRange.u32);
    }

    
    if(u8OsdIndex == 1)
    {
    	U_ISP_DS1_OSD1_INFO stOsd1Info;
        stOsd1Info.u32 = 0;
        stOsd1Info.bits.ds1_osd1_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd1Info.bits.ds1_osd1_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd1Info.bits.ds1_osd1_enable = pstOsdAttr->stOsdInfo.osd_enable;        
        ISP_DS_DRV_SET_Ds1Osd1Info(apstIspDsReg, stOsd1Info.u32);

    	U_ISP_DS1_OSD1_SIZE stOsd1Size;  
        stOsd1Size.u32 = 0;
        stOsd1Size.bits.ds1_osd1_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd1Size.bits.ds1_osd1_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds1Osd1Size(apstIspDsReg, stOsd1Size.u32);
        
    	U_ISP_DS1_OSD1_BUF_ADDR0 stOsd1Addr0;
        stOsd1Addr0.u32 = 0;
        stOsd1Addr0.bits.ds1_osd1_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds1Osd1BufAddr0(apstIspDsReg, stOsd1Addr0.u32);

    	U_ISP_DS1_OSD1_BUF_ADDR1 stOsd1Addr1;
        stOsd1Addr1.u32 = 0;
        stOsd1Addr1.bits.ds1_osd1_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds1Osd1BufAddr1(apstIspDsReg, stOsd1Addr1.u32);

    	
        U_ISP_DS1_OSD1_ALPHA_BUF_ADDR0 stOsd1AlphaAddr0;     
        stOsd1AlphaAddr0.u32 = 0;
        stOsd1AlphaAddr0.bits.ds1_osd1_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds1Osd1AlphaBufAddr0(apstIspDsReg, stOsd1AlphaAddr0.u32);

	    U_ISP_DS1_OSD1_ALPHA_BUF_ADDR1 stOsd1AlphaAddr1;
        stOsd1AlphaAddr1.u32 = 0;
        stOsd1AlphaAddr1.bits.ds1_osd1_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds1Osd1AlphaBufAddr1(apstIspDsReg, stOsd1AlphaAddr1.u32);

    	U_ISP_DS1_OSD1_DMA_CTL stOsd1DmaCtl;   
        stOsd1DmaCtl.u32 = 0;
        stOsd1DmaCtl.bits.ds1_osd1_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd1DmaCtl.bits.ds1_osd1_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd1DmaCtl.bits.ds1_osd1_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds1_osd1_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd1DmaCtl.bits.ds1_osd1_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd1DmaCtl.bits.ds1_osd1_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd1DmaCtl.bits.ds1_osd1_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds1Osd1DmaCtl(apstIspDsReg, stOsd1DmaCtl.u32);

    	U_ISP_DS1_OSD1_STRIDE stOsd1Stride;    
        stOsd1Stride.u32 = 0;
        stOsd1Stride.bits.ds1_osd1_osd_stride = pstOsdAttr->stOsdBuf.osd_stride >> 3;
        stOsd1Stride.bits.ds1_osd1_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride >> 3;
        ISP_DS_DRV_SET_Ds1Osd1Stride(apstIspDsReg, stOsd1Stride.u32);

    	U_ISP_DS1_OSD1_X_RANGE stOsd1XRange;
        stOsd1XRange.u32 = 0;
        stOsd1XRange.bits.ds1_osd1_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd1XRange.bits.ds1_osd1_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds1Osd1XRange(apstIspDsReg, stOsd1XRange.u32);

    	U_ISP_DS1_OSD1_Y_RANGE stOsd1YRange;     
        stOsd1YRange.u32 = 0;
        stOsd1YRange.bits.ds1_osd1_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd1YRange.bits.ds1_osd1_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds1Osd1YRange(apstIspDsReg, stOsd1YRange.u32);
    }
    
    if(u8OsdIndex == 2)
    {
    	U_ISP_DS1_OSD2_INFO stOsd2Info;
        stOsd2Info.u32 = 0;
        stOsd2Info.bits.ds1_osd2_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd2Info.bits.ds1_osd2_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd2Info.bits.ds1_osd2_enable = pstOsdAttr->stOsdInfo.osd_enable;        
        ISP_DS_DRV_SET_Ds1Osd2Info(apstIspDsReg, stOsd2Info.u32);

    	U_ISP_DS1_OSD2_SIZE stOsd2Size;
        stOsd2Size.u32 = 0;
        stOsd2Size.bits.ds1_osd2_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd2Size.bits.ds1_osd2_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds1Osd2Size(apstIspDsReg, stOsd2Size.u32);

    	U_ISP_DS1_OSD2_BUF_ADDR0 stOsd2Addr0;  
        stOsd2Addr0.u32 = 0;
        stOsd2Addr0.bits.ds1_osd2_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds1Osd2BufAddr0(apstIspDsReg, stOsd2Addr0.u32);

    	U_ISP_DS1_OSD2_BUF_ADDR1 stOsd2Addr1;     
        stOsd2Addr1.u32 = 0;
        stOsd2Addr1.bits.ds1_osd2_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds1Osd2BufAddr1(apstIspDsReg, stOsd2Addr1.u32);

    	U_ISP_DS1_OSD2_ALPHA_BUF_ADDR0 stOsd2AlphaAddr0;
        stOsd2AlphaAddr0.u32 = 0;
        stOsd2AlphaAddr0.bits.ds1_osd2_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds1Osd2AlphaBufAddr0(apstIspDsReg, stOsd2AlphaAddr0.u32);

    	U_ISP_DS1_OSD2_ALPHA_BUF_ADDR1 stOsd2AlphaAddr1;
        stOsd2AlphaAddr1.u32 = 0;
        stOsd2AlphaAddr1.bits.ds1_osd2_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds1Osd2AlphaBufAddr1(apstIspDsReg, stOsd2AlphaAddr1.u32);

    	U_ISP_DS1_OSD2_DMA_CTL stOsd2DmaCtl;   
        stOsd2DmaCtl.u32 = 0;
        stOsd2DmaCtl.bits.ds1_osd2_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd2DmaCtl.bits.ds1_osd2_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd2DmaCtl.bits.ds1_osd2_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds1_osd2_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd2DmaCtl.bits.ds1_osd2_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd2DmaCtl.bits.ds1_osd2_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd2DmaCtl.bits.ds1_osd2_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds1Osd2DmaCtl(apstIspDsReg, stOsd2DmaCtl.u32);
        
    	U_ISP_DS1_OSD2_STRIDE stOsd2Stride;
        stOsd2Stride.u32 = 0;
        stOsd2Stride.bits.ds1_osd2_stride = pstOsdAttr->stOsdBuf.osd_stride >> 3;
        stOsd2Stride.bits.ds1_osd2_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride >> 3;
        ISP_DS_DRV_SET_Ds1Osd2Stride(apstIspDsReg, stOsd2Stride.u32);

	    U_ISP_DS1_OSD2_X_RANGE stOsd2XRange;
        stOsd2XRange.u32 = 0;
        stOsd2XRange.bits.ds1_osd2_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd2XRange.bits.ds1_osd2_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds1Osd2XRange(apstIspDsReg, stOsd2XRange.u32);
        
    	U_ISP_DS1_OSD2_Y_RANGE stOsd2YRange; 
        stOsd2YRange.u32 = 0;
        stOsd2YRange.bits.ds1_osd2_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd2YRange.bits.ds1_osd2_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds1Osd2YRange(apstIspDsReg, stOsd2YRange.u32);
    }
    
    return 0;
}

static int ISP_DRV_DS_SetDs2OsdAttr(unsigned char u8OsdIndex,ISP_DS_OSD_ATTR_S *pstOsdAttr)
{
	ISP_CHECK_POINTER(pstOsdAttr);

	S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
	ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);
    
    if(u8OsdIndex == 0)
    {
	    U_ISP_DS2_OSD0_INFO stOsd0Info;
        stOsd0Info.u32 = 0;
        stOsd0Info.bits.ds2_osd0_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd0Info.bits.ds2_osd0_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd0Info.bits.ds2_osd0_enable = pstOsdAttr->stOsdInfo.osd_enable;        
        ISP_DS_DRV_SET_Ds2Osd0Info(apstIspDsReg, stOsd0Info.u32);

    	U_ISP_DS2_OSD0_SIZE stOsd0Size; 
        stOsd0Size.u32 = 0;
        stOsd0Size.bits.ds2_osd0_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd0Size.bits.ds2_osd0_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds2Osd0Size(apstIspDsReg, stOsd0Size.u32);

    	U_ISP_DS2_OSD0_BUF_ADDR0 stOsd0Addr0;    
        stOsd0Addr0.u32 = 0;
        stOsd0Addr0.bits.ds2_osd0_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds2Osd0BufAddr0(apstIspDsReg, stOsd0Addr0.u32);

    	U_ISP_DS2_OSD0_BUF_ADDR1 stOsd0Addr1;    	   
        stOsd0Addr1.u32 = 0;
        stOsd0Addr1.bits.ds2_osd0_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds2Osd0BufAddr1(apstIspDsReg, stOsd0Addr1.u32);

        U_ISP_DS2_OSD0_ALPHA_BUF_ADDR0 stOsd0AlphaAddr0;   
        stOsd0AlphaAddr0.u32 = 0;
        stOsd0AlphaAddr0.bits.ds2_osd0_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds2Osd0AlphaBufAddr0(apstIspDsReg, stOsd0AlphaAddr0.u32);

    	U_ISP_DS2_OSD0_ALPHA_BUF_ADDR1 stOsd0AlphaAddr1;
        stOsd0AlphaAddr1.u32 = 0;
        stOsd0AlphaAddr1.bits.ds2_osd0_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds2Osd0AlphaBufAddr1(apstIspDsReg, stOsd0AlphaAddr1.u32);
        
    	U_ISP_DS2_OSD0_DMA_CTL stOsd0DmaCtl;
        stOsd0DmaCtl.u32 = 0;
        stOsd0DmaCtl.bits.ds2_osd0_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd0DmaCtl.bits.ds2_osd0_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd0DmaCtl.bits.ds2_osd0_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd0DmaCtl.bits.ds2_osd0_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd0DmaCtl.bits.ds2_osd0_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd0DmaCtl.bits.ds2_osd0_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd0DmaCtl.bits.ds2_osd0_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds2Osd0DmaCtl(apstIspDsReg, stOsd0DmaCtl.u32);

    	U_ISP_DS2_OSD0_STRIDE stOsd0Stride;
        stOsd0Stride.u32 = 0;
        stOsd0Stride.bits.ds2_osd0_stride = pstOsdAttr->stOsdBuf.osd_stride >> 3;
        stOsd0Stride.bits.ds2_osd0_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride >> 3;
        ISP_DS_DRV_SET_Ds2Osd0Stride(apstIspDsReg, stOsd0Stride.u32);

    	U_ISP_DS2_OSD0_X_RANGE stOsd0XRange;
        stOsd0XRange.u32 = 0;
        stOsd0XRange.bits.ds2_osd0_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd0XRange.bits.ds2_osd0_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds2Osd0XRange(apstIspDsReg, stOsd0XRange.u32);

    	U_ISP_DS2_OSD0_Y_RANGE stOsd0YRange;    
        stOsd0YRange.u32 = 0;
        stOsd0YRange.bits.ds2_osd0_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd0YRange.bits.ds2_osd0_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds2Osd0YRange(apstIspDsReg, stOsd0YRange.u32);
    }

    
    if(u8OsdIndex == 1)
    {
    	U_ISP_DS2_OSD1_INFO stOsd1Info;
        stOsd1Info.u32 = 0;
        stOsd1Info.bits.ds2_osd1_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd1Info.bits.ds2_osd1_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd1Info.bits.ds2_osd1_enable = pstOsdAttr->stOsdInfo.osd_enable;                
        ISP_DS_DRV_SET_Ds2Osd1Info(apstIspDsReg, stOsd1Info.u32);

    	U_ISP_DS2_OSD1_SIZE stOsd1Size; 
        stOsd1Size.u32 = 0;
        stOsd1Size.bits.ds2_osd1_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd1Size.bits.ds2_osd1_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds2Osd1Size(apstIspDsReg, stOsd1Size.u32);

    	U_ISP_DS2_OSD1_BUF_ADDR0 stOsd1Addr0;  
        stOsd1Addr0.u32 = 0;
        stOsd1Addr0.bits.ds2_osd1_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds2Osd1BufAddr0(apstIspDsReg, stOsd1Addr0.u32);

    	U_ISP_DS2_OSD1_BUF_ADDR1 stOsd1Addr1;     
        stOsd1Addr1.u32 = 0;
        stOsd1Addr1.bits.ds2_osd1_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds2Osd1BufAddr1(apstIspDsReg, stOsd1Addr1.u32);

    	U_ISP_DS2_OSD1_ALPHA_BUF_ADDR0 stOsd1AlphaAddr0; 
        stOsd1AlphaAddr0.u32 = 0;
        stOsd1AlphaAddr0.bits.ds2_osd1_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds2Osd1AlphaBufAddr0(apstIspDsReg, stOsd1AlphaAddr0.u32);

    	U_ISP_DS2_OSD1_ALPHA_BUF_ADDR1 stOsd1AlphaAddr1;
        stOsd1AlphaAddr1.u32 = 0;
        stOsd1AlphaAddr1.bits.ds2_osd1_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds2Osd1AlphaBufAddr1(apstIspDsReg, stOsd1AlphaAddr1.u32);

    	U_ISP_DS2_OSD1_DMA_CTL stOsd1DmaCtl;     
        stOsd1DmaCtl.u32 = 0;
        stOsd1DmaCtl.bits.ds2_osd1_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd1DmaCtl.bits.ds2_osd1_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd1DmaCtl.bits.ds2_osd1_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds2_osd1_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd1DmaCtl.bits.ds2_osd1_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd1DmaCtl.bits.ds2_osd1_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd1DmaCtl.bits.ds2_osd1_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd1DmaCtl.bits.ds2_osd1_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;        
        ISP_DS_DRV_SET_Ds2Osd1DmaCtl(apstIspDsReg, stOsd1DmaCtl.u32);

    	U_ISP_DS2_OSD1_STRIDE stOsd1Stride;  
        stOsd1Stride.u32 = 0;
        stOsd1Stride.bits.ds2_osd1_osd_stride = pstOsdAttr->stOsdBuf.osd_stride >> 3;
        stOsd1Stride.bits.ds2_osd1_osd_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride >> 3;
        ISP_DS_DRV_SET_Ds2Osd1Stride(apstIspDsReg, stOsd1Stride.u32);

    	U_ISP_DS2_OSD1_X_RANGE stOsd1XRange;
        stOsd1XRange.u32 = 0;
        stOsd1XRange.bits.ds2_osd1_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd1XRange.bits.ds2_osd1_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds2Osd1XRange(apstIspDsReg, stOsd1XRange.u32);

    	U_ISP_DS2_OSD1_Y_RANGE stOsd1YRange;     
        stOsd1YRange.u32 = 0;
        stOsd1YRange.bits.ds2_osd1_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd1YRange.bits.ds2_osd1_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds2Osd1YRange(apstIspDsReg, stOsd1YRange.u32);
    }
    
    if(u8OsdIndex == 2)
    {
    	U_ISP_DS2_OSD2_INFO stOsd2Info;
        stOsd2Info.u32 = 0;
        stOsd2Info.bits.ds2_osd2_type = pstOsdAttr->stOsdInfo.osd_type;
        stOsd2Info.bits.ds2_osd2_alpha_tpye = pstOsdAttr->stOsdInfo.osd_alpha_tpye;
        stOsd2Info.bits.ds2_osd2_enable = pstOsdAttr->stOsdInfo.osd_enable;                
        ISP_DS_DRV_SET_Ds2Osd2Info(apstIspDsReg, stOsd2Info.u32);

    	U_ISP_DS2_OSD2_SIZE stOsd2Size; 
        stOsd2Size.u32 = 0;
        stOsd2Size.bits.ds2_osd2_width = pstOsdAttr->stOsdSize.osd_width;
        stOsd2Size.bits.ds2_osd2_height = pstOsdAttr->stOsdSize.osd_height;
        ISP_DS_DRV_SET_Ds2Osd2Size(apstIspDsReg, stOsd2Size.u32);

    	U_ISP_DS2_OSD2_BUF_ADDR0 stOsd2Addr0;   
        stOsd2Addr0.u32 = 0;
        stOsd2Addr0.bits.ds2_osd2_rgb_addr0 = pstOsdAttr->stOsdBuf.osd_rgb_addr0;
        ISP_DS_DRV_SET_Ds2Osd2BufAddr0(apstIspDsReg, stOsd2Addr0.u32);
        
    	U_ISP_DS2_OSD2_BUF_ADDR1 stOsd2Addr1; 
        stOsd2Addr1.u32 = 0;
        stOsd2Addr1.bits.ds2_osd2_rgb_addr1 = pstOsdAttr->stOsdBuf.osd_rgb_addr1;
        ISP_DS_DRV_SET_Ds2Osd2BufAddr1(apstIspDsReg, stOsd2Addr1.u32);

    	U_ISP_DS2_OSD2_ALPHA_BUF_ADDR0 stOsd2AlphaAddr0; 
        stOsd2AlphaAddr0.u32 = 0;
        stOsd2AlphaAddr0.bits.ds2_osd2_alpha_addr0 = pstOsdAttr->stOsdBuf.osd_alpha_addr0;
        ISP_DS_DRV_SET_Ds2Osd2AlphaBufAddr0(apstIspDsReg, stOsd2AlphaAddr0.u32);

    	U_ISP_DS2_OSD2_ALPHA_BUF_ADDR1 stOsd2AlphaAddr1;
        stOsd2AlphaAddr1.u32 = 0;
        stOsd2AlphaAddr1.bits.ds2_osd2_alpha_addr1 = pstOsdAttr->stOsdBuf.osd_alpha_addr1;
        ISP_DS_DRV_SET_Ds2Osd2AlphaBufAddr1(apstIspDsReg, stOsd2AlphaAddr1.u32);

    	U_ISP_DS2_OSD2_DMA_CTL stOsd2DmaCtl;  
        stOsd2DmaCtl.u32 = 0;
        stOsd2DmaCtl.bits.ds2_osd2_dma_request_length = pstOsdAttr->stOsdDmaCtl.osd_dma_request_length;
        stOsd2DmaCtl.bits.ds2_osd2_dma_map = pstOsdAttr->stOsdDmaCtl.osd_dma_map;
        stOsd2DmaCtl.bits.ds2_osd2_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds2_osd2_rgb_rev = pstOsdAttr->stOsdDmaCtl.osd_rgb_rev;
        stOsd2DmaCtl.bits.ds2_osd2_global_alpha = pstOsdAttr->stOsdDmaCtl.osd_global_alpha;
        stOsd2DmaCtl.bits.ds2_osd2_swap_64 = pstOsdAttr->stOsdDmaCtl.osd_swap_64;
        stOsd2DmaCtl.bits.ds2_osd2_outstanding_num = pstOsdAttr->stOsdDmaCtl.osd_outstanding_num;
        stOsd2DmaCtl.bits.ds2_osd2_bd_limit_en = pstOsdAttr->stOsdDmaCtl.osd_bd_limit_en;                
        ISP_DS_DRV_SET_Ds2Osd2DmaCtl(apstIspDsReg, stOsd2DmaCtl.u32);

    	U_ISP_DS2_OSD2_STRIDE stOsd2Stride;   
        stOsd2Stride.u32 = 0;
        stOsd2Stride.bits.ds2_osd2_stride = pstOsdAttr->stOsdBuf.osd_stride >> 3;
        stOsd2Stride.bits.ds2_osd2_alpha_stride = pstOsdAttr->stOsdBuf.osd_alpha_stride >> 3;
        ISP_DS_DRV_SET_Ds2Osd2Stride(apstIspDsReg, stOsd2Stride.u32);

    	U_ISP_DS2_OSD2_X_RANGE stOsd2XRange;
        stOsd2XRange.u32 = 0;
        stOsd2XRange.bits.ds2_osd2_start_x = pstOsdAttr->stOsdBuf.osd_position_start_x;
        stOsd2XRange.bits.ds2_osd2_stop_x = pstOsdAttr->stOsdBuf.osd_position_stop_x;
        ISP_DS_DRV_SET_Ds2Osd2XRange(apstIspDsReg, stOsd2XRange.u32);
        
        U_ISP_DS2_OSD2_Y_RANGE stOsd2YRange; 
        stOsd2YRange.u32 = 0;
        stOsd2YRange.bits.ds2_osd2_start_y = pstOsdAttr->stOsdBuf.osd_position_start_y;
        stOsd2YRange.bits.ds2_osd2_stop_y = pstOsdAttr->stOsdBuf.osd_position_stop_y;
        ISP_DS_DRV_SET_Ds2Osd2YRange(apstIspDsReg, stOsd2YRange.u32);
    }
    
    return 0;
}
/*
*
*/
static int ISP_DRV_DS_SetVCoef(int a[],int num)
{
    S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
    ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);
    
    unsigned int addr = &apstIspDsReg->ISP_VSCALE_COFF_BASE[0];//0x92663000+ (0x0440 <<2);
    printf("ISP_DRV_DS_SetVCoef :ISP_VSCALE_COFF_BASE = 0x%x addr =  0x%x \n",&apstIspDsReg->ISP_VSCALE_COFF_BASE[0],addr);
    for (int i =0;i<num; i++)
    {
    //	RegWr32((base_addr + ((i*2)<<2)),a[i*2]);
    //	RegWr32((base_addr + ((i*2+1)<<2)),a[i*2+1]);
        apstIspDsReg->ISP_VSCALE_COFF_BASE[i*2] = a[i*2];
        apstIspDsReg->ISP_VSCALE_COFF_BASE[i*2+1] = a[i*2+1];
        //writel(a[i*2],(addr + ((i*2)<<2)));
        //writel(a[i*2+1],(addr + ((i*2+1)<<2)));

    }
    printf("Isp2K DS VCoef Config done!\n");
    return 0;
}
/*
*
*/
static int ISP_DRV_DS_SetHCoef0(int a[],int num)
{
    S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
    ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);
    
    unsigned int addr = &apstIspDsReg->ISP_HSCALE_COFF_0_BASE[0];//addr = 0x92663000+ (0x0140 <<2);
    printf("ISP_DRV_DS_SetVCoef :ISP_HSCALE_COFF_0_BASE = 0x%x addr = 0x%x\n",&apstIspDsReg->ISP_HSCALE_COFF_0_BASE[0],addr);
    for (int i =0;i<num; i++)
    {
        //writel(a[i*3],(addr + ((i*4)<<2)));
        //writel(a[i*3+1],(addr + ((i*4+1)<<2)));
        //writel(a[i*3+2],(addr + ((i*4+2)<<2)));
        apstIspDsReg->ISP_HSCALE_COFF_0_BASE[i*4] = a[i*3];
        apstIspDsReg->ISP_HSCALE_COFF_0_BASE[i*4+1] = a[i*3+1];
        apstIspDsReg->ISP_HSCALE_COFF_0_BASE[i*4+2] = a[i*3+2];
    }
    printf("Isp2K DS HCoef0 Config done!\n");
    return 0;
}
/*
*
*/
static int ISP_DRV_DS_SetHCoef1(int a[],int num)
{
    S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
    ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

    unsigned int addr = &apstIspDsReg->ISP_HSCALE_COFF_1_BASE[0];//0x92663000+ (0x0240 <<2);
    printf("ISP_DRV_DS_SetVCoef :ISP_HSCALE_COFF_1_BASE = 0x%x ,addr =0x%x \n",&apstIspDsReg->ISP_HSCALE_COFF_1_BASE[0],addr); 
    for (int i =0;i<num; i++)
    {
        //writel(a[i*3],(addr + ((i*4)<<2)));
        //writel(a[i*3+1],(addr + ((i*4+1)<<2)));
        //writel(a[i*3+2],(addr + ((i*4+2)<<2)));
        apstIspDsReg->ISP_HSCALE_COFF_1_BASE[i*4] = a[i*3];
        apstIspDsReg->ISP_HSCALE_COFF_1_BASE[i*4+1] = a[i*3+1];
        apstIspDsReg->ISP_HSCALE_COFF_1_BASE[i*4+2] = a[i*3+2];
    }
    printf("Isp2K DS HCoef1 Config done!\n");
    return 0;
}
/*
*
*/
static int ISP_DRV_DS_SetHCoef2(int a[],int num)
{
    S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
    ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);
    
    unsigned int addr = &apstIspDsReg->ISP_HSCALE_COFF_2_BASE[0];//0x92663000+ (0x0340 <<2);
    printf("ISP_DRV_DS_SetVCoef :ISP_HSCALE_COFF_2_BASE = 0x%x addr=0x%x \n",&apstIspDsReg->ISP_HSCALE_COFF_2_BASE[0],addr);  
    for (int i =0;i<num; i++)
    {
        //writel(a[i*3],(addr + ((i*4)<<2)));
        //writel(a[i*3+1],(addr + ((i*4+1)<<2)));
        //writel(a[i*3+2],(addr + ((i*4+2)<<2)));
        apstIspDsReg->ISP_HSCALE_COFF_2_BASE[i*4] = a[i*3];
        apstIspDsReg->ISP_HSCALE_COFF_2_BASE[i*4+1] = a[i*3+1];
        apstIspDsReg->ISP_HSCALE_COFF_2_BASE[i*4+2] = a[i*3+2];
    }
    printf("Isp2K DS HCoef2 Config done!\n");
    return 0;
}
/*
*
*/
void ISP_DRV_DS_SetCoeff(void)
{
	ISP_DRV_DS_SetVCoef(ISP_2K_POST_V_Coef_TABLE,64);
	ISP_DRV_DS_SetHCoef0(ISP_2K_POST_H_Coef_TABLE,64);
	ISP_DRV_DS_SetHCoef1(ISP_2K_POST_H_Coef_TABLE,64);
	ISP_DRV_DS_SetHCoef2(ISP_2K_POST_H_Coef_TABLE,64);
	return;
}
/*
*
*/
static void ISP_DRV_SetSingleDS(unsigned int u8Index,ISP_S_DS_ATTR_S *stSDsAttr)
{
    ISP_CHECK_POINTER(stSDsAttr);

   // isp_ds_calc_scale(inputsize,dsInfo);

    ISP_DS_HSCALE_PARM_S *pstHscale = &stSDsAttr->stHscalePram;
//	pstHscale.hscale_pstep = dsInfo->stHscalePram.hscale_pstep;//(InputWidth / OutputWidth0);
//	pstHscale.hscale_dstep = dsInfo->stHscalePram.hscale_dstep;//((InputWidth % OutputWidth0) * 65536 / OutputWidth0);
//	pstHscale.hscale_filter_en = dsInfo->stHscalePram.hscale_filter_en;//dsInfo1;
    ISP_DRV_DS_SetHscaleParam(u8Index, pstHscale);

    ISP_DS_VSCALE_PARM_S *pstVscale = &stSDsAttr->stVscalePram;
	//pstVscale.vscale_pstep = dsInfo->stVscalePram.vscale_pstep;//(InputHeight / OutputHeight0);
	//pstVscale.vscale_dstep = dsInfo->stVscalePram.vscale_dstep;//((InputHeight % OutputHeight0) * 65536 / OutputHeight0);
	//pstVscale.vscale_filter_en = dsInfo->stVscalePram.vscale_filter_en;//1;
	//pstVscale.scale_en = dsInfo->stVscalePram.scale_en;//1;
    ISP_DRV_DS_SetVscaleParam(u8Index, pstVscale);
	
    ISP_DS_SIZE_S *pstDsSize = &stSDsAttr->stDsSize;
	//pstSize.frame_output_width = dsInfo->stDsSize.frame_output_width;//OutputWidth0 -1;
	//pstSize.frame_output_height = dsInfo->stDsSize.frame_output_height;//OutputHeight0 -1;
	ISP_DRV_DS_SetOutputSize(u8Index, pstDsSize);
	
    ISP_DS_FORMAT_S *pstFormat = &stSDsAttr->stDsFormat;	
	//pstFormat.out_rgb_mode = dsInfo->stDsFormat.out_rgb_mode;//0;
	//pstFormat.out_rgb_en = dsInfo->stDsFormat.out_rgb_en;//0;
	//pstFormat.out_yuv_mode = dsInfo->stDsFormat.out_yuv_mode;//0;
	//pstFormat.out_uv_swap = dsInfo->stDsFormat.out_uv_swap;//0;
	ISP_DRV_DS_SetOutputFormat(u8Index, pstFormat);


    if(0 == u8Index)
    {
        unsigned int u8OsdIndex = 0;
        ISP_DS_OSD_ATTR_S *pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs0OsdAttr(u8OsdIndex,pstOsdAttr);

        u8OsdIndex = 1;
        pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs0OsdAttr(u8OsdIndex,pstOsdAttr);

        u8OsdIndex = 2;
        pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs0OsdAttr(u8OsdIndex,pstOsdAttr);
    }
 

    if(1 == u8Index)
    {
        unsigned int u8OsdIndex = 0;
        ISP_DS_OSD_ATTR_S *pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs1OsdAttr(u8OsdIndex,pstOsdAttr);

        u8OsdIndex = 1;
        pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs1OsdAttr(u8OsdIndex,pstOsdAttr);

        u8OsdIndex = 2;
        pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs1OsdAttr(u8OsdIndex,pstOsdAttr);
    }


    if(2 == u8Index)
    {
        unsigned int u8OsdIndex = 0;
        ISP_DS_OSD_ATTR_S *pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs2OsdAttr(u8OsdIndex,pstOsdAttr);

        u8OsdIndex = 1;
        pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs2OsdAttr(u8OsdIndex,pstOsdAttr);

        u8OsdIndex = 2;
        pstOsdAttr = &stSDsAttr->stDsOsdAttr[u8OsdIndex];
        ISP_DRV_DS_SetDs2OsdAttr(u8OsdIndex,pstOsdAttr);
    }

    return;    
}
/*
*
*/
int ISP_DRV_SetDs(ISP_DS_ATTR_S *pstDsAttr)
{
    ISP_CHECK_POINTER(pstDsAttr);

    //InputWidth = width;
    //InputHeight = height;
    
    //OutputWidth0 = 960;
    //OutputHeight0 = 1080;
    
    //OutputWidth1 = 320;
    //OutputHeight1 = 240;

    //OutputWidth2 = 256;
    //OutputHeight2 = 240;
 
    ISP_DRV_DS_SetCoeff();
    
    ISP_DS_INPUT_SIZE_S *pstInputSize = &pstDsAttr->stDsInputSize;
    ISP_DRV_DS_SetInputSize(pstInputSize);

    ISP_DS_OSD_RGB2YUV_COEFF_S *pstRgb2YuvCoeff = &pstDsAttr->stDsOsdRgb2YuvCoeff;
    ISP_DRV_DS_SetRgb2YuvCoff(pstRgb2YuvCoeff);

    ISP_DS_OSD_YUV2RGB_COEFF_S *pstYuv2RgbCoeff = &pstDsAttr->stDsOsdYuv2RgbCoeff;
    ISP_DRV_DS_SetYuv2RgbCoff(pstYuv2RgbCoeff);

    unsigned int u8Index = 0;
    ISP_S_DS_ATTR_S	*pstSDsAttr = &pstDsAttr->stSDsAttr[u8Index];    
    ISP_DRV_SetSingleDS(u8Index,pstSDsAttr);

    u8Index = 1;
    pstSDsAttr = &pstDsAttr->stSDsAttr[u8Index];
    ISP_DRV_SetSingleDS(u8Index,pstSDsAttr);

    u8Index = 2;
    pstSDsAttr = &pstDsAttr->stSDsAttr[u8Index];
    ISP_DRV_SetSingleDS(u8Index,pstSDsAttr);

    return 0;
}

int ISP_DRV_GetDsRegsVal(void)
{
    S_ISP_DS_REGS_TYPE *apstIspDsReg = NULL;
    ISP_2K_DRV_DS_REG_CTX(apstIspDsReg);

	ISP_DS_DRV_GET_DsRegsVal(apstIspDsReg);

	return 0;
}
