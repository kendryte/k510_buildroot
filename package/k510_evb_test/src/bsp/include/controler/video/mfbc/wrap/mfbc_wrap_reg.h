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

#ifndef _MFBC_WRAP_REG_DEF_H_
#define _MFBC_WRAP_REG_DEF_H_

typedef union { /* MFBC_WrapSwRst */
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
} U_MFBC_WRAP_SW_RST;

typedef union { /* MFBC_WrapOutSel */
    /* Define the struct bits */
    struct 
    {
        unsigned int mfbc_chl_sel                : 4;
        unsigned int reserved0                   : 28;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_WRAP_OUT_SEL;

typedef union { /* MFBC_WrapClkEn */
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
} U_MFBC_WRAP_CLK_EN;

typedef union { /* MFBC_WrapDmaArbMode */
    /* Define the struct bits */
    struct
   {
        unsigned int wr_arb_mode                 : 1;
        unsigned int rd_arb_mode                 : 1;
        unsigned int reserved0                   : 30;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_WRAP_DMA_ARB_MODE;

typedef union { /* MFBC_WrapDmaWeightWr0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 8;
        unsigned int ch1                         : 8;
        unsigned int ch2                         : 8;
        unsigned int ch3                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_WRAP_DMA_WEIGHT_WR0;

typedef union { /* MFBC_WrapDmaWeightWr1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch4                         : 8;
        unsigned int ch5                         : 8;
        unsigned int ch6                         : 8;
        unsigned int ch7                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_WRAP_DMA_WEIGHT_WR1;

typedef union { /* MFBC_WrapDmaWeightRd0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch0                         : 8;
        unsigned int ch1                         : 8;
        unsigned int ch2                         : 8;
        unsigned int ch3                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_WRAP_DMA_WEIGHT_RD0;

typedef union { /* MFBC_WrapDmaWeightRd1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int ch4                         : 8;
        unsigned int ch5                         : 8;
        unsigned int ch6                         : 8;
        unsigned int ch7                         : 8;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_WRAP_DMA_WEIGHT_RD1;

typedef union { /* MFBC_WrapDmaPriorityWr */
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
} U_MFBC_WRAP_DMA_PRIORITY_WR;

typedef union { /* MFBC_WrapDmaPriorityRd */
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
} U_MFBC_WRAP_DMA_PRIORITY_RD;

typedef union { /* MFBC_WrapDmaIdWr */
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
} U_MFBC_WRAP_DMA_ID_WR;

typedef union { /* MFBC_WrapDmaIdRd */
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
} U_MFBC_WRAP_DMA_ID_RD;

typedef union { /* MFBC_WrapCfg */
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
} U_MFBC_WRAP_CFG;

typedef union { /* MFBC_WrapInt */
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
} U_MFBC_WRAP_INT;

typedef struct
{
    volatile U_MFBC_WRAP_SW_RST                 MFBC_WRAP_SW_RST;
    volatile U_MFBC_WRAP_OUT_SEL                MFBC_WRAP_OUT_SEL;
    volatile unsigned int                       reserved0;
    volatile U_MFBC_WRAP_CLK_EN                 MFBC_WRAP_CLK_EN;
    volatile unsigned int                       reserve1[4];
    volatile U_MFBC_WRAP_DMA_ARB_MODE           MFBC_WRAP_DMA_ARB_MODE;
    volatile U_MFBC_WRAP_DMA_WEIGHT_WR0         MFBC_WRAP_DMA_WEIGHT_WR0;
    volatile U_MFBC_WRAP_DMA_WEIGHT_WR1         MFBC_WRAP_DMA_WEIGHT_WR1;
    volatile U_MFBC_WRAP_DMA_WEIGHT_RD0         MFBC_WRAP_DMA_WEIGHT_RD0;
    volatile U_MFBC_WRAP_DMA_WEIGHT_RD1         MFBC_WRAP_DMA_WEIGHT_RD1;
    volatile U_MFBC_WRAP_DMA_PRIORITY_WR        MFBC_WRAP_DMA_PRIORITY_WR;
    volatile U_MFBC_WRAP_DMA_PRIORITY_RD        MFBC_WRAP_DMA_PRIORITY_RD;
    volatile U_MFBC_WRAP_DMA_ID_WR              MFBC_WRAP_DMA_ID_WR;
    volatile U_MFBC_WRAP_DMA_ID_RD              MFBC_WRAP_DMA_ID_RD;
    volatile unsigned int                       reserve2[13];
    volatile U_MFBC_WRAP_CFG                    MFBC_WRAP_CFG;
    volatile U_MFBC_WRAP_INT                    MFBC_WRAP_INT;
} S_MFBC_WRAP_REGS_TYPE;

int MFBC_WRAP_DRV_SET_SWRst(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_OutSel(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaArbMode(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaWeightWr0(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaWeightWr1(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaWeightRd0(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaWeightRd1(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaPriorityWR(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaPriorityRD(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaIDWR(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_DmaIDRD(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_CLK_EN(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_SET_CFG(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_WRAP_DRV_GET_CFG(S_MFBC_WRAP_REGS_TYPE *pstRegs);
int MFBC_WRAP_DRV_SET_INT_MASK(S_MFBC_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int MFBC_WRAP_DRV_GET_INT_STS(S_MFBC_WRAP_REGS_TYPE *pstRegs);
//debug
int MFBC_WRAP_DRV_GET_WrapRegsVal(S_MFBC_WRAP_REGS_TYPE *pstRegs);
#endif /*_MFBC_WRAP_REG_DEF_H_*/
