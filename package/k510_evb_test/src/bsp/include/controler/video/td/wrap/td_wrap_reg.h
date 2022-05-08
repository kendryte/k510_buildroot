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

#ifndef _TD_WRAP_REG_DEF_H_
#define _TD_WRAP_REG_DEF_H_

typedef union { /* TD_WrapSwRst */
   
    struct 
    {
        unsigned int rotationrw                  : 1;
        unsigned int mixerrw                     : 1;
        unsigned int reserved0                   : 6;
        unsigned int axiwr                       : 1;
        unsigned int axird                       : 1;
        unsigned int reserved1                   : 22;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_SWRST;

typedef union { /* TD_WrapClkEn */
   
    struct 
    {
        unsigned int ch0rd                       : 1;
        unsigned int ch1rd                       : 1;
        unsigned int ch2rd                       : 1;
        unsigned int ch3rd                       : 1;
        unsigned int ch4rd                       : 1;
        unsigned int ch5rd                       : 1;
        unsigned int reserved0                   : 2;
        unsigned int ch0wr                       : 1;
        unsigned int ch1wr                       : 1;
        unsigned int ch2wr                       : 1;
        unsigned int reserved1                   : 5;
        unsigned int axiwr                       : 1;
        unsigned int axird                       : 1;
        unsigned int reserved2                   : 14;
    } bits;     
    unsigned int u32; 
} U_TD_WRAP_CLK_EN;

typedef union { /* TD_WrapDmaArbMode */
   
    struct 
    {
        unsigned int wr                          : 1;
        unsigned int rd                          : 1;
        unsigned int reserved0                   : 30;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_ARB_MODE;

typedef union { /* TD_WrapDmaWeightWR0 */
   
    struct 
    {
        unsigned int ch0                         : 8;
        unsigned int ch1                         : 8;
        unsigned int ch2                         : 8;
        unsigned int ch3                         : 8;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_WEIGHT_WR0;

typedef union { /* TD_WrapDmaWeightWR1 */
   
    struct 
    {
        unsigned int ch4                         : 8;
        unsigned int ch5                         : 8;
        unsigned int ch6                         : 8;
        unsigned int ch7                         : 8;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_WEIGHT_WR1;

typedef union { /* TD_WrapDmaWeightRD0 */
   
    struct 
    {
        unsigned int ch0                         : 8;
        unsigned int ch1                         : 8;
        unsigned int ch2                         : 8;
        unsigned int ch3                         : 8;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_WEIGHT_RD0;

typedef union { /* TD_WrapDmaWeightRD1 */
   
    struct 
    {
        unsigned int ch4                         : 8;
        unsigned int ch5                         : 8;
        unsigned int ch6                         : 8;
        unsigned int ch7                         : 8;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_WEIGHT_RD1;

typedef union { /* TD_WrapDmaPriorityWR */
   
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
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_PRIORITY_WR;

typedef union { /* TD_WrapDmaPriorityRD */
   
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
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_PRIORITY_RD;

typedef union { /* TD_WrapDmaIdWR */
   
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
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_ID_WR;

typedef union { /* TD_WrapDmaIdRD */
   
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
    } bits;     
    unsigned int u32;
} U_TD_WRAP_DMA_ID_RD;

typedef union { /* TD_WrapCfg */
   
    struct 
    {
        unsigned int done                        : 1;
        unsigned int reserved0                   : 15;
        unsigned int int_pol                     : 1;
        unsigned int reserved1                   : 15;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_CFG;

typedef union { /* TD_WrapInt */
   
    struct 
    {
        unsigned int rotationdone                : 1;
        unsigned int rotationtimeout             : 1;
        unsigned int mixerdone                   : 1;
        unsigned int reserved0                   : 13;
        unsigned int rotationdone_mask           : 1;
        unsigned int rotationtimeout_mask        : 1;
        unsigned int mixerdone_mask              : 1;
        unsigned int reserved1                   : 13;
    } bits;     
    unsigned int u32;
} U_TD_WRAP_INT;

typedef struct
{
    volatile U_TD_WRAP_SWRST                    TD_WRAP_SWRST;
    volatile unsigned int                       reserved0[2];
    volatile U_TD_WRAP_CLK_EN                   TD_WRAP_CLK_EN;
    volatile unsigned int                       reserved1[4];
    volatile U_TD_WRAP_DMA_ARB_MODE             TD_WRAP_DMA_ARB_MODE;
    volatile U_TD_WRAP_DMA_WEIGHT_WR0           TD_WRAP_DMA_WEIGHT_WR0;
    volatile U_TD_WRAP_DMA_WEIGHT_WR1           TD_WRAP_DMA_WEIGHT_WR1;
    volatile U_TD_WRAP_DMA_WEIGHT_RD0           TD_WRAP_DMA_WEIGHT_RD0;
    volatile U_TD_WRAP_DMA_WEIGHT_RD1           TD_WRAP_DMA_WEIGHT_RD1;
    volatile U_TD_WRAP_DMA_PRIORITY_WR          TD_WRAP_DMA_PRIORITY_WR;
    volatile U_TD_WRAP_DMA_PRIORITY_RD          TD_WRAP_DMA_PRIORITY_RD;
    volatile U_TD_WRAP_DMA_ID_WR                TD_WRAP_DMA_ID_WR;
    volatile U_TD_WRAP_DMA_ID_RD                TD_WRAP_DMA_ID_RD;
    volatile unsigned int                       reserved2[13];
    volatile U_TD_WRAP_CFG                      TD_WRAP_CFG;
    volatile U_TD_WRAP_INT                      TD_WRAP_INT;
} S_TD_WRAP_REGS_TYPE;

int TD_WRAP_DRV_SET_SWRst(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_ClkEn(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaArbMode(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaWeightWR0(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaWeightWR1(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaWeightRD0(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaWeightRD1(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaPriorityWr(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaPriorityRd(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaIDWr(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_DmaIDRd(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
int TD_WRAP_DRV_SET_Cfg(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int TD_WRAP_DRV_GET_Cfg(S_TD_WRAP_REGS_TYPE *pstRegs);
int TD_WRAP_DRV_SET_Int(S_TD_WRAP_REGS_TYPE *pstRegs, unsigned int uData);
//DEBUG
int TD_WRAP_DRV_GET_WrapRegsVal(S_TD_WRAP_REGS_TYPE *pstRegs);
#endif /*_TD_WRAP_REG_DEF_H_*/