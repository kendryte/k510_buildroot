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
  File Name     : audio3a_task.c
  Version       : 0.1
  Description   : audio3a task on dsp

******************************************************************************/
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include "scheduler.h"
#include "audio3a.h"
#include <cache.h>

#define AUDIO_3A_MIN_SAMPLES  160
#define AUDIO_3A_INPUT_BUF_SIZE 1280

typedef struct
{
    DspTaskChannel ch;
    int sem;     
    int counter;
    int sample_rate;
}Audio3aTaskContext;

void* audio3a_task_init()
{
    Audio3aTaskContext *pArg;

    pArg = (Audio3aTaskContext*)malloc(sizeof(Audio3aTaskContext));
    pArg->sem = 0;
    pArg->counter = 0;
    pArg->ch = DSP_TASK_1_CH;  //the number is from alltasks.c when register task
    printc(pArg->ch, "%s>\n", __FUNCTION__);
    return pArg;
}

ScheRunType audio3a_task_run(void *arg)
{    
    Audio3aTaskContext *pArg = (Audio3aTaskContext*)arg;

    pArg->counter++;

    if(pArg->sem)
    {
        // printc(pArg->ch, "%s>start process messages\n", __FUNCTION__);
        DSP_MESSAGE revMsg;
        TASK1_MESSAGE *task1RevMsg;
        DSP_MESSAGE sendMsg;
        TASK1_MESSAGE *task1SendMsg;

        SCHE_GetMessage(&revMsg, pArg->ch);
        // printc(pArg->ch, "%s>get msg id 0x%x\n", __FUNCTION__, revMsg.msgId);

        if(revMsg.msgId == DSP_TASK_USER_MSG)
        {
            task1RevMsg = (TASK1_MESSAGE *)revMsg.msg_phyAddr;
            cache_inval(revMsg.msg_phyAddr, revMsg.msg_phyAddr, sizeof(TASK1_MESSAGE), L1_DCACHE);
            // printc(pArg->ch, "task1RevMsg->id: %d\n",task1RevMsg->id);
            if(task1RevMsg->id == DSP_TASK_1_AUDIO3A_INIT)
            {
                // printc(pArg->ch, "DSP_TASK_1_AUDIO3A_INIT\n");
                audio_3a_init(task1RevMsg->sample_rate, task1RevMsg->agcMode, task1RevMsg->nsLevel, task1RevMsg->aec_test_en);
                sendMsg.msgId = DSP_TASK_USER_MSG;
                sendMsg.msg_phyAddr = revMsg.msg_phyAddr + sizeof(TASK1_MESSAGE);
                // sendMsg.msg_phyAddr = revMsg.msg_phyAddr;
                sendMsg.len = sizeof(TASK1_MESSAGE);

                task1SendMsg = (TASK1_MESSAGE*)(sendMsg.msg_phyAddr);
                memset(task1SendMsg, 0, sizeof(TASK1_MESSAGE));
                task1SendMsg->id = DSP_TASK_1_AUDIO3A_INIT_DONE;
                task1SendMsg->sample_rate = task1RevMsg->sample_rate;
                task1SendMsg->agcMode = task1RevMsg->agcMode;
                task1SendMsg->nsLevel = task1RevMsg->nsLevel;
                task1SendMsg->aec_test_en = task1RevMsg->aec_test_en;

                // printc(pArg->ch, "%s>send message: msg_phyAddr 0x%x\n", __FUNCTION__, sendMsg.msg_phyAddr);
                // printc(pArg->ch, "%s>send message: msg_phyAddr 0x%x\n", __FUNCTION__, sendMsg.msg_phyAddr);
                // printc(pArg->ch, "sizeof(TASK1_MESSAGE): 0x%x\n", sizeof(TASK1_MESSAGE));
                // printc(pArg->ch, "task1SendMsg: 0x%x\n", task1SendMsg);
                // cache_wb(sendMsg, sendMsg, sizeof(DSP_MESSAGE));
                cache_wb(task1SendMsg, task1SendMsg, sizeof(TASK1_MESSAGE));
                SCHE_SendMessage(&sendMsg, pArg->ch);
                // printc(pArg->ch, "sended init done\n");
            }
            else if(task1RevMsg->id == DSP_TASK_1_AUDIO3A_PROCESS)
            {
                // printc(pArg->ch, "DSP_TASK_1_AUDIO3A_PROCESS\n");
                cache_inval(task1RevMsg->inbuf, task1RevMsg->inbuf, task1RevMsg->input_size, L1_DCACHE);
                audio_3a_process(task1RevMsg->inbuf, task1RevMsg->outbuf);
                cache_wb(task1RevMsg->outbuf, task1RevMsg->outbuf, task1RevMsg->output_size);
                sendMsg.msgId = DSP_TASK_USER_MSG;
                sendMsg.msg_phyAddr = revMsg.msg_phyAddr + sizeof(TASK1_MESSAGE);
                sendMsg.len = sizeof(TASK1_MESSAGE);

                task1SendMsg = (TASK1_MESSAGE*)(sendMsg.msg_phyAddr);
                memset(task1SendMsg, 0, sizeof(TASK1_MESSAGE));
                task1SendMsg->id = DSP_TASK_1_AUDIO3A_PROCESS_DONE;

                // printc(pArg->ch, "%s>send message: msg_phyAddr 0x%x\n", __FUNCTION__, sendMsg.msg_phyAddr);
                // cache_wb(sendMsg, sendMsg, sizeof(DSP_MESSAGE));
                cache_wb(task1SendMsg, task1SendMsg, sizeof(TASK1_MESSAGE));
                SCHE_SendMessage(&sendMsg, pArg->ch);
            }
            else if(task1RevMsg->id == DSP_TASK_1_AUDIO3A_DEINIT)
            {
                // printc(pArg->ch, "DSP_TASK_1_AUDIO3A_DEINIT\n");
                audio_3a_deinit();
                sendMsg.msgId = DSP_TASK_USER_MSG;
                sendMsg.msg_phyAddr = revMsg.msg_phyAddr + sizeof(TASK1_MESSAGE);
                sendMsg.len = sizeof(TASK1_MESSAGE);

                task1SendMsg = (TASK1_MESSAGE*)(sendMsg.msg_phyAddr);
                memset(task1SendMsg, 0, sizeof(TASK1_MESSAGE));
                task1SendMsg->id = DSP_TASK_1_AUDIO3A_DEINIT_DONE;

                // printc(pArg->ch, "%s>send message: msg_phyAddr 0x%x\n", __FUNCTION__, sendMsg.msg_phyAddr);
                // printc(pArg->ch, "%s>send message: msg_phyAddr 0x%x\n", __FUNCTION__, sendMsg.msg_phyAddr);
                // cache_wb(sendMsg, sendMsg, sizeof(DSP_MESSAGE));
                cache_wb(task1SendMsg, task1SendMsg, sizeof(TASK1_MESSAGE));
                SCHE_SendMessage(&sendMsg, pArg->ch);
            }
            else
            {
                printc(pArg->ch, "task1RevMsg->id: %d\n", task1RevMsg->id);
            }
        }
        else
        {
            printc(pArg->ch, "%s>unknown message 0x%x\n", __FUNCTION__, revMsg.msgId);
        }
        pArg->sem = 0;
    }    

    if(pArg->counter % 10000 == 1)
    {
        printc(pArg->ch, "%s>counter %d\n", __FUNCTION__, pArg->counter);
    }
    return SCHE_CONTINUE_RUN;  
}

int audio3a_task_deinit(void *arg)
{    
    free(arg);
    return 0;  
}

void audio3a_task_callback(void *arg)
{    
    Audio3aTaskContext *pArg = (Audio3aTaskContext*)arg;

    pArg->sem = 1;
    printc(pArg->ch, "%s>\n", __FUNCTION__);
    return 0;  
}

DSP_TASK dsp_audio3a_task = {
    .name             = "audio3a task",
    .priority         = 1,
    .init             = audio3a_task_init,
    .deinit           = audio3a_task_deinit,
    .run              = audio3a_task_run,
    .rev_callback     = audio3a_task_callback,
    .ack_callback     = NULL,    
};

