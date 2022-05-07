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

#ifndef _MIPI_TXDPHY_DEF_H_
#define _MIPI_TXDPHY_DEF_H_

#define TXDPHY_PLL_891M_F           3563
#define TXDPHY_PLL_891M_R           24
#define TXDPHY_PLL_891M_D           3

#define TXDPHY_PLL_1782M_F          1781
#define TXDPHY_PLL_1782M_R          24
#define TXDPHY_PLL_1782M_D          0

#define TXDPHY_PLL_445M_F           1781
#define TXDPHY_PLL_445M_R           24
#define TXDPHY_PLL_445M_D           3

typedef enum
{
    TXDPHY_LANE_0 = 0,
    TXDPHY_LANE_1,
    TXDPHY_LANE_2,
    TXDPHY_LANE_3,
    TXDPHY_LANE_MAX,
} txdphy_lane_t;


void mipi_txdphy_set_pll(uint32_t fbdiv, uint32_t refdiv, uint32_t outdiv);
void mipi_txdphy_init(void);
void mipi_txdphy_set_enlp(txdphy_lane_t lane);
void mipi_txdphy_set_tlpx(uint32_t level);
void mipi_txdphy_set_tlpxesc(uint32_t level);
void mipi_txdphy_set_tclkprep(uint32_t level);
void mipi_txdphy_set_tclkprzero(uint32_t level);
void mipi_txdphy_set_tclktail(uint32_t level);
void mipi_txdphy_set_thsprep(uint32_t level);
void mipi_txdphy_set_thsprzero(uint32_t level);
void mipi_txdphy_set_thstrail(uint32_t level);


#endif /*_MIPI_TXDPHY_DEF_H_*/
