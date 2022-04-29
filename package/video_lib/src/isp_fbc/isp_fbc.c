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
 * isp_fbc.c
 *
 * CANAAN ISP - isp 3d wrap module
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */
#ifdef  _USE_V4L2
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <media/v4l2-event.h>
#endif

#include <stdio.h>
#include "isp_com.h"
#include "isp_fbc/isp_fbc.h"
#include "isp_fbc/wrap/fbc_wrap_reg.h"
#include "isp_fbc/wrap/fbc_wrap_drv.h"
#include "isp_fbc/core/fbc_core_reg.h"
#include "isp_fbc/core/fbc_core_drv.h"

/*
*WRAP
*/
static int fbc_wrap_config(struct isp_fbc_device *fbc,
		       FBC_WRAP_ATTR_S *pstWrapAttr)
{
    ISP_CHECK_POINTER(fbc);
    ISP_CHECK_POINTER(pstWrapAttr);

    struct isp_device *isp = to_isp_device(fbc);

    FBC_WRAP_RST_S *pstRst = &pstWrapAttr->stSwRst;
    Fbc_Drv_Wrap_SetRst(isp,pstRst);

    FBC_WRAP_DMA_S *pstDma = &pstWrapAttr->stDma;
    Fbc_Drv_Wrap_SetDma(isp,pstDma);

    FBC_WRAP_CLK_EN_S *pstClkEn = &pstWrapAttr->stClkEn;
    Fbc_Drv_Wrap_SetClkEn(isp,pstClkEn);

    unsigned int fbc_chl_sel = pstWrapAttr->fbc_chl_sel;
    Fbc_Drv_Wrap_SetChlSel(isp,fbc_chl_sel);

    FBC_WRAP_INT_MASK_S *pstIntMsk = &pstWrapAttr->stIntMsk;
    Fbc_Drv_Wrap_SetIntMask(isp,pstIntMsk);

    FBC_WRAP_CFG_DONE_S *pstCfgdDone = &pstWrapAttr->stCfgdDone;
    Fbc_Drv_Wrap_SetCfgDone(isp,pstCfgdDone);

    return 0;
}
/*
*
*/
static void fbc_cfg_done(struct isp_fbc_device *fbc)
{
    ISP_CHECK_POINTER(fbc);
	struct isp_device *isp = to_isp_device(fbc);

    FBC_WRAP_CFG_DONE_S pstCfgdDone;    
    pstCfgdDone.done = 1;
    Fbc_Drv_Wrap_SetCfgDone(isp,&pstCfgdDone);
}
/*
 * fbc_wrap_print_status - Prints the values of the isp fbc wrap module registers.
 */
#ifdef _USE_V4L2
#define FBC_WRAP_PRINT_REGISTER(isp,name)\
	dev_dbg(isp->dev,"###FBC_WRAP" #name "=0x%08x\n",isp_reg_readl(isp,ISP_IOMEM_FBC_WRAP,name))
#else
#define FBC_WRAP_PRINT_REGISTER(isp,name)\
	printf("###FBC_WRAP" #name "=0x%08x\n",isp_reg_readl(isp,ISP_IOMEM_FBC_WRAP,name))
#endif

void fbc_wrap_print_status(struct isp_fbc_device *fbc)
{
	struct isp_device *isp = to_isp_device(fbc);
#ifdef _USE_V4L2
	dev_dbg(isp->dev,"-------------ISP FBC WRAP Register dump start----------\n");
#else
	printf("-------------ISP FBC WRAP Register dump start----------\n");
#endif
	
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_SW_RST);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_OUT_SEL);
					
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_CLK_EN );
					
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_ARB_MODE);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_WEIGHT_WR0);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_WEIGHT_WR1);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_WEIGHT_RD0);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_WEIGHT_RD1);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_PRIORITY_WR);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_PRIORITY_RD);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_ID_WR);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_DMA_ID_RD);

	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_AXI_RST_REQ);	
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_CFG);
	FBC_WRAP_PRINT_REGISTER(isp,FBC_WRAP_INT);
