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
#ifndef _MIPI_CSI_DEF_H_
#define _MIPI_CSI_DEF_H_

void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_normal_30fps(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr3f_12bit_6p25fps(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr3f_12bit_6p25fps_cs1(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps(void);
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_2lane_imx385_wdr2f_12bit_12fps_cs1(void);
void cdns_mipi_reg_init_3840x2160_RAW12_mipi_4lane_OS8A10_noraml_10bit_7p5fps(void);
void csdn_opn8008_320x240_lane2_12bit(void);
void csdn_irs328c_224x172_lane2_12bit(void);
void cdns_mipi_reg_rd(void);
//
void cdns_mipi_reg_init_1920x1080xRAW12_mipi_4lane_imx385_normal(void);
void csdn_imx385_1920x1080_lane2_12bit(void);
//
void csdn_opn8018_640x480_lane2_12bit(void);
void csdn_opn8018_640x480_lane4_12bit(void);
#endif /*_MIPI_CSI_DEF_H_*/
