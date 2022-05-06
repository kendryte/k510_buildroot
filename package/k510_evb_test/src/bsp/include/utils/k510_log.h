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
#ifndef _SYSLOG_H
#define _SYSLOG_H

#include <stdint.h>
#include <stdio.h>
#include <core_v5.h>
#ifdef _SIMU
#include <atomic.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Logging library
 *
 * Log library has two ways of managing log verbosity: compile time, set via
 * menuconfig
 *
 * At compile time, filtering is done using CONFIG_LOG_DEFAULT_LEVEL macro, set via
 * menuconfig. All logging statments for levels higher than CONFIG_LOG_DEFAULT_LEVEL
 * will be removed by the preprocessor.
 *
 *
 * How to use this library:
 *
 * In each C file which uses logging functionality, define TAG variable like this:
 *
 *      static const char *TAG = "MODULE_NAME";
 *
 * then use one of logging macros to produce output, e.g:
 *
 *      LOGW(TAG, "Interrupt error %d", error);
 *
 * Several macros are available for different verbosity levels:
 *
 *      LOGE - error
 *      LOGW - warning
 *      LOGI - info
 *      LOGD - debug
 *      LOGV - verbose
 *
 * To override default verbosity level at file or component scope, define LOG_LEVEL macro.
 * At file scope, define it before including esp_log.h, e.g.:
 *
 *      #define LOG_LEVEL LOG_VERBOSE
 *      #include "dxx_log.h"
 *
 * At component scope, define it in component makefile:
 *
 *      CFLAGS += -D LOG_LEVEL=LOG_DEBUG
 *
 *
 */

/* clang-format off */
enum maix_log_level_e {
    LOG_NONE,       /*!< No log output */
    LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    LOG_INFO,       /*!< Information messages which describe normal flow of events */
    LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
};
/* clang-format on */

/* clang-format off */
#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V
#else /* CONFIG_LOG_COLORS */
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif /* CONFIG_LOG_COLORS */
/* clang-format on */

/* level, counter, state: */
#ifdef _HAVE_DBG_LOG_INT_
uint32_t g_dbg_log_lvl = LOG_INFO;
#else
extern uint32_t g_dbg_log_lvl;
#endif

#define k510_log_set_level( x ) (g_dbg_log_lvl = (x))
#define k510_log_disable() (g_dbg_log_lvl = (LOG_NONE))
#define k510_log_get_level()    (g_dbg_log_lvl)

#define LOGTC_FORMAT(letter, format)  LOG_COLOR_ ## letter "(%lu) %s: " format LOG_RESET_COLOR "\n"
#define LOGT_FORMAT(letter, format)   LOG_COLOR_ ## letter "%s: " format LOG_RESET_COLOR "\n"
#define LOGC_FORMAT(letter, format)   LOG_COLOR_ ## letter "(%lu) : " format LOG_RESET_COLOR "\n"
#define LOG_FORMAT(letter, format)    LOG_COLOR_ ## letter "" format LOG_RESET_COLOR
#define LOGNTAB_FORMAT(letter, format)    LOG_COLOR_ ## letter "" format LOG_RESET_COLOR "\n"

#define LOG_PRINTF printf

#ifdef _SIMU
extern corelock_t lock;

#define k510_logtce(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_ERROR)   {corelock_lock(&lock);LOG_PRINTF(LOGTC_FORMAT(E, format), read_cycle(), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtcw(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_WARN)    {corelock_lock(&lock);LOG_PRINTF(LOGTC_FORMAT(W, format), read_cycle(), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtci(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_INFO)    {corelock_lock(&lock);LOG_PRINTF(LOGTC_FORMAT(I, format), read_cycle(), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtcd(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_DEBUG)   {corelock_lock(&lock);LOG_PRINTF(LOGTC_FORMAT(D, format), read_cycle(), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtcv(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_VERBOSE) {corelock_lock(&lock);LOG_PRINTF(LOGTC_FORMAT(V, format), read_cycle(), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)

#define k510_logte(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_ERROR)   {corelock_lock(&lock);LOG_PRINTF(LOGT_FORMAT(E, format), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtw(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_WARN)    {corelock_lock(&lock);LOG_PRINTF(LOGT_FORMAT(W, format), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logti(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_INFO)    {corelock_lock(&lock);LOG_PRINTF(LOGT_FORMAT(I, format), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtd(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_DEBUG)   {corelock_lock(&lock);LOG_PRINTF(LOGT_FORMAT(D, format), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logtv(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_VERBOSE) {corelock_lock(&lock);LOG_PRINTF(LOGT_FORMAT(V, format), tag, ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)