#ifdef _USE_V4L2
	dev_dbg(isp->dev,"-------------ISP FBC WRAP Register dump end----------\n");
#else
  	printf("-------------ISP FBC WRAP Register dump end----------\n");
#endif
}
/*
*CORE
*/
static int fbc_core_config(struct isp_fbc_device *fbc,
		       FBC_CORE_ATTR_S *pstCoreAttr)
{
    ISP_CHECK_POINTER(fbc);
    ISP_CHECK_POINTER(pstCoreAttr);

	struct isp_device *isp = to_isp_device(fbc);
    FBC_CORE_SIZE_S *pstSize = &pstCoreAttr->stFbcSize;
    Fbc_Drv_Core_SetSize(isp,pstSize);

    unsigned int yuv420_en = pstCoreAttr->yuv420_en;
    Fbc_Drv_Core_SetCtl(isp,yuv420_en);
    return 0;
}
/*
 * fbc_set_outaddr - Set memory address to save output image
 * @fbc: Pointer to ISP fbc device.
 * @addr: ISP MMU Mapped 32-bit memory address aligned on 32 byte boundary.
 *
 * Sets the memory address where the output will be saved.
 */
static void fbc_set_outaddr(struct isp_fbc_device *fbc, unsigned int addr)
{
    ISP_CHECK_POINTER(fbc);
	struct isp_device *isp = to_isp_device(fbc);    
    FBC_CORE_BUF_S pstFbcBuf;

	Fbc_Drv_Core_SetBuf(isp,&pstFbcBuf);
}
/*
 * FBC_CORE_print_status - Prints the values of the isp fbc core module registers.
 */
#ifdef _USE_V4L2
#define FBC_CORE_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev,"###FBC_CORE" #name "=0x%08x\n", \
		isp_reg_readl(isp, ISP_IOMEM_FBC_CORE, name))
#else
#define FBC_CORE_PRINT_REGISTER(isp, name)\
	printf("###FBC_CORE" #name "=0x%08x\n", \
		isp_reg_readl(isp, ISP_IOMEM_FBC_CORE, name))
#endif

void Fbc_Core_print_status(struct isp_fbc_device *fbc)
{
	struct isp_device *isp = to_isp_device(fbc);
#ifdef _USE_V4L2
	dev_dbg(isp->dev,"-------------ISP FBC CORE Register dump start----------\n");
#else
	printf("-------------ISP FBC CORE Register dump start----------\n");
#endif	
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_INPUT_SIZE               );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_OUT_FORMAT               );
																		
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_DATA_BASE_ADDR_0       );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_DATA_BASE_ADDR_1       );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_DATA_LINE_STRIDE       );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_DATA_WR_BLENGTH        );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_HEAD_DATA_BASE_ADDR_0  );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_HEAD_DATA_BASE_ADDR_1  );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_HEAD_DATA_LINE_STRIDE  );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_Y_HEAD_DATA_WR_BLENGTH   );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_DATA_BASE_ADDR_0      );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_DATA_BASE_ADDR_1      );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_DATA_LINE_STRIDE      );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_DATA_WR_BLENGTH       );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_HEAD_DATA_BASE_ADDR_0 );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_HEAD_DATA_BASE_ADDR_1 );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_HEAD_DATA_LINE_STRIDE );
	FBC_CORE_PRINT_REGISTER(isp,FBC_CORE_UV_HEAD_DATA_WR_BLENGTH  );
#ifdef _USE_V4L2
	dev_dbg(isp->dev,"-------------ISP FBC CORE Register dump end----------\n");
#else
  	printf("-------------ISP FBC CORE Register dump end----------\n");
#endif
}

#ifdef _USE_V4L2
static void fbc_apply_controls(struct isp_fbc_device *fbc)
{
	if (fbc->update & FBC_WRAP_CONFIG_DONE) {
		fbc_configure_done(fbc);
		fbc->update &= ~FBC_WRAP_CONFIG_DONE;
	}
}

