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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "key.h"
#include "hal_comm.h"
#include "hal_key.h"

#define DEV_PATH_FMT	"/dev/input/event%d"
#define CLASS_PATH_FMT	"/sys/class/input/event%d/device/name"
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

static key_result_t g_result[2];
unsigned short key_code = 0;
unsigned short key_value = 0;
static int get_event_dev_id(const char *name);
static void key_result_callback(key_result_t *result);
key_result_t pre_result;

static int get_event_dev_id(const char *name)
{
	int ret = -1;
	int c_try = 20;
	int id = 0;
	int fd = -1;
	
	char file[128];
	char buf[1024];

	if (!name)
	{
		printf("name is NULL\n");
		ret = -1;
		goto EXIT;
	}
	
	while(c_try--)
	{
		memset(file, 0x00, sizeof(file));
		ret = snprintf(file, sizeof(file), CLASS_PATH_FMT, id);
		if (ret >= sizeof(file) || ret < 0)
		{
			printf("snprintf failed");
			ret = -1;
			goto EXIT;
		}

		if (!access(file, F_OK))
		{
			fd = open(file, O_RDONLY);
			if (fd < 0)
			{
				printf("open %s failed: %s\n", file, strerror(errno));
				ret = -1;
				goto EXIT;
			}

			memset(buf, 0x00, sizeof(buf));
			ret = read(fd, buf, sizeof(buf));
			if (ret <= 0)
			{
				printf("read %s failed: %s\n", file, strerror(errno));
				ret = -1;
				goto EXIT;
			}

			close(fd);
			fd = -1;

			if (strstr(buf, name))
			{
				ret = id;
				goto EXIT;
			}
			
		}
		else
		{
			ret = id = -1;
			goto EXIT;
		}

		id++;
	}

	if (c_try <= 0)
		ret = id = -1;

EXIT:
	if (fd > 0)
		close(fd);
	return ret;
}




int get_keys()
{
	int ret = -1;
	int id = -1;
	int key_fd = -1;
	
	char key[128];
	
	id = get_event_dev_id("gpio-keys");
	if (id < 0)
	{
		ret = -1;
		goto EXIT;
	}

	memset(key, 0x00, sizeof(key));
	ret = snprintf(key, sizeof(key), DEV_PATH_FMT, id);
	if (ret >= sizeof(key) || ret < 0)
	{
		dbgmsg("snprintf failed");
		ret = -1;
		goto EXIT;
	}

	key_fd = hal_key_open(key, O_RDONLY);
	if (key_fd < 0)
	{
		ret = -1;
		goto EXIT;
	}

	memset(g_result, 0x00, sizeof(g_result));
	//while (1)
	{
		memset(&pre_result, 0x00, sizeof(pre_result));
		ret = hal_key_read(key_fd, &pre_result, key_result_callback);
		if (ret != sizeof(pre_result))
		{
			ret = -1;
			goto EXIT;
		}
		if(key_code == 30 || key_code == 48)
		{
			ret = 1;
			goto EXIT;
		}
	}
	hal_key_close(&key_fd);
EXIT:
	if (key_fd > 0)
		hal_key_close(&key_fd);
	return ret;
}
static void key_result_callback(key_result_t *result)
{
	int i = 0;
	printf(">>>>> key code: %d, action: %s <<<<<\n", result->code, result->value?"pressed":"released");
	key_code = result->code;
	key_value = result->value;
}
int key_init(void)
{
	return -1;
}
int key_get(void)
{
	char rc = 0;
	if (get_keys() != -1)
	{
		if(key_code == 30)
			rc = 1;
		else if(key_code == 48)
			rc = 2;
		else
			rc = 0;
			
	}
	return rc;
}


