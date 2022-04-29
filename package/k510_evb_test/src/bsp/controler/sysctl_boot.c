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


