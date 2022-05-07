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
#include <sys/stat.h>
#include <k510.h>
#include "uart.h"
#include "interrupt.h"
#include "cache.h"
#include "atomic.h"
#include <string.h>
#include "muxpin.h"
#include "k510_log.h"
#include "cache.h"
#include "lpddr3.h"

extern void reset_vector(void);
extern void __libc_init_array(void);
extern void __libc_fini_array(void);

extern volatile uint64_t g_wake_up[2];

core_instance_t core1_instance;

static bool k510_print_flag = true;

void k510_print_enable(bool en)
{
    k510_print_flag = en;
}

bool k510_get_print_status(void)
{
    return k510_print_flag;
}

uint32_t g_dbg_log_lvl = LOG_INFO;

/*
 * When compiling C++ code with static objects, the compiler inserts
 * a call to __cxa_atexit() with __dso_handle as one of the arguments.
 * The dummy versions of these symbols should be provided.
 */
void __cxa_atexit(void (*arg1)(void*), void* arg2, void* arg3)
{
}

void*   __dso_handle = (void*) &__dso_handle;

/* This must be a leaf function, no child function */
void __platform_init (void) __attribute__((naked));
void __platform_init(void)
{
    /* Do your platform low-level initial */

    __asm("ret");
}

void c_startup(void)
{
#define MEMCPY(des, src, n)     __builtin_memcpy ((des), (src), (n))
#define MEMSET(s, c, n)         __builtin_memset ((s), (c), (n))
    /* Data section initialization */
    extern char  _edata, _end;
    unsigned int size;

    /* Clear bss section */
    size = &_end - &_edata;
#ifndef NOMEMINIT
    MEMSET(&_edata, 0, size);
#endif
}

void core_init(void)
{
    /* Enable PLIC features */
    if (read_csr(NDS_MMISC_CTL) & (1 << 1)) {
        /* External PLIC interrupt is vectored */
        __nds__plic_set_feature(NDS_PLIC_FEATURE_PREEMPT | NDS_PLIC_FEATURE_VECTORED);
    } else {
        /* External PLIC interrupt is NOT vectored */
        __nds__plic_set_feature(NDS_PLIC_FEATURE_PREEMPT);
    }

    /* Enable Misaligned access */
    set_csr(NDS_MMISC_CTL, (1 << 6));
}

void system_init(void)
{
	core_init();
	/* Initial UART port */
	uart_debug_init(UART_DEVICE_0, 115200);
}

int register_core1(core_function func, void *ctx)
{
    if(func == NULL)
        return -1;
    core1_instance.callback = func;
    core1_instance.ctx = ctx;
    g_wake_up[1] = 1;
    return 0;
}

void core1_waiting(void)
{
    while(g_wake_up[1] == 0);
}

#define _SIMU_CACHE_FLUSH  0

#ifdef _SIMU
#define SIMU_DSP_PRINT_BASE (0x800FFE00UL)
#define SIMU_PRINT_BASE     (SIMU_DSP_PRINT_BASE + 0x100UL)
#define SIMU_PRINT_LEN  124

corelock_t lock = CORELOCK_INIT;

typedef struct _simu_print{
    uint8_t start;
    uint8_t end;
    uint16_t length;
    char str[SIMU_PRINT_LEN];
} simu_print_t;

extern uint32_t g_trap_status[2];
#if _SIMU_CACHE_FLUSH
static void simu_print_init(void)
{
    simu_print_t *v_simu_print;
    v_simu_print = (simu_print_t *)SIMU_DSP_PRINT_BASE;
    v_simu_print->start = 0;
    v_simu_print->end = 1;
    (v_simu_print + 1)->start = 0;
    (v_simu_print + 1)->end = 1;
    (v_simu_print + 2)->start = 0;
    (v_simu_print + 2)->end = 1;
    (v_simu_print + 3)->start = 0;
    (v_simu_print + 3)->end = 1;
    cache_flush();
}

static void simu_print(char *ptr, int len)
{
    uint64_t v_coreid = read_coreid();
    simu_print_t *v_simu_print = (simu_print_t *)((is_dsp_type() ? SIMU_DSP_PRINT_BASE : SIMU_PRINT_BASE) + sizeof(simu_print_t) * (g_trap_status[v_coreid] > 0 ? 1 : 0));

    while(v_simu_print->start)
    {
        cache_flush();
    }
    memcpy(v_simu_print->str, ptr, len);
    if(len < SIMU_PRINT_LEN)
        writeb(0, (intptr_t)(v_simu_print->str) + len);
    v_simu_print->length = len;
    cache_flush();
    writew(0x1, &v_simu_print->start); /* set start to 1, end to 0 */
    /* Flush Cache */
    cache_flush();
}
#else
void simu_print_init(void)
{
    simu_print_t *v_simu_print;
    v_simu_print = (simu_print_t *)SIMU_DSP_PRINT_BASE;
    v_simu_print->start = 0;
    v_simu_print->end = 1;
    (v_simu_print + 1)->start = 0;
    (v_simu_print + 1)->end = 1;
    (v_simu_print + 2)->start = 0;
    (v_simu_print + 2)->end = 1;
    (v_simu_print + 3)->start = 0;
    (v_simu_print + 3)->end = 1;
    cache_wb((intptr_t)(SIMU_DSP_PRINT_BASE), (intptr_t)(SIMU_DSP_PRINT_BASE), 512);
}

