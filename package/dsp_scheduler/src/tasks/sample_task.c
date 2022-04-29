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
  File Name     : sample_task.c
  Version       : 0.1
  Description   : sample task on dsp

******************************************************************************/
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cache.h"
#include "scheduler.h"


typedef struct
{
    DspTaskChannel ch;
    int sem;     
    int counter;
}sampleTaskContext;

typedef enum
{
    DSP_TASK_0_PROCESS_START,
    DSP_TASK_0_PROCESS_END,
    MAX_NUM_DSP_TASK_0_MSG
} Task0MsgID;

//the message should be defined in header file which is included by cpu
typedef struct tTASK0_MSG
{
    Task0MsgID  id;
    uint32_t src_phyAddr;
    uint32_t dst_phyAddr;
    uint32_t data_size;
}TASK0_MESSAGE;   


void *sample_task_init()
{
    sampleTaskContext *pArg;

    pArg = (sampleTaskContext*)malloc(sizeof(sampleTaskContext));
    pArg->sem = 0;
    pArg->counter = 0;
    pArg->ch = DSP_TASK_0_CH;  //the number is from alltasks.c when register task
    printc(pArg->ch, "%s>\n", __FUNCTION__);
    return pArg;
}

ScheRunType sample_task_run(void *arg)
{    
    sampleTaskContext *pArg = (sampleTaskContext*)arg;

    pArg->counter++;

    if(pArg->sem)
    {
        DSP_MESSAGE revMsg;
        TASK0_MESSAGE *task0RevMsg;
        DSP_MESSAGE sendMsg;
        TASK0_MESSAGE *task0SendMsg;
        
        SCHE_GetMessage(&revMsg, pArg->ch);
        printc(pArg->ch, "%s>get msg id 0x%x\n", __FUNCTION__, revMsg.msgId);
        if(revMsg.msgId == DSP_TASK_USER_MSG)
        {
            task0RevMsg = (TASK0_MESSAGE *)revMsg.msg_phyAddr;
            if(task0RevMsg->id == DSP_TASK_0_PROCESS_START)
            {
                int i;
                uint8_t *pSrc, *pDst;

                pSrc = (uint8_t *)task0RevMsg->src_phyAddr;
                pDst = (uint8_t *)task0RevMsg->dst_phyAddr;
                for(i=0; i<task0RevMsg->data_size; i++)
                {
                    pDst[i] = pSrc[i]*2;
                }
                cache_wb(task0RevMsg->dst_phyAddr, task0RevMsg->dst_phyAddr, task0RevMsg->data_size);

                sendMsg.msgId = DSP_TASK_USER_MSG;
                sendMsg.msg_phyAddr = revMsg.msg_phyAddr + sizeof(TASK0_MESSAGE);
                sendMsg.len = sizeof(TASK0_MESSAGE);
                
                task0SendMsg = (TASK0_MESSAGE*)(sendMsg.msg_phyAddr);
                task0SendMsg->id = DSP_TASK_0_PROCESS_END;
                task0SendMsg->src_phyAddr = task0RevMsg->src_phyAddr;
                task0SendMsg->dst_phyAddr = task0RevMsg->dst_phyAddr;
                                
                printc(pArg->ch, "%s>send message: msg_phyAddr 0x%x\n", __FUNCTION__, sendMsg.msg_phyAddr);
                SCHE_SendMessage(&sendMsg, pArg->ch);
            }
        }
        else
        {
            printc(pArg->ch, "%s>unknown message 0x%x\n", __FUNCTION__, revMsg.msgId);
        }
        pArg->sem = 0;
    }    

    return SCHE_CONTINUE_RUN;  
}

int sample_task_deinit(void *arg)
{    
    sampleTaskContext *pArg = (sampleTaskContext*)arg;
    DspTaskChannel ch;

    ch = pArg->ch;
    free(arg);
    printc(ch, "%s>\n", __FUNCTION__);
    return 0;  
}

void sample_task_callback(void *arg)
{    
    sampleTaskContext *pArg = (sampleTaskContext*)arg;

    pArg->sem = 1;
    printc(pArg->ch, "%s>\n", __FUNCTION__);
}

void sample_ack_callback(void *arg)
{    
    sampleTaskContext *pArg = (sampleTaskContext*)arg;
    printc(pArg->ch, "%s>\n", __FUNCTION__);
}


DSP_TASK dsp_sample_task = {
    .name             = "sample task",
    .priority         = 2,
    .init             = sample_task_init,
    .deinit           = sample_task_deinit,
    .run              = sample_task_run,
    .rev_callback     = sample_task_callback,
    .ack_callback     = sample_ack_callback,
};


