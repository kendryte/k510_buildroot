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

/*
 * k510isp.h
 *
 * CANAAN K510 ISP - User-space API
 *
 * Contacts: zhudalei <zhudalei@canaan-creative.com>
 *
 */

#ifndef __K510_ISP_USER_H__
#define __K510_ISP_USER_H__

#include <linux/types.h>
#include <linux/videodev2.h>

/*
 * Private IOCTLs
 */
#define VIDIOC_K510ISP_VI_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 1,struct vi_cfg_info)
#define VIDIOC_K510ISP_F2K_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 2,struct isp_wrap_cfg_info)
#define VIDIOC_K510ISP_F2K_CORE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 3,struct isp_core_cfg_info)
#define VIDIOC_K510ISP_F2K_DS_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 4,struct isp_ds_cfg_info)
#define VIDIOC_K510ISP_F2K_REMAP_MAIN_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 5,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_F2K_REMAP_OUT0_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 6,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_F2K_REMAP_OUT1_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 7,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_F2K_FBCD_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 8,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_R2K_WRAP_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 9,struct isp_wrap_cfg_info)
#define VIDIOC_K510ISP_R2K_CORE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 10,struct isp_core_cfg_info)
#define VIDIOC_K510ISP_R2K_DS_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 11,struct isp_ds_cfg_info)
#define VIDIOC_K510ISP_R2K_REMAP_MAIN_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 12,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_R2K_REMAP_OUT0_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 13,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_R2K_REMAP_OUT1_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 14,struct isp_remap_cfg_info)
#define VIDIOC_K510ISP_CSI2_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 15,struct isp_csi2_info)
#define VIDIOC_K510ISP_F2K_AF_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 16, struct k510isp_af_config)
#define VIDIOC_K510ISP_F2K_AF_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 17, struct k510isp_af_stats)
#define VIDIOC_K510ISP_F2K_AF_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 18, unsigned long)
#define VIDIOC_K510ISP_R2K_AF_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 19, struct k510isp_af_config)
#define VIDIOC_K510ISP_R2K_AF_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 20, struct k510isp_af_stats)
#define VIDIOC_K510ISP_R2K_AF_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 21, unsigned long)
#define VIDIOC_K510ISP_F2K_AE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 22, struct k510isp_ae_config)
#define VIDIOC_K510ISP_F2K_AE_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 23, struct k510isp_ae_stats)
#define VIDIOC_K510ISP_F2K_AE_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 24, unsigned long)
#define VIDIOC_K510ISP_R2K_AE_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 25, struct k510isp_ae_config)
#define VIDIOC_K510ISP_R2K_AE_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 26, struct k510isp_ae_stats)
#define VIDIOC_K510ISP_R2K_AE_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 27, unsigned long)
#define VIDIOC_K510ISP_F2K_AWB_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 28, struct k510isp_awb_config)
#define VIDIOC_K510ISP_F2K_AWB_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 29, struct k510isp_awb_stats)
#define VIDIOC_K510ISP_F2K_AWB_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 30, unsigned long)
#define VIDIOC_K510ISP_R2K_AWB_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 31, struct k510isp_awb_config)
#define VIDIOC_K510ISP_R2K_AWB_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 32, struct k510isp_awb_stats)
#define VIDIOC_K510ISP_R2K_AWB_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 33, unsigned long)
#define VIDIOC_K510ISP_F2K_CFG_SET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 34,struct isp_cfg_info)
#define VIDIOC_K510ISP_R2K_CFG_SET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 35,struct isp_cfg_info)
#define VIDIOC_K510ISP_F2K_CORE_CFG_GET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 36,struct isp_core_cfg_info)
#define VIDIOC_K510ISP_R2K_CORE_CFG_GET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 37,struct isp_core_cfg_info)
#define VIDIOC_K510ISP_SYSCTL_RST_CSI \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 38,unsigned long)
#define VIDIOC_K510ISP_SYSCTL_RST_VI \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 39,unsigned long)
#define VIDIOC_K510ISP_SYSCTL_RST_F2K \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 40,unsigned long)
#define VIDIOC_K510ISP_SYSCTL_RST_R2K \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 41,unsigned long)
#define VIDIOC_K510ISP_F2K_CORE_REG_SET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 42, struct k510isp_reg_val)
#define VIDIOC_K510ISP_F2K_CORE_REG_GET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 43, struct k510isp_reg_val)
#define VIDIOC_K510ISP_R2K_CORE_REG_SET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 44, struct k510isp_reg_val)
#define VIDIOC_K510ISP_R2K_CORE_REG_GET \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 45, struct k510isp_reg_val)
//
/*
 * Events
 *
 * V4L2_EVENT_K510ISP_AWB: AWB statistics data ready
 * V4L2_EVENT_K510ISP_AF: AF statistics data ready
 * V4L2_EVENT_K510ISP_AE: AE statistics data ready
 */

