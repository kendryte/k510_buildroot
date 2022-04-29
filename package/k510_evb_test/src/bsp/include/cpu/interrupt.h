#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"
/*
 * Define 'NDS_PLIC_BASE' and 'NDS_PLIC_SW_BASE' before include platform
 * intrinsic header file to active PLIC/PLIC_SW related intrinsic functions.
 */
#define NDS_PLIC_BASE        PLIC_BASE_ADDR
#define NDS_PLIC_SW_BASE     PLIC_SW_BASE_ADDR
#include "nds_v5_platform.h"

#define USE_PLIC

/*
 * CPU Machine timer control
 */
#define HAL_MTIMER_INITIAL()
#define HAL_MTIME_ENABLE()                              set_csr(NDS_MIE, MIP_MTIP)
#define HAL_MTIME_DISABLE()                             clear_csr(NDS_MIE, MIP_MTIP);

/*
 * CPU Machine SWI control
 *
 * Machine SWI (MSIP) is connected to PLIC_SW source 1.
 */
#define HAL_MSWI_INITIAL()                              \
{                                                       \
        __nds__plic_sw_set_priority(1, 1);              \
        __nds__plic_sw_enable_interrupt(1);             \
}
#define HAL_MSWI_ENABLE()                               set_csr(NDS_MIE, MIP_MSIP)
#define HAL_MSWI_DISABLE()                              clear_csr(NDS_MIE, MIP_MTIP)
#define HAL_MSWI_PENDING()                              __nds__plic_sw_set_pending(1)
#define HAL_MSWI_CLEAR()                                __nds__plic_sw_claim_interrupt()
#define HAL_IPI_SEND(to)                                __nds__plic_sw_set_pending((to + 1))

/*
 * Platform defined interrupt controller access
 *
 * This uses the vectored PLIC scheme.
 */
#define HAL_MEIP_ENABLE()                               set_csr(NDS_MIE, MIP_MEIP)
#define HAL_MEIP_DISABLE()                              clear_csr(NDS_MIE, MIP_MEIP)
#define HAL_INTERRUPT_ENABLE(vector)                    __nds__plic_enable_interrupt(vector)
#define HAL_INTERRUPT_DISABLE(vector)                   __nds__plic_disable_interrupt(vector)
#define HAL_INTERRUPT_THRESHOLD(threshold)              __nds__plic_set_threshold(threshold)
#define HAL_INTERRUPT_SET_LEVEL(vector, level)          __nds__plic_set_priority(vector, level)

/*
 * Vectored based inline interrupt attach and detach control
 */
extern int __vectors[];
extern void default_irq_entry(void);

#define HAL_INLINE_INTERRUPT_ATTACH(vector, isr)        { __vectors[vector] = (int)isr; }
#define HAL_INLINE_INTERRUPT_DETACH(vector, isr)        { if ( __vectors[vector] == (int)isr ) __vectors[vector] = (int)default_irq_entry; }

/*
 * Inline nested interrupt entry/exit macros
 */
/* Svae/Restore macro */
#define SAVE_CSR(r)                                     long __##r = read_csr(r);
#define RESTORE_CSR(r)                                  write_csr(r, __##r);

#if SUPPORT_PFT_ARCH
#define SAVE_MXSTATUS()                                 SAVE_CSR(NDS_MXSTATUS)
#define RESTORE_MXSTATUS()                              RESTORE_CSR(NDS_MXSTATUS)
#else
#define SAVE_MXSTATUS()
#define RESTORE_MXSTATUS()
#endif

__attribute__((always_inline)) static inline void __canaan__plic_set_threshold (unsigned int threshold)
{
  unsigned int hart_id = __nds__mfsr(NDS_MHARTID);
  volatile unsigned int *threshold_ptr = (volatile unsigned int *)(NDS_PLIC_BASE +
                                                                   PLIC_THRESHOLD_OFFSET +
                                                                   ((hart_id * 2) << PLIC_THRESHOLD_SHIFT_PER_TARGET));
  *threshold_ptr = threshold;
}

__attribute__((always_inline)) static inline void __canaan__plic_enable_interrupt (unsigned int source)
{
  unsigned int hart_id = __nds__mfsr(NDS_MHARTID);
  volatile unsigned int *current_ptr = (volatile unsigned int *)(NDS_PLIC_BASE +
                                                                 PLIC_ENABLE_OFFSET +
                                                                 ((hart_id * 2) << PLIC_ENABLE_SHIFT_PER_TARGET) +
                                                                 ((source >> 5) << 2));
  unsigned int current = *current_ptr;
  current = current | (1 << (source & 0x1F));
  *current_ptr = current;
}

