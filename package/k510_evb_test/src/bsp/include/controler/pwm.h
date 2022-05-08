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
// See LICENSE for license details.
#ifndef HBIRD_PWM_H
#define HBIRD_PWM_H
#include <stdint.h>
#include <stdbool.h>

/* Register offsets */

#define PWM_CFG_SCALE 0x0000000F
#define PWM_CFG_STICKY 0x00000100
#define PWM_CFG_ZEROCMP 0x00000200
#define PWM_CFG_DEGLITCH 0x00000400
#define PWM_CFG_ENALWAYS 0x00001000
#define PWM_CFG_ONESHOT 0x00002000
#define PWM_CFG_CMP0CENTER 0x00010000
#define PWM_CFG_CMP1CENTER 0x00020000
#define PWM_CFG_CMP2CENTER 0x00040000
#define PWM_CFG_CMP3CENTER 0x00080000
#define PWM_CFG_CMP0GANG 0x01000000
#define PWM_CFG_CMP1GANG 0x02000000
#define PWM_CFG_CMP2GANG 0x04000000
#define PWM_CFG_CMP3GANG 0x08000000
#define PWM_CFG_CMP0IP 0x10000000
#define PWM_CFG_CMP1IP 0x20000000
#define PWM_CFG_CMP2IP 0x40000000
#define PWM_CFG_CMP3IP 0x80000000

#define PWM_SCALE_MASK (0x0000000F)

#define pwm_set_scale(num, scale)       (pwm[num]->pwmcfg = (pwm[num]->pwmcfg & (~PWM_SCALE_MASK)) | scale)
#define pwm_set_sticky(num)             (pwm[num]->pwmcfg |= (1 << 8))
#define pwm_clear_sticky(num)           (pwm[num]->pwmcfg &= ~(1 << 8))
#define pwm_set_zerocmp(num)            (pwm[num]->pwmcfg |= (1 << 9))
#define pwm_clear_zerocmp(num)          (pwm[num]->pwmcfg &= ~(1 << 9))
#define pwm_set_deglitch(num)           (pwm[num]->pwmcfg |= (1 << 10))
#define pwm_clear_deglitch(num)         (pwm[num]->pwmcfg &= ~(1 << 10))

#define pwm_set_cmp0center(num)         (pwm[num]->pwmcfg |= 1 << 16)
#define pwm_set_cmp1center(num)         (pwm[num]->pwmcfg |= 1 << 17)
#define pwm_set_cmp2center(num)         (pwm[num]->pwmcfg |= 1 << 18)
#define pwm_set_cmp3center(num)         (pwm[num]->pwmcfg |= 1 << 19)
#define pwm_clear_cmp0center(num)       (pwm[num]->pwmcfg &= ~(1 << 16))
#define pwm_clear_cmp1center(num)       (pwm[num]->pwmcfg &= ~(1 << 17))
#define pwm_clear_cmp2center(num)       (pwm[num]->pwmcfg &= ~(1 << 18))
#define pwm_clear_cmp3center(num)       (pwm[num]->pwmcfg &= ~(1 << 19))

#define pwm_set_cmp0gang(num)         (pwm[num]->pwmcfg |= 1 << 24)
#define pwm_set_cmp1gang(num)         (pwm[num]->pwmcfg |= 1 << 25)
#define pwm_set_cmp2gang(num)         (pwm[num]->pwmcfg |= 1 << 26)
#define pwm_set_cmp3gang(num)         (pwm[num]->pwmcfg |= 1 << 27)
#define pwm_clear_cmp0gang(num)       (pwm[num]->pwmcfg &= ~(1 << 24))
#define pwm_clear_cmp1gang(num)       (pwm[num]->pwmcfg &= ~(1 << 25))
#define pwm_clear_cmp2gang(num)       (pwm[num]->pwmcfg &= ~(1 << 26))
#define pwm_clear_cmp3gang(num)       (pwm[num]->pwmcfg &= ~(1 << 27))

#define pwm_set_cmp0val(num, val)          (pwm[num]->pwmcmp0 = val)
#define pwm_set_cmp1val(num, val)          (pwm[num]->pwmcmp1 = val)
#define pwm_set_cmp2val(num, val)          (pwm[num]->pwmcmp2 = val)
#define pwm_set_cmp3val(num, val)          (pwm[num]->pwmcmp3 = val)

#define pwm_set_cmp1duty(num, duty)        (pwm[num]->pwmcmp1 = (pwm[num]->pwmcmp0 + 1) * duty)
#define pwm_set_cmp2duty(num, duty)        (pwm[num]->pwmcmp2 = (pwm[num]->pwmcmp0 + 1) * duty)
#define pwm_set_cmp3duty(num, duty)        (pwm[num]->pwmcmp3 = (pwm[num]->pwmcmp0 + 1) * duty)

#endif /* _HBIRD_PWM_H */
typedef struct
{
    volatile uint32_t pwmcfg;            /* 0x00 */
    volatile uint32_t reserved0;
    volatile uint32_t pwmcount;          /* 0x08 */
    volatile uint32_t reserved1;
    volatile uint32_t pwms;              /* 0x10 */
    volatile uint32_t reserved2;
    volatile uint32_t reserved3;
    volatile uint32_t reserved4;
    volatile uint32_t pwmcmp0;           /* 0x20 */
    volatile uint32_t pwmcmp1;           /* 0x24 */
    volatile uint32_t pwmcmp2;           /* 0x28 */
    volatile uint32_t pwmcmp3;           /* 0x2c */
} pwm_t;

typedef enum pwm_device
{
    pwmcmp1,
    pwmcmp2,
    pwmcmp3,
} pwm_device_t;

typedef enum pwm_irq
{
    pwmirq0,
    pwmirq1,
    pwmirq2,
    pwmirq3,
} pwm_irq_t;

typedef enum pwm_mode
{
    pwmmode,
    irqmode,
} pwm_mode_t;

typedef enum
{
    PWM_ONESHOT,
    PWM_ALWAYS,
} pwm_shot_mode_t;

typedef enum
{
    PWM_NUMBER0,
    PWM_NUMBER1,
    PWM_NUMBERMAX,
} pwm_number_t;

typedef struct
{
    uint32_t scale : 4;
    uint32_t reserve: 4;
    uint32_t sticky : 1;
    uint32_t zerocmp : 1;
    uint32_t deglitch : 1;
    uint32_t reserve1 : 5;
    uint32_t cmp0center : 1;
    uint32_t cmp1center : 1;
    uint32_t cmp2center : 1;
    uint32_t cmp3center : 1;
    uint32_t reserve2 : 4;
    uint32_t cmp0gang : 1;
    uint32_t cmp1gang : 1;
    uint32_t cmp2gang : 1;
    uint32_t cmp3gang : 1;
    uint32_t reserve3 : 4;
} pwm_cfg_t;

typedef struct
{
    pwm_cfg_t cfg;
    uint32_t  freq;
    uint32_t cmp0_val;
    double   cmp1_duty;
    double   cmp2_duty;
    double   cmp3_duty;
} pwm_param_t;

extern pwm_t *pwm[2];

void pwm_init(pwm_number_t num, pwm_param_t param);
void pwm_start(pwm_number_t num, pwm_shot_mode_t shot_mode);
void pwm_stop(pwm_number_t num);