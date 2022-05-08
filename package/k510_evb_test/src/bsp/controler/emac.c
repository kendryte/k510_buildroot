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
#include "emac.h"
#include "platform.h"
#include "emac_regs_non_vm.h"
#include "muxpin.h"
#include "io.h"
#include <string.h>
#include <assert.h>
#include <gpio.h>
#include <sysctl_rst.h>
#include <sleep.h>

volatile emac_t* const  emac = (volatile emac_t*)EMAC_BASE_ADDR;

emac_txqueue_t tx_queue[EMAC_QUEUE_NUMBER_MAX];
emac_rxqueue_t rx_queue[EMAC_QUEUE_NUMBER_MAX];

emac_general_callback_t emac_general_callback;  /* Q0 general interrupt */
emac_qn_callback_t emac_qn_callback[2];         /* Q1 Q2 interrupt */

static int emac_general_callback_func(void *ctx)
{
    uint32_t int_status = emac->int_status;
    emac->int_status = int_status;  /* clear interrupt */

    if(int_status & EMAC_GENERAL_SMI_SEND)
    {
        if(emac_general_callback.smi_complete)
            emac_general_callback.smi_complete(emac_general_callback.smi_complete_ctx);
        else
            k510_logci("General Smi send complete\n");
    }

    if(int_status & EMAC_GENERAL_RECEIVE_COMPLETE)
    {
        if(emac_general_callback.rx_complete)
            emac_general_callback.rx_complete(emac_general_callback.rx_complete_ctx);
        else
            k510_logci("General receive a frame\n");
    }

    if(int_status & EMAC_GENERAL_RX_USED_BIT_READ)
    {
        if(emac_general_callback.rx_used_bit_read)
            emac_general_callback.rx_used_bit_read(emac_general_callback.rx_used_bit_read_ctx);
        else
            k510_logci("General rx_used_bit_read\n");
    }

    if(int_status & EMAC_GENERAL_TX_USED_BIT_READ)
    {
        if(emac_general_callback.tx_used_bit_read)
            emac_general_callback.tx_used_bit_read(emac_general_callback.tx_used_bit_read_ctx);
        else
            k510_logci("General tx_used_bit_read\n");
    }

    if(int_status & EMAC_GENERAL_TRANSMIT_UNDER_RUN)
    {
        if(emac_general_callback.transmit_under_run)
            emac_general_callback.transmit_under_run(emac_general_callback.transmit_under_run_ctx);
        else
            k510_logci("General transmit_under_run\n");
    }

    if(int_status & EMAC_GENERAL_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION)
    {
        if(emac_general_callback.limit_exceeded_late_collison)
            emac_general_callback.limit_exceeded_late_collison(emac_general_callback.limit_exceeded_late_collison_ctx);
        else
            k510_logci("General limit_exceeded_late_collison\n");
    }

    if(int_status & EMAC_GENERAL_AMBA_ERROR)
    {
        if(emac_general_callback.amba_error)
            emac_general_callback.amba_error(emac_general_callback.amba_error_ctx);
        else
            k510_logci("General amba_error\n");
    }

    if(int_status & EMAC_GENERAL_TRANSMIT_COMPLETE)
    {
        if(emac_general_callback.tx_complete)
            emac_general_callback.tx_complete(emac_general_callback.tx_complete_ctx);
        else
            k510_logci("General tx_complete\n");
    }

    if(int_status & EMAC_GENERAL_RECEIVE_OVERRUN)
    {
        if(emac_general_callback.rx_overrun)
            emac_general_callback.rx_overrun(emac_general_callback.rx_overrun_ctx);
        else
            k510_logci("General rx_overrun\n");
    }

    if(int_status & EMAC_GENERAL_RESP_NOT_OK)
    {
        if(emac_general_callback.resp_not_ok)
            emac_general_callback.resp_not_ok(emac_general_callback.resp_not_ok_ctx);
        else
            k510_logci("General resp_not_ok\n");
    }

    if(int_status & EMAC_GENERAL_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED)
    {
        if(emac_general_callback.pause_nonzero_received)
            emac_general_callback.pause_nonzero_received(emac_general_callback.pause_nonzero_received_ctx);
        else
            k510_logci("General pause_nonzero_received\n");
    }

    if(int_status & EMAC_GENERAL_PAUSE_TIME_ELAPSED_ZERO_PAUSE_QUANTUM_RECEIVED)
    {
        if(emac_general_callback.pause_time_elapse)
            emac_general_callback.pause_time_elapse(emac_general_callback.pause_time_elapse_ctx);
        else
            k510_logci("General pause_time_elapse or receive zero pause frame\n");
    }

    if(int_status & EMAC_GENERAL_PAUSE_FRAME_TRANSMITTED)
    {
        if(emac_general_callback.pause_tx_transmitted)
            emac_general_callback.pause_tx_transmitted(emac_general_callback.pause_tx_transmitted_ctx);
        else
            k510_logci("General pause_tx_transmitted\n");
    }

    if(int_status & EMAC_GENERAL_EXTERNAL_INTERRUPT)
    {
        if(emac_general_callback.external_interrupt)
            emac_general_callback.external_interrupt(emac_general_callback.external_interrupt_ctx);
        else
            k510_logci("General external_interrupt\n");
    }

    if(int_status & EMAC_GENERAL_PTP_DELAY_REQ_FRAME_RECEIVED)
    {
        if(emac_general_callback.ptp_dreq_received)
            emac_general_callback.ptp_dreq_received(emac_general_callback.ptp_dreq_received_ctx);
        else
            k510_logci("General PTP_DELAY_REQ_FRAME_RECEIVED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_SYNC_FRAME_RECEIVED)
    {
        if(emac_general_callback.ptp_sync_received)
            emac_general_callback.ptp_sync_received(emac_general_callback.ptp_sync_received_ctx);
        else
            k510_logci("General PTP_SYNC_FRAME_RECEIVED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_DELAY_REQ_FRAME_TRANSMITTED)
    {
        if(emac_general_callback.ptp_dreq_tranmitted)
            emac_general_callback.ptp_dreq_tranmitted(emac_general_callback.ptp_dreq_tranmitted_ctx);
        else
            k510_logci("General PTP_DELAY_REQ_FRAME_TRANSMITTED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_SYNC_FRAME_TRANSMITTED)
    {
        if(emac_general_callback.ptp_sync_transmitted)
            emac_general_callback.ptp_sync_transmitted(emac_general_callback.ptp_sync_transmitted_ctx);
        else
            k510_logci("General PTP_SYNC_FRAME_TRANSMITTED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_RECEIVED)
    {
        if(emac_general_callback.ptp_pdreq_received)
            emac_general_callback.ptp_pdreq_received(emac_general_callback.ptp_pdreq_received_ctx);
        else
            k510_logci("General PTP_PDELAY_REQ_FRAME_RECEIVED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_RECEIVED)
    {
        if(emac_general_callback.ptp_pdresq_received)
            emac_general_callback.ptp_pdresq_received(emac_general_callback.ptp_pdresq_received_ctx);
        else
            k510_logci("General PTP_PDELAY_RESP_FRAME_RECEIVED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_TRANSMITTED)
    {
        if(emac_general_callback.ptp_pdreq_transmitted)
            emac_general_callback.ptp_pdreq_transmitted(emac_general_callback.ptp_pdreq_transmitted_ctx);
        else
            k510_logci("General PTP_PDELAY_REQ_FRAME_TRANSMITTED\n");
    }

    if(int_status & EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_TRANSMITTED)
    {
        if(emac_general_callback.ptp_pdresq_transmitted)
            emac_general_callback.ptp_pdresq_transmitted(emac_general_callback.ptp_pdresq_transmitted_ctx);
        else
            k510_logci("General PTP_PDELAY_RESP_FRAME_TRANSMITTED\n");
    }

    if(int_status & EMAC_GENERAL_TSU_SECONDS_REGISTER_INCREMENT)
    {
        if(emac_general_callback.tsu_second_increment)
            emac_general_callback.tsu_second_increment(emac_general_callback.tsu_second_increment_ctx);
        else
            k510_logci("General TSU_SECONDS_REGISTER_INCREMENT\n");
    }

    if(int_status & EMAC_GENERAL_RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE)
    {
        if(emac_general_callback.lpi_status_changed)
            emac_general_callback.lpi_status_changed(emac_general_callback.lpi_status_changed_ctx);
        else
            k510_logci("General RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE\n");
    }

    if(int_status & EMAC_GENERAL_WOL_INTERRUPT)
    {
        if(emac_general_callback.wol_interrupt)
            emac_general_callback.wol_interrupt(emac_general_callback.wol_interrupt_ctx);
        else
            k510_logci("General WOL_INTERRUPT\n");
    }

    if(int_status & EMAC_GENERAL_TSU_TIMER_COMPARISON_INTERRUPT)
    {
        if(emac_general_callback.tsu_timer_comparis_on)
            emac_general_callback.tsu_timer_comparis_on(emac_general_callback.tsu_timer_comparis_on_ctx);
        else
            k510_logci("General TSU_TIMER_COMPARISON_INTERRUPT\n");
    }

    if(int_status & EMAC_GENERAL_RX_LOCKUP_DETECTED)
    {
        if(emac_general_callback.rx_lockup)
            emac_general_callback.rx_lockup(emac_general_callback.rx_lockup_ctx);
        else
            k510_logci("General RX_LOCKUP_DETECTED\n");
    }

    if(int_status & EMAC_GENERAL_TX_LOCKUP_DETECTED)
    {
        if(emac_general_callback.tx_lockup)
            emac_general_callback.tx_lockup(emac_general_callback.tx_lockup_ctx);
        else
            k510_logci("General TX_LOCKUP_DETECTED\n");
    }
    return 0;
}

int emac_general_irq_register(uint32_t int_type, plic_irq_callback_t cb, void *ctx)
{
    emac->int_enable = int_type;
    if(int_type & EMAC_GENERAL_SMI_SEND)
    {
        emac_general_callback.smi_complete = cb;
        emac_general_callback.smi_complete_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RECEIVE_COMPLETE)
    {
        emac_general_callback.rx_complete = cb;
        emac_general_callback.rx_complete_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RX_USED_BIT_READ)
    {
        emac_general_callback.rx_used_bit_read = cb;
        emac_general_callback.rx_used_bit_read_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_TX_USED_BIT_READ)
    {
        emac_general_callback.tx_used_bit_read = cb;
        emac_general_callback.tx_used_bit_read_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_TRANSMIT_UNDER_RUN)
    {
        emac_general_callback.transmit_under_run = cb;
        emac_general_callback.transmit_under_run_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION)
    {
        emac_general_callback.limit_exceeded_late_collison = cb;
        emac_general_callback.limit_exceeded_late_collison_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_AMBA_ERROR)
    {
        emac_general_callback.amba_error = cb;
        emac_general_callback.amba_error_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_TRANSMIT_COMPLETE)
    {
        emac_general_callback.tx_complete = cb;
        emac_general_callback.tx_complete_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RECEIVE_OVERRUN)
    {
        emac_general_callback.rx_overrun = cb;
        emac_general_callback.rx_overrun_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RESP_NOT_OK)
    {
        emac_general_callback.resp_not_ok = cb;
        emac_general_callback.resp_not_ok_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED)
    {
        emac_general_callback.pause_nonzero_received = cb;
        emac_general_callback.pause_nonzero_received_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PAUSE_TIME_ELAPSED_ZERO_PAUSE_QUANTUM_RECEIVED)
    {
        emac_general_callback.pause_time_elapse = cb;
        emac_general_callback.pause_time_elapse_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PAUSE_FRAME_TRANSMITTED)
    {
        emac_general_callback.pause_tx_transmitted = cb;
        emac_general_callback.pause_tx_transmitted_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_EXTERNAL_INTERRUPT)
    {
        emac_general_callback.external_interrupt = cb;
        emac_general_callback.external_interrupt_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_DELAY_REQ_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_dreq_received = cb;
        emac_general_callback.ptp_dreq_received_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_SYNC_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_sync_received = cb;
        emac_general_callback.ptp_sync_received_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_DELAY_REQ_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_dreq_tranmitted = cb;
        emac_general_callback.ptp_dreq_tranmitted_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_SYNC_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_sync_transmitted = cb;
        emac_general_callback.ptp_sync_transmitted_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_pdreq_received = cb;
        emac_general_callback.ptp_pdreq_received_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_pdresq_received = cb;
        emac_general_callback.ptp_pdresq_received_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_pdreq_transmitted = cb;
        emac_general_callback.ptp_pdreq_transmitted_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_pdresq_transmitted = cb;
        emac_general_callback.ptp_pdresq_transmitted_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_TSU_SECONDS_REGISTER_INCREMENT)
    {
        emac_general_callback.tsu_second_increment = cb;
        emac_general_callback.tsu_second_increment_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE)
    {
        emac_general_callback.lpi_status_changed = cb;
        emac_general_callback.lpi_status_changed_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_WOL_INTERRUPT)
    {
        emac_general_callback.wol_interrupt = cb;
        emac_general_callback.wol_interrupt_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_TSU_TIMER_COMPARISON_INTERRUPT)
    {
        emac_general_callback.tsu_timer_comparis_on = cb;
        emac_general_callback.tsu_timer_comparis_on_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_RX_LOCKUP_DETECTED)
    {
        emac_general_callback.rx_lockup = cb;
        emac_general_callback.rx_lockup_ctx = ctx;
    }

    if(int_type & EMAC_GENERAL_TX_LOCKUP_DETECTED)
    {
        emac_general_callback.tx_lockup = cb;
        emac_general_callback.tx_lockup_ctx = ctx;
    }
    return 0;
}

int emac_general_irq_unregister(uint32_t int_type)
{
    emac->int_disable = int_type;
    if(int_type & EMAC_GENERAL_SMI_SEND)
    {
        emac_general_callback.smi_complete = NULL;
        emac_general_callback.smi_complete_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RECEIVE_COMPLETE)
    {
        emac_general_callback.rx_complete = NULL;
        emac_general_callback.rx_complete_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RX_USED_BIT_READ)
    {
        emac_general_callback.rx_used_bit_read = NULL;
        emac_general_callback.rx_used_bit_read_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_TX_USED_BIT_READ)
    {
        emac_general_callback.tx_used_bit_read = NULL;
        emac_general_callback.tx_used_bit_read_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_TRANSMIT_UNDER_RUN)
    {
        emac_general_callback.transmit_under_run = NULL;
        emac_general_callback.transmit_under_run_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION)
    {
        emac_general_callback.limit_exceeded_late_collison = NULL;
        emac_general_callback.limit_exceeded_late_collison_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_AMBA_ERROR)
    {
        emac_general_callback.amba_error = NULL;
        emac_general_callback.amba_error_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_TRANSMIT_COMPLETE)
    {
        emac_general_callback.tx_complete = NULL;
        emac_general_callback.tx_complete_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RECEIVE_OVERRUN)
    {
        emac_general_callback.rx_overrun = NULL;
        emac_general_callback.rx_overrun_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RESP_NOT_OK)
    {
        emac_general_callback.resp_not_ok = NULL;
        emac_general_callback.resp_not_ok_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_RECEIVED)
    {
        emac_general_callback.pause_nonzero_received = NULL;
        emac_general_callback.pause_nonzero_received_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PAUSE_TIME_ELAPSED_ZERO_PAUSE_QUANTUM_RECEIVED)
    {
        emac_general_callback.pause_time_elapse = NULL;
        emac_general_callback.pause_time_elapse_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PAUSE_FRAME_TRANSMITTED)
    {
        emac_general_callback.pause_tx_transmitted = NULL;
        emac_general_callback.pause_tx_transmitted_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_EXTERNAL_INTERRUPT)
    {
        emac_general_callback.external_interrupt = NULL;
        emac_general_callback.external_interrupt_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_DELAY_REQ_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_dreq_received = NULL;
        emac_general_callback.ptp_dreq_received_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_SYNC_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_sync_received = NULL;
        emac_general_callback.ptp_sync_received_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_DELAY_REQ_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_dreq_tranmitted = NULL;
        emac_general_callback.ptp_dreq_tranmitted_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_SYNC_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_sync_transmitted = NULL;
        emac_general_callback.ptp_sync_transmitted_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_pdreq_received = NULL;
        emac_general_callback.ptp_pdreq_received_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_RECEIVED)
    {
        emac_general_callback.ptp_pdresq_received = NULL;
        emac_general_callback.ptp_pdresq_received_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_REQ_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_pdreq_transmitted = NULL;
        emac_general_callback.ptp_pdreq_transmitted_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_PTP_PDELAY_RESP_FRAME_TRANSMITTED)
    {
        emac_general_callback.ptp_pdresq_transmitted = NULL;
        emac_general_callback.ptp_pdresq_transmitted_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_TSU_SECONDS_REGISTER_INCREMENT)
    {
        emac_general_callback.tsu_second_increment = NULL;
        emac_general_callback.tsu_second_increment_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RECEIVE_LPI_INDICATION_STATUS_BIT_CHANGE)
    {
        emac_general_callback.lpi_status_changed = NULL;
        emac_general_callback.lpi_status_changed_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_WOL_INTERRUPT)
    {
        emac_general_callback.wol_interrupt = NULL;
        emac_general_callback.wol_interrupt_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_TSU_TIMER_COMPARISON_INTERRUPT)
    {
        emac_general_callback.tsu_timer_comparis_on = NULL;
        emac_general_callback.tsu_timer_comparis_on_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_RX_LOCKUP_DETECTED)
    {
        emac_general_callback.rx_lockup = NULL;
        emac_general_callback.rx_lockup_ctx = NULL;
    }

    if(int_type & EMAC_GENERAL_TX_LOCKUP_DETECTED)
    {
        emac_general_callback.tx_lockup = NULL;
        emac_general_callback.tx_lockup_ctx = NULL;
    }
    return 0;
}

static int emac_gn_callback_func(void *ctx)
{
    emac_qn_callback_t *qn_cb = (emac_qn_callback_t *)ctx;
    uint32_t *int_status_reg = (uint32_t *)((uintptr_t)(&emac->int_q1_status) + (qn_cb->qnum - 1) * 4);
    uint32_t int_status = *int_status_reg;
    *int_status_reg = int_status;   /* clear interrupt */

    if(int_status & EMAC_QN_RECEIVE_COMPLETE)
    {
        if(qn_cb->rx_complete)
            qn_cb->rx_complete(qn_cb->rx_complete_ctx);
        else
            k510_logci("Q%d receive a frame\n", qn_cb->qnum);
    }

    if(int_status & EMAC_QN_RX_USED_BIT_READ)
    {
        if(qn_cb->rx_used_bit_read)
            qn_cb->rx_used_bit_read(qn_cb->rx_used_bit_read_ctx);
        else
            k510_logci("Q%d rx_used_bit_read\n", qn_cb->qnum);
    }

    if(int_status & EMAC_QN_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION)
    {
        if(qn_cb->limit_exceeded_late_collison)
            qn_cb->limit_exceeded_late_collison(qn_cb->limit_exceeded_late_collison_ctx);
        else
            k510_logci("Q%d limit_exceeded_late_collison\n", qn_cb->qnum);
    }

    if(int_status & EMAC_QN_AMBA_ERROR)
    {
        if(qn_cb->amba_error)
            qn_cb->amba_error(qn_cb->amba_error_ctx);
        else
            k510_logci("Q%d amba_error\n", qn_cb->qnum);
    }

    if(int_status & EMAC_QN_TRANSMIT_COMPLETE)
    {
        if(qn_cb->tx_complete)
            qn_cb->tx_complete(qn_cb->tx_complete_ctx);
        else
            k510_logci("Q%d tx_complete\n", qn_cb->qnum);
    }

    if(int_status & EMAC_QN_RESP_NOT_OK)
    {
        if(qn_cb->resp_not_ok)
            qn_cb->resp_not_ok(qn_cb->resp_not_ok_ctx);
        else
            k510_logci("Q%d resp_not_ok\n", qn_cb->qnum);
    }
    return 0;
}

int emac_qn_irq_register(emac_queue_number_t qnum, uint32_t int_type, plic_irq_callback_t cb, void *ctx)
{
    emac_qn_callback_t *qn_cb = (emac_qn_callback_t *)&emac_qn_callback[qnum - 1];
    uint32_t *int_enable_reg = (uint32_t *)((uintptr_t)(&emac->int_q1_enable) + (qnum - 1) * 4);

    *int_enable_reg = int_type;

    if(int_type & EMAC_QN_RECEIVE_COMPLETE)
    {
        qn_cb->rx_complete = cb;
        qn_cb->rx_complete_ctx = ctx;
    }

    if(int_type & EMAC_QN_RX_USED_BIT_READ)
    {
        qn_cb->rx_used_bit_read = cb;
        qn_cb->rx_used_bit_read_ctx = ctx;
    }

    if(int_type & EMAC_QN_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION)
    {
        qn_cb->limit_exceeded_late_collison = cb;
        qn_cb->limit_exceeded_late_collison_ctx = ctx;
    }

    if(int_type & EMAC_QN_AMBA_ERROR)
    {
        qn_cb->amba_error = cb;
        qn_cb->amba_error_ctx = ctx;
    }

    if(int_type & EMAC_QN_TRANSMIT_COMPLETE)
    {
        qn_cb->tx_complete = cb;
        qn_cb->tx_complete_ctx = ctx;
    }

    if(int_type & EMAC_QN_RESP_NOT_OK)
    {
        qn_cb->resp_not_ok = cb;
        qn_cb->resp_not_ok_ctx = ctx;
    }
    return 0;
}

int emac_qn_irq_unsregister(emac_queue_number_t qnum, uint32_t int_type)
{
    emac_qn_callback_t *qn_cb = (emac_qn_callback_t *)&emac_qn_callback[qnum - 1];
    uint32_t *int_disable_reg = (uint32_t *)((uintptr_t)(&emac->int_q1_disable) + (qnum - 1) * 4);

    *int_disable_reg = int_type;

    if(int_type & EMAC_QN_RECEIVE_COMPLETE)
    {
        qn_cb->rx_complete = NULL;
        qn_cb->rx_complete_ctx = NULL;
    }

    if(int_type & EMAC_QN_RX_USED_BIT_READ)
    {
        qn_cb->rx_used_bit_read = NULL;
        qn_cb->rx_used_bit_read_ctx = NULL;
    }

    if(int_type & EMAC_QN_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION)
    {
        qn_cb->limit_exceeded_late_collison = NULL;
        qn_cb->limit_exceeded_late_collison_ctx = NULL;
    }

    if(int_type & EMAC_QN_AMBA_ERROR)
    {
        qn_cb->amba_error = NULL;
        qn_cb->amba_error_ctx = NULL;
    }

    if(int_type & EMAC_QN_TRANSMIT_COMPLETE)
    {
        qn_cb->tx_complete = NULL;
        qn_cb->tx_complete_ctx = NULL;
    }

    if(int_type & EMAC_QN_RESP_NOT_OK)
    {
        qn_cb->resp_not_ok = NULL;
        qn_cb->resp_not_ok_ctx = NULL;
    }
    return 0;
}

#define EMAC_TRX_CLK_CFG_ADDR (0x97001000 + 0x104)

void rgmii_clk_init(void)
{
    uint32_t reg = readl(EMAC_TRX_CLK_CFG_ADDR);

    reg |= (1 << 6) | (1 << 27);    /* EMAC_TRX_CLK_CFG.emac_refclk_en = 1 enable emac_phy_refclk*/
    reg |= (1 << 9) | (1 << 30);    /* EMAC_TRX_CLK_CFG.emac_refclk_oen = 1  Reference Clock input enable*/

    reg |= (1 << 7) | (1 << 28);    /* EMAC host controller Tx Clock source selection in MII or RGMII mode. */
    reg |= (1 << 8) | (1 << 29);    /* EMAC_TRX_CLK_CFG.emac_txclk_sel = 0   using the Reference Clock in RMII mode*/
    writel(reg, EMAC_TRX_CLK_CFG_ADDR);
}

void rgmii_io_init(void)
{
    muxpin_set_function(35, FUNC_EMAC_MDC);
    muxpin_set_function(36, FUNC_EMAC_MDIO);

    muxpin_set_function(29, FUNC_EMAC_TX_CLK_OUT);
    muxpin_set_function(38, FUNC_EMAC_TX_CTL);
    muxpin_set_function(46, FUNC_EMAC_TX_D0);
    muxpin_set_function(45, FUNC_EMAC_TX_D1);
    muxpin_set_function(44, FUNC_EMAC_TX_D2);
    muxpin_set_function(43, FUNC_EMAC_TX_D3);

    muxpin_set_function(30, FUNC_EMAC_RX_CLK_IN);
    muxpin_set_function(37, FUNC_EMAC_RX_CTL);
    muxpin_set_function(42, FUNC_EMAC_RX_D0);
    muxpin_set_function(41, FUNC_EMAC_RX_D1);
    muxpin_set_function(40, FUNC_EMAC_RX_D2);
    muxpin_set_function(39, FUNC_EMAC_RX_D3);
}

void mii_clk_init(void)
{
    uint32_t reg = readl(EMAC_TRX_CLK_CFG_ADDR);

    reg |= (1 << 6) | (1 << 27);    /* EMAC_TRX_CLK_CFG.emac_refclk_en = 1 enable emac_phy_refclk*/
    reg |= (1 << 9) | (1 << 30);    /* EMAC_TRX_CLK_CFG.emac_refclk_oen = 1  Reference Clock input enable*/

    reg &= ~(1 << 7);
    reg |= (1 << 28);               /* EMAC host controller Tx Clock source selection in MII or RGMII mode. */

    reg |= (1 << 8) | (1 << 29);    /* EMAC_TRX_CLK_CFG.emac_txclk_sel = 0   using the Reference Clock in RMII mode*/
    writel(reg, EMAC_TRX_CLK_CFG_ADDR);
}

void mii_io_init(void)
{
    muxpin_set_function(35, FUNC_EMAC_MDC);
    muxpin_set_function(37, FUNC_EMAC_MDIO);

    muxpin_set_function(32, FUNC_EMAC_CRS);
    muxpin_set_function(31, FUNC_EMAC_COL);

    muxpin_set_function(29, FUNC_EMAC_TX_CLK_IN);
    muxpin_set_function(38, FUNC_EMAC_TX_EN);
    muxpin_set_function(46, FUNC_EMAC_TX_D0);
    muxpin_set_function(45, FUNC_EMAC_TX_D1);
    muxpin_set_function(44, FUNC_EMAC_TX_D2);
    muxpin_set_function(43, FUNC_EMAC_TX_D3);

    muxpin_set_function(30, FUNC_EMAC_RX_CLK_IN);
    muxpin_set_function(34, FUNC_EMAC_RX_ER);
    muxpin_set_function(37, FUNC_EMAC_RX_DV);
    muxpin_set_function(42, FUNC_EMAC_RX_D0);
    muxpin_set_function(41, FUNC_EMAC_RX_D1);
    muxpin_set_function(40, FUNC_EMAC_RX_D2);
    muxpin_set_function(39, FUNC_EMAC_RX_D3);
}

void rmii_io_init(void)
{
    muxpin_set_function(35, FUNC_EMAC_MDC);
    muxpin_set_function(36, FUNC_EMAC_MDIO);
    muxpin_set_function(34, FUNC_EMAC_RX_ER);
    muxpin_set_function(38, FUNC_EMAC_TX_EN);
    muxpin_set_function(32, FUNC_EMAC_CRS);
    muxpin_set_function(46, FUNC_EMAC_TX_D0);
    muxpin_set_function(45, FUNC_EMAC_TX_D1);
    muxpin_set_function(42, FUNC_EMAC_RX_D0);
    muxpin_set_function(41, FUNC_EMAC_RX_D1);
    muxpin_set_function(29, FUNC_EMAC_REF_IN);
#if defined(_EVBLP3) || defined(_EVBLP4)
    muxpin_set_function(31, FUNC_GPIO20);       /* rst use gpio20 */
    gpio_set_drive_mode(20, GPIO_DM_OUTPUT);
    gpio_set_pin(20, GPIO_PV_LOW);
    usleep(200);
    gpio_set_pin(20, GPIO_PV_HIGH);
#endif
}

/* Set rmii mode */
void rmii_input_ref_init(void)
{
    uint32_t reg = readl(EMAC_TRX_CLK_CFG_ADDR);
    reg |= (1 << 6) | (1 << 27);    /* EMAC_TRX_CLK_CFG.emac_refclk_en = 1 enable emac_phy_refclk*/
    reg |= (1 << 9) | (1 << 30);    /* EMAC_TRX_CLK_CFG.emac_refclk_oen = 1  Reference Clock input enable*/
    reg &= ~(1 << 8);
    reg |= 1 << 29;                 /* EMAC_TRX_CLK_CFG.emac_txclk_sel = 0   using the Reference Clock in RMII mode*/
    writel(reg, EMAC_TRX_CLK_CFG_ADDR);
}

void rmii_output_ref_init(void)
{
    uint32_t reg = readl(EMAC_TRX_CLK_CFG_ADDR);
    reg |= (1 << 6) | (1 << 27);    /* EMAC_TRX_CLK_CFG.emac_refclk_en = 1 enable emac_phy_refclk*/
    reg &= ~(1 << 9);
    reg |= 1 << 30;                 /* EMAC_TRX_CLK_CFG.emac_refclk_oen = 0  Reference Clock output enable*/
    reg &= ~(1 << 8);
    reg |= 1 << 29;                 /* EMAC_TRX_CLK_CFG.emac_txclk_sel = 0   using the Reference Clock in RMII mode*/
    writel(reg, EMAC_TRX_CLK_CFG_ADDR);
}

void rmii_io_out_init(void)
{
    muxpin_set_function(35, FUNC_EMAC_MDC);
    muxpin_set_function(36, FUNC_EMAC_MDIO);
    muxpin_set_function(34, FUNC_EMAC_RX_ER);
    muxpin_set_function(38, FUNC_EMAC_TX_EN);
    muxpin_set_function(32, FUNC_EMAC_CRS);
    muxpin_set_function(46, FUNC_EMAC_TX_D0);
    muxpin_set_function(45, FUNC_EMAC_TX_D1);
    muxpin_set_function(42, FUNC_EMAC_RX_D0);
    muxpin_set_function(41, FUNC_EMAC_RX_D1);
    muxpin_set_function(29, FUNC_EMAC_REF_OUT);

#if defined(_EVBLP3) || defined(_EVBLP4)
    muxpin_set_function(31, FUNC_GPIO20);       /* rst use gpio20 */
    gpio_set_drive_mode(20, GPIO_DM_OUTPUT);
    gpio_set_pin(20, GPIO_PV_LOW);
    usleep(200);
    gpio_set_pin(20, GPIO_PV_HIGH);
#endif
}

int emac_smi_is_done(void)
{
    uint32_t i = SMI_MDIO_BUS_TIMEOUT;
    while(--i)
    {
        if(emac->network_status & (0x1U << 2))
            break;
    }
    if(i == 0)
    {
        k510_logce("SDIO TIME OUT\n");
        return -1;
    }

    return 0;
}

void emac_smi_wait_done(void)
{
    while(!(emac->network_status & (0x1U << 2)));
}

int emac_smi_write(uint8_t phyaddr, uint8_t reg, uint16_t regval)
{
    emac->phy_management = (regval | (0x2U << 16) | (reg << 18) | (phyaddr << 23) | (0x1U << 28) | (0x1 << 30));
    return emac_smi_is_done();
}

int emac_smi_read(uint8_t phyaddr, uint8_t reg, uint16_t *regval)
{
    emac->phy_management = ((0x2U << 16) | (reg << 18) | (phyaddr << 23) | (0x2U << 28) | (0x1 << 30));
    if(emac_smi_is_done())
        return -1;
    *regval = emac->phy_management & 0xFFFF;
    return 0;
}

int emac_smi_clause45_write(uint8_t phyaddr, uint8_t reg, uint16_t regval)
{
    emac->phy_management = (regval | (0x2U << 16) | (reg << 18) | (phyaddr << 23) | (0x1U << 28));
    return emac_smi_is_done();
}

int emac_smi_clause45_read(uint8_t phyaddr, uint8_t reg, uint16_t *regval)
{
    emac->phy_management = ((0x2U << 16) | (reg << 18) | (phyaddr << 23) | (0x2U << 28));
    if(emac_smi_is_done())
        return -1;
    *regval = emac->phy_management & 0xFFFF;
    return 0;
}

void emac_set_rx_buf_size(uint32_t size, emac_queue_number_t qnum)
{
    // assert(qnum < EMAC_QUEUE_NUMBER_MAX && qnum >= EMAC_QUEUE_NUMBER0);

    switch(qnum)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->dma_config = ((emac->dma_config & ~(EMAC_RX_BUF_SIZE_MASK << EMAC_RX_BUF_SIZE_OFFSET))    \
                                | ((size >> 6) << EMAC_RX_BUF_SIZE_OFFSET));
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->dma_rxbuf_size_q1 = (emac->dma_rxbuf_size_q1 & ~0xFFU) | ((size >> 6) & 0xFF);
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->dma_rxbuf_size_q2 = (emac->dma_rxbuf_size_q2 & ~0xFFU) | ((size >> 6) & 0xFF);
            break;
    }
}

uint32_t emac_get_rx_buf_size(emac_queue_number_t qnum)
{
    // assert(qnum < EMAC_QUEUE_NUMBER_MAX && qnum >= EMAC_QUEUE_NUMBER0);
    switch(qnum)
    {
        case EMAC_QUEUE_NUMBER0:
            return ((emac->dma_config >> EMAC_RX_BUF_SIZE_OFFSET) & EMAC_RX_BUF_SIZE_MASK) << 6;
            break;
        case EMAC_QUEUE_NUMBER1:
            return (emac->dma_rxbuf_size_q1 & 0xFF) << 6;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            return (emac->dma_rxbuf_size_q2 & 0xFF) << 6;
            break;
    }
}

void emac_set_speed(emac_ifspeed_t speed)
{
    uint32_t reg = emac->network_config;
    switch(speed)
    {
        case EMAC_IFSPEED_10M:
            reg &= ~EMAC_SPEED_100M;
            reg &= ~EMAC_GIGABIT_MODE;
        break;
        case EMAC_IFSPEED_100M:
            reg |= EMAC_SPEED_100M;
            reg &= ~EMAC_GIGABIT_MODE;
        break;
        case EMAC_IFSPEED_1000M:
        default:
            reg |= EMAC_GIGABIT_MODE;
        break;
    }
    emac->network_config = reg;
}

void emac_read_stats()
{
        emac_stats_t stats;
        stats.octetsTxLo = ((emac->octets_txed_bottom));
        stats.octetsTxHi = (uint16_t) EMAC_REGS__OCTETS_TXED_TOP__COUNT__READ(
                             ((emac->octets_txed_top)));
        stats.framesTx = ((emac->frames_txed_ok));
        stats.broadcastTx = ((emac->broadcast_txed));
        stats.multicastTx = ((emac->multicast_txed));
        stats.pauseFrTx = (uint16_t)EMAC_REGS__PAUSE_FRAMES_TXED__COUNT__READ(
                            ((emac->pause_frames_txed)));
        stats.fr64byteTx = ((emac->frames_txed_64));
        stats.fr65_127byteTx = ((emac->frames_txed_65));
        stats.fr128_255byteTx = ((emac->frames_txed_128));
        stats.fr256_511byteTx = ((emac->frames_txed_256));
        stats.fr512_1023byteTx = ((emac->frames_txed_512));
        stats.fr1024_1518byteTx =
                                ((emac->frames_txed_1024));
        stats.fr1519_byteTx = ((emac->frames_txed_1519));
            stats.underrunFrTx = (uint16_t)EMAC_REGS__TX_UNDERRUNS__COUNT__READ(
                                ((emac->tx_underruns)));
        stats.singleCollFrTx =
                            ((emac->single_collisions));
        stats.multiCollFrTx =
                            ((emac->multiple_collisions));
        stats.excessCollFrTx = (uint16_t)EMAC_REGS__EXCESSIVE_COLLISIONS__COUNT__READ(
                           ((emac->excessive_collisions)));
        stats.lateCollFrTx = (uint16_t)EMAC_REGS__LATE_COLLISIONS__COUNT__READ(
                                ((emac->late_collisions)));
        stats.carrSensErrsTx = (uint16_t)EMAC_REGS__CRS_ERRORS__COUNT__READ(
                                  ((emac->crs_errors)));
        stats.deferredFrTx = ((emac->deferred_frames));
        stats.alignErrsRx = (uint16_t)EMAC_REGS__ALIGNMENT_ERRORS__COUNT__READ(
                            ((emac->alignment_errors)));
            stats.octetsRxLo = ((emac->octets_rxed_bottom));
        stats.octetsRxHi = (uint16_t)EMAC_REGS__OCTETS_RXED_TOP__COUNT__READ(
                              ((emac->octets_rxed_top)));
        stats.framesRx = ((emac->frames_rxed_ok));
        stats.broadcastRx = ((emac->broadcast_rxed));
        stats.multicastRx = ((emac->multicast_rxed));
        stats.pauseFrRx = (uint16_t)EMAC_REGS__PAUSE_FRAMES_RXED__COUNT__READ(
                            ((emac->pause_frames_rxed)));
        stats.fr64byteRx = ((emac->frames_rxed_64));
        stats.fr65_127byteRx = ((emac->frames_rxed_65));
        stats.fr128_255byteRx = ((emac->frames_rxed_128));
        stats.fr256_511byteRx = ((emac->frames_rxed_256));
        stats.fr512_1023byteRx =
                                ((emac->frames_rxed_512));
        stats.fr1024_1518byteRx =
                                ((emac->frames_rxed_1024));
        stats.fr1519_byteRx =
                                ((emac->frames_rxed_1519));
        stats.undersizeFrRx = (uint16_t)EMAC_REGS__UNDERSIZE_FRAMES__COUNT__READ(
                              ((emac->undersize_frames)));
        stats.oversizeFrRx = (uint16_t)EMAC_REGS__EXCESSIVE_RX_LENGTH__COUNT__READ(
                        ((emac->excessive_rx_length)));
        stats.jabbersRx = (uint16_t)EMAC_REGS__RX_JABBERS__COUNT__READ(
                                ((emac->rx_jabbers)));
        stats.fcsErrorsRx = (uint16_t)EMAC_REGS__FCS_ERRORS__COUNT__READ(
                                ((emac->fcs_errors)));
        stats.lenChkErrRx = (uint16_t)EMAC_REGS__RX_LENGTH_ERRORS__COUNT__READ(
                              ((emac->rx_length_errors)));
        stats.rxSymbolErrs = (uint16_t)EMAC_REGS__RX_SYMBOL_ERRORS__COUNT__READ(
                            ((emac->rx_symbol_errors)));
        stats.rxResourcErrs =
                            ((emac->rx_resource_errors));
        stats.overrunFrRx = (uint16_t)EMAC_REGS__RX_OVERRUNS__COUNT__READ(
                                ((emac->rx_overruns)));
        stats.ipChksumErrs = (uint16_t)EMAC_REGS__RX_IP_CK_ERRORS__COUNT__READ(
                            ((emac->rx_ip_ck_errors)));
        stats.tcpChksumErrs = (uint16_t)EMAC_REGS__RX_TCP_CK_ERRORS__COUNT__READ(
                            ((emac->rx_tcp_ck_errors)));
        stats.udpChksumErrs = (uint16_t)EMAC_REGS__RX_UDP_CK_ERRORS__COUNT__READ(
                            ((emac->rx_udp_ck_errors)));
        stats.dmaRxPBufFlush = (uint16_t)EMAC_REGS__AUTO_FLUSHED_PKTS__COUNT__READ(
                            ((emac->auto_flushed_pkts)));

            k510_logci("\nStatistics regs copy (MAC%u)-\n" \
                "          octetsTx:  0x%08X %08X\n" \
                "          framesTx:%3u        broadcastTx:%u         multicastTx:%u           pauseFrTx:%u  \n" \
                "        fr64byteTx:%u       fr65_127byteTx:%u     fr128_255byteTx:%u     fr256_511byteTx:%u\n" \
                "  fr512_1023byteTx:%u    fr1024_1518byteTx:%u       fr1519_byteTx:%u        underrunFrTx:%u\n" \
                "    singleCollFrTx:%u        multiCollFrTx:%u      excessCollFrTx:%u        lateCollFrTx:%u\n" \
                "      deferredFrTx:%u       carrSensErrsTx:%u\n" \
                "          octetsRx:  0x%08X %08X\n" \
                "          framesRx:%3u        broadcastRx:%u         multicastRx:%u           pauseFrRx:%u  \n" \
                "        fr64byteRx:%u       fr65_127byteRx:%u     fr128_255byteRx:%u     fr256_511byteRx:%u\n" \
                "  fr512_1023byteRx:%u    fr1024_1518byteRx:%u       fr1519_byteRx:%u       undersizeFrRx:%u\n" \
                "      oversizeFrRx:%u            jabbersRx:%u         fcsErrorsRx:%u         lenChkErrRx:%u\n" \
                "      rxSymbolErrs:%u          alignErrsRx:%u       rxResourcErrs:%u         overrunFrRx:%u\n" \
                "      ipChksumErrs:%u        tcpChksumErrs:%u       udpChksumErrs:%u      dmaRxPBufFlush:%u\n",
                0,
                stats.octetsTxHi,
                stats.octetsTxLo,
                stats.framesTx,
                stats.broadcastTx,
                stats.multicastTx,
                stats.pauseFrTx,
                stats.fr64byteTx,
                stats.fr65_127byteTx,
                stats.fr128_255byteTx,
                stats.fr256_511byteTx,
                stats.fr512_1023byteTx,
                stats.fr1024_1518byteTx,
                stats.fr1519_byteTx,
                stats.underrunFrTx,
                stats.singleCollFrTx,
                stats.multiCollFrTx,
                stats.excessCollFrTx,
                stats.lateCollFrTx,
                stats.deferredFrTx,
                stats.carrSensErrsTx,
                stats.octetsRxHi,
                stats.octetsRxLo,
                stats.framesRx,
                stats.broadcastRx,
                stats.multicastRx,
                stats.pauseFrRx,
                stats.fr64byteRx,
                stats.fr65_127byteRx,
                stats.fr128_255byteRx,
                stats.fr256_511byteRx,
                stats.fr512_1023byteRx,
                stats.fr1024_1518byteRx,
                stats.fr1519_byteRx,
                stats.undersizeFrRx,
                stats.oversizeFrRx,
                stats.jabbersRx,
                stats.fcsErrorsRx,
                stats.lenChkErrRx,
                stats.rxSymbolErrs,
                stats.alignErrsRx,
                stats.rxResourcErrs,
                stats.overrunFrRx,
                stats.ipChksumErrs,
                stats.tcpChksumErrs,
                stats.udpChksumErrs,
                stats.dmaRxPBufFlush );
}

void emac_tx_bd_info(emac_bd_t *tx_list, uint32_t tx_bd_num)
{
    k510_logci("---  Tx Descriptor List Queue  --- txlist %p\n", tx_list);
    for(uint32_t i = 0; i < tx_bd_num; i++)
    {
        k510_logi("d%3u   w0:%08X    wd1:%08X    u:%u w:%u l:%u tsV:%u len:%4u\n",
                    i,
                    tx_list[i].word0,
                    tx_list[i].word1,
                    (tx_list[i].word1 & EMAC_TXD_USED) ? 1 : 0,
                    (tx_list[i].word1 & EMAC_TXD_WRAP) ? 1 : 0,
                    (tx_list[i].word1 & EMAC_TXD_LAST_BUF) ? 1 : 0,
                    (tx_list[i].word1 & EMAC_TXD_TS_VALID) ? 1 : 0,
                    tx_list[i].word1 & EMAC_TXD_LMASK
        );
    }
}

void emac_rx_bd_info(emac_bd_t *rx_list, uint32_t tx_bd_num)
{
    uint32_t len;
    k510_logci("\n---  Rx Descriptor List Queue 0  ---  rxlist %p\n", rx_list);
    for(uint32_t i = 0; i < tx_bd_num; i++)
    {
        len = rx_list[i].word1 & EMAC_RXD_LEN_MASK;
        k510_logci("d%3u   w0:%08X    wd1:%08X    u:%u w:%u s:%u e:%u  add:%08X tsv:%u len:%4u\n",
                    i,
                    rx_list[i].word0,
                    rx_list[i].word1,
                    (rx_list[i].word0 & EMAC_RXD_USED) ? 1 : 0, (rx_list[i].word0 & EMAC_RXD_WRAP) ? 1 : 0,
                    (rx_list[i].word1 & EMAC_RXD_SOF) ? 1 : 0, (rx_list[i].word1 & EMAC_RXD_EOF) ? 1 : 0,
                    rx_list[i].word0 & EMAC_RXD_ADDR_MASK,(rx_list[i].word0 & EMAC_RXD_TS_VALID) ? 1 : 0,
                    len
        );
    }
}

/* Initialise Network Control register from config struct */
void emac_init_netcontrol(emac_config_t *config)
{
    uint32_t regVal = 0U;

    if(0U != config->loopBack)
    {
        EMAC_REGS__EMAC_NETWORK_CONTROL__LOOPBACK_LOCAL__SET(regVal);
    }

    if(config->ifTypeSel == EMAC_IFSP_MII)
    {
        EMAC_REGS__NETWORK_CONTROL__SEL_MII_ON_RGMII__SET(regVal);
    }

    if (0U != config->enableMdio) {
        EMAC_REGS__NETWORK_CONTROL__MAN_PORT_EN__SET(regVal);
    }

    if (0U != config->storeUdpTcpOffset) {
        EMAC_REGS__NETWORK_CONTROL__STORE_UDP_OFFSET__SET(regVal);
    }

    /* pfc multi quantum functionality */
    if(0U != config->pfcMultiQuantum) {
        EMAC_REGS__NETWORK_CONTROL__PFC_CTRL__SET(regVal);
    }

    /* clear stats */
    EMAC_REGS__NETWORK_CONTROL__CLEAR_ALL_STATS_REGS__SET(regVal);

    emac->network_control = regVal;

}

/* Initialise Network Config register from config struct */
void emac_init_netconfig(emac_config_t *config)
{
    uint32_t regVal = 0U;

    if(0U != config->copyAllFrame)
    {
        EMAC_REGS__NETWORK_CONFIG__COPY_ALL_FRAMES__SET(regVal);
    }

    if(0U != config->ignoreRxFcs)
    {
        EMAC_REGS__NETWORK_CONFIG__IGNORE_RX_FCS__SET(regVal);
    }

    if (config->ifSpeedSel == EMAC_IFSPEED_100M)
    {
        EMAC_REGS__NETWORK_CONFIG__SPEED__SET(regVal);
    }
    else if (config->ifSpeedSel == EMAC_IFSPEED_1000M)
    {
        EMAC_REGS__NETWORK_CONFIG__GIGABIT_MODE_ENABLE__SET(regVal);
    }

    if (0U != config->uniDirEnable) {
        EMAC_REGS__NETWORK_CONFIG__UNI_DIRECTION_ENABLE__SET(regVal);
    }

    if (0U != config->enRxBadPreamble) {
        EMAC_REGS__NETWORK_CONFIG__NSP_ACCEPT__SET(regVal);
    }

    if (0U != config->fullDuplex) {
        EMAC_REGS__NETWORK_CONFIG__FULL_DUPLEX__SET(regVal);
    }

    if (0U != config->enRxHalfDupTx) {
        EMAC_REGS__NETWORK_CONFIG__EN_HALF_DUPLEX_RX__SET(regVal);
    }

    if (0U != config->ignoreIpgRxEr) {
        EMAC_REGS__NETWORK_CONFIG__IGNORE_IPG_RX_ER__SET(regVal);
    }

    if (0U != config->rx1536ByteEn) {
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_1536_BYTE_FRAMES__SET(regVal);
    }

    EMAC_REGS__NETWORK_CONFIG__RECEIVE_BUFFER_OFFSET__MODIFY(regVal, config->rxBufOffset);

    if (0U != config->rxLenErrDisc) {
        EMAC_REGS__NETWORK_CONFIG__LENGTH_FIELD_ERROR_FRAME_DISCARD__SET(regVal);
    }

    EMAC_REGS__NETWORK_CONFIG__MDC_CLOCK_DIVISION__MODIFY(regVal, config->mdcPclkDiv);

    EMAC_REGS__NETWORK_CONFIG__DATA_BUS_WIDTH__MODIFY(regVal, 1);   // should be 1 to 64bit

    if (0U != config->disCopyPause) {
        EMAC_REGS__NETWORK_CONFIG__DISABLE_COPY_OF_PAUSE_FRAMES__SET(regVal);
    }

    if (0U != (config->chkSumOffEn & EMAC_CFG_CHK_OFF_RX)) {
        EMAC_REGS__NETWORK_CONFIG__RECEIVE_CHECKSUM_OFFLOAD_ENABLE__SET(regVal);
    }

    emac->network_config = regVal;
}

/* Initialise DMA Config register from config struct */
void emac_init_dmaconfig(emac_config_t *config)
{
    uint32_t regTmp = 0U;

    EMAC_REGS__DMA_CONFIG__RX_PBUF_SIZE__MODIFY(regTmp, 0x3U);
    EMAC_REGS__DMA_CONFIG__TX_PBUF_SIZE__MODIFY(regTmp, 0x1U);
    // convert enums to uint32_t (enum values are as defined in dma_config register)
    EMAC_REGS__DMA_CONFIG__AMBA_BURST_LENGTH__MODIFY(regTmp, (uint32_t) (config->dmaDataBurstLen));

    if (0U != (config->dmaEndianism & (uint8_t)EMAC_END_SWAP_DESC)) {
        EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_MANAGEMENT__SET(regTmp);
    }
    if (0U != (config->dmaEndianism & (uint8_t)EMAC_END_SWAP_DATA)) {
        EMAC_REGS__DMA_CONFIG__ENDIAN_SWAP_PACKET__SET(regTmp);
    }

    if (0U != (config->chkSumOffEn & (uint8_t)EMAC_CFG_CHK_OFF_TX)) {
        EMAC_REGS__DMA_CONFIG__TX_PBUF_TCP_EN__SET(regTmp);
    }

    if (0U != (config->dmaCfgFlags & (uint8_t)EMAC_CFG_DMA_DISC_RXP)) {
        EMAC_REGS__DMA_CONFIG__FORCE_DISCARD_ON_ERR__SET(regTmp);
    }

    if (0U != (config->dmaCfgFlags & (uint8_t)EMAC_CFG_DMA_FRCE_RX_BRST)) {
        EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_RX__SET(regTmp);
    }

    if (0U != (config->dmaCfgFlags & (uint8_t)EMAC_CFG_DMA_FRCE_TX_BRST)) {
        EMAC_REGS__DMA_CONFIG__FORCE_MAX_AMBA_BURST_TX__SET(regTmp);
    }

    EMAC_REGS__DMA_CONFIG__RX_BUF_SIZE__MODIFY(regTmp, 2);

    emac->dma_config = regTmp;
}

static void emac_general_interrupt_init(uint32_t priority)
{
    plic_set_priority(IRQN_EMAC_INTERRUPT, priority);
    plic_irq_register(IRQN_EMAC_INTERRUPT, emac_general_callback_func, NULL);
    plic_irq_enable(IRQN_EMAC_INTERRUPT);
}

static void emac_qn_interrupt_init(emac_queue_number_t qnum,  uint32_t priority)
{
    emac_qn_callback[qnum - 1].qnum = qnum;

    plic_set_priority(IRQN_EMAC_INTERRUPT + qnum, priority);
    plic_irq_register(IRQN_EMAC_INTERRUPT + qnum, emac_gn_callback_func, &emac_qn_callback[qnum - 1]);
    plic_irq_enable(IRQN_EMAC_INTERRUPT + qnum);
}

void emac_init(emac_config_t *config)
{
    emac_init_netcontrol(config);
    emac_init_netconfig(config);
    emac_init_dmaconfig(config);
    emac_disable_specaddr();
    emac_disable_all_queue();
    emac_general_interrupt_disable_all();
    emac_q1_interrupt_disable_all();
    emac_q2_interrupt_disable_all();
    emac_general_interrupt_clear_all();
    emac_q1_interrupt_clear_all();
    emac_q2_interrupt_clear_all();
}

void emac_interrupt_init(uint32_t q0_priority, uint32_t q1_priority, uint32_t q2_priority)
{
    plic_interrupt_enable();
    emac_general_interrupt_init(q0_priority);
    emac_qn_interrupt_init(EMAC_QUEUE_NUMBER1, q1_priority);
    emac_qn_interrupt_init(EMAC_QUEUE_NUMBER2, q2_priority);
}

void emac_interrupt_set_priority(emac_queue_number_t qnum, uint32_t priority)
{
    plic_set_priority(IRQN_EMAC_INTERRUPT + qnum, priority);
}

void emac_interrupt_disable(emac_queue_number_t qnum)
{
    plic_irq_unregister(IRQN_EMAC_INTERRUPT + qnum);
    plic_irq_disable(IRQN_EMAC_INTERRUPT + qnum);
}

void emac_get_txstatus(emac_txstatus_t *txStatus)
{
    uint32_t reg;
    reg = emac->transmit_status;

    txStatus->txComplete =
            EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_COMPLETE__READ(reg);
    txStatus->usedBitRead =
            EMAC_REGS__TRANSMIT_STATUS__USED_BIT_READ__READ(reg);
    txStatus->collisionOcc =
            EMAC_REGS__TRANSMIT_STATUS__COLLISION_OCCURRED__READ(reg);
    txStatus->retryLimExc =
            EMAC_REGS__TRANSMIT_STATUS__RETRY_LIMIT_EXCEEDED__READ(reg);
    txStatus->lateCollision =
            EMAC_REGS__TRANSMIT_STATUS__LATE_COLLISION_OCCURRED__READ(reg);
    txStatus->txActive =
            EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_GO__READ(reg);
    txStatus->txFrameErr =
            EMAC_REGS__TRANSMIT_STATUS__AMBA_ERROR__READ(reg);
    txStatus->txUnderRun =
            EMAC_REGS__TRANSMIT_STATUS__TRANSMIT_UNDER_RUN__READ(reg);
    txStatus->hRespNotOk =
            EMAC_REGS__TRANSMIT_STATUS__RESP_NOT_OK__READ(reg);

}

void emac_print_txstatus(void)
{
    emac_txstatus_t txStatus;
    emac_get_txstatus(&txStatus);

    k510_logci("MAC TxStatus: %s %s %s %s %s %s %s %s %s\n",
                txStatus.txComplete ? "txFrComplete" : "",
                txStatus.usedBitRead ? "usedRead" : "",
                txStatus.collisionOcc ? "collision" : "",
                txStatus.retryLimExc ? "retryExceeded" : "",
                txStatus.txActive ? "txActive" : "",
                txStatus.txFrameErr ? "frameErr" : "",
                txStatus.txUnderRun ? "txUnderrun" : "",
                txStatus.lateCollision ? "lateColl" : "",
                txStatus.hRespNotOk ? "HrespNotOk" : "");
}

/**
 * timeout      0:block
 */
int emac_tx_wait_done(uint32_t timeout)
{
    if(timeout == 0)
    {
        while(!emac_transmit_is_complete());
    }
    else
    {
        while(--timeout)
        {
            if(emac_transmit_is_complete())
                break;
        }
        if(timeout == 0)
        {
            k510_logce("Transmit time out\n");
            return -1;
        }
    }
    emac_clear_transmit_complete();
    return 0;
}

int emac_rx_wait_done(uint32_t timeout)
{
    if(timeout == 0)
    {
        while(!emac_frame_is_received());
    }
    else
    {
        while(--timeout)
        {
            if(emac_frame_is_received())
                break;
        }
        if(timeout == 0)
        {
            k510_logce("Receive time out\n");
            return -1;
        }
    }
    emac_clear_frame_received();
    return 0;
}

void emac_stop(void)
{
    emac_tx_halt();
    for(uint32_t i = 10000; (i && emac_transmit_going()); i--);
    emac_tx_disable();
    emac_rx_disable();
    emac_disable_all_interrupt();
}

void emac_print_txtsdesclist(emac_txtsqueue_t *txqueue)
{
    if(txqueue->descMax == 0)
        return;

    k510_logce("---  Tx Descriptor List Queue %d ---txlist %p\n", txqueue->qNumber, txqueue->bdBase);

    emac_bd_timestamp_t *bd = txqueue->bdBase;

    for (uint32_t i = 0; i < txqueue->descMax; i++) {

        k510_logi("d%3u ",i);

        k510_logi("wd0:%08X  ", bd->word0);
        k510_logi("wd1:%08X  ", bd->word1);
        k510_logi("wd2:%08X  ", bd->word2);
        k510_logi("wd3:%08X  ", bd->word3);

        k510_logi("u:%u w:%u l:%u tsV:%u len:%4u %s%s\n",
                    (bd->word1 & EMAC_TXD_USED) ? 1 : 0,
                    (bd->word1 & EMAC_TXD_WRAP) ? 1 : 0,
                    (bd->word1 & EMAC_TXD_LAST_BUF) ? 1 : 0,
                    (bd->word1 & EMAC_TXD_TS_VALID) ? 1 : 0,
                    bd->word1 & EMAC_TXD_LMASK,
                    (bd == txqueue->bdTail) ? "<--tail" : "",
                    (bd == txqueue->bdHead) ? "<--head" : "");

        bd++;
    }

    k510_logi("\n");
}

void emac_print_txdesclist(emac_txqueue_t *txqueue)
{
    if(txqueue->descMax == 0)
        return;

    k510_logci("---  Tx Descriptor List Queue %d ---txlist %p\n", txqueue->qNumber, txqueue->bdBase);

    emac_bd_t *bd = txqueue->bdBase;

    for (uint32_t i = 0; i < txqueue->descMax; i++) {

        k510_logi("d%3u ",i);

        k510_logi("wd0:%08X  ", bd->word0);
        k510_logi("wd1:%08X  ", bd->word1);

        k510_logi("u:%u w:%u l:%u tsV:%u len:%4u %s%s\n",
                    (bd->word1 & EMAC_TXD_USED) ? 1 : 0,
                    (bd->word1 & EMAC_TXD_WRAP) ? 1 : 0,
                    (bd->word1 & EMAC_TXD_LAST_BUF) ? 1 : 0,
                    (bd->word1 & EMAC_TXD_TS_VALID) ? 1 : 0,
                    bd->word1 & EMAC_TXD_LMASK,
                    (bd == txqueue->bdTail) ? "<--tail" : "",
                    (bd == txqueue->bdHead) ? "<--head" : "");

        bd++;
    }

    k510_logi("\n");
}

void emac_print_global_txdesclist(void)
{
    for(uint32_t i = 0; i < EMAC_QUEUE_NUMBER_MAX; i++)
    {
        emac_print_txdesclist(&tx_queue[i]);
    }
}

int emac_txtsqueue_set_send_data(emac_txtsqueue_t *txqueue, uint8_t *data, uint32_t length, uint32_t flags)
{
    if(txqueue->descFree == 0)
    {
        k510_logce("There are not not enough space to send data\n");
        return -1;
    }
    emac_bd_timestamp_t *bd = txqueue->bdHead;
    bd->word0 = (uintptr_t)data;
    bd->word1 |= ((0 != (flags & EMAC_TXB_LAST_BUFF))?EMAC_TXD_LAST_BUF:0)
                | ((0 != (flags & EMAC_TXB_NO_AUTO_CRC))?EMAC_TXD_NO_AUTO_CRC:0)
                | length;
    bd->word1 &= ~EMAC_TXBD_USED_BIT;

    txqueue->descFree--;
    txqueue->descUsed++;

    if(bd->word1 & EMAC_TXD_WRAP)
    {
        txqueue->bdHead = txqueue->bdBase;
    }
    else
    {
        txqueue->bdHead++;
    }

    if(txqueue->bdTail == NULL)
    {
        txqueue->bdTail = txqueue->bdBase;
    }

    return 0;
}

int emac_txqueue_set_send_data(emac_txqueue_t *txqueue, uint8_t *data, uint32_t length, uint32_t flags)
{
    if(txqueue->descFree == 0)
    {
        k510_logce("There are not not enough space to send data\n");
        return -1;
    }
    emac_bd_t *bd = txqueue->bdHead;
    bd->word0 = (uintptr_t)data;
    bd->word1 |= ((0 != (flags & EMAC_TXB_LAST_BUFF))?EMAC_TXD_LAST_BUF:0)
                | ((0 != (flags & EMAC_TXB_NO_AUTO_CRC))?EMAC_TXD_NO_AUTO_CRC:0)
                | length;
    bd->word1 &= ~EMAC_TXBD_USED_BIT;

    txqueue->descFree--;
    txqueue->descUsed++;

    if(bd->word1 & EMAC_TXD_WRAP)
    {
        txqueue->bdHead = txqueue->bdBase;
    }
    else
    {
        txqueue->bdHead++;
    }

    if(txqueue->bdTail == NULL)
    {
        txqueue->bdTail = txqueue->bdBase;
    }

    return 0;
}

int emac_txqueue_free_data(emac_txqueue_t *txqueue)
{
    if(txqueue->descUsed == 0)
    {
        k510_logce("There are no send data\n");
        return -1;
    }
    emac_bd_t *bd = txqueue->bdTail;
    bd->word0 = 0x0U;
    if(bd->word1 & EMAC_TXD_WRAP)
    {
        bd->word1 = EMAC_TXD_USED | EMAC_TXD_WRAP;
        txqueue->bdTail = txqueue->bdBase;
    }
    else
    {
        bd->word1 = EMAC_TXD_USED;
        txqueue->bdTail++;
    }

    txqueue->descFree++;
    txqueue->descUsed--;

    return 0;
}

void emac_txqueue_timestamp_init(emac_txtsqueue_t *txqueue, emac_bd_timestamp_t *list, uint32_t bd_number, emac_queue_number_t qnumber)
{
    *txqueue = (emac_txtsqueue_t){
        .bdBase = list,
        .bdHead = list,
        .bdTail = NULL,
        .descMax = bd_number,
        .descFree = bd_number,
        .descUsed = 0,
        .qNumber = qnumber,
    };

    memset(list, 0, sizeof(emac_bd_timestamp_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word1 |= EMAC_TXBD_USED_BIT /*| EMAC_TXD_TS_VALID*/;    /* Set used bit */
    }
    list[bd_number -1].word1 |= EMAC_TXBD_WRAP_BIT;   /* Last bd set wrap bit */

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->transmit_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->transmit_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->transmit_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

void emac_txqueue_init(emac_txqueue_t *txqueue, emac_bd_t *list, uint32_t bd_number, emac_queue_number_t qnumber)
{
    *txqueue = (emac_txqueue_t){
        .bdBase = list,
        .bdHead = list,
        .bdTail = NULL,
        .descMax = bd_number,
        .descFree = bd_number,
        .descUsed = 0,
        .qNumber = qnumber,
    };

    memset(list, 0, sizeof(emac_bd_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word1 |= EMAC_TXBD_USED_BIT;    /* Set used bit */
    }
    list[bd_number -1].word1 |= EMAC_TXBD_WRAP_BIT;   /* Last bd set wrap bit */

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->transmit_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->transmit_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->transmit_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

void emac_txqueue_global_init(emac_bd_t *list, uint32_t bd_number, emac_queue_number_t qnumber)
{
    tx_queue[qnumber] = (emac_txqueue_t){
        .bdBase = list,
        .bdHead = list,
        .bdTail = NULL,
        .descMax = bd_number,
        .descFree = bd_number,
        .descUsed = 0,
        .qNumber = qnumber,
    };

    memset(list, 0, sizeof(emac_bd_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word1 |= EMAC_TXBD_USED_BIT;    /* Set used bit */
    }
    list[bd_number -1].word1 |= EMAC_TXBD_WRAP_BIT;   /* Last bd set wrap bit */

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->transmit_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->transmit_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->transmit_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

static void emac_rxqueue_tail_sync(emac_rxqueue_t *rxqueue)
{
    emac_bd_t *bd = rxqueue->bdTail;
    for(uint32_t i = 0; i < rxqueue->descMax; i++)
    {
        if(bd->word0 & EMAC_RXD_USED)   /* tail指向接收缓存 */
        {
            if(bd->word0 & EMAC_RXD_WRAP)   /* 遇到wrap位循环 */
                bd = rxqueue->bdBase;
            else
                bd++;
            rxqueue->bdTail = bd;
            if(rxqueue->bdTail == rxqueue->bdHead)  /* head == tail 说明接收缓存已满，此时tail也指向used位BD */
                break;
        }
        else
            break;
    }
}

static uint32_t emac_rxqueue_get_used_bdnumber(emac_rxqueue_t *rxqueue)
{
    uint32_t count = 0;
    emac_bd_t *bd = rxqueue->bdBase;
    for(uint32_t i = 0; i < rxqueue->descMax; i++)
    {
        if(bd->word0 & EMAC_RXD_USED)   /* 只要used位置1 则有数据 */
            count++;
        bd++;
    }
    return count;
}


#define emac_head_plus_one(bd)              if(bd->word0 & EMAC_RXD_WRAP)     \
                                                bd = rxqueue->bdBase;         \
                                            else                                \
                                                bd++;

#define emac_rx_clear_invalid_data()        do{                                 \
                                                head->word0 &= ~EMAC_RXD_USED;  \
                                                head->word1 = 0;                \
                                                emac_head_plus_one(head);           \
                                            }while(head != judge);

/**
 * Get a frame from receive buf
 */
int emac_rxqueue_get_frame(emac_rxqueue_t *rxqueue, uint8_t *rxbuf, uint32_t rx_len)
{
    rxqueue->buflength = emac_get_rx_buf_size(rxqueue->qNumber);
    uint8_t head_data_flag = emac_get_head_data_split();
    if(rx_len < 64)
    {
        k510_logci("WARNING: The frame length must larger than 64\n");
    }

    if(emac_rxqueue_get_used_bdnumber(rxqueue) == 0) /* 确定接收缓存里有数据 */
    {
        k510_logce("There are no received data\n");
        return 0;
    }
    emac_rxqueue_tail_sync(rxqueue);    /* 同步tail */

    /* 确保head指向的BD,used已经置位 */
    emac_bd_t *head = rxqueue->bdHead;
    if((head->word0 & EMAC_RXD_USED) == 0)
    {
        k510_logce("RxQueue head ERR\n");
        return -1;
    }

    /* 确保head指向的BD,SOF已经置位 */
    for(uint32_t i = 0; i < rxqueue->descMax; i++)
    {
        if(head->word1 & EMAC_RXD_SOF)
            break;

        // head->word0 &= ~EMAC_RXD_USED;
        // head->word1 = 0;
        // if(head->word0 & EMAC_RXD_WRAP)
        //     head = rxqueue->bdBase;
        // else
        //     head++;
        emac_head_plus_one(head);

        if(head == rxqueue->bdTail)
        {
            k510_logce("RxBD head is not SOF\n");
            rxqueue->bdHead = head;
            return -1;
        }
    }

    /* SOF 和 EOF之间，不存SOF，并且SOF和EOF之间的缓存的数据和要小于EOF BD显示的长度 */
    if(!(head->word1 & EMAC_RXD_EOF))
    {
        uint32_t frame_len_total;

        if(head_data_flag && (head->word1 & EMAC_RXD_EOH))      /* 如果head data split word1 len is head length */
        {
            k510_logci("Header/Data split EOH\n");
            frame_len_total = (head->word1 & EMAC_RXD_LEN_MASK) % (rxqueue->buflength);
        }
        else
        {
            frame_len_total = rxqueue->buflength;
        }

        emac_bd_t *judge = head;
        emac_head_plus_one(judge);

        for(uint32_t i = 0; i < rxqueue->descMax; i++)
        {
            if(judge == rxqueue->bdTail)
            {
                k510_logce("RxBD no EOF\n");
                // do{
                //     head->word0 &= ~EMAC_RXD_USED;
                //     head->word1 = 0;
                // }while(++head != judge);
                emac_rx_clear_invalid_data();
                rxqueue->bdHead = head;
                return -1;
            }
            if(judge->word1 & EMAC_RXD_EOF)
            {
                if(frame_len_total > (judge->word1 & EMAC_RXD_LEN_MASK)) // EOF-SOF > frame length ERR
                {
                    k510_logce("Frame length ERR\n");
                    // do{
                    //     head->word0 &= ~EMAC_RXD_USED;
                    //     head->word1 = 0;
                    // }while(++head != judge);
                    emac_rx_clear_invalid_data();
                    rxqueue->bdHead = head;
                    return -1;
                }

                if((judge->word1 & EMAC_RXD_LEN_MASK) > rx_len)
                {
                    k510_logce("Frame length > rxbuf lenth\n");
                    return -1;
                }
                break;
            }
            else if(judge->word1 & EMAC_RXD_SOF)
            {
                if(head_data_flag && (judge->word1 & EMAC_RXD_EOH))      /* 如果head data split word1 len is head length */
                {
                    k510_logci("Header/Data split EOH\n");
                    frame_len_total = (judge->word1 & EMAC_RXD_LEN_MASK) % (rxqueue->buflength);
                }
                else
                {
                    frame_len_total = rxqueue->buflength;
                }
                // frame_len_total = 0;
                // do{
                //     head->word0 &= ~EMAC_RXD_USED;
                //     head->word1 = 0;
                // }while(++head != judge);
                emac_rx_clear_invalid_data();
            }
            else if(head_data_flag && (judge->word1 & EMAC_RXD_EOH))
            {
                frame_len_total += ((judge->word1 & EMAC_RXD_LEN_MASK) % (rxqueue->buflength));
            }
            else
            {
                frame_len_total += rxqueue->buflength;
            }

            // if(judge->word0 & EMAC_RXD_WRAP)
            //     judge = rxqueue->bdBase;
            // else
            //     judge++;
            emac_head_plus_one(judge);
        }
    }
    else
    {
        if((head->word1 & EMAC_RXD_LEN_MASK) > rx_len)
        {
            k510_logce("Frame length > rxbuf lenth\n");
            return -1;
        }
    }

    /* 开始搬数 */
    int frame_len = 0;
    uintptr_t frame_addr;
    for(uint32_t i = 0; i < rxqueue->descMax; i++)
    {
        frame_addr = head->word0 & EMAC_RXD_ADDR_MASK;
        if((head->word1 & EMAC_RXD_SOF) && (head->word1 & EMAC_RXD_EOF))    /* head指向的bd，即有sof也有eof，即bd中包含一帧数据 */
        {
            frame_len = head->word1 & EMAC_RXD_LEN_MASK;
            memcpy(rxbuf, (void *)frame_addr, frame_len);
            head->word0 &= ~EMAC_RXD_USED;
            head->word1 = 0;
            break;
        }
        else if(head->word1 & EMAC_RXD_EOF)    /* 最后复制eof BD，长度为word1的帧长度减去之前复制的数据总数 */
        {
            uint32_t bd_len = head->word1 & EMAC_RXD_LEN_MASK;
            memcpy(rxbuf, (void *)frame_addr, bd_len - frame_len);
            head->word0 &= ~EMAC_RXD_USED;
            head->word1 = 0;
            frame_len = bd_len;
            break;
        }
        else if(head_data_flag && (head->word1 & EMAC_RXD_EOH))
        {
            uint32_t header_recv_len = (head->word1 & EMAC_RXD_LEN_MASK) % (rxqueue->buflength);
            memcpy(rxbuf, (void *)frame_addr, header_recv_len);
            rxbuf += header_recv_len;
            frame_len += header_recv_len;
            head->word0 &= ~EMAC_RXD_USED;
            head->word1 = 0;
        }
        else    /* 非eof BD 复制整个 BD buf */
        {
            memcpy(rxbuf, (void *)frame_addr, rxqueue->buflength);
            rxbuf += rxqueue->buflength;
            frame_len += rxqueue->buflength;
            head->word0 &= ~EMAC_RXD_USED;
            head->word1 = 0;
        }
        // if(head->word0 & EMAC_RXD_WRAP)
        //     head = rxqueue->bdBase;
        // else
        //     head++;
        emac_head_plus_one(head);
    }

    // if(head->word0 & EMAC_RXD_WRAP)
    //     head = rxqueue->bdBase;
    // else
    //     head++;
    emac_head_plus_one(head);   /* head指向下一个bd */
    rxqueue->bdHead = head;
    return frame_len;   /* 返回帧长度 */
}

void emac_rxqueue_timestamp_init(emac_rxtsqueue_t *rxqueue, emac_bd_timestamp_t *list, uint8_t *rx_buf, uint16_t rx_buf_len, uint32_t bd_number, emac_queue_number_t qnumber)
{
    *rxqueue = (emac_rxtsqueue_t) {
        .bdBase = list,
        .bdHead = list,
        .bdTail = list,
        .descMax = bd_number,
        .qNumber = qnumber,
    };

    emac_set_rx_buf_size(rx_buf_len, qnumber);

    memset(list, 0, sizeof(emac_bd_timestamp_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word0 = (uintptr_t)(rx_buf + rx_buf_len * i);
    }
    list[bd_number - 1].word0 |= EMAC_RXBD_WRAP_BIT;

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->receive_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->receive_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->receive_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

/**
 * receive queue init
 */
void emac_rxqueue_init(emac_rxqueue_t *rxqueue, emac_bd_t *list, uint8_t *rx_buf, uint16_t rx_buf_len, uint32_t bd_number, emac_queue_number_t qnumber)
{
    *rxqueue = (emac_rxqueue_t) {
        .bdBase = list,
        .bdHead = list,
        .bdTail = list,
        .descMax = bd_number,
        .qNumber = qnumber,
    };

    emac_set_rx_buf_size(rx_buf_len, qnumber);

    memset(list, 0, sizeof(emac_bd_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word0 = (uintptr_t)(rx_buf + rx_buf_len * i);
    }
    list[bd_number - 1].word0 |= EMAC_RXBD_WRAP_BIT;

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->receive_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->receive_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->receive_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

void emac_rxqueue_global_init(emac_bd_t *list, uint8_t *rx_buf, uint16_t rx_buf_len, uint32_t bd_number, emac_queue_number_t qnumber)
{
    rx_queue[qnumber] = (emac_rxqueue_t) {
        .bdBase = list,
        .bdHead = list,
        .bdTail = list,
        .descMax = bd_number,
        .qNumber = qnumber,
    };

    emac_set_rx_buf_size(rx_buf_len, qnumber);

    memset(list, 0, sizeof(emac_bd_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word0 = (uintptr_t)(rx_buf + rx_buf_len * i);
    }
    list[bd_number - 1].word0 |= EMAC_RXBD_WRAP_BIT;

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->receive_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->receive_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->receive_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

void emac_print_rxtsdesclist(emac_rxtsqueue_t *rxqueue)
{
    if(rxqueue->descMax == 0)
        return;

    uint32_t len;
    k510_logci("---  Rx Descriptor List Queue %d ---rxlist %p\n", rxqueue->qNumber, rxqueue->bdBase);
    emac_bd_timestamp_t *bd = rxqueue->bdBase;
    for (uint32_t i = 0; i < rxqueue->descMax; i++) {

        k510_logi("d%3u ",i);

        k510_logi("wd0:%08X  ",bd->word0);
        k510_logi("wd1:%08X  ",bd->word1);
        k510_logi("wd2:%08X  ",bd->word2);
        k510_logi("wd3:%08X  ",bd->word3);

        len = bd->word1 & EMAC_RXD_LEN_MASK;

        k510_logi("u:%u w:%u s:%u e:%u  add:%08X tsv:%u len:%4u %s %s\n",
                    (bd->word0 & EMAC_RXD_USED) ? 1 : 0, (bd->word0 & EMAC_RXD_WRAP) ? 1 : 0,
                    (bd->word1 & EMAC_RXD_SOF) ? 1 : 0, (bd->word1 & EMAC_RXD_EOF) ? 1 : 0,
                    bd->word0 & EMAC_RXD_ADDR_MASK,(bd->word0 & EMAC_RXD_TS_VALID) ? 1 : 0,
                    len,
                    (bd == rxqueue->bdTail) ? "<-tail" : "",
                    (bd == rxqueue->bdHead) ? "<-head" : "");

        if ((bd->word0 & EMAC_RXD_USED) && (bd->word1 & EMAC_RXD_EOF)) {
            k510_logi("  fcsErr:%u cfi:%u vPri:%lu pTag:%u vTag:%u " \
                        "tyReg:%lu tyMat:%u sReg:%lu sAdd:%u ext:%u uni:%u " \
                        "mul:%u brd:%u\n",
                        (bd->word1 & EMAC_RXD_LEN13_FCS_STAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_CFI) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_VLAN_PRI_MASK) >> EMAC_RXD_VLAN_PRI_SHIFT,
                        (bd->word1 & EMAC_RXD_PRI_TAG) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_VLAN_TAG) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_TYP_IDR_CHK_STA_MASK) >> EMAC_RXD_TYP_IDR_CHK_STA_SHIFT,
                        (bd->word1 & EMAC_RXD_TYP_MAT_SNP_NCFI) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_SPEC_REG_MASK) >> EMAC_RXD_SPEC_REG_SHIFT,
                        (bd->word1 & EMAC_RXD_SPEC_ADD_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_EXT_ADD_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_UNI_HASH_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_MULTI_HASH_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_BROADCAST_DET) ? 1 : 0);
        }
#if 0
#ifdef EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ
        else   /* show header-split flags when relevant */
        if (pD->hwCfg.hdr_split && (bd->word0 & EMAC_RXD_USED) && !(bd->word1 & EMAC_RXD_EOF)
            && EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(
                CPS_UncachedRead32(&(pD->regs->dma_config)))) {
            k510_logi("                                   hdr:%u eoh:%u\n",
                        (bd->word1 & EMAC_RXD_HDR) ? 1 : 0, (bd->word1 & EMAC_RXD_EOH) ? 1 : 0);
        }
#endif
#endif
        bd++;
    }

    k510_logi("\n");
}

/**
 * print receive info
 */
void emac_print_rxdesclist(emac_rxqueue_t *rxqueue)
{
    if(rxqueue->descMax == 0)
        return;

    uint32_t len;
    k510_logci("---  Rx Descriptor List Queue %d ---rxlist %p\n", rxqueue->qNumber, rxqueue->bdBase);
    emac_bd_t *bd = rxqueue->bdBase;
    for (uint32_t i = 0; i < rxqueue->descMax; i++) {

        k510_logi("d%3u ",i);

        k510_logi("wd0:%08X  ",bd->word0);
        k510_logi("wd1:%08X  ",bd->word1);

        len = bd->word1 & EMAC_RXD_LEN_MASK;

        k510_logi("u:%u w:%u s:%u e:%u  add:%08X tsv:%u len:%4u %s %s\n",
                    (bd->word0 & EMAC_RXD_USED) ? 1 : 0, (bd->word0 & EMAC_RXD_WRAP) ? 1 : 0,
                    (bd->word1 & EMAC_RXD_SOF) ? 1 : 0, (bd->word1 & EMAC_RXD_EOF) ? 1 : 0,
                    bd->word0 & EMAC_RXD_ADDR_MASK,(bd->word0 & EMAC_RXD_TS_VALID) ? 1 : 0,
                    len,
                    (bd == rxqueue->bdTail) ? "<-tail" : "",
                    (bd == rxqueue->bdHead) ? "<-head" : "");

        if ((bd->word0 & EMAC_RXD_USED) && (bd->word1 & EMAC_RXD_EOF)) {
            k510_logi("  fcsErr:%u cfi:%u vPri:%lu pTag:%u vTag:%u " \
                        "tyReg:%lu tyMat:%u sReg:%lu sAdd:%u ext:%u uni:%u " \
                        "mul:%u brd:%u\n",
                        (bd->word1 & EMAC_RXD_LEN13_FCS_STAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_CFI) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_VLAN_PRI_MASK) >> EMAC_RXD_VLAN_PRI_SHIFT,
                        (bd->word1 & EMAC_RXD_PRI_TAG) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_VLAN_TAG) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_TYP_IDR_CHK_STA_MASK) >> EMAC_RXD_TYP_IDR_CHK_STA_SHIFT,
                        (bd->word1 & EMAC_RXD_TYP_MAT_SNP_NCFI) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_SPEC_REG_MASK) >> EMAC_RXD_SPEC_REG_SHIFT,
                        (bd->word1 & EMAC_RXD_SPEC_ADD_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_EXT_ADD_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_UNI_HASH_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_MULTI_HASH_MAT) ? 1 : 0,
                        (bd->word1 & EMAC_RXD_BROADCAST_DET) ? 1 : 0);
        }
#if 0
#ifdef EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ
        else   /* show header-split flags when relevant */
        if (pD->hwCfg.hdr_split && (bd->word0 & EMAC_RXD_USED) && !(bd->word1 & EMAC_RXD_EOF)
            && EMAC_REGS__DMA_CONFIG__HDR_DATA_SPLITTING_EN__READ(
                CPS_UncachedRead32(&(pD->regs->dma_config)))) {
            k510_logi("                                   hdr:%u eoh:%u\n",
                        (bd->word1 & EMAC_RXD_HDR) ? 1 : 0, (bd->word1 & EMAC_RXD_EOH) ? 1 : 0);
        }
#endif
#endif
        bd++;
    }

    k510_logi("\n");
}

void emac_print_global_rxdesclist(void)
{
    for(uint32_t i = 0; i < EMAC_QUEUE_NUMBER_MAX; i++)
    {
        emac_print_rxdesclist(&rx_queue[i]);
    }
}

/* Tx Rx bd init reserve */

void emac_tx_bd_init(emac_bd_t *list, uint32_t bd_number, emac_queue_number_t qnumber)
{
    memset(list, 0, sizeof(emac_bd_t) * bd_number);
    for(uint32_t i = 0; i < bd_number; i++)
    {
        list[i].word1 |= EMAC_TXBD_USED_BIT;    /* Set used bit */
    }
    list[bd_number -1].word1 |= EMAC_TXBD_WRAP_BIT;   /* Last bd set wrap bit */

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->transmit_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->transmit_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->transmit_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

void emac_rx_bd_init(emac_bd_t *list, uint32_t bd_number, uint8_t *rx_buf[],  emac_queue_number_t qnumber)
{
    memset(list, 0, sizeof(emac_bd_t) * bd_number);
    for(uint32_t i = 0; i < bd_number - 1; i++)
    {
        list[i].word0 = (uintptr_t)rx_buf[i] & 0xFFFFFFFCU;
    }
    list[bd_number - 1].word0 |= EMAC_RXBD_USED_BIT | EMAC_RXBD_WRAP_BIT;

    switch(qnumber)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->receive_q_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->receive_q1_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->receive_q2_ptr = (uintptr_t)list & 0xFFFFFFFCU;
            break;
    }
}

/**
 * byte_mask:
 * When high, the associated byte of the specific
 * address will not be compared. Bit 24 controls whether
 * the first byte received should be compared. Bit 29
 * controls whether the last byte received should be
 * compared
 */
void emac_set_specific_addr(emac_spec_addr_num_t num, emac_macaddress_t *mac, emac_spec_addr_filer_t filter, uint8_t byte_mask)
{
    uint32_t bottom_val = mac->byte[0] + (mac->byte[1] << 8) + (mac->byte[2] << 16) + (mac->byte[3] << 24);
    uint32_t top_val = mac->byte[4] + (mac->byte[5] << 8) + (filter << 16);
    if(num != EMAC_SPEC_ADDRESS_1)
    {
        top_val += (byte_mask << 24);
    }
    writel(bottom_val, (uintptr_t)(&emac->spec_add1_bottom) + num * 8);
    writel(top_val, (uintptr_t)(&emac->spec_add1_top) + num * 8);
}

void emac_set_addr1_mask(emac_macaddress_t *mac)
{
    emac->mask_add1_bottom = mac->byte[0] + (mac->byte[1] << 8) + (mac->byte[2] << 16) + (mac->byte[3] << 24);
    emac->mask_add1_top = mac->byte[4] + (mac->byte[5] << 8);
}

int emac_transmit_data(emac_txqueue_t *txqueue, uint8_t *tx_buf, uint32_t tx_len, uint32_t send_flag)
{
    emac_txqueue_set_send_data(txqueue, tx_buf, tx_len, send_flag);

    if(send_flag & EMAC_TXB_LAST_BUFF)
    {
        emac_tx_start();

        if(emac_tx_wait_done(EMAC_WORK_TIMEOUT))
        {
            k510_logce("EMAC SEND DATA ERR\n");
            return -1;
        }
        emac_print_txdesclist(txqueue);
        emac_txqueue_free_data(txqueue);
    }
    else
        emac_print_txdesclist(txqueue);
    return 0;
}

int emac_tx_rx_check(emac_txqueue_t *txqueue, emac_rxqueue_t *rxqueue, uint8_t *tx_buf, uint32_t tx_len,
                        uint8_t *rx_buf, uint32_t rx_buf_len, uint32_t send_flag)
{
    int ret = 0;
    emac_txqueue_set_send_data(txqueue, tx_buf, tx_len, send_flag);
    if(!(send_flag & EMAC_TXB_LAST_BUFF))
    {
        k510_logce("%s:> send flag should include EMAC_TXB_LAST_BUFF\n", __func__);
        return -1;
    }
    emac_tx_start();

    if(emac_tx_wait_done(EMAC_WORK_TIMEOUT))
    {
        k510_logce("EMAC SEND DATA ERR\n");
        return -1;
    }
    emac_print_txdesclist(txqueue);
    emac_txqueue_free_data(txqueue);

    if(emac_rx_wait_done(EMAC_WORK_TIMEOUT))
    {
        k510_logce("EMAC REJECT\n");
        return -1;
    }
    emac_print_rxdesclist(rxqueue);

    if(emac_rxqueue_get_frame(rxqueue, rx_buf, rx_buf_len) > 0)
    {
        emac_print_rxdesclist(rxqueue);
        if(memcmp(rx_buf, tx_buf, tx_len) != 0)
        {
            k510_logce("ERR:> TX DATA != TX DATA\n");
            emac_clear_all_stats();
            return -1;
        }
        else
            k510_logci("TX DATA == RX DATA\n");
    }
    else
    {
        ret = -1;
    }
    emac_read_stats();
    return ret;
}

void emac_set_mdc_clk_div(emac_mdc_div_t div)
{
    emac->network_config = ((emac->network_config &      \
                        ~(EMAC_MDC_CLOCK_DIVISION_MASK << EMAC_MDC_CLOCK_DIVISION_OFFSET))  \
                        | (div << EMAC_MDC_CLOCK_DIVISION_OFFSET));
}

void emac_set_spec_type(uint16_t type, emac_spec_type_num_t type_num)
{
    // uint32_t *reg = (uint32_t *)((uintptr_t)(&emac->spec_type1) + type_num * 4);
    // *reg = (1 << 31) | type;
    writel((1 << 31) | type, (uintptr_t)(&emac->spec_type1) + type_num * 4);
}

void emac_spec_type_disable(emac_spec_type_num_t type_num)
{
    uint32_t *reg = (uint32_t *)((uintptr_t)(&emac->spec_type1) + type_num * 4);
    *reg &= ~(1 << 31);
}

void emac_screen_type1_disable_all(void)
{
    for(uint32_t i = 0; i < EMAC_SCREEN_TYPE1_REGMAX; i++)
    {
        writel(0, (uintptr_t)(&emac->screening_type_1_register_0) + i * 4);
    }
}

void emac_set_screen_type1(emac_screen_type1_t *type1_cfg, emac_screen_type1_num_t num)
{
    writel(readl(type1_cfg), (uintptr_t)(&emac->screening_type_1_register_0) + num * 4);
}

void emac_get_screen_type1(emac_screen_type1_t *type1_cfg, emac_screen_type1_num_t num)
{
    uint32_t reg_val = readl((uintptr_t)(&emac->screening_type_1_register_0) + num * 4);
    *type1_cfg = *((emac_screen_type1_t *) &reg_val);
}

void emac_screen_type2_disable_all(void)
{
    for(uint32_t i = 0; i < EMAC_SCREEN_TYPE2_REGMAX; i++)
    {
        writel(0, (uintptr_t)(&emac->screening_type_2_register_0) + i * 4);
    }
}

void emac_set_screen_type2(emac_screen_type2_t *type2_cfg, emac_screen_type2_num_t num)
{
    writel(readl(type2_cfg), (uintptr_t)(&emac->screening_type_2_register_0) + num * 4);
}

void emac_get_screen_type2(emac_screen_type2_t *type2_cfg, emac_screen_type2_num_t num)
{
    uint32_t reg_val = readl((uintptr_t)(&emac->screening_type_2_register_0) + num * 4);
    *type2_cfg = *((emac_screen_type2_t *) &reg_val);
}

void emac_set_screen_type2_ethertype(uint16_t ether_type, emac_screen_type2_ethertype_t num)
{
    writel(ether_type, (uintptr_t)(&emac->screening_type_2_ethertype_reg_0) + 4 * num);
}

void emac_set_screen_type2_compare(emac_screen_type2_compare_t *type2_compare, emac_screen_type2_compare_num_t num)
{
    uint32_t reg0 = 0;
    uint32_t reg1 = 0;
    switch(type2_compare->offsetPosition)
    {
        case EMAC_T2COMP_OFF_VID_C_TAG:
        case EMAC_T2COMP_OFF_VID_S_TAG:
            EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_VLAN_ID__SET(reg1);
            EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__CLR(reg1);
            reg1 &= ~EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MASK;
            reg1 &= ~EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MASK;

            /* if S-TAG VID comparison set bit 7 */
            if (type2_compare->offsetPosition == EMAC_T2COMP_OFF_VID_S_TAG) {
                reg1 |= EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__WRITE(0x01);
            }
            break;

        case EMAC_T2COMP_OFF_SOF:
        case EMAC_T2COMP_OFF_ETYPE:
        case EMAC_T2COMP_OFF_IPHDR:
        case EMAC_T2COMP_OFF_TCPUDP:
            EMAC_REGS__TYPE2_COMPARE_WORD_1__OFFSET_VALUE__MODIFY(reg1, type2_compare->offsetVal);
            EMAC_REGS__TYPE2_COMPARE_WORD_1__COMPARE_OFFSET__MODIFY(reg1, type2_compare->offsetPosition);
            EMAC_REGS__TYPE2_COMPARE_WORD_1__DISABLE_MASK__MODIFY(reg1, type2_compare->disableMask);
            break;
    }

    EMAC_REGS__TYPE2_COMPARE_WORD_0__MASK_VALUE__MODIFY(reg0, type2_compare->compMask);
    EMAC_REGS__TYPE2_COMPARE_WORD_0__COMPARE_VALUE__MODIFY(reg0, type2_compare->compValue);

    writel(reg0, (uintptr_t)(&emac->type2_compare_0_word_0) + num * 8);
    writel(reg1, (uintptr_t)(&emac->type2_compare_0_word_1) + num * 8);
}

void emac_set_1588timer(emac_1588timerval_t *time_val)
{
    emac->tsu_timer_msb_sec = time_val->secsUpper;
    emac->tsu_timer_sec = time_val->secsLower;
    emac->tsu_timer_nsec = time_val->nanosecs;
}

void emac_get_1588timer(emac_1588timerval_t *time_val)
{
    time_val->secsUpper = emac->tsu_timer_msb_sec;
    time_val->secsLower = emac->tsu_timer_sec;
    time_val->nanosecs = emac->tsu_timer_nsec;
}

void emac_set_1588timer_inc(emac_timerincrement_t *inc)
{
    emac->tsu_timer_incr_sub_nsec = inc->subNsInc | (inc->lsbSubNsInc << 24);
    emac->tsu_timer_incr = inc->nanoSecsInc;
}

void emac_get_1588timer_inc(emac_timerincrement_t *inc)
{
    inc->subNsInc = emac->tsu_timer_incr_sub_nsec & 0xFFFFU;
    inc->lsbSubNsInc = (emac->tsu_timer_incr_sub_nsec >> 24) & 0xFFU;
    inc->nanoSecsInc = emac->tsu_timer_incr & 0xFFU;
}

void emac_set_tsutimer_compare(emac_tsutimerval_t *time_val)
{
    emac->tsu_nsec_cmp = time_val->nanosecs;
    emac->tsu_sec_cmp = time_val->secsLower;
    emac->tsu_msb_sec_cmp = time_val->secsUpper;
}

void emac_get_tsutimer_compare(emac_tsutimerval_t *time_val)
{
    time_val->nanosecs = emac->tsu_nsec_cmp & 0x3FFFFFU;
    time_val->secsLower = emac->tsu_sec_cmp;
    time_val->secsUpper = emac->tsu_msb_sec_cmp & 0xFFFFU;
}

void emac_adjust_1588timer(int nSecAdjust)
{
    uint32_t reg = 0;
    /* Absolute value */
    uint32_t nSecAdjustAbs;
    if (nSecAdjust<0) {
        EMAC_REGS__TSU_TIMER_ADJUST__ADD_SUBTRACT__SET(reg);
        nSecAdjustAbs = -nSecAdjust;
    } else {
        nSecAdjustAbs = nSecAdjust;
    }
    EMAC_REGS__TSU_TIMER_ADJUST__INCREMENT_VALUE__MODIFY(reg, nSecAdjustAbs);
    emac->tsu_timer_adjust = reg;
}

static void fillEnableQ0ExclusiveEvents(uint32_t events, uint32_t *regVal)
{
    if (0U != (events & (uint32_t)EMAC_EV_MAN_FRAME)) {
        EMAC_REGS__INT_ENABLE__ENABLE_MANAGEMENT_DONE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_USED_READ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_UNDERRUN)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PCS_LINK_CHANGE_DET)) {
        EMAC_REGS__INT_ENABLE__ENABLE_LINK_CHANGE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PCS_AN_COMPLETE)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PCS_LP_PAGE_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TSU_SEC_INC)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TSU_TIME_MATCH)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(*regVal);
    }


    if (0U != (events & (uint32_t)EMAC_EV_RX_OVERRUN)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_OVERRUN_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PAUSE_NZ_QU_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PAUSE_TIME_ZERO)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PAUSE_FRAME_TX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_EXT_INTR)) {
        EMAC_REGS__INT_ENABLE__ENABLE_EXTERNAL_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_DLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_SYNC)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_DLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_SYNC)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_PDLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_PDLY_RSP)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_PDLY_REQ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_PDLY_RSP)) {
        EMAC_REGS__INT_ENABLE__ENABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_LPI_CH_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RX_LPI_INDICATION_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_WOL_RX)) {
        EMAC_REGS__INT_ENABLE__ENABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(*regVal);
    }


    if (0U != (events & (uint32_t)EMAC_EV_RX_LOCKUP)) {
     EMAC_REGS__INT_ENABLE__ENABLE_RX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
    if (0U != (events & (uint32_t)EMAC_EV_TX_LOCKUP)) {
     EMAC_REGS__INT_ENABLE__ENABLE_TX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
}


static void fillDisableQ0ExclusiveEvents(uint32_t events, uint32_t *regVal)
{
    if (0U != (events & (uint32_t)EMAC_EV_MAN_FRAME)) {
        EMAC_REGS__INT_DISABLE__DISABLE_MANAGEMENT_DONE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_USED_READ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_USED_BIT_READ_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_UNDERRUN)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_BUFFER_UNDER_RUN_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PCS_LINK_CHANGE_DET)) {
        EMAC_REGS__INT_DISABLE__DISABLE_LINK_CHANGE_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PCS_AN_COMPLETE)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PCS_AUTO_NEGOTIATION_COMPLETE_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PCS_LP_PAGE_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PCS_LINK_PARTNER_PAGE_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TSU_SEC_INC)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TSU_SECONDS_REGISTER_INCREMENT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TSU_TIME_MATCH)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TSU_TIMER_COMPARISON_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_RX_OVERRUN)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_OVERRUN_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PAUSE_NZ_QU_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_WITH_NON_ZERO_PAUSE_QUANTUM_INTERRUPT__SET
        (*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PAUSE_TIME_ZERO)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_TIME_ZERO_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PAUSE_FRAME_TX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PAUSE_FRAME_TRANSMITTED_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_EXT_INTR)) {
        EMAC_REGS__INT_DISABLE__DISABLE_EXTERNAL_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_DLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_SYNC)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_DLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_DELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_SYNC)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_SYNC_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_PDLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_RX_PDLY_RSP)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_RECEIVED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_PDLY_REQ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_REQ_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_PTP_TX_PDLY_RSP)) {
        EMAC_REGS__INT_DISABLE__DISABLE_PTP_PDELAY_RESP_FRAME_TRANSMITTED__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_LPI_CH_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RX_LPI_INDICATION_INTERRUPT__SET(*regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_WOL_RX)) {
        EMAC_REGS__INT_DISABLE__DISABLE_WOL_EVENT_RECEIVED_INTERRUPT__SET(*regVal);
    }


    if (0U != (events & (uint32_t)EMAC_EV_RX_LOCKUP)) {
     EMAC_REGS__INT_DISABLE__DISABLE_RX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
    if (0U != (events & (uint32_t)EMAC_EV_TX_LOCKUP)) {
     EMAC_REGS__INT_DISABLE__DISABLE_TX_LOCKUP_DETECTED_INTERRUPT__SET
        (*regVal);
    }
}

