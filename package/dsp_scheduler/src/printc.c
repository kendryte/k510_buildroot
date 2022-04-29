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

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "types.h"
#include "cache.h"
#include "printc.h"
#include "scheduler.h"

static uint32_t log_addr[MAX_NUM_DSP_TASKS];
static uint32_t cur_addr[MAX_NUM_DSP_TASKS];
static uint32_t log_len[MAX_NUM_DSP_TASKS];

static char sprint_buf[1024];

int printc_init(uint32_t log_id, uint32_t start_addr, uint32_t len)
{
    log_addr[log_id] = start_addr;
    cur_addr[log_id] = start_addr;
    log_len[log_id] = len;
    printf("%s>log_id %d, cur_addr 0x%x, log_len %d\n", __FUNCTION__, log_id, cur_addr[log_id], log_len[log_id]);
}

int printc(uint32_t log_id, char *fmt, ...)
{
    va_list args;
    int n;

    if(log_addr[log_id] == 0)
    {
        printf("printc error: no buffer for task %d\n", log_id);
    }
    
    va_start(args, fmt);
    n = vsprintf(sprint_buf, fmt, args);
    va_end(args);


    if((cur_addr[log_id] + n) > (log_addr[log_id] + log_len[log_id]))
    {
        int remain_len = (log_addr[log_id] + log_len[log_id]) - cur_addr[log_id];
        memcpy(cur_addr[log_id], sprint_buf, remain_len);
        
        // printf("log overflow, print from begining.\n");
        
        memcpy(log_addr[log_id], sprint_buf[remain_len], n - remain_len);
        cur_addr[log_id] = log_addr[log_id] + n - remain_len;
        //printf("cur_addr[%d] = 0x%08x\n", log_id, cur_addr[log_id]);
    }
    else
    {
        memcpy(cur_addr[log_id], sprint_buf, n);
        cur_addr[log_id] += n;
        //printf("cur_addr[%d] = 0x%08x\n", log_id, cur_addr[log_id]);
    }
    return n;
}

int printc_deinit(uint32_t log_id)
{    
    cache_wb(log_addr[log_id], log_addr[log_id], log_len[log_id]);    
    log_addr[log_id] = 0;
    cur_addr[log_id] = 0;
    log_len[log_id] = 0;
}