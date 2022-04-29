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