static void emac_q0events_disable(uint32_t events)
{
    uint32_t regVal = 0U;

    fillDisableQ0ExclusiveEvents(events, &regVal);

    if (0U != (events & (uint32_t)EMAC_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_RX_USED_READ)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    emac->int_disable = regVal;
}

static void emac_q0events_enable(uint32_t events)
{
    uint32_t regVal = 0U;

    fillEnableQ0ExclusiveEvents(events, &regVal);

    if (0U != (events & (uint32_t)EMAC_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_RX_USED_READ)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RECEIVE_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    emac->int_enable = regVal;
}


static void emac_qnevents_enable(uint32_t events, emac_queue_number_t queueNum)
{
    uint32_t regVal = 0U;
    volatile uint32_t *regPtr = NULL;

    regPtr = (uint32_t *)((uintptr_t)(&emac->int_q1_enable) + 4 * queueNum);

    if (0U != (events & (uint32_t)EMAC_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_RX_USED_READ)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RX_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_Q_ENABLE__ENABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    *regPtr = regVal;

}

static void emac_qnevents_disable(uint32_t events, emac_queue_number_t queueNum)
{
    uint32_t regVal = 0U;
    volatile uint32_t *regPtr = NULL;

    regPtr = (uint32_t *)((uintptr_t)(&emac->int_q1_disable) + 4 * queueNum);

    if (0U != (events & (uint32_t)EMAC_EV_RX_COMPLETE)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RECEIVE_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_RX_USED_READ)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RX_USED_BIT_READ_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_RETRY_EX_LATE_COLL)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RETRY_LIMIT_EXCEEDED_OR_LATE_COLLISION_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_FR_CORRUPT)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_FRAME_CORRUPTION_DUE_TO_AMBA_ERROR_INTERRUPT__SET
        (regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_TX_COMPLETE)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_TRANSMIT_COMPLETE_INTERRUPT__SET(regVal);
    }

    if (0U != (events & (uint32_t)EMAC_EV_HRESP_NOT_OK)) {
        EMAC_REGS__INT_Q_DISABLE__DISABLE_RESP_NOT_OK_INTERRUPT__SET(regVal);
    }

    *regPtr = regVal;

}

