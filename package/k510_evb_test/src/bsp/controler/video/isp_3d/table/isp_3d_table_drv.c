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
#include "video/isp_3d/core/isp_3d_core_reg.h"
#include "video/isp_3d/core/isp_3d_core_drv.h"
#include "video/isp_3d/table/isp_3d_table_reg.h"
#include "video/isp_3d/table/isp_3d_table_drv.h"

#include "video/video_subsystem_addr.h"
#include <stdio.h>
#include <k510.h>
#include <io.h>

extern int ISP_3D_YUV_GAMMA[256];

unsigned int *reg_tof_table_base;
#define TOF_DRV_TABLE_REG_CTX(pstCtx)     pstCtx = (S_ISP_3D_TABLE_REGS_TYPE *)(reg_tof_table_base)
/*
*
*/
int TOF_DRV_Table_Remap(void)
{
	reg_tof_table_base = (unsigned int*)TOF_TABLE_REG_BASE;

	return SUCCESS;
}

static int  Isp3dConfigTable(int a[],int num)
{
	S_ISP_3D_TABLE_REGS_TYPE *apstIsp3dTableReg = NULL;
	TOF_DRV_TABLE_REG_CTX(apstIsp3dTableReg);

	int isp_ram_ready = TOF_DRV_CORE_GetRamRdDone();
	printf("isp_ram_ready = 0x%x\n",isp_ram_ready);
	while((isp_ram_ready & 0x80) != 0x80)
	{	
		msleep(500);		
		isp_ram_ready = TOF_DRV_CORE_GetRamRdDone();
		printf("isp_ram_ready = 0x%x\n",isp_ram_ready);
		if((isp_ram_ready & 0x80) != 0x80)
		{
			printf(" isp share config ram is not ready for wr!!!!!!!!!!\n");
            return 1;
		}
		break;
	}

    for (int i =0;i<num; i++)
    {
  		apstIsp3dTableReg->isp_table[i] = (unsigned int )a[i]; 
    }

    TOF_DRV_CORE_SetRamWrStatus(1);

	isp_ram_ready = TOF_DRV_CORE_GetRamRdDone();
	printf("isp_ram_ready = 0x%x\n",isp_ram_ready);
	while((isp_ram_ready & 0x80) != 0x80)
	{	
		msleep(500);		
		isp_ram_ready = TOF_DRV_CORE_GetRamRdDone();
		printf("isp_ram_ready = 0x%x\n",isp_ram_ready);
		if((isp_ram_ready & 0x80) != 0x80)
		{
			printf(" isp share config ram is not ready for wr!!!!!!!!!!\n");
            return 1;
		}
		break;
	}
	TOF_DRV_CORE_SetRamWrStatus(0);

	printf("Isp 3D RGB Gamma TABLE config done!\n"); 
    return	0;	
}
/*
 * 
 */
void isp_3d_table_init(void)
{
    Isp3dConfigTable(ISP_3D_YUV_GAMMA,256);

    return;
}
