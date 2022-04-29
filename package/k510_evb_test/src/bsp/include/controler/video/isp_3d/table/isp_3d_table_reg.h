/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_table_reg.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : isp driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _ISP_3D_TABLE_REG_DEF_H_
#define _ISP_3D_TABLE_REG_DEF_H_

typedef struct{
    volatile unsigned int           isp_table[1024];
} S_ISP_3D_TABLE_REGS_TYPE;

#endif /*_ISP_3D_TABLE_REG_DEF_H_*/