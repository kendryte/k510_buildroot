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
#include "verify_common.h"
#include <stdio.h>
#include <string.h>
#include <cache.h>
#include <stdlib.h>
#include <sleep.h>

int g_result = VERIFY_SUCCESS; /* any validate__ fail will clear this */

int verify_writereg(uint64_t address, uint32_t value, bool print_err)
{
    uint32_t status;
    uint32_t reg;

    writel(value, address);
    reg = readl(address);

    if (reg == value)
    {
        status = VERIFY_SUCCESS;
    }
    else
    {
        if(print_err)
            k510_logce("Error: Register %08lX verification failed, written:%08x read:%08x \n",address, value, reg);
        status = VERIFY_FAILED;
    }

    return status;
}

int verify_writereg_and_mask(uint64_t address, uint32_t value, uint32_t mask, bool print_err)
{
    uint8_t retVal;
    uint32_t reg;
    writel(value, address);
    reg = readl(address);

    value &= mask;
    reg &= mask;

    if (reg == value)
    {
        retVal = VERIFY_SUCCESS;
    }
    else
    {
        if(print_err)
            k510_logce("Error: Register %08lX verification failed, written:%08x read:%08x \n",address, value, reg);
        retVal = VERIFY_FAILED;
    }

    return retVal;
}

