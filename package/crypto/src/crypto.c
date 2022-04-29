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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_alg.h>

struct param {
	char *crypto_type;
	char *crypto_name;
	uint32_t crypto_op;
	char *crypto_key;
	char *crypto_iv;
	char *in_file;
	char *out_file;
};

struct crypto_config {
	char *crypto_type;
	char *crypto_name;
	char *in_file;
	char *out_file;
	int fd;
	FILE *in;
	FILE *out;
	uint32_t sha_len;
	uint32_t crypto_op;
	uint32_t key_len;
	uint32_t iv_len;
	uint8_t key[32];
	uint8_t iv[32];
};

static void show_help(void)
{
	printf("\
Usage: crypto_demo [OPTION]... IN_FILE OUT_FILE\n\
use OPTION -h display a detailed description\n");
}

static void show_longhelp(void)
{
	printf("\
Usage: crypto_demo [OPTION]... IN_FILE OUT_FILE\n\
    -h  display this help\n\
    -t  crypto type: hash,skcipher\n\
    -n  crypto name: sha256,cbc(aes),ecb(aes)\n\
    -x  decrypt\n\
    -k  crypto key\n\
    -v  crypto iv\n");
}

static int parameter_parse(int argc, char *argv[], struct param *pp)
{
	int opt;

	memset(pp, 0, sizeof(struct param));
	pp->crypto_op = ALG_OP_ENCRYPT;
	while ((opt = getopt(argc, argv, "hxt:n:k:v:")) != -1) {
		switch (opt) {
		case 't':
			pp->crypto_type = optarg;
			break;
		case 'n':
			pp->crypto_name = optarg;
			break;
		case 'k':
			pp->crypto_key = optarg;
			break;
		case 'v':
			pp->crypto_iv = optarg;
			break;
		case 'x':
			pp->crypto_op = ALG_OP_DECRYPT;
			break;
		case 'h':
			show_longhelp();
			exit(0);
		case '?':
			break;
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "no input file\n");
		show_help();
		return -EINVAL;
	}
	pp->in_file = argv[optind];
	optind++;
	if (optind >= argc) {
		fprintf(stderr, "no output file\n");
		show_help();
		return -EINVAL;
	}
	pp->out_file = argv[optind];

	return 0;
}

static int a2b_hex(char *s, uint8_t *buff, uint32_t len)
{
	if ((s == NULL) || (len == 0) || (strlen(s) < (len * 2))) {
		fprintf(stderr, "key or iv length too short\n");
		return -EINVAL;
	}

	for (int i = 0; i < len; i++) {
		if (sscanf(s, "%2hhx", buff) != 1) {
			fprintf(stderr, "key or iv parse error\n");
			return -EINVAL;
		}
		s += 2;
		buff++;
	}

	return 0;
}

static int parameter_check(struct param *pp, struct crypto_config *cfg)
{
	if (strcmp(pp->crypto_type, "hash") == 0) {
		if (strcmp(pp->crypto_name, "sha256") == 0)
			cfg->sha_len = 32;
	} else if (strcmp(pp->crypto_type, "skcipher") == 0) {
		if (strcmp(pp->crypto_name, "ecb(aes)") == 0) {
			cfg->key_len = 16;
			cfg->iv_len = 0;
			if (a2b_hex(pp->crypto_key, cfg->key, cfg->key_len) !=
			    0)
				return -EINVAL;
		} else if (strcmp(pp->crypto_name, "cbc(aes)") == 0) {
			cfg->key_len = 16;
			cfg->iv_len = 16;
			if (a2b_hex(pp->crypto_key, cfg->key, cfg->key_len) !=
			    0)
				return -EINVAL;
			if (a2b_hex(pp->crypto_iv, cfg->iv, cfg->iv_len) != 0)
				return -EINVAL;
		}
	} else {
		show_help();
		return -EINVAL;
	}

	cfg->crypto_type = pp->crypto_type;
	cfg->crypto_name = pp->crypto_name;
	cfg->crypto_op = pp->crypto_op;
	cfg->in_file = pp->in_file;
	cfg->out_file = pp->out_file;

	return 0;
}

