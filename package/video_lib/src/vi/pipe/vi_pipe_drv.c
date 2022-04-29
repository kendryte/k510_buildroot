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
 * vi_pipe_drv.c
 *
 * CANAAN ISP - vi pipe module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#include "isp_com.h"
#include "vi/vi.h"
#include "vi/vi_com.h"
#include "vi/pipe/vi_pipe_drv.h"
#include "vi/pipe/vi_pipe_reg.h"

unsigned int reg_vi_pipe_base[] = {
    //VI_PIPE_CSI_0_0_REG_BASE,
    //VI_PIPE_CSI_0_1_REG_BASE,
    //VI_PIPE_CSI_0_2_REG_BASE,
    //VI_PIPE_CSI_1_0_REG_BASE,
    //VI_PIPE_CSI_1_1_REG_BASE,
    //VI_PIPE_CSI_1_2_REG_BASE,
    //VI_PIPE_DVP_0_REG_BASE,
    //VI_PIPE_DVP_1_REG_BASE,
	ISP_IOMEM_VI_PIPE_CSI00,
	ISP_IOMEM_VI_PIPE_CSI01,
	ISP_IOMEM_VI_PIPE_CSI02,
	ISP_IOMEM_VI_PIPE_CSI10,
	ISP_IOMEM_VI_PIPE_CSI11,
	ISP_IOMEM_VI_PIPE_CSI12,
	ISP_IOMEM_VI_PIPE_DVP0,	
	ISP_IOMEM_VI_PIPE_DVP1,	 
};
/*
*
*/
 int VI_DRV_PIPE_SetPipeCtl(struct isp_device *isp,int s8Index, VI_PIPE_CTRL_S *pstPipeCtl)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstPipeCtl);

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
	
	//stData.u32 = 0x4ff1000;//0x06e9140f;
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_CTRL);
	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetTimingCtl(struct isp_device *isp,int s8Index, VI_PIPE_TIMING_CTRL_S *pstTimingCtl)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstTimingCtl);

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
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TIMING_CTRL);
	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetSyncWidthCtl(struct isp_device *isp,int s8Index, VI_PIPE_SYNC_WIDTH_S *pstSyncWidth)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstSyncWidth);
	
	U_VI_PIPE_SYNC_WIDTH stData;
	stData.u32 = 0;
	stData.bits.image_hsync_width = pstSyncWidth->image_hsync_width;
	stData.bits.image_vsync_width = pstSyncWidth->image_vsync_width;

	//stData.u32 = 0x00070007;
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_SYNC_WIDTH);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetImageAttr(struct isp_device *isp,int s8Index, VI_PIPE_IMAGE_ATTR_S *pstImgAttr)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstImgAttr);	

	U_VI_PIPE_IMAGE_SIZE_TOTAL			stImageSizeTotal;
	stImageSizeTotal.u32 = 0; //0x08970464
	stImageSizeTotal.bits.image_h_size_total = pstImgAttr->stImageSizeTotal.image_h_size_total;
	stImageSizeTotal.bits.image_v_size_total = pstImgAttr->stImageSizeTotal.image_v_size_total;
	isp_reg_writel(isp,stImageSizeTotal.u32,reg_vi_pipe_base[s8Index],VI_PIPE_IMAGE_SIZE_TOTAL);

	U_VI_PIPE_IMAGE_SIZE_ACTIVE			stImageSizeActive;
	stImageSizeActive.u32 = 0; //0x07810437
	stImageSizeActive.bits.image_h_size_active = pstImgAttr->stImageSizeActive.image_h_size_active;
	stImageSizeActive.bits.image_v_size_active = pstImgAttr->stImageSizeActive.image_v_size_active;
	isp_reg_writel(isp,stImageSizeActive.u32,reg_vi_pipe_base[s8Index],VI_PIPE_IMAGE_SIZE_ACTIVE);	

	U_VI_PIPE_IMAGE_START 				stImageStart;	
	stImageStart.u32 = 0; //0x00003FFF
	stImageStart.bits.image_h_start = pstImgAttr->stImageStart.image_h_start;
	stImageStart.bits.image_v_start = pstImgAttr->stImageStart.image_v_start;
	isp_reg_writel(isp,stImageStart.u32,reg_vi_pipe_base[s8Index],VI_PIPE_IMAGE_START);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetBuf(struct isp_device *isp,int s8Index,VI_PIPE_BUF_S *pstBuf)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstBuf);	

	U_VI_PIPE_FRM_BASE_ADDR0_Y stFrameY0;
	stFrameY0.u32 = 0;
	stFrameY0.bits.image_frm_y_base_addr0 = pstBuf->y_base_addr0;//0x30000000;
	isp_reg_writel(isp,stFrameY0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_FRM_BASE_ADDR0_Y);
	
	U_VI_PIPE_FRM_BASE_ADDR1_Y stFrameY1;
	stFrameY1.u32 = 0;
	stFrameY1.bits.image_frm_y_base_addr1 = pstBuf->y_base_addr1;//0x30000000;
	isp_reg_writel(isp,stFrameY0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_FRM_BASE_ADDR1_Y);

	U_VI_PIPE_FRM_BASE_ADDR0_UV stFrameUV0;
	stFrameUV0.u32 = 0;
	stFrameUV0.bits.image_frm_uv_base_addr0 = pstBuf->uv_base_addr0;
	isp_reg_writel(isp,stFrameUV0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_FRM_BASE_ADDR0_UV);

	U_VI_PIPE_FRM_BASE_ADDR1_UV stFrameUV1;	
	stFrameUV1.u32 = 0;
	stFrameUV1.bits.image_frm_uv_base_addr1 = pstBuf->uv_base_addr1;
	isp_reg_writel(isp,stFrameUV0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_FRM_BASE_ADDR1_UV);

	U_VI_PIPE_LINE_STRIDE stFrameStride;
	stFrameStride.u32 = 0;
	stFrameStride.bits.image_y_line_stride = pstBuf->y_line_stride;//0xb40;
	stFrameStride.bits.image_uv_line_stride = pstBuf->uv_line_stride;
	isp_reg_writel(isp,stFrameStride.u32,reg_vi_pipe_base[s8Index],VI_PIPE_LINE_STRIDE);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetTpgDmaCtl(struct isp_device *isp,int s8Index,VI_PIPE_TPG_DMA_CTL_S *TpgDmaCtl)
{
    ISP_CHECK_POINTER(isp);
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(TpgDmaCtl);

	U_VI_PIPE_TPG_DMA_CTL stTpgDmaCtl;
	stTpgDmaCtl.u32 = 0;
	stTpgDmaCtl.bits.dma_y_module_en = TpgDmaCtl->dma_y_module_en;//1;
	stTpgDmaCtl.bits.dma_uv_module_en = TpgDmaCtl->dma_uv_module_en;//0;
	stTpgDmaCtl.bits.dma_tpg_read_en = TpgDmaCtl->dma_tpg_read_en;//1;
	stTpgDmaCtl.bits.sync_out_en = TpgDmaCtl->sync_out_en;//1;
	stTpgDmaCtl.bits.sw_triger_en = TpgDmaCtl->sw_triger_en;//1;
	stTpgDmaCtl.bits.dma_wr_ch_err_dec_en = TpgDmaCtl->dma_wr_ch_err_dec_en;//1;
	stTpgDmaCtl.bits.dma_rd_ch_err_dec_en = TpgDmaCtl->dma_rd_ch_err_dec_en;//1;
	isp_reg_writel(isp,stTpgDmaCtl.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_DMA_CTL);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetTpgSize(struct isp_device *isp,int s8Index,VI_PIPE_TPG_IMAGE_ATTR_S *pstPipeTpgImage)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstPipeTpgImage);
	

	VI_PIPE_TPG_SIZE_TOTAL_S   *pstTpgSizeTotal = &pstPipeTpgImage->stTpgSizeTotal;
	U_VI_PIPE_TPG_SIZE_TOTAL stSizeTotal;
	stSizeTotal.u32 = 0;
	stSizeTotal.bits.tpg_vsize_total = pstTpgSizeTotal->tpg_vsize_total;//0x464;
	stSizeTotal.bits.tpg_hsize_total = pstTpgSizeTotal->tpg_hsize_total;//0x897;
	isp_reg_writel(isp,stSizeTotal.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_SIZE_TOTAL);

	U_VI_PIPE_TPG_SIZE_ACTIVE stSizeAct;
	VI_PIPE_TPG_SIZE_ACTIVE_S *TpgSizeActive = &pstPipeTpgImage->stTpgSizeActive;
	stSizeAct.u32 = 0;
	stSizeAct.bits.tpg_vsize_active = TpgSizeActive->tpg_vsize_active;//0x437;
	stSizeAct.bits.tpg_hsize_active = TpgSizeActive->tpg_hsize_active;//0x77f;
	isp_reg_writel(isp,stSizeAct.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_SIZE_ACTIVE);

	U_VI_PIPE_TPG_START stStart;
	VI_PIPE_TPG_START_S *TpgStart = &pstPipeTpgImage->stTpgStart;
	stStart.u32 = 0;
	stStart.bits.tpg_v_start = TpgStart->tpg_v_start;//0x2c;
	stStart.bits.tpg_h_start = TpgStart->tpg_h_start;//0x117;
	isp_reg_writel(isp,stStart.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_START);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetTpgBuf(struct isp_device *isp,int s8Index,VI_PIPE_TPG_BUF_S  *pstPipeTpgBuf)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstPipeTpgBuf);


	U_VI_PIPE_TPG_FRM_BASE_ADDR0_Y stYBuf0;
	stYBuf0.u32 = 0;
	stYBuf0.bits.tpg_y_frm_base_addr0 = pstPipeTpgBuf->tpg_y_base_addr0;//0x30000000;
	isp_reg_writel(isp,stYBuf0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_FRM_BASE_ADDR0_Y);
	
	U_VI_PIPE_TPG_FRM_BASE_ADDR1_Y stYBuf1;
	stYBuf1.u32 = 0;
	stYBuf1.bits.tpg_y_frm_base_addr1 = pstPipeTpgBuf->tpg_y_base_addr1;//0x30000000;
	isp_reg_writel(isp,stYBuf0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_FRM_BASE_ADDR1_Y);

	U_VI_PIPE_TPG_LINE_STRIDE stLineStride;
	stLineStride.u32 = 0;
	stLineStride.bits.tpg_y_line_stride = pstPipeTpgBuf->tpg_y_line_stride;//0xb40;
	isp_reg_writel(isp,stLineStride.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_LINE_STRIDE);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetDmaCtrl(struct isp_device *isp,int s8Index,VI_PIPE_DMA_MODE_S *DmaCtrl)
{
    ISP_CHECK_POINTER(isp);
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(DmaCtrl);

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
	isp_reg_writel(isp,stDmaCtrl.u32,reg_vi_pipe_base[s8Index],VI_PIPE_DMA_MODE);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetTpgAttr(struct isp_device *isp,int s8Index,VI_PIPE_TPG_S *pstTpg)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstTpg);

	VI_PIPE_BUF_S *pstBuf = &pstTpg->stPipeBuf;
	VI_DRV_PIPE_SetBuf(isp,s8Index,pstBuf);

	VI_PIPE_TPG_IMAGE_ATTR_S *pstPipeTpgImage = &pstTpg->stPipeTpgImage;
	VI_DRV_PIPE_SetTpgSize(isp,s8Index,pstPipeTpgImage);
 
	VI_PIPE_TPG_BUF_S  *stPipeTpgBuf = &pstTpg->stPipeTpgBuf;
	VI_DRV_PIPE_SetTpgBuf(isp,s8Index,stPipeTpgBuf);
	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetIspTpg(struct isp_device *isp,int s8Index, VI_PIPE_TPG_CTL_S *stPipeTpgCtl)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stPipeTpgCtl);	    

	U_VI_PIPE_TPG_CTL stTpgCtl;
	stTpgCtl.u32 = 0;
	stTpgCtl.bits.tpg_en = stPipeTpgCtl->tpg_en;//1;
	stTpgCtl.bits.tpg_frame_ratio_mode = stPipeTpgCtl->tpg_frame_ratio_mode;//0;
	stTpgCtl.bits.tpg_sync_timing_gen_mode = stPipeTpgCtl->tpg_sync_timing_gen_mode;//0;
	stTpgCtl.bits.tpg_frame_ratio_fast_slow = stPipeTpgCtl->tpg_frame_ratio_fast_slow;//1;
	isp_reg_writel(isp,stTpgCtl.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_CTL);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetTofTpg(struct isp_device *isp,int s8Index,VI_PIPE_TPG_TOF_S *stPipeTpgTof)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(stPipeTpgTof);

	U_VI_PIPE_TPG_TOF stTpgTof;
	stTpgTof.u32 = 0;
	stTpgTof.bits.tof_mode_enable = stPipeTpgTof->tof_mode_enable;
	stTpgTof.bits.vi_pipe_tpg_tof_frm_num = stPipeTpgTof->vi_pipe_tpg_tof_frm_num;
	stTpgTof.bits.vi_pipe_tpg_tof_frm_stride = stPipeTpgTof->vi_pipe_tpg_tof_frm_stride;
	isp_reg_writel(isp,stTpgTof.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_TOF);

	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetCfgDone(struct isp_device *isp,int s8Index,VI_PIPE_CONFIG_DONE_S *pstCfgDone)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstCfgDone);	

	U_VI_PIPE_CONFIG_DONE stData;
	stData.u32 = isp_reg_readl(isp,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	stData.bits.int_pol = pstCfgDone->int_pol;//1;
	stData.bits.pipe_config_done = pstCfgDone->pipe_config_done;//1;
	stData.bits.sens_reg_wr_protect = pstCfgDone->sens_reg_wr_protect;
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	
	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SET_IntPol(struct isp_device *isp,int s8Index,VI_PIPE_CONFIG_DONE_S *pstCfgDone)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstCfgDone);	

	U_VI_PIPE_CONFIG_DONE stData;
	stData.u32 = isp_reg_readl(isp,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	stData.bits.int_pol = pstCfgDone->int_pol;//1;
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	return 0;
}
/*
*
*/
int VI_PIPE_DRV_SET_RegWP(struct isp_device *isp,int s8Index,VI_PIPE_CONFIG_DONE_S *pstCfgDone)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstCfgDone);

	U_VI_PIPE_CONFIG_DONE stData;
	stData.u32 = isp_reg_readl(isp,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	stData.bits.sens_reg_wr_protect = pstCfgDone->sens_reg_wr_protect;
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	return 0;
}
/*
*
*/
 int VI_DRV_PIPE_SetInt(struct isp_device *isp,int s8Index,VI_PIPE_INT_CTL_S *pstIntCtl)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(pstIntCtl);

	U_VI_PIPE_INT_CTL stIntCtl;
	stIntCtl.u32 = 0xffff0000;
	
	stIntCtl.bits.dma_raw_rd_ch_err_frame_end_mask 	= ~pstIntCtl->dma_raw_rd_ch_err_frame_end_en;
	stIntCtl.bits.dma_raw_rd_ch_err_immediate_mask 	= ~pstIntCtl->dma_raw_rd_ch_err_immediate_en;
	stIntCtl.bits.dma_raw_rd_ch_frame_end_mask 		= ~pstIntCtl->dma_raw_rd_ch_frame_end_en;
	stIntCtl.bits.dma_raw_rd_ch_line_base_mask 		= ~pstIntCtl->dma_raw_rd_ch_line_base_en;
	stIntCtl.bits.dma_uv_wr_ch_err_frame_end_mask 	= ~pstIntCtl->dma_uv_wr_ch_err_frame_end_en;
	stIntCtl.bits.dma_uv_wr_ch_err_immediate_mask 	= ~pstIntCtl->dma_uv_wr_ch_err_immediate_en;
	stIntCtl.bits.dma_uv_wr_ch_frame_end_mask 		= ~pstIntCtl->dma_uv_wr_ch_frame_end_en;
	stIntCtl.bits.dma_uv_wr_ch_line_base_mask 		= ~pstIntCtl->dma_uv_wr_ch_line_base_en;
	stIntCtl.bits.dma_y_wr_ch_err_frame_end_mask 	= ~pstIntCtl->dma_y_wr_ch_err_frame_end_en;
	stIntCtl.bits.dma_y_wr_ch_err_immediate_mask 	= ~pstIntCtl->dma_y_wr_ch_err_immediate_en;
	stIntCtl.bits.dma_y_wr_ch_line_base_mask 		= ~pstIntCtl->dma_y_wr_ch_line_base_en;
	stIntCtl.bits.dma_y_wr_frame_end_mask 			= ~pstIntCtl->dma_y_wr_frame_end_en;
	stIntCtl.bits.emb_ctl_frame_end_mask 			= ~pstIntCtl->emb_ctl_frame_end_en;
	stIntCtl.bits.emb_ctl_time_out_mask 			= ~pstIntCtl->emb_ctl_time_out_en;
	stIntCtl.bits.tpg_ctl_frame_end_mask 			= ~pstIntCtl->tpg_ctl_frame_end_en;
	stIntCtl.bits.win_ctl_frame_end_mask 			= ~pstIntCtl->win_ctl_frame_end_en;
	isp_reg_writel(isp,stIntCtl.u32,reg_vi_pipe_base[s8Index],VI_PIPE_INT_CTL);
	
	return 0;
}
/*
*
*/
unsigned int VI_DRV_PIPE_GetPipeIntSts(struct isp_device *isp,int s8Index)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);

	U_VI_PIPE_INT_CTL stIntCtl;
	stIntCtl.u32 = isp_reg_readl(isp,reg_vi_pipe_base[s8Index],VI_PIPE_INT_CTL);
	return stIntCtl.u32;
}
/*
*
*/
int VI_DRV_PIPE_ClearPipeIntSts(struct isp_device *isp,int s8Index,int int_status)
{
	ISP_CHECK_POINTER(isp);		

	isp_reg_writel(isp,int_status,reg_vi_pipe_base[s8Index],VI_PIPE_INT_CTL);
	return 0;
}
/*
*
*/
int VI_DRV_PIPE_SetPipeInt(struct isp_device *isp,int s8Index,int en_int)
{
	ISP_CHECK_POINTER(isp);		

	isp_reg_writel(isp,en_int,reg_vi_pipe_base[s8Index],VI_PIPE_INT_CTL);

	return 0;
}
/**
 * @brief 
 * 
 */
