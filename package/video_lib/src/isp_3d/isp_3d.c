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
 * isp_3d.c
 *
 * CANAAN ISP - isp 3d module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifdef _USE_V4L2
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <media/v4l2-event.h>
#include "isp_video.h"
#endif

#include "isp_com.h"

#include "isp_3d/isp_3d.h"
#include "isp_3d/wrap/isp_3d_wrap_drv.h"
#include "isp_3d/core/isp_3d_core_drv.h"
/*-----------------------------------------------------------------------------
*WRAP
-----------------------------------------------------------------------------*/
/*
*reset
*/
static void tof_wrap_reset(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);

	TOF_WRAP_CTL_SWRST_S stSwRst;
	stSwRst.tof_wrap_com_pipe_rst = 1;
	stSwRst.tof_wrap_cfg_pipe_rst = 1;
	stSwRst.tof_core_com_pipe_rst = 1;
	stSwRst.tof_core_com_pipe_rst = 1;	
	stSwRst.tof_out_depth_pipe_rst = 1;
	stSwRst.tof_out_gray_pipe_rst = 1;
	stSwRst.tof_pixel_clk_pipe_rst = 1;
	stSwRst.tof_pixel_div6_clk_pipe_rst = 1;
	stSwRst.tof_depth_dma_ch_rst = 1;
	stSwRst.tof_gray_dma_ch_rst = 1;
	stSwRst.tof_axi_wr_ch_rst = 1;
	stSwRst.tof_axi_rd_ch_rst = 1;   
	TOF_Drv_Wrap_SetReset(isp,&stSwRst);
}
/*
*
*/
static void tof_wrap_enable(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    
    //
    TOF_WRAP_CTL_CLK_EN_S stClkEn;
	stClkEn.tof_wrap_com_clk_en = 1;
	stClkEn.tof_wrap_cfg_clk_en = 1;
	stClkEn.tof_core_com_clk_en = 1;
	stClkEn.tof_core_cfg_clk_en = 1;
		   
	stClkEn.tof_out_depth_clk_en = 1;
	stClkEn.tof_out_gray_clk_en = 1;
	stClkEn.tof_core_sensor_clk_en = 1;
	stClkEn.tof_axi_wr_clk_en = 1;
	stClkEn.tof_axi_rd_clk_en = 1;
    TOF_Drv_Wrap_SetPipeClkCtl(isp,&stClkEn);
    //
    unsigned int tof_wrap_dma_out_en = 1;
    TOF_Drv_Wrap_SetCtlDmaEn(isp,tof_wrap_dma_out_en);
}
/*
*
*/
static void tof_set_outaddr(struct isp_device *isp,unsigned int addr)
{
    ISP_CHECK_POINTER(isp);
    

	TOF_WRAP_BUF_S pstBuf;
	TOF_Drv_Wrap_SetBuf(isp,&pstBuf);
}
/*
*
*/
static void tof_wrap_done(struct isp_device *isp)
{
    ISP_CHECK_POINTER(isp);
    

	TOF_WRAP_COFIG_DONE_S stCfgDone;
    stCfgDone.tof_wrap_config_done_en =  1;
    stCfgDone.tof_sen_reg_pro_en      =  1;
    stCfgDone.tof_int_polarity        =  1;
	TOF_Drv_Wrap_SetConfigDone(isp,&stCfgDone);
}
/*
*
*/
static void tof_set_int(struct isp_device *isp,TOF_WRAP_INT_CTL_S *stIntMask)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(stIntMask);

    
	TOF_Drv_Wrap_SetInt(isp,stIntMask);
}
/*
*
*/
static int tof_wrap_config(struct isp_device *isp,TOF_WRAP_ATTR_S *tofWrapAttr)
{
	ISP_CHECK_POINTER(isp);
	ISP_CHECK_POINTER(tofWrapAttr);

	

//	TOF_WRAP_CTL_SWRST_S *stSwRst = &tofWrapAttr->stSwRst;
//	TOF_Drv_Wrap_SetReset(isp,stSwRst);
	
	TOF_WRAP_CTL_MODE_S  *stMode =  &tofWrapAttr->stMode;
	TOF_Drv_Wrap_SetCtlMode(isp,stMode);

//	TOF_WRAP_CTL_CLK_EN_S *stClkEn = &tofWrapAttr->stClkEn;
//	TOF_Drv_Wrap_SetPipeClkCtl(isp,stClkEn);

//	unsigned int tof_wrap_dma_out_en = tofWrapAttr->tof_wrap_dma_out_en;
//	TOF_Drv_Wrap_SetCtlDmaEn(isp,tof_wrap_dma_out_en);

	unsigned int ctrl_pixel_format_isp = tofWrapAttr->ctrl_pixel_format_isp;
	TOF_Drv_Wrap_SetCtlPixelFormatISP(isp,ctrl_pixel_format_isp);

	unsigned int tof_out_pixel_format = tofWrapAttr->tof_out_pixel_format;
	TOF_Drv_Wrap_SetPixelFormatOut(isp,tof_out_pixel_format);

	TOF_WRAP_OUT_SIZE_S *pstSize = &tofWrapAttr->stOutSize;
	TOF_Drv_Wrap_SetOutSize(isp,pstSize);

	TOF_WRAP_DMA_MODE_S *pstDmaMode = &tofWrapAttr->stDmaMode;	
	TOF_Drv_Wrap_SetDma(isp,pstDmaMode);

//	TOF_WRAP_BUF_S *pstBuf = &tofWrapAttr->stBuf;
//	TOF_Drv_Wrap_SetBuf(isp,pstBuf);

	TOF_WRAP_AXI_CTL_S *stAxiCtl = &tofWrapAttr->stAxiCtl;
	TOF_Drv_Wrap_SetAxiCtl(isp,stAxiCtl);

//	TOF_WRAP_COFIG_DONE_S *stCfgDone = &tofWrapAttr->stCfgDone;
//	TOF_Drv_Wrap_SetConfigDone(isp,stCfgDone);

//	TOF_WRAP_INT_CTL_S *stIntMask = &tofWrapAttr->stIntMask;
//	TOF_Drv_Wrap_SetInt(isp,stIntMask);

	return 0;
}
#if 0
/*
 * tof_wrap_print_status - Prints the values of the isp 3d wrap module registers.
 */