static void simu_print(char *ptr, int len)
{
    uint64_t v_coreid = read_coreid();
    simu_print_t *v_simu_print = (simu_print_t *)((is_dsp_type() ? SIMU_DSP_PRINT_BASE : SIMU_PRINT_BASE) + sizeof(simu_print_t) * (g_trap_status[v_coreid] > 0 ? 1 : 0));

    while(readb_nocache(&v_simu_print->start));

    // while(v_simu_print->start)
    // {
    //     cache_wbinval((intptr_t)(&v_simu_print->start), (intptr_t)(&v_simu_print->start), 1);
    // }

    memcpy(v_simu_print->str, ptr, len);
    if(len < SIMU_PRINT_LEN)
    {
        memset((void *)((intptr_t)(v_simu_print->str) + len), 0, SIMU_PRINT_LEN - len);
    }

    v_simu_print->length = len;
    cache_wb((intptr_t)(v_simu_print), (intptr_t)(v_simu_print), 128);
    writew(0x1, &v_simu_print->start); /* set start to 1, end to 0 */
    /* Flush Cache */
    cache_wbinval((intptr_t)(&v_simu_print->start), (intptr_t)(&v_simu_print->start), 2);
}
#endif
#endif

__attribute__((weak)) void reset_handler(void)
{
    extern int main(void);
    uint64_t v_core_id = read_csr(NDS_MHARTID);

    if(v_core_id == 0)
    {
        /* Enable cache */
        // cache_enable();
#ifndef _FPGA
#if 1
        if(is_dsp_type())
        {
            writel(0x0f000300,0x97001010);//792M----DSP
        }
        else
        {
            writel(0x0f000f00,0x97001000);//792M----CPU
        }
#endif
#endif
        /*
         * Initialize LMA/VMA sections.
         * Relocation for any sections that need to be copied from LMA to VMA.
         */
        c_startup();

        /* Call platform specific hardware initialization */
        core_init();

        /* Plic init */
        // plic_init();
        /* 0x8017FF80 for SIMU printf init */
        /* IOMUX default init */
        // muxpin_default_init();
#ifdef _SIMU
        simu_print_init();
#ifdef _SIM_DDR
        lpddr3_init();
#endif
        /* IOMUX init */
        // muxpin_init();
#else
        /* UART IOMUX */
        // muxpin_set_function(112, FUNC_UART0_SIN);
        // muxpin_set_function(113, FUNC_UART0_SOUT);

        /* Initial UART port */
        // uart_debug_init(UART_DEVICE_0, 115200);
        if(is_dsp_type())
        {
            // k510_logci("DSP freq %lf MHZ\n", sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25P_SRC) / 1000000.0);
        }
        else
        {
            k510_logci("CPU freq %lf MHZ\n", sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25M_SRC) / 1000000.0);
        }
#endif
        /* Do global constructors */
        __libc_init_array();

        core1_instance.callback = NULL;
        core1_instance.ctx = NULL;

        /* Set NMI trap in sysctl */
        /* TODO */
        plic_interrupt_enable();
        /* Entry function */
        main();

        l1cache_flush();
        l1cache_disable();
    }
    else
    {
        /* Enable L1 */
        // l1cache_enable();
        plic_interrupt_enable();
        core_init();
        /* Plic init */
        // plic_init();
        core1_waiting();
        if(core1_instance.callback == NULL)
            core1_waiting();
        else
            core1_instance.callback(core1_instance.ctx);

        l1cache_flush();
        l1cache_disable();
    }
}

int _fstat (int file, struct stat * st) {
    return 0;
}

__attribute__((weak)) int _write (int file, char * ptr, int len) {
    /* Begin protected code */
#ifdef _SIMU
    // corelock_lock(&lock);
    if(len > SIMU_PRINT_LEN)
    {
        while(1)
        {
            simu_print(ptr, SIMU_PRINT_LEN);
            len -= SIMU_PRINT_LEN;
            ptr += SIMU_PRINT_LEN;
            if(len <= SIMU_PRINT_LEN)
            {
                simu_print(ptr, len);
                break;
            }
        }
    }
    else
    {
        simu_print(ptr, len);
    }
    // corelock_unlock(&lock);
#else
    if(!k510_print_flag)
        return 0;
    /* Turn character to capital letter and output to UART port */
    /*for (i = 0; i < len; i++) uart_putc(toupper((int)*ptr++));*/
    for (uint32_t i = 0; i < len; i++)
    {
        uart_outbyte(((int)*ptr++));
    }
#endif
    /* End protected code */
    return len;
}

__attribute__((weak)) int _exit(int status)
{
#if _SIMU
    simu_print_t *v_simu_print;
    v_simu_print = (simu_print_t *)SIMU_PRINT_BASE;

    while(readb_nocache(&v_simu_print->start));

    if(status)
        v_simu_print->start = 0x90;
    else
        v_simu_print->start = 0x80;
    #if _SIMU_CACHE_FLUSH
    cache_flush();
    #else
    cache_wbinval((intptr_t)(&v_simu_print->start), (intptr_t)(&v_simu_print->start), 1);
    #endif
#endif
    cache_flush_disable();
    while(1);
    return 0;
}