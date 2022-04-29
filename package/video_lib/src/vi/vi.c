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
/******************************************************************************
  File Name     : vi.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file
******************************************************************************/
#include "isp_com.h"

#include "vi/vi.h"
#include "vi/vi_com.h"
#include "vi/wrap/vi_wrap_reg.h"
#include "vi/wrap/vi_wrap_drv.h"
#include "vi/pipe/vi_pipe_reg.h"
#include "vi/pipe/vi_pipe_drv.h"

extern unsigned int reg_vi_pipe_base[];
/**************************************************************************************
 * debug registers
 * ***********************************************************************************/
/*
 * isp_vi_wrap_print_status - Prints the values of the isp vi wrap module registers.
 */
#ifdef _USE_V4L2
#define VI_WRAP_PRINT_REGISTER(isp, name)\
	dev_dbg(isp->dev, "###ISP_VI_WRAP" #name "=0x%08x\n", \
		isp_reg_readl(isp, VI_WRAP_BASE, name))
#else
#define VI_WRAP_PRINT_REGISTER(isp, name)\
    printf("###ISP_VI_WRAP" #name "=0x%08x\n",isp_reg_readl(isp, VI_WRAP_BASE,name))
#endif
void isp_vi_wrap_print_status(struct vi_device *vi)
{
	struct isp_device *isp = to_isp_device(vi);
#ifdef _USE_V4L2
	dev_dbg(isp->dev, "-------------VI WRAP Register dump start----------\n");
#else
    printf("-------------VI WRAP Register dump start----------\n");
#endif	
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_SWRST_CTL);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_CSI_MODE_CTL);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_ISP_CH_SEL);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_CLOCK_CTL);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_ARB_MODE);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_WR_WEIGHT_0);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_WR_WEIGHT_1);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_RD_WEIGHT_0);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_RD_WEIGHT_1);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_WR_PRIORITY);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_RD_PRIORITY);
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_WR_CH_ID   );
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_RD_CH_ID   );
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_DMA_AXI_CTL    );
	VI_WRAP_PRINT_REGISTER(isp,VI_WRAP_CONFIG_CTL     );
	VI_WRAP_PRINT_REGISTER(isp,VI_WARP_INT_CTL     	);
#ifdef _USE_V4L2   
    dev_dbg(isp->dev, "-------------VI WRAP Register dump end----------\n");
#else
    printf("-------------VI WRAP Register dump end----------\n");
#endif
}
#ifdef _USE_V4L2
#define VI_PIPE_PRINT_REGISTER(isp,s8Index,name)\
	dev_dbg(isp->dev, "###ISP_VI_PIPE" #s8Index "=0x%08x" #name "=0x%08x\n", \
		isp_reg_readl(isp,reg_vi_pipe_base[s8Index],name))
#else
#define VI_PIPE_PRINT_REGISTER(isp,s8Index,name)\
    printf("###ISP_VI_PIPE" #s8Index "=0x%08x" #name "=0x%08x\n", \
		isp_reg_readl(isp,reg_vi_pipe_base[s8Index],name)) 
#endif
void isp_vi_pipe_print_status(struct vi_device *vi)
{
	struct isp_device *isp = to_isp_device(vi);
#ifdef _USE_V4L2  
	dev_dbg(isp->dev, "-------------VI PIPE Register dump start----------\n");
#else
    printf("-------------VI PIPE Register dump start----------\n");
#endif
	unsigned char s8Index = VI_MIPI_CSI00_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);
	s8Index = VI_MIPI_CSI01_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);
	s8Index = VI_MIPI_CSI02_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);   
	s8Index = VI_MIPI_CSI10_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			); 
	s8Index = VI_MIPI_CSI11_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);
	s8Index = VI_MIPI_CSI12_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);
	s8Index = VI_DVP_0_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);
	s8Index = VI_DVP_1_PIPE_ID;
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CTRL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TIMING_CTRL    		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_SYNC_WIDTH     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_TOTAL   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_SIZE_ACTIVE  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_IMAGE_START     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_Y   	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR0_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_FRM_BASE_ADDR1_UV  	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_LINE_STRIDE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_DMA_CTL     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_CTL     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_TOF     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_TOTAL     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_SIZE_ACTIVE    	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_START     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR0_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_FRM_BASE_ADDR1_Y   );
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_TPG_LINE_STRIDE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_MODE     			);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_ERROR_MODE     	);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_DMA_RST_REQ     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_CONFIG_DONE     		);
	VI_PIPE_PRINT_REGISTER(isp,s8Index,VI_PIPE_INT_CTL     			);
#ifdef _USE_V4L2  
    dev_dbg(isp->dev, "-------------VI PIPE Register dump end----------\n");
#else
    printf("-------------VI PIPE Register dump end----------\n");
#endif
}

void vi_wrap_rst(struct isp_device *isp)
{
	printf("vi_wrap_rst\n");
    ISP_CHECK_POINTER(isp);
    VI_WRAP_RESET_CTL_S pstRstCtl;
    pstRstCtl.csi_00_rst_en    = VI_WRAP_SW_RST_EN;
    pstRstCtl.csi_01_rst_en    = VI_WRAP_SW_RST_EN;
    pstRstCtl.csi_02_rst_en    = VI_WRAP_SW_RST_EN;
    pstRstCtl.csi_10_rst_en    = VI_WRAP_SW_RST_EN;
    pstRstCtl.csi_11_rst_en    = VI_WRAP_SW_RST_EN;
    pstRstCtl.csi_12_rst_en    = VI_WRAP_SW_RST_EN;
    pstRstCtl.dvp_0_rst_en     = VI_WRAP_SW_RST_EN;
    pstRstCtl.dvp_1_rst_en     = VI_WRAP_SW_RST_EN;
    pstRstCtl.axi_wr_ch_rst_en = VI_WRAP_SW_RST_EN;
    pstRstCtl.axi_rd_ch_rst_en = VI_WRAP_SW_RST_EN;    
    VI_DRV_WRAP_SetRst(isp,&pstRstCtl);
}

