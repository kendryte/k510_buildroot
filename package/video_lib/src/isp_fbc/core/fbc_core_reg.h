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
 * fbc_core_reg.h
 *
 * CANAAN ISP - header definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _FBC_CORE_REG_H_
#define _FBC_CORE_REG_H_

typedef union { /* FBC_InputSize */
    /* Define the struct bits */
    struct 
    {
        unsigned int height                      : 13;
        unsigned int reserved0                   : 3;
        unsigned int width                       : 13;
        unsigned int reserved1                   : 3;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_INPUT_SIZE;

typedef union { /* FBC_OutFormat */
    /* Define the struct bits */
    struct 
    {
        unsigned int disable420                  : 1;
        unsigned int reserved0                   : 31;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_OUT_FORMAT;
/*Y*/
typedef union { /* FBC_Y_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_Y_DATA_BASE_ADDR_0;

typedef union { /* FBC_Y_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_Y_DATA_BASE_ADDR_1;

typedef union { /* FBC_Y_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_Y_DATA_LINE_STRIDE;

typedef union { /* FBC_Y_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_FBC_Y_DATA_WR_BLENGTH;
/*Y HEAD*/
typedef union { /* FBC_Y_HEAD_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_Y_HEAD_DATA_BASE_ADDR_0;

typedef union { /* FBC_Y_HEAD_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_Y_HEAD_DATA_BASE_ADDR_1;

typedef union { /* FBC_Y_HEAD_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_Y_HEAD_DATA_LINE_STRIDE;

typedef union { /* FBC_Y_HEAD_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_FBC_Y_HEAD_DATA_WR_BLENGTH;
/*UV*/
typedef union { /* FBC_UV_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_UV_DATA_BASE_ADDR_0;

typedef union { /* FBC_UV_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_UV_DATA_BASE_ADDR_1;

typedef union { /* FBC_UV_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_UV_DATA_LINE_STRIDE;

typedef union { /* FBC_UV_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_FBC_UV_DATA_WR_BLENGTH;
/*UV HEAD*/
typedef union { /* FBC_UV_HEAD_DATA_BASE_ADDR_0 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr0                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_UV_HEAD_DATA_BASE_ADDR_0;

typedef union { /* FBC_UV_HEAD_DATA_BASE_ADDR_1 */
    /* Define the struct bits */
    struct 
    {
        unsigned int addr1                      : 32;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_UV_HEAD_DATA_BASE_ADDR_1;

typedef union { /* FBC_UV_HEAD_DATA_LINE_STRIDE */
    /* Define the struct bits */
    struct 
    {
        unsigned int stride                      : 15;
        unsigned int reserved0                   : 17;
    } bits; /* Define an unsigned member */
    unsigned int u32;
} U_FBC_UV_HEAD_DATA_LINE_STRIDE;

typedef union { /* FBC_UV_HEAD_DATA_WR_BLENGTH */
    /* Define the struct bits */
    struct 
    {
        unsigned int blen                        : 5;
        unsigned int reserved0                   : 27;
    } bits; /* Define an unsigned member */
    unsigned int u32;    
} U_FBC_UV_HEAD_DATA_WR_BLENGTH;

#define  FBC_CORE_INPUT_SIZE                   (0x0000)
#define  FBC_CORE_OUT_FORMAT                   (0x0004)
												
#define  FBC_CORE_Y_DATA_BASE_ADDR_0           (0x0010)
#define  FBC_CORE_Y_DATA_BASE_ADDR_1           (0x0014)
#define  FBC_CORE_Y_DATA_LINE_STRIDE           (0x0018)
#define  FBC_CORE_Y_DATA_WR_BLENGTH            (0x001C)
#define  FBC_CORE_Y_HEAD_DATA_BASE_ADDR_0      (0x0020)
#define  FBC_CORE_Y_HEAD_DATA_BASE_ADDR_1      (0x0024)
#define  FBC_CORE_Y_HEAD_DATA_LINE_STRIDE      (0x0028)
#define  FBC_CORE_Y_HEAD_DATA_WR_BLENGTH       (0x002C)
#define  FBC_CORE_UV_DATA_BASE_ADDR_0          (0x0030)
#define  FBC_CORE_UV_DATA_BASE_ADDR_1          (0x0034)
#define  FBC_CORE_UV_DATA_LINE_STRIDE          (0x0038)
#define  FBC_CORE_UV_DATA_WR_BLENGTH           (0x003C)
#define  FBC_CORE_UV_HEAD_DATA_BASE_ADDR_0     (0x0040)
#define  FBC_CORE_UV_HEAD_DATA_BASE_ADDR_1     (0x0044)
#define  FBC_CORE_UV_HEAD_DATA_LINE_STRIDE     (0x0048)
#define  FBC_CORE_UV_HEAD_DATA_WR_BLENGTH      (0x004C)

#endif /*_FBC_CORE_REG_H_*/