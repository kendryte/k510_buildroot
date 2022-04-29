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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <k510.h>
#include <math.h>
#include <mailbox.h>
#include "cache.h"
#include "sysctl_clk.h"
#include "interrupt.h"
#include "printc.h"
#include "scheduler.h"
#include "alltasks.c"

//from k510 dts: DSP: 128M to 136M (0x8000000, 0x87FFFFF)
//reserve 512 bytes for comunication bewteen CPU and DSP
//the following address is from k510_crb_lp3_v0_1.dts
const unsigned int DspChTxAddr[MAX_NUM_DSP_TASKS] = 
{
    0x087fff00,
    0x087fff20,
    0x087fff40,
    0x087fff60,
    0x087fff80,
    0x087fffa0,
    0x087fffc0,
    0x087fffe0
};

const unsigned int DspChRxAddr[MAX_NUM_DSP_TASKS] = 
{
    0x087ffe00,
    0x087ffe20,
    0x087ffe40,
    0x087ffe60,
    0x087ffe80,
    0x087ffea0,
    0x087ffec0,
    0x087ffee0
};

typedef struct st_TASK_BLOCK
{
    DSP_TASK       *task;
    int            id;
    void           *arg;        
    bool            isEnabled;
    bool            incomingSysCmd;
    DSP_MESSAGE     message;
    struct st_TASK_BLOCK *next;
    struct st_TASK_BLOCK *prev;
    int            numCalled;
    int            numRun;
    int            ranThisTime;
} TASK_BLOCK;

typedef struct
{
    int id;
    bool isUsed;
}SCHE_MUTEX;

typedef struct
{
    TASK_BLOCK task_block[MAX_NUM_DSP_TASKS];
    TASK_BLOCK *rootTask; //Pointer to the highest priority task.
    TASK_BLOCK *currentTask; //Current task.
}SchedulerContext;

SchedulerContext ScheCtx;


ScheStatus SCHE_SendMessage(DSP_MESSAGE *pMsg, DspTaskChannel ch)
{
    void *msg_addr;
        
    msg_addr = (void*)DspChTxAddr[ch];
    memcpy(msg_addr, pMsg, sizeof(DSP_MESSAGE));
    cache_wb(msg_addr, msg_addr, sizeof(DSP_MESSAGE));
    mailbox_dsp2cpu_send_int(ch);
}

ScheStatus SCHE_GetMessage(DSP_MESSAGE *pMsg, DspTaskChannel ch)
{   
    SchedulerContext *pCtx = &ScheCtx;
    TASK_BLOCK *task_block;
    
    task_block = &pCtx->task_block[ch];
    memcpy(pMsg, &task_block->message, sizeof(DSP_MESSAGE));
}

ScheStatus SCHE_TaskRegister(DSP_TASK *task, DspTaskChannel ch)
{
    SchedulerContext *pCtx = &ScheCtx;
    TASK_BLOCK *curTask, *prevTask, *nextTask;

    if(pCtx->task_block[ch].task)
    {
        printf("dsp schduler: register %s fail, ch %d\n", task->name, ch);
        return SCHE_ERR;
    }

    curTask = &(pCtx->task_block[ch]);
    curTask->task = task;
    curTask->id = ch;
    curTask->numCalled = 0;
    curTask->numRun = 0;
    curTask->ranThisTime = 0;
    curTask->isEnabled = false;
    curTask->incomingSysCmd = false;
    curTask->arg = NULL;
    
    // now we insert the item in the priority-sorted list
    prevTask = NULL;
    nextTask = pCtx->rootTask;
    while (nextTask != NULL && nextTask->task->priority < task->priority)
    {
        prevTask = nextTask;
        nextTask = nextTask->next;
    }
    
    // do previous link
    curTask->prev = prevTask;
    if(prevTask)
    {
        prevTask->next = curTask;
    }
    else
    {
        pCtx->rootTask = curTask;
    }
    // previous link complete, now do the next link
    curTask->next = nextTask;
    if(nextTask != NULL)
    {
        // there is another task with equal or lower priority
        nextTask->prev = curTask;
    }
    // insertion complete
    printf("dsp schduler: register %s successful, ch %d\n", task->name, ch);
    return SCHE_SUCCESS;
}