static int fbc_isr_buffer(struct isp_fbc_device *fbc)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&fbc->subdev.entity);
	struct isp_device *isp = to_isp_device(fbc);
	struct isp_buffer *buffer;

	/* The fbc generates done interrupts even when disabled (the datasheet
	 * doesn't explicitly state if that's supposed to happen or not, so it
	 * can be considered as a hardware bug or as a feature, but we have to
	 * deal with it anyway). Disabling the fbc when no buffer is available
	 * would thus not be enough, we need to handle the situation explicitly.
	 */
	if (list_empty(&fbc->video_out.dmaqueue))
		return 0;

	/* We're in continuous mode, and memory writes were disabled due to a
	 * buffer underrun. Reenable them now that we have a buffer. The buffer
	 * address has been set in ccdc_video_queue.
	 */
	if (fbc->state == ISP_PIPELINE_STREAM_CONTINUOUS && fbc->underrun) {
		fbc->underrun = 0;
		return 1;
	}

	buffer = canaanisp_video_buffer_next(&ccdc->video_out);
	if (buffer != NULL)
		fbc_set_outaddr(fbc, buffer->dma);

	pipe->state |= ISP_PIPELINE_IDLE_OUTPUT;

	return buffer != NULL;
}

/*
 * fbc_ydone_isr - Handle YDONE event
 * @ccdc: Pointer to ISP fbc device.
 *
 * Executes BUFFER  before next frame starts.
 */
static void fbc_ydone_isr(struct isp_fbc_device *fbc)
{
	unsigned long flags;
	int restart = 0;

	if (fbc->output & FBC_OUTPUT_MEM)
		restart = fbc_isr_buffer(fbc);

	spin_lock_irqsave(&fbc->lock, flags);
	if (!fbc->shadow_update)
		fbc_apply_controls(fbc);
	spin_unlock_irqrestore(&fbc->lock, flags);

	if (restart)
		fbc_enable(fbc);
}
/*
 * isp_fbc_isr - Configure fbc during interframe time.
 * @ccdc: Pointer to ISP fbc device.
 * @events: fbc events
 */
int isp_fbc_isr(struct isp_fbc_device *fbc,u32 events)
{
	if (fbc->state == ISP_PIPELINE_STREAM_STOPPED)
		return 0;

	if (events & FBC_INT_ST_Y_DONE)
		fbc_ydone_isr(fbc);

	return 0;
}
/* -----------------------------------------------------------------------------
 * ISP video operations
 -----------------------------------------------------------------------------*/

static int fbc_video_queue(struct isp_video *video, struct isp_buffer *buffer)
{
	struct isp_fbc_device *fbc = &video->isp->isp_fbc;
	unsigned long flags;
	bool restart = false;

	if (!(fbc->output & FBC_OUTPUT_MEM))
		return -ENODEV;

	fbc_set_outaddr(fbc, buffer->dma);

	/* We now have a buffer queued on the output, restart the pipeline
	 * on the next fbc interrupt if running in continuous mode (or when
	 * starting the stream) in external sync mode, or immediately in BT.656
	 * sync mode as no fbc interrupt is generated when the fbc is stopped
	 * in that case.
	 */
	spin_lock_irqsave(&fbc->lock, flags);
	if (fbc->state == ISP_PIPELINE_STREAM_CONTINUOUS && !fbc->running)
		restart = true;
	else
		fbc->underrun = 1;
	spin_unlock_irqrestore(&fbc->lock, flags);

	if (restart)
		fbc_enable(fbc);

	return 0;
}

static const struct isp_video_operations isp_fbc_video_ops = {
	.queue = fbc_video_queue,
};
/* -----------------------------------------------------------------------------
 * V4L2 subdev operations
 -----------------------------------------------------------------------------*/
/*
 * fbc_ioctl - FBC module private ioctl's
 * @sd: ISP fbc V4L2 subdevice
 * @cmd: ioctl command
 * @arg: ioctl argument
 *
 * Return 0 on success or a negative error code otherwise.
 */
