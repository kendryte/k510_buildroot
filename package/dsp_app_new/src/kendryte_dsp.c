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
#include <sys/ioctl.h>
#include <kendryte_cmem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <kendryte_dsp.h>

static kendryte_cmem_t dsp_cmem;

static long get_file_size(const char *path)
{
    long filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0) {
        return filesize;
    } else {
        filesize = statbuff.st_size;
    }
    return filesize;
}

int kendryte_dsp_load_bin(intptr_t addr, const char *path)
{
    int ret = 0;
    long dsp_file_size;
    int fd_dsp;
    int read_size;
    if(path == NULL) {
        printf("ERR: The dsp bin path is NULL\n");
        ret = -1;
        goto dsp_load_err2;
    }
    dsp_file_size = get_file_size(path);
    if(dsp_file_size <= 0) {
        printf("ERR: Dsp bin file err, please put the correct path\n");
        ret = -1;
        goto dsp_load_err2;
    }
    dsp_cmem.pa_addr = addr;
    dsp_cmem.size = dsp_file_size;

    if(kendryte_cmem_init(&dsp_cmem) < 0) {
        printf("ERR: Alloc DSP memory err\n");
        ret = -1;
        goto dsp_load_err2;
    }

    if((fd_dsp = open(path, O_RDWR)) < 0) {
        printf("ERR: Open %s err\n", path);
        ret = -1;
        goto dsp_load_err1;
    }

    read_size = read(fd_dsp, dsp_cmem.va_addr, dsp_file_size);
    if(read_size != dsp_file_size) {
        printf("ERR: Read %s err. File size is %d, But read %d\n", path, dsp_file_size, read_size);
        ret = -1;
    }

    close(fd_dsp);
dsp_load_err1:
    kendryte_cmem_deinit(&dsp_cmem);
dsp_load_err2:
    return ret;
}

int kendryte_dsp_boot(unsigned long reset_vector)
{
    int ret = 0;
    int fd_dsp;
    if((fd_dsp = open(DSP_DEV, O_RDWR)) < 0)
    {
        printf("ERR: Open %s err\n", DSP_DEV);
        ret = -1;
        goto dsp_boot_err0;
    }

    if (ioctl(fd_dsp, DSP_CMD_BOOT, reset_vector) < 0)
    {
        printf("Call cmd DSP_CMD_BOOT fail\n");
        ret = -1;
    }

    close(fd_dsp);
dsp_boot_err0:
    return ret;
}