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
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <k510.h>
#include <math.h>
#include "cache.h"
#include "sysctl_clk.h"
#include "interrupt.h"
#include "hard_fft.h"
#include "platform.h"
#include "interrupt.h"

//#define FFT_PRINT

volatile uint64_t *fft_result = (volatile uint64_t *)(DSP_FFT_BASE_ADDR + 0x80000);
volatile struct fft_t *const fft = (volatile struct fft_t *)DSP_FFT_BASE_ADDR;

uint8_t fft_done_flag;
extern void soft_calc_fft_ri(unsigned int fft_n,float *input, float *real, float *image);
static int fft_intr(void *ctx)
{
    fft_done_flag = 1;
    clear_fft_int();
    return 0;
}

int fft_init(uint8_t point, uint8_t mode, uint16_t shift, uint8_t is_dma, fft_input_mode_e input_mode, fft_data_mode_e data_mode)
{
    struct fft_fft_ctrl_t temp;

    temp = fft->fft_ctrl;

    temp.fft_point = point;  //0:512, 1:256, 2:128, 3:64
    temp.fft_mode = mode;  //1: fft, 0: ifft
    temp.fft_shift = shift;
    temp.dma_send = is_dma;
    //fft->intr_mask.fft_done_mask = 1; 
    temp.fft_input_mode = input_mode;
    temp.fft_data_mode = data_mode;
    temp.fft_enable = 1;

    fft->fft_ctrl = temp;

    return 0;
}

void reset_fft(void)
{
    fft->fifo_ctrl.resp_fifo_flush_n = 0;
    fft->fifo_ctrl.cmd_fifo_flush_n = 0;
    fft->fifo_ctrl.gs_fifo_flush_n = 0;
}

void enable_fft_int(void)
{
    fft->intr_mask.fft_done_mask = 1;
}

void clear_fft_int(void)
{
    fft->intr_clear.fft_done_clear = 1;
}


void fft_input_data(float *x, float *y, uint8_t point, fft_input_mode_e input_mode, fft_data_mode_e data_mode)
{
    uint16_t point_num = 0;
    uint16_t i;
    fft_data32 input_data;

    if (point == 0)
        point_num = 512;
    else if (point == 1)
        point_num = 256;
    else if (point == 2)
        point_num = 128;
    else if (point == 3)
        point_num = 64;

    if(INPUT_64BIT == data_mode)
    {
        if(RIRI == input_mode)
        {
            for (i = 0; i < point_num; i++) {
                input_data.R1 = x[i];
                input_data.I1 = y[i];
                fft->fft_input_fifo.fft_input_fifo = *(uint64_t *)&input_data;
            }
        }
        else if(RRRR == input_mode)
        {
            for (i = 0; i < point_num / 2; i++) {
                input_data.R1 = x[2*i];
                input_data.I1 = x[2*i + 1];
                fft->fft_input_fifo.fft_input_fifo = *(uint64_t *)&input_data;
            }
        }
        else if(RR_II == input_mode)
        {
            for (i = 0; i < point_num / 2; i++) {
                input_data.R1 = x[2*i];
                input_data.I1 = x[2*i + 1];
                fft->fft_input_fifo.fft_input_fifo = *(uint64_t *)&input_data;
            }
            for (i = 0; i < point_num / 2; i++) {
            input_data.R1 = y[2*i];
            input_data.I1 = y[2*i + 1];
            fft->fft_input_fifo.fft_input_fifo = *(uint64_t *)&input_data;
            }
        }
    }
    else if(INPUT_32BIT == data_mode)
    {
        if(RIRI == input_mode)
        {
            for (i = 0; i < point_num; i++) {
                fft->fft_input_fifo.fft_input_fifo = (uint32_t)x[i];
                fft->fft_input_fifo.fft_input_fifo = (uint32_t)y[i];
            }
        }
        else if(RRRR == input_mode)
        {
            for (i = 0; i < point_num; i++) {
                fft->fft_input_fifo.fft_input_fifo = (uint32_t)x[i];
            }
        }
        else if(RR_II == input_mode)
        {
            for (i = 0; i < point_num; i++) {
                fft->fft_input_fifo.fft_input_fifo = (uint32_t)x[i];
            }
            for (i = 0; i < point_num; i++) {
                fft->fft_input_fifo.fft_input_fifo = (uint32_t)y[i];
            }
        }
    }
}

void fft_input_intdata(float *data, uint8_t point)
{
    uint16_t point_num = 0;
    uint16_t i;
    fft_data32 input_data;

    if (point == 0)
        point_num = 512;
    else if (point == 1)
        point_num = 256;
    else if (point == 2)
        point_num = 128;
    else if (point == 3)
        point_num = 64;

    for (i = 0; i < point_num; i++) {
        input_data.R1 = data[i];
        input_data.I1 = 0;
        fft->fft_input_fifo.fft_input_fifo = *(uint64_t *)&input_data;
    }
}

