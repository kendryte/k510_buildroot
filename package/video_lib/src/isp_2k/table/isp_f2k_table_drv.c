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
  File Name     : isp_f2k_table_drv.c
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
#include "video_subsystem.h"
#include "isp_2k/table/isp_table_drv.h"
#include "isp_2k/core/isp_core_drv.h"

extern int ISP_2K_WDR_L3_TABLE[1024];
extern int ISP_2K_WDR_M3_TABLE[1024];
extern int ISP_2K_WDR_S3_TABLE[1024];
extern int ISP_2K_WDR_L2_TABLE[1024];
extern int ISP_2K_WDR_S2_TABLE[1024];

extern int ISP_2K_YUV_GAMMA[256];
extern int ISP_2K_RGB_GAMMA[256];


static int IspCoreConfigTable(struct isp_device *isp,int a[],int num,ISP_TABLE table)
{
    ISP_CHECK_POINTER(isp);

	int isp_ram_ready = Isp_Drv_F2k_Core_GetRamRdStatus(isp);
	while((isp_ram_ready & 0x80) != 0x80)
	{
		msleep(500);

		isp_ram_ready = Isp_Drv_F2k_Core_GetRamRdStatus(isp);
		if((isp_ram_ready & 0x80) != 0x80)
		{
			printf(" isp share config ram is not ready for wr!!!!!!!!!!\n");
            return 1;
		}
		break;
	}

    for (int i =0;i<num; i++)
    {
  		//apstIspTableReg->isp_table[i] = (unsigned int )a[i]; 
        isp_reg_writel(isp,(unsigned int )a[i],ISP_IOMEM_F2K_CORE_TABLE,i<<2);
    }
	//ISP_CORE_DRV_SET_CoreRamWrStatus(apstIspCoreReg,(0x1<<table));
	//ISP_CORE_DRV_SET_CoreRamWrStatus(apstIspCoreReg,0x00);
    Isp_Drv_F2k_Core_SetRamWrStatus(isp,(0x1<<table));
    Isp_Drv_F2k_Core_SetRamWrStatus(isp,0x00);
	//writel((ISP_2K_BASE_ADDR + 0xc9<<2),(0x1<<table));
	//writel((ISP_2K_BASE_ADDR + 0xc9<<2),0x00);
    switch(table)
    {
    	case RGB_GAMMA: 
			printf("Isp2K RGB Gamma TABLE config done!\n"); 
			break;
    	case YUV_GAMMA: 
			printf("Isp2K YUV Gamma TABLE config done!\n");
			break;
    	case WDR_L3: 
			printf("Isp2K WDR L3 TABLE config done!\n");
			break;
    	case WDR_M3: 
			printf("Isp2K WDR M3 TABLE config done!\n");
			break;
    	case WDR_S3: 
			printf("Isp2K WDR S3 TABLE config done!\n");
			break;
    	case WDR_L2: 
			printf("Isp2K WDR L2 TABLE config done!\n");
			break;
    	case WDR_S2: 
			printf("Isp2K WDR S2 TABLE config done!\n");
			break;
    	default: 
			printf(" NO ANY Isp2K TABLE will be configed!!!!!!!!\n");
			break;
    }
    return	0;	
}
/*
 * 
 */
void isp_f2k_core_table_init(struct isp_device *isp)
{
    printf("isp_f2k_core_table_init start！\n");

    struct isp_f2k_device *f2k = &isp->isp_f2k;
    struct _WDR_INFO_S	*wdrcoreInfo = &f2k->isp_core_cfg.wdrInfo;

    IspCoreConfigTable(isp,ISP_2K_RGB_GAMMA,256,RGB_GAMMA);
    IspCoreConfigTable(isp,ISP_2K_YUV_GAMMA,256,YUV_GAMMA);

    if((1 == wdrcoreInfo->wdr_en)&&(1 == wdrcoreInfo->wdr_mode_sel))
    {
        IspCoreConfigTable(isp,ISP_2K_WDR_L3_TABLE,1024,WDR_L3);
        IspCoreConfigTable(isp,ISP_2K_WDR_M3_TABLE,1024,WDR_M3);
        IspCoreConfigTable(isp,ISP_2K_WDR_S3_TABLE,1024,WDR_S3);
        IspCoreConfigTable(isp,ISP_2K_WDR_L2_TABLE,1024,WDR_L2);
        IspCoreConfigTable(isp,ISP_2K_WDR_S2_TABLE,1024,WDR_S2);
    }
    else if((1 == wdrcoreInfo->wdr_en)&&(0 == wdrcoreInfo->wdr_mode_sel))
    {
        IspCoreConfigTable(isp,ISP_2K_WDR_L2_TABLE,1024,WDR_L2);
        IspCoreConfigTable(isp,ISP_2K_WDR_S2_TABLE,1024,WDR_S2);
    }
    else
    {
        /* code */
    }
    
    return;
}
