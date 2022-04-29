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
  File Name     : mipi_csi_reg.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file
******************************************************************************/
#ifndef _MIPI_CSI_REG_H_
#define _MIPI_CSI_REG_H_

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_lane_nb                    : 3; /* [2 ..0 ]  */
        unsigned int    cdns_phy_present               : 1; /* [3 ]  */
        unsigned int    num_streams                    : 3; /* [6:4]      */
        unsigned int    datapath_size                  : 2; /* [8:7]      */
        unsigned int    vcx_config                     : 1; /* [9 ]  */
        unsigned int    asf_config                     : 1; /* [10 ]  */
        unsigned int    reserved0                      : 1; /* [11 ]  */
        unsigned int    stream0_fifo_mode              : 2; /* [12:13]      */
        unsigned int    stream0_num_pixels             : 2; /* [14:15]      */
        unsigned int    stream0_monitor_present        : 1; /* [16]      */   
        unsigned int    stream1_fifo_mode              : 2; /* [17:18]      */
        unsigned int    stream1_num_pixels             : 2; /* [19:20]      */
        unsigned int    stream1_monitor_present        : 1; /* [21]      */   
        unsigned int    stream2_fifo_mode              : 2; /* [22:23]      */
        unsigned int    stream2_num_pixels             : 2; /* [25:24]      */
        unsigned int    stream2_monitor_present        : 1; /* [26]      */        
        unsigned int    stream3_fifo_mode              : 2; /* [28:27]      */
        unsigned int    stream3_num_pixels             : 2; /* [30:29]      */
        unsigned int    stream3_monitor_present        : 1; /* [31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_DEVICE_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        
        unsigned int    front                          : 1   ; /* [0]      */
        unsigned int    protocol                       : 1   ; /* [1]      */
        unsigned int    reserved0                      : 30  ; /* [31:2 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_SFT_RST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sel                             : 2; /* [0..1 ]  */
        unsigned int    Reserved6                       : 2; /*[2..3]      */
        unsigned int    v2p0_support_enable             : 1;/*[4]      */
        unsigned int    Reserved5                       : 3; /*[5..7]      */
        unsigned int    lane_nb                         : 3; /*[8..10]      */
        unsigned int    Reserved4                       : 1; /*[11]      */
        unsigned int    sony_wdr                        : 4; /*[12..15]      */
        unsigned int    dl0_map                         : 3; /*[16:18]      */
        unsigned int    Reserved3                       : 1; /*[19]      */
        unsigned int    dl1_map                         : 3; /*[20:22]      */
        unsigned int    Reserved2                       : 1; /*[23]      */
        unsigned int    dl2_map                         : 3; /*[24:26]      */
        unsigned int    Reserved1                       : 1; /*[27]      */
        unsigned int    dl3_map                         : 3; /*[28:30]      */
        unsigned int    Reserved0                       : 1; /*[31]      */
    } bits;    /* Define an unsigned member */
    unsigned int    udata;
} U_CSI_RX_STREAM_STATIC_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved0                      : 32  ; /* [0..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_CFG_ADDR;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    crc                            : 1  ; /* [0 ]  */
        unsigned int    ecc                            : 1  ; /* [1 ]  */
        unsigned int    data_id                        : 1   ; /* [2]      */
        unsigned int    reserved0                      : 29  ; /* [3..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_ERR_BYPASS_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stream0_timer_irq              : 1   ; /* [0] */
        unsigned int    stream0_lb_irq                 : 1   ; /* [1] */
        unsigned int    stream0_frame_irq              : 1   ; /* [2] */
        unsigned int    stream0_fcc_start_irq          : 1   ; /* [3] */
        unsigned int    stream0_fcc_stop_irq           : 1   ; /* [4] */
        unsigned int    stream0_frame_cnt_error_irq    : 1   ; /* [5] */
        unsigned int    stream0_frame_mismatch_irq     : 1   ; /* [6] */
        unsigned int    stream0_line_cnt_error_irq     : 1   ; /* [7] */
        unsigned int    stream1_timer_irq              : 1   ; /* [8] */
        unsigned int    stream1_lb_irq                 : 1   ; /* [9] */
        unsigned int    stream1_frame_irq              : 1   ; /* [10] */
        unsigned int    stream1_fcc_start_irq          : 1   ; /* [11] */
        unsigned int    stream1_fcc_stop_irq           : 1   ; /* [12] */
        unsigned int    stream1_frame_cnt_error_irq    : 1   ; /* [13] */
        unsigned int    stream1_frame_mismatch_irq     : 1   ; /* [14] */
        unsigned int    stream1_line_cnt_error_irq     : 1   ; /* [15] */
        unsigned int    stream2_timer_irq              : 1   ; /* [16] */
        unsigned int    stream2_lb_irq                 : 1   ; /* [17] */
        unsigned int    stream2_frame_irq              : 1   ; /* [18] */
        unsigned int    stream2_fcc_start_irq          : 1   ; /* [19] */
        unsigned int    stream2_fcc_stop_irq           : 1   ; /* [20] */
        unsigned int    stream2_frame_cnt_error_irq    : 1   ; /* [21] */
        unsigned int    stream2_frame_mismatch_irq     : 1   ; /* [22] */
        unsigned int    stream2_line_cnt_error_irq     : 1   ; /* [23] */
        unsigned int    stream3_timer_irq              : 1   ; /* [24] */
        unsigned int    stream3_lb_irq                 : 1   ; /* [25] */
        unsigned int    stream3_frame_irq              : 1   ; /* [26] */
        unsigned int    stream3_fcc_start_irq          : 1   ; /* [27] */
        unsigned int    stream3_fcc_stop_irq           : 1   ; /* [28] */
        unsigned int    stream3_frame_cnt_error_irq    : 1   ; /* [29] */
        unsigned int    stream3_frame_mismatch_irq     : 1   ; /* [30] */
        unsigned int    stream3_line_cnt_error_irq     : 1   ; /* [31] */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_MONITOR_IRQS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stream0_timer_irqm              : 1   ; /* [0] */
        unsigned int    stream0_lb_irqm                 : 1   ; /* [1] */
        unsigned int    stream0_frame_irqm              : 1   ; /* [2] */
        unsigned int    stream0_fcc_start_irqm          : 1   ; /* [3] */
        unsigned int    stream0_fcc_stop_irqm           : 1   ; /* [4] */
        unsigned int    stream0_frame_cnt_error_irqm    : 1   ; /* [5] */
        unsigned int    stream0_frame_mismatch_irqm     : 1   ; /* [6] */
        unsigned int    stream0_line_cnt_error_irqm     : 1   ; /* [7] */
        unsigned int    stream1_timer_irqm              : 1   ; /* [8] */
        unsigned int    stream1_lb_irqm                 : 1   ; /* [9] */
        unsigned int    stream1_frame_irqm              : 1   ; /* [10] */
        unsigned int    stream1_fcc_start_irqm          : 1   ; /* [11] */
        unsigned int    stream1_fcc_stop_irqm           : 1   ; /* [12] */
        unsigned int    stream1_frame_cnt_error_irqm    : 1   ; /* [13] */
        unsigned int    stream1_frame_mismatch_irqm     : 1   ; /* [14] */
        unsigned int    stream1_line_cnt_error_irqm     : 1   ; /* [15] */
        unsigned int    stream2_timer_irqm              : 1   ; /* [16] */
        unsigned int    stream2_lb_irqm                 : 1   ; /* [17] */
        unsigned int    stream2_frame_irqm              : 1   ; /* [18] */
        unsigned int    stream2_fcc_start_irqm          : 1   ; /* [19] */
        unsigned int    stream2_fcc_stop_irqm           : 1   ; /* [20] */
        unsigned int    stream2_frame_cnt_error_irqm    : 1   ; /* [21] */
        unsigned int    stream2_frame_mismatch_irqm     : 1   ; /* [22] */
        unsigned int    stream2_line_cnt_error_irqm     : 1   ; /* [23] */
        unsigned int    stream3_timer_irqm              : 1   ; /* [24] */
        unsigned int    stream3_lb_irqm                 : 1   ; /* [25] */
        unsigned int    stream3_frame_irqm              : 1   ; /* [26] */
        unsigned int    stream3_fcc_start_irqm          : 1   ; /* [27] */
        unsigned int    stream3_fcc_stop_irqm           : 1   ; /* [28] */
        unsigned int    stream3_frame_cnt_error_irqm    : 1   ; /* [29] */
        unsigned int    stream3_frame_mismatch_irqm     : 1   ; /* [30] */
        unsigned int    stream3_line_cnt_error_irqm     : 1   ; /* [31] */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_MONITOR_IRQS_MASK_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sp_rcvd_irq                    : 1   ; /* [0]      */
        unsigned int    lp_rcvd_irq                    : 1   ; /* [1]      */
        unsigned int    sleep_irq                      : 1   ; /* [2]      */
        unsigned int    wakeup_irq                     : 1   ; /* [3]      */
        unsigned int    ecc_spares_nonzero_irq         : 1   ; /* [4]      */
        unsigned int    deskew_entry_irq               : 1   ; /* [5]      */
        unsigned int    sp_generic_rcvd_irq            : 1   ; /* [6]      */
        unsigned int    stream0_stop_irq               : 1   ; /* [7]      */
        unsigned int    stream0_abort_irq              : 1   ; /* [8]      */
        unsigned int    stream1_stop_irq               : 1   ; /* [9]      */
        unsigned int    stream1_abort_irq              : 1   ; /* [10]      */
        unsigned int    stream2_stop_irq               : 1   ; /* [11]      */
        unsigned int    stream2_abort_irq              : 1   ; /* [12]      */
        unsigned int    stream3_stop_irq               : 1   ; /* [13]      */
        unsigned int    stream3_abort_irq              : 1   ; /* [14]      */
        unsigned int    reserved0                      : 17  ; /* [15 ..31 ]  */

    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_INFO_IRQS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sp_rcvd_irqm                    : 1   ; /* [0]      */
        unsigned int    lp_rcvd_irqm                    : 1   ; /* [1]      */
        unsigned int    sleep_irqm                      : 1   ; /* [2]      */
        unsigned int    wakeup_irqm                     : 1   ; /* [3]      */
        unsigned int    ecc_spares_nonzero_irqm         : 1   ; /* [4]      */
        unsigned int    deskew_entry_irqm               : 1   ; /* [5]      */
        unsigned int    sp_generic_rcvd_irqm            : 1   ; /* [6]      */
        unsigned int    stream0_stop_irqm               : 1   ; /* [7]      */
        unsigned int    stream0_abort_irqm              : 1   ; /* [8]      */
        unsigned int    stream1_stop_irqm               : 1   ; /* [9]      */
        unsigned int    stream1_abort_irqm              : 1   ; /* [10]      */
        unsigned int    stream2_stop_irqm               : 1   ; /* [11]      */
        unsigned int    stream2_abort_irqm              : 1   ; /* [12]      */
        unsigned int    stream3_stop_irqm               : 1   ; /* [13]      */
        unsigned int    stream3_abort_irqm              : 1   ; /* [14]      */
        unsigned int    reserved0                       : 17  ; /* [15 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_INFO_IRQS_MASK_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    front_fifo_overflow_irq         : 1   ; /* [0]      */
        unsigned int    reserved2                       : 3  ; /* [1 ..3 ]  */
        unsigned int    payload_crc_irq                 : 1   ; /* [4]      */
        unsigned int    header_ecc_irq                  : 1   ; /* [5]      */
        unsigned int    header_corrected_ecc_irq        : 1   ; /* [6]      */
        unsigned int    data_id_irq                     : 1   ; /* [7]      */
        unsigned int    invalid_access_irq              : 1   ; /* [8]      */
        unsigned int    sp_invalid_rcvd_irq             : 1   ; /* [9]      */
        unsigned int    front_lp_no_payload_irq         : 1   ; /* [10]      */
        unsigned int    prot_truncated_packet_irq       : 1   ; /* [11]      */
        unsigned int    front_trunc_hdr_irq             : 1   ; /* [12]      */
        unsigned int    reserved1                       : 3  ; /* [13 ..15 ]  */
        unsigned int    stream0_fifo_overflow_irq       : 1   ; /* [16]      */
        unsigned int    stream1_fifo_overflow_irq       : 1   ; /* [17]      */
        unsigned int    stream2_fifo_overflow_irq       : 1   ; /* [18]      */
        unsigned int    stream3_fifo_overflow_irq       : 1   ; /* [19]      */
        unsigned int    reserved0                       : 12  ; /* [20 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_ERROR_IRQS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    front_fifo_overflow_irqm         : 1   ; /* [0]      */
        unsigned int    reserved2                       : 3  ; /* [1 ..3 ]  */
        unsigned int    payload_crc_irqm                 : 1   ; /* [4]      */
        unsigned int    header_ecc_irqm                  : 1   ; /* [5]      */
        unsigned int    header_corrected_ecc_irqm        : 1   ; /* [6]      */
        unsigned int    data_id_irqm                     : 1   ; /* [7]      */
        unsigned int    invalid_access_irqm              : 1   ; /* [8]      */
        unsigned int    sp_invalid_rcvd_irqm             : 1   ; /* [9]      */
        unsigned int    front_lp_no_payload_irqm         : 1   ; /* [10]      */
        unsigned int    prot_truncated_packet_irqm       : 1   ; /* [11]      */
        unsigned int    front_trunc_hdr_irqm             : 1   ; /* [12]      */
        unsigned int    reserved1                       : 3  ; /* [13 ..15 ]  */
        unsigned int    stream0_fifo_overflow_irqm       : 1   ; /* [16]      */
        unsigned int    stream1_fifo_overflow_irqm       : 1   ; /* [17]      */
        unsigned int    stream2_fifo_overflow_irqm       : 1   ; /* [18]      */
        unsigned int    stream3_fifo_overflow_irqm       : 1   ; /* [19]      */
        unsigned int    reserved0                        : 12  ; /* [20 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_ERROR_IRQS_MASK_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dl0_enable                        : 1; /* [0]      */        
        unsigned int    dl1_enable                        : 1; /* [1]      */
        unsigned int    dl2_enable                        : 1; /* [2]      */
        unsigned int    dl3_enable                        : 1; /* [3]      */
        unsigned int    cl_enable                         : 1; /* [4]      */
        unsigned int    reserved1                         : 7; /* [5 ..11 ]  */
        unsigned int    dl0_reset                         : 1; /* [12]      */        
        unsigned int    dl1_reset                         : 1; /* [13]      */
        unsigned int    dl2_reset                         : 1; /* [14]      */
        unsigned int    dl3_reset                         : 1; /* [15]      */
        unsigned int    cl_reset                          : 1; /* [16]      */
        unsigned int    reserved0                         : 15; /* [17 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_DPHY_LANE_CONTROL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved0                      : 32  ; /* [0 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_DPHY_LANE_CONFIG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cl_StopState                   : 1   ; /* [0]      */
        unsigned int    cl_ULPSActiveNot               : 1   ; /* [1]      */
        unsigned int    cl_RxULPSClkNot                : 1   ; /* [2]      */
        unsigned int    reserved4                      : 5  ; /* [3..7 ]  */
        unsigned int    dl0_StopState                  : 1   ; /* [8]      */
        unsigned int    dl0_ULPSActiveNot              : 1   ; /* [9]      */
        unsigned int    dl0_RxULPSEsc                  : 1   ; /* [10]      */
        unsigned int    reserved3                      : 1  ; /* [11 ]  */
        unsigned int    dl1_StopState                  : 1   ; /* [12]      */
        unsigned int    dl1_ULPSActiveNot              : 1   ; /* [13]      */
        unsigned int    dl1_RxULPSEsc                  : 1   ; /* [14]      */
        unsigned int    reserved2                      : 1  ; /* [15 ]  */
        unsigned int    dl2_StopState                  : 1   ; /* [16]      */
        unsigned int    dl2_ULPSActiveNot              : 1   ; /* [17]      */
        unsigned int    dl2_RxULPSEsc                  : 1   ; /* [18]      */
        unsigned int    reserved1                      : 1  ; /* [19 ]  */
        unsigned int    dl3_StopState                  : 1   ; /* [20]      */
        unsigned int    dl3_ULPSActiveNot              : 1   ; /* [21]      */
        unsigned int    dl3_RxULPSEsc                  : 1   ; /* [22]      */
        unsigned int    reserved0                      : 9  ; /* [23 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_DPHY_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved4                      : 8  ; /* [0 ..7 ]  */
        unsigned int    dl0_ErrSotHS_irq               : 1  ; /* [8 ]  */
        unsigned int    reserved3                      : 3  ; /* [9 ..11 ]  */
        unsigned int    dl1_ErrSotHS_irq               : 1  ; /* [12 ]  */
        unsigned int    reserved2                      : 3  ; /* [13 ..15 ]  */
        unsigned int    dl2_ErrSotHS_irq               : 1  ; /* [16 ]  */
        unsigned int    reserved1                      : 3  ; /* [17 ..19 ]  */
        unsigned int    dl3_ErrSotHS_irq               : 1   ; /* [20]      */
        unsigned int    reserved0                      : 11  ; /* [21 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_DPHY_ERR_STATUS_IRQ;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved4                      : 8  ; /* [0 ..7 ]  */
        unsigned int    dl0_ErrSotHS_irqm               : 1  ; /* [8 ]  */
        unsigned int    reserved3                      : 3  ; /* [9 ..11 ]  */
        unsigned int    dl1_ErrSotHS_irqm               : 1  ; /* [12 ]  */
        unsigned int    reserved2                      : 3  ; /* [13 ..15 ]  */
        unsigned int    dl2_ErrSotHS_irqm               : 1  ; /* [16 ]  */
        unsigned int    reserved1                      : 3  ; /* [17 ..19 ]  */
        unsigned int    dl3_ErrSotHS_irqm               : 1   ; /* [20]      */
        unsigned int    reserved0                      : 11  ; /* [21 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_DPHY_ERR_IRQ_MASK;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved0                      : 32  ; /* [0 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_DPHY_TEST;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    prot_word_count                 : 16  ; /* [0 ..15 ]  */
        unsigned int    prot_dt                         : 6  ; /* [16 ..21 ]  */
        unsigned int    prot_vc                         : 2  ; /* [22 ..23 ]  */
        unsigned int    Reserved0                       : 4  ; /* [24 ..27 ]  */
        unsigned int    prot_fsm_state                  : 4  ; /* [28 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_INTEGRATION_DEBUG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dt                       : 6  ; /* [0..5 ]  */
        unsigned int    vc                       : 2  ; /* [6..7 ]  */
        unsigned int    Reserved0                : 8  ; /* [8..15 ]  */
        unsigned int    data_field               : 16  ; /*[16..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_ERROR_DEBUG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ctrl                           : 16; /* [0..15 ]  */
        unsigned int    status                         : 16; /* [16..31]      */

    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_TEST_GENERIC;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start                          :1; /* [1]      */
        unsigned int    stop                           :1; /* [1]      */
        unsigned int    abort                          :1; /* [2]      */
        unsigned int    Reserved1                      :1; /* [3]      */
        unsigned int    soft_rst                       :1; /* [4]      */
        unsigned int    reserved0                      :17; /* [5 ..31 ]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_CTRL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    protocol_fsm                   :2; /* [0 ..1]  */
        unsigned int    reserved1                      :2; /* [2 ..3]  */
        unsigned int    stream_fsm                     :4; /* [4..7]  */
        unsigned int    ready_state                    :1 ; /* [8]      */
        unsigned int    reserved0                      :22; /* [9..30]  */
        unsigned int    running                        :1; /* [31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_STATUS;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    datatype_select0                :6; /* [0..5]  */
        unsigned int    Reserved2                       :1; /* [6]      */
        unsigned int    enable_dt0                      :1; /* [7]      */
        unsigned int    datatype_select1                :6; /* [8..13]  */
        unsigned int    Reserved1                       :1; /* [14]      */
        unsigned int    enable_dt1                      :1; /* [15]      */
        unsigned int    vc_select                       :16; /* [16..31]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_DATA_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    interface_mode                 :1; /* [0]*/
        unsigned int    ls_le_mode                     :1; /* [1]*/
        unsigned int    Reserved3                      :2; /* [2..3]*/
        unsigned int    num_pixels                     :2; /* [4..5]*/
        unsigned int    Reserved2                      :2; /* [6..7]*/
        unsigned int    fifo_mode                      :2; /* [8..9]*/
        unsigned int    Reserved1                      :2; /* [10..11]*/
        unsigned int    bpp_bypass                     :3; /* [12..14]*/
        unsigned int    Reserved0                      :1; /* [15]*/
        unsigned int    fifo_fill                      :16; /* [16..31]  */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lb_vc                           :4; /* [0..3]      */
        unsigned int    lb_en                           :1; /* [4]      */
        unsigned int    timer_vc                        :4; /* [5..8]      */
        unsigned int    timer_en                        :1; /* [9]      */
        unsigned int    timer_eof                       :1; /* [10]      */
        unsigned int    frame_mon_vc                    :4; /* [11 ..14 ]  */
        unsigned int    frame_mon_en                    :1; /* [15]      */
        unsigned int    frame_length                    :16; /* [16..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_MONITOR_CTRL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nb                              :16; /* [0 ..15 ]  */
        unsigned int    packet_size                     :16; /*[16..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_MONITOR_FRAME;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    byte_count                      :16; /* [0 ..15 ]  */
        unsigned int    line_count                      :16; /*[16..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_MONITOR_LB;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    count                           :25; /* [0 ..24 ]  */
        unsigned int    Reserved0                       :7; /*[25..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_TIMER;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_count_start                :16; /* [0 ..15 ]  */
        unsigned int    frame_count_stop                 :16; /*[16..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_FCC_CFG;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fcc_en                            : 1  ; /* [0]  */
        unsigned int    fcc_vc                            : 4  ; /* [1..4]  */
        unsigned int    reserved0                         : 11   ; /* [5..15]      */
        unsigned int    fcc_debug                         : 16   ; /* [16..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_FCC_CTRL;

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    count                             :10; /* [9 ..0 ]  */
        unsigned int    Reserved1                         :2; /* [10..11]      */
        unsigned int    mode                              :2; /* [12..13]      */
        unsigned int    Reserved0                         :18; /* [14..31]      */
    } bits;    /* Define an unsigned member */

    unsigned int    udata;
} U_CSI_RX_STREAM_FCC_FILL_LVL;

