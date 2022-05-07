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

#ifndef _MIPI_RXDPHY_DEF_H_
#define _MIPI_RXDPHY_DEF_H_

typedef enum
{
    RXDPHY_SPEED_MODE_2500M,
    RXDPHY_SPEED_MODE_1500M,
    RXDPHY_SPEED_MODE_MAX,
} rxdphy_speed_mode_t;

typedef enum
{
    RXDPHY_CHCFG_2X2,
    RXDPHY_CHCFG_1X4,
    RXDPHY_CHCFG_MAX,
} rxdphy_chcfg_t;


void mipi_rxdphy_init(rxdphy_speed_mode_t speed,rxdphy_chcfg_t chcfg);
unsigned int mipi_rxdphy_get_status(void);
unsigned int mipi_rxdphy_get_errstatus(void);
void mipi_rxdphy_standy(void);
void mipi_rxdphy_enable_deskew(void);
void mipi_rxdphy_disable_deskew(void);
void mipi_rxdphy_invert_lane(int lane);
void mipi_rxdphy_set_tclktermen(int enable);
void mipi_rxdphy_set_thstermen(int enable);
void mipi_rxdphy_set_thssettle(int value);
void mipi_rxdphy_settclkmiss(int value);
void mipi_rxdphy_set_tclksettle(int value);

#endif /*_MIPI_RXDPHY_DEF_H_*/