uint8_t fft_get_finish_flag(void)
{
    return (uint8_t)fft->fft_status.fft_done_status & 0x01;
}

void FixToDou(float *fData, uint32_t u32Data)
{
    if (u32Data & 0x8000)
        *fData = -((float)(u32Data & 0x7fff)) / 32;
    else
        *fData = ((float)u32Data) / 32;
}

void fft_get_result(float *x, float *y, uint8_t point, uint8_t mode)
{
    uint64_t u64Data;
    uint16_t point_num = 0;
    uint16_t i;
    fft_data32 output_data;

    if (point == 0)
        point_num = 512;
    else if (point == 1)
        point_num = 256;
    else if (point == 2)
        point_num = 128;
    else if (point == 3)
        point_num = 64;
    else
    {
        printf("fft_get_result point %d error!\r\n",point);
        while(1);
    }

    if((point == 0) || (point == 2))
        fft_result = (volatile uint64_t *)(DSP_FFT_BASE_ADDR + 0x81000);
    else
        fft_result = (volatile uint64_t *)(DSP_FFT_BASE_ADDR + 0x80000);

    for (i = 0; i < point_num; i++) {
        u64Data = fft_result[i];

        output_data = *(fft_data32 *)&u64Data;
        if(IFFT_MODE == mode)
        {
            x[i] = (float)output_data.R1 / point_num;
            y[i] = (float)output_data.I1 / point_num;
        }
        else
        {
            x[i] = (float)output_data.R1;
            y[i] = (float)output_data.I1;
        }
    }
}

int fft_test(uint32_t fft_n, float *input_real, float *input_image)
{
    int i;

    float i_real[512];
    float i_imag[512];
    float hard_real[512];
    float hard_imag[512];

    if((fft_n != 64) && (fft_n != 128) && (fft_n != 256) && (fft_n != 512))
    {
        // printf("fft_test fft point error,point = %d!\r\n",fft_n);
        while(1);
    }

    memcpy(i_real, input_real, fft_n*4);
    memcpy(i_imag, input_image, fft_n*4);

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
        fft_init(FFT_N64, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N64, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(hard_real, hard_imag, FFT_N64, FFT_MODE);
    }
    else if(128 == fft_n)
    {
        fft_init(FFT_N128, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N128, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(hard_real, hard_imag, FFT_N128, FFT_MODE);
    }
    else if(256 == fft_n)
    {
        fft_init(FFT_N256, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N256, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(hard_real, hard_imag, FFT_N256, FFT_MODE);
    }
    else if(512 == fft_n)
    {
        fft_init(FFT_N512, FFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(i_real, i_imag, FFT_N512, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(hard_real, hard_imag, FFT_N512, FFT_MODE);
    }

    memcpy(input_real, hard_real, fft_n*4);
    memcpy(input_image, hard_imag, fft_n*4);

#ifdef FFT_PRINT
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
            printf("%15lf ", input_real[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabs(input_real[i]));
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
            printf("%15lf ", input_image[i]);
        }
        else
        {
            printf("-");
            printf("%15lf ", fabs(input_image[i]));
        }
    }
    printf("\r\n");
#endif

    return 0;
}

int ifft_test(uint32_t fft_n, float *input_real, float *input_image)
{
    int i;
    uint64_t cycles;

    float hard_real[512];
    float hard_imag[512];

    float o_real_ifft[512];
    float o_imag_ifft[512];

    uint64_t hard_ifft_cycles;

    if((fft_n != 64) && (fft_n != 128) && (fft_n != 256) && (fft_n != 512))
    {
        // printf("fft_test fft point error,point = %d!\r\n",fft_n);
        while(1);
    }

    memcpy(hard_real, input_real, fft_n*4);
    memcpy(hard_imag, input_image, fft_n*4);

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

    /* ifft */
    // printf("\r\n\r\n----------------------calc hard ifft---------------------------------\r\n");
    if(64 == fft_n)
    {
        fft_init(FFT_N64, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N64, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N64, IFFT_MODE);
    }
    else if(128 == fft_n)
    {
        fft_init(FFT_N128, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N128, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N128, IFFT_MODE);
    }
    else if(256 == fft_n)
    {
        fft_init(FFT_N256, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N256, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N256, IFFT_MODE);
    }
    else if(512 == fft_n)
    {
        fft_init(FFT_N512, IFFT_MODE, 0x1ff, 0, RIRI, INPUT_64BIT);
        fft_input_data(hard_real, hard_imag, FFT_N512, RIRI, INPUT_64BIT);
        while (!fft_done_flag);
        fft_get_result(o_real_ifft, o_imag_ifft, FFT_N512, IFFT_MODE);
    }

    memcpy(input_real, o_real_ifft, fft_n*4);
    memcpy(input_image, o_imag_ifft, fft_n*4);

    return 0;
}
