/******************************************************************************

  Copyright (C), 2020, CANAAN Tech. Co., Ltd.

 ******************************************************************************
  File Name     : bt1120_reg.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : bt1120 driver interface
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef _BT1120_REG_DEF_H_
#define _BT1120_REG_DEF_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bt_in_sel                      : 4   ; /* [3..0 ]      */
        unsigned int    reserved0                      : 28  ; /* [31..4]      */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_BT_IN_SEL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bt_en                           : 1   ; /* [0 ]      */
        unsigned int    yc_reorder                      : 1   ; /* [1 ]      */
        unsigned int    reserved0                       : 2   ; /* [3..2 ]      */
        unsigned int    crc_order                       : 1   ; /* [4 ]      */
        unsigned int    crc_init_val                    : 1   ; /* [5 ]      */
        unsigned int    reserved1                       : 26  ; /* [31..6 ]      */
    } bits;    /* Define an unsigned member */
    unsigned int    u32;
} U_BT_CTRL_MODE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bt_vbit_start                   : 12   ; /* [11..0 ]      */
        unsigned int    reserved0                       : 4    ; /* [15..12]      */
        unsigned int    bt_vbit_end                     : 12   ; /* [27..16]      */
        unsigned int    reserved1                       : 4    ; /* [31..28]      */        
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_BT_CTRL_VBIT;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bt_sav_start                   : 12   ; /* [11..0 ]      */
        unsigned int    reserved0                      : 20  ; /* [31..12]      */
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_BT_CTRL_SAV;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    img_vsize_total                 : 12   ; /* [11..0 ]      */
        unsigned int    reserved0                       : 4    ; /* [15..12]      */
        unsigned int    img_hsize_total                 : 12   ; /* [27..16 ]      */
        unsigned int    reserved1                       : 4    ; /* [31..28]      */        
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_BT_IMAGE_SIZE_TOTAL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    img_vsize_active                : 12   ; /* [11..0 ]      */
        unsigned int    reserved0                       : 4    ; /* [15..12]      */
        unsigned int    img_hsize_active                : 12   ; /* [27..16 ]      */
        unsigned int    reserved1                       : 4    ; /* [31..28]      */        
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_BT_IMAGE_SIZE_ACTIVE;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    config_done                     : 1   ; /* [0 ]      */
        unsigned int    reserved0                       : 15   ; /*[15..1]      */
        unsigned int    wp_clr                          : 1   ; /* [16 ]      */
        unsigned int    reserved1                       : 15    ; /* [31..17]      */        
    } bits;    /* Define an unsigned member */

    unsigned int    u32;
} U_BT_CONFIG_DONE;

typedef struct
{
    volatile U_BT_IN_SEL                    BT_IN_SEL;
    volatile U_BT_CTRL_MODE                 BT_CTRL_MODE;
    volatile U_BT_CTRL_VBIT                 BT_CTRL_VBIT;
    volatile U_BT_CTRL_SAV                  BT_CTRL_SAV;
    volatile U_BT_IMAGE_SIZE_TOTAL          BT_IMAGE_SIZE_TOTAL;
    volatile U_BT_IMAGE_SIZE_ACTIVE         BT_IMAGE_SIZE_ACTIVE;
    volatile U_BT_CONFIG_DONE               BT_CONFIG_DONE;
}S_BT1120_REGS_TYPE;

int BT1120_DRV_SET_InSel(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
int BT1120_DRV_SET_CtlMode(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int BT1120_DRV_GET_CtlMode(S_BT1120_REGS_TYPE *pstRegs);
int BT1120_DRV_SET_CtlVBit(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
int BT1120_DRV_SET_CtlSav(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
int BT1120_DRV_SET_ImgSizeTotal(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
int BT1120_DRV_SET_ImgSizeActive(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
int BT1120_DRV_SET_ConfigDone(S_BT1120_REGS_TYPE *pstRegs, unsigned int uData);
unsigned int BT1120_DRV_GET_ConfigDone(S_BT1120_REGS_TYPE *pstRegs);

#endif /*_BT1120_REG_DEF_H_*/