void emac_set_event_enable(uint32_t events, emac_queue_number_t queueNum)
{
    if(queueNum == EMAC_QUEUE_NUMBER0)
        emac_q0events_enable(events);
    else
        emac_qnevents_enable(events, queueNum);
}

void emac_set_event_disable(uint32_t events, emac_queue_number_t queueNum)
{
    if(queueNum == EMAC_QUEUE_NUMBER0)
        emac_q0events_disable(events);
    else
        emac_qnevents_disable(events, queueNum);
}

void emac_set_desctimestamp_mode(emac_txtsmode_t txmode, emac_rxtsmode_t rxmode)
{
    emac->tx_bd_control = txmode << 4;
    emac->rx_bd_control = rxmode << 4;
}

void emac_wol_config(emac_wol_config_t *config)
{
    emac->wol_register = readl(config);
}

void emac_set_txqueue_schedule(emac_queue_number_t qnum, emac_txschedtype_t schedtype)
{
    if(schedtype == EMAC_TX_SCHED_TYPE_CBS && qnum == EMAC_QUEUE_NUMBER0)
        assert("Q0 can't be CBS\n");

    switch(qnum)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->tx_sched_ctrl = ((emac->tx_sched_ctrl & ~(0x3)) | schedtype);
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->tx_sched_ctrl = ((emac->tx_sched_ctrl & ~(0x0c)) | (schedtype << 2));
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->tx_sched_ctrl = ((emac->tx_sched_ctrl & ~(0x30)) | (schedtype << 4));
            break;
    }
}

