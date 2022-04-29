/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : td_wrap_drv.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#ifndef _TD_WRAP_DRV_DEF_H_
#define _TD_WRAP_DRV_DEF_H_

typedef struct _TD_WRAP_SWRST_S
{
    unsigned int rotationrw;
    unsigned int mixerrw;
    unsigned int axiwr  ;
    unsigned int axird  ;
} TD_WRAP_SWRST_S;

typedef struct _TD_WRAP_CLK_EN_S
{
    unsigned int ch0rd;
    unsigned int ch1rd;
    unsigned int ch2rd;
    unsigned int ch3rd;
    unsigned int ch4rd;
    unsigned int ch5rd;
    unsigned int ch0wr;
    unsigned int ch1wr;
    unsigned int ch2wr;
    unsigned int axiwr;
    unsigned int axird;
} TD_WRAP_CLK_EN_S;

typedef struct _TD_WRAP_DMA_ARB_MODE_S
{
        unsigned int wr;
        unsigned int rd;
} TD_WRAP_DMA_ARB_MODE_S;

typedef struct _TD_WRAP_DMA_WEIGHT_WR_S
{
        unsigned int ch0;
        unsigned int ch1;
        unsigned int ch2;
        unsigned int ch3;
        unsigned int ch4;
        unsigned int ch5;
        unsigned int ch6;
        unsigned int ch7;
} TD_WRAP_DMA_WEIGHT_WR_S;

typedef struct _TD_WRAP_DMA_WEIGHT_RD_S
{
        unsigned int ch0;
        unsigned int ch1;
        unsigned int ch2;
        unsigned int ch3;
        unsigned int ch4;
        unsigned int ch5;
        unsigned int ch6;
        unsigned int ch7;
} TD_WRAP_DMA_WEIGHT_RD_S;

typedef struct _TD_WRAP_DMA_PRIORITY_WR_S
{
        unsigned int ch0;
        unsigned int ch1;
        unsigned int ch2;
        unsigned int ch3;
        unsigned int ch4;
        unsigned int ch5;
        unsigned int ch6;
        unsigned int ch7;
} TD_WRAP_DMA_PRIORITY_WR_S;

typedef struct _D_WRAP_DMA_PRIORITY_RD_S
{
        unsigned int ch0;
        unsigned int ch1;
        unsigned int ch2;
        unsigned int ch3;
        unsigned int ch4;
        unsigned int ch5;
        unsigned int ch6;
        unsigned int ch7;
} TD_WRAP_DMA_PRIORITY_RD_S;

typedef struct _TD_WRAP_DMA_ID_WR_S
{
        unsigned int ch0;
        unsigned int ch1;
        unsigned int ch2;
        unsigned int ch3;
        unsigned int ch4;
        unsigned int ch5;
        unsigned int ch6;
        unsigned int ch7;
} TD_WRAP_DMA_ID_WR_S;

typedef struct _TD_WRAP_DMA_ID_RD_S
{
        unsigned int ch0;
        unsigned int ch1;
        unsigned int ch2;
        unsigned int ch3;
        unsigned int ch4;
        unsigned int ch5;
        unsigned int ch6;
        unsigned int ch7;
} TD_WRAP_DMA_ID_RD_S;		

typedef struct _TD_WRAP_DMA_CTL_S
{ 
       TD_WRAP_DMA_ARB_MODE_S    arb_mode;
       TD_WRAP_DMA_WEIGHT_WR_S   weight_wr;
       TD_WRAP_DMA_WEIGHT_RD_S   weight_rd;
       TD_WRAP_DMA_PRIORITY_WR_S prior_wr;
       TD_WRAP_DMA_PRIORITY_RD_S prior_rd;
       TD_WRAP_DMA_ID_WR_S       id_wr;
       TD_WRAP_DMA_ID_RD_S       id_rd; 
}TD_WRAP_DMA_CTL_S;

typedef struct 	_TD_WRAP_CFG_S	
{		
        unsigned int done   ;
        unsigned int int_pol;
} TD_WRAP_CFG_S;

typedef struct _TD_WRAP_INT_MASK_S
{
        unsigned int rotationdone_mask;
        unsigned int rotationtimeout_mask;
        unsigned int mixerdone_mask;
} TD_WRAP_INT_MASK_S;

typedef struct _TD_WRAP_CTL_S
{
      TD_WRAP_CLK_EN_S    clk_en;
      TD_WRAP_SWRST_S     swrst;
      TD_WRAP_DMA_CTL_S   dma_ctl;
      TD_WRAP_CFG_S       cfg_done;
      TD_WRAP_INT_MASK_S  int_mask;
}TD_WRAP_CTL_S;

int TD_DRV_Wrap_Remap(void);
int TD_DRV_SetWrap(TD_WRAP_CTL_S *tdWrapCtl);
//DEBUG
int TD_DRV_GetWrapRegsVal(void);
#endif /*_TD_WRAP_DRV_DEF_H_*/