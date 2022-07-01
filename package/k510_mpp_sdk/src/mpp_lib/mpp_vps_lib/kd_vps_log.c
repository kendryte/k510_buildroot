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
  File Name     : kd_vps_log.c
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
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <string.h>
#include "kd_vps_log.h"

static LOG_LEVEL_E enEnvLogLevel = ERROR;

void initLog()
{
    // set log level
    char *pEnvLog = getenv("VPSS_LOG_LEVEL");
    if (pEnvLog == NULL)
        return;

    int logLevel = atoi(pEnvLog);
    switch (logLevel)
    {
        case 0:
        {
            enEnvLogLevel = ERROR;
            break;
        }
        case 1:
        {
            enEnvLogLevel = WARNING;
            break;
        }
        case 2:
        {
            enEnvLogLevel = INFO;
            break;
        }
        case 3:
        {
            enEnvLogLevel = DEBUG;
            break;
        }
    }

    return;
}

static void getTimeStamp(char *buffer)
{
    time_t t;
    struct tm *p;
    struct timeval tv;
    int len;
    int millsec;

    t = time(NULL);
    p = localtime(&t);

    gettimeofday(&tv, NULL);
    millsec = (int)(tv.tv_usec / 1000);

    len = snprintf(buffer, 32, "[%04d-%02d-%02d %02d:%02d:%02d:%03d] ",
                    p->tm_year + 1990,
                    p->tm_mon + 1,
                    p->tm_mday,
                    p->tm_hour,
                    p->tm_min,
                    p->tm_sec,
                    millsec);

    buffer[len] = '\0';
}

void printLog(const char *filename, int line, LOG_LEVEL_E enLevel, const char *fmt, ...)
{
    if (enLevel > enEnvLogLevel)
        return;

    va_list arg_list;
    char buf[1024];
    memset(buf, 0, 1024);
    va_start(arg_list, fmt);
    vsnprintf(buf, 1024, fmt, arg_list);
    
    char time[32] = {0};
    const char *tmp = strrchr(filename, '/');
    if (!tmp)
    {
        tmp = filename;
    }
    else
    {
        tmp++;
    }

    getTimeStamp(time);

    switch (enLevel)
    {
        case DEBUG:
        {
            printf("\033[1;32m%s[%s] [%s:%d] %s\n\033[0m", time, "DEBUG", tmp, line, buf);
            break;
        }
        case INFO:
        {
            printf("\033[1;34m%s[%s] [%s:%d] %s\n\033[0m", time, "INFO", tmp, line, buf);
            break;
        }
        case WARNING:
        {
            printf("\033[1;31m%s[%s] [%s:%d] %s\n\033[0m", time, "WARNING", tmp, line, buf);
            break;
        }
        case ERROR:
        {
            printf("\033[1;33m%s[%s] [%s:%d] %s\n\033[0m", time, "ERROR", tmp, line, buf);
            break;
        }
    }
    va_end(arg_list);
}