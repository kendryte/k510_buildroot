/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : bt1120_drv.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : bt1120 driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _BT1120_DRV_DEF_H_
#define _BT1120_DRV_DEF_H_

typedef struct  _BT_CTRL_MODE_S                       
{                                        
        unsigned int    bt_en             ;
        unsigned int    yc_reorder        ;
        unsigned int    crc_order         ;
        unsigned int    crc_init_val      ;
} BT_CTRL_MODE_S;  

typedef struct  _BT_CTRL_VBIT_S                        
{                                         
        unsigned int    bt_vbit_start     ;
        unsigned int    bt_vbit_end       ;
       
} BT_CTRL_VBIT_S;                     
										  
typedef struct  _BT_IMAGE_SIZE_TOTAL_S                             
{                                         
        unsigned int    img_vsize_total   ;
        unsigned int    img_hsize_total   ;
} BT_IMAGE_SIZE_TOTAL_S;                 
										 
typedef struct  _BT_IMAGE_SIZE_ACTIVE_S                          
{                                         
        unsigned int    img_vsize_active  ;
        unsigned int    img_hsize_active  ;

} BT_IMAGE_SIZE_ACTIVE_S;               
										 
typedef struct  _BT_CONFIG_DONE_S                             
{                                         
        unsigned int    config_done       ;
        unsigned int    wp_clr            ;    
} BT_CONFIG_DONE_S;  

typedef struct _BT1120_WRAP_CTL_S
{
    unsigned int            bt_in_sel;
    unsigned int            bt_sav_start;
    BT_CTRL_MODE_S          stCtrlMode;
    BT_CTRL_VBIT_S          stCtrlVbit;
    BT_IMAGE_SIZE_TOTAL_S   stSizeTotal;
    BT_IMAGE_SIZE_ACTIVE_S  stSizeActive;
    BT_CONFIG_DONE_S        stConfigDone;
} BT1120_WRAP_CTL_S;

//int BT1120_DRV_set(BT1120_WRAP_INFO_S *bt1120WrapInfo);
//int BT1120_DRV_EnBt1120(unsigned int enable);
int BT1120_DRV_SetBt1120(BT1120_WRAP_CTL_S *pstBt1120Wrap);

#endif /* _BT1120_DRV_DEF_H_ */