#define V4L2_EVENT_K510ISP_CLASS	    (V4L2_EVENT_PRIVATE_START | 0x100)
#define V4L2_EVENT_K510ISP_F2K_AWB	    (V4L2_EVENT_K510ISP_CLASS | 0x1)
#define V4L2_EVENT_K510ISP_F2K_AF		(V4L2_EVENT_K510ISP_CLASS | 0x2)
#define V4L2_EVENT_K510ISP_F2K_AE	    (V4L2_EVENT_K510ISP_CLASS | 0x3)
#define V4L2_EVENT_K510ISP_R2K_AWB	    (V4L2_EVENT_K510ISP_CLASS | 0x4)
#define V4L2_EVENT_K510ISP_R2K_AF		(V4L2_EVENT_K510ISP_CLASS | 0x5)
#define V4L2_EVENT_K510ISP_R2K_AE	    (V4L2_EVENT_K510ISP_CLASS | 0x6)
//3a
#define K510ISP_WIN_HZSTART_MIN		0
#define K510ISP_WIN_HZSTART_MAX		1919
#define K510ISP_WIN_VTSTART_MIN		0
#define K510ISP_WIN_VTSTART_MAX		1079
#define K510ISP_AF_PAXEL_SIZE		48
//awb
struct k510isp_awb_config{
    __u32 awb_en;//White balance enable
    __u32 awb_md_sl;//White balance mode selection, 1: auto, 0:handle
    __u32 awb_win_sl;//Auto while balance hist mode, 1: limited image 0: full image
    __u32 awb_vrf_en;//AWB verification enable
    __u32 awb_fb_en;//AWB mode selection, 1: feedback mode, 0: through mode
    __u32 awb_sv_en;//AWB value save enable, active
    __u32 awb_sbz_en;//AWB stabilization enable
    //
    __u32 awb_win_stth;//White balance window start (horizontal)
    __u32 awb_win_endh;//White balance window end (horizontal)
    __u32 awb_win_sttv;//White balance window start (vertical)
    __u32 awb_win_endv;//White balance window end (vertical)
    //
    __u32 awb_fb_th; //Difference threshold of white balance correction value
    __u32 awb_exch_th;//Response time of color sudden change
    __u32 awb_hist_th;//rgb threshold when color gain statistics
    //
    __u32 awb_rk;//Manual adjustment of red gain
    __u32 awb_gk;//Manual adjustment of green gain
    __u32 awb_bk;//Manual adjustment of blue gain
    //
    __u32 awb_rmax;//White balance value of red,max
    __u32 awb_bmax;//White balance value of blue,max
    __u32 awb_rmin;//White balance value of red,min
    __u32 awb_bmin;//White balance value of blue,min
    //
    __u32 awb_r_obj;//White balance object value of red
    __u32 awb_b_obj;//White balance object value of blue
};

struct k510isp_awb_sync_info {
    __u32 awb_ar; // AWB value of red
    __u32 awb_ab; // AWB value of blue
};

