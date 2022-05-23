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
#include "muxpin.h"
#include "k510.h"
#include <stdio.h>

/*
 * NOTE: This file is automatic generated, do not edit directly.
 * Please edit the generator instead.
 */

/* FIXME: ideally this address should come from config string. */
volatile muxpin_t *const muxpin = (volatile muxpin_t *)IOMUX_BASE_ADDR;

/**
 * @brief      Internal used MUXPIN function initialize cell
 *
 *             This is NOT fpioa_io_config_t, can't assign directly
 *
 */

/* LSIO Function list */
static const muxpin_config_t function_config[(FUNC_MAX & MUXPIN_FUCTION_MASK) + 1] = {
	/*
	 * Internal function signal 0        : SPI1_D0
	 * SPI0 Data 0
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
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 1        : SPI1_D1
	 * SPI0 Data 1
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
	 .lsio_sel = 1
    },
	/*
	 * Internal function signal 2        : SPI1_D2
	 * SPI0 Data 2
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
	 .lsio_sel = 2
    },
	/*
	 * Internal function signal 3        : SPI1_D3
	 * SPI0 Data 3
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
	 .lsio_sel = 3
    },
	/*
	 * Internal function signal 4        : SPI1_D4
	 * SPI0 Data 4
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
	 .lsio_sel = 4
    },
	/*
	 * Internal function signal 5        : SPI1_D5
	 * SPI0 Data 5
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
	 .lsio_sel = 5
    },
	/*
	 * Internal function signal 6        : SPI1_D6
	 * SPI0 Data 6
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
	 .lsio_sel = 6
    },
	/*
	 * Internal function signal 7        : SPI1_D7
	 * SPI0 Data 7
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
	 .lsio_sel = 7
    },
	/*
	 * Internal function signal 8        : SPI1_SS0
	 * SPI0 Chip Select 0
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
	 .lsio_sel = 8
    },
	/*
	 * Internal function signal 9        : SPI1_SCLK
	 * SPI0 Serial Clock
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
	 .lsio_sel = 9
    },
	/*
	 * Internal function signal 10       : GPIO0
	 * GPIO pin 0
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
	/*
	 * Internal function signal 11       : GPIO1
	 * GPIO pin 1
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
	 * Internal function signal 12       : GPIO2
	 * GPIO pin 2
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
	 * Internal function signal 13       : GPIO3
	 * GPIO pin 3
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
	 * Internal function signal 14       : GPIO4
	 * GPIO pin 4
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
	 .lsio_sel = 14
    },
	/*
	 * Internal function signal 15       : GPIO5
	 * GPIO pin 5
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
	 .lsio_sel = 15
    },
	/*
	 * Internal function signal 16       : GPIO6
	 * GPIO pin 6
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
	 .lsio_sel = 16
    },
	/*
	 * Internal function signal 17       : GPIO7
	 * GPIO pin 7
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
	 .lsio_sel = 17
    },
	/*
	 * Internal function signal 18       : GPIO8
	 * GPIO pin 8
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
	 * Internal function signal 19       : GPIO9
	 * GPIO pin 9
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
	 * Internal function signal 20       : GPIO10
	 * GPIO pin 10
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
	 * Internal function signal 21       : GPIO11
	 * GPIO pin 11
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
	 * Internal function signal 22       : GPIO12
	 * GPIO pin 12
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
	 * Internal function signal 23       : GPIO13
	 * GPIO pin 13
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
	 * Internal function signal 24       : GPIO14
	 * GPIO pin 14
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
	 * Internal function signal 25       : GPIO15
	 * GPIO pin 15
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
	 * Internal function signal 26       : GPIO16
	 * GPIO pin 16
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
	 * Internal function signal 27       : GPIO17
	 * GPIO pin 17
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
	 * Internal function signal 28       : GPIO18
	 * GPIO pin 18
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
	 .lsio_sel = 28
    },
	/*
	 * Internal function signal 29       : GPIO19
	 * GPIO pin 19
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
	 .lsio_sel = 29
    },
	/*
	 * Internal function signal 30       : GPIO20
	 * GPIO pin 20
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
	 * Internal function signal 31       : GPIO21
	 * GPIO pin 21
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
	 * Internal function signal 32       : GPIO22
	 * GPIO pin 22
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
	 * Internal function signal 33       : GPIO23
	 * GPIO pin 23
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
	 * Internal function signal 34       : GPIO24
	 * GPIO pin 24
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
	 * Internal function signal 35       : GPIO25
	 * GPIO pin 25
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
	 * Internal function signal 36       : GPIO26
	 * GPIO pin 26
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
	 * Internal function signal 37       : GPIO27
	 * GPIO pin 27
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
	 * Internal function signal 38       : GPIO28
	 * GPIO pin 28
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
	 * Internal function signal 39       : GPIO29
	 * GPIO pin 29
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
	 .lsio_sel = 39
    },
	/*
	 * Internal function signal 40       : GPIO30
	 * GPIO pin 30
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
	 .lsio_sel = 40
    },
	/*
	 * Internal function signal 41       : GPIO31
	 * GPIO pin 31
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
	 .lsio_sel = 41
    },
	/*
	 * Internal function signal 42       : SPI2_D0
	 * SPI1 Data 0
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
	 .lsio_sel = 42
    },
	/*
	 * Internal function signal 43       : SPI2_D1
	 * SPI1 Data 1
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
	 .lsio_sel = 43
    },
	/*
	 * Internal function signal 44       : SPI2_D2
	 * SPI1 Data 2
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
	 .lsio_sel = 44
    },
	/*
	 * Internal function signal 45       : SPI2_D3
	 * SPI1 Data 3
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
	 .lsio_sel = 45
    },
	/*
	 * Internal function signal 46       : SPI2_D4
	 * SPI1 Data 4
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
	 .lsio_sel = 46
    },
	/*
	 * Internal function signal 47       : SPI2_D5
	 * SPI1 Data 5
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
	 .lsio_sel = 47
    },
	/*
	 * Internal function signal 48       : SPI2_D6
	 * SPI1 Data 6
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
	 .lsio_sel = 48
    },
	/*
	 * Internal function signal 49       : SPI2_D7
	 * SPI1 Data 7
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
	 .lsio_sel = 49
    },
	/*
	 * Internal function signal 50       : SPI2_SS0
	 * SPI1 Chip Select 0
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
	 .lsio_sel = 50
    },
	/*
	 * Internal function signal 51       : SPI2_SCLK
	 * SPI1 Serial Clock
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
	 .lsio_sel = 51
    },
	/*
	 * Internal function signal 52       : SPI_SLAVE_RXD
	 * SPI Slave RX data
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
	 .lsio_sel = 52
    },
	/*
	 * Internal function signal 53       : SPI_SLAVE_TXD
	 * SPI Slave TX data
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
	 .io_sel   = 3,
	 .lsio_sel = 53
    },
	/*
	 * Internal function signal 54       : SPI_SLAVE_SS
	 * SPI Slave Select
	 */
	{
	 .st       = 1,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 54
    },
	/*
	 * Internal function signal 55       : SPI_SLAVE_SCLK
	 * SPI Slave Serial Clock
	 */
	{
	 .st       = 1,
	 .ds       = 0x0,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 55
    },
	/*
	 * Internal function signal 56       : I2S2SCLK
	 * I2S0 Serial Clock(BCLK)
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
	 .lsio_sel = 56
    },
	/*
	 * Internal function signal 57       : I2S2WS
	 * I2S0 Word Select(LRCLK)
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
	 .lsio_sel = 57
    },
	/*
	 * Internal function signal 58       : I2S2IN_D0
	 * I2S0 Serial Data Input 0
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
	 .lsio_sel = 58
    },
	/*
	 * Internal function signal 59       : I2S2IN_D1
	 * I2S0 Serial Data Input 1
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
	 .lsio_sel = 59
    },
	/*
	 * Internal function signal 60       : I2S2IN_D2
	 * I2S0 Serial Data Input 2
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
	 .lsio_sel = 60
    },
	/*
	 * Internal function signal 61       : I2S2IN_D3
	 * I2S0 Serial Data Input 3
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
	 .lsio_sel = 61
    },
	/*
	 * Internal function signal 62       : I2S2OUT_D0
	 * I2S0 Serial Data Output 0
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
	 .lsio_sel = 62
    },
	/*
	 * Internal function signal 63       : I2S2OUT_D1
	 * I2S0 Serial Data Output 1
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
	 .lsio_sel = 63
    },
	/*
	 * Internal function signal 64       : I2S2OUT_D2
	 * I2S0 Serial Data Output 2
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
	 .lsio_sel = 64
    },
	/*
	 * Internal function signal 65       : I2S2OUT_D3
	 * I2S0 Serial Data Output 3
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
	 .lsio_sel = 65
    },
	/*
	 * Internal function signal 66       : I2C0_SCLK
	 * I2C0 Serial Clock
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
	 .lsio_sel = 66
    },
	/*
	 * Internal function signal 67       : I2C0_SDA
	 * I2C0 Serial Data
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
	 .lsio_sel = 67
    },
	/*
	 * Internal function signal 68       : I2C1_SCLK
	 * I2C1 Serial Clock
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
	 * Internal function signal 69       : I2C1_SDA
	 * I2C1 Serial Data
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
	 * Internal function signal 70       : I2C2_SCLK
	 * I2C2 Serial Clock
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
	 .lsio_sel = 70
    },
	/*
	 * Internal function signal 71       : I2C2_SDA
	 * I2C2 Serial Data
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
	 .lsio_sel = 71
    },
	/*
	 * Internal function signal 72       : I2C3_SCLK
	 * I2C3 Serial Clock
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
	 .lsio_sel = 72
    },
	/*
	 * Internal function signal 73       : I2C3_SDA
	 * I2C3 Serial Data
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
	 .lsio_sel = 73
    },
	/*
	 * Internal function signal 74       : I2C4_SCLK
	 * I2C4 Serial Clock
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
	 .lsio_sel = 74
    },
	/*
	 * Internal function signal 75       : I2C4_SDA
	 * I2C4 Serial Data
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
	 .lsio_sel = 75
    },
	/*
	 * Internal function signal 76       : I2C5_SCLK
	 * I2C5 Serial Clock
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
	 .lsio_sel = 76
    },
	/*
	 * Internal function signal 77       : I2C5_SDA
	 * I2C5 Serial Data
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
	 .lsio_sel = 77
    },
	/*
	 * Internal function signal 78       : I2C6_SCLK
	 * I2C6 Serial Clock
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
	 .lsio_sel = 78
    },
	/*
	 * Internal function signal 79       : I2C6_SDA
	 * I2C6 Serial Data
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
	 .lsio_sel = 79
    },
	/*
	 * Internal function signal 80       : UART0_CTS
	 * UART1 Clear To Send
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
	 .lsio_sel = 80
    },
	/*
	 * Internal function signal 81       : UART0_DSR
	 * UART1 Data Set Ready
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
	 .lsio_sel = 81
    },
	/*
	 * Internal function signal 82       : UART0_DCD
	 * UART1 Data Carrier Detect
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
	 .lsio_sel = 82
    },
	/*
	 * Internal function signal 83       : UART0_RI
	 * UART1 Ring Indicator
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
	 .lsio_sel = 83
    },
	/*
	 * Internal function signal 84       : UART0_SIN
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 84
    },
	/*
	 * Internal function signal 85       : UART0_SIR_IN
	 * UART1 Serial Infrared Input
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
	 .lsio_sel = 85
    },
	/*
	 * Internal function signal 86       : UART0_DTR
	 * UART1 Data Terminal Ready
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 86
    },
	/*
	 * Internal function signal 87       : UART0_RTS
	 * UART1 Request To Send
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
	 .lsio_sel = 87
    },
	/*
	 * Internal function signal 88       : UART0_OUT2
	 * UART1 User-designated Output 2
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 88
    },
	/*
	 * Internal function signal 89       : UART0_OUT1
	 * UART1 User-designated Output 1
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 89
    },
	/*
	 * Internal function signal 90       : UART0_SOUT
	 *
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
	 * Internal function signal 91       : UART0_SIR_OUT
	 * UART1 Serial Infrared Output
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
	 .lsio_sel = 91
    },
	/*
	 * Internal function signal 92       : UART0_BAUD
	 * UART1 Transmit Clock Output
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 0,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 92
    },
	/*
	 * Internal function signal 93       : UART0_RE
	 * UART1 Receiver Output Enable
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
	 .lsio_sel = 93
    },
	/*
	 * Internal function signal 94       : UART0_DE
	 * UART1 Driver Output Enable
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
	 .lsio_sel = 94
    },
	/*
	 * Internal function signal 95       : UART0_RS485_EN
	 * UART1 RS485 Enable
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
	 .lsio_sel = 95
    },
	/*
	 * Internal function signal 96       : UART1_CTS
	 * UART2 Clear To Send
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
	 .lsio_sel = 96
    },
	/*
	 * Internal function signal 97       : UART1_DSR
	 * UART2 Data Set Ready
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
	 .lsio_sel = 97
    },
	/*
	 * Internal function signal 98       : UART1_DCD
	 * UART2 Data Carrier Detect
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
	 .lsio_sel = 98
    },
	/*
	 * Internal function signal 99       : UART1_RI
	 * UART2 Ring Indicator
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
	 .lsio_sel = 99
    },
	/*
	 * Internal function signal 100      : UART1_SIN
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 100
    },
	/*
	 * Internal function signal 101      : UART1_SIR_IN
	 * UART2 Serial Infrared Input
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
	 .lsio_sel = 101
    },
	/*
	 * Internal function signal 102      : UART1_DTR
	 * UART2 Data Terminal Ready
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
	 .lsio_sel = 102
    },
	/*
	 * Internal function signal 103      : UART1_RTS
	 * UART2 Request To Send
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
	 .lsio_sel = 103
    },
	/*
	 * Internal function signal 104      : UART1_OUT2
	 * UART2 User-designated Output 2
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
	 .lsio_sel = 104
    },
	/*
	 * Internal function signal 105      : UART1_OUT1
	 * UART2 User-designated Output 1
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
	 .lsio_sel = 105
    },
	/*
	 * Internal function signal 106      : UART1_SOUT
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 106
    },
	/*
	 * Internal function signal 107      : UART1_SIR_OUT
	 * UART2 Serial Infrared Output
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
	 .lsio_sel = 107
    },
	/*
	 * Internal function signal 108      : UART1_BAUD
	 * UART2 Transmit Clock Output
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
	 .lsio_sel = 108
    },
	/*
	 * Internal function signal 109      : UART1_RE
	 * UART2 Receiver Output Enable
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
	 .lsio_sel = 109
    },
	/*
	 * Internal function signal 110      : UART1_DE
	 * UART2 Driver Output Enable
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
	 .lsio_sel = 110
    },
	/*
	 * Internal function signal 111      : UART1_RS485_EN
	 * UART2 RS485 Enable
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
	 .lsio_sel = 111
    },
	/*
	 * Internal function signal 112      : UART2_CTS
	 * UART3 Clear To Send
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
	 .lsio_sel = 112
    },
	/*
	 * Internal function signal 113      : UART2_DSR
	 * UART3 Data Set Ready
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
	 .lsio_sel = 113
    },
	/*
	 * Internal function signal 114      : UART2_DCD
	 * UART3 Data Carrier Detect
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
	 .lsio_sel = 114
    },
	/*
	 * Internal function signal 115      : UART2_RI
	 * UART3 Ring Indicator
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
	 .lsio_sel = 115
    },
	/*
	 * Internal function signal 116      : UART2_SIN
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 116
    },
	/*
	 * Internal function signal 117      : UART2_SIR_IN
	 * UART3 Serial Infrared Input
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
	 .lsio_sel = 117
    },
	/*
	 * Internal function signal 118      : UART2_DTR
	 * UART3 Data Terminal Ready
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
	 .lsio_sel = 118
    },
	/*
	 * Internal function signal 119      : UART2_RTS
	 * UART3 Request To Send
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
	 .lsio_sel = 119
    },
	/*
	 * Internal function signal 120      : UART2_OUT2
	 * UART3 User-designated Output 2
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
	 .lsio_sel = 120
    },
	/*
	 * Internal function signal 121      : UART2_OUT1
	 * UART3 User-designated Output 1
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
	 .lsio_sel = 121
    },
	/*
	 * Internal function signal 122      : UART2_SOUT
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 122
    },
	/*
	 * Internal function signal 123      : UART2_SIR_OUT
	 * UART3 Serial Infrared Output
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
	 .lsio_sel = 123
    },
	/*
	 * Internal function signal 124      : UART2_BAUD
	 * UART3 Transmit Clock Output
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
	 .lsio_sel = 124
    },
	/*
	 * Internal function signal 125      : UART2_RE
	 * UART3 Receiver Output Enable
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
	 .lsio_sel = 125
    },
	/*
	 * Internal function signal 126      : UART2_DE
	 * UART3 Driver Output Enable
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
	 .lsio_sel = 126
    },
	/*
	 * Internal function signal 127      : UART2_RS485_EN
	 * UART3 RS485 Enable
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
	 .lsio_sel = 127
    },
	/*
	 * Internal function signal 128      : UART3_CTS
	 * UART3 Clear To Send
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
	 .lsio_sel = 128
    },
	/*
	 * Internal function signal 129      : UART3_DSR
	 * UART3 Data Set Ready
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
	 .lsio_sel = 129
    },
	/*
	 * Internal function signal 130      : UART3_DCD
	 * UART3 Data Carrier Detect
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
	 .lsio_sel = 130
    },
	/*
	 * Internal function signal 131      : UART3_RI
	 * UART3 Ring Indicator
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
	 .lsio_sel = 131
    },
	/*
	 * Internal function signal 132      : UART3_SIN
	 *
	 */
	{
	 .st       = 1,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 0,
	 .ie_en    = 1,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 132
    },
	/*
	 * Internal function signal 133      : UART3_SIR_IN
	 * UART3 Serial Infrared Input
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
	 .lsio_sel = 133
    },
	/*
	 * Internal function signal 134      : UART3_DTR
	 * UART3 Data Terminal Ready
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
	 .lsio_sel = 134
    },
	/*
	 * Internal function signal 135      : UART3_RTS
	 * UART3 Request To Send
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
	 .lsio_sel = 135
    },
	/*
	 * Internal function signal 136      : UART3_OUT2
	 * UART3 User-designated Output 2
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
	 .lsio_sel = 136
    },
	/*
	 * Internal function signal 137      : UART3_OUT1
	 * UART3 User-designated Output 1
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
	 .lsio_sel = 137
    },
	/*
	 * Internal function signal 138      : UART3_SOUT
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 1,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 0,
	 .io_sel   = 3,
	 .lsio_sel = 138
    },
	/*
	 * Internal function signal 139      : UART3_SIR_OUT
	 * UART3 Serial Infrared Output
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
	 .lsio_sel = 139
    },
	/*
	 * Internal function signal 140      : UART3_BAUD
	 * UART3 Transmit Clock Output
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
	 .lsio_sel = 140
    },
	/*
	 * Internal function signal 141      : UART3_RE
	 * UART3 Receiver Output Enable
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
	 .lsio_sel = 141
    },
	/*
	 * Internal function signal 142      : UART3_DE
	 * UART3 Driver Output Enable
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
	 .lsio_sel = 142
    },
	/*
	 * Internal function signal 143      : UART3_RS485_EN
	 * UART3 RS485 Enable
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
	 .lsio_sel = 143
    },
	/*
	 * Internal function signal 144      : CLK_SPI2
	 * Clock SPI2
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
	 .lsio_sel = 144
    },
	/*
	 * Internal function signal 145      : CLK_I2C2
	 * Clock I2C2
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
	 .lsio_sel = 145
    },
	/*
	 * Internal function signal 146      : AUDIO_OUT_TDM_FSYNC
	 * TDM OUT FSYNC, pull down on evb board
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
	 .lsio_sel = 146
    },
	/*
	 * Internal function signal 147      : AUDIO_IN0
	 * audio data in
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
	 * Internal function signal 148      : AUDIO_IN1
	 * audio data in
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
	 .lsio_sel = 148
    },
	/*
	 * Internal function signal 149      : AUDIO_IN2
	 * audio data in
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
	 .lsio_sel = 149
    },
	/*
	 * Internal function signal 150      : AUDIO_IN3
	 * audio data in
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
	 .lsio_sel = 150
    },
	/*
	 * Internal function signal 151      : AUDIO_IN4
	 * audio data in
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
	 .lsio_sel = 151
    },
	/*
	 * Internal function signal 152      : AUDIO_IN5
	 * audio data in
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
	 .lsio_sel = 152
    },
	/*
	 * Internal function signal 153      : AUDIO_IN6
	 * audio data in
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
	 .lsio_sel = 153
    },
	/*
	 * Internal function signal 154      : AUDIO_IN7
	 * audio data in
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
	 .lsio_sel = 154
    },
	/*
	 * Internal function signal 155      : AUDIO_IN8
	 * audio data in
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
	 .lsio_sel = 155
    },
	/*
	 * Internal function signal 156      : AUDIO_IN9
	 * audio data in
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
	 .lsio_sel = 156
    },
	/*
	 * Internal function signal 157      : AUDIO_IN10
	 * audio data in
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
	 .lsio_sel = 157
    },
	/*
	 * Internal function signal 158      : AUDIO_IN11
	 * audio data in
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
	 .lsio_sel = 158
    },
	/*
	 * Internal function signal 159      : AUDIO_IN12
	 * audio data in
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
	 .lsio_sel = 159
    },
	/*
	 * Internal function signal 160      : AUDIO_IN13
	 * audio data in
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
	 .lsio_sel = 160
    },
	/*
	 * Internal function signal 161      : AUDIO_IN14
	 * audio data in
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
	 .lsio_sel = 161
    },
	/*
	 * Internal function signal 162      : AUDIO_IN15
	 * audio data in
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
	 .lsio_sel = 162
    },
	/*
	 * Internal function signal 163      : AUDIO_OUT0
	 * audio data out
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
	 * Internal function signal 164      : AUDIO_OUT1
	 * audio data out
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
	 .lsio_sel = 164
    },
	/*
	 * Internal function signal 165      : AUDIO_OUT2
	 * audio data out
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
	 .lsio_sel = 165
    },
	/*
	 * Internal function signal 166      : AUDIO_OUT3
	 * audio data out
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
	 .lsio_sel = 166
    },
	/*
	 * Internal function signal 167      : AUDIO_OUT4
	 * audio data out
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
	 .lsio_sel = 167
    },
	/*
	 * Internal function signal 168      : AUDIO_OUT5
	 * audio data out
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
	 .lsio_sel = 168
    },
	/*
	 * Internal function signal 169      : AUDIO_OUT6
	 * audio data out
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
	 .lsio_sel = 169
    },
	/*
	 * Internal function signal 170      : AUDIO_OUT7
	 * audio data out
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
	 .lsio_sel = 170
    },
	/*
	 * Internal function signal 171      : AUDIO_INOUT_I2S_SCLK_GATE
	 * audio i2s sclk output (for data in and data out)
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
	 .io_sel   = 3,
	 .lsio_sel = 171
    },
	/*
	 * Internal function signal 172      : AUDIO_OUT_I2S_SCLK_EN
	 * not used
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
	 .lsio_sel = 172
    },
	/*
	 * Internal function signal 173      : AUDIO_INOUT_I2S_WS
	 * audio i2s ws output (for data in and data out)
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
	 .io_sel   = 3,
	 .lsio_sel = 173
    },
	/*
	 * Internal function signal 174      : AUDIO_IN_TDM_FSYNC
	 * TDM IN FSYNC
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
	 .lsio_sel = 174
    },
	/*
	 * Internal function signal 175      : VAD_IN_DATA
	 *
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
	 .lsio_sel = 175
    },
	/*
	 * Internal function signal 176      : VAD_FSYNC
	 *
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
	 .lsio_sel = 176
    },
	/*
	 * Internal function signal 177      : VAD_DEV_SCLK
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
	 .io_sel   = 3,
	 .lsio_sel = 177
    },
	/*
	 * Internal function signal 178      : PWM_PINS_1_IO_PINS_PWM_0_O_OVAL
	 *
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
	 .lsio_sel = 178
    },
	/*
	 * Internal function signal 179      : PWM_PINS_1_IO_PINS_PWM_1_O_OVAL
	 *
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
	 .lsio_sel = 179
    },
	/*
	 * Internal function signal 180      : PWM_PINS_1_IO_PINS_PWM_2_O_OVAL
	 *
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
	 .lsio_sel = 180
    },
	/*
	 * Internal function signal 181      : PWM_PINS_1_IO_PINS_PWM_3_O_OVAL
	 *
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
	 .lsio_sel = 181
    },
	/*
	 * Internal function signal 182      : PWM_PINS_1_IO_PINS_PWM_4_O_OVAL
	 *
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
	 .lsio_sel = 182
    },
	/*
	 * Internal function signal 183      : PWM_PINS_1_IO_PINS_PWM_5_O_OVAL
	 *
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
	 .lsio_sel = 183
    },
	/*
	 * Internal function signal 184      : PWM_PINS_1_IO_PINS_PWM_6_O_OVAL
	 *
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
	 .lsio_sel = 184
    },
	/*
	 * Internal function signal 185      : PWM_PINS_1_IO_PINS_PWM_7_O_OVAL
	 *
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
	 .lsio_sel = 185
    },
	/*
	 * Internal function signal 186      : I2C2AXI_SCLK
	 *
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
	 .lsio_sel = 186
    },
	/*
	 * Internal function signal 187      : I2C2AXI_SDA
	 *
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
	 .lsio_sel = 187
    },
	/*
	 * Internal function signal 188      : AUDIO_OUT_TDM_SCLK
	 * TDM OUT SCLK
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
	 .lsio_sel = 188
    },
	/*
	 * Internal function signal 189      : AUDIO_OUT_PDM_SCLK
	 * PDM OUT SCLK
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
	 * Internal function signal 190      : AUDIO_IN_TDM_PDM_SCLK
	 * TDM or PDM in sclk
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
	 .io_sel   = 3,
	 .lsio_sel = 190
    },
	/*
	 * Internal function signal 191      : LSRESV6
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 191
    },
	/*
	 * Internal function signal 192      : LSRESV7
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 192
    },
	/*
	 * Internal function signal 193      : LSRESV8
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 193
    },
	/*
	 * Internal function signal 194      : LSRESV9
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 194
    },
	/*
	 * Internal function signal 195      : LSRESV10
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 195
    },
	/*
	 * Internal function signal 196      : LSRESV11
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 196
    },
	/*
	 * Internal function signal 197      : LSRESV12
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 197
    },
	/*
	 * Internal function signal 198      : LSRESV13
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 198
    },
	/*
	 * Internal function signal 199      : LSRESV14
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 199
    },
	/*
	 * Internal function signal 200      : LSRESV15
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 200
    },
	/*
	 * Internal function signal 201      : LSRESV16
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 201
    },
	/*
	 * Internal function signal 202      : LSRESV17
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 202
    },
	/*
	 * Internal function signal 203      : LSRESV18
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 203
    },
	/*
	 * Internal function signal 204      : LSRESV19
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 204
    },
	/*
	 * Internal function signal 205      : LSRESV20
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 205
    },
	/*
	 * Internal function signal 206      : LSRESV21
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 206
    },
	/*
	 * Internal function signal 207      : LSRESV22
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 207
    },
	/*
	 * Internal function signal 208      : LSRESV23
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 208
    },
	/*
	 * Internal function signal 209      : LSRESV24
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 209
    },
	/*
	 * Internal function signal 210      : LSRESV25
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 210
    },
	/*
	 * Internal function signal 211      : LSRESV26
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 211
    },
	/*
	 * Internal function signal 212      : LSRESV27
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 212
    },
	/*
	 * Internal function signal 213      : LSRESV28
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 213
    },
	/*
	 * Internal function signal 214      : LSRESV29
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 214
    },
	/*
	 * Internal function signal 215      : LSRESV30
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 215
    },
	/*
	 * Internal function signal 216      : LSRESV31
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 216
    },
	/*
	 * Internal function signal 217      : LSRESV32
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 217
    },
	/*
	 * Internal function signal 218      : LSRESV33
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 218
    },
	/*
	 * Internal function signal 219      : LSRESV34
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 219
    },
	/*
	 * Internal function signal 220      : LSRESV35
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 220
    },
	/*
	 * Internal function signal 221      : LSRESV36
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 221
    },
	/*
	 * Internal function signal 222      : LSRESV37
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 222
    },
	/*
	 * Internal function signal 223      : LSRESV38
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 223
    },
	/*
	 * Internal function signal 224      : LSRESV39
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 224
    },
	/*
	 * Internal function signal 225      : LSRESV40
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 225
    },
	/*
	 * Internal function signal 226      : LSRESV41
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 226
    },
	/*
	 * Internal function signal 227      : LSRESV42
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 227
    },
	/*
	 * Internal function signal 228      : LSRESV43
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 228
    },
	/*
	 * Internal function signal 229      : LSRESV44
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 229
    },
	/*
	 * Internal function signal 230      : LSRESV45
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 230
    },
	/*
	 * Internal function signal 231      : LSRESV46
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 231
    },
	/*
	 * Internal function signal 232      : LSRESV47
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 232
    },
	/*
	 * Internal function signal 233      : LSRESV48
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 233
    },
	/*
	 * Internal function signal 234      : LSRESV49
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 234
    },
	/*
	 * Internal function signal 235      : LSRESV50
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 235
    },
	/*
	 * Internal function signal 236      : LSRESV51
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 236
    },
	/*
	 * Internal function signal 237      : LSRESV52
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 237
    },
	/*
	 * Internal function signal 238      : LSRESV53
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 238
    },
	/*
	 * Internal function signal 239      : LSRESV54
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 239
    },
	/*
	 * Internal function signal 240      : LSRESV55
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 240
    },
	/*
	 * Internal function signal 241      : LSRESV56
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 241
    },
	/*
	 * Internal function signal 242      : LSRESV57
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 242
    },
	/*
	 * Internal function signal 243      : LSRESV58
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 243
    },
	/*
	 * Internal function signal 244      : LSRESV59
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 244
    },
	/*
	 * Internal function signal 245      : LSRESV60
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 245
    },
	/*
	 * Internal function signal 246      : LSRESV61
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 246
    },
	/*
	 * Internal function signal 247      : LSRESV62
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 247
    },
	/*
	 * Internal function signal 248      : LSRESV63
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 248
    },
	/*
	 * Internal function signal 249      : LSRESV64
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 249
    },
	/*
	 * Internal function signal 250      : LSRESV65
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 250
    },
	/*
	 * Internal function signal 251      : LSRESV66
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 251
    },
	/*
	 * Internal function signal 252      : LSRESV67
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 252
    },
	/*
	 * Internal function signal 253      : LSRESV68
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 253
    },
	/*
	 * Internal function signal 254      : LSRESV69
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 254
    },
	/*
	 * Internal function signal 255      : LSRESV_MAX
	 *
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
	 .io_sel   = 3,
	 .lsio_sel = 255
    },
	/*
	 * Internal function signal 256      : BOOT_CTL1
	 *
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
	 * Internal function signal 257      : BOOT_CTL0
	 *
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
	 * Internal function signal 258      : JTAG_TCK
	 *
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
	 * Internal function signal 259      : JTAG_TDI
	 *
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
	 * Internal function signal 260      : JTAG_TDO
	 *
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
	 * Internal function signal 261      : JTAG_TMS
	 *
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
	 * Internal function signal 262      : JTAG_TRSTN
	 *
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
	 * Internal function signal 263      : MMC0_CLK
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
	 * Internal function signal 264      : MMC0_CMD
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
	 * Internal function signal 265      : MMC0_DATA7
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
	 * Internal function signal 266      : MMC0_DATA6
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
	 * Internal function signal 267      : MMC0_DATA5
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
	 * Internal function signal 268      : MMC0_DATA4
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
	 * Internal function signal 269      : MMC0_DATA3
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
	 * Internal function signal 270      : MMC0_DATA2
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
	 * Internal function signal 271      : MMC0_DATA1
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
	 * Internal function signal 272      : MMC0_DATA0
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
	 * Internal function signal 273      : MMC1_CLK
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
	 * Internal function signal 274      : MMC1_CMD
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
	 * Internal function signal 275      : MMC1_DATA3
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
	 * Internal function signal 276      : MMC1_DATA2
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
	 * Internal function signal 277      : MMC1_DATA1
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
	 * Internal function signal 278      : MMC1_DATA0
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
	 * Internal function signal 279      : MMC2_CLK
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
	 * Internal function signal 280      : MMC2_CMD
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
	 * Internal function signal 281      : MMC2_DATA3
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
	 * Internal function signal 282      : MMC2_DATA2
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
	 * Internal function signal 283      : MMC2_DATA1
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
	 * Internal function signal 284      : MMC2_DATA0
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
	 * Internal function signal 285      : MMC_SLV_CLK
	 *
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
	 .io_sel   = 1,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 286      : MMC_SLV_CMD
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
	 .io_sel   = 1,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 287      : MMC_SLV_DATA3
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
	 .io_sel   = 1,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 288      : MMC_SLV_DATA2
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
	 .io_sel   = 1,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 289      : MMC_SLV_DATA1
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
	 .io_sel   = 1,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 290      : MMC_SLV_DATA0
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
	 .io_sel   = 1,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 291      : EMAC_TX_CLK_OUT
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
	 * Internal function signal 292      : EMAC_TX_CLK_IN
	 * EMAC input tx clock
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
	 * Internal function signal 293      : EMAC_REF_OUT
	 * EMAC RMII output ref clock
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
	 * Internal function signal 294      : EMAC_REF_IN
	 * EMAC RMII input erf clock
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
	 * Internal function signal 295      : EMAC_RX_CLK_OUT
	 * EMAC output rx clock
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
	 * Internal function signal 296      : EMAC_RX_CLK_IN
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
	 * Internal function signal 297      : EMAC_COL
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
	 * Internal function signal 298      : EMAC_CRS
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
	 * Internal function signal 299      : EMAC_TX_ER
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
	 * Internal function signal 300      : EMAC_RX_ER
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
	 * Internal function signal 301      : EMAC_MDC
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
	 * Internal function signal 302      : EMAC_MDIO
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
	 * Internal function signal 303      : EMAC_RX_CTL
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
	 * Internal function signal 304      : EMAC_RX_DV
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
	 * Internal function signal 305      : EMAC_TX_CTL
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
	 * Internal function signal 306      : EMAC_TX_EN
	 * EMAC Transmit enable to the PHY
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
	 * Internal function signal 307      : EMAC_RX_D3
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
	 * Internal function signal 308      : EMAC_RX_D2
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
	 * Internal function signal 309      : EMAC_RX_D1
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
	 * Internal function signal 310      : EMAC_RX_D0
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
	 * Internal function signal 311      : EMAC_TX_D3
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
	 * Internal function signal 312      : EMAC_TX_D2
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
	 * Internal function signal 313      : EMAC_TX_D1
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
	 * Internal function signal 314      : EMAC_TX_D0
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
	 * Internal function signal 315      : DVP_D0
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
	 * Internal function signal 316      : DVP_D1
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
	 * Internal function signal 317      : DVP_D2
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
	 * Internal function signal 318      : DVP_D3
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
	 * Internal function signal 319      : DVP_D4
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
	 * Internal function signal 320      : DVP_D5
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
	 * Internal function signal 321      : DVP_D6
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
	 * Internal function signal 322      : DVP_D7
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
	 * Internal function signal 323      : DVP_D8
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
	 * Internal function signal 324      : DVP_D9
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
	 * Internal function signal 325      : DVP_D10
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
	 * Internal function signal 326      : DVP_D11
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
	 * Internal function signal 327      : DVP_D12
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
	 * Internal function signal 328      : DVP_D13
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
	 * Internal function signal 329      : DVP_D14
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
	 * Internal function signal 330      : DVP_D15
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
	 * Internal function signal 331      : DVP_VSYNC
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
	 * Internal function signal 332      : DVP_HREF
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
	 * Internal function signal 333      : HSRESV21
	 *
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
	 * Internal function signal 334      : DVP_PCLK
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
	 * Internal function signal 335      : BT1120_OUT_DATA_D0
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
	 * Internal function signal 336      : BT1120_OUT_DATA_D1
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
	 * Internal function signal 337      : BT1120_OUT_DATA_D2
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
	 * Internal function signal 338      : BT1120_OUT_DATA_D3
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
	 * Internal function signal 339      : BT1120_OUT_DATA_D4
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
	 * Internal function signal 340      : BT1120_OUT_DATA_D5
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
	 * Internal function signal 341      : BT1120_OUT_DATA_D6
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
	 * Internal function signal 342      : BT1120_OUT_DATA_D7
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
	 * Internal function signal 343      : BT1120_OUT_DATA_C0
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
	 * Internal function signal 344      : BT1120_OUT_DATA_C1
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
	 * Internal function signal 345      : BT1120_OUT_DATA_C2
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
	 * Internal function signal 346      : BT1120_OUT_DATA_C3
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
	 * Internal function signal 347      : BT1120_OUT_DATA_C4
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
	 * Internal function signal 348      : BT1120_OUT_DATA_C5
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
	 * Internal function signal 349      : BT1120_OUT_DATA_C6
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
	 * Internal function signal 350      : BT1120_OUT_DATA_C7
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
	 * Internal function signal 351      : BT1120_OUT_CLK
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
	 * Internal function signal 352      : BT1120_OUT_VSYNC
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
	 * Internal function signal 353      : BT1120_OUT_HSYNC
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
	 * Internal function signal 354      : SPI0_CLK
	 *
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
	 * Internal function signal 355      : SPI0_CS
	 *
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
	 * Internal function signal 356      : SPI0_D0
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
	 * Internal function signal 357      : SPI0_D1
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
	 * Internal function signal 358      : SPI0_D2
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
	 * Internal function signal 359      : SPI0_D3
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
	 * Internal function signal 360      : SPI0_D4
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
	 * Internal function signal 361      : SPI0_D5
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
	 * Internal function signal 362      : SPI0_D6
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
	 * Internal function signal 363      : SPI0_D7
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
	 * Internal function signal 364      : HSRESV0
	 *
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
	 * Internal function signal 365      : HSRESV1
	 *
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
	 * Internal function signal 366      : HSRESV2
	 *
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
	 * Internal function signal 367      : HSRESV3
	 *
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
	 * Internal function signal 368      : HSRESV4
	 *
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
	 * Internal function signal 369      : HSRESV5
	 *
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
	 * Internal function signal 370      : HSRESV6
	 *
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
	 * Internal function signal 371      : HSRESV7
	 *
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
	 * Internal function signal 372      : HSRESV8
	 *
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
	 * Internal function signal 373      : HSRESV9
	 *
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
	 * Internal function signal 374      : HSRESV10
	 *
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
	 * Internal function signal 375      : HSRESV11
	 *
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
	 * Internal function signal 376      : HSRESV12
	 *
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
	 * Internal function signal 377      : HSRESV13
	 *
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
	 * Internal function signal 378      : HSRESV14
	 *
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
	 * Internal function signal 379      : HSRESV15
	 *
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
	 * Internal function signal 380      : HSRESV16
	 *
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
	 * Internal function signal 381      : HSRESV17
	 *
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
	 * Internal function signal 382      : HSRESV18
	 *
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
	 * Internal function signal 383      : HSRESV19
	 *
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
	 * Internal function signal 384      : DDR_BSR_TCK
	 *
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
	 * Internal function signal 385      : DDR_BSR_TDI
	 *
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
	 * Internal function signal 386      : DDR_BSR_TDO
	 *
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
	 * Internal function signal 387      : DDR_BSR_TMS
	 *
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
	 * Internal function signal 388      : DDR_BSR_TRSTN
	 *
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
	 * Internal function signal 389      : HSRESV20
	 *
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
	 * Internal function signal 390      : TEST_PIN0
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 391      : TEST_PIN1
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 392      : TEST_PIN2
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 393      : TEST_PIN3
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 394      : TEST_PIN4
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 395      : TEST_PIN5
	 *
	 */
	{
	 .st       = 0,
	 .ds       = 0x7,
	 .pd       = 0,
	 .pu       = 0,
	 .oe_en    = 1,
	 .ie_en    = 0,
	 .msc      = 1,
	 .sl       = 1,
	 .io_sel   = 0,
	 .lsio_sel = 0
    },
	/*
	 * Internal function signal 396      : MAX
	 *
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
};

int muxpin_init(void)
{
	/* Enable muxpin clock in system controller */
	//sysctl_clock_enable(SYSCTL_CLOCK_MUXPIN);
    for(uint32_t i = 0; i < MUXPIN_NUM_IO; i++)
    {
        muxpin_set_function(i, FUNC_LSRESV_MAX);
    }
	return 0;
}