#define ISP_3D_WRAP_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###ISP_3D_WRAP " #name "=0x%08x\n", \
		isp_reg_readl(isp, TOF_WRAP_BASE, name))



static void tof_wrap_print_status(struct isp_device *isp)
{
	

	dev_dbg(isp->dev, "-------------isp 3d tof wrap Register dump start----------\n");
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_CTL_SWRST     		);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CTL_SWRST     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_CTL_MODE     			);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_CTL_CLK_EN    	    );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_CTL_DMA_EN    	    );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_CTL_PIXEL_FORMAT_ISP  );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_CTL_PIXEL_FORMAT      );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_OUT_SIZE     			);

	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_ARB_MODE     		);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_WR_WEIGHT_0     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_WR_WEIGHT_1     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_RD_WEIGHT_0     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_RD_WEIGHT_1     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_WR_PRIORITY     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_RD_PRIORITY     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_DMA_WR_CH_ID     			);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_DMA_RD_CH_ID     			);

	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DEPTH_BUF0_BASE     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DEPTH_BUF1_BASE     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_GRAY_BUF0_BASE     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_GRAY_BUF1_BASE     	);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_BUF_STRIDE     		);

	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CH0_CFG     		);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CH1_CFG     		);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CH0_ERR_DEC_CFG   );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CH1_ERR_DEC_CFG   );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CH0_ERR_STATUS    );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_DMA_CH1_ERR_STATUS    );
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_AXI_CTL     			);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_COFIG_DONE     		);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_WRAP_INT_CTL     			);
	
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_VERSION     				);
	ISP_3D_WRAP_PRINT_REGISTER(isp,TOF_RELEASE_INFO     			);
	dev_dbg(isp->dev, "-------------isp 3d tof wrap Register dump end----------\n");
}
/*-----------------------------------------------------------------------------
*CORE
-----------------------------------------------------------------------------*/
static int tof_core_config(struct isp_device *isp,TOF_CORE_ATTR_S *tofCoreAttr)
{
	ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(tofCoreAttr);

    

	TOF_CORE_ITC_ATTR_S *pstItcAttr =&tofCoreAttr->stItcAttr;
	TOF_DRV_CORE_SetItcAttr(isp,pstItcAttr);

	TOF_DRV_SENSOR_TYPE_E eSensorType = tofCoreAttr->eSensorType;
	TOF_DRV_CORE_SetSensorType(isp,eSensorType );

	TOF_CORE_GEN_ATTR_S *pstGenAttr =&tofCoreAttr->stGenAttr;
	TOF_DRV_CORE_SetGenAttr(isp,pstGenAttr);

	TOF_CORE_GRAY_TH_ATTR_S *pstGrayTHAttr = &tofCoreAttr->stGrayTHAttr;
	TOF_DRV_CORE_SetGrayThAttr(isp,pstGrayTHAttr);

	TOF_CORE_AE_ATTR_S *pstAeAttr =&tofCoreAttr->stAeAttr;
	TOF_DRV_CORE_SetAECtl(isp,pstAeAttr);

	TOF_CORE_NR2D_ATTR_S *pstNr2dAttr = &tofCoreAttr->stNr2dAttr;
	TOF_DRV_CORE_SetNr2dAttr(isp,pstNr2dAttr);

	TOF_CORE_POST_ATTR_S *pstPostAttr =&tofCoreAttr->stPostAttr;
	TOF_DRV_CORE_SetPostAttr(isp,pstPostAttr);
	return 0;
}
/*
 * isp_3d_core_print_status - Prints the values of the isp 3d core module registers.
 */
