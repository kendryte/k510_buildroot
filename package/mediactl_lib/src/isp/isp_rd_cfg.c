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
/******************************************************************************
  File Name     : isp_rd_cfg.c
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../media_ctl.h"

/**
 * @brief 
 * 
 * @param addr 
 * @return unsigned int 
 */
static unsigned int RegRd32(unsigned int addr)
{
    char result[10240] = {0};
	char buf[1024] = {0};
    char cmd[1024] = {0};
    unsigned ret;
    FILE *fp = NULL;

    sprintf(cmd, "devmem 0x%08X\n", addr);

    if( (fp = popen(cmd, "r")) == NULL ) {
        printf("popen error!\n");
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        strcat(result, buf);
    }
    pclose(fp);
    // printf("result: %s\n", result);

    ret = strtol(result, NULL, 16);
    return ret;
}
/**
 * @brief 
 * 
 * @param pipeline 
 * @param module 
 * @return unsigned int 
 */
unsigned int mediactl_get_isp_modules(enum isp_pipeline_e pipeline,enum isp_modules module)
{
    unsigned int enable = 0;
    unsigned base_addr = 0x92650400;
    if(ISP_F2K_PIPELINE == pipeline)
    {
        base_addr = 0x92650400;
    }
    else if(ISP_R2K_PIPELINE == pipeline)
    {
        base_addr = 0x92660400;
    }

    switch(module)
    {
        case ISP_TPG:
            enable = (RegRd32(base_addr + 0x01c)>>8) & 0x1;
            break;
        case ISP_BLC:
            enable = (RegRd32(base_addr + 0x020)>>0) & 0x1;
            break;
        case ISP_LSC:
            enable = (RegRd32(base_addr + 0x02c)>>0) & 0x1;
            break;
        case ISP_AE:
            enable = (RegRd32(base_addr + 0x050)>>1) & 0x1;
            break;
        case ISP_AWB:
            enable = (RegRd32(base_addr + 0x104)>>2) & 0x1;
            break;
        case ISP_AWB_D65:
            enable = (RegRd32(base_addr + 0x104)>>0) & 0x1;
            break;
        case ISP_AWB_CCM:
            enable = (RegRd32(base_addr + 0x104)>>1) & 0x1;
            break;
        case ISP_WDR:
            enable = (RegRd32(base_addr + 0x1B8)>>4) & 0x1;
            break;
        case ISP_RGB_GAMMA:
            enable = (RegRd32(base_addr + 0x204)>>0) & 0x1;
            break;
        case ISP_YUV_GAMMA:
            enable = (RegRd32(base_addr + 0x204)>>1) & 0x1;
            break;
        case ISP_ADA:
            enable = (RegRd32(base_addr + 0x204)>>2) & 0x1;
            break;
        case ISP_ADA_SBZ:
            enable = (RegRd32(base_addr + 0x204)>>3) & 0x1;
            break;
        case ISP_ADA_CCR:
            enable = (RegRd32(base_addr + 0x204)>>4) & 0x1;
            break;
        case ISP_RGBIR:
            enable = (RegRd32(base_addr + 0x230)>>0) & 0x1;
            break;
        case ISP_RAW_2DNR:
            enable = (RegRd32(base_addr + 0x258)>>1) & 0x1;
            break;
        case ISP_YUV_Y_2DNR:
            enable = (RegRd32(base_addr + 0x258)>>4) & 0x1;
            break;
        case ISP_YUV_UV_2DNR:
            enable = (RegRd32(base_addr + 0x258)>>5) & 0x1;
            break;
        case ISP_3DNR:
            enable = (RegRd32(base_addr + 0x278)>>0) & 0x1;
            break;
        case ISP_LTM:
            enable = (RegRd32(base_addr + 0x2BC)>>0) & 0x1;
            break;
        case ISP_SHARP:
            enable = (RegRd32(base_addr + 0x2BC)>>1) & 0x1;
            break;
        case ISP_CC:
            enable = (RegRd32(base_addr + 0x2BC)>>2) & 0x1;
            break;
        case ISP_CTRST:
            enable = (RegRd32(base_addr + 0x2E4)>>4) & 0x1;
            break;
        case ISP_LUMA:
            enable = (RegRd32(base_addr + 0x2E4)>>5) & 0x1;
            break;
        case ISP_SATURATION:
            enable = (RegRd32(base_addr + 0x2E4)>>6) & 0x1;
            break;
        case ISP_LDC:
            enable = (RegRd32(base_addr + 0x304)>>0) & 0x1;
            break;
        case ISP_AF:
            enable = (RegRd32(base_addr + 0x340)>>0) & 0x1;
            break;
        default:
            printf("%s:no module!!\n",__func__);
    }
    return enable;
}