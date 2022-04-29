/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : td_table_drv.c
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
#include "video/video_subsystem_addr.h"
//#include "video/td/td.h"
#include "video/td/table/td_table_reg.h"
#include "video/td/table/td_table_drv.h"

extern int TD_V_Coef[128];
extern int TD_H_Coef[192];

unsigned int  *reg_td_v_scale_table_base;
unsigned int  *reg_td_h_scale_table_base;

#define TD_DRV_V_SCALE_TABLE_REG_CTX(pstCtx)	pstCtx = (S_TD_V_SCALE_COEFF_REGS_TYPE *)(reg_td_v_scale_table_base)
#define TD_DRV_H_SCALE_TABLE_REG_CTX(pstCtx)	pstCtx = (S_TD_H_SCALE_COEFF_REGS_TYPE *)(reg_td_h_scale_table_base)
/*
*
*/
int TD_DRV_Table_Remap(void)
{
	  reg_td_v_scale_table_base  = (unsigned int *)TD_VSCALE_BASE; 
	  reg_td_h_scale_table_base  = (unsigned int *)TD_HSCALE_BASE; 

    return 0;
}
/*
*
*/
static void  TdConfigVCoef(int a[],int num)  //128/2
{
	S_TD_V_SCALE_COEFF_REGS_TYPE *apstTdVScaleTableReg = NULL;
	TD_DRV_V_SCALE_TABLE_REG_CTX(apstTdVScaleTableReg);

    for (int i =0;i<num; i++)
    {
		apstTdVScaleTableReg->td_v_coeff_table[i*2] = a[i*2];
		apstTdVScaleTableReg->td_v_coeff_table[i*2+1] = a[i*2+1];
	}
	printf("TD  VCoef Config done!\n");
}
/*
*
*/
static void  TdConfigHCoef(int a[],int num)
{
	S_TD_H_SCALE_COEFF_REGS_TYPE *apstTdHScaleTableReg = NULL;
	TD_DRV_H_SCALE_TABLE_REG_CTX(apstTdHScaleTableReg);
    
	for (int i =0;i<num; i++)
	{
		apstTdHScaleTableReg->td_h_coeff_table[i*4] = a[i*3];
		apstTdHScaleTableReg->td_h_coeff_table[i*4+1] = a[i*3+1];
		apstTdHScaleTableReg->td_h_coeff_table[i*4+2] = a[i*3+2];
	}
    printf("TD  HCoef Config done!\n");
}
/*
*
*/
void td_table_init(void)
{
     TdConfigVCoef(TD_V_Coef,64); //128/2
     TdConfigHCoef(TD_H_Coef,64); //192/3
}
