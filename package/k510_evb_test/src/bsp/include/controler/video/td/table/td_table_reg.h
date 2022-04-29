/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : td_table_reg.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : td driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _TD_TABLE_REG_DEF_H_
#define _TD_TABLE_REG_DEF_H_

typedef struct{
    volatile unsigned int           td_h_coeff_table[1024];
} S_TD_H_SCALE_COEFF_REGS_TYPE;

typedef struct{
    volatile unsigned int           td_v_coeff_table[1024];
} S_TD_V_SCALE_COEFF_REGS_TYPE;

#endif /*_TD_TABLE_REG_DEF_H_*/