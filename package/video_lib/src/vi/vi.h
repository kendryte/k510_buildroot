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
  File Name     : vi.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file
******************************************************************************/
#ifndef _VI_H_
#define _VI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "isp_com.h"
#include "vi/vi_com.h"
#include "isp_2k/isp.h"
//imx385
void vi_wrap_rst(struct isp_device *isp);
void vi_wrap_config(struct vi_device *vi);
void vi_pipe_SetIntEn(struct vi_device *vi,unsigned int s8Index,struct VI_PIPE_INT_EN *int_en);
unsigned int vi_pipe_GetIntSts(struct vi_device *vi,unsigned int s8Index);
void vi_pipe_config(struct vi_device *vi,unsigned int s8Index);
void video_in_imx385_normal_12bit_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size);
//jfx23s
void video_in_jxf23s_rgbir_10bit_30fps_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size);
//
void video_in_imx219_normal_10bit_new(struct isp_device *isp,ISP_ADDR_INFO *isp_addr,ISP_SIZE_S *isp_size);
#ifdef __cplusplus
}
#endif
#endif /*_VI_H_*/