#define k510_logce(format, ...)           do {if (g_dbg_log_lvl >= LOG_ERROR)   {corelock_lock(&lock);LOG_PRINTF(LOGC_FORMAT(E, format), read_cycle(), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logcw(format, ...)           do {if (g_dbg_log_lvl >= LOG_WARN)    {corelock_lock(&lock);LOG_PRINTF(LOGC_FORMAT(W, format), read_cycle(), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logci(format, ...)           do {if (g_dbg_log_lvl >= LOG_INFO)    {corelock_lock(&lock);LOG_PRINTF(LOGC_FORMAT(I, format), read_cycle(), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logcd(format, ...)           do {if (g_dbg_log_lvl >= LOG_DEBUG)   {corelock_lock(&lock);LOG_PRINTF(LOGC_FORMAT(D, format), read_cycle(), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logcv(format, ...)           do {if (g_dbg_log_lvl >= LOG_VERBOSE) {corelock_lock(&lock);LOG_PRINTF(LOGC_FORMAT(V, format), read_cycle(), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)

#define k510_loge(format, ...)            do {if (g_dbg_log_lvl >= LOG_ERROR)   {corelock_lock(&lock);LOG_PRINTF(LOG_FORMAT(E, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logw(format, ...)            do {if (g_dbg_log_lvl >= LOG_WARN)    {corelock_lock(&lock);LOG_PRINTF(LOG_FORMAT(W, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logi(format, ...)            do {if (g_dbg_log_lvl >= LOG_INFO)    {corelock_lock(&lock);LOG_PRINTF(LOG_FORMAT(I, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logd(format, ...)            do {if (g_dbg_log_lvl >= LOG_DEBUG)   {corelock_lock(&lock);LOG_PRINTF(LOG_FORMAT(D, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logv(format, ...)            do {if (g_dbg_log_lvl >= LOG_VERBOSE) {corelock_lock(&lock);LOG_PRINTF(LOG_FORMAT(V, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)

#define k510_logntabe(format, ...)        do {if (g_dbg_log_lvl >= LOG_ERROR)   {corelock_lock(&lock);LOG_PRINTF(LOGNTAB_FORMAT(E, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logntabw(format, ...)        do {if (g_dbg_log_lvl >= LOG_WARN)    {corelock_lock(&lock);LOG_PRINTF(LOGNTAB_FORMAT(W, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logntabi(format, ...)        do {if (g_dbg_log_lvl >= LOG_INFO)    {corelock_lock(&lock);LOG_PRINTF(LOGNTAB_FORMAT(I, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logntabd(format, ...)        do {if (g_dbg_log_lvl >= LOG_DEBUG)   {corelock_lock(&lock);LOG_PRINTF(LOGNTAB_FORMAT(D, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)
#define k510_logntabv(format, ...)        do {if (g_dbg_log_lvl >= LOG_VERBOSE) {corelock_lock(&lock);LOG_PRINTF(LOGNTAB_FORMAT(V, format), ##__VA_ARGS__); corelock_unlock(&lock);}} while (0)

#else

#define k510_logtce(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_ERROR)   LOG_PRINTF(LOGTC_FORMAT(E, format), read_cycle(), tag, ##__VA_ARGS__); } while (0)
#define k510_logtcw(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_WARN)    LOG_PRINTF(LOGTC_FORMAT(W, format), read_cycle(), tag, ##__VA_ARGS__); } while (0)
#define k510_logtci(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_INFO)    LOG_PRINTF(LOGTC_FORMAT(I, format), read_cycle(), tag, ##__VA_ARGS__); } while (0)
#define k510_logtcd(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_DEBUG)   LOG_PRINTF(LOGTC_FORMAT(D, format), read_cycle(), tag, ##__VA_ARGS__); } while (0)
#define k510_logtcv(tag, format, ...)     do {if (g_dbg_log_lvl >= LOG_VERBOSE) LOG_PRINTF(LOGTC_FORMAT(V, format), read_cycle(), tag, ##__VA_ARGS__); } while (0)

