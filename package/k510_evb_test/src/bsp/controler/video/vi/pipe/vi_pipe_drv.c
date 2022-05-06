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
#include "video/video_subsystem_addr.h"
//#include "video/vi/vi.h"
#include "video/vi/pipe/vi_pipe_reg.h"
#include "video/vi/pipe/vi_pipe_drv.h"

unsigned int *reg_vi_pipe_base[VI_MAX_PIPE_NUM];
//extern unsigned int reg_vi_pipe_base[VI_MAX_PIPE_NUM];
#define VI_DRV_PIPE_REG_CTX(pipeIndex, pstCtx)       pstCtx = (S_VI_PIPE_REGS_TYPE *)(reg_vi_pipe_base[pipeIndex]);
int VI_DRV_PIPE_Remap(void)
{
	
	reg_vi_pipe_base[0] = (unsigned int *)VI_PIPE_CSI_0_0_REG_BASE;
	
	reg_vi_pipe_base[1] = (unsigned int *)VI_PIPE_CSI_0_1_REG_BASE;
	
	reg_vi_pipe_base[2] = (unsigned int *)VI_PIPE_CSI_0_2_REG_BASE;
	
	reg_vi_pipe_base[3] = (unsigned int *)VI_PIPE_CSI_1_0_REG_BASE;
	
	reg_vi_pipe_base[4] = (unsigned int *)VI_PIPE_CSI_1_1_REG_BASE;

	reg_vi_pipe_base[5] = (unsigned int *)VI_PIPE_CSI_1_2_REG_BASE;

	reg_vi_pipe_base[6] = (unsigned int *)VI_PIPE_DVP_0_REG_BASE;

	reg_vi_pipe_base[7] = (unsigned int *)VI_PIPE_DVP_1_REG_BASE;

	for(int i = 0; i<8; i++)
	{
	//	printf("reg_vi_pipe_base[%d] = 0x%x\n",i,reg_vi_pipe_base[i]);
	}
	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetPipeCtl(int s8Index, VI_PIPE_CTRL_S *pstPipeCtl)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstPipeCtl);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_CTRL stData;
	stData.u32 = 0;
	stData.bits.win_mode_en = pstPipeCtl->win_mode_en;
	stData.bits.emb_en = pstPipeCtl->emb_en;
	stData.bits.hsync_vsync_out_en = pstPipeCtl->hsync_vsync_out_en;
	stData.bits.sensor_input_swap_en = pstPipeCtl->sensor_input_swap_en;

	stData.bits.sen_mipi_clk_pol = pstPipeCtl->sen_mipi_clk_pol;
	stData.bits.sen_mipi_vsync_pol = pstPipeCtl->sen_mipi_vsync_pol;
	stData.bits.sen_mipi_hsync_pol = pstPipeCtl->sen_mipi_hsync_pol;
	stData.bits.sen_mipi_field_pol = pstPipeCtl->sen_mipi_field_pol;

	stData.bits.isp_clk_pol = pstPipeCtl->isp_clk_pol;
	stData.bits.isp_vsync_pol = pstPipeCtl->isp_vsync_pol;
	stData.bits.isp_hsync_pol = pstPipeCtl->isp_hsync_pol;
	stData.bits.isp_field_pol = pstPipeCtl->isp_field_pol;

	stData.bits.sync_source_sel = pstPipeCtl->sync_source_sel;
	stData.bits.input_ch_sel = pstPipeCtl->input_ch_sel;
	stData.bits.ch_mode_sel = pstPipeCtl->ch_mode_sel;
	stData.bits.emb_enable = pstPipeCtl->emb_enable;

	stData.bits.emb_mode_sel = pstPipeCtl->emb_mode_sel;
	stData.bits.emb_ecc_mode_en = pstPipeCtl->emb_ecc_mode_en;
	stData.bits.sync_code_remove_en = pstPipeCtl->sync_code_remove_en;
	stData.bits.sync_code_ext_en = pstPipeCtl->sync_code_ext_en;
	
	//stData.u32 = 0x4e9140f;//0x06e9140f;
	VI_PIPE_DRV_SET_PipeCtrl(apstPipeReg, stData.u32);
	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetTimingCtl(int s8Index, VI_PIPE_TIMING_CTRL_S *pstTimingCtl)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstTimingCtl);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_TIMING_CTRL stData;	
	stData.u32 = 0;
	stData.bits.input_pixel_type = pstTimingCtl->input_pixel_type;
	stData.bits.input_yuv_format = pstTimingCtl->input_yuv_format;
	stData.bits.output_yuv_format = pstTimingCtl->output_yuv_format;
	stData.bits.yuv_order = pstTimingCtl->yuv_order;

	stData.bits.raw_pixel_width = pstTimingCtl->raw_pixel_width;
	stData.bits.data_out_timming_ctrl = pstTimingCtl->data_out_timming_ctrl;
	stData.bits.sync_mode = pstTimingCtl->sync_mode;
	stData.bits.sync_pulse_mode = pstTimingCtl->sync_pulse_mode;

	//stData.u32 = 0x00004120;//0x00004340;
	VI_PIPE_DRV_SET_PipeTimingCtrl(apstPipeReg, stData.u32);
	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetSyncWidthCtl(int s8Index, VI_PIPE_SYNC_WIDTH_S *pstSyncWidth)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstSyncWidth);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);
	
	U_VI_PIPE_SYNC_WIDTH stData;
	stData.u32 = 0;
	stData.bits.image_hsync_width = pstSyncWidth->image_hsync_width;
	stData.bits.image_vsync_width = pstSyncWidth->image_vsync_width;

	//stData.u32 = 0x00070007;
	VI_PIPE_DRV_SET_PipeSyncWidth(apstPipeReg, stData.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetImageAttr(int s8Index, VI_PIPE_IMAGE_ATTR_S *pstImgAttr)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstImgAttr);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_IMAGE_SIZE_TOTAL			stImageSizeTotal;
	stImageSizeTotal.u32 = 0; //0x08970464
	stImageSizeTotal.bits.image_h_size_total = pstImgAttr->stImageSizeTotal.image_h_size_total;
	stImageSizeTotal.bits.image_v_size_total = pstImgAttr->stImageSizeTotal.image_v_size_total;
	VI_PIPE_DRV_SET_PipeImageSizeTotal(apstPipeReg, stImageSizeTotal.u32);

	U_VI_PIPE_IMAGE_SIZE_ACTIVE			stImageSizeActive;
	stImageSizeActive.u32 = 0; //0x07810437
	stImageSizeActive.bits.image_h_size_active = pstImgAttr->stImageSizeActive.image_h_size_active;
	stImageSizeActive.bits.image_v_size_active = pstImgAttr->stImageSizeActive.image_v_size_active;
	VI_PIPE_DRV_SET_PipeImageSizeActive(apstPipeReg, stImageSizeActive.u32);	

	U_VI_PIPE_IMAGE_START 				stImageStart;	
	stImageStart.u32 = 0; //0x00003FFF
	stImageStart.bits.image_h_start = pstImgAttr->stImageStart.image_h_start;
	stImageStart.bits.image_v_start = pstImgAttr->stImageStart.image_v_start;
	VI_PIPE_DRV_SET_PipeImageStart(apstPipeReg, stImageStart.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetBuf(int s8Index,VI_PIPE_BUF_S *pstBuf)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstBuf);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_FRM_BASE_ADDR0_Y stFrameY0;
	stFrameY0.u32 = 0;
	stFrameY0.bits.image_frm_y_base_addr0 = pstBuf->y_base_addr0;//0x30000000;
	VI_PIPE_DRV_SET_PipeFrmBaseAddr0Y(apstPipeReg, stFrameY0.u32);
	
	U_VI_PIPE_FRM_BASE_ADDR1_Y stFrameY1;
	stFrameY1.u32 = 0;
	stFrameY1.bits.image_frm_y_base_addr1 = pstBuf->y_base_addr1;//0x30000000;
	VI_PIPE_DRV_SET_PipeFrmBaseAddr1Y(apstPipeReg, stFrameY1.u32);

	U_VI_PIPE_FRM_BASE_ADDR0_UV stFrameUV0;
	stFrameUV0.u32 = 0;
	stFrameUV0.bits.image_frm_uv_base_addr0 = pstBuf->uv_base_addr0;
	VI_PIPE_DRV_SET_PipeFrmBaseAddr0Uv(apstPipeReg, stFrameUV0.u32);

	U_VI_PIPE_FRM_BASE_ADDR1_UV stFrameUV1;	
	stFrameUV1.u32 = 0;
	stFrameUV1.bits.image_frm_uv_base_addr1 = pstBuf->uv_base_addr1;
	VI_PIPE_DRV_SET_PipeFrmBaseAddr1Uv(apstPipeReg, stFrameUV1.u32);

	U_VI_PIPE_LINE_STRIDE stFrameStride;
	stFrameStride.u32 = 0;
	stFrameStride.bits.image_y_line_stride = pstBuf->y_line_stride;//0xb40;
	stFrameStride.bits.image_uv_line_stride = pstBuf->uv_line_stride;
	VI_PIPE_DRV_SET_PipeLineStride(apstPipeReg, stFrameStride.u32);

	VI_PIPE_TPG_DMA_CTL_S *TpgDmaCtl = &pstBuf->stTpgDmaCtrl;
	U_VI_PIPE_TPG_DMA_CTL stTpgDmaCtl;
	stTpgDmaCtl.u32 = 0;
	stTpgDmaCtl.bits.dma_y_module_en = TpgDmaCtl->dma_y_module_en;//1;
	stTpgDmaCtl.bits.dma_uv_module_en = TpgDmaCtl->dma_uv_module_en;//0;
	stTpgDmaCtl.bits.dma_tpg_read_en = TpgDmaCtl->dma_tpg_read_en;//1;
	stTpgDmaCtl.bits.sync_out_en = TpgDmaCtl->sync_out_en;//1;
	stTpgDmaCtl.bits.sw_triger_en = TpgDmaCtl->sw_triger_en;//1;
	stTpgDmaCtl.bits.dma_wr_ch_err_dec_en = TpgDmaCtl->dma_wr_ch_err_dec_en;//1;
	stTpgDmaCtl.bits.dma_rd_ch_err_dec_en = TpgDmaCtl->dma_rd_ch_err_dec_en;//1;
	VI_PIPE_DRV_SET_PipeTpgDmaCtl(apstPipeReg, stTpgDmaCtl.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetTpgSize(int s8Index,VI_PIPE_TPG_IMAGE_ATTR_S *pstPipeTpgImage)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstPipeTpgImage);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	VI_PIPE_TPG_SIZE_TOTAL_S   *pstTpgSizeTotal = &pstPipeTpgImage->stTpgSizeTotal;
	U_VI_PIPE_TPG_SIZE_TOTAL stSizeTotal;
	stSizeTotal.u32 = 0;
	stSizeTotal.bits.tpg_vsize_total = pstTpgSizeTotal->tpg_vsize_total;//0x464;
	stSizeTotal.bits.tpg_hsize_total = pstTpgSizeTotal->tpg_hsize_total;//0x897;
	VI_PIPE_DRV_SET_PipeTpgSizeTotal(apstPipeReg, stSizeTotal.u32);

	U_VI_PIPE_TPG_SIZE_ACTIVE stSizeAct;
	VI_PIPE_TPG_SIZE_ACTIVE_S *TpgSizeActive = &pstPipeTpgImage->stTpgSizeActive;
	stSizeAct.u32 = 0;
	stSizeAct.bits.tpg_vsize_active = TpgSizeActive->tpg_vsize_active;//0x437;
	stSizeAct.bits.tpg_hsize_active = TpgSizeActive->tpg_hsize_active;//0x77f;
	VI_PIPE_DRV_SET_PipeTpgSizeActive(apstPipeReg, stSizeAct.u32);

	U_VI_PIPE_TPG_START stStart;
	VI_PIPE_TPG_START_S *TpgStart = &pstPipeTpgImage->stTpgStart;
	stStart.u32 = 0;
	stStart.bits.tpg_v_start = TpgStart->tpg_v_start;//0x2c;
	stStart.bits.tpg_h_start = TpgStart->tpg_h_start;//0x117;
	VI_PIPE_DRV_SET_PipeTpgStart(apstPipeReg, stStart.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetTpgBuf(int s8Index,VI_PIPE_TPG_BUF_S  *pstPipeTpgBuf)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstPipeTpgBuf);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_TPG_FRM_BASE_ADDR0_Y stYBuf0;
	stYBuf0.u32 = 0;
	stYBuf0.bits.tpg_y_frm_base_addr0 = pstPipeTpgBuf->tpg_y_base_addr0;//0x30000000;
	VI_PIPE_DRV_SET_PipeTpgFrmBaseAddr0Y(apstPipeReg, stYBuf0.u32);
	
	U_VI_PIPE_TPG_FRM_BASE_ADDR1_Y stYBuf1;
	stYBuf1.u32 = 0;
	stYBuf1.bits.tpg_y_frm_base_addr1 = pstPipeTpgBuf->tpg_y_base_addr1;//0x30000000;
	VI_PIPE_DRV_SET_PipeTpgFrmBaseAddr1Y(apstPipeReg, stYBuf1.u32);

	U_VI_PIPE_TPG_LINE_STRIDE stLineStride;
	stLineStride.u32 = 0;
	stLineStride.bits.tpg_y_line_stride = pstPipeTpgBuf->tpg_y_line_stride;//0xb40;
	VI_PIPE_DRV_SET_PipeTpgLineStride(apstPipeReg, stLineStride.u32);
	

	VI_PIPE_DMA_MODE_S *DmaCtrl = &pstPipeTpgBuf->stPipeDmaMode;
	U_VI_PIPE_DMA_MODE stDmaCtrl;
	stDmaCtrl.u32 = 0;
	stDmaCtrl.bits.dma_int_line_num = DmaCtrl->dma_int_line_num;
	stDmaCtrl.bits.dma_raw_blen = DmaCtrl->dma_raw_blen;
	stDmaCtrl.bits.dma_raw_outstand = DmaCtrl->dma_raw_outstand;
	stDmaCtrl.bits.dma_uv_blen = DmaCtrl->dma_uv_blen;
	stDmaCtrl.bits.dma_uv_outstand = DmaCtrl->dma_uv_outstand;
	stDmaCtrl.bits.dma_y_blen = DmaCtrl->dma_y_blen;
	stDmaCtrl.bits.dma_y_outstand = DmaCtrl->dma_y_outstand;//8;
	stDmaCtrl.bits.dma_y_uv_out_swap = DmaCtrl->dma_y_outstand;
	VI_PIPE_DRV_SET_PipeDmaCtrl(apstPipeReg, stDmaCtrl.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetTpgAttr(int s8Index,VI_PIPE_TPG_S *pstTpg)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstTpg);

	VI_PIPE_BUF_S *pstBuf = &pstTpg->stPipeBuf;
	VI_DRV_PIPE_SetBuf(s8Index,pstBuf);

	VI_PIPE_TPG_IMAGE_ATTR_S *pstPipeTpgImage = &pstTpg->stPipeTpgImage;
	VI_DRV_PIPE_SetTpgSize(s8Index,pstPipeTpgImage);
 
	VI_PIPE_TPG_BUF_S  *stPipeTpgBuf = &pstTpg->stPipeTpgBuf;
	VI_DRV_PIPE_SetTpgBuf(s8Index,stPipeTpgBuf);
	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetIspTpg(int s8Index, VI_PIPE_TPG_CTL_S *stPipeTpgCtl)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(stPipeTpgCtl);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);    

	U_VI_PIPE_TPG_CTL stTpgCtl;
	stTpgCtl.u32 = 0;
	stTpgCtl.bits.tpg_en = stPipeTpgCtl->tpg_en;//1;
	stTpgCtl.bits.tpg_frame_ratio_mode = stPipeTpgCtl->tpg_frame_ratio_mode;//0;
	stTpgCtl.bits.tpg_sync_timing_gen_mode = stPipeTpgCtl->tpg_sync_timing_gen_mode;//0;
	stTpgCtl.bits.tpg_frame_ratio_fast_slow = stPipeTpgCtl->tpg_frame_ratio_fast_slow;//1;
	VI_PIPE_DRV_SET_PipeTpgCtl(apstPipeReg, stTpgCtl.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetTofTpg(int s8Index,VI_PIPE_TPG_TOF_S *stPipeTpgTof)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(stPipeTpgTof);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_TPG_TOF stTpgTof;
	stTpgTof.u32 = 0;
	stTpgTof.bits.tof_mode_enable = stPipeTpgTof->tof_mode_enable;
	stTpgTof.bits.vi_pipe_tpg_tof_frm_num = stPipeTpgTof->vi_pipe_tpg_tof_frm_num;
	stTpgTof.bits.vi_pipe_tpg_tof_frm_stride = stPipeTpgTof->vi_pipe_tpg_tof_frm_stride;
	VI_PIPE_DRV_SET_PipeTpgTof(apstPipeReg,stTpgTof.u32);

	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetCfgDone(int s8Index,VI_PIPE_CONFIG_DONE_S *pstCfgDone)
{
	VI_CHECK_PIPE(s8Index);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_CONFIG_DONE stData;
	stData.u32 = VI_PIPE_DRV_GET_PipeConfigDone(apstPipeReg);
	stData.bits.int_pol = pstCfgDone->int_pol;//1;
	stData.bits.pipe_config_done = pstCfgDone->pipe_config_done;//1;
	VI_PIPE_DRV_SET_PipeConfigDone(apstPipeReg, stData.u32);
	
	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SET_IntPol(int s8Index,VI_PIPE_CONFIG_DONE_S *pstCfgDone)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstCfgDone);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_CONFIG_DONE stData;
	stData.u32 = VI_PIPE_DRV_GET_PipeConfigDone(apstPipeReg);
	stData.bits.int_pol = pstCfgDone->int_pol;//1;
	VI_PIPE_DRV_SET_PipeConfigDone(apstPipeReg, stData.u32);
	return 0;
}
/*
*
*/
static int VI_PIPE_DRV_SET_RegWP(int s8Index,VI_PIPE_CONFIG_DONE_S *pstCfgDone)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstCfgDone);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_CONFIG_DONE stData;
	stData.u32 = VI_PIPE_DRV_GET_PipeConfigDone(apstPipeReg);
	stData.bits.sens_reg_wr_protect = pstCfgDone->sens_reg_wr_protect;
	VI_PIPE_DRV_SET_PipeConfigDone(apstPipeReg, stData.u32);
	return 0;
}
/*
*
*/
static int VI_DRV_PIPE_SetInt(int s8Index, BOOL bIntrPolHigh, VI_PIPE_INT_CTL_S *pstIntCtl)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstIntCtl);
	
	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	unsigned int intPol;
	intPol = 0;
	if(TRUE == bIntrPolHigh)
	{
		intPol = 1;
	}
	VI_PIPE_DRV_SET_IntPol(apstPipeReg, intPol);

	U_VI_PIPE_INT_CTL stIntCtl;
	stIntCtl.u32 = 0xffffffff;
	
	stIntCtl.bits.dma_raw_rd_ch_err_frame_end_mask = pstIntCtl->dma_raw_rd_ch_err_frame_end_mask;
	stIntCtl.bits.dma_raw_rd_ch_err_immediate_mask = pstIntCtl->dma_raw_rd_ch_err_immediate_mask;
	stIntCtl.bits.dma_raw_rd_ch_frame_end_mask = pstIntCtl->dma_raw_rd_ch_frame_end_mask;
	stIntCtl.bits.dma_raw_rd_ch_line_base_mask = pstIntCtl->dma_raw_rd_ch_line_base_mask;
	stIntCtl.bits.dma_uv_wr_ch_err_frame_end_mask = pstIntCtl->dma_uv_wr_ch_err_frame_end_mask;
	stIntCtl.bits.dma_uv_wr_ch_err_immediate_mask = pstIntCtl->dma_uv_wr_ch_err_immediate_int;
	stIntCtl.bits.dma_uv_wr_ch_frame_end_mask = pstIntCtl->dma_uv_wr_ch_frame_end_mask;
	stIntCtl.bits.dma_uv_wr_ch_line_base_mask = pstIntCtl->dma_uv_wr_ch_line_base_mask;
	stIntCtl.bits.dma_y_wr_ch_err_frame_end_mask = pstIntCtl->dma_y_wr_ch_err_frame_end_mask;
	stIntCtl.bits.dma_y_wr_ch_err_immediate_int = pstIntCtl->dma_y_wr_ch_err_immediate_int;
	stIntCtl.bits.dma_y_wr_ch_line_base_mask = pstIntCtl->dma_y_wr_ch_line_base_mask;
	stIntCtl.bits.dma_y_wr_frame_end_mask = pstIntCtl->dma_y_wr_frame_end_mask;
	stIntCtl.bits.emb_ctl_frame_end_mask = pstIntCtl->emb_ctl_frame_end_mask;
	stIntCtl.bits.emb_ctl_time_out_mask = pstIntCtl->emb_ctl_time_out_mask;
	stIntCtl.bits.tpg_ctl_frame_end_mask = pstIntCtl->tpg_ctl_frame_end_mask;
	stIntCtl.bits.win_ctl_frame_end_mask = pstIntCtl->win_ctl_frame_end_mask;
	VI_PIPE_DRV_SET_PipeIntCtl(apstPipeReg, stIntCtl.u32);
	
	return 0;
}
/*
*
*/
int VI_DRV_PIPE_InitPipeInterrupt(int s8Index, BOOL bIntrPolHigh,unsigned int uIntrCtlData)
{
	VI_CHECK_PIPE(s8Index);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;

	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);
	//printf( "0x%x,apstPipeReg[%d] = 0x%x\n",reg_vi_pipe_base[s8Index],s8Index,apstPipeReg);

	unsigned int intPol;
	U_VI_PIPE_INT_CTL stIntCtl;
	stIntCtl.u32 = 0xffff0000;
	VI_PIPE_DRV_SET_PipeIntCtl(apstPipeReg, stIntCtl.u32);

	intPol = 0;
	if(TRUE == bIntrPolHigh)
	{
		intPol = 1;
	}
	VI_PIPE_DRV_SET_IntPol(apstPipeReg, intPol);

	stIntCtl.u32 = uIntrCtlData;
	VI_PIPE_DRV_SET_PipeIntCtl(apstPipeReg, stIntCtl.u32);
	
	return 0;
}
/*
*
*/
unsigned int VI_DRV_PIPE_GetPipeIntSts(int s8Index)
{
	VI_CHECK_PIPE(s8Index);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	U_VI_PIPE_INT_CTL stIntCtl;
	stIntCtl.u32 = VI_PIPE_DRV_GET_PipeIntCtl(apstPipeReg);
	
	return stIntCtl.u32;
}
/*
*
*/
int VI_DRV_PIPE_SetPipe(int s8Index,VI_PIPE_ATTR_S *pstVipipe)
{
	VI_CHECK_PIPE(s8Index);
	VI_CHECK_POINTER(pstVipipe);
	
	VI_PIPE_CTRL_S *pstPipeCtl = &pstVipipe->stPipeCtl;
	VI_DRV_PIPE_SetPipeCtl(s8Index, pstPipeCtl);

	VI_PIPE_TIMING_CTRL_S *pstTimingCtl = &pstVipipe->stTimingCtl;
	VI_DRV_PIPE_SetTimingCtl(s8Index,pstTimingCtl);

	VI_PIPE_SYNC_WIDTH_S *pstSyncWidth = &pstVipipe->stPipeSync;
	VI_DRV_PIPE_SetSyncWidthCtl(s8Index, pstSyncWidth);
	
	VI_PIPE_IMAGE_ATTR_S *pstImgAttr = &pstVipipe->stPipeImage;
	VI_DRV_PIPE_SetImageAttr(s8Index,pstImgAttr);

	VI_PIPE_TPG_S *pstTpg = &pstVipipe->stPipeTpg;
	VI_DRV_PIPE_SetTpgAttr(s8Index,pstTpg);
	//
	VI_PIPE_TPG_CTL_S *pstPipeTpgCtl = &pstVipipe->stPipeTpgCtl;
	VI_DRV_PIPE_SetIspTpg(s8Index,pstPipeTpgCtl);
	//
	VI_PIPE_TPG_TOF_S *pstPipeTpgTof = &pstVipipe->stPipeTpgTof;
	VI_DRV_PIPE_SetTofTpg(s8Index,pstPipeTpgTof);
	//
	VI_PIPE_INT_CTL_S *pstIntCtl = &pstVipipe->stIntCtl;
	VI_DRV_PIPE_SetInt(s8Index,TRUE,pstIntCtl);
	//
	VI_PIPE_CONFIG_DONE_S *pstCfgDone = &pstVipipe->stConfigDone;
	VI_DRV_PIPE_SetCfgDone(s8Index,pstCfgDone);

	return 0;
}
/*
*debug
*/
unsigned int VI_DRV_PIPE_GetPipeRegsVal(int s8Index)
{
	VI_CHECK_PIPE(s8Index);

	S_VI_PIPE_REGS_TYPE *apstPipeReg = NULL;
	VI_DRV_PIPE_REG_CTX(s8Index, apstPipeReg);

	VI_PIPE_DRV_GET_PipeRegsVal(apstPipeReg);

	return 0;
}

