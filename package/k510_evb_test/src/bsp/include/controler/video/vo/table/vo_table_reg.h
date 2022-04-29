/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : vo_table_reg.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : vo driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _VO_TABLE_REG_DEF_H_
#define _VO_TABLE_REG_DEF_H_

typedef struct{
    volatile unsigned int           vo_h_coeff_table[1024];
} S_VO_H_SCALE_COEFF_REGS_TYPE;

typedef struct{
    volatile unsigned int           vo_v_coeff_table[1024];
} S_VO_V_SCALE_COEFF_REGS_TYPE;

typedef struct{
    volatile unsigned int           vo_r_gamma_table[1024];
    volatile unsigned int           vo_g_gamma_table[1024];
    volatile unsigned int           vo_b_gamma_table[1024];
} S_VO_GAMMA_TABLE_REGS_TYPE;

#endif /*_VO_TABLE_REG_DEF_H_*/