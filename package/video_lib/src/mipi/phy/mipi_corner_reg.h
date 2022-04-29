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
 * mipi_corner_reg.h
 *
 * CANAAN ISP - Registers definitions
 *
 * Contacts: zhu dalei <zhudalei@canaan-creative.com>
 */

#ifndef _MIPI_CORNER_REG_H_
#define _MIPI_CORNER_REG_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bg_apd                          : 1  ; /* [0 ]  */
        unsigned int    bg_selin                        : 1  ; /* [1 ]  */
        unsigned int    pvtcal_start                    : 1  ; /* [2 ]  */
        unsigned int    rst_n                           : 1  ; /* [3]  */
        unsigned int    v2i_apd                         : 1  ; /* [4]  */
        unsigned int    bypass                          : 1  ; /* [5]  */
        unsigned int    pvt_resword_bypass              : 16  ; /* [21..6]  */
        unsigned int    clk_div                         : 8  ; /* [29..22]  */
        unsigned int    reservd0                        : 2  ; /* [31..30]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_MIPI_CORNER_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvt_resword_core                :16  ; /* [15..0 ]  */
        unsigned int    pvtcal_done                     :1  ; /* [16 ]  */
        unsigned int    reservd0                        :15  ; /* [31..17]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} MIPI_CORNER_STA;

#define MIPI_CORNER_CFG        (0x0000)
#define MIPI_CORNER_STA        (0x0004)

#endif /*_MIPI_CORNER_REG_H_*/