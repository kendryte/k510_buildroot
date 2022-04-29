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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>     //exit
#include <stdint.h>     //uint32_t
#include <stdbool.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>
#define MMAP_SIZE           0x4000

#define IOMUX_BASE_ADDR     0x80000000U   //SRAM
#define SHARE_MEMORY_LENGTH         (0x2000 - 0x8)
struct share_memory {
    uint8_t dsp_input_begin;
    uint8_t dsp_input_end;
    uint8_t reserved1[2];
    uint32_t dsp_input_length;
    uint8_t dsp_input_data[SHARE_MEMORY_LENGTH];
    uint8_t cpu_input_begin;
    uint8_t cpu_input_end;
    uint8_t reserved2[2];
    uint32_t cpu_input_length;
    uint8_t cpu_input_data[SHARE_MEMORY_LENGTH];
};

int main(void)
{
    int fd;
    volatile uint8_t *mmap_addr = NULL;
    volatile struct share_memory *fft_share_memory;
    float *result_addr;
    int i = 0;

    fd = open("/dev/mem", O_RDWR | O_NDELAY);
    if(fd < 0)
    {
        printf("open /dev/mem error\r\n");
        return -1;
    }

#if 0
    mmap_addr = (uint8_t*)mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IOMUX_BASE_ADDR);
    //result_addr = (float *)(mmap_addr + 0x1000);
    if(mmap_addr == NULL)
    {
        printf("mmap_addr error\r\n");
        return -1;
    }

    while(*mmap_addr != 0xff)
    {
        sleep(1);
        printf("begin\r\n");
        i++;
        if(i > 20)
            break;
    }
    printf("begin calculate\r\n");
    i = 0;
    while(*(mmap_addr+1) != 0xff)
    {
        sleep(1);
        printf("begin\r\n");
        i++;
        if(i > 20)
            break;
    }
    printf("end calculate\r\n");
    printf("data length:%u\r\n", *(uint32_t*)(mmap_addr + 4));

    for(i = 0; i < 128; i++)
    {
        if(i%8 == 0)
            printf("\r\n");
        //printf("data[%2d]:%14.8f  ", i, result_addr[i]);
        printf("data[%3d]:%14.8f  ", i, *(float*)(mmap_addr + 8 + i*4));
    }

    memset(mmap_addr, 0, 0x4000);

    munmap(mmap_addr, MMAP_SIZE);
#endif

#if 1
    fft_share_memory = (struct share_memory*)mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IOMUX_BASE_ADDR);
    //result_addr = (float *)(mmap_addr + 0x1000);
    if(fft_share_memory == NULL)
    {
        printf("fft_share_memory error\r\n");
        return -1;
    }

    while(1)
    {
        while(fft_share_memory->dsp_input_begin != 0xff)
        {
            sleep(1);
            // printf("begin\r\n");
            // i++;
            // if(i > 20)
            //     break;
        }
        printf("begin calculate\r\n");
        i = 0;
        while(fft_share_memory->dsp_input_end != 0xff)
        {
            sleep(1);
            // printf("end\r\n");
            // i++;
            // if(i > 20)
            //     break;
        }
        printf("end calculate\r\n");
        printf("data length:%u\r\n", fft_share_memory->dsp_input_length);

        for(i = 0; i < 128; i++)
        {
            if(i%8 == 0)
                printf("\r\n");
            //printf("data[%2d]:%14.8f  ", i, result_addr[i]);
            printf("data[%3d]:%14.8f  ", i, *(float *)(fft_share_memory->dsp_input_data + i*4));
        }

        memset(fft_share_memory, 0, 0x4000);
    }

    munmap(mmap_addr, MMAP_SIZE);
#endif

    return 0;
}
