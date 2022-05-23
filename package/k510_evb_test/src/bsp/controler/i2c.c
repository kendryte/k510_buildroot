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
#include "i2c.h"
#include "platform.h"
#include "stdlib.h"
#include "string.h"
#include "utils.h"
#include "io.h"
#include <sleep.h>
#include <dmac.h>
#include <sysctl_clk.h>
#include <sysctl_rst.h>

typedef struct _i2c_slave_instance
{
    uint32_t i2c_num;
    const i2c_slave_handler_t *slave_handler;
} i2c_slave_instance_t;

static i2c_slave_instance_t slave_instance[I2C_MAX_NUM];

volatile i2c_t *const i2c[7] =
    {
        (volatile i2c_t *)I2C0_BASE_ADDR,
        (volatile i2c_t *)I2C1_BASE_ADDR,
        (volatile i2c_t *)I2C2_BASE_ADDR,
        (volatile i2c_t *)I2C3_BASE_ADDR,
        (volatile i2c_t *)I2C4_BASE_ADDR,
        (volatile i2c_t *)I2C5_BASE_ADDR,
        (volatile i2c_t *)I2C6_BASE_ADDR,
        };

static void i2c_clk_init(i2c_device_number_t i2c_num)
{
    configASSERT(i2c_num < I2C_MAX_NUM);
    //sysctl_clock_enable(SYSCTL_CLOCK_I2C0 + i2c_num);
    //sysctl_clock_set_threshold(SYSCTL_THRESHOLD_I2C0 + i2c_num, 3);
}

void i2c_ss_init(i2c_device_number_t i2c_num, uint32_t slave_address, uint32_t address_width,
              uint32_t i2c_clk, i2c_bus_speed_mode_t speed_mode)
{
    configASSERT(i2c_num < I2C_MAX_NUM);
    configASSERT(address_width == 7 || address_width == 10);

    volatile i2c_t *i2c_adapter = i2c[i2c_num];

    i2c_clk_init(i2c_num);
#ifdef _FPGA
    uint32_t v_i2c_freq = 25000000;//sysctl_clock_get_freq(SYSCTL_CLOCK_I2C0 + i2c_num);
#else
    uint32_t v_i2c_freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_I2C0_SCLK + i2c_num);
#endif
    uint16_t v_period_clk_cnt = v_i2c_freq / i2c_clk / 2;

    if(v_period_clk_cnt == 0)
        v_period_clk_cnt = 1;

    i2c_adapter->enable = 0;
    i2c_adapter->con = I2C_CON_MASTER_MODE | I2C_CON_SLAVE_DISABLE | I2C_CON_RESTART_EN |
                       (address_width == 10 ? I2C_CON_10BITADDR_SLAVE : 0) | I2C_CON_SPEED(speed_mode);
    switch(speed_mode)
    {
        case I2C_BS_STANDARD:
            i2c_adapter->ss_scl_hcnt = I2C_SS_SCL_HCNT_COUNT(v_period_clk_cnt);
            i2c_adapter->ss_scl_lcnt = I2C_SS_SCL_LCNT_COUNT(v_period_clk_cnt);
            break;
        case I2C_BS_FAST:
            i2c_adapter->fs_scl_hcnt = I2C_SS_SCL_HCNT_COUNT(v_period_clk_cnt);
            i2c_adapter->fs_scl_lcnt = I2C_SS_SCL_LCNT_COUNT(v_period_clk_cnt);
            break;
        case I2C_BS_HIGHSPEED:
            i2c_adapter->hs_scl_hcnt = I2C_SS_SCL_HCNT_COUNT(v_period_clk_cnt);
            i2c_adapter->hs_scl_lcnt = I2C_SS_SCL_LCNT_COUNT(v_period_clk_cnt);
            break;
    }

    i2c_adapter->tar = I2C_TAR_ADDRESS(slave_address);
    i2c_adapter->intr_mask = 0;
    i2c_adapter->dma_cr = 0;//0x3;
    i2c_adapter->dma_rdlr = 0;
    i2c_adapter->dma_tdlr = 0;//4;
    i2c_adapter->enable = I2C_ENABLE_ENABLE;
}

uintptr_t i2c_reset_addr[] = {
    0x97002040,
    0x97002044,
};

