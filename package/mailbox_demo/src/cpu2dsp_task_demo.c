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
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include "dsp_tasks.h"

//Mailbox channel is used to communicate with corresponding DSP task
//mailbox channel number is decided by CPU and DSP software

#define MBOX_CHAN_0_TX          _IOW('x', 0, unsigned long)
#define MBOX_CHAN_1_TX          _IOW('x', 1, unsigned long)
#define MBOX_CHAN_2_TX          _IOW('x', 2, unsigned long)
#define MBOX_CHAN_3_TX          _IOW('x', 3, unsigned long)
#define MBOX_CHAN_4_TX          _IOW('x', 4, unsigned long)
#define MBOX_CHAN_5_TX          _IOW('x', 5, unsigned long)
#define MBOX_CHAN_6_TX          _IOW('x', 6, unsigned long)
#define MBOX_CHAN_7_TX          _IOW('x', 7, unsigned long)
#define MBOX_CHAN_0_RX          _IOR('x', 0, unsigned long)
#define MBOX_CHAN_1_RX          _IOR('x', 1, unsigned long)
#define MBOX_CHAN_2_RX          _IOR('x', 2, unsigned long)
#define MBOX_CHAN_3_RX          _IOR('x', 3, unsigned long)
#define MBOX_CHAN_4_RX          _IOR('x', 4, unsigned long)
#define MBOX_CHAN_5_RX          _IOR('x', 5, unsigned long)
#define MBOX_CHAN_6_RX          _IOR('x', 6, unsigned long)
#define MBOX_CHAN_7_RX          _IOR('x', 7, unsigned long)

#define MBOX_DEV                "/dev/mailbox-client"
#define SHARE_MEMORY_DEV "/dev/k510-share-memory"
#define DEV_NAME_DDR "/dev/mem"
#define MEMORY_TEST_BLOCK_ALIGN 4096        /* align 4k for mmap */
#define SHARE_MEMORY_ALLOC          _IOWR('m', 1, unsigned long)
#define SHARE_MEMORY_ALIGN_ALLOC    _IOWR('m', 2, unsigned long)
#define SHARE_MEMORY_FREE           _IOWR('m', 3, unsigned long)
#define SHARE_MEMORY_SHOW           _IOWR('m', 4, unsigned long)
#define SHARE_MEMORY_INVAL_RANGE    _IOWR('m', 5, unsigned long)
#define SHARE_MEMORY_WB_RANGE       _IOWR('m', 6, unsigned long)

struct share_memory_alloc_align_args {
    unsigned int size;
    unsigned int alignment;
    unsigned int phyAddr;
};

struct memory_cache_sync_request {
    unsigned long size;
    unsigned long vaddr;
    unsigned long paddr;
};

typedef struct
{
    int fd_ddr;
    int fd_share_memory;
    int fd_mailbox;
    pthread_t thread_0;
    unsigned int task0msg_phyAddr;
    void *task0msg_vAddr;
    unsigned int task0msg_size;
    void *task0print_vAddr;
    unsigned int task0print_size;
    unsigned int task0print_phyAddr;
    unsigned int task0src_phyAddr;
    void *task0src_vAddr;
    unsigned int task0src_size;
    unsigned int task0dst_phyAddr;
    void *task0dst_vAddr;
    unsigned int task0user_msg_phyAddr;
    void *task0user_msg_vAddr;
    unsigned int task0user_msg_size;
    unsigned int task0dst_size;
    int task0_start_send_msg;
    int is_task0_enabled;
    int is_print_finished;
    int exit_waiting_cnt;
}Cpu2DspTaskContext;

Cpu2DspTaskContext Ctx;
static int received_sigterm = 0;

typedef enum
{
    DSP_TASK_0_PROCESS_START,
    DSP_TASK_0_PROCESS_END,
    MAX_NUM_DSP_TASK_0_MSG
} Task0MsgID;

typedef struct tTASK0_MSG
{
    Task0MsgID  id;
    unsigned int src_phyAddr;
    unsigned int dst_phyAddr;
    unsigned int data_size;
}TASK0_MESSAGE;

