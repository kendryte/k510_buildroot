/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mfbc_core_reg.h
  Version       : Initial Draft
  Author        : zhudalei
  Created       : 
  Description   : 
  History       :
  Date        : 
 ******************************************************************************/

#ifndef _MFBC_CORE_REG_DEF_H_
#define _MFBC_CORE_REG_DEF_H_

typedef union { /* MFBC_InputSize */
    /* Define the struct bits */
    struct 
    {
        unsigned int height                      : 13;
        unsigned int reserved0                   : 3;
        unsigned int width                       : 13;
        unsigned int reserved1                   : 3;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_INPUT_SIZE;

typedef union { /* MFBC_OutFormat */
    /* Define the struct bits */
    struct 
    {
        unsigned int disable420                  : 1;
        unsigned int reserved0                   : 31;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_OUT_FORMAT;
/*Y*/
typedef union { /* MFBC_Y_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_Y_DATA_BASE_ADDR_0;

typedef union { /* MFBC_Y_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_Y_DATA_BASE_ADDR_1;

typedef union { /* MFBC_Y_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_Y_DATA_LINE_STRIDE;

typedef union { /* MFBC_Y_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_MFBC_Y_DATA_WR_BLENGTH;
/*Y HEAD*/
typedef union { /* MFBC_Y_HEAD_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_Y_HEAD_DATA_BASE_ADDR_0;

typedef union { /* MFBC_Y_HEAD_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_Y_HEAD_DATA_BASE_ADDR_1;

typedef union { /* MFBC_Y_HEAD_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_Y_HEAD_DATA_LINE_STRIDE;

typedef union { /* MFBC_Y_HEAD_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_MFBC_Y_HEAD_DATA_WR_BLENGTH;
/*UV*/
typedef union { /* MFBC_UV_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_UV_DATA_BASE_ADDR_0;

typedef union { /* MFBC_UV_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_UV_DATA_BASE_ADDR_1;

typedef union { /* MFBC_UV_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_UV_DATA_LINE_STRIDE;

typedef union { /* MFBC_UV_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_MFBC_UV_DATA_WR_BLENGTH;
/*UV HEAD*/
typedef union { /* MFBC_UV_HEAD_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_UV_HEAD_DATA_BASE_ADDR_0;

typedef union { /* MFBC_UV_HEAD_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_UV_HEAD_DATA_BASE_ADDR_1;

typedef union { /* MFBC_UV_HEAD_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_MFBC_UV_HEAD_DATA_LINE_STRIDE;

typedef union { /* MFBC_UV_HEAD_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_MFBC_UV_HEAD_DATA_WR_BLENGTH;

typedef struct
{
    volatile U_MFBC_INPUT_SIZE               MFBC_INPUT_SIZE              ;
    volatile U_MFBC_OUT_FORMAT               MFBC_OUT_FORMAT              ;
    volatile unsigned int                    reserved0[14]                 ;      
    volatile U_MFBC_Y_DATA_BASE_ADDR_0       MFBC_Y_DATA_BASE_ADDR_0      ;
    volatile U_MFBC_Y_DATA_BASE_ADDR_1       MFBC_Y_DATA_BASE_ADDR_1      ;
    volatile U_MFBC_Y_DATA_LINE_STRIDE       MFBC_Y_DATA_LINE_STRIDE      ;
    volatile U_MFBC_Y_DATA_WR_BLENGTH        MFBC_Y_DATA_WR_BLENGTH       ;
    volatile unsigned int                    reserved1[12]                 ; 
    volatile U_MFBC_Y_HEAD_DATA_BASE_ADDR_0  MFBC_Y_HEAD_DATA_BASE_ADDR_0 ;
    volatile U_MFBC_Y_HEAD_DATA_BASE_ADDR_1  MFBC_Y_HEAD_DATA_BASE_ADDR_1 ;
    volatile U_MFBC_Y_HEAD_DATA_LINE_STRIDE  MFBC_Y_HEAD_DATA_LINE_STRIDE ;
    volatile U_MFBC_Y_HEAD_DATA_WR_BLENGTH   MFBC_Y_HEAD_DATA_WR_BLENGTH  ;
    volatile unsigned int                    reserved2[12]                 ; 
    volatile U_MFBC_UV_DATA_BASE_ADDR_0      MFBC_UV_DATA_BASE_ADDR_0     ;
    volatile U_MFBC_UV_DATA_BASE_ADDR_1      MFBC_UV_DATA_BASE_ADDR_1     ;
    volatile U_MFBC_UV_DATA_LINE_STRIDE      MFBC_UV_DATA_LINE_STRIDE     ;
    volatile U_MFBC_UV_DATA_WR_BLENGTH       MFBC_UV_DATA_WR_BLENGTH      ;
    volatile unsigned int                    reserved3[12]                 ; 
    volatile U_MFBC_UV_HEAD_DATA_BASE_ADDR_0 MFBC_UV_HEAD_DATA_BASE_ADDR_0;
    volatile U_MFBC_UV_HEAD_DATA_BASE_ADDR_1 MFBC_UV_HEAD_DATA_BASE_ADDR_1;
    volatile U_MFBC_UV_HEAD_DATA_LINE_STRIDE MFBC_UV_HEAD_DATA_LINE_STRIDE;
    volatile U_MFBC_UV_HEAD_DATA_WR_BLENGTH  MFBC_UV_HEAD_DATA_WR_BLENGTH ;
}S_MFBC_CORE_REGS_TYPE;

int MFBC_CORE_DRV_SET_InputSize(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_OutFormat(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YHeadDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YHeadDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YHeadDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_YHeadDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVHeadDataBase0(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVHeadDataBase1(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVHeadDataLineStride(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
int MFBC_CORE_DRV_SET_UVHeadDataWrBlen(S_MFBC_CORE_REGS_TYPE *pstRegs, unsigned int uData);
//debug
int MFBC_CORE_DRV_GET_CoreRegsVal(S_MFBC_CORE_REGS_TYPE *pstRegs);
#endif /*_MFBC_CORE_REG_DEF_H_*/