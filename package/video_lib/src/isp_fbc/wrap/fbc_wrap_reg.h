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

/*
 * fbc_wrap_reg.h
 *
 * CANAAN ISP - header definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _FBC_WRAP_REG_H_
#define _FBC_WRAP_REG_H_

typedef union { /* FBC_WrapSwRst */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0ywr                      : 1;
        unsigned int ch1uvwr                     : 1;
        unsigned int ch2headwr                   : 1;
        unsigned int reserved0                   : 5;
        unsigned int axiwr                       : 1;
        unsigned int axird                       : 1;
        unsigned int reserved1                   : 22;
    } bits; /* Define an unsigned member */

    unsigned int u32;
} U_FBC_WRAP_SW_RST;

typedef union { /* FBC_WrapOutSel */
    /* Define the struct bits */
    struct 
    {
        unsigned int fbc_chl_sel                : 4;
        unsigned int reserved0                   : 28;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_OUT_SEL;

typedef union { /* FBC_WrapClkEn */
    /* Define the struct bits */ 
    struct 
    {
        unsigned int ch0ywr                      : 1;
        unsigned int ch1uvwr                     : 1;
        unsigned int ch2headwr                   : 1;
        unsigned int reserved0                   : 13;
        unsigned int axiwr                       : 1;
        unsigned int axird                       : 1;
        unsigned int reserved1                   : 14;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_CLK_EN;

typedef union { /* FBC_WrapDmaArbMode */
    /* Define the struct bits */
    struct
   {
        unsigned int wr_arb_mode                 : 1;
        unsigned int rd_arb_mode                 : 1;
        unsigned int reserved0                   : 30;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_ARB_MODE;

typedef union { /* FBC_WrapDmaWeightWr0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 8;
        unsigned int ch1                         : 8;
        unsigned int ch2                         : 8;
        unsigned int ch3                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_WEIGHT_WR0;

typedef union { /* FBC_WrapDmaWeightWr1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch4                         : 8;
        unsigned int ch5                         : 8;
        unsigned int ch6                         : 8;
        unsigned int ch7                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_WEIGHT_WR1;

typedef union { /* FBC_WrapDmaWeightRd0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 8;
        unsigned int ch1                         : 8;
        unsigned int ch2                         : 8;
        unsigned int ch3                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_WEIGHT_RD0;

typedef union { /* FBC_WrapDmaWeightRd1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch4                         : 8;
        unsigned int ch5                         : 8;
        unsigned int ch6                         : 8;
        unsigned int ch7                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_WEIGHT_RD1;

typedef union { /* FBC_WrapDmaPriorityWr */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 4;
        unsigned int ch1                         : 4;
        unsigned int ch2                         : 4;
        unsigned int ch3                         : 4;
        unsigned int ch4                         : 4;
        unsigned int ch5                         : 4;
        unsigned int ch6                         : 4;
        unsigned int ch7                         : 4;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_PRIORITY_WR;

typedef union { /* FBC_WrapDmaPriorityRd */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 4;
        unsigned int ch1                         : 4;
        unsigned int ch2                         : 4;
        unsigned int ch3                         : 4;
        unsigned int ch4                         : 4;
        unsigned int ch5                         : 4;
        unsigned int ch6                         : 4;
        unsigned int ch7                         : 4;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_PRIORITY_RD;

typedef union { /* FBC_WrapDmaIdWr */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 4;
        unsigned int ch1                         : 4;
        unsigned int ch2                         : 4;
        unsigned int ch3                         : 4;
        unsigned int ch4                         : 4;
        unsigned int ch5                         : 4;
        unsigned int ch6                         : 4;
        unsigned int ch7                         : 4;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_ID_WR;

typedef union { /* FBC_WrapDmaIdRd */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 4;
        unsigned int ch1                         : 4;
        unsigned int ch2                         : 4;
        unsigned int ch3                         : 4;
        unsigned int ch4                         : 4;
        unsigned int ch5                         : 4;
        unsigned int ch6                         : 4;
        unsigned int ch7                         : 4;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_DMA_ID_RD;

typedef union { /* FBC_WrapCfg */
    /* Define the struct bits */
    struct 
    {
        unsigned int done                        : 1;
        unsigned int reserved0                   : 15;
        unsigned int wp_clr                      : 1;
        unsigned int int_irq_pol                 : 1;
        unsigned int reserved1                   : 14;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_CFG;

typedef union { /* FBC_WrapInt */
    /* Define the struct bits */
    struct 
    {
        unsigned int ydone                       : 1;
        unsigned int uvdone                      : 1;
        unsigned int headdone                    : 1;
        unsigned int reserved0                   : 13;
        unsigned int ydonemask                   : 1;
        unsigned int uvdonemask                  : 1;
        unsigned int headdonemask                : 1;
        unsigned int reserved1                   : 13;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_WRAP_INT;

#define  FBC_INT_ST_Y_DONE         (1<<0)
#define  FBC_INT_ST_UV_DONE        (1<<1)
#define  FBC_INT_ST_HEAD_DONE      (1<<2)
//
#define  FBC_WRAP_CONFIG_DONE      (1<<0)   
//define registers
#define  FBC_WRAP_SW_RST     		(0x0004)
#define  FBC_WRAP_OUT_SEL     		(0x0008)
	
#define  FBC_WRAP_CLK_EN     		(0x000C)
	
#define  FBC_WRAP_DMA_ARB_MODE     (0x0020)
#define  FBC_WRAP_DMA_WEIGHT_WR0   (0x0024)
#define  FBC_WRAP_DMA_WEIGHT_WR1   (0x0028)
#define  FBC_WRAP_DMA_WEIGHT_RD0   (0x002C)
#define  FBC_WRAP_DMA_WEIGHT_RD1   (0x0030)
#define  FBC_WRAP_DMA_PRIORITY_WR  (0x0034)
#define  FBC_WRAP_DMA_PRIORITY_RD  (0x0038)
#define  FBC_WRAP_DMA_ID_WR    	    (0x003C)
#define  FBC_WRAP_DMA_ID_RD    	    (0x0040)

#define  FBC_WRAP_AXI_RST_REQ		(0x0074)	
#define  FBC_WRAP_CFG     			(0x0078)
#define  FBC_WRAP_INT     			(0x007C)

#endif /*_FBC_WRAP_REG_H_*/
