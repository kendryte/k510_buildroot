#pragma once

#define		G711_A_LAW	(0)
#define		G711_MU_LAW	(1)

#ifdef __cplusplus
extern "C" {
#endif
	int encode(char *a_psrc, char *a_pdst, int in_data_len, unsigned char type);
	int decode(char *a_psrc, char *a_pdst, int in_data_len, unsigned char type);
#ifdef __cplusplus
}
#endif