static long fbc_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	int ret;

	switch (cmd) {
	case VIDIOC_ISP_FBC_WRAP_CFG:
		mutex_lock(&fbc->ioctl_lock);
		ret = fbc_wrap_config(fbc, arg);
		mutex_unlock(&fbc->ioctl_lock);
		break;
	case VIDIOC_ISP_FBC_CORE_CFG:
		mutex_lock(&fbc->ioctl_lock);
		ret = FBC_CORE_config(fbc, arg);
		mutex_unlock(&fbc->ioctl_lock);
		break;
	default:
		return -ENOIOCTLCMD;
	}

	return ret;
}

static int fbc_subscribe_event(struct v4l2_subdev *sd, struct v4l2_fh *fh,
				struct v4l2_event_subscription *sub)
{
	if (sub->type != V4L2_EVENT_FRAME_SYNC)
		return -EINVAL;

	/* line number is zero at frame start */
	if (sub->id != 0)
		return -EINVAL;

	return v4l2_event_subscribe(fh, sub, ISP_FBC_NEVENTS, NULL);
}

static int fbc_unsubscribe_event(struct v4l2_subdev *sd, struct v4l2_fh *fh,
				  struct v4l2_event_subscription *sub)
{
	return v4l2_event_unsubscribe(fh, sub);
}
/*
 * fbc_set_stream - Enable/Disable streaming on the fbc module
 * @sd: ISP fbc V4L2 subdevice
 * @enable: Enable/disable stream
 *
 * When writing to memory, the fbc hardware can't be enabled without a memory
 * buffer to write to. As the s_stream operation is called in response to a
 * STREAMON call without any buffer queued yet, just update the enabled field
 * and return immediately. The fbc will be enabled in fbc_isr_buffer().
 *
 * When not writing to memory enable the fbc immediately.
 */
static int fbc_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct isp_device *isp = to_isp_device(fbc);
	int ret = 0;

	if (fbc->state == ISP_PIPELINE_STREAM_STOPPED) {
		if (enable == ISP_PIPELINE_STREAM_STOPPED)
			return 0;

		//ccdc_configure(ccdc);

		//ccdc_print_status(ccdc);
        fbc_wrap_print_status(fbc);
        fbc_core_print_status(fbc);
	}

	switch (enable) {
	case ISP_PIPELINE_STREAM_CONTINUOUS:
		fbc_enable(fbc);
		fbc->underrun = 0;
		break;
	case ISP_PIPELINE_STREAM_STOPPED:
		ret = fbc_disable(fbc);
		fbc->underrun = 0;
		break;
	}

	fbc->state = enable;
	return ret;
}

static struct v4l2_mbus_framefmt *
__fbc_get_format(struct isp_fbc_device *fbc, struct v4l2_subdev_pad_config *cfg,
		  unsigned int pad, enum v4l2_subdev_format_whence which)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_format(&fbc->subdev, cfg, pad);
	else
		return &fbc->formats[pad];
}

static struct v4l2_rect *
__fbc_get_crop(struct isp_fbc_device *fbc, struct v4l2_subdev_pad_config *cfg,
		enum v4l2_subdev_format_whence which)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_crop(&fbc->subdev, cfg,FBC_OUTPUT_MEM);
	else
		return &fbc->crop;
}
/*
 * fbc_enum_mbus_code - Handle pixel format enumeration
 * @sd     : pointer to v4l2 subdev structure
 * @cfg : V4L2 subdev pad configuration
 * @code   : pointer to v4l2_subdev_mbus_code_enum structure
 * return -EINVAL or zero on success
 */
