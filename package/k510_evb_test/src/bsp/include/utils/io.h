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
#ifndef _DRIVER_IO_H
#define _DRIVER_IO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BIT33_NOCACHE_ADDR (0x100000000UL)

#define readb(addr) (*(volatile uint8_t *)((size_t)(addr)))
#define readw(addr) (*(volatile uint16_t *)((size_t)(addr)))
#define readl(addr) (*(volatile uint32_t *)((size_t)(addr)))
#define readq(addr) (*(volatile uint64_t *)((size_t)(addr)))

#define writeb(v, addr)                      \
    {                                        \
        (*(volatile uint8_t *)((size_t)(addr))) = (v); \
    }
#define writew(v, addr)                       \
    {                                         \
        (*(volatile uint16_t *)((size_t)(addr))) = (v); \
    }
#define writel(v, addr)                       \
    {                                         \
        (*(volatile uint32_t *)((size_t)(addr))) = (v); \
    }
#define writeq(v, addr)                       \
    {                                         \
        (*(volatile uint64_t *)((size_t)(addr))) = (v); \
    }

#define readb_nocache(addr) (*(volatile uint8_t  *)((size_t)(addr) | BIT33_NOCACHE_ADDR))
#define readw_nocache(addr) (*(volatile uint16_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR))
#define readl_nocache(addr) (*(volatile uint32_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR))
#define readq_nocache(addr) (*(volatile uint64_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR))

#define writeb_nocache(v, addr)                      \
    {                                        \
        (*(volatile uint8_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR)) = (v); \
    }
#define writew_nocache(v, addr)                       \
    {                                         \
        (*(volatile uint16_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR)) = (v); \
    }
#define writel_nocache(v, addr)                       \
    {                                         \
        (*(volatile uint32_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR)) = (v); \
    }
#define writeq_nocache(v, addr)                       \
    {                                         \
        (*(volatile uint64_t *)((size_t)(addr) | BIT33_NOCACHE_ADDR)) = (v); \
    }

#define NOCACHE_ADDR(addr)         ((size_t)(addr) | BIT33_NOCACHE_ADDR)

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_IO_H */