#define ISP_3D_CORE_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###ISP_3D_CORE " #name "=0x%08x\n", \
		isp_reg_readl(isp, TOF_CORE_BASE, name))


static void tof_core_print_status(struct isp_device *isp)
{
	

	dev_dbg(isp->dev, "-------------isp 3d tof core Register dump start----------\n");
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_CTL     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_HEIGHT     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_WIDTH     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_VSTART     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_HSTART     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_ACTIVE_WIDTH     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_ACTIVE_HEIGHT     );
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_ITC_ACTIVE_START_LINE );

	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_SENSOR_SEL     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_GEN_CTL     			);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_GRAY_TH     			);

	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_CTL     			);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_WIN_HSTART     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_WIN_VSTART     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_WIN_H_END    		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_WIN_V_END    		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_TAR_BRIGHT     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_TAR_BRIGHT_RANGE   );
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_EX_TIME     		);														   
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_AGC     			);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_AD_FREQ     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_AD_STEP_MAX    	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_EX_VALUE_MAX     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_EX_VALUE_MID     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_EX_VALUE_MIN     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_GAIN_MAX     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_GAIN_MID     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_GAIN_MIN     		);	
  
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_VALUE_READY     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_LONG_CUR_EX     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_SHORT_CUR_EX     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_CUR_DIGITAL_GAIN   );
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_CUR_AVE_BRIGHTNESS );
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_EX_STATUS     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_SUM     			);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_AE_PIXEL_SUM     		);
   
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_2DNR_CTL     			);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_2DNR_GRAY     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_2DNR_DEPTH    		);
  
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_POST_CTL     			);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_CONT_GAIN     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_LUMA_GAIN     		);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_SATU_GAIN     		);

	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_RAM_WR_STATUS     	);
	ISP_3D_CORE_PRINT_REGISTER(isp,TOF_CORE_RAM_RD_STATUS     	);
	dev_dbg(isp->dev, "-------------isp 3d tof core Register dump end----------\n");
}


