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

/******************************************************************************
  File Name     : dsp_tasks.h
  Version       : 0.1
  Description   : dsp task related definition

******************************************************************************/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    DSP_TASK_ENABLE = 0x10000000,
    DSP_TASK_DISABLE,
    DSP_TASK_PRINT_INFO,
    DSP_TASK_USER_MSG,
    MAX_NUM_DSP_TASK_MSG
} DspTaskMsg;


typedef struct tDSP_MESSAGE
{
    DspTaskMsg      msgId;         /**<Message ID*/
    unsigned int    msg_phyAddr;   /**<Message content, shared memory physical address
                                      when msgId is DSP_TASK_ENABLE, it is
                                      buffer address for print log
                                   */
    unsigned int    len;           /**<Length of message*/
} DSP_MESSAGE;


#ifdef __cplusplus
}
#endif