int verify_mem_compare_uint8(intptr_t src, size_t len, uint8_t val)
{
    uint8_t *addr = (uint8_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != val)
        {
            k510_logce("%p  err 0x%02X expected 0x%02X\n", addr - 1, *(addr - 1), val);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

int verify_mem_compare_uint16(intptr_t src, size_t len, uint16_t val)
{
    uint16_t *addr = (uint16_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != val)
        {
            k510_logce("0x%p  err 0x%04X expected %04X\n", addr - 1, *(addr - 1), val);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

int verify_mem_compare_uint32(intptr_t src, size_t len, uint32_t val)
{
    uint32_t *addr = (uint32_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != val)
        {
            k510_logce("0x%p  err 0x%08X expected %08X\n", addr - 1, *(addr - 1), val);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

int verify_mem_compare_uint64(intptr_t src, size_t len, uint64_t val)
{
    uint64_t *addr = (uint64_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != val)
        {
            k510_logce("0x%p  err 0x%16lX expected %16lX\n", addr - 1, *(addr - 1), val);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

void verify_mem_set_uint8(intptr_t src, size_t len, uint8_t val)
{
    uint8_t *addr = (uint8_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = val;
    }
}

void verify_mem_set_uint16(intptr_t src, size_t len, uint16_t val)
{
    uint16_t *addr = (uint16_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = val;
    }
}

void verify_mem_set_uint32(intptr_t src, size_t len, uint32_t val)
{
    uint32_t *addr = (uint32_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = val;
    }
}

void verify_mem_set_uint64(intptr_t src, size_t len, uint64_t val)
{
    uint64_t *addr = (uint64_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = val;
    }
}

void verify_mem_set_sequnce_uint8(intptr_t src, size_t len)
{
    uint8_t *addr = (uint8_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = i & 0xFF;
    }
}

void verify_mem_set_sequnce_uint16(intptr_t src, size_t len)
{
    uint16_t *addr = (uint16_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = i & 0xFFFF;
    }
}

void verify_mem_set_sequnce_uint32(intptr_t src, size_t len)
{
    uint32_t *addr = (uint32_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = i & 0xFFFFFFFFU;
    }
}

void verify_mem_set_sequnce_uint64(intptr_t src, size_t len)
{
    uint64_t *addr = (uint64_t *)src;
    for(size_t i = 0; i < len; i++)
    {
        *addr++ = i;
    }
}

int verify_mem_compare_sequnce_uint8(intptr_t src, size_t len)
{
    uint8_t *addr = (uint8_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != (i & 0xFF))
        {
            k510_logce("%p  err 0x%02X expected %02lX\n", addr - 1, *(addr - 1), i);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

int verify_mem_compare_sequnce_uint16(intptr_t src, size_t len)
{
    uint16_t *addr = (uint16_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != (i & 0xFFFF))
        {
            k510_logce("%p  err 0x%04X expected %04lX\n", addr - 1, *(addr - 1), i);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

int verify_mem_compare_sequnce_uint32(intptr_t src, size_t len)
{
    uint32_t *addr = (uint32_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != (i & 0xFFFFFFFFU))
        {
            k510_logce("%p  err 0x%08X expected %08lX\n", addr - 1, *(addr - 1), i);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

int verify_mem_compare_sequnce_uint64(intptr_t src, size_t len)
{
    uint64_t *addr = (uint64_t *)src;
	for(size_t i = 0; i < len; i++)
	{
		if(*addr++ != i)
        {
            k510_logce("%p  err 0x%16lX expected %16lX\n", addr - 1, *(addr - 1), i);
			return VERIFY_FAILED;
        }
	}
	return VERIFY_SUCCESS;
}

#define random(x) (rand()%x)

int verify_mem_random(intptr_t src, size_t len_uint8, size_t test_cnt)
{
    intptr_t addr;
    uint8_t  val;
    for(size_t i = 0; i < test_cnt; i++)
    {
        addr = src + random(len_uint8);
        val = random(256);
        writeb(val, addr);
        verify_compare_false_return(readb(addr), val);
        if((i + 1) % (1 * 1024 * 1024) == 0)        // 1MB
        {
            k510_logntabd("Random %ld\n", i);
        }
    }
    return VERIFY_SUCCESS;
}

int verify_mem_test(intptr_t addr, size_t len_uint8, verify_mem_type_t type)
{
    size_t len_uint16 = len_uint8 >> 1;
    size_t len_uint32 = len_uint8 >> 2;
    size_t len_uint64 = len_uint8 >> 3;

    k510_logci("Cache Enable\n");
    cache_enable();

    k510_logci("Read Write 0x00\n");
    memset((uint8_t *)addr, VERIFY_TEST_00, len_uint8);
    cache_flush();
    verify_compare_mem_uint64_false_return(addr, len_uint64, VERIFY_TEST_00);

    k510_logci("Read Write 0xFF\n");
    memset((uint8_t *)addr, VERIFY_TEST_UINT8_FF, len_uint8);
    cache_flush();
    verify_compare_mem_uint64_false_return(addr, len_uint64, VERIFY_TEST_UINT64_FF);

    k510_logci("Read Write 0x55\n");
    memset((uint8_t *)addr, VERIFY_TEST_UINT8_55, len_uint8);
    cache_flush();
    verify_compare_mem_uint64_false_return(addr, len_uint64, VERIFY_TEST_UINT64_55);

    k510_logci("Read Write 0xAA\n");
    memset((uint8_t *)addr, VERIFY_TEST_UINT8_AA, len_uint8);
    cache_flush();
    verify_compare_mem_uint64_false_return(addr, len_uint64, VERIFY_TEST_UINT64_AA);

    k510_logci("Sequential Testing\n");
    if(len_uint8 <= 0x100UL) /* 0 ~ 256 char */
    {
        verify_mem_set_sequnce_uint8(addr, len_uint8);
        cache_flush();
        verify_compare_mem_sequnce_uint8_false_return(addr, len_uint8);
    }
    else if(len_uint8 <= 0x20000UL)  /* short */
    {
        verify_mem_set_sequnce_uint16(addr, len_uint16);
        cache_flush();
        verify_compare_mem_sequnce_uint16_false_return(addr, len_uint16);
    }
    else if(len_uint8 <= 0x400000000UL) /* int */
    {
        verify_mem_set_sequnce_uint32(addr, len_uint32);
        cache_flush();
        verify_compare_mem_sequnce_uint32_false_return(addr, len_uint32);
    }
    else    /* long */
    {
        verify_mem_set_sequnce_uint64(addr, len_uint64);
        cache_flush();
        verify_compare_mem_sequnce_uint64_false_return(addr, len_uint64);
    }

    if(type != VERIFY_NOCACHE)
    {
        k510_logci("Cache Disable\n");
        cache_flush_disable();
        l1icache_enable();
    }

    if(type == VERIFY_SRAM || type == VERIFY_NOCACHE)
    {
        k510_logci("Char   Read Write\n");
        verify_mem_set_uint8(addr, len_uint8, VERIFY_TEST_UINT8_55);
        verify_compare_mem_uint8_false_return(addr, len_uint8, VERIFY_TEST_UINT8_55);

        k510_logci("Short  Read Write\n");
        verify_mem_set_uint16(addr, len_uint16, VERIFY_TEST_UINT16_AA);
        verify_compare_mem_uint16_false_return(addr, len_uint16, VERIFY_TEST_UINT16_AA);

        k510_logci("Int    Read Write\n");
        verify_mem_set_uint32(addr, len_uint32, VERIFY_TEST_UINT32_55);
        verify_compare_mem_uint32_false_return(addr, len_uint32, VERIFY_TEST_UINT32_55);

        k510_logci("Long   Read Write\n");
        verify_mem_set_uint64(addr, len_uint64, VERIFY_TEST_UINT64_AA);
        verify_compare_mem_uint64_false_return(addr, len_uint64, VERIFY_TEST_UINT64_AA);

        k510_logci("Random Testing\n");
        return verify_mem_random(addr, len_uint8, len_uint8);
    }
    else
    {
        k510_logci("Short  Read Write\n");
        writew(VERIFY_TEST_UINT16_AA, addr);
        writew(VERIFY_TEST_UINT16_AA, (addr + len_uint8 / 2));
        writew(VERIFY_TEST_UINT16_AA, (addr + len_uint8 - 2));
        verify_compare_false_return(readw(addr), VERIFY_TEST_UINT16_AA);
        verify_compare_false_return(readw(addr + len_uint8 / 2), VERIFY_TEST_UINT16_AA);
        verify_compare_false_return(readw(addr + len_uint8 - 2), VERIFY_TEST_UINT16_AA);

        k510_logci("Int    Read Write\n");
        writel(VERIFY_TEST_UINT32_AA, addr);
        writel(VERIFY_TEST_UINT32_AA, (addr + len_uint8 / 2));
        writel(VERIFY_TEST_UINT32_AA, (addr + len_uint8 - 4));
        verify_compare_false_return(readl(addr), VERIFY_TEST_UINT32_AA);
        verify_compare_false_return(readl(addr + len_uint8 / 2), VERIFY_TEST_UINT32_AA);
        verify_compare_false_return(readl(addr + len_uint8 - 4), VERIFY_TEST_UINT32_AA);

        k510_logci("Random Testing\n");
        return verify_mem_random(addr, len_uint8, 100 * 1024);
    }
}

int verify_memory(intptr_t addr, size_t len, verify_mem_type_t type, uint32_t loopcnt)
{
    int ret;
    for(uint32_t i = 0; i < loopcnt; i++)
    {
        k510_logci("Loop %d\n", i);
        ret = verify_mem_test(addr, len, type);
        verify_compare_false_return(ret, VERIFY_SUCCESS);
    }
    return VERIFY_SUCCESS;
}

int verify_wait(uint32_t *val, uint32_t expt, uint32_t timeout)
{
    while(--timeout)
    {
        if(*val == expt)
            break;
        else
            usleep(1);
    }

    if(timeout == 0)
        return VERIFY_FAILED;

    return VERIFY_SUCCESS;
}


#define CPU_TEST_DET_ADDR       (0x80100000U)
#define CPU_TEST_SRC_ADDR       (0x80080000U)
#define CPU_TEST_LEN            (0x80000)
#define CPU_LOOP_CNT            (10)

void cpu_perf_init(void)
{
    memset((void *)CPU_TEST_SRC_ADDR, VERIFY_TEST_UINT8_AA, CPU_TEST_LEN);
}

void cpu_perf_test(void)
{
    uint64_t start, stop;

    start = read_cycle();
    for(uint32_t i = 0; i < CPU_LOOP_CNT; i++)
    {
        memcpy((void *)CPU_TEST_DET_ADDR, (void *)CPU_TEST_SRC_ADDR, CPU_TEST_LEN);
    }
    stop = read_cycle();
    if(read_coreid() == 0)
        sleep(1);
    k510_logi("Core%ld use %ld cycle\n",read_coreid(), stop - start);
}

