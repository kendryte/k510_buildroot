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
#include <muxpin.h>

#ifdef _EVBLP4
/* iomux default list */
static muxpin_config_t muxpin_default[MUXPIN_NUM_IO] = {
	/*
	 * IO 0        : BOOT_CTL1
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 1        : BOOT_CTL0
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 2        : JTAG_TCK
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 3        : JTAG_TDI
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 4        : JTAG_TDO
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 5        : JTAG_TMS
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 6        : JTAG_TRSTN
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 7        : MMC0_CLK
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 8        : MMC0_CMD
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 9        : MMC0_DATA7
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 10       : MMC0_DATA6
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 11       : MMC0_DATA5
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 12       : MMC0_DATA4
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 13       : MMC0_DATA3
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 14       : MMC0_DATA2
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 15       : MMC0_DATA1
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 16       : MMC0_DATA0
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 17       : MMC1_CLK
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 18       : MMC1_CMD
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 19       : MMC1_DATA3
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 20       : MMC1_DATA2
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 21       : MMC1_DATA1
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 22       : MMC1_DATA0
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 23       : MMC2_CLK
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 24       : MMC2_CMD
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 25       : MMC2_DATA3
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 26       : MMC2_DATA2
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 27       : MMC2_DATA1
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 28       : MMC2_DATA0
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 29       : EMAC_TX_CLK_OUT
	 * EMAC output tx clock
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 30       : EMAC_RX_CLK_IN
	 * EMAC input rx clock
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 31       : EMAC_COL
	 * EMAC Collision detect from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 32       : EMAC_CRS
	 * EMAC Carrier sense from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 33       : EMAC_TX_ER
	 * EMAC Transmit error signal to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 34       : EMAC_RX_ER
	 * EMAC Receive error signal from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 35       : EMAC_MDC
	 * EMAC Management data clock to pin
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 36       : EMAC_MDIO
	 * EMAC Management data input/out pin
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 37       : EMAC_RX_CTL
	 * EMAC Receive control signal from the PHY.
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 38       : EMAC_TX_CTL
	 * EMAC Transmit control signal to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 39       : EMAC_RX_D3
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 40       : EMAC_RX_D2
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 41       : EMAC_RX_D1
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 42       : EMAC_RX_D0
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 43       : EMAC_TX_D3
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 44       : EMAC_TX_D2
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 45       : EMAC_TX_D1
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 46       : EMAC_TX_D0
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 47       : DVP_D0
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 48       : DVP_D1
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 49       : DVP_D2
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 50       : DVP_D3
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 51       : DVP_D4
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 52       : DVP_D5
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 53       : DVP_D6
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 54       : DVP_D7
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 55       : DVP_D8
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 56       : DVP_D9
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 57       : DVP_D10
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 58       : DVP_D11
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 59       : DVP_D12
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 60       : DVP_D13
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 61       : DVP_D14
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 62       : DVP_D15
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 63       : DVP_VSYNC
	 * DVP interface VSYNC input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 64       : DVP_HREF
	 * DVP interface HSYNC input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 65       : HSRESV21
	 * Used as DVP sensor power down pin ctrl, GPIO, DEN is not used，GPIO8
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 18
    },
	/*
	 * IO 66       : DVP_PCLK
	 * DVP interface clk input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 67       : BT1120_OUT_DATA_D0
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 68       : BT1120_OUT_DATA_D1
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 69       : BT1120_OUT_DATA_D2
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 70       : BT1120_OUT_DATA_D3
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 71       : BT1120_OUT_DATA_D4
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 72       : BT1120_OUT_DATA_D5
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 73       : BT1120_OUT_DATA_D6
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 74       : BT1120_OUT_DATA_D7
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 75       : BT1120_OUT_DATA_C0
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 76       : BT1120_OUT_DATA_C1
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 77       : BT1120_OUT_DATA_C2
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 78       : BT1120_OUT_DATA_C3
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 79       : BT1120_OUT_DATA_C4
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 80       : BT1120_OUT_DATA_C5
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 81       : BT1120_OUT_DATA_C6
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 82       : BT1120_OUT_DATA_C7
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 83       : BT1120_OUT_CLK
	 * BT1120 interface output CLK
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 84       : BT1120_OUT_VSYNC
	 * BT1120 interface output VSYNC (Not necessary)
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 85       : BT1120_OUT_HSYNC
	 * BT1120 interface output HSYNC (Not necessary)
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 86       : SPI0_CLK
	 * SPI0_CLK
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 87       : SPI0_CS
	 * SPI0_CS
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 88       : SPI0_D0
	 * SPI0_D0
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 89       : SPI0_D1
	 * SPI0_D1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 90       : SPI0_D2
	 * SPI0_D2
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 91       : SPI0_D3
	 * SPI0_D3
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 92       : SPI0_D4
	 * SD DETECT，GPIO3
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 13
    },
	/*
	 * IO 93       : SPI0_D5
	 * USB OTG VBUS EN，GPIO2
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 12
    },
	/*
	 * IO 94       : SPI0_D6
	 * LP DDR4 EVB DVP/MIPI board SDA I2C2
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 71
    },
	/*
	 * IO 95       : SPI0_D7
	 * LP DDR4 EVB DVP/MIPI board SCL I2C2
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 70
    },
	/*
	 * IO 96       : HSRESV0
	 * PMU AXP228，N_VBUSEN GPIO28
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 38
    },
	/*
	 * IO 97       : HSRESV1
	 * GNNE power supply，GNNE_SLEEP GPIO27
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 37
    },
	/*
	 * IO 98       : HSRESV2
	 * plug pin GPIO26
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 36
    },
	/*
	 * IO 99       : HSRESV3
	 * plug pin GPIO25
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 35
    },
	/*
	 * IO 100      : HSRESV4
	 * plug pin GPIO24
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 34
    },
	/*
	 * IO 101      : HSRESV5
	 * plug pin GPIO23
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 33
    },
	/*
	 * IO 102      : HSRESV6
	 * plug pin GPIO22
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 32
    },
	/*
	 * IO 103      : HSRESV7
	 * plug pin GPIO21
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 31
    },
	/*
	 * IO 104      : HSRESV8
	 * MIPI board CSI1 VSYNC on LP4 EVB, used as GPIO GPIO16
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 26
    },
	/*
	 * IO 105      : HSRESV9
	 * MIPI board CSI1 PowerDown on LP4 EVB, used as GPIO GPIO12
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 22
    },
	/*
	 * IO 106      : HSRESV10
	 * MIPI board CSI1 HSYNC on LP4 EVB, used as GPIO GPIO17
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 27
    },
	/*
	 * IO 107      : HSRESV11
	 * MIPI board CSI1 Reset on LP4 EVB, used as GPIO GPIO13
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 23
    },
	/*
	 * IO 108      : HSRESV12
	 * DVP Sensor Reset on LP4 EVB, used as GPIO GPIO9
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 19
    },
	/*
	 * IO 109      : HSRESV13
	 * MIC_WS ?
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 173
    },
	/*
	 * IO 110      : HSRESV14
	 * MIC_SCLK_PDM
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 189
    },
	/*
	 * IO 111      : HSRESV15
	 * MIC_DATA_PDM
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 147
    },
	/*
	 * IO 112      : HSRESV16
	 * uart0 rx
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 84
    },
	/*
	 * IO 113      : HSRESV17
	 * uart0 tx
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 90
    },
	/*
	 * IO 114      : HSRESV18
	 * PDMINDAT
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 175
    },
	/*
	 * IO 115      : HSRESV19
	 * PDMINCLK
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 177
    },
	/*
	 * IO 116      : DDR_BSR_TCK
	 * IIS_DA_1V8
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 163
    },
	/*
	 * IO 117      : DDR_BSR_TDI
	 * IIS_WS_1V8 ?
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 173
    },
	/*
	 * IO 118      : DDR_BSR_TDO
	 * BT1120 board I2C SDA on LP4 EVB I2C1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 3,
	 .lsio_sel = 69
    },
	/*
	 * IO 119      : DDR_BSR_TMS
	 * BT1120 board I2C SCL on LP4 EVB I2C1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 3,
	 .lsio_sel = 68
    },
	/*
	 * IO 120      : DDR_BSR_TRSTN
	 * LED WS2812 GPIO20
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 30
    },
	/*
	 * IO 121      : HSRESV20
	 * IIS_BCK_1V8
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 171
    },
	/*
	 * IO 122      : TEST_PIN0
	 * MIPI board CSI0 VSYNC on LP4 EVB, used as GPIO GPIO14
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 24
    },
	/*
	 * IO 123      : TEST_PIN1
	 * MIPI board CSI0 PowerDown on LP4 EVB, used as GPIO GPIO10
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 20
    },
	/*
	 * IO 124      : TEST_PIN2
	 * MIPI board CSI0 HSYNC on LP4 EVB, used as GPIO GPIO15
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 25
    },
	/*
	 * IO 125      : TEST_PIN3
	 * MIPI board CSI0 Reset on LP4 EVB, used as GPIO GPIO11
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 21
    },
	/*
	 * IO 126      : TEST_PIN4
	 * WIFI/BT RESET GPIO1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 11
    },
	/*
	 * IO 127      : TEST_PIN5
	 * WIFI/BT INT GPIO0
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 10
    },
};
#endif

#ifdef _EVBLP3
/* iomux default list */
static muxpin_config_t muxpin_default[MUXPIN_NUM_IO] = {
	/*
	 * IO 0        : BOOT_CTL1
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 1        : BOOT_CTL0
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 2        : JTAG_TCK
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 3        : JTAG_TDI
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 4        : JTAG_TDO
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 5        : JTAG_TMS
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 6        : JTAG_TRSTN
	 * Use the default values without modification
	 */
	{
	 .st       = 0,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 7        : MMC0_CLK
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 8        : MMC0_CMD
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 9        : MMC0_DATA7
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 10       : MMC0_DATA6
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 11       : MMC0_DATA5
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 12       : MMC0_DATA4
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 13       : MMC0_DATA3
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 14       : MMC0_DATA2
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 15       : MMC0_DATA1
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 16       : MMC0_DATA0
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 17       : MMC1_CLK
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 18       : MMC1_CMD
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 19       : MMC1_DATA3
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 20       : MMC1_DATA2
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 21       : MMC1_DATA1
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 22       : MMC1_DATA0
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 23       : MMC2_CLK
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 24       : MMC2_CMD
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 25       : MMC2_DATA3
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 26       : MMC2_DATA2
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 27       : MMC2_DATA1
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 28       : MMC2_DATA0
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 29       : EMAC_TX_CLK_OUT
	 * EMAC output tx clock
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 30       : EMAC_RX_CLK_IN
	 * EMAC input rx clock
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 31       : EMAC_COL
	 * EMAC Collision detect from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 32       : EMAC_CRS
	 * EMAC Carrier sense from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 33       : EMAC_TX_ER
	 * EMAC Transmit error signal to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 34       : EMAC_RX_ER
	 * EMAC Receive error signal from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 35       : EMAC_MDC
	 * EMAC Management data clock to pin
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 36       : EMAC_MDIO
	 * EMAC Management data input/out pin
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 37       : EMAC_RX_CTL
	 * EMAC Receive control signal from the PHY.
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 38       : EMAC_TX_CTL
	 * EMAC Transmit control signal to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 39       : EMAC_RX_D3
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 40       : EMAC_RX_D2
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 41       : EMAC_RX_D1
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 42       : EMAC_RX_D0
	 * EMAC Receive data from the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 43       : EMAC_TX_D3
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 44       : EMAC_TX_D2
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 45       : EMAC_TX_D1
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 46       : EMAC_TX_D0
	 * EMAC Transmit data to the PHY
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 47       : DVP_D0
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 48       : DVP_D1
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 49       : DVP_D2
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 50       : DVP_D3
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 51       : DVP_D4
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 52       : DVP_D5
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 53       : DVP_D6
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 54       : DVP_D7
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 55       : DVP_D8
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 56       : DVP_D9
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 57       : DVP_D10
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 58       : DVP_D11
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 59       : DVP_D12
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 60       : DVP_D13
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 61       : DVP_D14
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 62       : DVP_D15
	 * DVP interface data input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 63       : DVP_VSYNC
	 * DVP interface VSYNC input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 64       : DVP_HREF
	 * DVP interface HSYNC input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 65       : HSRESV21
	 * Used as DVP sensor power down pin ctrl, GPIO, DEN is not used，GPIO8
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 18
    },
	/*
	 * IO 66       : DVP_PCLK
	 * DVP interface clk input
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 67       : BT1120_OUT_DATA_D0
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 68       : BT1120_OUT_DATA_D1
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 69       : BT1120_OUT_DATA_D2
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 70       : BT1120_OUT_DATA_D3
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 71       : BT1120_OUT_DATA_D4
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 72       : BT1120_OUT_DATA_D5
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 73       : BT1120_OUT_DATA_D6
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 74       : BT1120_OUT_DATA_D7
	 * BT1120 interface output Y data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 75       : BT1120_OUT_DATA_C0
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 76       : BT1120_OUT_DATA_C1
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 77       : BT1120_OUT_DATA_C2
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 78       : BT1120_OUT_DATA_C3
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 79       : BT1120_OUT_DATA_C4
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 80       : BT1120_OUT_DATA_C5
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 81       : BT1120_OUT_DATA_C6
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 82       : BT1120_OUT_DATA_C7
	 * BT1120 interface output C data
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 83       : BT1120_OUT_CLK
	 * BT1120 interface output CLK
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 84       : BT1120_OUT_VSYNC
	 * BT1120 interface output VSYNC (Not necessary)
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 85       : BT1120_OUT_HSYNC
	 * BT1120 interface output HSYNC (Not necessary)
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 86       : SPI0_CLK
	 * SPI0_CLK
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 87       : SPI0_CS
	 * SPI0_CS
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 88       : SPI0_D0
	 * SPI0_D0
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 89       : SPI0_D1
	 * SPI0_D1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 90       : SPI0_D2
	 * SPI0_D2
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 91       : SPI0_D3
	 * SPI0_D3
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 92       : SPI0_D4
	 * SPI0_D4，SD DETECT，GPIO3 for lp4
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 93       : SPI0_D5
	 * SPI0_D5，USB OTG VBUS EN，GPIO2 for lp4
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 94       : SPI0_D6
	 * SPI0_D6
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 95       : SPI0_D7
	 * SPI0_D7
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * IO 96       : HSRESV0
	 * PMU AXP228，N_VBUSEN GPIO28
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 38
    },
	/*
	 * IO 97       : HSRESV1
	 * GNNE power supply，GNNE_SLEEP GPIO27
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 37
    },
	/*
	 * IO 98       : HSRESV2
	 * plug pin GPIO26
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 36
    },
	/*
	 * IO 99       : AUDIO_IN0
	 * plug pin GPIO25
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 35
    },
	/*
	 * IO 100      : HSRESV4
	 * plug pin GPIO24
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 34
    },
	/*
	 * IO 101      : HSRESV5
	 * plug pin GPIO23
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 33
    },
	/*
	 * IO 102      : HSRESV6
	 * plug pin GPIO22
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 32
    },
	/*
	 * IO 103      : AUDIO_IN_I2S_TDM_PDM_SCLK
	 * plug pin GPIO21
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 31
    },
	/*
	 * IO 104      : HSRESV8
	 * MIPI board CSI1 VSYNC on LP4 EVB, used as GPIO GPIO16
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 26
    },
	/*
	 * IO 105      : HSRESV9
	 * MIPI board CSI1 PowerDown on LP4 EVB, used as GPIO GPIO12
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 22
    },
	/*
	 * IO 106      : HSRESV10
	 * MIPI board CSI1 HSYNC on LP4 EVB, used as GPIO GPIO17
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 27
    },
	/*
	 * IO 107      : HSRESV11
	 * MIPI board CSI1 Reset on LP4 EVB, used as GPIO GPIO13
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 23
    },
	/*
	 * IO 108      : HSRESV12
	 * PCAL6416 INT, could still use GPIO 9. It&#x27;s DVP reset pin on LP4 EVB.
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 19
    },
	/*
	 * IO 109      : AUDIO_INOUT_I2S_WS
	 * MIC_WS ?
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 173
    },
	/*
	 * IO 110      : HSRESV14
	 * MIC_SCLK_PDM
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 189
    },
	/*
	 * IO 111      : HSRESV15
	 * MIC_DATA_PDM
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 147
    },
	/*
	 * IO 112      : HSRESV16
	 * uart0 rx
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 84
    },
	/*
	 * IO 113      : HSRESV17
	 * uart0 tx
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 90
    },
	/*
	 * IO 114      : HSRESV18
	 * PDMINDAT
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 175
    },
	/*
	 * IO 115      : HSRESV19
	 * PDMINCLK
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 177
    },
	/*
	 * IO 116      : DDR_BSR_TCK
	 * LP DDR3 EVB DVP/MIPI board SDA I2C2， IO94 for lp4
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 71
    },
	/*
	 * IO 117      : DDR_BSR_TDI
	 * LP DDR3 EVB DVP/MIPI board SCL I2C2， IO95 for lp4
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 70
    },
	/*
	 * IO 118      : DDR_BSR_TDO
	 * BT1120 board I2C SDA on LP3 EVB I2C1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 3,
	 .lsio_sel = 69
    },
	/*
	 * IO 119      : DDR_BSR_TMS
	 * BT1120 board I2C SCL on LP3 EVB I2C1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 3,
	 .lsio_sel = 68
    },
	/*
	 * IO 120      : DDR_BSR_TRSTN
	 * PCAL6416 reset，LED WS2812 GPIO20 for LP4
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 30
    },
	/*
	 * IO 121      : HSRESV20
	 * IIS_BCK_1V8
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 171
    },
	/*
	 * IO 122      : TEST_PIN0
	 * MIPI board CSI0 VSYNC on LP4 EVB, used as GPIO GPIO14
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 24
    },
	/*
	 * IO 123      : TEST_PIN1
	 * MIPI board CSI0 PowerDown on LP4 EVB, used as GPIO GPIO10
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 20
    },
	/*
	 * IO 124      : TEST_PIN2
	 * MIPI board CSI0 HSYNC on LP4 EVB, used as GPIO GPIO15
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 25
    },
	/*
	 * IO 125      : TEST_PIN3
	 * MIPI board CSI0 Reset on LP4 EVB, used as GPIO GPIO11
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 21
    },
	/*
	 * IO 126      : TEST_PIN4
	 * WIFI/BT RESET GPIO1
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 11
    },
	/*
	 * IO 127      : TEST_PIN5
	 * WIFI/BT INT GPIO0
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 10
    },
};
#endif
#if (defined _EVBLP3 || defined _EVBLP4)
void muxpin_default_init(void)
{
    /* skip bootctl and jtag pins */
    for (uint32_t i = 7; i < MUXPIN_NUM_IO; i++)
    {
        muxpin_set_config(i, &muxpin_default[i]);
    }
}
#endif