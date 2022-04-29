#ifndef _k510_RESUME_H
#define _k510_RESUME_H

#define AX25MP0_RESET_VECTOR      (0x97000100UL)
#define AX25MP1_RESET_VECTOR      (0x97000104UL)

/* CPU resume boot addr */
#define RESUME_BASE_ADDR    (0x80060000UL)

/* Core0 sp store addr */
#define RESUME_SP0_ADDR     (RESUME_BASE_ADDR + 0x1000)
/* Core1 sp store addr */
#define RESUME_SP1_ADDR     (RESUME_SP0_ADDR + 0x4)
/* Resume code (cpu_resume) point store addr */
#define RESUME_CODE_ADDR    (RESUME_SP1_ADDR + 0x4)

#endif