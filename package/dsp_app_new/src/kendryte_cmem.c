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
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <kendryte_cmem.h>

int kendryte_cmem_init(kendryte_cmem_t *cmem)
{
    if(cmem == NULL)
    {
        printf("CMEM: ERR: cmem is NULL\n");
        return -1;
    }

    cmem->fd_mem = open("/dev/mem", O_RDWR | O_SYNC);
    if (cmem->fd_mem == -1) {
        printf("CMEM: failed to open /dev/mem!");
        return -1;
    } else {
        printf("CMEM: Open /dev/mem success, fd is %d\n", cmem->fd_mem);
    }

    cmem->va_addr = mmap(NULL, cmem->size, PROT_READ | PROT_WRITE,
                MAP_SHARED, cmem->fd_mem, cmem->pa_addr | 0x100000000);
    if (cmem->va_addr == MAP_FAILED) {
        close(cmem->fd_mem);
        printf("CMEM: failed to mmap /dev/mem!");
        return -1;
    } else {
        printf("CMEM: Mmap 0x%08X size %d success, VA is 0x%08X\n", cmem->pa_addr, cmem->size, cmem->va_addr);
    }
    return 0;
}

int kendryte_cmem_deinit(kendryte_cmem_t *cmem)
{
    if(cmem) {
        if(cmem->va_addr) {
            if (munmap(cmem->va_addr, cmem->size) == -1) {
                printf("CMEM: failed to munmap /dev/mem!");
                return -1;
            } else {
                printf("CMEM: 0x%08X size %d unmap success\n", cmem->pa_addr, cmem->size);
                cmem->va_addr = NULL;
            }
        } else {
            printf("CMEM: Warning: cmem->va_addr is NULL\n");
        }

        if(cmem->fd_mem >= 0) {
            close(cmem->fd_mem);
            cmem->fd_mem = -1;
        } else {
            printf("CMEM: Warning: fd < 0\n");
        }
    } else {
        printf("CMEM: ERR: The cmem is NULL\n");
        return -1;
    }

    return 0;
}