static unsigned int alloc_memory(int fd_share_memory, unsigned int size)
{
    struct share_memory_alloc_align_args  allocAlignMem;
      
    allocAlignMem.size = (size + 0xfff) & (~0xfff);
    allocAlignMem.alignment = MEMORY_TEST_BLOCK_ALIGN;
    allocAlignMem.phyAddr = 0;

    if(ioctl(fd_share_memory, SHARE_MEMORY_ALIGN_ALLOC, &allocAlignMem) < 0)
    {
          printf("cpu alloc_memory Error!\n");
          return -1;
    }
    //printf("%s>phy_addr 0x%x, size %d\n", __FUNCTION__, allocAlignMem.phyAddr, allocAlignMem.size);
    
    return allocAlignMem.phyAddr;
}

static int InvalidateCache(unsigned int phyAddr, void* vAddr, unsigned int size)
{
  Cpu2DspTaskContext *pCtx = &Ctx;
  struct memory_cache_sync_request request;
 
  //printf("%s>phyAddr 0x%x, vaddr %p, size %d\n", __FUNCTION__, phyAddr, vAddr, size);

  request.paddr = phyAddr;
  request.vaddr = vAddr;
  request.size  = size;

  if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_INVAL_RANGE, &request) < 0)
  {
    printf("fd invalidate range op failure!\r\n");
    return -1;
  }

  return 0;
}

static int FlushCache(unsigned int phyAddr, void* vAddr, unsigned int size)
{
    Cpu2DspTaskContext *pCtx = &Ctx;
    struct memory_cache_sync_request request;
    
    //printf("%s>phyAddr 0x%x, vaddr %p, size %d\n", __FUNCTION__, phyAddr, vAddr, size);

    request.paddr = phyAddr;
    request.vaddr = vAddr;
    request.size  = size;

    if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_WB_RANGE, &request) < 0)
    {
      printf("fd wb range op failure!\r\n");
      return -1;
    }

    return 0;
}


static void *cpu2dsp_task0(void *arg)
{
    Cpu2DspTaskContext *pCtx= (Cpu2DspTaskContext *)arg;
    int ret = 0;
    struct pollfd fds;
    DSP_MESSAGE msg;

    while(1)
    {
        fds.fd = pCtx->fd_mailbox;
        fds.events = POLLIN;
        ret = poll(&fds, 1, -1);
        if (ret)
        {
            if (ioctl(pCtx->fd_mailbox, MBOX_CHAN_0_RX, &msg) < 0)
                printf("rx 0 error\n");
                
            if(msg.msgId == DSP_TASK_ENABLE)
            {
                printf("task 0 is enabled\n", msg.msgId);
                pCtx->is_task0_enabled = 1;
            }
            else if(msg.msgId == DSP_TASK_DISABLE)
            {
                printf("task 0 is disabled\n", msg.msgId);
                pCtx->is_task0_enabled = 0;
            }
            else if(msg.msgId == DSP_TASK_PRINT_INFO)
            {
                printf("print tasks info finished\n", msg.msgId);
                pCtx->is_print_finished = 1;
            }
            else if(msg.msgId == DSP_TASK_USER_MSG)
            {
                TASK0_MESSAGE *task0_msg;
                unsigned int offset;

                InvalidateCache(pCtx->task0msg_phyAddr, pCtx->task0msg_vAddr, pCtx->task0msg_size);
                offset = msg.msg_phyAddr - pCtx->task0msg_phyAddr;
                task0_msg = (TASK0_MESSAGE*)(pCtx->task0msg_vAddr + offset);
                
                if(task0_msg->id == DSP_TASK_0_PROCESS_END)
                {
                    int i;
                    unsigned char *pSrc, *pDst;

                    pSrc = pCtx->task0src_vAddr;
                    pDst = pCtx->task0dst_vAddr;
                    InvalidateCache(pCtx->task0dst_phyAddr, pCtx->task0dst_vAddr, pCtx->task0dst_size);
                    for(i=0; i<pCtx->task0dst_size; i++)
                    {
                        if(pSrc[i]*2 != pDst[i])
                        {
                            printf("ERROR: task 0 process data error, data = 0x%x\n", pDst[i]);
                            break;
                        }
                    }

                    printf("cpu receive PROCESS_END\n");

                    pCtx->task0_start_send_msg = 0;
                }
            }
            else
            {
                printf("unknown dsp message 0x%x\n", msg.msgId);
            }
        }
        else
        {
            printf("read error\n");
        }
    }
}

static void exit_handler(int sig)
{
  if(SIGINT == sig)
  {
    received_sigterm = 1;
  }
  return;
}