static int fbc_enum_mbus_code(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_mbus_code_enum *code)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	switch (code->pad) {
	case FBC_PAD_SINK:
		if (code->index >= ARRAY_SIZE(fbc_fmts))
			return -EINVAL;

		code->code = fbc_fmts[code->index];
		break;

	case FBC_OUTPUT_MEM:
		format = __fbc_get_format(fbc, cfg, code->pad,
					   code->which);

		if (format->code == MEDIA_BUS_FMT_YUYV8_2X8 ||
		    format->code == MEDIA_BUS_FMT_UYVY8_2X8) {
			/* In YUV mode the FBC can swap bytes. */
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

static int fbc_enum_frame_size(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_size_enum *fse)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt format;

	if (fse->index != 0)
		return -EINVAL;

	format.code = fse->code;
	format.width = 1;
	format.height = 1;
	fbc_try_format(fbc, cfg, fse->pad, &format, fse->which);
	fse->min_width = format.width;
	fse->min_height = format.height;

	if (format.code != fse->code)
		return -EINVAL;

	format.code = fse->code;
	format.width = -1;
	format.height = -1;
	fbc_try_format(fbc, cfg, fse->pad, &format, fse->which);
	fse->max_width = format.width;
	fse->max_height = format.height;

	return 0;
}
/*
 * fbc_get_format - Retrieve the video format on a pad
 * @sd : ISP fbc V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL if the pad is invalid or doesn't correspond
 * to the format type.
 */
static int fbc_get_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = __fbc_get_format(fbc, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	fmt->format = *format;
	return 0;
}

/*
 * fbc_set_format - Set the video format on a pad
 * @sd : ISP fbc V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @fmt: Format
 *
 * Return 0 on success or -EINVAL if the pad is invalid or doesn't correspond
 * to the format type.
 */
static int fbc_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *fmt)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	format = __fbc_get_format(fbc, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	fbc_try_format(fbc, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == FBC_PAD_SINK) {
		/* Reset the crop rectangle. */
		crop = __fbc_get_crop(fbc, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->format.width;
		crop->height = fmt->format.height;

		fbc_try_crop(fbc, &fmt->format, crop);

		/* Update the source formats. */
		format = __fbc_get_format(fbc, cfg, FBC_PAD_SOURCE_MEM,
					   fmt->which);
		*format = fmt->format;
		fbc_try_format(fbc, cfg, FBC_PAD_SOURCE_MEM, format,
				fmt->which);
	}

	return 0;
}
/*
 * fbc_get_selection - Retrieve a selection rectangle on a pad
 * @sd: ISP fbc V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangles are the crop rectangles on the output formatter
 * source pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
static int fbc_get_selection(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_selection *sel)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	if (sel->pad != FBC_PAD_SOURCE_MEM)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = INT_MAX;
		sel->r.height = INT_MAX;

		format = __fbc_get_format(fbc, cfg, FBC_PAD_SINK, sel->which);
		fbc_try_crop(fbc, format, &sel->r);
		break;

	case V4L2_SEL_TGT_CROP:
		sel->r = *__fbc_get_crop(fbc, cfg, sel->which);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}
/*
 * fbc_set_selection - Set a selection rectangle on a pad
 * @sd: ISP fbc V4L2 subdevice
 * @cfg: V4L2 subdev pad configuration
 * @sel: Selection rectangle
 *
 * The only supported rectangle is the actual crop rectangle on the output
 * formatter source pad.
 *
 * Return 0 on success or a negative error code otherwise.
 */
static int fbc_set_selection(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_selection *sel)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;


	return 0;
}
/*
*
*/
static int fbc_link_validate(struct v4l2_subdev *sd,
			      struct media_link *link,
			      struct v4l2_subdev_format *source_fmt,
			      struct v4l2_subdev_format *sink_fmt)
{
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	unsigned long parallel_shift;

	/* Check if the two ends match */
	if (source_fmt->format.width != sink_fmt->format.width ||
	    source_fmt->format.height != sink_fmt->format.height)
		return -EPIPE;


	return 0;
}
/*
 * fbc_init_formats - Initialize formats on all pads
 * @sd: ISP fbc V4L2 subdevice
 * @fh: V4L2 subdev file handle
 *
 * Initialize all pad formats with default values. If fh is not NULL, try
 * formats are initialized on the file handle. Otherwise active formats are
 * initialized on the device.
 */