void i2c_reset(i2c_device_number_t i2c_num)
{
#ifdef _FPGA
    if(i2c_num < 3)
    {
        writel(((1 << (16 + i2c_num)) | (1 << i2c_num)), i2c_reset_addr[0]);
        usleep(50);
        writel((1 << (16 + i2c_num)), i2c_reset_addr[0]);
    }
    else
    {
        writel(((1 << (16 + i2c_num - 3)) | (1 << (i2c_num -3 ))), i2c_reset_addr[1]);
        usleep(50);
        writel((1 << (16 + i2c_num - 3)), i2c_reset_addr[1]);
    }
#else
    sysctl_reset(SYSCTL_RESET_I2C0 + i2c_num);
#endif
}

void i2c_init(i2c_device_number_t i2c_num, uint32_t slave_address, uint32_t address_width,
              uint32_t i2c_clk)
{

    configASSERT(i2c_num < I2C_MAX_NUM);
    configASSERT(address_width == 7 || address_width == 10);

    volatile i2c_t *i2c_adapter = i2c[i2c_num];

    i2c_clk_init(i2c_num);
    i2c_reset(i2c_num);

#ifdef _FPGA
    uint32_t v_i2c_freq = 25000000;//sysctl_clock_get_freq(SYSCTL_CLOCK_I2C0 + i2c_num);
#else
    uint32_t v_i2c_freq = sysctl_clk_get_leaf_freq(SYSCTL_CLK_I2C0_SCLK + i2c_num);
#endif
    uint16_t v_period_clk_cnt = v_i2c_freq / i2c_clk / 2;

    if(v_period_clk_cnt == 0)
        v_period_clk_cnt = 1;

    i2c_adapter->enable = 0;
    i2c_adapter->con = I2C_CON_MASTER_MODE | I2C_CON_SLAVE_DISABLE | I2C_CON_RESTART_EN |
                       (address_width == 10 ? I2C_CON_10BITADDR_SLAVE : 0) | I2C_CON_SPEED(1);
    i2c_adapter->ss_scl_hcnt = I2C_SS_SCL_HCNT_COUNT(v_period_clk_cnt);
    i2c_adapter->ss_scl_lcnt = I2C_SS_SCL_LCNT_COUNT(v_period_clk_cnt);

    i2c_adapter->tar = I2C_TAR_ADDRESS(slave_address);
    i2c_adapter->intr_mask = 0;
    i2c_adapter->dma_cr = 0x3;
    i2c_adapter->dma_rdlr = 0;
    i2c_adapter->dma_tdlr = 4;
    i2c_adapter->enable = I2C_ENABLE_ENABLE;
}

static int i2c_slave_irq(void *userdata)
{
    i2c_slave_instance_t *instance = (i2c_slave_instance_t *)userdata;
    volatile i2c_t *i2c_adapter = i2c[instance->i2c_num];
    uint32_t status = i2c_adapter->intr_stat;
    if(status & I2C_INTR_STAT_START_DET)
    {
        instance->slave_handler->on_event(I2C_EV_START);
        readl(&i2c_adapter->clr_start_det);
    }
    if(status & I2C_INTR_STAT_STOP_DET)
    {
        instance->slave_handler->on_event(I2C_EV_STOP);
        readl(&i2c_adapter->clr_stop_det);
    }
    if(status & I2C_INTR_STAT_RX_FULL)
    {
        instance->slave_handler->on_receive(i2c_adapter->data_cmd);
    }
    if(status & I2C_INTR_STAT_RD_REQ)
    {
        i2c_adapter->data_cmd = instance->slave_handler->on_transmit();
        readl(&i2c_adapter->clr_rd_req);
    }
    return 0;
}

