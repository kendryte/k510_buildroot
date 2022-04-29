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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "hal_comm.h"
#include "hal_key.h"

int hal_key_open(const char *key, int mode)
{
	int ret = HAL_FAILURE;
    
    if (!key)
    {
        dbgmsg ("key is NULL\n");
        ret = HAL_FAILURE;
        goto EXIT;
    }

    ret = open(key, mode, 0777);
    if (0 > ret)
    {
        dbgmsg ("open %s failed: %s\n", key, strerror(errno));
        ret = HAL_FAILURE;
        goto EXIT;
    }

EXIT:
    return ret;
}

int hal_key_close(int *fd)
{
	int ret = HAL_FAILURE;
	
	if (!fd || *fd < 0)
	{
		dbgmsg("fd is NULL, or *fd < 0\n");
		ret = HAL_FAILURE;
		goto EXIT;
	}
	

    close (*fd);
    *fd = -1;
    ret = HAL_SUCCESS;
    
EXIT:
   	return ret;
}

int hal_key_read(int fd, key_result_t *result, callback_func_t cb)
{
	int ret = HAL_FAILURE;
	struct input_event ev;

	if (fd < 0)
	{
		dbgmsg("fd < 0\n");
		ret = HAL_FAILURE;
		goto EXIT;
	}

	if (!result)
	{
		dbgmsg("result is NULL\n");
		ret = HAL_FAILURE;
		goto EXIT;
	}
	
	memset(&ev, 0x00, sizeof(ev));
	ret = read(fd, &ev, sizeof(ev));
	if (ret != sizeof(ev))
	{
		dbgmsg("read length %d invalid\n", ret);
		ret = HAL_FAILURE;
		goto EXIT;
	}

	if (ev.type == EV_KEY)
	{
		result->code = ev.code;
		result->value = ev.value;
		result->time.tv_sec = ev.time.tv_sec;
		result->time.tv_usec = ev.time.tv_usec;

		if (cb)
			cb(result);
	}

	ret = sizeof(key_result_t);
EXIT:
	return ret;
}
