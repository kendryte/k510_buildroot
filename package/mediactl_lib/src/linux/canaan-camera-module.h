/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef _CANAAN_CAMERA_MODULE__H
#define _CANAAN_CAMERA_MODULE__H

#include <linux/types.h>

#define CNMODULE_NAME_LEN		64

#define CANAANMODULE_CAMERA_MODULE_INDEX	"canaanchip,camera-module-index"
#define CANAANMODULE_CAMERA_MODULE_FACING	"canaanchip,camera-module-facing"
#define CANAANMODULE_CAMERA_MODULE_NAME	"canaanchip,camera-module-name"
#define CANAANMODULE_CAMERA_LENS_NAME	"canaanchip,camera-module-lens-name"


#define CNMODULE_GET_MODULE_INFO	\
		_IOR('V', BASE_VIDIOC_PRIVATE + 0, struct cnmodule_inf)

#define CNMODULE_NORMAL_AE_EXP_CFG	\
		_IOW('V', BASE_VIDIOC_PRIVATE + 1, struct cnmodule_normal_ae_cfg)

#define CNMODULE_HDR_AE_EXP_CFG	\
		_IOW('V', BASE_VIDIOC_PRIVATE + 2, struct cnmodule_hdr_ae_cfg)

#define CNMODULE_GET_HDR_CFG	\
		_IOR('V', BASE_VIDIOC_PRIVATE + 3, struct cnmodule_hdr_cfg)

#define CNMODULE_SET_HDR_CFG	\
		_IOW('V', BASE_VIDIOC_PRIVATE + 4, struct cnmodule_hdr_cfg)



/**
 * struct cnmodule_base_inf - module base information
 *
 */
struct cnmodule_base_inf {
	char sensor[CNMODULE_NAME_LEN];
	char module[CNMODULE_NAME_LEN];
	char lens[CNMODULE_NAME_LEN];
};

/**
 * struct cnmodule_inf - module information
 *
 */
struct cnmodule_inf {
	struct cnmodule_base_inf base;
	//struct cnmodule_fac_inf fac;
	//struct cnmodule_awb_inf awb;
	//struct cnmodule_lsc_inf lsc;
	//struct cnmodule_af_inf af;
};

/**
 * struct cnmodule_hdr_ae_exp_cfg
 *
 */
struct cnmodule_normal_ae_cfg {
	__u32 exp_val;
	__u32 gain_val;
};

/**
 * struct cnmodule_hdr_ae_exp_cfg
 *
 */
struct cnmodule_hdr_ae_cfg {
	__u32 long_exp_val;
	__u32 long_gain_val;
	__u32 middle_exp_val;
	__u32 middle_gain_val;
	__u32 short_exp_val;
	__u32 short_gain_val;
};

struct cnmodule_hdr_cfg {
	__u32 hdr_mode;
};

/**
 * NO_HDR: linear mode
 * HDR_X2: hdr two frame mode
 * HDR_X3: hdr three frame mode
 */
enum cnmodule_hdr_mode {
	NO_HDR = 0,
	HDR_X2 = 1,
	HDR_X3 = 2,
};

#endif /* _CANAAN_CAMERA_MODULE__H */