__attribute__((always_inline)) static inline void __canaan__plic_disable_interrupt (unsigned int source)
{
  unsigned int hart_id = __nds__mfsr(NDS_MHARTID);
  volatile unsigned int *current_ptr = (volatile unsigned int *)(NDS_PLIC_BASE +
                                                                 PLIC_ENABLE_OFFSET +
                                                                 ((hart_id * 2) << PLIC_ENABLE_SHIFT_PER_TARGET) +
                                                                 ((source >> 5) << 2));
  unsigned int current = *current_ptr;
  current = current & ~((1 << (source & 0x1F)));
  *current_ptr = current;
}

__attribute__((always_inline)) static inline unsigned int __canaan__plic_claim_interrupt(void)
{
  unsigned int hart_id = __nds__mfsr(NDS_MHARTID);
  volatile unsigned int *claim_addr = (volatile unsigned int *)(NDS_PLIC_BASE +
                                                                PLIC_CLAIM_OFFSET +
                                                                ((hart_id * 2) << PLIC_CLAIM_SHIFT_PER_TARGET));
  return  *claim_addr;
}

__attribute__((always_inline)) static inline void __canaan__plic_complete_interrupt(unsigned int source)
{
  unsigned int hart_id = __nds__mfsr(NDS_MHARTID);
  volatile unsigned int *claim_addr = (volatile unsigned int *)(NDS_PLIC_BASE +
                                                                PLIC_CLAIM_OFFSET +
                                                                ((hart_id * 2) << PLIC_CLAIM_SHIFT_PER_TARGET));
  *claim_addr = source;
}

/* Nested IRQ entry macro : Save CSRs and enable global interrupt. */
#define NESTED_IRQ_ENTER()                              \
        SAVE_CSR(NDS_MEPC)                              \
        SAVE_CSR(NDS_MSTATUS)                           \
        SAVE_MXSTATUS()                                 \
        set_csr(NDS_MSTATUS, MSTATUS_MIE);

/* Nested IRQ exit macro : Restore CSRs */
#define NESTED_IRQ_EXIT()                               \
        clear_csr(NDS_MSTATUS, MSTATUS_MIE);            \
        RESTORE_CSR(NDS_MSTATUS)                        \
        RESTORE_CSR(NDS_MEPC)                           \
        RESTORE_MXSTATUS()