void emac_set_cbs_idleslope(emac_queue_number_t qnum, uint32_t idleslope)
{
    if(qnum == EMAC_QUEUE_NUMBER0)
        assert("Q0 can't be CBS\n");
    emac_set_txqueue_schedule(qnum, EMAC_TX_SCHED_TYPE_FIXED);
    if(qnum == EMAC_QUEUE_NUMBER1)
    {
        emac->cbs_idleslope_q_b = idleslope;
    }
    else
    {
        emac->cbs_idleslope_q_a = idleslope;
    }
    emac_set_txqueue_schedule(qnum, EMAC_TX_SCHED_TYPE_CBS);
}

void emac_cbs_enable(emac_cbs_num_t num, uint32_t idleslope)
{
    emac_cbs_disable(num);
    if(num == EMAC_CBS_QA)
    {
        emac->cbs_idleslope_q_a = idleslope;
        emac->cbs_control |= 0x1U;
    }
    else
    {
        emac->cbs_idleslope_q_b = idleslope;
        emac->cbs_control |= 0x2U;
    }
}

void emac_cbs_disable(emac_cbs_num_t num)
{
    if(num == EMAC_CBS_QA)
    {
        emac->cbs_control &= ~0x1U;
    }
    else
    {
        emac->cbs_control &= ~0x2U;
    }
}

