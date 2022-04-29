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
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define DEFAULT_OUTPUT_LENGTH 4
#define TRNG_DEV "/dev/hwrng"

struct param {
	uint32_t length;
};

static void show_help(void)
{
	printf("\
Usage: trng -b number\n\
use OPTION -h display a detailed description\n");
}

static void show_longhelp(void)
{
	printf("\
Usage: trng -b number\n\
    -h  display this help\n\
    -b  output byte number, default -b4\n");
}

static int parameter_parse(int argc, char *argv[], struct param *pp)
{
	int opt;
	int length;

	length = DEFAULT_OUTPUT_LENGTH;
	while ((opt = getopt(argc, argv, "hb:")) != -1) {
		switch (opt) {
		case 'b':
			length = strtoul(optarg, NULL, 0);
			length = length > 0 ? length : 0;
			break;
		case 'h':
			show_longhelp();
			exit(0);
		case '?':
			break;
		}
	}

	if (length == 0) {
		fprintf(stderr, "length invalid\n");
		show_help();
		return -EINVAL;
	}
	pp->length = length;

	return 0;
}

static int rng_generate(uint32_t length)
{
	int r, fd, rd;
	uint32_t cnt;
	uint8_t buff[32];

	if ((fd = open(TRNG_DEV, O_RDONLY)) < 0) {
		r = -errno;
		printf("RESULT:FAIL:open %s %s\n", TRNG_DEV,strerror(errno));
		return r;
	}

	while (length) {
		cnt = length > 32 ? 32 : length;
		rd = read(fd, buff, cnt);
		if (rd != cnt) {
			r = -errno;
			printf("RESULT:FAIL:read %s %s\n", TRNG_DEV,strerror(errno));
			close(fd);
			return r;
		}
		for (int i = 0; i < cnt; i++)
			printf("%02X", buff[i]);
		length -= cnt;
	}
	puts("");

	close(fd);

	return 0;
}

int main(int argc, char *argv[])
{
	int r;
	struct param p;

	if ((r = parameter_parse(argc, argv, &p)) != 0)
		goto error;
	r = rng_generate(p.length);
	if(r == 0)
		printf("RESULT:PASS\n");
error:
	return r;
}