#if 0
/*
*
*/
int VI_DRV_PIPE_SetCtl(int s8Index,VI_PIPE_CONFIG_S *vipipeInfo)
{
	VI_PIPE_CTRL_S pstPipeCtl;
	VI_PIPE_TIMING_CTRL_S pstTimingCtl;
	VI_PIPE_SYNC_WIDTH_S pstSyncWidth;
	VI_PIPE_IMAGE_ATTR_S pstImgAttr;
	VI_PIPE_TPG_S pstTpg;

	VI_PIPE_CTRL_INFO *ctrlInfo  = &vipipeInfo->ctrlInfo;
	pstPipeCtl.ch_mode_sel = ctrlInfo->ch_mode_sel;
	pstPipeCtl.emb_ecc_mode_en = ctrlInfo->emb_ecc_mode_en;
	pstPipeCtl.emb_en = ctrlInfo->emb_en;
	pstPipeCtl.emb_enable = ctrlInfo->emb_enable;
	pstPipeCtl.emb_mode_sel = ctrlInfo->emb_mode_sel;
	pstPipeCtl.hsync_vsync_out_en = ctrlInfo->hsync_vsync_out_en;
	pstPipeCtl.input_ch_sel = ctrlInfo->input_ch_sel;
	pstPipeCtl.isp_clk_pol = ctrlInfo->isp_clk_pol;//1;
	pstPipeCtl.isp_field_pol =ctrlInfo->isp_field_pol;//1;
	pstPipeCtl.isp_hsync_pol =ctrlInfo->isp_hsync_pol;//1;
	pstPipeCtl.isp_vsync_pol =ctrlInfo->isp_vsync_pol;//1;
	pstPipeCtl.sen_mipi_clk_pol =ctrlInfo->sen_mipi_clk_pol;//1;
	pstPipeCtl.sen_mipi_field_pol  =ctrlInfo->sen_mipi_field_pol;//1;
	pstPipeCtl.sen_mipi_hsync_pol  =ctrlInfo->sen_mipi_hsync_pol;//1;
	pstPipeCtl.sen_mipi_vsync_pol  =ctrlInfo->sen_mipi_vsync_pol;//1;
	pstPipeCtl.sensor_input_swap_en  = ctrlInfo->sensor_input_swap_en;
	pstPipeCtl.sync_code_ext_en  = ctrlInfo->sync_code_ext_en;
	pstPipeCtl.sync_code_remove_en  = ctrlInfo->sync_code_remove_en;
	pstPipeCtl.sync_source_sel  = ctrlInfo->sync_source_sel;
	pstPipeCtl.win_mode_en  = ctrlInfo->win_mode_en;
	VI_DRV_PIPE_SetPipeCtl(s8Index, &pstPipeCtl);

	VI_PIPE_TIMING_CTRL_INFO *timingInfo = &vipipeInfo->timingInfo;
	pstTimingCtl.data_out_timming_ctrl = timingInfo->data_out_timming_ctrl;
	pstTimingCtl.emb_timeout_set = timingInfo->emb_timeout_set;
	pstTimingCtl.input_pixel_type = timingInfo->input_pixel_type;
	pstTimingCtl.input_yuv_format = timingInfo->input_yuv_format;
	pstTimingCtl.output_yuv_format = timingInfo->output_yuv_format;
	pstTimingCtl.raw_pixel_width = timingInfo->raw_pixel_width;
	pstTimingCtl.sync_mode = timingInfo->sync_mode;
	pstTimingCtl.sync_pulse_mode = timingInfo->sync_pulse_mode;
	pstTimingCtl.yuv_order = timingInfo->yuv_order;
	VI_DRV_PIPE_SetTimingCtl(s8Index,&pstTimingCtl);

    VI_PIPE_SYNC_WIDTH_INFO  *syncwidthInfo = &vipipeInfo->syncwidthInfo;
	pstSyncWidth.image_hsync_width = syncwidthInfo->image_hsync_width ;//7; //8 -1
	pstSyncWidth.image_vsync_width = syncwidthInfo->image_vsync_width;//7; //8 -1
	VI_DRV_PIPE_SetSyncWidthCtl(s8Index,&pstSyncWidth);

	W_IMAGE_SZIE_INFO *imageSizeInfo = &vipipeInfo->imageSizeInfo;
	pstImgAttr.stImageSizeTotal.image_h_size_total = imageSizeInfo->vi_pipe_tpg_w_size_total.Width;
	pstImgAttr.stImageSizeActive.image_h_size_active =imageSizeInfo->vi_pipe_tpg_w_size_active.Height;
	pstImgAttr.stImageSizeActive.image_v_size_active =imageSizeInfo->vi_pipe_tpg_w_size_active.Height;
	pstImgAttr.stImageStart.image_h_start =imageSizeInfo->vi_pipe_tpg_w_size_active.Width_st;
	pstImgAttr.stImageStart.image_v_start =imageSizeInfo->vi_pipe_tpg_w_size_active.Height_st;
	VI_DRV_PIPE_SetImageAttr(s8Index,&pstImgAttr);

	TPG_INFO   *TpgInfo = &vipipeInfo->TpgInfo;
	pstTpg.stPipeTpgCtl.tpg_en = TpgInfo->vi_pipe_tpg_en;
	if(1 == TpgInfo->vi_pipe_tpg_en)
	{
		pstTpg.stPipeTpgCtl.tpg_frame_ratio_fast_slow = TpgInfo->vi_pipe_tpg_frm_ratio;
		pstTpg.stPipeTpgCtl.tpg_frame_ratio_mode = TpgInfo->vi_pipe_tpg_frm_ratio_mode;
		pstTpg.stPipeTpgCtl.tpg_sync_timing_gen_mode = SENSOR_TRG_TPG_TIMING;
		if( 1 == TpgInfo->vi_pipe_tpg_sw_triger_en)
		{
			pstTpg.stPipeTpgCtl.tpg_sync_timing_gen_mode = SW_TRG_TPG_TIMING;
		}
		//
		pstTpg.stPipeTpgDmaCtl.dma_y_module_en = TpgInfo->vi_pipe_tpg_y_w_en;
		pstTpg.stPipeTpgDmaCtl.dma_uv_module_en = TpgInfo->vi_pipe_tpg_uv_w_en;
		pstTpg.stPipeTpgDmaCtl.dma_tpg_read_en = TpgInfo->vi_pipe_tpg_raw_r_en;
		pstTpg.stPipeTpgDmaCtl.sw_triger_en = TpgInfo->vi_pipe_tpg_sw_triger_en;
		pstTpg.stPipeTpgDmaCtl.sync_out_en = TpgInfo->sync_out_en;//1;
		pstTpg.stPipeTpgDmaCtl.dma_wr_ch_err_dec_en =TpgInfo->dma_wr_ch_err_dec_en;//1;
		pstTpg.stPipeTpgDmaCtl.dma_rd_ch_err_dec_en =TpgInfo->dma_rd_ch_err_dec_en;//1;
		//
		pstTpg.stPipeFrmBaseAddrY0.y_addr_base = TpgInfo->vi_pipe_w_addr_y;
		pstTpg.stPipeFrmBaseAddrY1.y_addr_base = TpgInfo->vi_pipe_w_addr_y;
		pstTpg.stPipeFrmBaseAddrUV0.uv_addr_base = TpgInfo->vi_pipe_w_addr_uv;
		pstTpg.stPipeFrmBaseAddrUV1.uv_addr_base = TpgInfo->vi_pipe_w_addr_uv;
		pstTpg.stPipeFrmLineStride.y_line_stride = TpgInfo->vi_pipe_w_addr_stride;
		pstTpg.stPipeFrmLineStride.uv_line_stride = TpgInfo->vi_pipe_w_addr_stride;
		//
		pstTpg.stPipeTpgSizeTotal.tpg_hsize_total = TpgInfo->vi_pipe_tpg_r_size_total.Width;
		pstTpg.stPipeTpgSizeTotal.tpg_vsize_total = TpgInfo->vi_pipe_tpg_r_size_total.Height;
		pstTpg.stPipeTpgSizeActive.tpg_hsize_active = TpgInfo->vi_pipe_tpg_r_size_active.Width;
		pstTpg.stPipeTpgSizeActive.tpg_vsize_active = TpgInfo->vi_pipe_tpg_r_size_active.Height;
		pstTpg.stPipeTpgStart.tpg_h_start = TpgInfo->vi_pipe_tpg_r_size_active.Width_st;
		pstTpg.stPipeTpgStart.tpg_v_start = TpgInfo->vi_pipe_tpg_r_size_active.Height_st;
		//
		pstTpg.stPipeTpgFrmBaseAddrY0.tpg_y_frm_base_addr = TpgInfo->vi_pipe_r_addr_y;
		pstTpg.stPipeTpgFrmBaseAddrY1.tpg_y_frm_base_addr = TpgInfo->vi_pipe_r_addr_y;
		pstTpg.stPipeTpgLineStride.tpg_y_line_stride = TpgInfo->vi_pipe_r_addr_stride;
		//
		VI_PIPE_DMA_CTRL_INFO *dmaCtrlInfo = &vipipeInfo->dmaCtrlInfo;
		pstTpg.stPipeDmaCtrl.dma_int_line_num = dmaCtrlInfo->dma_int_line_num;//4; //?
		pstTpg.stPipeDmaCtrl.dma_raw_blen = dmaCtrlInfo->dma_raw_blen;//8;
		pstTpg.stPipeDmaCtrl.dma_raw_outstand = dmaCtrlInfo->dma_raw_outstand;//8;
		pstTpg.stPipeDmaCtrl.dma_uv_blen = dmaCtrlInfo->dma_uv_blen;//8;
		pstTpg.stPipeDmaCtrl.dma_uv_outstand = dmaCtrlInfo->dma_uv_outstand;//8;
		pstTpg.stPipeDmaCtrl.dma_y_blen = dmaCtrlInfo->dma_y_blen;//8;
		pstTpg.stPipeDmaCtrl.dma_y_outstand = dmaCtrlInfo->dma_y_outstand;//8;
		pstTpg.stPipeDmaCtrl.dma_y_uv_out_swap = dmaCtrlInfo->dma_y_uv_out_swap;
		//
		pstTpg.stPipeTpgTof.tof_mode_enable = TpgInfo->tof_mode_enable;
		if( 1 == TpgInfo->tof_mode_enable)
		{
			pstTpg.stPipeTpgTof.vi_pipe_tpg_tof_frm_num = TpgInfo->vi_pipe_tpg_tof_frm_num;
			pstTpg.stPipeTpgTof.vi_pipe_tpg_tof_frm_stride = TpgInfo->vi_pipe_tpg_tof_frm_stride;
		}
	}
	VI_DRV_PIPE_SetTpgAttr(s8Index,&pstTpg);

	VI_DRV_PIPE_SetConfigDoneCtl(s8Index);
	return 0;
}
#endif

