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

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <kendryte_dsp.h>
#include <stdlib.h>
#include <string.h>


#define DSP_BIN_PATH_def "fft.bin"


#ifndef DSP_RESET_VECTOR_def
#define DSP_RESET_VECTOR_def 0x8000000
#endif

#define USAGE "usage:\n" 	  \
	"\t %s firmware address ,for example:\n"  	  \
	"\t %s  fft.bin   0x8000000\r\n"

int main(int argc, char *argv[])
{
	char *pDspBinmPath = DSP_BIN_PATH_def;
	unsigned long DspRestVector = DSP_RESET_VECTOR_def;

	if( (argc > 1) && strstr(argv[1], "-h") ){
		printf(USAGE , argv[0], argv[0] );
		exit(0);
	}
	
	if(argc > 1 ){		
		pDspBinmPath = argv[1];
	}

	if(argc > 2 ){
		DspRestVector = atoll(argv[2]);
	}
	
	printf("firmware path=%s reset vector=0x%lx\n", pDspBinmPath, DspRestVector);
	
    if(kendryte_dsp_load_bin(DspRestVector, pDspBinmPath)) {
        printf("ERR: Load dsp bin file err\n");
        return -1;
    } else {
        printf("Load dsp success\n");
    }

    if(kendryte_dsp_boot(DspRestVector)) {
        printf("ERR: Boot dsp err\n");
        return -1;
    }
}
