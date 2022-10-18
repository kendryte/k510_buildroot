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

#ifndef _ADAPTIVE_PARAMS_SETTING_
#define _ADAPTIVE_PARAMS_SETTING_

/* f2k adaptive param include */
#include "sensor_params/imx219/adaptive_imx219_f2k.h"
#include "sensor_params/imx385/adaptive_imx385_f2k.h"
#include "sensor_params/gc2093_gc2053/adaptive_gc2093_f2k.h"

/* r2k adaptive param include */
#include "sensor_params/imx219/adaptive_imx219_r2k.h"
#include "sensor_params/imx385/adaptive_imx385_r2k.h"
#include "sensor_params/gc2093_gc2053/adaptive_gc2053_r2k.h"



#include "adaptive_setting.h"

/* user use different sensor will use corresponding param */
ADAPTIVE_SENSOR_NAME_T adaptive_sensor_name[] =
{
    // imx219(default)
    {
        .cSensor0Name = "m00_f_imx219_0 0-0010",
        .cSensor1Name = "m01_f_imx219_1 3-0010",
        .tAdapIspParamF2k = &adap_imx219_f2k,
        .tAdapIspParamR2k = &adap_imx219_r2k,
    },
    // imx385
    {
        .cSensor0Name = "m00_f_IMX385 0-001a",
        .cSensor1Name = "m00_f_imx385 3-001a",
        .tAdapIspParamF2k = &adap_imx385_f2k,
        .tAdapIspParamR2k = &adap_imx385_r2k,
    },
    // gc2093_gc2053
    {
        .cSensor0Name = "m00_f_gc2093 0-007e",
        .cSensor1Name = "m01_f_gc2053 0-0037",
        .tAdapIspParamF2k = &adap_gc2093_f2k,
        .tAdapIspParamR2k = &adap_gc2053_r2k,
    },
};

ADAPTIVE_SENSOR_NAME_S_T adaptive_sensor_name_s =
{
    .size = sizeof(adaptive_sensor_name) / sizeof(ADAPTIVE_SENSOR_NAME_T),
    .tAdaptiveSensorName = adaptive_sensor_name,
};
#endif