static int fbc_init_formats(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct v4l2_subdev_format format;

	memset(&format, 0, sizeof(format));
	format.pad = FBC_PAD_SINK;
	format.which = fh ? V4L2_SUBDEV_FORMAT_TRY : V4L2_SUBDEV_FORMAT_ACTIVE;
	format.format.code = MEDIA_BUS_FMT_SGRBG10_1X10;
	format.format.width = 4096;
	format.format.height = 4096;
	fbc_set_format(sd, fh ? fh->pad : NULL, &format);

	return 0;
}
/* V4L2 subdev core operations */
static const struct v4l2_subdev_core_ops fbc_v4l2_core_ops = {
	.ioctl = fbc_ioctl,
	.subscribe_event = fbc_subscribe_event,
	.unsubscribe_event = fbc_unsubscribe_event,
};

/* V4L2 subdev video operations */
static const struct v4l2_subdev_video_ops fbc_v4l2_video_ops = {
	.s_stream = fbc_set_stream,
};

/* V4L2 subdev pad operations */
static const struct v4l2_subdev_pad_ops fbc_v4l2_pad_ops = {
	.enum_mbus_code = fbc_enum_mbus_code,
	.enum_frame_size = fbc_enum_frame_size,
	.get_fmt = fbc_get_format,
	.set_fmt = fbc_set_format,
	.get_selection = fbc_get_selection,
	.set_selection = fbc_set_selection,
	.link_validate = fbc_link_validate,
};

/* V4L2 subdev operations */
static const struct v4l2_subdev_ops fbc_v4l2_ops = {
	.core = &fbc_v4l2_core_ops,
	.video = &fbc_v4l2_video_ops,
	.pad = &fbc_v4l2_pad_ops,
};

/* V4L2 subdev internal operations */
static const struct v4l2_subdev_internal_ops fbc_v4l2_internal_ops = {
	.open = fbc_init_formats,
};
/* -----------------------------------------------------------------------------
 * Media entity operations
 -----------------------------------------------------------------------------*/
/*
 * fbc_link_setup - Setup fbc connections
 * @entity: fbc media entity
 * @local: Pad at the local end of the link
 * @remote: Pad at the remote end of the link
 * @flags: Link flags
 *
 * return -EINVAL or zero on success
 */
