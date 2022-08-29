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

#ifndef __ADAPTIVE_USER_FUNC_H__
#define __ADAPTIVE_USER_FUNC_H__

#include "sensor_params/canaan_isp_struct.h"
#include "adaptive_isp_reg.h"
#include "adaptive_setting.h"

/* user init */
int adaptive_calc_feture_init(enum adaptive_isp_pipeline_e pipeline, ADAPTIVE_IMG_TIMING_CFG_T image_timing_cfg);
int adaptive_param_init(enum adaptive_isp_pipeline_e pipeline, ADAPTIVE_SENSOR_NAME_S_T adaptive_sensor_name_s, char * sensor_name);

/* user functions */
int adaptive_get_3a_stat(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe);
int adaptive_setting_ctl(enum adaptive_isp_pipeline_e pipeline);
int adaptive_param_apply(enum adaptive_isp_pipeline_e pipeline, struct media_entity * pipe);

/* user ex opeartion */
int adaptive_ex_gt_update_flag(enum adaptive_isp_pipeline_e pipeline);
int adaptive_ex_gt_awb_apply_flag(enum adaptive_isp_pipeline_e pipeline);
int adaptive_ex_st_ev_apply_flag(enum adaptive_isp_pipeline_e pipeline, int flag);
int adaptive_ex_st_ae_apply(enum adaptive_isp_pipeline_e pipeline, int yeverage, int expl, int agco);
int adaptive_ex_st_update_flag(enum adaptive_isp_pipeline_e pipeline);

/* user get version */
char * adaptive_get_version();

#endif