void vi_wrap_config_dma(struct isp_device *isp,VI_WRAP_DMA_ATTR_S *pstDmaAttr)
{
    ISP_CHECK_POINTER(isp);
    ISP_CHECK_POINTER(pstDmaAttr);

	VI_WRAP_DMA_ARB_MODE_S *stDmaArbMode = &pstDmaAttr->stDmaArbMode;
	stDmaArbMode->wr_dma_arb_mode = 0;//1;
	stDmaArbMode->rd_dma_arb_mode = 0;//1;

	VI_WRAP_DMA_WR_WEIGHT_0_S  *stWrChWeight0 = &pstDmaAttr->stWrChWeight0;
	stWrChWeight0->vi_dma_ch0_wr_weight = 1;
	stWrChWeight0->vi_dma_ch1_wr_weight = 1;
	stWrChWeight0->vi_dma_ch2_wr_weight = 1;
	stWrChWeight0->vi_dma_ch3_wr_weight = 1;
	VI_WRAP_DMA_WR_WEIGHT_1_S  *stWrChWeight1 = &pstDmaAttr->stWrChWeight1;
	stWrChWeight1->vi_dma_ch4_wr_weight = 1;
	stWrChWeight1->vi_dma_ch5_wr_weight = 1;
	stWrChWeight1->vi_dma_ch6_wr_weight = 1;
	stWrChWeight1->vi_dma_ch7_wr_weight = 1;
    VI_WRAP_DMA_RD_WEIGHT_0_S  *stRdChWeight0 = &pstDmaAttr->stRdChWeight0;
	stRdChWeight0->vi_dma_ch0_rd_weight = 1;
	stRdChWeight0->vi_dma_ch1_rd_weight = 1;
	stRdChWeight0->vi_dma_ch2_rd_weight = 1;
	stRdChWeight0->vi_dma_ch3_rd_weight = 1;
	VI_WRAP_DMA_RD_WEIGHT_1_S  *stRdChWeight1 = &pstDmaAttr->stRdChWeight1;
	stRdChWeight1->vi_dma_ch4_rd_weight = 1;
	stRdChWeight1->vi_dma_ch5_rd_weight = 1;
	stRdChWeight1->vi_dma_ch6_rd_weight = 1;
	stRdChWeight1->vi_dma_ch7_rd_weight = 1;
    VI_WRAP_DMA_WR_PRIORITY_S  *stWrChPriority = &pstDmaAttr->stWrChPriority;
	stWrChPriority->vi_dma_ch0_wr_priority = 7;//0;
	stWrChPriority->vi_dma_ch1_wr_priority = 6;//1;
	stWrChPriority->vi_dma_ch2_wr_priority = 5;//2;
	stWrChPriority->vi_dma_ch3_wr_priority = 4;//3;
	stWrChPriority->vi_dma_ch4_wr_priority = 3;//4;
	stWrChPriority->vi_dma_ch5_wr_priority = 2;//5;
	stWrChPriority->vi_dma_ch6_wr_priority = 1;//6;
	stWrChPriority->vi_dma_ch7_wr_priority = 0;//7;
    VI_WRAP_DMA_RD_PRIORITY_S  *stRdChPriority = &pstDmaAttr->stRdChPriority;
	stRdChPriority->vi_dma_ch0_rd_priority = 7;//0;
	stRdChPriority->vi_dma_ch1_rd_priority = 6;//1;
	stRdChPriority->vi_dma_ch2_rd_priority = 5;//2;
	stRdChPriority->vi_dma_ch3_rd_priority = 4;//3;
	stRdChPriority->vi_dma_ch4_rd_priority = 3;//4;
	stRdChPriority->vi_dma_ch5_rd_priority = 2;//5;
	stRdChPriority->vi_dma_ch6_rd_priority = 1;//6;
	stRdChPriority->vi_dma_ch7_rd_priority = 0;//7;
    VI_WRAP_DMA_WR_CH_ID_S     *stWriteChId = &pstDmaAttr->stWriteChId;
	stWriteChId->vi_dma_wr_ch0_id = 0;
	stWriteChId->vi_dma_wr_ch1_id = 1;
	stWriteChId->vi_dma_wr_ch2_id = 2;
	stWriteChId->vi_dma_wr_ch3_id = 3;
	stWriteChId->vi_dma_wr_ch4_id = 4;
	stWriteChId->vi_dma_wr_ch5_id = 5;
	stWriteChId->vi_dma_wr_ch6_id = 6;
	stWriteChId->vi_dma_wr_ch7_id = 7;
    VI_WRAP_DMA_RD_CH_ID_S     *stReadChId = &pstDmaAttr->stReadChId;	
	stReadChId->vi_dma_rd_ch0_id = 0;
	stReadChId->vi_dma_rd_ch1_id = 1;
	stReadChId->vi_dma_rd_ch2_id = 2;
	stReadChId->vi_dma_rd_ch3_id = 3;
	stReadChId->vi_dma_rd_ch4_id = 4;
	stReadChId->vi_dma_rd_ch5_id = 5;
	stReadChId->vi_dma_rd_ch6_id = 6;
	stReadChId->vi_dma_rd_ch7_id = 7; 
    VI_DRV_WRAP_SetDmaAttr(isp,pstDmaAttr);
}