static void get_message(SchedulerContext *pCtx, DspTaskChannel ch)
{   
    void *msg_addr;
    TASK_BLOCK *task_block;
    
    task_block = &pCtx->task_block[ch];
    
    msg_addr = (void*)DspChRxAddr[ch];
    cache_inval(msg_addr, msg_addr, sizeof(DSP_MESSAGE), L1_DCACHE);
    memcpy(&task_block->message, msg_addr, sizeof(DSP_MESSAGE));
    mailbox_dsp2cpu_send_int(ch+8);   //send ACK
}


int mailbox_int_irq(void *ctx)
{
    SchedulerContext *pCtx = (SchedulerContext *)ctx;
    volatile mailbox_t* mailbox = (volatile mailbox_t *)MAILBOX_BASE_ADDR;
    int i;
    TASK_BLOCK *task_block;
    DSP_MESSAGE msg;

    //printf("dsp %s>cpu2dsp_int_status = 0x%x\n", __FUNCTION__, mailbox->cpu2dsp_int_status);
    
    for(i = 0; i < MAILBOX_INT_NUMBERMAX; i++)
    {
        if(mailbox_cpu2dsp_get_int_status(i))
        {
            mailbox_cpu2dsp_clear_int(i);

            //printf("dsp %s>mailbox ch %d\n", __FUNCTION__, i);

            if(i < MAX_NUM_DSP_TASKS)
            {
                task_block = &pCtx->task_block[i];
                if(task_block->task)
                {        
                    get_message(pCtx, i);

                    SCHE_GetMessage(&msg, i);
                    
                    if(msg.msgId == DSP_TASK_USER_MSG)
                    {
                        if(task_block->isEnabled && task_block->task->rev_callback)
                        {
                            task_block->task->rev_callback(task_block->arg);
                        }
                    }     
                    else
                    {
                        task_block->incomingSysCmd = true;
                    }
                }
            }
            else
            {
                task_block = &pCtx->task_block[i-MAX_NUM_DSP_TASKS];
                if(task_block->isEnabled && task_block->task->ack_callback)
                {
                    task_block->task->ack_callback(task_block->arg);
                }
            }
        }
    }

    return 0;
}

static void process_command(SchedulerContext *pCtx)
{
    DSP_MESSAGE msg;
    int i,j;
    TASK_BLOCK *task_block;

    for(i=0; i<MAX_NUM_DSP_TASKS; i++)
    {
        task_block = &pCtx->task_block[i];
        if(task_block->incomingSysCmd)
        {
            SCHE_GetMessage(&msg, i);
            //printf("dsp %s>task %d, msgId 0x%x, init 0x%x\n", __FUNCTION__, i, msg.msgId, task_block->task->init);
            
            task_block->incomingSysCmd = false;
            
            if(task_block->task)
            {
                switch (msg.msgId)
                {
                    case DSP_TASK_ENABLE:
                        task_block->isEnabled = true;
                        printc_init(i, msg.msg_phyAddr, msg.len);                        
                        task_block->arg = task_block->task->init();
                        printf("dsp %s>task %d: init done\n", __FUNCTION__, i);
                        SCHE_SendMessage(&msg, i);
                    break;

                    case DSP_TASK_DISABLE:
                        task_block->isEnabled = false;
                        task_block->task->deinit(task_block->arg);
                        printc_deinit(i);
                        printf("dsp %s>task %d: deinit done\n", __FUNCTION__, i);
                        SCHE_SendMessage(&msg, i);
                    break;

                    case DSP_TASK_PRINT_INFO:
                        printf("dsp total register tasks:\n");
                        for(j=0; j<MAX_NUM_DSP_TASKS; j++)
                        {
                            TASK_BLOCK *block;
                            
                            block = &pCtx->task_block[j];
                            if(block->task)
                            {
                                printf("dsp Task %d: %s, isEnabled %d\n", j, block->task->name, block->isEnabled);
                            }
                        }
                        SCHE_SendMessage(&msg, i);
                    break;

                    default:
                    break;
                } 
            }
        }
    }
}

