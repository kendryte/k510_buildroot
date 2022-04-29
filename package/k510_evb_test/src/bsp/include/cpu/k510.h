#ifndef __K510_H__
#define __K510_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "core_v5.h"
#include "platform.h"
#include "verify_common.h"
#include <stddef.h>
#include "io.h"
#include <stdbool.h>
#include <stdlib.h>
#include "k510_log.h"
#include <sysctl_clk.h>

/*****************************************************************************
 * System clock
 ****************************************************************************/
#define KHz                     1000
#define MHz                     1000000
#ifdef _FPGA
#define BUSFREQ                 (25 * MHz)
#define CPUFREQ                 (50 * MHz)
// #define RTCFREQ                 (32768)
#else
#define BUSFREQ                 (250 * MHz)
#define CPUFREQ                 (is_dsp_type() ? sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25P_SRC) : sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25M_SRC))
// #define RTCFREQ                 (32768)
#endif

// #define HCLKFREQ                (BUSFREQ)
// #define PCLKFREQ                (BUSFREQ)
// #define UCLKFREQ                (BUSFREQ)

#define CAUSE_MISALIGNED_FETCH 		0
#define CAUSE_FAULT_FETCH 			1
#define CAUSE_ILLEGAL_INSTRUCTION 	2
#define CAUSE_BREAKPOINT 			3
#define CAUSE_MISALIGNED_LOAD 		4
#define CAUSE_FAULT_LOAD 			5
#define CAUSE_MISALIGNED_STORE 		6
#define CAUSE_FAULT_STORE 			7
#define CAUSE_USER_ECALL 			8
#define CAUSE_SUPERVISOR_ECALL 		9
#define CAUSE_HYPERVISOR_ECALL 		10
#define CAUSE_MACHINE_ECALL 		11
#define CAUSE_STACK_OVERFLOW 		32
#define CAUSE_STACK_UNDERFLOW 		33

typedef struct {
	__IO unsigned long long MTIME;          /* 0x00 Machine Time */
	__IO unsigned long long MTIMECMP0;      /* 0x08 Machine Time Compare of mhart0 */
	__IO unsigned long long MTIMECMP1;      /* 0x10 Machine Time Compare of mhart1 */
} PLMT_RegDef;

#define DEV_PLMT              ((PLMT_RegDef *) PLIC_MTIMER_BASE_ADDR)

typedef int (*core_function)(void *ctx);

typedef struct _core_instance_t
{
    core_function callback;
    void *ctx;
} core_instance_t;

int register_core1(core_function func, void *ctx);

void k510_print_enable(bool en);
bool k510_get_print_status(void);

#ifdef __cplusplus
}
#endif

#endif	/* __K510_H__ */
