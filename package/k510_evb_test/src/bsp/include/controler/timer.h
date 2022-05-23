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
#ifndef _DRIVER_TIMER_H
#define _DRIVER_TIMER_H

#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */
typedef struct _timer_channel
{
    /* TIMER_N Load Count Register              (0x00+(N-1)*0x14) */
    volatile uint32_t load_count;
    /* TIMER_N Current Value Register           (0x04+(N-1)*0x14) */
    volatile uint32_t current_value;
    /* TIMER_N Control Register                 (0x08+(N-1)*0x14) */
    volatile uint32_t control;
    /* TIMER_N Interrupt Clear Register         (0x0c+(N-1)*0x14) */
    volatile uint32_t eoi;
    /* TIMER_N Interrupt Status Register        (0x10+(N-1)*0x14) */
    volatile uint32_t intr_stat;
} __attribute__((packed, aligned(4))) timer_channel_t;

typedef struct _kendryte_timer
{
    /* TIMER_N Register                         (0x00-0x4c) */
    volatile timer_channel_t channel[4];
    /* reserverd                                (0x50-0x9c) */
    volatile uint32_t resv1[20];
    /* TIMER Interrupt Status Register          (0xa0) */
    volatile uint32_t intr_stat;
    /* TIMER Interrupt Clear Register           (0xa4) */
    volatile uint32_t eoi;
    /* TIMER Raw Interrupt Status Register      (0xa8) */
    volatile uint32_t raw_intr_stat;
    /* TIMER Component Version Register         (0xac) */
    volatile uint32_t comp_version;
    /* TIMER_N Load Count2 Register             (0xb0-0xbc) */
    volatile uint32_t load_count2[4];
} __attribute__((packed, aligned(4))) kendryte_timer_t;

typedef enum _timer_deivce_number
{
    TIMER_DEVICE_0,
    TIMER_DEVICE_MAX,
} timer_device_number_t;

typedef enum _timer_channel_number
{
    TIMER_CHANNEL_0,
    TIMER_CHANNEL_1,
    TIMER_CHANNEL_2,
    TIMER_CHANNEL_3,
    TIMER_CHANNEL_4,
    TIMER_CHANNEL_5,
    TIMER_CHANNEL_MAX,
} timer_channel_number_t;

/* TIMER Control Register */
#define TIMER_CR_ENABLE             0x00000001
#define TIMER_CR_MODE_MASK          0x00000002
#define TIMER_CR_FREE_MODE          0x00000000
#define TIMER_CR_USER_MODE          0x00000002
#define TIMER_CR_INTERRUPT_MASK     0x00000004
#define TIMER_CR_PWM_ENABLE         0x00000008
/* clang-format on */

extern volatile kendryte_timer_t *const timer[1];

/**
 * @brief       Definitions for the timer callbacks
 */
typedef int (*timer_callback_t)(void *ctx);

/**
 * @brief       Set timer timeout
 *
 * @param[in]   timer           timer
 * @param[in]   channel         channel
 * @param[in]   nanoseconds     timeout
 *
 * @return      the real timeout
 */
size_t timer_set_interval(timer_device_number_t timer_number, timer_channel_number_t channel, size_t nanoseconds);

/**
 * @brief       Init timer
 *
 * @param[in]   timer       timer
 */
void timer_init(timer_device_number_t timer_number);

/**
 * @brief       [DEPRECATED] Set timer timeout function
 *
 * @param[in]   timer           timer
 * @param[in]   channel         channel
 * @param[in]   func            timeout function
 * @param[in]   priority        interrupt priority
 *
 */
void timer_set_irq(timer_device_number_t timer_number, timer_channel_number_t channel, void (*func)(), uint32_t priority);

/**
 * @brief      Register timer interrupt user callback function
 *
 * @param[in]  device       The timer device number
 * @param[in]  channel      The channel
 * @param[in]  is_one_shot  Indicates if single shot
 * @param[in]  priority     The priority
 * @param[in]  callback     The callback function
 * @param[in]  ctx          The context
 *
 * @return     result
 *     - 0      Success
 *     - Other  Fail
 */
int timer_irq_register(timer_device_number_t device, timer_channel_number_t channel, int is_single_shot, uint32_t priority, timer_callback_t callback, void *ctx);

/**
 * @brief      Deregister timer interrupt user callback function
 *
 * @param[in]  device   The timer device number
 * @param[in]  channel  The channel
 *
 * @return     result
 *     - 0      Success
 *     - Other  Fail
 */
int timer_irq_unregister(timer_device_number_t device, timer_channel_number_t channel);

/**
 * @brief       Enable timer
 *
 * @param[in]   timer       timer
 * @param[in]   channel     channel
 * @param[in]   enable      Enable or disable
 *
 */
void timer_set_enable(timer_device_number_t timer_number, timer_channel_number_t channel, uint32_t enable);

void timer_pause_enable(timer_channel_number_t channel);

void timer_pause_disable(timer_channel_number_t channel);

uint32_t timer_get_count(timer_device_number_t timer_number, timer_channel_number_t channel);
#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_TIMER_H */