int main(int argc, char *argv[])
{
    SchedulerContext *pCtx = &ScheCtx;
    TASK_BLOCK *prevTask, *nextTask, *insertionPoint, *nextToRun;
    int numProcessed;
    int runCount = 0, prevRunCount = 0;
    ScheStatus ret;
    int i;

    printf("dsp schduler start\n");
   
    memset(pCtx, 0, sizeof(SchedulerContext));  

    register_all_tasks();

    for(i = 0; i < MAILBOX_INT_NUMBERMAX; i++)
    {
        mailbox_cpu2dsp_clear_int(i);
    }

    cache_enable();
    plic_interrupt_enable();
    plic_set_priority(IRQN_CPU2DSP_INTERRUPT, 1);
    plic_irq_register(IRQN_CPU2DSP_INTERRUPT, mailbox_int_irq, pCtx);
    plic_irq_enable(IRQN_CPU2DSP_INTERRUPT);
    mailbox_cpu2dsp_int_enable();

    //main loop    
    while (1)
    {   
        // make current task "not available" during command processing
        pCtx->currentTask = NULL;

        // first, process all commands
        process_command(pCtx);

        // clear all run flags
        for(nextTask = pCtx->rootTask; nextTask != NULL; nextTask = nextTask->next)
        {
            nextTask->ranThisTime = 0;
        }        
        
        // start from the top, pick the highest priority task ready to run
        pCtx->currentTask = pCtx->rootTask;

        // save the current count of successful runs for later
        prevRunCount = runCount;

        while (pCtx->currentTask != NULL)
        {

            // if we already ran this task this batch, skip
            if(pCtx->currentTask->ranThisTime)
            {
                pCtx->currentTask = pCtx->currentTask->next;
                continue;
            }

            if(pCtx->currentTask->isEnabled)
            {
                numProcessed = pCtx->currentTask->task->run(pCtx->currentTask->arg);
                // update task table
                pCtx->currentTask->numCalled++;
            }
            else
            {
                numProcessed = 0;
            }
            
            if(numProcessed)
            {
                pCtx->currentTask->ranThisTime = 1;
                pCtx->currentTask->numRun++;
                runCount++;
            }

            // first, remember the next task to run
            nextTask = pCtx->currentTask->next;

            // exit this loop if we just processed the last task
            if(nextTask == NULL)
            {
                break;
            }
            if(numProcessed > 0)
            {                   /* was able to run */
                // place this task at the end of the current priority list

                insertionPoint = nextTask;

                // first, find the first task with a different priority
                while (insertionPoint->next != NULL && pCtx->currentTask->task->priority == insertionPoint->task->priority)
                {
                    insertionPoint = insertionPoint->next;
                }
                // now, insertionPoint is either the last task, or the first with a different priority

                // see if there is a priority change
                if(pCtx->currentTask->task->priority != insertionPoint->task->priority)
                {
                    // yes, so we need to move current task to be before insertionPoint
                    // which is also after insertionPoint->prev:
                    insertionPoint = insertionPoint->prev;
                    // new we need to move current to after insertionPoint
                }
                else
                {
                    // insertionPoint is the last task, and has the same priority
                    // so do nothing, we will move current task to after insertionPoint
                }

                // check to see that new and old positions are not the same
                if(pCtx->currentTask != insertionPoint)
                {
                    // link up previous and next tasks
                    prevTask = pCtx->currentTask->prev;
                    nextToRun = nextTask = pCtx->currentTask->next;

                    if(prevTask)
                    {
                        prevTask->next = nextTask;
                    }
                    else
                    {
                        pCtx->rootTask = nextTask;
                    }

                    nextTask->prev = prevTask;

                    // Now we use "prevTask" and "nextTask" for the new insertion
                    prevTask = insertionPoint;
                    nextTask = prevTask->next;

                    prevTask->next = pCtx->currentTask;
                    if(nextTask != NULL)
                    {
                        nextTask->prev = pCtx->currentTask;
                    }
                    pCtx->currentTask->prev = prevTask;
                    pCtx->currentTask->next = nextTask;

                    pCtx->currentTask = nextToRun;
                }
                else
                {
                    // this was already the last in its priority group, so go on to next one
                    pCtx->currentTask = nextTask;
                }

            }
            else
            {
                // the component was blocked, just try the next one
                pCtx->currentTask = nextTask;
            }
        }

        if(runCount == prevRunCount)
        {
            int i, j;

            for(i = 0; i < (1 << 10); i++)
            {
                j += i;
            }
            numProcessed = j;   /* so that the optimizer does not eliminate the loop */

        }
    }
    printf("dsp scheduler is end\n");
}

