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
  File Name     : vo_table_drv.c
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
#include "vo/vo.h"
#include "vo/table/vo_table_drv.h"

extern int V_Coef[128];
extern int H_Coef[192];
extern int GammaCoef[256];
/*
*
*/
static void  VoCfgVCoef(struct isp_device *isp,int a[],int num)  //128/2
{
	VO_CHECK_POINTER(isp);

    for (int i =0;i<num; i++)
    {
		isp_reg_writel(isp,a[i*2],ISP_IOMEM_VO_VSCALE,((i*2)<<2));
		isp_reg_writel(isp,a[i*2+1],ISP_IOMEM_VO_VSCALE,((i*2+1)<<2));
	}
	printf("VO  VCoef Config done!\n");
}
/*
*
*/
static void  VoCfgHCoef(struct isp_device *isp,int a[],int num)
{
	VO_CHECK_POINTER(isp);
	int base_addr= ISP_IOMEM_VO_HSCALE;
	for (int i =0;i<num; i++)
	{
		isp_reg_writel(isp,a[i*3],ISP_IOMEM_VO_HSCALE,((i*4)<<2));
		isp_reg_writel(isp,a[i*3+1],ISP_IOMEM_VO_HSCALE,((i*4+1)<<2));
		isp_reg_writel(isp,a[i*3+2],ISP_IOMEM_VO_HSCALE,((i*4+2)<<2));
	}
    printf("VO  HCoef Config done!\n");
}
/*
*
*/
static void  VoCfgGammaCoef(struct isp_device *isp,int a[],int num)
{
	VO_CHECK_POINTER(isp);
	int base_addr= ISP_IOMEM_VO_GAMMA;
	for (int i =0;i<num; i++)
	{
		isp_reg_writel(isp,a[i],ISP_IOMEM_VO_GAMMA,0x00  + ((i*2)<<2));
		isp_reg_writel(isp,a[i],ISP_IOMEM_VO_GAMMA,0x400 + ((i*2)<<2));
		isp_reg_writel(isp,a[i],ISP_IOMEM_VO_GAMMA,0x800 + ((i*2)<<2));
	}	
	printf("VO  GAMMA Coef Config done!\n");
	return;
}
/*
*
*/
void Vo_Table_init(struct isp_vo_device *vo)
{
	VO_CHECK_POINTER(vo_osd_virtual_addr);
	struct isp_device *isp = to_isp_device(vo);

    VoCfgVCoef(isp,V_Coef,64); //128/2
    VoCfgHCoef(isp,H_Coef,64); //192/3
	VoCfgGammaCoef(isp,GammaCoef,256);
	return;
}
