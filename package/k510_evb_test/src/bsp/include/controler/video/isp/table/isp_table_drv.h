/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_table_drv.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : isp driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _ISP_TABLE_DRV_DEF_H_
#define _ISP_TABLE_DRV_DEF_H_

//#include "isp/inc/isp.h"
#include "video/isp/table/isp_table_reg.h"

//int  IspCoreConfigTable(int a[],int num,ISP_TABLE table);
void isp_core_table_init(ISP_PIPE_WDR_MODE_E Wdrmode);
#endif /* _ISP_TABLE_DRV_DEF_H_ */
