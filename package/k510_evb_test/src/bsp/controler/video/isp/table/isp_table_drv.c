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
#include "video/isp/core/isp_core_reg.h"
#include "video/isp/core/isp_core_drv.h"
#include "video/isp/table/isp_table_reg.h"
#include "video/isp/table/isp_table_drv.h"

#include "video/video_subsystem_addr.h"
#include <stdio.h>
#include <k510.h>
#include <io.h>
//#include "video_com.h"

extern int ISP_2K_WDR_L3_TABLE[1024];
extern int ISP_2K_WDR_M3_TABLE[1024];
extern int ISP_2K_WDR_S3_TABLE[1024];
extern int ISP_2K_WDR_L2_TABLE[1024];
extern int ISP_2K_WDR_S2_TABLE[1024];

extern int ISP_2K_YUV_GAMMA[256];
extern int ISP_2K_RGB_GAMMA[256];

extern unsigned int  *reg_isp_2k_table_base;
#define ISP_2K_DRV_TABLE_REG_CTX(pstCtx)	pstCtx = (S_ISP_TABLE_REGS_TYPE *)(reg_isp_2k_table_base)

static int  IspCoreConfigTable(int a[],int num,ISP_TABLE table)
{
	S_ISP_TABLE_REGS_TYPE *apstIspTableReg = NULL;
	ISP_2K_DRV_TABLE_REG_CTX(apstIspTableReg);

	//int isp_ram_ready = ISP_CORE_DRV_GET_CoreRamRdStatus(apstIspCoreReg);
//	int isp_ram_ready = readl(ISP_2K_BASE_ADDR + 0xc9<<2);//
	int isp_ram_ready = ISP_DRV_CORE_GetRamRdStatus();
	while((isp_ram_ready & 0x80) != 0x80)
	{	
#ifndef _SIMU 
		msleep(500);
#endif
		//isp_ram_ready = ISP_CORE_DRV_GET_CoreRamRdStatus(apstIspCoreReg);
		//isp_ram_ready = readl(ISP_2K_BASE_ADDR + 0xc9<<2);//
		isp_ram_ready = ISP_DRV_CORE_GetRamRdStatus();
		if((isp_ram_ready & 0x80) != 0x80)
		{
			printf(" isp share config ram is not ready for wr!!!!!!!!!!\n");
            return 1;
		}
		break;
	}

    for (int i =0;i<num; i++)
    {
  		apstIspTableReg->isp_table[i] = (unsigned int )a[i]; 
    }
	//ISP_CORE_DRV_SET_CoreRamWrStatus(apstIspCoreReg,(0x1<<table));
	//ISP_CORE_DRV_SET_CoreRamWrStatus(apstIspCoreReg,0x00);
    ISP_DRV_CORE_SetRamWrStatus((0x1<<table));
    ISP_DRV_CORE_SetRamWrStatus(0x00);
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
void isp_core_table_init(ISP_PIPE_WDR_MODE_E Wdrmode)
{
    IspCoreConfigTable(ISP_2K_RGB_GAMMA,256,RGB_GAMMA);
    IspCoreConfigTable(ISP_2K_YUV_GAMMA,256,YUV_GAMMA);

    if( ISP_PIPE_WDR_3_FRAME == Wdrmode )
    {
        IspCoreConfigTable(ISP_2K_WDR_L3_TABLE,1024,WDR_L3);
        IspCoreConfigTable(ISP_2K_WDR_M3_TABLE,1024,WDR_M3);
        IspCoreConfigTable(ISP_2K_WDR_S3_TABLE,1024,WDR_S3);
        IspCoreConfigTable(ISP_2K_WDR_L2_TABLE,1024,WDR_L2);
        IspCoreConfigTable(ISP_2K_WDR_S2_TABLE,1024,WDR_S2);
    }
    else if( ISP_PIPE_WDR_2_FRAME == Wdrmode )
    {
        IspCoreConfigTable(ISP_2K_WDR_L2_TABLE,1024,WDR_L2);
        IspCoreConfigTable(ISP_2K_WDR_S2_TABLE,1024,WDR_S2);
    }
    else
    {
        /* code */
    }
    
    return;
}
