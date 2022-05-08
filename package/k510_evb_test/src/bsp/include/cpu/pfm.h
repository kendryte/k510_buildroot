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
/*
 * pfm.h
 *
 *  Created on: Nov 1, 2019
 *      Author: zhaozhongxiang
 */
#ifndef _PFM_H
#define _PFM_H

#include <k510.h>
#include <stdio.h>

extern uint64_t pfm_start;
extern uint64_t pfm_stop;

/* AndesCore_AX25MP_DS156_V1.2 19.4.4 table 95 */

#define	CYCLE_COUNT														0x010
#define	RETIRED_INST													0x020
#define	INTEGER_LOAD_INSTRUCTION_COUNT									0x030
#define	INTEGER_STORE_INSTRUCTION_COUNT									0x040
#define	ATOMIC_INSTRUCTION_COUNT										0x050
#define	SYSTEM_INSTRUCTION_COUNT										0x060
#define	INTEGER_COMPUTATIONAL_INSTRUCTION_COUNT							0x070
#define	CONDITIONAL_BRANCH_INSTRUCTION_COUNT							0x080
#define	TAKEN_CONDITIONAL_BRANCH_INSTRUCTION_COUNT						0x090
#define	JAL_INSTRUCTION_COUNT											0x0A0
#define	JALR_INSTRUCTION_COUNT											0x0B0
#define	RETURN_INSTRUCTION_COUNT										0x0C0
#define	CONTROL_TRANSFER_INSTRUCTION_COUNT								0x0D0
#define	EXEC_IT_INSTRUCTION_COUNT										0x0E0
#define	INTEGER_MULTIPLICATION_INSTRUCTION_COUNT						0x0F0
#define	INTEGER_DIVISION_INSTRUCTION_COUNT								0x100
#define	FLOATING_POINT_LOAD_INSTRUCTION_COUNT							0x110
#define	FLOATING_POINT_STORE_INSTRUCTION_COUNT							0x120
#define	FLOATING_POINT_ADDITION_INSTRUCTION_COUNT						0x130
#define	FLOATING_POINT_MULTIPLICATION_INSTRUCTION_COUNT					0x140
#define	FLOATING_POINT_FUSED_MULTIPLY_ADD_INSTRUCTION_COUNT				0x150
#define	FLOATING_POINT_DIVISION_OR_SQUARE_ROOT_INSTRUCTION_COUNT		0x160
#define	OTHER_FLOATING_POINT_INSTRUCTION_COUNT							0x170
#define	INTEGER_MULTIPLICATION_AND_ADD_SUB_INSTRUCTION_COUNT			0x180
#define	ILM_ACCESS														0x001
#define	DLM_ACCESS														0x011
#define	I_CACHE_ACCESS													0x021
#define	I_CACHE_MISS													0x031
#define	D_CACHE_ACCESS													0x041
#define	D_CACHE_MISS													0x051
#define	D_CACHE_LOAD_ACCESS												0x061
#define	D_CACHE_LOAD_MISS												0x071
#define	D_CACHE_STORE_ACCESS											0x081
#define	D_CACHE_STORE_MISS												0x091
#define	D_CACHE_WRITEBACK												0x0A1
#define	CYCLES_WAITING_FOR_I_CACHE_FILL_DATA							0x0B1
#define	CYCLES_WAITING_FOR_D_CACHE_FILL_DATA							0x0C1
#define	UNCACHED_FETCH_DATA_ACCESS_FROM_BUS								0x0D1
#define	UNCACHED_LOAD_DATA_ACCESS_FROM_BUS								0x0E1
#define	CYCLES_WAITING_FOR_UNCACHED_FETCH_DATA_FROM_BUS					0x0F1
#define	CYCLES_WAITING_FOR_UNCACHED_LOAD_DATA_FROM_BUS					0x101
#define	MAIN_ITLB_ACCESS												0x111
#define	MAIN_ITLB_MISS													0x121
#define	MAIN_DTLB_ACCESS												0x131
#define	MAIN_DTLB_MISS													0x141
#define	CYCLES_WAITING_FOR_MAIN_ITLB_FILL_DATA							0x151
#define	PIPELINE_STALL_CYCLES_CAUSED_BY_MAIN_DTLB_MISS					0x161
#define	MISPREDICTION_OF_CONDITIONAL_BRANCHES							0x002
#define	MISPREDICTION_OF_TAKEN_CONDITIONAL_BRANCHES						0x012
#define	MISPREDICTION_OF_TARGETS_OF_RETURN_INSTRUCTIONS					0x022
#define	REPLAY_FOR_LOAD_AFTER_STORE_OR_STORE_AFTER_STORE_CASES			0x032

#define pfm_set_mhpmevent3(event_slector) write_csr(NDS_MHPMEVENT3, event_slector)
#define pfm_set_mhpmevent4(event_slector) write_csr(NDS_MHPMEVENT4, event_slector)
#define pfm_set_mhpmevent5(event_slector) write_csr(NDS_MHPMEVENT5, event_slector)
#define pfm_set_mhpmevent6(event_slector) write_csr(NDS_MHPMEVENT6, event_slector)

#define pfm_set_mhpmcounter3(val) write_csr(NDS_MHPMCOUNTER3, val)
#define pfm_get_mhpmcounter3()    read_csr(NDS_MHPMCOUNTER3)
#define pfm_set_mhpmcounter4(val) write_csr(NDS_MHPMCOUNTER4, val)
#define pfm_get_mhpmcounter4()    read_csr(NDS_MHPMCOUNTER4)
#define pfm_set_mhpmcounter5(val) write_csr(NDS_MHPMCOUNTER5, val)
#define pfm_get_mhpmcounter5()    read_csr(NDS_MHPMCOUNTER5)
#define pfm_set_mhpmcounter6(val) write_csr(NDS_MHPMCOUNTER6, val)
#define pfm_get_mhpmcounter6()    read_csr(NDS_MHPMCOUNTER6)

#define pfm_set_cycle(val)	write_csr(NDS_MCYCLE, val)
#define pfm_get_cycle()		read_csr(NDS_MCYCLE)

#define pfm_set_instruction_retired(val) write_csr(NDS_MINSTRET, val)
#define pfm_get_instruction_retired()    read_csr(NDS_MINSTRET)

#define pfm_start_cycle()       pfm_start = read_cycle()
#define pfm_stop_cycle()        k510_logi("\nCycle: %ld\n", read_cycle() - pfm_start)
#define pfm_stop_us()           k510_logi("\nUs: %ld\n", (read_cycle() - pfm_start) / (CPUFREQ / 1000000))

#endif

