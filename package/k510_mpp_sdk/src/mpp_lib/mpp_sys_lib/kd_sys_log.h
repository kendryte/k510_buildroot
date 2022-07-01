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
  File Name     : kd_mem_log.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef __KD_SYS_LOG_H__
#define __KD_SYS_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum kdLOG_LEVEL_E
{
    ERROR = 0,
    WARNING,
    INFO,
    DEBUG,
} LOG_LEVEL_E;

void initLog();
void printLog(const char *filename, int line, LOG_LEVEL_E enLevel, const char *fmt, ...) __attribute__((format(printf, 4, 5)));

#define KD_SYS_LOG_DEBUG(format, ...) printLog(__FILE__, __LINE__, DEBUG, format, ## __VA_ARGS__)
#define KD_SYS_LOG_INFO(format, ...) printLog(__FILE__, __LINE__, INFO, format, ## __VA_ARGS__)
#define KD_SYS_LOG_WARING(format, ...) printLog(__FILE__, __LINE__, WARNING, format, ## __VA_ARGS__)
#define KD_SYS_LOG_ERROR(format, ...) printLog(__FILE__, __LINE__, ERROR, format, ## __VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif // __KD_SYS_LOG_H__