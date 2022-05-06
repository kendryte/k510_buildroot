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
#include <k510.h>
#include "hard_fft.h"
#include <math.h>
#include "cache.h"
#include "sysctl_clk.h"
#include "interrupt.h"

/*
  SW1 1/3 on 2/4/ off   cpu & dsp
./ICEman --target-cfg ax25mp_dsp.cfg -H
riscv64-elf-gdb bootrom.elf --eval-command="target remote:1111" connect to cpu
set *0x97002014=0 reset dsp
exit
/maix2_bootrom/test/asic# riscv64-elf-gdb bootrom.elf --eval-command="target remote:1112"  connect to dsp
file ../../../xxx.elf
load
c
*/

#define IRQN_FFT_INTERRUPT 95
#define PI 3.141592653589793

float i_real[512];
float i_imag[512];
float soft_real[512];
float soft_imag[512];
float hard_real[512];
float hard_imag[512];

float o_real_ifft[512];
float o_imag_ifft[512];

float fft_real_hard_soft_precision_diff_max_ratio = 0;
float fft_real_hard = 0;
float fft_real_soft = 0;
int   fft_real_index = 0;

float fft_imag_hard_soft_precision_diff_max_ratio = 0;
float fft_imag_hard = 0;
float fft_imag_soft = 0;
int   fft_imag_index = 0;

float ifft_real_hard_soft_precision_diff_max_ratio = 0;
float ifft_real_hard = 0;
float ifft_real_soft = 0;
int   ifft_real_index = 0;

float ifft_imag_hard_soft_precision_diff_max_ratio = 0;

uint64_t soft_fft_cycles;
uint64_t hard_fft_cycles;
uint64_t hard_ifft_cycles;

float power[512];

uint8_t fft_done_flag;

extern void soft_calc_fft_ri(unsigned int fft_n,float *input, float *real, float *image);

int fft_intr(void *ctx)
{
    fft_done_flag = 1;
    clear_fft_int();
    return 0;
}

