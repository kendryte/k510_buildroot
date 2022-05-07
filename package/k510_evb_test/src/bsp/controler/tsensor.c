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
#include <k510.h>
#include <tsensor.h>

volatile tsensor_t* const  tsensor = (volatile tsensor_t* const)(0x970E0300UL);

int tsenor_set_ratio(uint8_t ratio)
{
    if (ratio > 99)
    {
        k510_loge("Tsensor ratio large than 99\n");
        return -1;
    }
    tsensor->clk_ratio = ratio;
    return 0;
}

uint8_t tsensor_get_ratio(void)
{
    return tsensor->clk_ratio & 0xFF;
}

int tsensor_set_work_mode(tsensor_work_mode_t mode)
{
    if (mode == TSENSOR_SINGLE_MODE)
    {
        tsensor->wr_an = 0x80800000;
    }
    else if (mode == TSENSOR_CONTINUE_MODE)
    {
        tsensor->wr_an = 0x80000000;
    }
    else
    {
        return -1;
    }

    return 0;
}

void tsensor_get_temperature(tsensor_temperature_t *temp)
{
    temp->status = tsensor->status;
    for (uint32_t i = 0; i < 5; i++)
    {
        temp->temperature[i] = ((double)tsensor_get_data(i) / TSENSOR_PARAM) * TSENSOR_Y - TSENSOR_X;
    }
}
