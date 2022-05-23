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
#include "pwm.h"
#include <k510.h>

#define PWM_CLK 125000000UL

pwm_t *pwm[2] = {
    (pwm_t *)PWM0_BASE_ADDR,
    (pwm_t *)PWM1_BASE_ADDR,
};

void pwm_init(pwm_number_t num, pwm_param_t param)
{
    pwm[num]->pwmcfg = readl(&param.cfg);

    // uint32_t count_freq = PWM_CLK / ( 1 << param.cfg.scale);

    pwm[num]->pwmcmp0 = param.cmp0_val - 1;
    pwm[num]->pwmcmp1 = param.cmp0_val * param.cmp1_duty;
    pwm[num]->pwmcmp2 = param.cmp0_val * param.cmp2_duty;
    pwm[num]->pwmcmp3 = param.cmp0_val * param.cmp3_duty;
}

void pwm_start(pwm_number_t num, pwm_shot_mode_t shot_mode)
{
     if(shot_mode == PWM_ONESHOT)
     {
         pwm[num]->pwmcfg |= 1 << 13;
     }
     else
     {
         pwm[num]->pwmcfg |= 1 << 12;
     }
}

void pwm_stop(pwm_number_t num)
{
    pwm[num]->pwmcfg = pwm[num]->pwmcfg & (~(1 << 12));
}