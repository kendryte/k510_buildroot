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
  File Name     : dev_hw.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef _DEF_DEV_HW_H_
#define _DEF_DEV_HW_H_
#ifdef __cplusplus  
extern "C"{
#endif
//
void DevRegWr(int addr,int data);
int  DevRegRd(int addr);
void ExtCtlRegWr(unsigned int addr,unsigned int data);
int ExtCtlRegRd(int addr);
void  I2cWr(int addr,int data);
void  I2cRd(int addr);
void  I2cWr_imx385(int addr,int data);
void  I2cRd_imx385(int addr);
void DevRegWr(int addr,int data);
int  DevRegRd(int addr);
//
void fpga_system_init(int isJxf23s);
void hmdi_init_jxf23s(void);
void hmdi_init_imx385(void);
void hmdi_init_dvp(void);
//
void  Dev_config_apb25MHZ(int byte_mode_config,int sensor_dev_addr,int dev_sel);
void  Dev_config_apb100MHZ(int byte_mode_config,int sensor_dev_addr,int dev_sel);
void  Set_manu(int enable);
void  Set_auto(int enable);
void  Start_Config(int start_flag);
void  HdmiI2cWr(int addr,int data);
void  HdmiI2cRd(int addr);
//
void Active_Cv8788_rstn(void);
void Release_Cv8788_rstn(void);
void Cv8788I2cWr(int addr,int data);
void Cv8788I2cRd(int addr);
void cv8788Init(void);
#ifdef __cplusplus
} 
#endif
#endif /* _DEF_DEV_HW_H_ */
