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

#ifndef _MFBC_WRAP_DRV_DEF_H_
#define _MFBC_WRAP_DRV_DEF_H_

typedef struct _MFBC_WRAP_ARBMODE_S
{
  unsigned int arbmode_wr;
  unsigned int arbmode_rd;
}MFBC_WRAP_ARBMODE_S;

typedef struct _MFBC_WRAP_WEIGHT_WR_S
{
  unsigned int weight_wr_ch0;
  unsigned int weight_wr_ch1;
  unsigned int weight_wr_ch2;
  unsigned int weight_wr_ch3;
  unsigned int weight_wr_ch4;
  unsigned int weight_wr_ch5;
  unsigned int weight_wr_ch6;
  unsigned int weight_wr_ch7;
}MFBC_WRAP_WEIGHT_WR_S;

typedef struct _MFBC_WRAP_WEIGHT_RD_S
{
  unsigned int weight_rd_ch0;
  unsigned int weight_rd_ch1;
  unsigned int weight_rd_ch2;
  unsigned int weight_rd_ch3;
  unsigned int weight_rd_ch4;
  unsigned int weight_rd_ch5;
  unsigned int weight_rd_ch6;
  unsigned int weight_rd_ch7;
}MFBC_WRAP_WEIGHT_RD_S;

typedef struct _MFBC_WRAP_PRIOR_WR_S
{
  unsigned int wr_ch0;
  unsigned int wr_ch1;
  unsigned int wr_ch2;
  unsigned int wr_ch3;
  unsigned int wr_ch4;
  unsigned int wr_ch5;
  unsigned int wr_ch6;
  unsigned int wr_ch7;
}MFBC_WRAP_PRIOR_WR_S;

typedef struct _MFBC_WRAP_PRIOR_RD_S
{
  unsigned int rd_ch0;
  unsigned int rd_ch1;
  unsigned int rd_ch2;
  unsigned int rd_ch3;
  unsigned int rd_ch4;
  unsigned int rd_ch5;
  unsigned int rd_ch6;
  unsigned int rd_ch7;
}MFBC_WRAP_PRIOR_RD_S;

typedef struct _MFBC_WRAP_WR_ID_S
{
  unsigned int wr_ch0;
  unsigned int wr_ch1;
  unsigned int wr_ch2;
  unsigned int wr_ch3;
  unsigned int wr_ch4;
  unsigned int wr_ch5;
  unsigned int wr_ch6;
  unsigned int wr_ch7;
}MFBC_WRAP_WR_ID_S;

typedef struct _MFBC_WRAP_RD_ID_S
{
  unsigned int rd_ch0;
  unsigned int rd_ch1;
  unsigned int rd_ch2;
  unsigned int rd_ch3;
  unsigned int rd_ch4;
  unsigned int rd_ch5;
  unsigned int rd_ch6;
  unsigned int rd_ch7;
}MFBC_WRAP_RD_ID_S;

typedef struct _MFBC_WRAP_DMA_S
{
  MFBC_WRAP_ARBMODE_S   arb_mode;
  MFBC_WRAP_WEIGHT_WR_S weight_wr;
  MFBC_WRAP_WEIGHT_RD_S weight_rd;
  MFBC_WRAP_PRIOR_WR_S  prior_wr;
  MFBC_WRAP_PRIOR_RD_S  prior_rd;
  MFBC_WRAP_WR_ID_S     wr_id;
  MFBC_WRAP_RD_ID_S     rd_id;
}MFBC_WRAP_DMA_S;

typedef struct _MFBC_WRAP_RST_S
{
    unsigned int ch0ywr   ;
    unsigned int ch1uvwr  ;
    unsigned int ch2headwr;
    unsigned int axiwr    ;
    unsigned int axird    ;
}MFBC_WRAP_RST_S;

typedef struct _MFBC_WRAP_CLK_EN_S
{
    unsigned int ch0ywr   ;
    unsigned int ch1uvwr  ;
    unsigned int ch2headwr;
    unsigned int axiwr    ;
    unsigned int axird    ;
}MFBC_WRAP_CLK_EN_S;

typedef struct _MFBC_WRAP_CFG_DONE_S
{
    unsigned int done;
    unsigned int wp_clr;
    unsigned int int_irq_pol;
}MFBC_WRAP_CFG_DONE_S;

typedef struct _MFBC_WRAP_INT_MASK_S
{
    unsigned int ydonemask;
    unsigned int uvdonemask;
    unsigned int headdonemask;
}MFBC_WRAP_INT_MASK_S;

typedef struct _MFBC_WRAP_ATTR_S
{
  MFBC_WRAP_RST_S stSwRst;
  unsigned int mfbc_chl_sel;
  MFBC_WRAP_CLK_EN_S stClkEn;
  MFBC_WRAP_CFG_DONE_S stCfgdDone;
  MFBC_WRAP_INT_MASK_S stIntMsk;
  MFBC_WRAP_DMA_S  stDma;
}MFBC_WRAP_ATTR_S;
//
int MFBC_DRV_Wrap_Remap(void);
int MFBC_DRV_SetWrap(MFBC_WRAP_ATTR_S *mfbcWrapAttr);
//debug
int MFBC_DRV_GetWrapRegsVal(void);
#endif /*_MFBC_WRAP_DRV_DEF_H_*/