void emac_set_rate_limit(emac_queue_number_t qnum, uint8_t limit)
{
    switch(qnum)
    {
        case EMAC_QUEUE_NUMBER0:
            emac->bw_rate_limit_q0to3 = (emac->bw_rate_limit_q0to3 & ~0xFF) | limit;
            break;
        case EMAC_QUEUE_NUMBER1:
            emac->bw_rate_limit_q0to3 = (emac->bw_rate_limit_q0to3 & ~0xFF00) | (limit << 8);
            break;
        case EMAC_QUEUE_NUMBER2:
        default:
            emac->bw_rate_limit_q0to3 = (emac->bw_rate_limit_q0to3 & ~0xFF0000) | (limit << 16);
            break;
    }
}
void __attribute__((weak, alias("emac_set_rate_limit"))) emac_set_dwrr_weight(emac_queue_number_t qnum, uint8_t weight);

// void emac_set_dwrr_weight(emac_queue_number_t qnum, uint8_t weight)
// {
//     emac_set_rate_limit(qnum, weight);
// }

void __attribute__((weak, alias("emac_set_rate_limit"))) emac_set_ets_band(emac_queue_number_t qnum, uint8_t band);

void emac_enst_enable(emac_queue_number_t qnum)
{
    emac->enst_control |= (1 << qnum);
}

