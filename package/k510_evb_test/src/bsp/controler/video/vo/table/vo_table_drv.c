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
//#include "video/vo/vo.h"
#include "video/vo/table/vo_table_reg.h"
#include "video/vo/table/vo_table_drv.h"

#include <stdio.h>
#include <k510.h>
#include <sleep.h>

extern int V_Coef[128];
extern int H_Coef[192];
extern int GammaCoef[256];

unsigned int  *reg_vo_v_scale_table_base;
unsigned int  *reg_vo_h_scale_table_base;
unsigned int  *reg_vo_gamma_table_base;

#define VO_DRV_V_SCALE_TABLE_REG_CTX(pstCtx)	pstCtx = (S_VO_V_SCALE_COEFF_REGS_TYPE *)(reg_vo_v_scale_table_base)
#define VO_DRV_H_SCALE_TABLE_REG_CTX(pstCtx)	pstCtx = (S_VO_H_SCALE_COEFF_REGS_TYPE *)(reg_vo_h_scale_table_base)
#define VO_DRV_GAMMA_TABLE_REG_CTX(pstCtx)	    pstCtx = (S_VO_GAMMA_TABLE_REGS_TYPE *)(reg_vo_gamma_table_base)

int VO_DRV_Table_Remap(void )
{
	//reg_vo_v_scale_table_base  = (unsigned int *)VO_VSCALE_BASE; //BASE + 0x8C00 ~ BASE + 0x8DFF
	//reg_vo_h_scale_table_base  = (unsigned int *)VO_HSCALE_BASE; //BASE + 0x8000 ~ BASE + 0x83FF
	//reg_vo_gamma_table_base    = (unsigned int *)VO_GAMMA_BASE;//BASE + 0xC000 ~ BASE + 0xCBFF
	return 0;
}

/*
*
*/
static void  VoConfigVCoef(int a[],int num)  //128/2
{
	//S_VO_V_SCALE_COEFF_REGS_TYPE *apstVoVScaleTableReg = NULL;
	//VO_DRV_V_SCALE_TABLE_REG_CTX(apstVoVScaleTableReg);
	int base_addr= VO_VSCALE_BASE;
    for (int i =0;i<num; i++)
    {
		//apstVoVScaleTableReg->vo_v_coeff_table[i*2] = a[i*2];
		//apstVoVScaleTableReg->vo_v_coeff_table[i*2+1] = a[i*2+1];
    	writel(a[i*2],(base_addr + ((i*2)<<2)));
    	writel(a[i*2+1],(base_addr + ((i*2+1)<<2)));
	}
	printf("VO  VCoef Config done!\n");
}
/*
*
*/
static void  VoConfigHCoef(int a[],int num)
{
	//S_VO_H_SCALE_COEFF_REGS_TYPE *apstVoHScaleTableReg = NULL;
	//VO_DRV_H_SCALE_TABLE_REG_CTX(apstVoHScaleTableReg);
	int base_addr= VO_HSCALE_BASE;
	for (int i =0;i<num; i++)
	{
		//apstVoHScaleTableReg->vo_h_coeff_table[i*4] = a[i*3];
		//apstVoHScaleTableReg->vo_h_coeff_table[i*4+1] = a[i*3+1];
		//apstVoHScaleTableReg->vo_h_coeff_table[i*4+2] = a[i*3+2];
		writel(a[i*3],(base_addr + ((i*4)<<2)));
		writel(a[i*3 + 1],(base_addr + ((i*4+1)<<2)));
		writel(a[i*3 +2 ],(base_addr + ((i*4+2)<<2)));
	}
    printf("VO  HCoef Config done!\n");
}
/*
*
*/
static void  VoConfigGammaCoef(int a[],int num)
{
	//S_VO_GAMMA_TABLE_REGS_TYPE *apstVoGammaTableReg = NULL;
	//VO_DRV_GAMMA_TABLE_REG_CTX(apstVoGammaTableReg);
	int base_addr= VO_GAMMA_BASE;
	for (int i =0;i<num; i++)
	{
		//apstVoGammaTableReg->vo_r_gamma_table[i] = a[i];
		//apstVoGammaTableReg->vo_g_gamma_table[i] = a[i];
		//apstVoGammaTableReg->vo_b_gamma_table[i] = a[i];
		//RegWr32((base_addr + 0x00  +((i)<<2)),a[i]);
		//RegWr32((base_addr + 0x400 +((i)<<2)),a[i]);
		//RegWr32((base_addr + 0x800 +((i)<<2)),a[i]);
		writel(a[i],(base_addr + 0x00 +((i)<<2)));
		writel(a[i],(base_addr + 0x400 +((i)<<2)));
		writel(a[i],(base_addr + 0x800 +((i)<<2)));
	}	
	printf("VO  GAMMA Coef Config done!\n");
	return;
}
/*
*
*/
void VO_TABLE_init(void)
{
     VoConfigVCoef(V_Coef,64); //128/2
     VoConfigHCoef(H_Coef,64); //192/3
	 VoConfigGammaCoef(GammaCoef,256);
	 return;
}