__attribute__((weak)) void muxpin_default_init(void)
{
    return ;
}

int muxpin_get_config(int number, muxpin_config_t *cfg)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO || cfg == NULL)
		return -1;
	/* Atomic read register */
	*cfg = muxpin->io[number];
	return 0;
}

int muxpin_set_config(int number, muxpin_config_t *cfg)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO || cfg == NULL)
		return -1;
	/* Atomic write register */
	muxpin->io[number] = *cfg;
	return 0;
}

int muxpin_set_io_pull(int number, muxpin_pull_t pull)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO || pull >= MUXPIN_PULL_MAX)
		return -1;

	/* Atomic read register */
	muxpin_config_t cfg = muxpin->io[number];

	switch (pull) {
	case MUXPIN_PULL_NONE:
		cfg.pu = 0;
		cfg.pd = 0;
		break;
	case MUXPIN_PULL_DOWN:
		cfg.pu = 0;
		cfg.pd = 1;
		break;
	case MUXPIN_PULL_UP:
		cfg.pu = 1;
		cfg.pd = 0;
		break;
	default:
		break;
	}
	/* Atomic write register */
	muxpin->io[number] = cfg;
	return 0;
}

int muxpin_get_io_pull(int number)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO)
		return -1;

	muxpin_pull_t pull;
	/* Atomic read register */
	muxpin_config_t cfg = muxpin->io[number];

	if (cfg.pu == 0 && cfg.pd == 1)
		pull = MUXPIN_PULL_DOWN;
	else if (cfg.pu == 1 && cfg.pd == 0)
		pull = MUXPIN_PULL_UP;
	else
		pull = MUXPIN_PULL_NONE;
	return pull;
}