#define k510_logte(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_ERROR)   LOG_PRINTF(LOGT_FORMAT(E, format), tag, ##__VA_ARGS__); } while (0)
#define k510_logtw(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_WARN)    LOG_PRINTF(LOGT_FORMAT(W, format), tag, ##__VA_ARGS__); } while (0)
#define k510_logti(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_INFO)    LOG_PRINTF(LOGT_FORMAT(I, format), tag, ##__VA_ARGS__); } while (0)
#define k510_logtd(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_DEBUG)   LOG_PRINTF(LOGT_FORMAT(D, format), tag, ##__VA_ARGS__); } while (0)
#define k510_logtv(tag, format, ...)      do {if (g_dbg_log_lvl >= LOG_VERBOSE) LOG_PRINTF(LOGT_FORMAT(V, format), tag, ##__VA_ARGS__); } while (0)

#define k510_logce(format, ...)           do {if (g_dbg_log_lvl >= LOG_ERROR)   LOG_PRINTF(LOGC_FORMAT(E, format), read_cycle(), ##__VA_ARGS__); } while (0)
#define k510_logcw(format, ...)           do {if (g_dbg_log_lvl >= LOG_WARN)    LOG_PRINTF(LOGC_FORMAT(W, format), read_cycle(), ##__VA_ARGS__); } while (0)
#define k510_logci(format, ...)           do {if (g_dbg_log_lvl >= LOG_INFO)    LOG_PRINTF(LOGC_FORMAT(I, format), read_cycle(), ##__VA_ARGS__); } while (0)
#define k510_logcd(format, ...)           do {if (g_dbg_log_lvl >= LOG_DEBUG)   LOG_PRINTF(LOGC_FORMAT(D, format), read_cycle(), ##__VA_ARGS__); } while (0)
#define k510_logcv(format, ...)           do {if (g_dbg_log_lvl >= LOG_VERBOSE) LOG_PRINTF(LOGC_FORMAT(V, format), read_cycle(), ##__VA_ARGS__); } while (0)

#define k510_loge(format, ...)            do {if (g_dbg_log_lvl >= LOG_ERROR)   LOG_PRINTF(LOG_FORMAT(E, format), ##__VA_ARGS__); } while (0)
#define k510_logw(format, ...)            do {if (g_dbg_log_lvl >= LOG_WARN)    LOG_PRINTF(LOG_FORMAT(W, format), ##__VA_ARGS__); } while (0)
#define k510_logi(format, ...)            do {if (g_dbg_log_lvl >= LOG_INFO)    LOG_PRINTF(LOG_FORMAT(I, format), ##__VA_ARGS__); } while (0)
#define k510_logd(format, ...)            do {if (g_dbg_log_lvl >= LOG_DEBUG)   LOG_PRINTF(LOG_FORMAT(D, format), ##__VA_ARGS__); } while (0)
#define k510_logv(format, ...)            do {if (g_dbg_log_lvl >= LOG_VERBOSE) LOG_PRINTF(LOG_FORMAT(V, format), ##__VA_ARGS__); } while (0)

#define k510_logntabe(format, ...)        do {if (g_dbg_log_lvl >= LOG_ERROR)   LOG_PRINTF(LOGNTAB_FORMAT(E, format), ##__VA_ARGS__); } while (0)
#define k510_logntabw(format, ...)        do {if (g_dbg_log_lvl >= LOG_WARN)    LOG_PRINTF(LOGNTAB_FORMAT(W, format), ##__VA_ARGS__); } while (0)
#define k510_logntabi(format, ...)        do {if (g_dbg_log_lvl >= LOG_INFO)    LOG_PRINTF(LOGNTAB_FORMAT(I, format), ##__VA_ARGS__); } while (0)
#define k510_logntabd(format, ...)        do {if (g_dbg_log_lvl >= LOG_DEBUG)   LOG_PRINTF(LOGNTAB_FORMAT(D, format), ##__VA_ARGS__); } while (0)
#define k510_logntabv(format, ...)        do {if (g_dbg_log_lvl >= LOG_VERBOSE) LOG_PRINTF(LOGNTAB_FORMAT(V, format), ##__VA_ARGS__); } while (0)

#endif
#ifdef __cplusplus
}
#endif


#endif /* _SYSLOG_H */

