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
#ifndef __HAL_COMM__
#define __HAL_COMM__

#ifdef _cplusplus
extern "C" {
#endif

#include <pthread.h>

#define dbgmsg(fmt, ...) printf("%s:%s[%d]: " fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define free_mem(p) do { if (NULL != p) {free (p); p = NULL;} } while (0)

typedef enum 
{
    HAL_FAILURE = -1,
    HAL_SUCCESS = 0,
    HAL_RET_END
} result_e;

typedef pthread_mutex_t mutex_t;
#define mutex_init(x)   pthread_mutex_init(&x, NULL)
#define mutex_deinit(x) pthread_mutex_destroy(&x)
#define mutex_lock(x)   pthread_mutex_lock(&x)
#define mutex_unlock(x) pthread_mutex_unlock(&x)

#ifdef _cplusplus
}
#endif

#endif /*__HAL_WIFI__*/