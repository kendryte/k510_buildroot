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
#ifndef SRC_BSP_ATOMIC_H_
#define SRC_BSP_ATOMIC_H_

#include <stdlib.h>
#include "core_v5.h"

#ifdef __riscv_atomic
#define atomic_add(ptr, inc)            __sync_fetch_and_add(ptr, inc)
#define atomic_or(ptr, inc)             __sync_fetch_and_or(ptr, inc)
#define atomic_swap(ptr, swp)           __sync_lock_test_and_set(ptr, swp)
#define atomic_cas(ptr, cmp, swp)       __sync_val_compare_and_swap(ptr, cmp, swp)
#else
#error "RISC-V atomic extension is required. Please add -matomic in CFLAGS."
#endif

#define mb()                             asm volatile ("fence" ::: "memory")
#define atomic_set(ptr, val)            (*(volatile typeof(*(ptr)) *)(ptr) = val)
#define atomic_read(ptr)                (*(volatile typeof(*(ptr)) *)(ptr))

#define DISABLE_IRQSAVE()               read_csr(NDS_MSTATUS) & MSTATUS_MIE;    clear_csr(NDS_MSTATUS, MSTATUS_MIE);
#define ENABLE_IRQRESTORE(flag)         do { if (flag) { set_csr(NDS_MSTATUS, MSTATUS_MIE); } } while(0);
#define SPINLOCK_INIT                   {0}

typedef struct { int lock; } spinlock_t;

static inline int spinlock_trylock(spinlock_t* lock)
{
    int res = atomic_swap(&lock->lock, -1);
    mb();
    return res;
}

static inline void spinlock_lock(spinlock_t* lock)
{
    do
    {
        while (atomic_read(&lock->lock));

    } while (spinlock_trylock(lock));
}

static inline void spinlock_unlock(spinlock_t* lock)
{
    mb();
    atomic_set(&lock->lock,0);
}

static inline long spinlock_lock_irqsave(spinlock_t* lock)
{
    long flag = DISABLE_IRQSAVE();
    spinlock_lock(lock);
    return flag;
}

static inline void spinlock_unlock_irqrestore(spinlock_t* lock, long flag)
{
    spinlock_unlock(lock);
    ENABLE_IRQRESTORE(flag);
}

#define CORELOCK_INIT          \
    {                          \
        .lock = SPINLOCK_INIT, \
        .count = 0,            \
        .core = -1             \
    }

typedef struct _corelock
{
    spinlock_t lock;
    int count;
    int core;
} corelock_t;

static inline int corelock_trylock(corelock_t *lock)
{
    int res = 0;
    unsigned long core;

    asm volatile("csrr %0, mhartid;"
                 : "=r"(core));
    if(spinlock_trylock(&lock->lock))
    {
        return -1;
    }

    if(lock->count == 0)
    {
        /* First time get lock */
        lock->count++;
        lock->core = core;
        res = 0;
    } else if(lock->core == core)
    {
        /* Same core get lock */
        lock->count++;
        res = 0;
    } else
    {
        /* Different core get lock */
        res = -1;
    }
    spinlock_unlock(&lock->lock);

    return res;
}

static inline void corelock_lock(corelock_t *lock)
{
    unsigned long core;

    asm volatile("csrr %0, mhartid;"
                 : "=r"(core));
    spinlock_lock(&lock->lock);

    if(lock->count == 0)
    {
        /* First time get lock */
        lock->count++;
        lock->core = core;
    } else if(lock->core == core)
    {
        /* Same core get lock */
        lock->count++;
    } else
    {
        /* Different core get lock */
        spinlock_unlock(&lock->lock);

        do
        {
            while(atomic_read(&lock->count))
                ;
        } while(corelock_trylock(lock));
        return;
    }
    spinlock_unlock(&lock->lock);
}

static inline void corelock_unlock(corelock_t *lock)
{
    unsigned long core;

    asm volatile("csrr %0, mhartid;"
                 : "=r"(core));
    spinlock_lock(&lock->lock);

    if(lock->core == core)
    {
        /* Same core release lock */
        lock->count--;
        if(lock->count <= 0)
        {
            lock->core = -1;
            lock->count = 0;
        }
    } else
    {
        /* Different core release lock */
        spinlock_unlock(&lock->lock);

        register unsigned long a7 asm("a7") = 93;
        register unsigned long a0 asm("a0") = 0;
        register unsigned long a1 asm("a1") = 0;
        register unsigned long a2 asm("a2") = 0;

        asm volatile("scall"
                     : "+r"(a0)
                     : "r"(a1), "r"(a2), "r"(a7));
    }
    spinlock_unlock(&lock->lock);
}

#endif /* SRC_BSP_ATOMIC_H_ */