static int fbc_link_setup(struct media_entity *entity,
			   const struct media_pad *local,
			   const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct isp_fbc_device *fbc = v4l2_get_subdevdata(sd);
	struct isp_device *isp = to_isp_device(fbc);

	switch (local->index | media_entity_type(remote->entity)) {
	case FBC_PAD_SINK | MEDIA_ENT_T_V4L2_SUBDEV:
		/* Read from the sensor (parallel interface), CCP2, CSI2a or
		 * CSI2c.
		 */
		if (!(flags & MEDIA_LNK_FL_ENABLED)) {
			fbc->input = FBC_INPUT_NONE;
			break;
		}

		if (fbc->input != FBC_INPUT_NONE)
			return -EBUSY;

		if (remote->entity == &isp->isp_f2k.subdev.entity)
			fbc->input = FBC_INPUT_F2k;
		else if (remote->entity == &isp->isp_r2k.subdev.entity)
			fbc->input = FBC_INPUT_R2k;
		else
			fbc->input = FBC_INPUT_NONE;

		break;

	/*
	 * The ISP core doesn't support pipelines with multiple video outputs.
	 * Revisit this when it will be implemented, and return -EBUSY for now.
	 */

	case FBC_PAD_SOURCE_MEM | MEDIA_ENT_T_V4L2_SUBDEV:
		/* Write to preview engine, histogram and H3A. When none of
		 * those links are active, the video port can be disabled.
		 */
		if (flags & MEDIA_LNK_FL_ENABLED) {
			if (fbc->output & ~FBC_OUTPUT_MEM)
				return -EBUSY;
			fbc->output |= FBC_OUTPUT_MEM;
		} else {
			fbc->output &= ~FBC_OUTPUT_MEM;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
/* media operations */
static const struct media_entity_operations fbc_media_ops = {
	.link_setup = fbc_link_setup,
	.link_validate = v4l2_subdev_link_validate,
};

void isp_fbc_unregister_entities(struct isp_fbc_device *fbc)
{
	v4l2_device_unregister_subdev(&fbc->subdev);
	isp_video_unregister(&fbc->video_out);
}

int isp_fbc_register_entities(struct isp_fbc_device *fbc,
	struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev and video node. */
	ret = v4l2_device_register_subdev(vdev, &fbc->subdev);
	if (ret < 0)
		goto error;

	ret = isp_video_register(&fbc->video_out, vdev);
	if (ret < 0)
		goto error;

	return 0;

error:
	isp_fbc_unregister_entities(fbc);
	return ret;
}
/* -----------------------------------------------------------------------------
 * ISP fbc initialisation and cleanup
 -----------------------------------------------------------------------------*/

/*
 * isp_fbc_init_entities - Initialize V4L2 subdev and media entity
 * @isp_fbc: ISP fbc module
 *
 * Return 0 on success and a negative error code on failure.
 */
static int isp_fbc_init_entities(struct isp_fbc_device *fbc)
{
	struct v4l2_subdev *sd = &fbc->subdev;
	struct media_pad *pads = fbc->pads;
	struct media_entity *me = &sd->entity;
	int ret;

	fbc->input = FBC_INPUT_NONE;

	v4l2_subdev_init(sd, &fbc_v4l2_ops);
	sd->internal_ops = &fbc_v4l2_internal_ops;
	strlcpy(sd->name, "CANAAN ISP FBC", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for isp subdevs */
	v4l2_set_subdevdata(sd, fbc);
	sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[FBC_PAD_SINK].flags = MEDIA_PAD_FL_SINK
				    | MEDIA_PAD_FL_MUST_CONNECT;
	pads[FBC_PAD_SOURCE_MEM].flags = MEDIA_PAD_FL_SOURCE;

	me->ops = &fbc_media_ops;
	ret = media_entity_init(me, FBC_PADS_NUM, pads, 0);
	if (ret < 0)
		return ret;

	fbc_init_formats(sd, NULL);

	fbc->video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fbc->video_out.ops = &fbc_video_ops;
	fbc->video_out.isp = to_isp_device(fbc);
	fbc->video_out.capture_mem = PAGE_ALIGN(4096 * 4096) * 3;
	fbc->video_out.bpl_alignment = 32;

	ret = isp_video_init(&fbc->video_out, "ISP_FBC");
	if (ret < 0)
		goto error_video;

	/* Connect the FBC subdev to the video node. */
	ret = media_entity_create_link(&fbc->subdev.entity, FBC_PAD_SOURCE_MEM,
			&fbc->video_out.video.entity, 0, 0);
	if (ret < 0)
		goto error_link;

	return 0;

error_link:
	canaanisp_video_cleanup(&fbc->video_out);
error_video:
	media_entity_cleanup(me);
	return ret;
}
/*
 * isp_fbc_init - FBC module initialization.
 * @isp: Device pointer specific to the OMAP3 ISP.
 *
 * TODO: Get the initialisation values from platform data.
 *
 * Return 0 on success or a negative error code otherwise.
 */
int isp_fbc_init(struct isp_device *isp)
{
	struct isp_fbc_device *fbc = &isp->fbc;
	int ret;

	spin_lock_init(&fbc->lock);
	init_waitqueue_head(&fbc->wait);
	mutex_init(&fbc->ioctl_lock);

	//fbc->stopping = CCDC_STOP_NOT_REQUESTED;

	ret = isp_fbc_init_entities(fbc);
	if (ret < 0) {
		mutex_destroy(&fbc->ioctl_lock);
		return ret;
	}

	return 0;
}
/*
 * isp_fbc_cleanup - FBC module cleanup.
 * @isp: Device pointer specific to the OMAP3 ISP.
 */
void isp_fbc_cleanup(struct isp_device *isp)
{
	struct isp_fbc_device *fbc = &isp->fbc;

	isp_video_cleanup(&fbc->video_out);
	media_entity_cleanup(&fbc->subdev.entity);

	if (fbc->fpc.addr != NULL)
		dma_free_coherent(isp->dev, fbc->fpc.fpnum * 1, fbc->fpc.addr,
				  fbc->fpc.dma);

	mutex_destroy(&fbc->ioctl_lock);
}
#endif