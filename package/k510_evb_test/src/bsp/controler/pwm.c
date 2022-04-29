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