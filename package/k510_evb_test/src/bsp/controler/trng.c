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
#include <stdlib.h>
#include "platform.h"
#include "trng.h"

volatile puf_t *const puf = (volatile puf_t *)PUF_REGISTER_ADDR;

int wait_us_1000(volatile uint32_t* register_addr, int mode)
{
    int wait_time = 1000;
    while(*register_addr != mode)
    {
        usleep(1);
        wait_time--;
        if(wait_time < 0)
            return -1;
    }
    return 0;
} 

#define check_pgm_busy_error() wait_us_1000(&puf->puf_reg_pgm_busy_addr, PUF_REG_PGM_READY)

int puf_init(puf_mode_t puf_mode)
{
    puf->puf_reg_enable_addr = PUF_REG_ENABLE_ENABLE;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_mode_addr = puf_mode;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_mode_en_addr = PUF_REG_MODE_EN_ENABLE;
    if(check_pgm_busy_error()) return -1;
    wait_us_1000(&puf->puf_reg_mode_sta_addr, puf_mode);
    return 0;
}

int lp_puf_init()
{
    puf->puf_reg_enable_addr = PUF_REG_ENABLE_ENABLE;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_test_row_addr = 0;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_trng_lp_en_addr = PUF_REG_TRNG_LP_ENABLE;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_mode_addr = PUF_REG_MODE_TRNG_OUTPUT;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_mode_en_addr = PUF_REG_MODE_EN_ENABLE;
    if(check_pgm_busy_error()) return -1;
    wait_us_1000(&puf->puf_reg_mode_sta_addr, PUF_REG_MODE_TRNG_OUTPUT);
    return 0;
}

int puf_disable()
{
    puf->puf_reg_mode_addr = PUF_REG_MODE_DEEP_STANDBY;
    if(check_pgm_busy_error()) return -1;
    puf->puf_reg_mode_en_addr = PUF_REG_MODE_EN_ENABLE;
    if(check_pgm_busy_error()) return -1;
    wait_us_1000(&puf->puf_reg_mode_sta_addr, PUF_REG_MODE_DEEP_STANDBY);
    puf->puf_reg_enable_addr = PUF_REG_ENABLE_DISABLE;
    if(check_pgm_busy_error()) return -1;
    return 0;
}

int check_trng_valid()
{
    if(wait_us_1000(&puf->puf_reg_trng_output_valid_addr, 1))
        return -1;
    return 0;
}

uint32_t get_trng()
{
    return puf->puf_reg_trng_output_addr;
}

int trng_lp_en()
{
    puf->puf_reg_trng_lp_en_addr = PUF_REG_TRNG_LP_ENABLE;
    if(check_pgm_busy_error()) 
        return -1;
    else
        return 0;    
}