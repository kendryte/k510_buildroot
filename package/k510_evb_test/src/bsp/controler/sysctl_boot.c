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
#include "platform.h"
#include "sysctl_boot.h"

volatile sysctl_boot_t* sysctl_boot = (volatile sysctl_boot_t*)SYSCTL_BOOT_BASE_ADDR;

sysctl_boot_mode_e sysctl_boot_get_boot_mode(void)
{
    switch(sysctl_boot->soc_boot_ctl & 0x3)/*bit0~1*/
    {        
        case 1:
            return SYSCTL_BOOT_SDCARD;
        case 2:
            return SYSCTL_BOOT_FLASH;
        case 3:
            return SYSCTL_BOOT_EMMC;
        case 0:
        default:
            return SYSCTL_BOOT_DOWNLOAD;
    }
}

bool sysctl_boot_get_otp_bypass(void)
{
    if(sysctl_boot->soc_boot_ctl & 0x4)
        return true;
    else
        return false;
}

void sysctl_boot_reset_soc(void)
{
    sysctl_boot->soc_glb_rst = ((1 << 0) | (1 << 16));
    while(1)
    {
    }
}


void sysctl_boot_osc_off_25m(void)
{
	sysctl_boot->osc_25m_off = ((1 << 16) | (1 << 0) );
}

void sysctl_boot_soc_sleep_ctl(void)
{
	sysctl_boot->soc_slp_ctl = ((1 << 4) | (1 << 25));
}

int sysctl_boot_read_is_boot_wakeup(void)
{
	return sysctl_boot->soc_wakeup_src;
}