void i2c_init_as_slave(i2c_device_number_t i2c_num, uint32_t slave_address, uint32_t address_width,
                       const i2c_slave_handler_t *handler)
{
    configASSERT(address_width == 7 || address_width == 10);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    slave_instance[i2c_num].i2c_num = i2c_num;
    slave_instance[i2c_num].slave_handler = handler;

    i2c_clk_init(i2c_num);
    i2c_adapter->enable = 0;
    i2c_adapter->con = (address_width == 10 ? I2C_CON_10BITADDR_SLAVE : 0) | I2C_CON_SPEED(1) | I2C_CON_STOP_DET_IFADDRESSED;
    i2c_adapter->ss_scl_hcnt = I2C_SS_SCL_HCNT_COUNT(37);
    i2c_adapter->ss_scl_lcnt = I2C_SS_SCL_LCNT_COUNT(40);
    i2c_adapter->sar = I2C_SAR_ADDRESS(slave_address);
    i2c_adapter->rx_tl = I2C_RX_TL_VALUE(0);
    i2c_adapter->tx_tl = I2C_TX_TL_VALUE(0);
    i2c_adapter->intr_mask = I2C_INTR_MASK_RX_FULL | I2C_INTR_MASK_START_DET | I2C_INTR_MASK_STOP_DET | I2C_INTR_MASK_RD_REQ;

    plic_set_priority(IRQN_I2C0_INTERRUPT + i2c_num, 1);
    plic_irq_register(IRQN_I2C0_INTERRUPT + i2c_num, i2c_slave_irq, slave_instance + i2c_num);
    plic_irq_enable(IRQN_I2C0_INTERRUPT + i2c_num);

    i2c_adapter->enable = I2C_ENABLE_ENABLE;
}

int i2c_send_data(i2c_device_number_t i2c_num, const uint8_t *send_buf, size_t send_buf_len)
{
    configASSERT(i2c_num < I2C_MAX_NUM);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    size_t fifo_len, index;
    i2c_adapter->clr_tx_abrt = i2c_adapter->clr_tx_abrt;
    while(send_buf_len)
    {
        fifo_len = 8 - i2c_adapter->txflr;
        fifo_len = send_buf_len < fifo_len ? send_buf_len : fifo_len;
        for(index = 0; index < fifo_len; index++)
            i2c_adapter->data_cmd = I2C_DATA_CMD_DATA(*send_buf++);
        if(i2c_adapter->tx_abrt_source != 0)
            return 1;
        send_buf_len -= fifo_len;
    }
    while((i2c_adapter->status & I2C_STATUS_ACTIVITY) || !(i2c_adapter->status & I2C_STATUS_TFE))
        ;

    if(i2c_adapter->tx_abrt_source != 0)
        return 1;

    return 0;
}
void i2c_send_data_dma(dma_ch_t dma_channel_num, i2c_device_number_t i2c_num, const uint8_t *send_buf, size_t send_buf_len)
{
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    i2c_adapter->clr_tx_abrt = i2c_adapter->clr_tx_abrt;
    uint32_t *buf = malloc(send_buf_len * sizeof(uint32_t));
    int i;
    for(i = 0; i < send_buf_len; i++)
    {
        buf[i] = send_buf[i];
    }

    volatile uint32_t* const tx = (volatile uint32_t*)(&i2c_adapter->data_cmd);
    peri_dma_cfg_t peri_tx_cfg = {
        .channel = dma_channel_num,
        .dev_sel = I2C0_TX + i2c_num*2,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = CONTINUOUS_ADDRESS,
        .buswidth = FOUR_BYTE,
        .dev_burst_len = 0,
        .line_size = send_buf_len * 4,
        .saddr = (void*)buf,
        .daddr = (void*)tx,
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&peri_tx_cfg);
    peri_dma_start(dma_channel_num);
    peri_dma_wait_done_or_timeout(dma_channel_num);
    if (peri_dma_is_timeout(dma_channel_num)) {
        k510_logd("%s", "peri dma ch0 is timeout.");
    } else {
        k510_logd("%s", "peri dma ch0 transfer finished.");
    }
    free((void *)buf);
    while((i2c_adapter->status & I2C_STATUS_ACTIVITY) || !(i2c_adapter->status & I2C_STATUS_TFE))
    {
        if(i2c_adapter->tx_abrt_source != 0)
            return;
    }
}
// void i2c_send_data_dma(dma_ch_t dma_channel_num, i2c_device_number_t i2c_num, const uint8_t *send_buf,
//                        size_t send_buf_len)
// {
    /*configASSERT(i2c_num < I2C_MAX_NUM);
    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    i2c_adapter->clr_tx_abrt = i2c_adapter->clr_tx_abrt;
#if FIX_CACHE
    uint32_t *buf = iomem_malloc(send_buf_len * sizeof(uint32_t));
#else
    uint32_t *buf = malloc(send_buf_len * sizeof(uint32_t));
#endif
    int i;
    for(i = 0; i < send_buf_len; i++)
    {
        buf[i] = send_buf[i];
    }

    sysctl_dma_select((sysctl_dma_channel_t)dma_channel_num, SYSCTL_DMA_SELECT_I2C0_TX_REQ + i2c_num * 2);
    dmac_set_single_mode(dma_channel_num, buf, (void *)(&i2c_adapter->data_cmd), DMAC_ADDR_INCREMENT, DMAC_ADDR_NOCHANGE,
                         DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, send_buf_len);

    dmac_wait_done(dma_channel_num);
#if FIX_CACHE
    iomem_free((void *)buf);
#else
    free((void *)buf);
#endif

    while((i2c_adapter->status & I2C_STATUS_ACTIVITY) || !(i2c_adapter->status & I2C_STATUS_TFE))
    {
        if(i2c_adapter->tx_abrt_source != 0)
            return;
    }
  */