#if 0
int fft_test(uint32_t fft_n)
{
    int i;
    float tempf1[5];
    uint64_t cycles;

    if((fft_n != 64) && (fft_n != 128) && (fft_n != 256) && (fft_n != 512))
    {
        // printf("fft_test fft point error,point = %d!\r\n",fft_n);
        while(1);
    }
#if 0
    for (i = 0; i < fft_n; i++) {                                       //init struct
        tempf1[0] = 10 * cosf(2 * PI * i / fft_n);
        tempf1[1] = 20 * cosf(2 * 2 * PI * i / fft_n);
        tempf1[2] = 30 * cosf(3 * 2 * PI * i / fft_n);
        tempf1[3] = 0.2 * cosf(4 * 2 * PI * i / fft_n);
        tempf1[4] = 1000 * cosf(5 * 2 * PI * i / fft_n);
        i_real[i] = tempf1[0] + tempf1[1] + tempf1[2] + tempf1[3] + tempf1[4];

        i_imag[i] = 0;                                                //imag to 0
    }
#endif

#if 0
    printf("\r\n\r\n\r\n##################################Start %d fft&ifft!##################################\r\n\r\n\r\n\r\n",fft_n);
    printf("####################################################################################\r\n\r\n\r\n\r\n");
    printf("\r\ninput real data:");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(i_real[i] >= 0)
        {
            printf("+");
            printf("%15lf ", i_real[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabsf(i_real[i]));
        }
    }
#endif

#if 0
    printf("\r\n\r\n------------------------calc software fft--------------------------------\r\n");
    cycles = read_cycle();
    soft_calc_fft_ri(fft_n,i_real,soft_real,soft_imag);
    soft_fft_cycles = read_cycle() - cycles;
#if 1
    printf("\r\nsoft fft real:\r\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(soft_real[i] >= 0)
        {
            printf("+");
            printf("%15lf ", soft_real[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabsf(soft_real[i]));
        }
    }
    printf("\r\nsoft fft image:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(soft_imag[i] >= 0)
        {
            printf("+");
            printf("%15lf ", soft_imag[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabsf(soft_imag[i]));
        }
    }
    printf("\r\n");
#endif
    printf("\r\n----------------------endsoft-----------------------------------\r\n");
#endif

    // printf("\r\n----------------------hardware----------------------------------\r\n");

    fft_done_flag = 0;
    plic_interrupt_enable();

    plic_set_priority(IRQN_FFT_INTERRUPT, 1);
    plic_irq_register(IRQN_FFT_INTERRUPT, fft_intr, NULL);
    if(plic_irq_enable(IRQN_FFT_INTERRUPT))
    {
        printf("plic enable err\r\n");
        while(1);
    }

    enable_fft_int();

    if(64 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N64, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N64, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_fft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(hard_real, hard_imag, FFT_N64, FFT_MODE);
    }
    else if(128 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N128, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N128, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_fft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(hard_real, hard_imag, FFT_N128, FFT_MODE);
    }
    else if(256 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N256, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N256, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_fft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(hard_real, hard_imag, FFT_N256, FFT_MODE);
    }
    else if(512 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N512, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N512, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_fft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(hard_real, hard_imag, FFT_N512, FFT_MODE);
    }

#if 0
    printf("\r\nhard fft real:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(hard_real[i] >= 0)
        {
            printf("+");
            printf("%15lf ", hard_real[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabs(hard_real[i]));
        }
    }
    printf("\r\nhard fft image:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(hard_imag[i] >= 0)
        {
            printf("+");
            printf("%15lf ", hard_imag[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabs(hard_imag[i]));
        }
    }
    printf("\r\n");
#endif

    // printf("\r\n--------------------------end hardware--------------------------------\r\n\r\n");

    // printf("\r\n--------------------------diff----------------------------------------\r\n\r\n");
#if 0
    printf("\r\nreal diff:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        printf("%16lf ", hard_real[i]-soft_real[i]);
    }
    printf("\r\nimage diff:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        printf("%16lf ", hard_imag[i]-soft_imag[i]);
    }
    printf("\r\n\r\n\r\n");
#endif
    float max_real = 0;
    float max_imag = 0;;
    float max_diff_real = 0;;
    float max_diff_imag = 0;;

    for(i = 0 ; i < fft_n; i++)
    {
        if(fabsf(soft_real[i]) > max_real)
            max_real = soft_real[i];
        if(fabsf(hard_real[i]) > max_real)
            max_real = hard_real[i];

        if(fabsf(soft_imag[i]) > max_imag)
            max_imag = soft_imag[i];
        if(fabsf(hard_imag[i]) > max_imag)
            max_imag = hard_imag[i];

        if(fabsf(soft_real[i]-hard_real[i]) > max_diff_real)
            max_diff_real = soft_real[i]-hard_real[i];

        if(fabsf(soft_imag[i]-hard_imag[i]) > max_diff_imag)
            max_diff_imag = soft_imag[i]-hard_imag[i];
    }
    // printf("max_real:%16lf  max_imag:%f  max_diff_real %16lf  max_diff_imag  %16lf\r\n\r\n",max_real,max_imag,max_diff_real,max_diff_imag);


    /* ifft */
    // printf("\r\n\r\n----------------------calc hard ifft---------------------------------\r\n");
    if(64 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N64, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N64, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_ifft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N64, IFFT_MODE);
    }
    else if(128 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N128, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N128, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_ifft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N128, IFFT_MODE);
    }
    else if(256 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N256, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N256, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_ifft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N256, IFFT_MODE);
    }
    else if(512 == fft_n)
    {
        cycles = read_cycle();
        fft_init(FFT_N512, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N512, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        hard_ifft_cycles = read_cycle() - cycles;
        // printf("\r\nfft get result:");
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N512, IFFT_MODE);
    }

#if 0
    printf("\r\nhard ifft real:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(o_real_ifft[i] >= 0)
        {
            printf("+");
            printf("%15lf ", o_real_ifft[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabs(o_real_ifft[i]));
        }
    }
    printf("\r\nhard ifft image:\n");
    for (i = 0; i < fft_n; i++)
    {
        if(i % 8 == 0)
        {
            printf("\r\n");
        }
        if(o_imag_ifft[i] >= 0)
        {
            printf("+");
            printf("%15lf ", o_imag_ifft[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabs(o_imag_ifft[i]));
        }
    }
    printf("\r\n");
#endif
    fft_real_hard_soft_precision_diff_max_ratio = 0;
    fft_imag_hard_soft_precision_diff_max_ratio = 0;

    ifft_real_hard_soft_precision_diff_max_ratio = 0;
    ifft_imag_hard_soft_precision_diff_max_ratio = 0;

    
    fft_real_hard = 0;
    fft_real_soft = 0;
    fft_real_index = 0;
    
    fft_imag_hard = 0;
    fft_imag_soft = 0;
    fft_imag_index = 0;
    
    ifft_real_hard = 0;
    ifft_real_soft = 0;
    ifft_real_index = 0;

    for(i = 0; i < fft_n; i++)
    {
        if(soft_real[i] != 0)
        {
            if(fabs((double)((double)soft_real[i]-(double)hard_real[i])/(double)soft_real[i]) > (double)fft_real_hard_soft_precision_diff_max_ratio)
            {
                fft_real_hard_soft_precision_diff_max_ratio = fabs((double)((double)soft_real[i]-(double)hard_real[i])/(double)soft_real[i]);
                fft_real_hard = hard_real[i];
                fft_real_soft = soft_real[i];
                fft_real_index = i;
            }
        }

        if(soft_imag[i] != 0)
        {
            if(fabs((double)((double)soft_imag[i]-(double)hard_imag[i])/(double)soft_imag[i]) > (double)fft_imag_hard_soft_precision_diff_max_ratio)
            {
                fft_imag_hard_soft_precision_diff_max_ratio = fabs((double)((double)soft_imag[i]-(double)hard_imag[i])/(double)soft_imag[i]);
                fft_imag_hard = hard_imag[i];
                fft_imag_soft = soft_imag[i];
                fft_imag_index = i;
            }
        }

        if(i_real[i] != 0)
        {
            if(fabs((double)((double)i_real[i]-(double)o_real_ifft[i])/(double)i_real[i]) > (double)ifft_real_hard_soft_precision_diff_max_ratio)
            {
                ifft_real_hard_soft_precision_diff_max_ratio = fabs((double)((double)i_real[i]-(double)o_real_ifft[i])/(double)i_real[i]);
                ifft_real_hard = o_real_ifft[i];
                ifft_real_soft = i_real[i];
                ifft_real_index = i;
            }
        }

        if(o_imag_ifft[i] != 0)
        {
            /*find max image*/
            if(fabs((double)o_imag_ifft[i]) > (double)ifft_imag_hard_soft_precision_diff_max_ratio)
            {
                ifft_imag_hard_soft_precision_diff_max_ratio = o_imag_ifft[i];
            }

        }
    }

    // printf("\r\n\r\n==================%d point precision result================\r\n",fft_n);
    // printf("cpu freq:%d\r\n",sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25M_CORE_0));
    // printf("soft fft cycles %ld, hard fft cycles %ld, hard iff cycles %ld\r\n",soft_fft_cycles,hard_fft_cycles,hard_ifft_cycles);

    // printf("fft index %d real soft %15lf hard %15lf pecision max %15lf\r\n",fft_real_index,(double)fft_real_soft,(double)fft_real_hard,(double)fft_real_hard_soft_precision_diff_max_ratio);
    // printf("fft index %d imag soft %15lf hard %15lf pecision max %15lf\r\n",fft_imag_index,(double)fft_imag_soft,(double)fft_imag_hard,(double)fft_imag_hard_soft_precision_diff_max_ratio);
    // printf("calc %15lf-%15lf=%15f pecision %15lf abs %15lf\r\n",(double)fft_imag_soft,(double)fft_imag_hard,(double)((double)fft_imag_soft-(double)fft_imag_hard),
    //                                                             (double)((double)fft_imag_soft-(double)fft_imag_hard)/(double)fft_imag_soft,
    //                                                             fabs((double)((double)fft_imag_soft-(double)fft_imag_hard)/(double)fft_imag_soft));
    // printf("ifft index %d real soft %15lf hard %15lf pecision max %15lf\r\n",ifft_real_index,(double)ifft_real_soft,(double)ifft_real_hard,(double)ifft_real_hard_soft_precision_diff_max_ratio);
    // printf("ifft imag max %15lf\r\n",(double)ifft_imag_hard_soft_precision_diff_max_ratio);

    return 0;
}
#endif

#define SHARE_MEMORY_ADDR           0x80000000U   //SRAM
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
    //uint8_t *share_memory_addr;
    volatile struct share_memory *fft_share_memory; 
    //share_memory_addr = (uint8_t *)SHARE_MEMORY_ADDR;
    fft_share_memory = (struct share_memory *)SHARE_MEMORY_ADDR;

    uint64_t v_hartid;
    int i;
    int fft_n = 64;
    float tempf1[5];
    for (i = 0; i < fft_n; i++) {                                       //init struct
        tempf1[0] = 10 * cosf(2 * PI * i / fft_n);
        tempf1[1] = 20 * cosf(2 * 2 * PI * i / fft_n);
        tempf1[2] = 30 * cosf(3 * 2 * PI * i / fft_n);
        tempf1[3] = 0.2 * cosf(4 * 2 * PI * i / fft_n);
        tempf1[4] = 1000 * cosf(5 * 2 * PI * i / fft_n);
        i_real[i] = tempf1[0] + tempf1[1] + tempf1[2] + tempf1[3] + tempf1[4];

        i_imag[i] = 0;                                                //imag to 0
    }
    

    //cache_disable();

    v_hartid = read_csr(NDS_MHARTID);

    //printf("Core %ld Hello world, fft calculate\n", v_hartid);
    //share_memory_addr[0] = 0xff;
    //printf("begin calculate\r\n");
    fft_share_memory->dsp_input_begin = 0xff;
    fft_share_memory->dsp_input_length = 128;

    fft_test(64, i_real, i_imag);
    //memcpy(share_memory_addr + 8, i_real, 64*4);
    memcpy(fft_share_memory->dsp_input_data, i_real, 64*4);
    ifft_test(64, i_real, i_imag);
    //memcpy(share_memory_addr + 8 + 64*4, i_real, 64*4);
    memcpy(fft_share_memory->dsp_input_data + 64*4, i_real, 64*4);

    //printf("end calculate\r\n");
    //share_memory_addr[1] = 0xff;
    fft_share_memory->dsp_input_end = 0xff;

    //fft_test(128);
    //fft_test(256);
    //fft_test(512);
    // while(1);
    return 0;
}