void vi_wrap_config(struct vi_device *vi)
{
	printf("vi_wrap_config start\n");
    ISP_CHECK_POINTER(vi);
    struct isp_device *isp = to_isp_device(vi);
	printf("struct isp_device = 0x%x,vi= 0x%x\n",isp,vi);
    struct vi_wrap_cfg_info  *vi_wrap_cfg = &vi->vi_wrap_cfg;
    SENSOR_INFO *mipi0Info = &vi_wrap_cfg->sensor_info[MIPI0];
    SENSOR_INFO *mipi1Info = &vi_wrap_cfg->sensor_info[MIPI1];
    SENSOR_INFO   *dvpInfo = &vi_wrap_cfg->sensor_info[DVP0];
    vi_wrap_rst(isp);
    VI_WRAP_CSI_MODE_CTL_S pstCsiModeCtl;
    pstCsiModeCtl.mipi_csi_0_mode = NORMAL_MODE;
    pstCsiModeCtl.mipi_csi_1_mode = NORMAL_MODE;
    pstCsiModeCtl.mipi_dphy_mode = TWO_LANES_MODE;
    pstCsiModeCtl.mipi_csi01_dbg_sel = CSI0_DEBUG_INFO;
    pstCsiModeCtl.isp_4k_clk_sel = F_CSI_0_CLK;
    pstCsiModeCtl.isp_2k_clk_sel = F_CSI_0_CLK;
    pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_CSI_1_CLK;
    pstCsiModeCtl.tof_clk_sel = R_TOF_CSI_1_CLK;
    pstCsiModeCtl.csi_0_sony_dol_en = SONY_POL_MODE_DIS;
    pstCsiModeCtl.dvp_clk_0_mode = DVP_RAISE_EGDE;
	if( ENABLE == mipi0Info->sensor_interface_en)
	{
		if( ENABLE == mipi0Info->tpg_w_en)
		{
			pstCsiModeCtl.mipi_csi_0_mode = DEBUG_MODE;
		}
    	if(SONY_WDR_SENSOR == mipi0Info->wdr_sensor_vendor)
		{
			if(( ISP_PIPE_WDR_2_FRAME == mipi0Info->wdr_mode) ||(ISP_PIPE_WDR_3_FRAME == mipi0Info->wdr_mode))
			{
				pstCsiModeCtl.csi_0_sony_dol_en = SONY_POL_MODE_EN;
			}			
		}
		if( ISP_F_2K == mipi0Info->isp_pipeline)
		{
			pstCsiModeCtl.isp_2k_clk_sel = F_CSI_0_CLK;
			if(ENABLE == mipi0Info->tpg_r_en)
			{
				pstCsiModeCtl.isp_2k_clk_sel = F_DPG_CLK;
			}
		}
		else if(ISP_R_2K == mipi0Info->isp_pipeline)
		{
			pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_CSI_0_CLK;
			if(ENABLE == mipi0Info->tpg_r_en)
			{
				pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_DPG_CLK;
			}		
		}
		else if(ISP_TOF == mipi0Info->isp_pipeline)
		{
			pstCsiModeCtl.tof_clk_sel = R_TOF_CSI_0_CLK;
			if(ENABLE == mipi0Info->tpg_r_en)
			{
				pstCsiModeCtl.tof_clk_sel = R_TOF_DPG_CLK;
			}	
		}
	}
	if( ENABLE == mipi1Info->sensor_interface_en)
	{
		if( ISP_F_2K == mipi1Info->isp_pipeline)
		{
			pstCsiModeCtl.isp_2k_clk_sel = F_CSI_1_CLK;
			if(ENABLE == mipi1Info->tpg_r_en)
			{
				pstCsiModeCtl.isp_2k_clk_sel = F_DPG_CLK;
			}
		}
		else if(ISP_R_2K == mipi1Info->isp_pipeline)
		{
			pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_CSI_1_CLK;
			if(ENABLE == mipi1Info->tpg_r_en)
			{
				pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_DPG_CLK;
			}		
		}
		else if(ISP_TOF == mipi1Info->isp_pipeline)
		{
			pstCsiModeCtl.tof_clk_sel = R_TOF_CSI_1_CLK;
			if(ENABLE == mipi1Info->tpg_r_en)
			{
				pstCsiModeCtl.tof_clk_sel = R_TOF_DPG_CLK;
			}	
		}
	}
	if(ENABLE == dvpInfo->sensor_interface_en)
	{
		pstCsiModeCtl.dvp_clk_0_mode = DVP_FALLING_EDGE;//RAISE_EGDE; //FALLING_EDGE;//
		if( ISP_F_2K == dvpInfo->isp_pipeline)
		{
			pstCsiModeCtl.isp_2k_clk_sel = F_DVP_0_CLK;//F_DPG_CLK;
			if(ENABLE == dvpInfo->tpg_r_en)
			{
				pstCsiModeCtl.isp_2k_clk_sel = F_DPG_CLK;
			}
		}
		else if(ISP_R_2K == dvpInfo->isp_pipeline)
		{
			pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_DVP_0_CLK;
			if(ENABLE == dvpInfo->tpg_r_en)
			{
				pstCsiModeCtl.isp_r_2k_clk_sel = R_TOF_DPG_CLK;
			}		
		}
		else if(ISP_TOF == dvpInfo->isp_pipeline)
		{
			pstCsiModeCtl.tof_clk_sel = R_TOF_DPG_CLK;
			if(ENABLE == dvpInfo->tpg_r_en)
			{
				pstCsiModeCtl.tof_clk_sel = R_TOF_DPG_CLK;
			}	
		} 
	}
    VI_DRV_WRAP_SetCtlMode(isp,&pstCsiModeCtl);
	VI_WRAP_ISP_CH_SEL_S pstIspChSel;
    pstIspChSel.isp_4k_l_ch_sel = CSI_10_PIPE;
    pstIspChSel.isp_4k_m_ch_sel = CSI_01_PIPE;
    pstIspChSel.isp_4k_s_ch_sel = CSI_02_PIPE;
    pstIspChSel.isp_2k_l_ch_sel = CSI_00_PIPE;
    pstIspChSel.isp_2k_m_ch_sel = CSI_11_PIPE;
    pstIspChSel.isp_2k_s_ch_sel = CSI_12_PIPE;
    pstIspChSel.isp_r_2k_ch_sel = DVP_0_PIPE;
    pstIspChSel.isp_3d_ch_sel   = DVP_1_PIPE;
	if( ENABLE == mipi0Info->sensor_interface_en)
	{
		if( ISP_F_2K == mipi0Info->isp_pipeline)
		{
    		pstIspChSel.isp_2k_l_ch_sel = CSI_00_PIPE;
    		pstIspChSel.isp_2k_m_ch_sel = CSI_01_PIPE;
    		pstIspChSel.isp_2k_s_ch_sel = CSI_02_PIPE;
		}
		else if(ISP_R_2K == mipi0Info->isp_pipeline)
		{
			pstIspChSel.isp_r_2k_ch_sel = CSI_00_PIPE;		
		}
		else if(ISP_TOF == mipi0Info->isp_pipeline)
		{
		    pstIspChSel.isp_3d_ch_sel = CSI_00_PIPE;//CSI_10_PIPE;
		}		
	}
	if( ENABLE == mipi1Info->sensor_interface_en)
	{
		if( ISP_F_2K == mipi1Info->isp_pipeline)
		{
    		pstIspChSel.isp_2k_l_ch_sel = CSI_10_PIPE;
    		pstIspChSel.isp_2k_m_ch_sel = CSI_11_PIPE;
    		pstIspChSel.isp_2k_s_ch_sel = CSI_12_PIPE;
		}
		else if(ISP_R_2K == mipi1Info->isp_pipeline)
		{
			pstIspChSel.isp_r_2k_ch_sel = CSI_10_PIPE;		
		}
		else if(ISP_TOF == mipi1Info->isp_pipeline)
		{
			pstIspChSel.isp_3d_ch_sel = CSI_10_PIPE; 	
		}		
	}
	if( ENABLE == dvpInfo->sensor_interface_en)
	{
		if( ISP_F_2K == dvpInfo->isp_pipeline)
		{
    		pstIspChSel.isp_2k_l_ch_sel = DVP_0_PIPE;
		}
		else if(ISP_R_2K == dvpInfo->isp_pipeline)
		{
			pstIspChSel.isp_r_2k_ch_sel = DVP_0_PIPE;		
		}
		else if(ISP_TOF == dvpInfo->isp_pipeline)
		{
			pstIspChSel.isp_3d_ch_sel = DVP_0_PIPE; 	
		}		
	}
	VI_DRV_WRAP_SetIspChSel(isp,&pstIspChSel);
	VI_WRAP_CLOCK_CTL_S pstClkCtl;
    pstClkCtl.csi_00_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_01_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_02_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_10_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_11_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_12_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.dvp_0_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.dvp_1_pixel_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_00_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_01_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_02_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_10_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_11_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.csi_12_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.dvp_0_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.dvp_1_dma_clk_en = VI_CLK_DIS;
    pstClkCtl.axi_wr_ch_clk_en = VI_CLK_EN;
    pstClkCtl.axi_rd_ch_clk_en = VI_CLK_EN;
	if( ENABLE == mipi0Info->sensor_interface_en)
	{
		pstClkCtl.csi_00_pixel_clk_en = VI_CLK_EN;
		if(( ISP_PIPE_WDR_2_FRAME == mipi0Info->wdr_mode) ||(ISP_PIPE_WDR_3_FRAME == mipi0Info->wdr_mode))
		{
			pstClkCtl.csi_01_pixel_clk_en = VI_CLK_EN;
    		pstClkCtl.csi_02_pixel_clk_en = VI_CLK_EN;
		}
		if((ENABLE == mipi0Info->tpg_w_en ) ||(ENABLE == mipi0Info->tpg_r_en ))
		{
		    pstClkCtl.csi_00_dma_clk_en = VI_CLK_EN;
			pstClkCtl.csi_01_dma_clk_en = VI_CLK_EN;
    		pstClkCtl.csi_02_dma_clk_en = VI_CLK_EN;	
		}
	}
	if( ENABLE == mipi1Info->sensor_interface_en)
	{
		pstClkCtl.csi_10_pixel_clk_en = VI_CLK_EN;
		if((ENABLE == mipi0Info->tpg_w_en ) ||(ENABLE == mipi0Info->tpg_r_en ))
		{
	    	pstClkCtl.csi_10_dma_clk_en = VI_CLK_EN;
		}
	}
	if( ENABLE == dvpInfo->sensor_interface_en)
	{
		pstClkCtl.dvp_0_pixel_clk_en = VI_CLK_EN;
		if((ENABLE == mipi0Info->tpg_w_en ) ||(ENABLE == mipi0Info->tpg_r_en ))
		{
			pstClkCtl.dvp_0_dma_clk_en = VI_CLK_EN;
		}
	}
	VI_DRV_WRAP_SetClockCtl(isp,&pstClkCtl);
	//
	VI_WRAP_DMA_ATTR_S pstDmaAttr;    
	vi_wrap_config_dma(isp,&pstDmaAttr);
	//
    VI_WRAP_INT_EN_S  pstIntEn;
    pstIntEn.csi_0_host_int_en = VI_INT_DIS;    
    pstIntEn.csi_0_host_err_int_en = VI_INT_DIS;
    pstIntEn.csi_1_host_int_en = VI_INT_DIS;    
    pstIntEn.csi_1_host_err_int_en = VI_INT_DIS;
    pstIntEn.csi_0_ctrl_0_int_en = VI_INT_DIS;  
    pstIntEn.csi_0_ctrl_1_int_en = VI_INT_DIS;  
    pstIntEn.csi_0_ctrl_2_int_en = VI_INT_DIS;  
    pstIntEn.dvp_0_ctrl_int_en = VI_INT_DIS;    
    pstIntEn.csi_1_ctrl_0_int_en = VI_INT_DIS;  
    pstIntEn.csi_1_ctrl_1_int_en = VI_INT_DIS;  
    pstIntEn.csi_1_ctrl_2_int_en = VI_INT_DIS;  
    pstIntEn.dvp_1_ctrl_int_en = VI_INT_DIS;       
	VI_DRV_WRAP_SetIntEn(isp,&pstIntEn);
	VI_WRAP_CFG_DONE_S pstWrapCfgDone;
    pstWrapCfgDone.vi_wrap_config_done = 1;
    pstWrapCfgDone.vi_wrap_wp_clr = VI_DONE_WP_EN;    
	VI_DRV_WRAP_SetCfgDone(isp,&pstWrapCfgDone);
	printf("vi_wrap_config end\n");
}
//
void vi_pipe_SetIntEn(struct vi_device *vi,unsigned int s8Index,struct VI_PIPE_INT_EN *int_en)
{
	VI_CHECK_POINTER(vi);
	struct isp_device *isp = to_isp_device(vi);
	VI_PIPE_INT_CTL_S pstIntCtl;
    pstIntCtl.win_ctl_frame_end_en           = VI_INT_DIS; 
    pstIntCtl.emb_ctl_frame_end_en           = VI_INT_DIS; 
    pstIntCtl.emb_ctl_time_out_en            = VI_INT_DIS; 
    pstIntCtl.tpg_ctl_frame_end_en           = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_frame_end_en          = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_ch_line_base_en       = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_ch_err_frame_end_en   = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_ch_err_immediate_en   = VI_INT_DIS; 
    pstIntCtl.dma_uv_wr_ch_frame_end_en      = VI_INT_DIS; 
    pstIntCtl.dma_uv_wr_ch_line_base_en      = VI_INT_DIS; 
    pstIntCtl.dma_uv_wr_ch_err_frame_end_en  = VI_INT_DIS;
    pstIntCtl.dma_uv_wr_ch_err_immediate_en  = VI_INT_DIS;
    pstIntCtl.dma_raw_rd_ch_frame_end_en     = VI_INT_DIS; 
    pstIntCtl.dma_raw_rd_ch_line_base_en     = VI_INT_DIS; 
    pstIntCtl.dma_raw_rd_ch_err_frame_end_en = VI_INT_DIS;
    pstIntCtl.dma_raw_rd_ch_err_immediate_en = VI_INT_DIS;
	VI_DRV_PIPE_SetInt(isp,s8Index,&pstIntCtl);
}
unsigned int vi_pipe_GetIntSts(struct vi_device *vi,unsigned int s8Index)
{
	VI_CHECK_POINTER(vi);
	struct isp_device *isp = to_isp_device(vi);
    return VI_DRV_PIPE_GetPipeIntSts(isp,s8Index);
}
//
void vi_pipe_config(struct vi_device *vi,unsigned int s8Index)
{
	VI_CHECK_POINTER(vi);
	struct isp_device *isp = to_isp_device(vi);
    struct vi_pipe_cfg_info  *vi_pipe_cfg =&vi->vi_pipe_cfg[s8Index];
	VI_PIPE_CTRL_S pstPipeCtl;
    pstPipeCtl.win_mode_en= vi_pipe_cfg->win_mode_en;//TRUE;//1;
    pstPipeCtl.emb_en= FALSE;//0;
    pstPipeCtl.hsync_vsync_out_en= TRUE;//1;
    pstPipeCtl.sensor_input_swap_en= FALSE;//0; 
    pstPipeCtl.isp_vsync_pol= vi_pipe_cfg->isp_vsync_pol;//TRUE;//1;
    pstPipeCtl.isp_hsync_pol= vi_pipe_cfg->isp_hsync_pol;//TRUE;//1;
    pstPipeCtl.isp_field_pol= vi_pipe_cfg->isp_field_pol;//TRUE;//1;
    pstPipeCtl.isp_clk_pol= vi_pipe_cfg->isp_clk_pol;//TRUE;//1;
    pstPipeCtl.sen_mipi_vsync_pol = vi_pipe_cfg->sen_mipi_vsync_pol;//FALSE;//0;//1;
    pstPipeCtl.sen_mipi_hsync_pol = vi_pipe_cfg->sen_mipi_hsync_pol;//FALSE;//0;//1;
    pstPipeCtl.sen_mipi_field_pol = vi_pipe_cfg->sen_mipi_field_pol;//TRUE;//1;
    pstPipeCtl.sen_mipi_clk_pol= vi_pipe_cfg->sen_mipi_clk_pol;//TRUE;//1;
    pstPipeCtl.sync_source_sel= EXTERNAL_SYNC;//0;//1;//0;
    pstPipeCtl.input_ch_sel= vi_pipe_cfg->input_ch_sel;//MIPI_INPUT;//1;
    pstPipeCtl.ch_mode_sel= vi_pipe_cfg->ch_mode_sel;//VI_MIPI_BT1120;//1;
    pstPipeCtl.emb_enable= EMB_DIS;//0;
    pstPipeCtl.emb_mode_sel= EMB_8BIT_656_MODE;//0;
    pstPipeCtl.emb_ecc_mode_en= FALSE;//0;
    pstPipeCtl.sync_code_remove_en= FALSE;//0;
    pstPipeCtl.sync_code_ext_en= FALSE;//0;    
    VI_DRV_PIPE_SetPipeCtl(isp,s8Index, &pstPipeCtl);
	
	VI_PIPE_TIMING_CTRL_S pstTimingCtl;
    pstTimingCtl.input_pixel_type= vi_pipe_cfg->pixel_type ;//SENSOR_INPUT_RAWRGB;//0; /*RAW input*/
    pstTimingCtl.input_yuv_format= vi_pipe_cfg->yuv_in_format;//VI_INPUT_YUV422;//0;
    pstTimingCtl.output_yuv_format= vi_pipe_cfg->yuv_out_format;//VI_OUTPUT_YUV422;//1;
    pstTimingCtl.yuv_order= vi_pipe_cfg->yuv422_order;//VI_YUV422_YUYV;//0;
    pstTimingCtl.raw_pixel_width= vi_pipe_cfg->pixel_width;//PIXEL_WIDTH_12BIT;//1;//2; /*RAW 10bit*/
    pstTimingCtl.data_out_timming_ctrl= vi_pipe_cfg->data_out_timming_ctrl;//CTRL_CYCLE_DELAY_4;//3;//2;//1;//0;//3;/*three cycle delay*/
    pstTimingCtl.sync_mode= SYNC_V_DATA_EN;//4;//6;//5;//3;//2;//1;//0;//4;
    pstTimingCtl.sync_pulse_mode= vi_pipe_cfg->sync_pulse_mode;//0;    
	VI_DRV_PIPE_SetTimingCtl(isp,s8Index,&pstTimingCtl);//
	VI_PIPE_SYNC_WIDTH_S pstSyncWidth;
	pstSyncWidth.image_hsync_width = 0x7;
	pstSyncWidth.image_vsync_width = 0x7;   
	VI_DRV_PIPE_SetSyncWidthCtl(isp,s8Index, &pstSyncWidth);
	VI_PIPE_IMAGE_ATTR_S pstImgAttr;
    pstImgAttr.stImageSizeTotal.image_v_size_total    = vi_pipe_cfg->total_size.Height - 1;
    pstImgAttr.stImageSizeTotal.image_h_size_total    = vi_pipe_cfg->total_size.Width  - 1;
    pstImgAttr.stImageSizeActive.image_v_size_active  = vi_pipe_cfg->in_size.Height - 1;
    pstImgAttr.stImageSizeActive.image_h_size_active  = vi_pipe_cfg->in_size.Width - 1;
    pstImgAttr.stImageStart.image_v_start             = vi_pipe_cfg->w_size_st.Height_st;
    pstImgAttr.stImageStart.image_h_start             = vi_pipe_cfg->w_size_st.Width_st;
	VI_DRV_PIPE_SetImageAttr(isp,s8Index,&pstImgAttr);
	VI_PIPE_TPG_S pstTpg;
    VI_PIPE_BUF_S *stPipeBuf = &pstTpg.stPipeBuf;
    stPipeBuf->y_base_addr0   = vi_pipe_cfg->vi_pipe_w_addr_y0;
    stPipeBuf->y_base_addr1   = vi_pipe_cfg->vi_pipe_w_addr_y1;
    stPipeBuf->y_line_stride  = vi_pipe_cfg->vi_pipe_addr_stride;
    stPipeBuf->uv_base_addr0  = vi_pipe_cfg->vi_pipe_w_addr_uv0;
    stPipeBuf->uv_base_addr1  = vi_pipe_cfg->vi_pipe_w_addr_uv1;
    stPipeBuf->uv_line_stride = vi_pipe_cfg->vi_pipe_addr_stride;
    VI_PIPE_TPG_IMAGE_ATTR_S *stPipeTpgImage = &pstTpg.stPipeTpgImage;
    stPipeTpgImage->stTpgSizeTotal.tpg_vsize_total   = vi_pipe_cfg->total_size.Height -1;
    stPipeTpgImage->stTpgSizeTotal.tpg_hsize_total   = vi_pipe_cfg->total_size.Width -1;
    stPipeTpgImage->stTpgSizeActive.tpg_vsize_active = vi_pipe_cfg->in_size.Height -1;
    stPipeTpgImage->stTpgSizeActive.tpg_hsize_active = vi_pipe_cfg->in_size.Width -1; 
    stPipeTpgImage->stTpgStart.tpg_v_start = vi_pipe_cfg->r_size_st.Height_st;
    stPipeTpgImage->stTpgStart.tpg_h_start = vi_pipe_cfg->r_size_st.Width_st;    
    VI_PIPE_TPG_BUF_S *stPipeTpgBuf = &pstTpg.stPipeTpgBuf;
    stPipeTpgBuf->tpg_y_base_addr0  = vi_pipe_cfg->vi_pipe_r_addr_y0;
    stPipeTpgBuf->tpg_y_base_addr1  = vi_pipe_cfg->vi_pipe_r_addr_y1;
    stPipeTpgBuf->tpg_y_line_stride = vi_pipe_cfg->vi_pipe_addr_stride;  
	VI_DRV_PIPE_SetTpgAttr(isp,s8Index,&pstTpg);
	VI_PIPE_TPG_DMA_CTL_S stTpgDmaCtrl;
    stTpgDmaCtrl.dma_y_module_en      = vi_pipe_cfg->tpg_w_en;
    stTpgDmaCtrl.dma_uv_module_en     = FALSE;
    stTpgDmaCtrl.dma_tpg_read_en      = vi_pipe_cfg->tpg_r_en;
    stTpgDmaCtrl.sync_out_en          = vi_pipe_cfg->tpg_w_en;
    stTpgDmaCtrl.sw_triger_en         = vi_pipe_cfg->tpg_w_en;
    stTpgDmaCtrl.dma_wr_ch_err_dec_en = vi_pipe_cfg->tpg_w_en;
    stTpgDmaCtrl.dma_rd_ch_err_dec_en = vi_pipe_cfg->tpg_r_en;
    VI_DRV_PIPE_SetTpgDmaCtl(isp,s8Index,&stTpgDmaCtrl); 
	VI_PIPE_TPG_CTL_S pstPipeTpgCtl;
    pstPipeTpgCtl.tpg_en                    = vi_pipe_cfg->tpg_r_en;
    pstPipeTpgCtl.tpg_frame_ratio_mode      = 0x0;
    pstPipeTpgCtl.tpg_sync_timing_gen_mode  = 0x1;
    pstPipeTpgCtl.tpg_frame_ratio_fast_slow = 0x1;
	VI_DRV_PIPE_SetIspTpg(isp,s8Index,&pstPipeTpgCtl);
    VI_PIPE_DMA_MODE_S DmaCtrl;
    DmaCtrl.dma_y_outstand   = 0x8;
    DmaCtrl.dma_uv_outstand  = 0x8;
    DmaCtrl.dma_raw_outstand = 0x8;
    DmaCtrl.dma_y_blen       = 0;
    DmaCtrl.dma_uv_blen      = 0;
    DmaCtrl.dma_raw_blen     = 0;
    DmaCtrl.dma_y_uv_out_swap= 0;
    DmaCtrl.dma_int_line_num = 0x10;    
    VI_DRV_PIPE_SetDmaCtrl(isp,s8Index,&DmaCtrl);
	VI_PIPE_TPG_TOF_S pstPipeTpgTof;
    pstPipeTpgTof.tof_mode_enable            = vi_pipe_cfg->tof_mode_enable;
    pstPipeTpgTof.vi_pipe_tpg_tof_frm_stride = vi_pipe_cfg->vi_pipe_tpg_tof_frm_stride;
    pstPipeTpgTof.vi_pipe_tpg_tof_frm_num    = vi_pipe_cfg->vi_pipe_tpg_tof_frm_num;
	VI_DRV_PIPE_SetTofTpg(isp,s8Index,&pstPipeTpgTof);
	VI_PIPE_INT_CTL_S pstIntCtl;
    pstIntCtl.win_ctl_frame_end_en         = VI_INT_DIS; 
    pstIntCtl.emb_ctl_frame_end_en         = VI_INT_DIS; 
    pstIntCtl.emb_ctl_time_out_en          = VI_INT_DIS; 
    pstIntCtl.tpg_ctl_frame_end_en         = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_frame_end_en        = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_ch_line_base_en     = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_ch_err_frame_end_en = VI_INT_DIS; 
    pstIntCtl.dma_y_wr_ch_err_immediate_en = VI_INT_DIS; 
    pstIntCtl.dma_uv_wr_ch_frame_end_en    = VI_INT_DIS; 
    pstIntCtl.dma_uv_wr_ch_line_base_en    = VI_INT_DIS; 
    pstIntCtl.dma_uv_wr_ch_err_frame_end_en = VI_INT_DIS;
    pstIntCtl.dma_uv_wr_ch_err_immediate_en = VI_INT_DIS;
    pstIntCtl.dma_raw_rd_ch_frame_end_en   = VI_INT_DIS; 
    pstIntCtl.dma_raw_rd_ch_line_base_en   = VI_INT_DIS; 
    pstIntCtl.dma_raw_rd_ch_err_frame_end_en= VI_INT_DIS;
    pstIntCtl.dma_raw_rd_ch_err_immediate_en= VI_INT_DIS;
	VI_DRV_PIPE_SetInt(isp,s8Index,&pstIntCtl);
	VI_PIPE_CONFIG_DONE_S pstCfgDone;
    pstCfgDone.pipe_config_done      = 1;
    pstCfgDone.sens_reg_wr_protect   = VI_DONE_WP_EN;
    pstCfgDone.int_pol               = VI_INT_HIGH_ACT; //must high
	VI_DRV_PIPE_SetCfgDone(isp,s8Index,&pstCfgDone);
}
/*
*
*/
void video_in_imx385_normal_12bit_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    printf("video_in_imx385_normal_12bit_new start \n");
	struct vi_device *vi = &isp->isp_vi;
	printf("struct isp_device 0x%x,vi 0x%x\n",isp,vi);
	struct vi_wrap_cfg_info *wrap_info = &vi->vi_wrap_cfg;
	wrap_info->dphy_mode = TWO_LANES_MODE;
	wrap_info->sony_mode = SONY_POL_MODE_DIS;
	SENSOR_INFO *mipi0info = &wrap_info->sensor_info[MIPI0];
	mipi0info->sensor_interface_en = ENABLE;
	mipi0info->tpg_w_en = isp_addr->vi_tpg_en;//DISABLE;
	mipi0info->tpg_r_en = isp_addr->vi_tpg_en;//DISABLE;
	mipi0info->wdr_sensor_vendor = SONY_WDR_SENSOR;
	mipi0info->wdr_mode = ISP_PIPE_WDR_NONE;
	mipi0info->mipi_mode = NORMAL_MODE;
	mipi0info->isp_pipeline = ISP_F_2K;
	wrap_info->sensor_info[MIPI1].sensor_interface_en = DISABLE;
	wrap_info->sensor_info[DVP0].sensor_interface_en = DISABLE;
	vi_wrap_config(vi);
	struct vi_pipe_cfg_info *pipe_info = &vi->vi_pipe_cfg[VI_MIPI_CSI00_PIPE_ID];
	pipe_info->win_mode_en = TRUE;	
	pipe_info->input_ch_sel = MIPI_INPUT;
	pipe_info->ch_mode_sel = VI_MIPI_BT1120;
    pipe_info->pixel_type = SENSOR_INPUT_RAWRGB;
    pipe_info->yuv_in_format = VI_INPUT_YUV422;
    pipe_info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe_info->yuv422_order = VI_YUV422_YUYV;
    pipe_info->pixel_width = PIXEL_WIDTH_12BIT;
	pipe_info->data_out_timming_ctrl = CTRL_CYCLE_DELAY_4;
	pipe_info->sync_pulse_mode = 0;//0;
	pipe_info->sen_mipi_clk_pol = TRUE;
	pipe_info->sen_mipi_vsync_pol = FALSE;
	pipe_info->sen_mipi_hsync_pol = FALSE;
	pipe_info->sen_mipi_field_pol = TRUE;
	pipe_info->isp_clk_pol = TRUE;
	pipe_info->isp_vsync_pol = TRUE;
	pipe_info->isp_hsync_pol = TRUE;
	pipe_info->isp_field_pol = TRUE;
	//
    pipe_info->tpg_w_en = isp_addr->vi_tpg_en;//DISABLE;
    pipe_info->tpg_r_en = isp_addr->vi_tpg_en;//DISABLE;
    pipe_info->total_size.Width = isp_size->total_size.Width;//2200;
	pipe_info->total_size.Height = isp_size->total_size.Height;//1125;
    pipe_info->in_size.Width = isp_size->in_size.Width;//1920;
	pipe_info->in_size.Height = isp_size->in_size.Height;//1080;
    pipe_info->w_size_st.Width_st = 0x0;
	pipe_info->w_size_st.Height_st = 0x3fff;
    pipe_info->r_size_st.Width_st = 0x117;
	pipe_info->r_size_st.Height_st = 0x2c;
    pipe_info->vi_pipe_w_addr_y0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_y1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_uv0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_uv1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_r_addr_y0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_r_addr_y1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_addr_stride = isp_addr->vi_tpg_stride;
	pipe_info->tof_mode_enable = DISABLE;
	pipe_info->vi_pipe_tpg_tof_frm_num = 0x3;
	pipe_info->vi_pipe_tpg_tof_frm_stride = 0x10380;
	vi_pipe_config(vi,VI_MIPI_CSI00_PIPE_ID);
    printf("video_in_imx385_normal_12bit_new end \n");
}
/*
*
*/
void video_in_imx219_normal_10bit_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    printf("video_in_imx219_normal_10bit_new start \n");
	struct vi_device *vi = &isp->isp_vi;
	printf("struct isp_device 0x%x,vi 0x%x\n",isp,vi);
	struct vi_wrap_cfg_info *wrap_info = &vi->vi_wrap_cfg;
	wrap_info->dphy_mode = TWO_LANES_MODE;
	wrap_info->sony_mode = SONY_POL_MODE_DIS;
	SENSOR_INFO *mipi0info = &wrap_info->sensor_info[MIPI0];
	mipi0info->sensor_interface_en = ENABLE;
	mipi0info->tpg_w_en = isp_addr->vi_tpg_en;//DISABLE;
	mipi0info->tpg_r_en = isp_addr->vi_tpg_en;//DISABLE;
	mipi0info->wdr_sensor_vendor = SONY_WDR_SENSOR;
	mipi0info->wdr_mode = ISP_PIPE_WDR_NONE;
	mipi0info->mipi_mode = NORMAL_MODE;
	mipi0info->isp_pipeline = ISP_F_2K;
	wrap_info->sensor_info[MIPI1].sensor_interface_en = DISABLE;
	wrap_info->sensor_info[DVP0].sensor_interface_en = DISABLE;
	vi_wrap_config(vi);
	struct vi_pipe_cfg_info *pipe_info = &vi->vi_pipe_cfg[VI_MIPI_CSI00_PIPE_ID];
	pipe_info->win_mode_en = TRUE;	
	pipe_info->input_ch_sel = MIPI_INPUT;
	pipe_info->ch_mode_sel = VI_MIPI_BT1120;
    pipe_info->pixel_type = SENSOR_INPUT_RAWRGB;
    pipe_info->yuv_in_format = VI_INPUT_YUV422;
    pipe_info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe_info->yuv422_order = VI_YUV422_YUYV;
    pipe_info->pixel_width = PIXEL_WIDTH_10BIT;
	pipe_info->data_out_timming_ctrl = CTRL_CYCLE_DELAY_4;
	pipe_info->sync_pulse_mode = 0;//0;
	pipe_info->sen_mipi_clk_pol = TRUE;
	pipe_info->sen_mipi_vsync_pol = FALSE;
	pipe_info->sen_mipi_hsync_pol = FALSE;
	pipe_info->sen_mipi_field_pol = TRUE;
	pipe_info->isp_clk_pol = TRUE;
	pipe_info->isp_vsync_pol = TRUE;
	pipe_info->isp_hsync_pol = TRUE;
	pipe_info->isp_field_pol = TRUE;
	//
    pipe_info->tpg_w_en = isp_addr->vi_tpg_en;//DISABLE;
    pipe_info->tpg_r_en = isp_addr->vi_tpg_en;//DISABLE;
    pipe_info->total_size.Width = isp_size->total_size.Width;//2200;
	pipe_info->total_size.Height = isp_size->total_size.Height;//1125;
    pipe_info->in_size.Width = isp_size->in_size.Width;//1920;
	pipe_info->in_size.Height = isp_size->in_size.Height;//1080;
    pipe_info->w_size_st.Width_st = 0x0;
	pipe_info->w_size_st.Height_st = 0x3fff;
    pipe_info->r_size_st.Width_st = 0x117;
	pipe_info->r_size_st.Height_st = 0x2c;
    pipe_info->vi_pipe_w_addr_y0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_y1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_uv0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_uv1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_r_addr_y0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_r_addr_y1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_addr_stride = isp_addr->vi_tpg_stride;
	pipe_info->tof_mode_enable = DISABLE;
	pipe_info->vi_pipe_tpg_tof_frm_num = 0x3;
	pipe_info->vi_pipe_tpg_tof_frm_stride = 0x10380;
	vi_pipe_config(vi,VI_MIPI_CSI00_PIPE_ID);
    printf("video_in_imx385_normal_12bit_new end \n");
}
/**
 * @brief 
 * 
 */
