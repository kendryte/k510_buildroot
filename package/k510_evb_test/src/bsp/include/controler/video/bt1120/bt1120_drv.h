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
