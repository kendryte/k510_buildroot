//any point FFT
#ifndef __FFT_H__
#define __FFT_H__
#include<math.h>

#ifdef FFT_GLOBALS
    #define FFT_EXT
#else
    #define FFT_EXT extern
#endif

#define  PI 3.141592653589793

FFT_EXT float dataR[512];
FFT_EXT float dataI[512];
#endif

