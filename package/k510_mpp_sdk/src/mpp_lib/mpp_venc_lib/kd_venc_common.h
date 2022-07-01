/* Copyright 2022 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
  File Name     : kd_venc_common.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef __KD_VENC_COMMON_H__
#define __KD_VENC_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum kdVENC_STATUS_S
{
    ENCODER_CREATED = 0,
    ENCODER_START,
    ENCODER_ENCODING,
    ENCODER_STOP,
    ENCODER_DESTROY,
} VENC_STATUS_S;

#ifdef __cplusplus
}
#endif

#endif // __KD_VENC_COMMON_H__