static int do_sha(struct crypto_config *cfg)
{
	int r = 0, fd;
	uint8_t buff[4096];
	uint32_t rb, wb;

	fd = accept(cfg->fd, NULL, 0);

	while ((rb = fread(buff, 1, sizeof(buff), cfg->in)) == sizeof(buff))
		write(fd, buff, rb);

	if ((r = ferror(cfg->in)) != 0)
		goto error;

	if (rb)
		write(fd, buff, rb);

	read(fd, buff, cfg->sha_len);
	if ((wb = fwrite(buff, 1, cfg->sha_len, cfg->out)) != cfg->sha_len)
		r = ferror(cfg->out);

error:
	close(fd);

	return r;
}

static int do_aes(struct crypto_config *cfg)
{
	int r = 0, fd;
	uint8_t buff[4096];
	uint32_t rb, wb;
	struct msghdr msg = {};
	struct cmsghdr *cmsg;
	struct af_alg_iv *iv;

	setsockopt(cfg->fd, SOL_ALG, ALG_SET_KEY, cfg->key, cfg->key_len);
	fd = accept(cfg->fd, NULL, 0);

	msg.msg_control = buff;
	msg.msg_controllen =
		CMSG_SPACE(4) + (cfg->iv_len ? CMSG_SPACE(4 + cfg->iv_len) : 0);

	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_level = SOL_ALG;
	cmsg->cmsg_type = ALG_SET_OP;
	cmsg->cmsg_len = CMSG_LEN(4);
	*(uint32_t *)CMSG_DATA(cmsg) = cfg->crypto_op;

	if (cfg->iv_len) {
		cmsg = CMSG_NXTHDR(&msg, cmsg);
		cmsg->cmsg_level = SOL_ALG;
		cmsg->cmsg_type = ALG_SET_IV;
		cmsg->cmsg_len = CMSG_LEN(4 + cfg->iv_len);
		iv = (struct af_alg_iv *)CMSG_DATA(cmsg);
		iv->ivlen = cfg->iv_len;
		memcpy(iv->iv, cfg->iv, cfg->iv_len);
	}

	sendmsg(fd, &msg, 0);

	while ((rb = fread(buff, 1, sizeof(buff), cfg->in)) == sizeof(buff)) {
		write(fd, buff, rb);
		read(fd, buff, rb);
		if ((wb = fwrite(buff, 1, rb, cfg->out)) != rb) {
			r = ferror(cfg->out);
			goto error;
		}
	}

	if ((r = ferror(cfg->in)) != 0)
		goto error;

	if (rb) {
		if (rb & 0xf)
			memset(buff + rb, 0, 0x10 - (rb & 0xf));
		rb = (rb + 15) & (~0xful);
		write(fd, buff, rb);
		read(fd, buff, rb);
		if ((wb = fwrite(buff, 1, rb, cfg->out)) != rb) {
			r = ferror(cfg->out);
			goto error;
		}
	}

error:
	close(fd);

	return r;
}

static int do_crypto(struct crypto_config *cfg)
{
	int r = 0;
	struct sockaddr_alg sa = { .salg_family = AF_ALG };

	if ((cfg->in = fopen(cfg->in_file, "rb")) == NULL) {
		perror(cfg->in_file);
		return -errno;
	}

	if ((cfg->out = fopen(cfg->out_file, "wb")) == NULL) {
		r = -errno;
		perror(cfg->out_file);
		goto error1;
	}

	if ((cfg->fd = socket(AF_ALG, SOCK_SEQPACKET, 0)) == -1) {
		r = -errno;
		perror("");
		goto error2;
	}
	strncpy((char *)sa.salg_type, cfg->crypto_type, sizeof(sa.salg_type));
	strncpy((char *)sa.salg_name, cfg->crypto_name, sizeof(sa.salg_name));
	bind(cfg->fd, (struct sockaddr *)&sa, sizeof(sa));

	if (strcmp(cfg->crypto_type, "hash") == 0)
		r = do_sha(cfg);
	else
		r = do_aes(cfg);

	close(cfg->fd);
error2:
	fclose(cfg->out);
error1:
	fclose(cfg->in);

	return r;
}

int main(int argc, char *argv[])
{
	int r;
	struct param p;
	struct crypto_config cfg;

	if ((r = parameter_parse(argc, argv, &p)) != 0)
		goto error;
	if ((r = parameter_check(&p, &cfg)) != 0)
		goto error;
	r = do_crypto(&cfg);

error:
	return r;
}