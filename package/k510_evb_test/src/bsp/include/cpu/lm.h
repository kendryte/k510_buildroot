#ifndef _K510_LM_H
#define _K510_LM_H

#include <core_v5.h>

#define lm_ilm_enable()         write_csr(NDS_MILMB, (read_csr(NDS_MILMB) | 0x1UL))

#define lm_ilm_disable()    write_csr(NDS_MILMB, (read_csr(NDS_MILMB) & ~0x1UL))

#define lm_dlm_enable()     write_csr(NDS_MDLMB, (read_csr(NDS_MDLMB) | 0x1UL))

#define lm_dlm_disable()    write_csr(NDS_MDLMB, (read_csr(NDS_MDLMB) & ~0x1UL))

#endif