int muxpin_set_io_driving(int number, muxpin_driving_t driving)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO || driving >= MUXPIN_DRIVING_MAX)
		return -1;

	/* Atomic read register */
	muxpin_config_t cfg = muxpin->io[number];
	/* Set IO driving */
	cfg.ds = driving;
	/* Atomic write register */
	muxpin->io[number] = cfg;
	return 0;
}

int muxpin_get_io_driving(int number)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO)
		return -1;

	return muxpin->io[number].ds;
}

int muxpin_set_function_raw(int number, muxpin_function_t function)
{
	/* Check parameters */
	if (number < 0 || number >= MUXPIN_NUM_IO)
		return -1;

	if((function & MUXPIN_FUCTION_MASK) > FUNC_LSRESV_MAX) /* High speed pin */
	{
		if(number != (function & MUXPIN_IONUM_MASK) >> 16)
		{
			printf("Warning:> Pin num %d, but want %d\n", number, (function & MUXPIN_IONUM_MASK) >> 16);
		}
		number = (function & MUXPIN_IONUM_MASK) >> 16;
		function = function & MUXPIN_FUCTION_MASK;
	}
	/* Atomic write register */
	muxpin->io[number] = (const muxpin_config_t) {
        .lsio_sel = function_config[function].lsio_sel,
		.io_sel = function_config[function].io_sel,
		.ds     = function_config[function].ds,
		.oe_en  = function_config[function].oe_en,
		.pu     = function_config[function].pu,
		.pd     = function_config[function].pd,
		.sl     = function_config[function].sl,
		.ie_en  = function_config[function].ie_en,
		.st     = function_config[function].st,
		.msc    = function_config[function].msc,
		/* resv and pad_di do not need initialization */
	};
	return 0;
}

