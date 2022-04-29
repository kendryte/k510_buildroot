/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_table_drv.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
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