static int tof_isr_buffer(struct isp_device *isp)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&tof->subdev.entity);
	
	struct isp_buffer *buffer;

	/* The tof generates DMA_WR_INT_ST_GRAY/DMA_WR_INT_ST_DEPTH interrupts even when disabled (the datasheet
	 * doesn't explicitly state if that's supposed to happen or not, so it
	 * can be considered as a hardware bug or as a feature, but we have to
	 * deal with it anyway). Disabling the tof when no buffer is available
	 * would thus not be enough, we need to handle the situation explicitly.
	 */
	if (list_empty(&tof->video_out.dmaqueue))
		return 0;

	/* We're in continuous mode, and memory writes were disabled due to a
	 * buffer underrun. Reenable them now that we have a buffer. The buffer
	 * address has been set in tof_video_queue.
	 */
	if (tof->state == ISP_PIPELINE_STREAM_CONTINUOUS && tof->underrun) {
		tof->underrun = 0;
		return 1;
	}

	buffer = isp_video_buffer_next(&tof->video_out);
	if (buffer != NULL)
		tof_set_outaddr(tof, buffer->dma);

	pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;

	return buffer != NULL;
}
/*
 * tof_ae_isr - Handle ae event
 * @tof: Pointer to ISP TOF device.
 *
 * Executes ae before next frame starts.
 */
static void tof_ae_isr(struct isp_device *isp)
{
	unsigned long flags;
}
/*
 * tof_gray_depth_isr - Handle ae event
 * @tof: Pointer to ISP TOF device.
 *
 * gray&depth enablement before next frame starts.
 */
static void tof_gray_depth_isr(struct isp_device *isp)
{
	unsigned long flags;
}
/*
 * tof_dma_isr - Handle dma event
 * @tof: Pointer to ISP TOF device.
 *
 * Executes LSC deferred enablement before next frame starts.
 */
static void tof_dma_isr(struct isp_device *isp)
{
	unsigned long flags;
	int restart = 0;

	if (tof->output & TOF_OUTPUT_MEMORY)
		restart = tof_isr_buffer(tof);

	spin_lock_irqsave(&tof->lock, flags);

	//if (tof_handle_stopping(tof, CCDC_EVENT_VD0)) {
	//	spin_unlock_irqrestore(&tof->lock, flags);
	//	return;
	//}

	if (!tof->shadow_update)
		//tof_apply_controls(tof);
	spin_unlock_irqrestore(&tof->lock, flags);

	if (restart)
		tof_enable(tof);

}
/*
 * tof_isr - Configure tof during interframe time.
 * @tof: Pointer to ISP tof device.
 * @events: tof events
 */
int tof_isr(struct isp_device *isp, u32 events)
{
	if (tof->state == ISP_PIPELINE_STREAM_STOPPED)
		return 0;

	if (events & TOF_CORE_INT_ST_AE_OUT)
		tof_ae_isr(tof);
	if (events & TOF_CORE_INT_ST_GRAY_DEPTH_OUT)
		tof_gray_depth_isr(tof);
	if (events & (DMA_WR_INT_ST_GRAY|DMA_WR_INT_ST_DEPTH))
		tof_dma_isr(tof);
	return 0;
}
/* -----------------------------------------------------------------------------
 * ISP video operations
 -----------------------------------------------------------------------------*/

static int tof_video_queue(struct isp_video *video, struct isp_buffer *buffer)
{
	struct isp_device *isp = &video->isp->tof;
	unsigned long flags;
	bool restart = false;

	if (!(tof->output & TOF_OUTPUT_MEMORY))
		return -ENODEV;

	tof_set_outaddr(tof, buffer->dma);

	/* We now have a buffer queued on the output, restart the pipeline
	 * on the next tof interrupt if running in continuous mode (or when
	 * starting the stream) in external sync mode, or immediately in BT.656
	 * sync mode as no tof interrupt is generated when the tof is stopped
	 * in that case.
	 */
	spin_lock_irqsave(&tof->lock, flags);
	if (tof->state == ISP_PIPELINE_STREAM_CONTINUOUS && !tof->running)
		restart = true;
	else
		tof->underrun = 1;
	spin_unlock_irqrestore(&tof->lock, flags);

	if (restart)
		tof_enable(tof);

	return 0;
}

static const struct isp_video_operations tof_video_ops = {
	.queue = tof_video_queue,
};
/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 -----------------------------------------------------------------------------*/