void emac_enst_disable(emac_queue_number_t qnum)
{
    emac->enst_control &= ~(1 << qnum);
}

void emac_set_enst_config(emac_queue_number_t qnum, emac_enst_config_t *config)
{
    if(config->startTimeS > 3 || config->startTimeNs >= 0x40000000U || config->onTime >= 0x20000U || config->offTime >= 0x20000U)
        assert("enst time config err\n");
    uint32_t reg_val = 0;
    reg_val |= config->startTimeS << 30;
    reg_val |= config->startTimeNs;
    writel(reg_val, ((uintptr_t)(&emac->enst_start_time_q8) + 4 * qnum));
    writel(config->onTime, ((uintptr_t)(&emac->enst_on_time_q8) + 4 * qnum));
    writel(config->offTime, ((uintptr_t)(&emac->enst_off_time_q8) + 4 * qnum));
}

void emac_set_pause_quantum(uint16_t value, uint8_t qpriority)
{
    switch(qpriority)
    {
        default:
        case 0:
            emac->tx_pause_quantum = (emac->tx_pause_quantum & ~0xFFFFU) | value;
            break;
        case 1:
            emac->tx_pause_quantum = (emac->tx_pause_quantum & ~(0xFFFFU << 16)) | (value << 16);
            break;
        case 2:
            emac->tx_pause_quantum1 = (emac->tx_pause_quantum & ~0xFFFFU) | value;
            break;
        case 3:
            emac->tx_pause_quantum1 = (emac->tx_pause_quantum & ~(0xFFFFU << 16)) | (value << 16);
            break;
        case 4:
            emac->tx_pause_quantum2 = (emac->tx_pause_quantum & ~0xFFFFU) | value;
            break;
        case 5:
            emac->tx_pause_quantum2 = (emac->tx_pause_quantum & ~(0xFFFFU << 16)) | (value << 16);
            break;
        case 6:
            emac->tx_pause_quantum1 = (emac->tx_pause_quantum & ~0xFFFFU) | value;
            break;
        case 7:
            emac->tx_pause_quantum3 = (emac->tx_pause_quantum & ~(0xFFFFU << 16)) | (value << 16);
            break;

    }
}

void emac_reset(void)
{
    sysctl_reset(SYSCTL_RESET_EMAC);
}