int VI_DRV_PIPE_SetWBuf(struct isp_device *isp,int s8Index,unsigned long BufAddr)
{
	VI_CHECK_PIPE(s8Index);
	ISP_CHECK_POINTER(isp);

	U_VI_PIPE_FRM_BASE_ADDR0_Y stFrameY0;
	stFrameY0.u32 = 0;
	stFrameY0.bits.image_frm_y_base_addr0 = BufAddr;//0x30000000;
	isp_reg_writel(isp,stFrameY0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_FRM_BASE_ADDR0_Y);
	
	U_VI_PIPE_FRM_BASE_ADDR1_Y stFrameY1;
	stFrameY1.u32 = 0;
	stFrameY1.bits.image_frm_y_base_addr1 = BufAddr;//0x30000000;
	isp_reg_writel(isp,stFrameY0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_FRM_BASE_ADDR1_Y);

	U_VI_PIPE_TPG_FRM_BASE_ADDR0_Y stYBuf0;
	stYBuf0.u32 = 0;
	stYBuf0.bits.tpg_y_frm_base_addr0 = BufAddr;//0x30000000;
	isp_reg_writel(isp,stYBuf0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_FRM_BASE_ADDR0_Y);
	
	U_VI_PIPE_TPG_FRM_BASE_ADDR1_Y stYBuf1;
	stYBuf1.u32 = 0;
	stYBuf1.bits.tpg_y_frm_base_addr1 = BufAddr;//0x30000000;
	isp_reg_writel(isp,stYBuf0.u32,reg_vi_pipe_base[s8Index],VI_PIPE_TPG_FRM_BASE_ADDR1_Y);

	U_VI_PIPE_CONFIG_DONE stData;
	isp_reg_readl(isp,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);
	stData.bits.pipe_config_done = 1;
	isp_reg_writel(isp,stData.u32,reg_vi_pipe_base[s8Index],VI_PIPE_CONFIG_DONE);

	return 0;
}