void video_in_jxf23s_rgbir_10bit_30fps_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size)
{
    printf("video_in_jxf23s_rgbir_10bit_30fps_new start \n");
	struct vi_device *vi = &isp->isp_vi;
	printf("struct isp_device 0x%x,vi 0x%x\n",isp,vi);
	struct vi_wrap_cfg_info *wrap_info = &vi->vi_wrap_cfg;
	wrap_info->dphy_mode = TWO_LANES_MODE;
	wrap_info->sony_mode = SONY_POL_MODE_DIS;
	SENSOR_INFO *dvp0info = &wrap_info->sensor_info[DVP0];
	dvp0info->sensor_interface_en = ENABLE;
	dvp0info->tpg_w_en = isp_addr->vi_tpg_en;//DISABLE;
	dvp0info->tpg_r_en = isp_addr->vi_tpg_en;//DISABLE;
	dvp0info->wdr_sensor_vendor = SONY_WDR_SENSOR;
	dvp0info->wdr_mode = ISP_PIPE_WDR_NONE;
	dvp0info->mipi_mode = NORMAL_MODE;
	dvp0info->isp_pipeline = ISP_F_2K;
	wrap_info->sensor_info[MIPI0].sensor_interface_en = DISABLE;
	wrap_info->sensor_info[MIPI1].sensor_interface_en = DISABLE;
	vi_wrap_config(vi);
	//
	struct vi_pipe_cfg_info *pipe_info = &vi->vi_pipe_cfg[VI_DVP_0_PIPE_ID];
	pipe_info->win_mode_en = FALSE;		
	pipe_info->input_ch_sel = DVP_INPUT;
	pipe_info->ch_mode_sel = VI_MIPI_BT1120;
    pipe_info->pixel_type = SENSOR_INPUT_RAWRGB;
    pipe_info->yuv_in_format = VI_INPUT_YUV422;
    pipe_info->yuv_out_format = VI_OUTPUT_YUV422;
    pipe_info->yuv422_order = VI_YUV422_YUYV;
    pipe_info->pixel_width = PIXEL_WIDTH_10BIT;
	pipe_info->data_out_timming_ctrl = CTRL_CYCLE_DELAY_1;
	pipe_info->sync_pulse_mode = 1;//0;
	pipe_info->sen_mipi_clk_pol = TRUE;
	pipe_info->sen_mipi_vsync_pol = TRUE;
	pipe_info->sen_mipi_hsync_pol = TRUE;
	pipe_info->sen_mipi_field_pol = TRUE;
	pipe_info->isp_clk_pol = TRUE;
	pipe_info->isp_vsync_pol = TRUE;
	pipe_info->isp_hsync_pol = TRUE;
	pipe_info->isp_field_pol = TRUE;
	//
    pipe_info->tpg_w_en = isp_addr->vi_tpg_en;//DISABLE;
    pipe_info->tpg_r_en = isp_addr->vi_tpg_en;//DISABLE;
    pipe_info->total_size.Width = isp_size->total_size.Width;//2200;
	pipe_info->total_size.Height = isp_size->total_size.Height;//1125;
    pipe_info->in_size.Width = isp_size->in_size.Width;//1920;
	pipe_info->in_size.Height = isp_size->in_size.Height;//1080;
    pipe_info->w_size_st.Width_st = 0x24f;//0x0;
	pipe_info->w_size_st.Height_st = 0x3fff;
    pipe_info->r_size_st.Width_st = 0x0;//0x117;
	pipe_info->r_size_st.Height_st = 0x0;//0x2c;
    pipe_info->vi_pipe_w_addr_y0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_y1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_uv0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_w_addr_uv1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_r_addr_y0 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_r_addr_y1 = isp_addr->vi_tpg_baseaddr;
    pipe_info->vi_pipe_addr_stride = isp_addr->vi_tpg_stride;
	pipe_info->tof_mode_enable = DISABLE;
	pipe_info->vi_pipe_tpg_tof_frm_num = 0x0;
	pipe_info->vi_pipe_tpg_tof_frm_stride = 0x0;
	vi_pipe_config(vi,VI_DVP_0_PIPE_ID);
    printf("video_in_jxf23s_rgbir_10bit_30fps_new end \n");	
}
/**
 * @brief 
 * 
 */
void video_in_Init(struct isp_device *isp)
{
    printf("video_in_Init start \n");
	struct vi_device *vi = &isp->isp_vi;

	vi_wrap_config(vi);
	//csi0
	vi_pipe_config(vi,VI_MIPI_CSI00_PIPE_ID);
	vi_pipe_config(vi,VI_MIPI_CSI01_PIPE_ID);
	vi_pipe_config(vi,VI_MIPI_CSI02_PIPE_ID);
	//csi1
	vi_pipe_config(vi,VI_MIPI_CSI10_PIPE_ID);
	//dvp
	vi_pipe_config(vi,VI_DVP_0_PIPE_ID);

    printf("video_in_Init end \n");	
}
