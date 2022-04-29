/******************************************************************************

  Copyright (C), 2020,  CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_wrap_calc.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : isp interface
  History       :
  1.Date        : 
  Author      :
  Modification: Created file

******************************************************************************/

//#include "video/isp/isp.h"
#include "video/isp_com.h"

unsigned int ISP_WRAP_DRV_calc_buf_base(unsigned int y_buf_base,IMAGE_SIZE img_size)
{
    unsigned int uv_buf_base;
    unsigned int width = img_size.Width;
    unsigned int height = img_size.Height;

    uv_buf_base = y_buf_base + width * height;
    return uv_buf_base;
}
