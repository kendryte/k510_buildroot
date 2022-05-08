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
#ifndef _VERIFY_COMMON_H
#define _VERIFY_COMMON_H
#include "io.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <k510_log.h>

#define VERIFY_SUCCESS 0
#define VERIFY_FAILED  -1

#define VERIFY_TEST_00                             (0)
#define VERIFY_TEST_UINT8_FF                       (0xff)
#define VERIFY_TEST_UINT16_FF                      (0xffff)
#define VERIFY_TEST_UINT32_FF                      (0xffffffffU)
#define VERIFY_TEST_UINT64_FF                      (0xffffffffffffffffUL)
#define VERIFY_TEST_UINT8_55		               (0x55)
#define VERIFY_TEST_UINT16_55		               (0x5555)
#define VERIFY_TEST_UINT32_55		               (0x55555555U)
#define VERIFY_TEST_UINT64_55		               (0x5555555555555555UL)
#define VERIFY_TEST_UINT8_AA                       (0xAA)
#define VERIFY_TEST_UINT16_AA                      (0xAAAA)
#define VERIFY_TEST_UINT32_AA                      (0xAAAAAAAAU)
#define VERIFY_TEST_UINT64_AA                      (0xAAAAAAAAAAAAAAAAUL)

typedef enum{
    VERIFY_SRAM,
    VERIFY_DDR,
    VERIFY_NOCACHE,
} verify_mem_type_t;

extern int g_result;

typedef enum
{
    VERIFY_RO = 1,
    VERIFY_WO,
    VERIFY_RW,
} verify_reg_type_t;

typedef struct
{
    uint32_t            offset;
    verify_reg_type_t   reg_type;
    uint32_t            mask;
    uint32_t            rst_val;
    char                name[32];
} verify_reg_t;

/* Pack of macros used to check values with immediate break of test */
#define verify_validate_xint(val,exp,teststr,varstr) \
                        do { if (val != exp) { k510_logci("%s:%d: TEST ERROR! %s - %s = 0x%08X, expected 0x%08X\n", \
                                       __func__, __LINE__, teststr, varstr, val, exp); g_result = VERIFY_FAILED;\
                          goto done;}} while (0)

#define verify_validate_int(val,exp,teststr,varstr) \
                            do { if (val != exp) { k510_logci("%s:%d: TEST ERROR! %s - %s = %d, expected %d\n", \
                                        __func__, __LINE__, teststr, varstr, val, exp); g_result = VERIFY_FAILED;\
                            goto done;}} while (0)

#define verify_validate_bool(val,exp,teststr,varstr) \
                            do { if (val != exp) { k510_logci("%s:%d: TEST ERROR! %s - %s = %d, expected %d\n", \
                                        __func__, __LINE__, teststr, varstr, val, exp); g_result = VERIFY_FAILED;\
                            goto done;}} while (0)

#define verify_validate_nxint(val,exp,teststr,varstr) \
    do { if (val == exp) { k510_logci("%s:%d: TEST ERROR! %s - %s = %X, expected not equal to  %X\n", \
                                       __func__, __LINE__, teststr, varstr, val, exp); g_result = VERIFY_FAILED;\
                          goto done;}} while (0)

#define verify_validate_nint(val,exp,teststr,varstr) \
                            do { if (val == exp) { k510_logci("%s:%d: TEST ERROR! %s - %s = %d, expected %d\n", \
                                        __func__, __LINE__, teststr, varstr, val, exp); g_result = VERIFY_FAILED;\
                            goto done;}} while (0)

#define verify_result(str)      if(g_result == VERIFY_SUCCESS)    \
                                {                               \
                                    k510_logci("[%s SIM_PASS]\n", str);   \
                                }                               \
                                else                            \
                                {                               \
                                    k510_logci("[%s SIM_FAIL]\n", str);   \
                                }

#define sys_exit()              exit(g_result)

#define verify_exit_result(str)     done:                           \
                                    if(g_result == VERIFY_SUCCESS)    \
                                    {                               \
                                        k510_logci("[%s SIM_PASS]\n", str);   \
                                    }                               \
                                    else                            \
                                    {                               \
                                        k510_logci("[%s SIM_FAIL]\n", str);   \
                                    }   \
                                    sys_exit()