/*
 * tof_ioctl - tof module private ioctl's
 * @sd: ISP tof V4L2 subdevice
 * @cmd: ioctl command
 * @arg: ioctl argument
 *
 * Return 0 on success or a negative error code otherwise.
 */
static long tof_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	int ret;

	switch (cmd) {
	case VIDIOC_tof_WRAP_CFG:
		mutex_lock(&tof->ioctl_lock);
		ret = tof_wrap_config(tof, arg);
		mutex_unlock(&tof->ioctl_lock);
		break;
	case VIDIOC_tof_CORE_CFG:
		mutex_lock(&tof->ioctl_lock);
		ret = tof_core_config(tof, arg);
		mutex_unlock(&tof->ioctl_lock);
		break;
	default:
		return -ENOIOCTLCMD;
	}

	return ret;
}

static int tof_subscribe_event(struct v4l2_subdev *sd, struct v4l2_fh *fh,
				struct v4l2_event_subscription *sub)
{
	if (sub->type != V4L2_EVENT_FRAME_SYNC)
		return -EINVAL;

	/* line number is zero at frame start */
	if (sub->id != 0)
		return -EINVAL;

	return v4l2_event_subscribe(fh, sub, tof_NEVENTS, NULL);
}

static int tof_unsubscribe_event(struct v4l2_subdev *sd, struct v4l2_fh *fh,
				  struct v4l2_event_subscription *sub)
{
	return v4l2_event_unsubscribe(fh, sub);
}
/*
 * tof_set_stream - Enable/Disable streaming on the TOF module
 * @sd: ISP TOF V4L2 subdevice
 * @enable: Enable/disable stream
 *
 * When writing to memory, the TOF hardware can't be enabled without a memory
 * buffer to write to. As the s_stream operation is called in response to a
 * STREAMON call without any buffer queued yet, just update the enabled field
 * and return immediately. The TOF will be enabled in tof_isr_buffer().
 *
 * When not writing to memory enable the TOF immediately.
 */
static int tof_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	
	int ret = 0;

	if (tof->state == ISP_PIPELINE_STREAM_STOPPED) {
		if (enable == ISP_PIPELINE_STREAM_STOPPED)
			return 0;

		//ccdc_configure(ccdc);

		//ccdc_print_status(ccdc);
        tof_wrap_print_status(tof);
        tof_core_print_status(tof);
	}

	switch (enable) {
	case ISP_PIPELINE_STREAM_CONTINUOUS:
		if (tof->underrun || !(tof->output & TOF_OUTPUT_MEMORY))
			tof_enable(tof);

		tof->underrun = 0;
		break;
	case ISP_PIPELINE_STREAM_STOPPED:
		ret = tof_disable(tof);
		if (tof->output & TOF_OUTPUT_MEMORY)

		tof->underrun = 0;
		break;
	}

	tof->state = enable;
	return ret;
}

static struct v4l2_mbus_framefmt *
__tof_get_format(struct isp_device *isp, struct v4l2_subdev_pad_config *cfg,
		  unsigned int pad, enum v4l2_subdev_format_whence which)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_format(&tof->subdev, cfg, pad);
	else
		return &tof->formats[pad];
}

static struct v4l2_rect *
__tof_get_crop(struct isp_device *isp, struct v4l2_subdev_pad_config *cfg,
		enum v4l2_subdev_format_whence which)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_crop(&tof->subdev, cfg, TOF_PAD_SOURCE_MEM);
	else
		return &tof->crop;
}
/*
 * tof_enum_mbus_code - Handle pixel format enumeration
 * @sd     : pointer to v4l2 subdev structure
 * @cfg : V4L2 subdev pad configuration
 * @code   : pointer to v4l2_subdev_mbus_code_enum structure
 * return -EINVAL or zero on success
 */
