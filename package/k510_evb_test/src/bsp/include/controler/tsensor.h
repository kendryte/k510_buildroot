#ifndef _TSENSOR_H
#define _TSENSOR_H
#include <stdint.h>

#define TSENSOR_PARAM       (4094.0)
#define TSENSOR_Y           (237.5)
#define TSENSOR_X           (81.1)

#define tsensor_get_data(num) (tsensor->data[num] & 0xFFFU)

typedef struct {
    volatile uint32_t config;               /* 0x0300 */
    volatile uint32_t reserve0;
    volatile uint32_t clk_ratio;            /* 0x0308 */
    volatile uint32_t wr_an;                /* 0x030C */
    volatile uint32_t status;               /* 0x0310 */
    volatile uint32_t data[5];              /* 0x0314-0x0324 */
} tsensor_t;

typedef enum {
    TSENSOR_SINGLE_MODE,
    TSENSOR_CONTINUE_MODE,
} tsensor_work_mode_t;

typedef struct {
    double temperature[5];
    uint32_t status;
} tsensor_temperature_t;

extern volatile tsensor_t* const  tsensor;

#define tsensor_poweron()   do {tsensor->config = 0;} while(0);
#define tsensor_powerdown() do {tsensor->config = 0x1F;} while(0);
#define tsensor_continue_stop() do {tsensor->wr_an |= 0x1000000U;} while(0);

int tsenor_set_ratio(uint8_t ratio);
int tsensor_set_work_mode(tsensor_work_mode_t mode);
uint8_t tsensor_get_ratio(void);
void tsensor_get_temperature(tsensor_temperature_t *temp);
#endif /* _TSENSOR_H */