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

#include "video/isp_com.h"
#include "video/bt1120/bt1120_reg.h"
#include "video/bt1120/bt1120_drv.h"

extern unsigned int  *reg_bt1120_wrap_base;
#define BT1120_DRV_REG_CTX(pstCtx)	pstCtx = (S_BT1120_REGS_TYPE *)(reg_bt1120_wrap_base)
/*
*
*/
static int BT1120_DRV_SetSize(BT1120_WRAP_CTL_S *pstBt1120Wrap)
{
    BT1120_CHECK_POINTER(pstBt1120Wrap);

    S_BT1120_REGS_TYPE *apstBt1120Reg = NULL;
    BT1120_DRV_REG_CTX(apstBt1120Reg);  

    U_BT_CTRL_VBIT    stCtrlVbit; 
    stCtrlVbit.u32    = 0;
    stCtrlVbit.bits.bt_vbit_start  = pstBt1120Wrap->stCtrlVbit.bt_vbit_start;
    stCtrlVbit.bits.bt_vbit_end    = pstBt1120Wrap->stCtrlVbit.bt_vbit_end;
    BT1120_DRV_SET_CtlVBit(apstBt1120Reg,stCtrlVbit.u32);  

    U_BT_CTRL_SAV     stCtrlSav; 
    stCtrlSav.u32     = 0;
    stCtrlSav.bits.bt_sav_start    = pstBt1120Wrap->bt_sav_start;
    BT1120_DRV_SET_CtlSav(apstBt1120Reg, stCtrlSav.u32);  

    U_BT_IMAGE_SIZE_TOTAL stSizeTotal;
    stSizeTotal.u32    = 0;
    stSizeTotal.bits.img_hsize_total= pstBt1120Wrap->stSizeTotal.img_hsize_total;
    stSizeTotal.bits.img_vsize_total= pstBt1120Wrap->stSizeTotal.img_vsize_total;
    BT1120_DRV_SET_ImgSizeTotal(apstBt1120Reg,stSizeTotal.u32);

    U_BT_IMAGE_SIZE_ACTIVE  stSizeActive;
    stSizeActive.u32   = 0;
    stSizeActive.bits.img_hsize_active= pstBt1120Wrap->stSizeActive.img_hsize_active;
    stSizeActive.bits.img_vsize_active= pstBt1120Wrap->stSizeActive.img_vsize_active;
    BT1120_DRV_SET_ImgSizeActive(apstBt1120Reg,stSizeActive.u32);
    return 0;
}
/*
*
*/
static int BT1120_DRV_setCtl(BT1120_WRAP_CTL_S *pstBt1120Wrap)
{
    BT1120_CHECK_POINTER(pstBt1120Wrap);

    S_BT1120_REGS_TYPE *apstBt1120Reg = NULL;
    BT1120_DRV_REG_CTX(apstBt1120Reg);
    
    U_BT_IN_SEL   stInSel;
    stInSel.u32  = 0;
    stInSel.bits.bt_in_sel  = pstBt1120Wrap->bt_in_sel;
    BT1120_DRV_SET_InSel(apstBt1120Reg,stInSel.u32);

    U_BT_CTRL_MODE   stCtrlMode;
    stCtrlMode.u32                = 0;
  //  stCtrlMode.bits.bt_en         = bt1120WrapInfo->stCtrlMode.bt_en;
    stCtrlMode.bits.crc_init_val  = pstBt1120Wrap->stCtrlMode.crc_init_val;
    stCtrlMode.bits.crc_order     = pstBt1120Wrap->stCtrlMode.crc_order;
    stCtrlMode.bits.yc_reorder    = pstBt1120Wrap->stCtrlMode.yc_reorder;
    BT1120_DRV_SET_CtlMode(apstBt1120Reg,stCtrlMode.u32);

    //BT1120_DRV_SetSize(pstBt1120Wrap);

    U_BT_CONFIG_DONE stConfigDone;
    stConfigDone.u32 = 0;
   // stConfigDone.bits.config_done   = bt1120WrapInfo->stConfigDone.config_done;
    stConfigDone.bits.wp_clr        = pstBt1120Wrap->stConfigDone.wp_clr;
    BT1120_DRV_SET_ConfigDone(apstBt1120Reg,stConfigDone.u32);
    return 0;
}
/*
*
*/
static int BT1120_DRV_EnBt1120(unsigned int enable,unsigned int config_done)
{
    S_BT1120_REGS_TYPE *apstBt1120Reg = NULL;
    BT1120_DRV_REG_CTX(apstBt1120Reg);

    U_BT_CTRL_MODE   stCtrlMode;
    stCtrlMode.u32                = BT1120_DRV_GET_CtlMode(apstBt1120Reg);
    stCtrlMode.bits.bt_en         = enable;
    BT1120_DRV_SET_CtlMode(apstBt1120Reg,stCtrlMode.u32);

    U_BT_CONFIG_DONE stConfigDone;
    stConfigDone.u32              = BT1120_DRV_GET_ConfigDone(apstBt1120Reg);
    stConfigDone.bits.config_done = config_done;//1;
    BT1120_DRV_SET_ConfigDone(apstBt1120Reg,stConfigDone.u32);
        
    return 0;
}
/*
*
*/
int BT1120_DRV_SetBt1120(BT1120_WRAP_CTL_S *pstBt1120Wrap)
{
    BT1120_CHECK_POINTER(pstBt1120Wrap);

    BT1120_DRV_SetSize(pstBt1120Wrap);

    BT1120_DRV_setCtl(pstBt1120Wrap);

    unsigned int enable = pstBt1120Wrap->stCtrlMode.bt_en;
    unsigned int config_done = pstBt1120Wrap->stConfigDone.config_done;
    BT1120_DRV_EnBt1120(enable,config_done);

    return 0;
}