//  # PER STREAM Addresses (paddr[7:0]
#define   CSI_RX_STREAM_DEVICE_CFG              (0x0000)
#define   CSI_RX_STREAM_SFT_RST                 (0x0004)
#define   CSI_RX_STREAM_STATIC_CFG              (0x0008)
#define   CSI_RX_STREAM_CFG_ADDR                (0x000C)
#define   CSI_RX_STREAM_ERR_BYPASS_CFG          (0x0010)
#define   CSI_RX_STREAM_MONITOR_FRAME           (0x0014)
#define   CSI_RX_STREAM_MONITOR_IRQS            (0x0018)
#define   CSI_RX_STREAM_MONITOR_IRQS_MASK_CFG   (0x001C)
#define   CSI_RX_STREAM_INFO_IRQS               (0x0020)
#define   CSI_RX_STREAM_INFO_IRQS_MASK_CFG      (0x0024)
#define   CSI_RX_STREAM_ERROR_IRQS              (0x0028)
#define   CSI_RX_STREAM_ERROR_IRQS_MASK_CFG     (0x002C)
//  # DPHY
#define   CSI_RX_DPHY_LANE_CONTROL              (0x0040)
#define   CSI_RX_DPHY_LANE_CONFIG               (0x0044)
#define   CSI_RX_DPHY_STATUS                    (0x0048)
#define   CSI_RX_DPHY_ERR_STATUS_IRQ            (0x004C)
#define   CSI_RX_DPHY_ERR_IRQ_MASK              (0x0050)
#define   CSI_RX_DPHY_TEST                      (0x0054)
// # DEBUG0       
#define   CSI_RX_INTEGRATION_DEBUG              (0x0060)
#define   CSI_RX_ERROR_DEBUG                    (0x0074)
#define   CSI_RX_TEST_GENERIC                   (0x0080)
//stream 0
#define   CSI_RX_STREAM0_CTRL                   (0x0100)  
#define   CSI_RX_STREAM0_STATUS                 (0x0104)
#define   CSI_RX_STREAM0_DATA_CFG               (0x0108)
#define   CSI_RX_STREAM0_CFG                    (0x010C)
#define   CSI_RX_STREAM0_MONITOR_CTRL           (0x0110)
#define   CSI_RX_STREAM0_MONITOR_FRAME          (0x0114)
#define   CSI_RX_STREAM0_MONITOR_LB             (0x0118)
#define   CSI_RX_STREAM0_TIMER                  (0x011C)
#define   CSI_RX_STREAM0_FCC_CFG                (0x0120)
#define   CSI_RX_STREAM0_FCC_CTRL               (0x0124)
#define   CSI_RX_STREAM0_FCC_FILL_LVL           (0x0128)
//stream 1
#define   CSI_RX_STREAM1_CTRL                   (0x0200)  
#define   CSI_RX_STREAM1_STATUS                 (0x0204)
#define   CSI_RX_STREAM1_DATA_CFG               (0x0208)
#define   CSI_RX_STREAM1_CFG                    (0x020C)
#define   CSI_RX_STREAM1_MONITOR_CTRL           (0x0210)
#define   CSI_RX_STREAM1_MONITOR_FRAME          (0x0214)
#define   CSI_RX_STREAM1_MONITOR_LB             (0x0218)
#define   CSI_RX_STREAM1_TIMER                  (0x021C)
#define   CSI_RX_STREAM1_FCC_CFG                (0x0220)
#define   CSI_RX_STREAM1_FCC_CTRL               (0x0224)
#define   CSI_RX_STREAM1_FCC_FILL_LVL           (0x0228)
//stream 2
#define   CSI_RX_STREAM2_CTRL                   (0x0300)  
#define   CSI_RX_STREAM2_STATUS                 (0x0304)
#define   CSI_RX_STREAM2_DATA_CFG               (0x0308)
#define   CSI_RX_STREAM2_CFG                    (0x030C)
#define   CSI_RX_STREAM2_MONITOR_CTRL           (0x0310)
#define   CSI_RX_STREAM2_MONITOR_FRAME          (0x0314)
#define   CSI_RX_STREAM2_MONITOR_LB             (0x0318)
#define   CSI_RX_STREAM2_TIMER                  (0x031C)
#define   CSI_RX_STREAM2_FCC_CFG                (0x0320)
#define   CSI_RX_STREAM2_FCC_CTRL               (0x0324)
#define   CSI_RX_STREAM2_FCC_FILL_LVL           (0x0328)
//stream 3
#define   CSI_RX_STREAM2_CTRL                   (0x0400)  
#define   CSI_RX_STREAM2_STATUS                 (0x0404)
#define   CSI_RX_STREAM2_DATA_CFG               (0x0408)
#define   CSI_RX_STREAM2_CFG                    (0x040C)
#define   CSI_RX_STREAM2_MONITOR_CTRL           (0x0410)
#define   CSI_RX_STREAM2_MONITOR_FRAME          (0x0414)
#define   CSI_RX_STREAM2_MONITOR_LB             (0x0418)
#define   CSI_RX_STREAM2_TIMER                  (0x041C)
#define   CSI_RX_STREAM2_FCC_CFG                (0x0420)
#define   CSI_RX_STREAM2_FCC_CTRL               (0x0424)
#define   CSI_RX_STREAM2_FCC_FILL_LVL           (0x0328)
#endif /*_MIPI_CSI_REG_H_*/