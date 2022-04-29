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
  File Name     : scheduler.h
  Version       : 0.1
  Description   : DSP scheduler head file

******************************************************************************/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dsp_tasks.h"

//Each task on DSP uses one mailbox channel to communicate with CPU
//mailbox channel number is decided by CPU and DSP software

typedef enum
{
    DSP_TASK_0_CH = 0, 
    DSP_TASK_1_CH,
    DSP_TASK_2_CH,
    DSP_TASK_3_CH,
    DSP_TASK_4_CH,
    DSP_TASK_5_CH,
    DSP_TASK_6_CH,
    DSP_TASK_7_CH,
    MAX_NUM_DSP_TASKS
} DspTaskChannel;


typedef enum
{
    SCHE_SUCCESS = 0, 
    SCHE_ERR = 1,
}ScheStatus;

typedef enum
{
    SCHE_RUN_ONCE = 0, 
    SCHE_CONTINUE_RUN = 1,
}ScheRunType;

typedef struct DSP_TASK
{
    /**task name*/
    char *name;

    /**priority 0 to 255, 0 is the highest*/
    int priority;        

    /**init function
       return task context pointer
    */
    void *(*init)();

    /**deinit function*/
    void (*deinit)(void *arg);
    
    /**task process function
       return 0 means run once
       return 1 means conitune run
    */   
    ScheRunType (*run)(void *arg);     

    /**ISR callback
       for receiving msg from cpu
    */
    void (*rev_callback)(void *arg); 
    
    /**ISR callback
       for ack msg from cpu
    */
    void (*ack_callback)(void *arg);  
} DSP_TASK;

ScheStatus SCHE_TaskRegister(DSP_TASK *task, DspTaskChannel ch);

ScheStatus SCHE_SendMessage(DSP_MESSAGE *pMsg, DspTaskChannel ch);

ScheStatus SCHE_GetMessage(DSP_MESSAGE *pMsg, DspTaskChannel ch);

#ifdef __cplusplus
}
#endif