int main(int argc, char *argv[])
{      
    Cpu2DspTaskContext *pCtx = &Ctx;
    DSP_MESSAGE msg;
    FILE *log_file;
    char name[20];

    memset(pCtx, 0, sizeof(Cpu2DspTaskContext));

    pCtx->fd_mailbox = open(MBOX_DEV, O_RDWR | O_NONBLOCK);
    if (pCtx->fd_mailbox < 0)
    {
        printf("Can't open file %s\r\n", MBOX_DEV);
        return -1;
    }

    pCtx->fd_share_memory = open(SHARE_MEMORY_DEV,O_RDWR | O_SYNC);
    if(pCtx->fd_share_memory < 0)
    {
       printf("Open %s Error!\n", SHARE_MEMORY_DEV);
    }

    pCtx->fd_ddr = open(DEV_NAME_DDR,O_RDWR|O_SYNC); 
    if(pCtx->fd_ddr < 0)
    {
      printf("Open %s Error!\n", DEV_NAME_DDR);
    }

    pCtx->task0msg_size = MEMORY_TEST_BLOCK_ALIGN;
    pCtx->task0msg_phyAddr = alloc_memory(pCtx->fd_share_memory, pCtx->task0msg_size);  
    pCtx->task0msg_vAddr = mmap(NULL, pCtx->task0msg_size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->task0msg_phyAddr); 
    printf("task 0 message buffer: vaddr 0x%x, phyAddr 0x%x, size %d\n", pCtx->task0msg_vAddr, pCtx->task0msg_phyAddr, pCtx->task0msg_size);

    pCtx->task0print_size = MEMORY_TEST_BLOCK_ALIGN;
    pCtx->task0print_phyAddr = alloc_memory(pCtx->fd_share_memory, pCtx->task0print_size);  
    pCtx->task0print_vAddr = mmap(NULL, pCtx->task0print_size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->task0print_phyAddr); 
    printf("task 0 print buffer: vaddr 0x%x, phyAddr 0x%x, size %d\n", pCtx->task0msg_vAddr, pCtx->task0print_phyAddr, pCtx->task0print_size);

    pCtx->task0src_size = MEMORY_TEST_BLOCK_ALIGN;
    pCtx->task0src_phyAddr = alloc_memory(pCtx->fd_share_memory, pCtx->task0src_size);  
    pCtx->task0src_vAddr = mmap(NULL, pCtx->task0src_size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->task0src_phyAddr); 
    printf("task 0 src buffer: vaddr 0x%x, phyAddr 0x%x, size %d\n", pCtx->task0src_vAddr, pCtx->task0src_phyAddr, pCtx->task0src_size);

    pCtx->task0dst_size = MEMORY_TEST_BLOCK_ALIGN;
    pCtx->task0dst_phyAddr = alloc_memory(pCtx->fd_share_memory, pCtx->task0dst_size);  
    pCtx->task0dst_vAddr = mmap(NULL, pCtx->task0dst_size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->task0dst_phyAddr); 
    printf("task 0 dst buffer: vaddr 0x%x, phyAddr 0x%x, size %d\n", pCtx->task0dst_vAddr, pCtx->task0dst_phyAddr, pCtx->task0dst_size);

    pCtx->task0user_msg_size = MEMORY_TEST_BLOCK_ALIGN;
    pCtx->task0user_msg_phyAddr = alloc_memory(pCtx->fd_share_memory, pCtx->task0user_msg_size);  
    pCtx->task0user_msg_vAddr = mmap(NULL, pCtx->task0user_msg_size, PROT_READ|PROT_WRITE, MAP_SHARED, pCtx->fd_ddr, pCtx->task0user_msg_phyAddr); 
    printf("task 10user_msg buffer: vaddr 0x%x, phyAddr 0x%x, size %d\n", pCtx->task0user_msg_vAddr, pCtx->task0user_msg_phyAddr, pCtx->task0user_msg_size);

    pthread_create(&pCtx->thread_0, NULL, cpu2dsp_task0, pCtx);

    msg.msgId = DSP_TASK_ENABLE;
    msg.msg_phyAddr = pCtx->task0print_phyAddr;
    msg.len = pCtx->task0print_size;
    if (ioctl(pCtx->fd_mailbox, MBOX_CHAN_0_TX, &msg) < 0)
        printf("enable task 0: tx 0 error\n");
       
    signal(SIGINT, exit_handler);
    
    while (1)
    {
        if(received_sigterm == 0)
        {
            TASK0_MESSAGE *task0_msg;

            if(pCtx->is_task0_enabled)
            {
                if(pCtx->task0_start_send_msg == 0)
                {
                    memset(pCtx->task0src_vAddr, 0x12, pCtx->task0src_size);
                    //TODO:
                    msg.msgId = DSP_TASK_USER_MSG;
                    msg.msg_phyAddr = pCtx->task0msg_phyAddr;
                    msg.len = sizeof(TASK0_MESSAGE);

                    task0_msg = (TASK0_MESSAGE*)pCtx->task0msg_vAddr;
                    task0_msg->id = DSP_TASK_0_PROCESS_START;
                    task0_msg->src_phyAddr = pCtx->task0src_phyAddr;
                    task0_msg->dst_phyAddr = pCtx->task0dst_phyAddr;
                    task0_msg->data_size = pCtx->task0src_size;
                    FlushCache(pCtx->task0src_phyAddr, pCtx->task0src_vAddr, pCtx->task0src_size);
                    FlushCache(pCtx->task0user_msg_phyAddr, pCtx->task0user_msg_vAddr, pCtx->task0user_msg_size);
                    FlushCache(pCtx->task0msg_phyAddr, pCtx->task0msg_vAddr, pCtx->task0msg_size);
                    printf("cpu send PROCESS_START\n");
                    if (ioctl(pCtx->fd_mailbox, MBOX_CHAN_0_TX, &msg) < 0)
                        printf("task 0 message: tx 0 error\n");
                        
                    pCtx->task0_start_send_msg = 1;
                }
            }
            sleep(1);
        }
        else
        {
            if(pCtx->is_print_finished == 0)
            {
                msg.msgId = DSP_TASK_PRINT_INFO;
                if (ioctl(pCtx->fd_mailbox, MBOX_CHAN_0_TX, &msg) < 0)
                    printf("enable task 0: tx 0 error\n");
            }
            else
            {
                break;
            }
            usleep(10*1000);
        }        
    }   

    //disable task
    while(1)
    {
        if(pCtx->is_task0_enabled && pCtx->exit_waiting_cnt == 0)
        {
            msg.msgId = DSP_TASK_DISABLE;
            if (ioctl(pCtx->fd_mailbox, MBOX_CHAN_0_TX, &msg) < 0)
                printf("disable task 0: tx 0 error\n");
        }
        
        pCtx->exit_waiting_cnt++;

        if(pCtx->is_task0_enabled == 0)
        {
            printf("exit: task0 is disabled\n");
            break;
        }

        if(pCtx->exit_waiting_cnt >= 5)
        {
            printf("exit: task0 is not disabled\n");
            break;
        }
        usleep(10*1000);
    }

    sprintf(name, "task%d.log", 0);
    if((log_file=fopen(name,"w+b")) == NULL )
    {
      printf("%s>Cannot open output file!\n", __FUNCTION__);
    }
    InvalidateCache(pCtx->task0print_phyAddr, pCtx->task0print_vAddr, pCtx->task0print_size);
    fwrite((void*)pCtx->task0print_vAddr, 1, pCtx->task0print_size, log_file);
    fclose(log_file);

    if(pCtx->task0msg_phyAddr != 0)
    {
        munmap((void*)pCtx->task0msg_vAddr, pCtx->task0msg_size);
        if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->task0msg_phyAddr) < 0)
        {
          printf("%s>Error!\n", __FUNCTION__);
        }
    }

    if(pCtx->task0print_phyAddr != 0)
    {
        munmap((void*)pCtx->task0print_vAddr, pCtx->task0print_size);
        if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->task0print_phyAddr) < 0)
        {
          printf("%s>Error!\n", __FUNCTION__);
        }
    }

    if(pCtx->task0src_phyAddr != 0)
    {
        munmap((void*)pCtx->task0src_vAddr, pCtx->task0src_size);
        if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->task0src_phyAddr) < 0)
        {
          printf("%s>Error!\n", __FUNCTION__);
        }
    } 

    if(pCtx->task0dst_phyAddr != 0)
    {
        munmap((void*)pCtx->task0dst_vAddr, pCtx->task0dst_size);
        if(ioctl(pCtx->fd_share_memory, SHARE_MEMORY_FREE, &pCtx->task0dst_phyAddr) < 0)
        {
          printf("%s>Error!\n", __FUNCTION__);
        }
    }  

    close(pCtx->fd_mailbox);
    close(pCtx->fd_share_memory);
    close(pCtx->fd_ddr);
    printf("cpu2dsp_task_demo: exit successful\n");
    return 0;
}