// }

int i2c_recv_data(i2c_device_number_t i2c_num, const uint8_t *send_buf, size_t send_buf_len, uint8_t *receive_buf,
                  size_t receive_buf_len)
{
    configASSERT(i2c_num < I2C_MAX_NUM);

    size_t fifo_len, index;
    size_t rx_len = receive_buf_len;
    volatile i2c_t *i2c_adapter = i2c[i2c_num];

    while(send_buf_len)
    {
        fifo_len = 8 - i2c_adapter->txflr;
        fifo_len = send_buf_len < fifo_len ? send_buf_len : fifo_len;
        for(index = 0; index < fifo_len; index++)
            i2c_adapter->data_cmd = I2C_DATA_CMD_DATA(*send_buf++);
        if(i2c_adapter->tx_abrt_source != 0)
            return 1;
        send_buf_len -= fifo_len;
    }

    while(receive_buf_len || rx_len)
    {
        fifo_len = i2c_adapter->rxflr;
        fifo_len = rx_len < fifo_len ? rx_len : fifo_len;
        for(index = 0; index < fifo_len; index++)
            *receive_buf++ = (uint8_t)i2c_adapter->data_cmd;
        rx_len -= fifo_len;
        fifo_len = 8 - i2c_adapter->txflr;
        fifo_len = receive_buf_len < fifo_len ? receive_buf_len : fifo_len;
        for(index = 0; index < fifo_len; index++)
            i2c_adapter->data_cmd = I2C_DATA_CMD_CMD;
        if(i2c_adapter->tx_abrt_source != 0)
            return 1;
        receive_buf_len -= fifo_len;
    }
    return 0;
}

void i2c_recv_data_dma(dma_ch_t dma_send_channel_num, dma_ch_t dma_receive_channel_num,
                       i2c_device_number_t i2c_num, const uint8_t *send_buf, size_t send_buf_len,
                       uint8_t *receive_buf, size_t receive_buf_len)
{
    volatile i2c_t *i2c_adapter = i2c[i2c_num];

    uint32_t *write_cmd = malloc(sizeof(uint32_t) * (send_buf_len + receive_buf_len));

    size_t i;
    for(i = 0; i < send_buf_len; i++)
        write_cmd[i] = *send_buf++;
    for(i = 0; i < receive_buf_len; i++)
        write_cmd[i + send_buf_len] = I2C_DATA_CMD_CMD;

    volatile uint32_t* const tx = (volatile uint32_t*)(&i2c_adapter->data_cmd);
    peri_dma_cfg_t peri_tx_cfg = {
        .channel = dma_send_channel_num,
        .dev_sel = I2C0_TX + i2c_num*2,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = CONTINUOUS_ADDRESS,
        .buswidth = FOUR_BYTE,
        .dev_burst_len = 0,
        .line_size = (receive_buf_len + send_buf_len) * 4,
        .saddr = (void*)write_cmd,
        .daddr = (void*)tx,
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&peri_tx_cfg);

    peri_dma_cfg_t peri_rx_cfg = {
        .channel = dma_receive_channel_num,
        .dev_sel = I2C0_RX + i2c_num*2,
        .ch_priority = 1,
        .mode = LINE_MODE,
        .src_type = FIXED_REG_ADDRESS,
        .buswidth = ONE_BYTE,
        .dev_burst_len = 0,
        .line_size = receive_buf_len,
        .saddr = (void*)tx,
        .daddr = (void*)receive_buf,
        .dev_timeout = 0xFFF
    };
    peri_dma_config(&peri_rx_cfg);

    peri_dma_start(dma_receive_channel_num);
    peri_dma_start(dma_send_channel_num);

    peri_dma_wait_done_or_timeout(dma_send_channel_num);
    if (peri_dma_is_timeout(dma_send_channel_num)) {
        k510_logd("%s", "peri dma ch0 is timeout.");
    } else {
        k510_logd("%s", "peri dma ch0 transfer finished.");
    }
    peri_dma_wait_done_or_timeout(dma_receive_channel_num);
    if (peri_dma_is_timeout(dma_receive_channel_num)) {
        k510_logd("%s", "peri dma ch0 is timeout.");
    } else {
        k510_logd("%s", "peri dma ch0 transfer finished.");
    }

    free(write_cmd);
}