int muxpin_set_function(int number, muxpin_function_t function)
{
    uint8_t index;
    /* Check parameters */
    if (number < 0 || number >= MUXPIN_NUM_IO)
        return -1;

    if (function == FUNC_LSRESV_MAX) {
        muxpin_set_function_raw(number, FUNC_LSRESV_MAX);
        return 0;
    }

    if((function & MUXPIN_FUCTION_MASK) < FUNC_LSRESV_MAX)  /* Low speed pin */
    {
        if((function != FUNC_AUDIO_INOUT_I2S_SCLK_GATE) && (function != FUNC_AUDIO_INOUT_I2S_WS))
        {
            /* Compare all IO */
            for (index = 0; index < MUXPIN_NUM_IO; index++) {
                if (muxpin->io[index].lsio_sel == function && index != number && muxpin->io[index].io_sel == 3)
                    muxpin_set_function_raw(index, FUNC_LSRESV_MAX);
            }
        }
    }

    muxpin_set_function_raw(number, function);
    return 0;
}

int muxpin_set_bank_voltage(int number,muxpin_io_voltage_t voltage)
{
    int group_start = 0;
    int group_end   = 0;
    int i;

    /* check dual voltage number */
    if((number >= 23) && (number <= 28)) {
        group_start = 23;
        group_end   = 28;
    } else if ((number >= 86) && (number <= 91)) {
        group_start = 86;
        group_end   = 91;
    } else if ((number >= 92) && (number <= 97)) {
        group_start = 92;
        group_end   = 97;
    } else if ((number >= 98) && (number <= 103)) {
        group_start = 98;
        group_end   = 103;
    } else if ((number >= 104) && (number <= 109)) {
        group_start = 104;
        group_end   = 109;
    } else if ((number >= 110) && (number <= 115)) {
        group_start = 110;
        group_end   = 115;
    } else if ((number >= 116) && (number <= 121)) {
        group_start = 116;
        group_end   = 121;
    } else if ((number >= 122) && (number <= 127)) {
        group_start = 122;
        group_end   = 127;
    } else {
        return -1; /* don't support dual voltage, only for 1v8*/
    }

    for(i = group_start; i <= group_end; i++) {
        muxpin->io[i].msc = (MUXPIN_IO_VOLTAGE_1V8 == voltage) ? 1:0;
    }
    return 0;
}

muxpin_io_voltage_t muxpin_get_bank_voltage(int number)
{
    int index = 0;

    /* check dual voltage number */
    if((number >= 23) && (number <= 28)) {
        index = 28;
    } else if ((number >= 86) && (number <= 91)) {
        index = 91;
    } else if ((number >= 92) && (number <= 97)) {
        index = 97;
    } else if ((number >= 98) && (number <= 103)) {
        index = 103;
    } else if ((number >= 104) && (number <= 109)) {
        index = 109;
    } else if ((number >= 110) && (number <= 115)) {
        index = 115;
    } else if ((number >= 116) && (number <= 121)) {
        index = 121;
    } else if ((number >= 122) && (number <= 127)) {
        index = 127;
    } else {
        return MUXPIN_IO_VOLTAGE_1V8; /* don't support dual voltage, only for 1v8*/
    }

    return (muxpin->io[index].msc) ? MUXPIN_IO_VOLTAGE_1V8:MUXPIN_IO_VOLTAGE_3V3;
}