typedef enum _plic_irq
{
    IRQN_UART0_INTERRUPT                        =1, /*!< UART1 interrupt */
    IRQN_UART1_INTERRUPT                        =2, /*!< UART2 interrupt */
    IRQN_UART2_INTERRUPT                        =3, /*!< UART3 interrupt */
    IRQN_UART3_INTERRUPT                        =4, /*!< UART3 interrupt */
    IRQN_I2S2_INTERRUPT                         =5, /*!< I2S2 interrupt */
    IRQN_SPI0_INTERRUPT                         =6, /*!< SPI0 interrupt */
    IRQN_SPI1_INTERRUPT                         =7, /*!< SPI1 interrupt */
    IRQN_SPI2_INTERRUPT                         =8, /*!< SPI2 interrupt */
    IRQN_SPI3_INTERRUPT                         =9, /*!< SPI3 interrupt */
    IRQN_AUDIO_IN_INTERRUPT                     =10,
    IRQN_AUDIO_OUT_INTERRUPT                    =11,
    IRQN_I2C0_INTERRUPT                         =12, /*!< I2C0 interrupt */
    IRQN_I2C1_INTERRUPT                         =13, /*!< I2C1 interrupt */
    IRQN_I2C2_INTERRUPT                         =14, /*!< I2C2 interrupt */
    IRQN_I2C3_INTERRUPT                         =15, /*!< I2C2 interrupt */
    IRQN_I2C4_INTERRUPT                         =16, /*!< I2C2 interrupt */
    IRQN_I2C5_INTERRUPT                         =17, /*!< I2C2 interrupt */
    IRQN_I2C6_INTERRUPT                         =18, /*!< I2C2 interrupt */
    IRQN_GPIO_INTERRUPT                         =19,
    IRQN_SYSCTL_INTERRUPT                       =20,
    IRQN_RTC_TICK_INTERRUPT                     =21,
    IRQN_RTC_ALARM_INTERRUPT                    =22,
    IRQN_PWM0_INTERRUPT                         =23,
    IRQN_PWM1_INTERRUPT                         =24,
    IRQN_PWM2_INTERRUPT                         =25,
    IRQN_PWM3_INTERRUPT                         =26,
    IRQN_VAD_INTERRUPT                          =27,
    IRQN_MAILBOX_TS_INTERRUPT                   =28,
    IRQN_DDRC_INTERRUPT                         =29,
    IRQN_SYS_DMAC_INTERRUPT                     =30,
    IRQN_PERI_DMAC_INTERRUPT                    =31,
    IRQN_NOC_INTERRUPT                          =32,

    IRQN_GNNE_DSP_INTERRUPT                     =38,
    IRQN_GNNE_CPU_INTERRUPT                     =39,
    IRQN_AI_CPU_INTERRUPT                       =40,
    IRQN_TIMER0_INTERRUPT                       =41,
    IRQN_TIMER1_INTERRUPT                       =42,
    IRQN_TIMER2_INTERRUPT                       =43,
    IRQN_TIMER3_INTERRUPT                       =44,
    IRQN_USB_INTERRUPT                          =45,
    IRQN_USB_WAKEUP_INTERRUPT                   =46,
    IRQN_DSIO_SLV_INTERRUPT                     =47,
    IRQN_SD0_INTERRUPT                          =48,
    IRQN_SD1_INTERRUPT                          =49,
    IRQN_SD2_INTERRUPT                          =50,
    IRQN_SD0_WAKEUP_INTERRUPT                   =51,
    IRQN_SD1_WAKEUP_INTERRUPT                   =52,
    IRQN_SD2_WAKEUP_INTERRUPT                   =53,
    IRQN_EMAC_INTERRUPT                         =54,
    IRQN_EMAC_Q1_INTERRUPT                      =55,
    IRQN_EMAC_Q2_INTERRUPT                      =56,
    IRQN_ISP_F4K_INTERRUPT                      =57,
    IRQN_ISP_F2K_INTERRUPT                      =58,
    IRQN_ISP_R2K_INTERRUPT                      =59,
    IRQN_ISP_TOF_INTERRUPT                      =60,
    IRQN_MBFC_INTTERRUPT                        =61,
    IRQN_VI_INTERRUPT                           =62,
    IRQN_H264_INTERRUPT                         =63,
    IRQN_L2CERR_INTERRUPT                       =64,
    IRQN_DSP2CPU_INTERRUPT                      =65,
    IRQN_DSI_INTERRUPT                          =66,
    IRQN_VO_INTERRUPT                           =67,
    IRQN_TWOD_INT_INTERRUPT                     =68,

    IRQN_TIMER4_INTERRUPT                       =92,
    IRQN_TIMER5_INTERRUPT                       =93,
    IRQN_GEMV_INTERRUPT                         =94,
    IRQN_FFT_INTERRUPT                          =95,
    IRQN_CPU2DSP_INTERRUPT                      =96,

    IRQN_MAX                                    = 256,
} plic_irq_t;

/* IRQ number settings */
#define PLIC_NUM_SOURCES    (IRQN_MAX - 1)
/* Real number of cores */
#define PLIC_NUM_CORES      (2)

typedef enum wdt_number
{
    WDT_NUMBER0,
    WDT_NUMBER1,
    WDT_NUMBER2,
    WDT_NUMBER_MAX,
} wdt_number_t;

/**
 * @brief       Definitions for the interrupt callbacks
 */
typedef int (*plic_irq_callback_t)(void *ctx);

/**
 * @brief       Definitions for IRQ table instance
 */
typedef struct _plic_instance_t
{
    plic_irq_callback_t callback;
    void *ctx;
} plic_instance_t;

void plic_irq_register(plic_irq_t irq, plic_irq_callback_t callback, void *ctx);
void plic_irq_unregister(plic_irq_t irq);
int plic_irq_enable(plic_irq_t irq_number);
int plic_irq_disable(plic_irq_t irq_number);
int plic_set_priority(plic_irq_t irq_number, unsigned int priority);
void plic_interrupt_enable(void);
void plic_interrupt_disable(void);
void interrupt_enable(void);
void interrupt_disable(void);
void wdt_irq_register(wdt_number_t wdt_number, plic_irq_callback_t callback, void *ctx);
void wdt_irq_unregister(wdt_number_t wdt_number);
void plic_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __INTERRUPT_H__ */