#define verify_fail_exit_result(str)        done:                           \
                                            if(g_result == VERIFY_SUCCESS)  \
                                            {                               \
                                                if(is_dsp_type())          \
                                                { k510_logci("[DSP %s SIM_PASS]\n", str); sys_exit();}   \
                                            }                               \
                                            if(g_result != VERIFY_SUCCESS)    \
                                            {                               \
                                                k510_logci("[%s SIM_FAIL]\n", str);   \
                                                sys_exit();   \
                                            }

#define verify_fail_exit_pass_noexit_result(str)   done:                           \
                                            if(g_result != VERIFY_SUCCESS)    \
                                            {                               \
                                                k510_logci("[%s SIM_FAIL]\n", str);   \
                                                sys_exit();   \
                                            }


#define verify_compare_false_return(src, result)        if(src != result)                   \
                                                        {                                   \
                                                            k510_logci("%s:%d: TEST ERR\n", __func__, __LINE__);\
                                                            return VERIFY_FAILED;                      \
                                                        }

#define verify_compare_mem_uint8_false_return(addr, len, val)   \
                            g_result = verify_mem_compare_uint8(addr, len, val);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_uint16_false_return(addr, len, val)   \
                            g_result = verify_mem_compare_uint16(addr, len, val);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_uint32_false_return(addr, len, val)   \
                            g_result = verify_mem_compare_uint32(addr, len, val);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_uint64_false_return(addr, len, val)   \
                            g_result = verify_mem_compare_uint64(addr, len, val);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_sequnce_uint8_false_return(addr, len)   \
                            g_result = verify_mem_compare_sequnce_uint8(addr, len);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_sequnce_uint16_false_return(addr, len)   \
                            g_result = verify_mem_compare_sequnce_uint16(addr, len);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_sequnce_uint32_false_return(addr, len)   \
                            g_result = verify_mem_compare_sequnce_uint32(addr, len);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

#define verify_compare_mem_sequnce_uint64_false_return(addr, len)   \
                            g_result = verify_mem_compare_sequnce_uint64(addr, len);   \
                            verify_compare_false_return(g_result, VERIFY_SUCCESS);

int verify_writereg(uint64_t address, uint32_t value, bool print_err);
int verify_writereg_and_mask(uint64_t address, uint32_t value, uint32_t mask, bool print_err);

void verify_mem_set_uint8(intptr_t src, size_t len, uint8_t val);
void verify_mem_set_uint16(intptr_t src, size_t len, uint16_t val);
void verify_mem_set_uint32(intptr_t src, size_t len, uint32_t val);
void verify_mem_set_uint64(intptr_t src, size_t len, uint64_t val);

int verify_mem_compare_uint8(intptr_t src, size_t len, uint8_t val);
int verify_mem_compare_uint16(intptr_t src, size_t len, uint16_t val);
int verify_mem_compare_uint32(intptr_t src, size_t len, uint32_t val);
int verify_mem_compare_uint64(intptr_t src, size_t len, uint64_t val);

void verify_mem_set_sequnce_uint8(intptr_t src, size_t len);
void verify_mem_set_sequnce_uint16(intptr_t src, size_t len);
void verify_mem_set_sequnce_uint32(intptr_t src, size_t len);
void verify_mem_set_sequnce_uint64(intptr_t src, size_t len);

int verify_mem_compare_sequnce_uint8(intptr_t src, size_t len);
int verify_mem_compare_sequnce_uint16(intptr_t src, size_t len);
int verify_mem_compare_sequnce_uint32(intptr_t src, size_t len);
int verify_mem_compare_sequnce_uint64(intptr_t src, size_t len);

int verify_mem_random(intptr_t src, size_t len_uint8, size_t test_cnt);
int verify_mem_test(intptr_t addr, size_t len_uint8, verify_mem_type_t type);
int verify_memory(intptr_t addr, size_t len, verify_mem_type_t type, uint32_t loopcnt);

int verify_wait(uint32_t *val, uint32_t expt, uint32_t timeout);

void cpu_perf_init(void);
void cpu_perf_test(void);
#endif