struct k510isp_awb_stats{
    //
    __u32 bfb_pos;//Blue hist value of AWB in feedback mode
    __u32 bfb_pot;//Blue hist pixels of AWB in feedback mode
    __u32 rfb_pos;//Red hist value of AWB in feedback mode
    __u32 rfb_pot;//Red hist pixels of AWB in feedback mode
    //
    __u32 bin_pos;//Blue hist value of AWB in bypass mode
    __u32 bin_pot;//Blue hist pixels of AWB in bypass mode
    __u32 rin_pos;//Red hist value of AWB in bypass mode
    __u32 rin_pot;//Red hist pixels of AWB in bypass mode
    //
    __u32 awb_ar;//AWB value of red
    __u32 awb_ag;//AWB value of green
    __u32 awb_ab;//AWB value of blue
    //
    __u32 awb_inr;//AWB value of red when only using original image
    __u32 awb_ing;//AWB value of green when only using original image
    __u32 awb_inb;//AWB value of blue when only using original image
};
//ae
struct k510isp_ae_config{
    __u32 ae_st_en;//Auto-shutter enable, active high
    __u32 ae_gain_en;//Auto-gain enable, active high
    __u32 ae_iris_en;//Auto-iris enable, active high
    __u32 ae_inlk_sl;//Enter lock status selection:1'b0: 32 frame; 1'b1: 64 frame
    __u32 ae_otlk_sl;//ae_Exit lock status selection:1'b0: 32 frame; 1'b1: 64 frame
    __u32 ae_win_sl;//window mode selection:2'b00: whole pictur,2'b01:central area,2'b10:Center-weighted measuring
    __u32 ae_md_sl;//Backlight Mode Selection
    __u32 ae_dn_hd_en;//Day and night handle change enable, active high
    __u32 ae_dn_s;//Day and night handle change selection, 1: night, 0:day
    //
    __u32 ae_win_stth;//Auto-exposure window start(horizontal)
    __u32 ae_win_endh;//Auto-exposure window end(horizontal)
    __u32 ae_win_sttv;//Auto-exposure window start(vertical)
    __u32 ae_win_endv;//Auto-exposure window end(vertical)
    //
    __u32 ae_yobj;//Target brightness of auto-exposure
    __u32 ae_av_rg;//Target brightness range. ([ae_yobj-ae_av_rg:[ae_yobj+ae_av_rg)
    //
    __u32 ae_exp_l;//Manual setting of exposure time for full image, long exposure frame
    __u32 ae_exp_m;//Manual setting of exposure time for full image, middle exposure frame
    __u32 ae_exp_s;//Manual setting of exposure time for full image, short exposure frame
    //
    __u32 ae_agc;//Manual setting of AGC val
    __u32 ae_chg_cnt_exp;//[3:0],ae_chg_cnt_exp:Adjusting frequency of shuttle
    __u32 ae_chg_cnt_agc;//,[7:4]:ae_chg_cnt_agc: Adjusting frequency of gain
    __u32 ae_num_max;//Adjusting step of auto-exposure, max
    __u32 ae_exp_max;//Auto-exposure value,max
    __u32 ae_exp_mid;//Auto-exposure value, mid
    __u32 ae_exp_min;//Auto-exposure value, min
    __u32 ae_agc_max;//Auto-gain value, max
    __u32 ae_agc_mid;//Auto-gain value, mid
    __u32 ae_agc_min;//Auto-gain value, min
    __u32 ae_dn_agcth;//Auto-exposure adjusting step, max
    __u32 ae_dn_tmth;//Waiting time of Day/Night switch
    __u32 apt_co_max;//Auto-aperture mode, difference between current luminance with target,max
    __u32 apt_drv_max;//Auto-aperture driver signal,max
    __u32 apt_ki;//Auto-aperture coefficient, distance
    __u32 apt_kp;//Auto-aperture coefficient, speed
    __u32 apt_kd;//Auto-aperture coefficient, acceleration
    __u32 apt_drv;//Manual setting of automatic aperture value
    __u32 apt_cnt;//Manual setting of automatic aperture value, damping
};

struct k510isp_ae_stats{
    __u32 ae_wren;//Auto-exposure value enable (It`s ready to be writen tp sensor)
    __u32 ae_expl;//Current exposure value, long exposure
    __u32 ae_expm;//Current exposure value, middle exposure
    __u32 ae_exps;//Current exposure value, short exposure
    __u32 ae_agco;//Current digital gain
    //
    __u32 y_av;//Current average brightness
    __u32 dn_st;//Current Day/Night status
    __u32 ae_exp_st;//Current exposure status
    __u32 ae_sum;//Total brightness statistics of auto-exposure
    __u32 ae_pxl;//Total number of auto-exposure pixel
};
//af
struct k510isp_af_config{
    __u32 af_sts_en;//AF statistics enable, active high
    __u32 af_sts_md;//AF statistics mode,2'b00: full image ; 2'b01: only inside 2'b10: 75% insdide window ;2'b11: 94% inside window
    __u32 af_win_stth;//AF statistics window start(horizontal)
    __u32 af_win_endh;//AF statistics window end(horizontal)
    __u32 af_win_sttv;//AF statistics window start(vertical)
    __u32 af_win_endv;//AF statistics window end(vertical)
};

struct k510isp_af_stats{
    __u32 af_mf;//AF statistics middle frequence
    __u32 af_hf;//AF statistics high frequence
    __u32 af_pxl;//AF statistics pixel num
};

/**
 * struct k510isp_stat_data - Statistic data sent to or received from user
 * @ts: Timestamp of returned framestats.
 * @buf: Pointer to pass to user.
 * @frame_number: Frame number of requested stats.
 * @cur_frame: Current frame number being processed.
 * @config_counter: Number of the configuration associated with the data.
 */
struct k510isp_stat_data {
	struct timeval ts;
	void *buf; //void __user *buf;
	__u32 buf_size;
	__u16 frame_number;
	__u16 cur_frame;
	__u16 config_counter;
};

struct k510isp_stat_event_status {
	__u32 frame_number;
	__u16 config_counter;
	__u8 buf_err;
};

struct k510isp_reg_val {
    __u32 reg_addr;
    __u32 reg_value;
};
#endif
