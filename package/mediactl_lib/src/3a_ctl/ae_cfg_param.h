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

#ifndef __3A_AE_CTL_CFG_H__
#define __3A_AE_CTL_CFG_H__

static AE_CTL_INIT_CFG_T ae_ctl_init_cfg_param_dual_imx219 =
{
	/* can modify */
	.bDualCameraSync           = 0,
	.nSingleSensorETDelayFrame = {1, 1}, // [0]: f2k, [1]: r2k
	.nSingleSensorSetMode      = {1, 1}, // [0]: f2k, [1]: r2k
	.nDualSensorETDelayFrame   = {1, 1}, // [0]: f2k, [1]: r2k
	.nDualSensorSetMode        = {1, 1}, // [0]: f2k, [1]: r2k
	.nFrameRate                = {30, 30}, // [0]: sensor0, [1]: sensor1
	/* do not change */
	.nAeSmoothSteps = 9,
};

static AE_CTL_INIT_CFG_T ae_ctl_init_cfg_param_dual_imx385 =
{
	/* can modify */
	.bDualCameraSync           = 0,
	.nSingleSensorETDelayFrame = {1, 1}, // [0]: f2k, [1]: r2k
	.nSingleSensorSetMode      = {0, 0}, // [0]: f2k, [1]: r2k
	.nDualSensorETDelayFrame   = {0, 0}, // [0]: f2k, [1]: r2k
	.nDualSensorSetMode        = {0, 0}, // [0]: f2k, [1]: r2k
	.nFrameRate                = {30, 30}, // [0]: sensor0, [1]: sensor1

	/* do not change */
	.nAeSmoothSteps = 9,
};

static AE_CTL_INIT_CFG_T ae_ctl_init_cfg_param_gc2093_gc2053 =
{
	/* can modify */
	.bDualCameraSync           = 0,
	.nSingleSensorETDelayFrame = {0, 0}, // [0]: f2k, [1]: r2k
	.nSingleSensorSetMode      = {0, 0}, // [0]: f2k, [1]: r2k
	.nDualSensorETDelayFrame   = {0, 0}, // [0]: f2k, [1]: r2k
	.nDualSensorSetMode        = {0, 0}, // [0]: f2k, [1]: r2k
	.nFrameRate                = {30, 30}, // [0]: sensor0, [1]: sensor1

	/* do not change */
	.nAeSmoothSteps = 9,
};

/* different sensor type between sensor0 and sensor1 */
// static AE_CTL_INIT_CFG_T ae_ctl_init_cfg_param_imx385_imx219 =
// {
// 	/* can modify */
// 	.bDualCameraSync           = 1,
// 	.nSingleSensorETDelayFrame = {1, 1}, // [0]: f2k, [1]: r2k
// 	.nSingleSensorSetMode      = {0, 0}, // [0]: f2k, [1]: r2k
// 	.nDualSensorETDelayFrame   = {0, 0}, // [0]: f2k, [1]: r2k
// 	.nDualSensorSetMode        = {0, 0}, // [0]: f2k, [1]: r2k
// 	.nFrameRate                = {30, 30}, // [0]: sensor0, [1]: sensor1

// 	/* do not change */
// 	.nAeSmoothSteps = 9,
// };

AE_CTL_SENSOR_NAME_T ae_ctl_sensor_name[] =
{
    // dual imx219(default)
    {
        .cSensor0Name = "m00_f_imx219_0 0-0010",
        .cSensor1Name = "m01_f_imx219_1 3-0010",
        .tAeCtlInitCfg = &ae_ctl_init_cfg_param_dual_imx219,
    },

    // dual imx385
    {
        .cSensor0Name = "m00_f_IMX385 0-001a",
        .cSensor1Name = "m00_f_imx385 3-001a",
        .tAeCtlInitCfg = &ae_ctl_init_cfg_param_dual_imx385,
    },

    // sensor0: gc2093, sensor1: gc2053
    {
        .cSensor0Name = "m00_f_gc2093 0-007e",
        .cSensor1Name = "m01_f_gc2053 0-0037",
        .tAeCtlInitCfg = &ae_ctl_init_cfg_param_gc2093_gc2053,
    },


	// // sensor0: imx385, sensor1: imx219
    // {
    //     .cSensor0Name = "m00_f_imx385_0 0-0010",
    //     .cSensor1Name = "m00_f_imx219_0 3-0010",
    //     .tAeCtlInitCfg = &ae_ctl_init_cfg_param_imx385_imx219,
    // },
};

AE_CTL_SENSOR_NAME_S_T ae_ctl_sensor_name_s =
{
	.nSize = sizeof(ae_ctl_sensor_name) / sizeof(AE_CTL_SENSOR_NAME_T),
	.tAeCtlSensorName = ae_ctl_sensor_name,
};

#endif