// void i2c_recv_data_dma(dma_ch_t dma_send_channel_num, dma_ch_t dma_receive_channel_num,
//                        i2c_device_number_t i2c_num, const uint8_t *send_buf, size_t send_buf_len,
//                        uint8_t *receive_buf, size_t receive_buf_len)
// {
/*    configASSERT(i2c_num < I2C_MAX_NUM);

    volatile i2c_t *i2c_adapter = i2c[i2c_num];
#if FIX_CACHE
    uint32_t *write_cmd = iomem_malloc(sizeof(uint32_t) * (send_buf_len + receive_buf_len));
#else
    uint32_t *write_cmd = malloc(sizeof(uint32_t) * (send_buf_len + receive_buf_len));
#endif
    size_t i;
    for(i = 0; i < send_buf_len; i++)
        write_cmd[i] = *send_buf++;
    for(i = 0; i < receive_buf_len; i++)
        write_cmd[i + send_buf_len] = I2C_DATA_CMD_CMD;

    sysctl_dma_select((sysctl_dma_channel_t)dma_send_channel_num, SYSCTL_DMA_SELECT_I2C0_TX_REQ + i2c_num * 2);
    sysctl_dma_select((sysctl_dma_channel_t)dma_receive_channel_num, SYSCTL_DMA_SELECT_I2C0_RX_REQ + i2c_num * 2);

    dmac_set_single_mode(dma_receive_channel_num, (void *)(&i2c_adapter->data_cmd), write_cmd, DMAC_ADDR_NOCHANGE,
                         DMAC_ADDR_INCREMENT, DMAC_MSIZE_1, DMAC_TRANS_WIDTH_32, receive_buf_len);

    dmac_set_single_mode(dma_send_channel_num, write_cmd, (void *)(&i2c_adapter->data_cmd), DMAC_ADDR_INCREMENT,
                         DMAC_ADDR_NOCHANGE, DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, receive_buf_len + send_buf_len);

    dmac_wait_done(dma_send_channel_num);
    dmac_wait_done(dma_receive_channel_num);

    for(i = 0; i < receive_buf_len; i++)
    {
        receive_buf[i] = (uint8_t)write_cmd[i];
    }
#if FIX_CACHE
        iomem_free(write_cmd);
#else
        free(write_cmd);
#endif
*/
// }
/*
static int i2c_dma_irq(void *ctx)
{
    i2c_instance_t *v_instance = (i2c_instance_t *)ctx;
    volatile i2c_t *i2c_adapter = i2c[v_instance->i2c_num];
    dmac_irq_unregister(v_instance->dmac_channel);
    if(v_instance->transfer_mode == I2C_SEND)
    {
        while((i2c_adapter->status & I2C_STATUS_ACTIVITY) || !(i2c_adapter->status & I2C_STATUS_TFE))
        {
            if(i2c_adapter->tx_abrt_source != 0)
            {
                spinlock_unlock(&v_instance->lock);
                return -1;
            }
        }
    }
    spinlock_unlock(&v_instance->lock);
    if(v_instance->i2c_int_instance.callback)
    {
        v_instance->i2c_int_instance.callback(v_instance->i2c_int_instance.ctx);
    }

    return 0;

}
*/
// void i2c_handle_data_dma(i2c_device_number_t i2c_num, i2c_data_t data,  plic_instance_t *cb)
// {
   /* configASSERT(i2c_num < I2C_MAX_NUM);
    configASSERT(data.tx_channel < DMAC_CHANNEL_MAX && data.rx_channel < DMAC_CHANNEL_MAX);

    spinlock_lock(&g_i2c_instance[i2c_num].lock);
    if(cb)
    {
        g_i2c_instance[i2c_num].i2c_int_instance.callback = cb->callback;
        g_i2c_instance[i2c_num].i2c_int_instance.ctx = cb->ctx;
    }

    volatile i2c_t *i2c_adapter = i2c[i2c_num];
    if(data.transfer_mode == I2C_SEND)
    {
        configASSERT(data.tx_buf && data.tx_len);

        i2c_adapter->clr_tx_abrt = i2c_adapter->clr_tx_abrt;
        if(cb)
        {
            g_i2c_instance[i2c_num].dmac_channel = data.tx_channel;
            g_i2c_instance[i2c_num].transfer_mode = I2C_SEND;
            dmac_irq_register(data.tx_channel, i2c_dma_irq, &g_i2c_instance[i2c_num], cb->priority);
        }
        sysctl_dma_select((sysctl_dma_channel_t)data.tx_channel, SYSCTL_DMA_SELECT_I2C0_TX_REQ + i2c_num * 2);
        dmac_set_single_mode(data.tx_channel, data.tx_buf, (void *)(&i2c_adapter->data_cmd), DMAC_ADDR_INCREMENT, DMAC_ADDR_NOCHANGE,
                             DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, data.tx_len);
        if(!cb)
        {
            dmac_wait_done(data.tx_channel);
            while((i2c_adapter->status & I2C_STATUS_ACTIVITY) || !(i2c_adapter->status & I2C_STATUS_TFE))
            {
                if(i2c_adapter->tx_abrt_source != 0)
                    configASSERT(!"source abort");
            }
        }
    } else
    {
        configASSERT(data.rx_buf && data.rx_len);
        if(data.tx_len)
            configASSERT(data.tx_buf);
        if(cb)
        {
            g_i2c_instance[i2c_num].dmac_channel = data.rx_channel;
            g_i2c_instance[i2c_num].transfer_mode = I2C_RECEIVE;
            dmac_irq_register(data.rx_channel, i2c_dma_irq, &g_i2c_instance[i2c_num], cb->priority);
        }
        sysctl_dma_select((sysctl_dma_channel_t)data.rx_channel, SYSCTL_DMA_SELECT_I2C0_RX_REQ + i2c_num * 2);
        dmac_set_single_mode(data.rx_channel, (void *)(&i2c_adapter->data_cmd), data.rx_buf, DMAC_ADDR_NOCHANGE,
                             DMAC_ADDR_INCREMENT, DMAC_MSIZE_1, DMAC_TRANS_WIDTH_32, data.rx_len);

        sysctl_dma_select((sysctl_dma_channel_t)data.tx_channel, SYSCTL_DMA_SELECT_I2C0_TX_REQ + i2c_num * 2);
        if(data.tx_len)
        {
            configASSERT(data.tx_buf);
            dmac_set_single_mode(data.tx_channel, data.tx_buf, (void *)(&i2c_adapter->data_cmd), DMAC_ADDR_INCREMENT,
                                 DMAC_ADDR_NOCHANGE, DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, data.tx_len);
            dmac_wait_done(data.tx_channel);
        }
        static uint32_t s_read_cmd = I2C_DATA_CMD_CMD;
        dmac_set_single_mode(data.tx_channel, &s_read_cmd, (void *)(&i2c_adapter->data_cmd), DMAC_ADDR_NOCHANGE,
                             DMAC_ADDR_NOCHANGE, DMAC_MSIZE_1, DMAC_TRANS_WIDTH_32, data.rx_len);

        if(!cb)
        {
            dmac_wait_done(data.tx_channel);
            dmac_wait_done(data.rx_channel);
        }
    }
    if(!cb)
        spinlock_unlock(&g_i2c_instance[i2c_num].lock);
*/
// }