static int tof_enum_mbus_code(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_mbus_code_enum *code)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	switch (code->pad) {
	case TOF_PAD_SINK:
		if (code->index >= ARRAY_SIZE(tof_fmts))
			return -EINVAL;

		code->code = tof_fmts[code->index];
		break;

	case TOF_PAD_SOURCE_MEM:
		format = __tof_get_format(tof, cfg, code->pad,
					   code->which);

		if (format->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
		    format->code == MEDIA_BUS_FMT_UYVY8_2X8) {
			/* In YUV mode the TOF can swap bytes. */
			if (code->index == 0)
				code->code = MEDIA_BUS_FMT_YUYV8_1X16;
			else if (code->index == 1)
				code->code = MEDIA_BUS_FMT_UYVY8_1X16;
			else
				return -EINVAL;
		} else {
			/* In raw mode, no configurable format confversion is
			 * available.
			 */
			if (code->index == 0)
				code->code = format->code;
			else
				return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int tof_enum_frame_size(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_size_enum *fse)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt format;

	if (fse->index != 0)
		return -EINVAL;

	format.code = fse->code;
	format.width = 1;
	format.height = 1;
	tof_try_format(tof, cfg, fse->pad, &format, fse->which);
	fse->min_width = format.width;
	fse->min_height = format.height;

	if (format.code != fse->code)
		return -EINVAL;

	format.code = fse->code;
	format.width = -1;
	format.height = -1;
	tof_try_format(tof, cfg, fse->pad, &format, fse->which);
	fse->max_width = format.width;
	fse->max_height = format.height;

	return 0;
}
/*
 * tof_get_format - Retrieve the video format on a pad
 * @sd : ISP TOF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL if the pad is invalid or doesn't correspond
 * to the format type.
 */
static int tof_get_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __tof_get_format(tof, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	fmt->format = *format;
	return 0;
}

/*
 * tof_set_format - Set the video format on a pad
 * @sd : ISP TOF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL if the pad is invalid or doesn't correspond
 * to the format type.
 */
static int tof_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	format = __tof_get_format(tof, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	tof_try_format(tof, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == TOF_PAD_SINK) {
		/* Reset the crop rectangle. */
		crop = __tof_get_crop(tof, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->format.width;
		crop->height = fmt->format.height;

		tof_try_crop(tof, &fmt->format, crop);

		/* Update the source formats. */
		format = __tof_get_format(tof, cfg, TOF_PAD_SOURCE_MEM,
					   fmt->which);
		*format = fmt->format;
		tof_try_format(tof, cfg, TOF_PAD_SOURCE_MEM, format,
				fmt->which);

	}

	return 0;
}
/*
 * tof_get_selection - Retrieve a selection rectangle on a pad
 * @sd: ISP TOF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangles are the crop rectangles on the output formatter
 * source pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
static int tof_get_selection(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_selection *sel)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	if (sel->pad != TOF_PAD_SOURCE_MEM)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = INT_MAX;
		sel->r.height = INT_MAX;

		format = __tof_get_format(tof, cfg, TOF_PAD_SINK, sel->which);
		tof_try_crop(tof, format, &sel->r);
		break;

	case V4L2_SEL_TGT_CROP:
		sel->r = *__tof_get_crop(tof, cfg, sel->which);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}
/*
 * tof_set_selection - Set a selection rectangle on a pad
 * @sd: ISP TOF V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangle is the actual crop rectangle on the output
 * formatter source pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
static int tof_set_selection(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_selection *sel)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	if (sel->target != V4L2_SEL_TGT_CROP ||
	    sel->pad != TOF_PAD_SOURCE_MEM)
		return -EINVAL;

	/* The crop rectangle can't be changed while streaming. */
	if (tof->state != ISP_PIPELINE_STREAM_STOPPED)
		return -EBUSY;

	/* Modifying the crop rectangle always changes the format on the source
	 * pad. If the KEEP_CONFIG flag is set, just return the current crop
	 * rectangle.
	 */
	if (sel->flags & V4L2_SEL_FLAG_KEEP_CONFIG) {
		sel->r = *__tof_get_crop(tof, cfg, sel->which);
		return 0;
	}

	format = __tof_get_format(tof, cfg, TOF_PAD_SINK, sel->which);
	tof_try_crop(tof, format, &sel->r);
	*__tof_get_crop(tof, cfg, sel->which) = sel->r;

	/* Update the source format. */
	format = __tof_get_format(tof, cfg, TOF_PAD_SOURCE_MEM, sel->which);
	tof_try_format(tof, cfg, TOF_PAD_SOURCE_MEM, format, sel->which);

	return 0;
}

static int tof_link_validate(struct v4l2_subdev *sd,
			      struct media_link *link,
			      struct v4l2_subdev_format *source_fmt,
			      struct v4l2_subdev_format *sink_fmt)
{
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	unsigned long parallel_shift;

	/* Check if the two ends match */
	if (source_fmt->format.width != sink_fmt->format.width ||
	    source_fmt->format.height != sink_fmt->format.height)
		return -EPIPE;

	/* We've got a parallel sensor here. */
	if (tof->input == TOF_INPUT_VI) {

	} else {
		
	}

	return 0;
}
/*
 * tof_init_formats - Initialize formats on all pads
 * @sd: ISP TOF V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad formats with default values. If fh is not NULL, try
 * formats are initialized on the file handle. Otherwise active formats are
 * initialized on the device.
 */
static int tof_init_formats(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct v4l2_subdev_format format;

	memset(&format, 0, sizeof(format));
	format.pad = TOF_PAD_SINK;
	format.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	format.format.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	format.format.width = 1920;
	format.format.height = 1080;
	tof_set_format(sd, fh ? fh->pad : NULL, &format);

	return 0;
}
/* V4L2 subdev core operations */
static const struct v4l2_subdev_core_ops tof_v4l2_core_ops = {
	.ioctl = tof_ioctl,
	.subscribe_event = tof_subscribe_event,
	.unsubscribe_event = tof_unsubscribe_event,
};

/* V4L2 subdev video operations */
static const struct v4l2_subdev_video_ops tof_v4l2_video_ops = {
	.s_stream = tof_set_stream,
};

/* V4L2 subdev pad operations */
static const struct v4l2_subdev_pad_ops tof_v4l2_pad_ops = {
	.enum_mbus_code = tof_enum_mbus_code,
	.enum_frame_size = tof_enum_frame_size,
	.get_fmt = tof_get_format,
	.set_fmt = tof_set_format,
	.get_selection = tof_get_selection,
	.set_selection = tof_set_selection,
	.link_validate = tof_link_validate,
};

/* V4L2 subdev operations */
static const struct v4l2_subdev_ops tof_v4l2_ops = {
	.core = &tof_v4l2_core_ops,
	.video = &tof_v4l2_video_ops,
	.pad = &tof_v4l2_pad_ops,
};

/* V4L2 subdev internal operations */
static const struct v4l2_subdev_internal_ops tof_v4l2_internal_ops = {
	.open = tof_init_formats,
};
/* -----------------------------------------------------------------------------
 * Media entity operations
 -----------------------------------------------------------------------------*/
/*
 * tof_link_setup - Setup TOF connections
 * @entity: TOF media entity
 * @local: Pad at the local end of the link
 * @remote: Pad at the remote end of the link
 * @flags: Link flags
 *
 * return -EINVAL or zero on success
 */
static int tof_link_setup(struct media_entity *entity,
			   const struct media_pad *local,
			   const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct isp_device *isp = v4l2_get_subdevdata(sd);
	

	switch (local->index | media_entity_type(remote->entity)) {
	case TOF_PAD_SINK | MEDIA_ENT_T_V4L2_SUBDEV:
		/* 
		 * Read from VI.
		 */
		if (!(flags & MEDIA_LNK_FL_ENABLED)) {
			tof->input = TOF_INPUT_NONE;
			break;
		}

		if (tof->input != TOF_INPUT_NONE)
			return -EBUSY;

		if (remote->entity == &isp->tof.subdev.entity)
			tof->input = TOF_INPUT_VI;
		else
			tof->input = TOF_INPUT_NONE;

		break;

	/*
	 * The ISP core doesn't support pipelines with multiple video outputs.
	 * Revisit this when it will be implemented, and return -EBUSY for now.
	 */

	case TOF_PAD_SOURCE_MEM | MEDIA_ENT_T_V4L2_SUBDEV:
		/* Write to preview engine, histogram and H3A. When none of
		 * those links are active, the video port can be disabled.
		 */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (tof->output & ~TOF_PAD_SOURCE_MEM)
				return -EBUSY;
			tof->output |= TOF_PAD_SOURCE_MEM;
		} else {
			tof->output &= ~TOF_PAD_SOURCE_MEM;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
/* media operations */
static const struct media_entity_operations tof_media_ops = {
	.link_setup = tof_link_setup,
	.link_validate = v4l2_subdev_link_validate,
};

void tof_unregister_entities(struct isp_device *isp)
{
	v4l2_device_unregister_subdev(&tof->subdev);
	isp_video_unregister(&tof->video_out);
}

int tof_register_entities(struct isp_device *isp,
	struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev and video node. */
	ret = v4l2_device_register_subdev(vdev, &tof->subdev);
	if (ret < 0)
		goto error;

	ret = isp_video_register(&tof->video_out, vdev);
	if (ret < 0)
		goto error;

	return 0;

error:
	tof_unregister_entities(tof);
	return ret;
}
/* -----------------------------------------------------------------------------
 * ISP TOF initialisation and cleanup
 -----------------------------------------------------------------------------*/
/*
 * tof_init_entities - Initialize V4L2 subdev and media entity
 * @tof: ISP TOF module
 *
 * Return 0 on success and a negative error code on failure.
 */
static int tof_init_entities(struct isp_device *isp)
{
	struct v4l2_subdev *sd = &tof->subdev;
	struct media_pad *pads = tof->pads;
	struct media_entity *me = &sd->entity;
	int ret;

	tof->input = TOF_INPUT_NONE;

	v4l2_subdev_init(sd, &tof_v4l2_ops);
	sd->internal_ops = &tof_v4l2_internal_ops;
	strlcpy(sd->name, "CANAAN ISP TOF", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for isp subdevs */
	v4l2_set_subdevdata(sd, tof);
	sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[TOF_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;
	pads[TOF_PAD_SOURCE_MEM].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &tof_media_ops;
	ret = media_entity_init(me, TOF_PADS_NUM, pads, 0);
	if (ret < 0)
		return ret;

	tof_init_formats(sd, NULL);

	tof->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tof->video_out.ops = &tof_video_ops;
	tof->video_out.isp = to_isp_device(tof);
	tof->video_out.capture_mem = PAGE_ALIGN(1920 * 1080) * 6;
	tof->video_out.bpl_alignment = 32;

	ret = isp_video_init(&tof->video_out, "TOF");
	if (ret < 0)
		goto error_video;

	/* Connect the TOF subdev to the video node. */
	ret = media_entity_create_link(&tof->subdev.entity, TOF_PAD_SOURCE_MEM,
			&tof->video_out.video.entity, 0, 0);
	if (ret < 0)
		goto error_link;

	return 0;

error_link:
	isp_video_cleanup(&tof->video_out);
error_video:
	media_entity_cleanup(me);
	return ret;
}
/*
 * tof_init - TOF module initialization.
 * @isp: Device pointer specific to the CANAAN ISP.
 *
 * TODO: Get the initialisation values from platform data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
int tof_init(struct isp_device *isp)
{
	struct isp_device *isp = &isp->tof;
	int ret;

	spin_lock_init(&tof->lock);
	init_waitqueue_head(&tof->wait);
	mutex_init(&tof->ioctl_lock);

	tof->stopping = CCDC_STOP_NOT_REQUESTED;

	ret = tof_init_entities(tof);
	if (ret < 0) {
		mutex_destroy(&tof->ioctl_lock);
		return ret;
	}

	return 0;
}
/*
 * tof_cleanup - TOF module cleanup.
 * @isp: Device pointer specific to the OMAP3 ISP.
 */
void tof_cleanup(struct isp_device *isp)
{
	struct isp_device *isp = &isp->tof;

	isp_video_cleanup(&tof->video_out);
	media_entity_cleanup(&tof->subdev.entity);

	if (tof->fpc.addr != NULL)
		dma_free_coherent(isp->dev, tof->fpc.fpnum *2, tof->fpc.addr,
				  tof->fpc.dma);

	mutex_destroy(&tof->ioctl_lock);
}
#endif