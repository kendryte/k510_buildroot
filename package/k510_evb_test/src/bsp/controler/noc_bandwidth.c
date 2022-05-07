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
#include <math.h>
#include <k510.h>
#include <sysctl_clk.h>
#include <noc_bandwidth.h>


struct probe_mctlpx_stat probe_mctlpx_status[4] = {
	{PROBE_IDLE,0,0,0,0,{0,0,0,0,0,0,0,0}},
	{PROBE_IDLE,0,0,0,0,{0,0,0,0,0,0,0,0}},
	{PROBE_IDLE,0,0,0,0,{0,0,0,0,0,0,0,0}},
	{PROBE_IDLE,0,0,0,0,{0,0,0,0,0,0,0,0}}
};



/**
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */
static inline unsigned int ffs(unsigned int x)
{
	int r = 1;

	if (!x)
		return 0;

	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}

	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}

	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}

	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}

	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}

	return r;
}


/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static inline unsigned int fls(unsigned int x)
{
	int r = 32;

	if (!x)
		return 0;

	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}

	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}

	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}

	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}

	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}

	return r;
}

static inline unsigned int ffz(unsigned int x)
{
	if(x == (~0UL))
		return 0;

	return ffs(~x);
}

uint32_t get_probe_clk_by_initflow(InitFlow_t initflow)
{
	switch (initflow) {
                case AX25MAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25M_SRC);
                case AX25PAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_AX25P_SRC);
                case GNNEAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_GNNE_SYS);
                case AIDATAAXIM:
			return -1;
                case DISPLAYAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_VO_AXI);
                case H264AXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_H264_AXI);
                case ISPAXIM_3DTOF:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_ISP_TOF_AXI);
                case ISPAXIM_F2K:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_ISP_F2K_AXI);
                case ISPAXIM_MFCB:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_MFBC_AXI);
                case ISPAXIM_R2K:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_ISP_R2K_AXI);
                case ISPAXIM_VI:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_VI_AXI);
                case TWODAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_1_TWOD_AXI);
                case STORAHBM_EMACAHBM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_DIV_3_EMAC_AHB);
                case STORAHBM_SDC0AHBM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_0_AHB);
                case STORAHBM_SDC1AHBM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_1_AHB);
                case STORAHBM_SDC2AHBM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_DIV_3_SD_2_AHB);
                case USBAHBM_SD3AHBM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_DIV_2_SD_SLV_AHB);
                case USBAHBM_USBAHBM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_DIV_2_USB_AHB);
                case PDMAAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_PERI_DMA_AXI);
                case SDMAAXIM:
			return sysctl_clk_get_leaf_freq(SYSCTL_CLK_NOC_CLK_0_SYS_DMA_AXI);
                default:
			return -1;

	}
}


/* configure probe_mctlpx_main_probe according to the initflow parameter.
 *
 * Please note: if you configure more than 1 flow in one mctl port, for example:
 * at first you configure DISPLAYAXIM,  and then configure ISPAXIM_R2K, both of the
 * operation will use the probe_mctlp2_main_probe,  the parameters such as
 * startaddr, windowsize and stat_period will be configured two times, and therefor,
 * only the last time you configured for ISPAXIM_R2K will be applied when you enable it.
 *
 * @initflow:           initflow to set, InitFlow_t type, invalid value is not accepted
 * @startaddr:          start address to set for the probe to monitor
 * @windowsize:         windowsize to set for the probe to minotor, with the startaddr
 *                      parameter to specify which address access will be monitored
 * @stat_period:        period to statistics
 *
 * return value:        mctl port index(value from 0 to 3) for success, -1 for failure
 *
 * */
probe_mctlpx_idx_t noc_probe_mctl_cfg(InitFlow_t initflow, unsigned int startaddr, unsigned int windowsize, unsigned int stat_period)
{
	probe_mctlpx_main_probe_t *probe_base;
	mctlpx_filters_t *filter_base;
	mctlpx_counters_t *counter_low;
	mctlpx_counters_t *counter_high;
	TargFlow_t targflow;
	probe_mctlpx_idx_t port_idx;
	unsigned int probe_clk;
	sysctl_clk_node_e leaf;
	unsigned int data;
	unsigned int filter_size = 0;
	unsigned int filter_idx = 0;

	switch (initflow) {
		case AX25MAXIM:
		case AX25PAXIM:
			targflow = MCTLAXI0S;
			port_idx = PROBE_MCTLP0;
			probe_base = PROBE_MCTLP0_ADDR;
			filter_size = 2;
			break;
		case GNNEAXIM:
		case AIDATAAXIM:
			targflow = MCTLAXI1S;
			port_idx = PROBE_MCTLP1;
			probe_base = PROBE_MCTLP1_ADDR;
			filter_size = 2;
			break;
		case DISPLAYAXIM:
		case H264AXIM:
		case ISPAXIM_3DTOF:
		case ISPAXIM_F2K:
		case ISPAXIM_MFCB:
		case ISPAXIM_R2K:
		case ISPAXIM_VI:
		case TWODAXIM:
			targflow = MCTLAXI2S;
			port_idx = PROBE_MCTLP2;
			probe_base = PROBE_MCTLP2_ADDR;
			filter_size = 4;
			break;
		case STORAHBM_EMACAHBM:
		case STORAHBM_SDC0AHBM:
		case STORAHBM_SDC1AHBM:
		case STORAHBM_SDC2AHBM:
		case USBAHBM_SD3AHBM:
		case USBAHBM_USBAHBM:
		case PDMAAXIM:
		case SDMAAXIM:
			targflow = MCTLAXI3S;
			port_idx = PROBE_MCTLP3;
			probe_base = PROBE_MCTLP3_ADDR;
			filter_size = 2;
			break;
		default:
			k510_loge("invalid initflow \n");
			return -1;
	}

	probe_clk = get_probe_clk_by_initflow(initflow);
	if(probe_clk == -1) {
		k510_loge("get probe clock freq failure \n");
		return -1;
	}

        /* get filter_base and counter_base by filter_idx */
        filter_idx = ffz(probe_mctlpx_status[port_idx].filters_inuse)-1;

        if((filter_idx+1) > filter_size){
                k510_logi("invalid fiter %d", filter_idx);
                return -1;
        }

        filter_base = &probe_base->filters_0_3[filter_idx];

        counter_low = &probe_base->counters_0_7[2*filter_idx];
        counter_high = &probe_base->counters_0_7[2*filter_idx+1];


	k510_logi("initflow:%x, targflow:%x, startaddr:%x, windowsize:%x, stat_period:%x, probe_clk:%d \n", initflow, targflow, startaddr, windowsize, stat_period, probe_clk);

	/* if the probe is active, disable it and wait until active bit is clear */
	if(probe_base->CfgCtl & CFGCTL_ACTIVE){
		probe_base->CfgCtl &= ~CFGCTL_GLOBALEN;

		while(probe_base->CfgCtl & CFGCTL_ACTIVE){
			usleep(10);
		}
	}

	/* enable statistics profiling and chained counters */
	data = probe_base->MainCtl;
	data |= MAINCTL_STATEN | MAINCTL_FILTBYTEALWAYSCHAINABLEEN;
	probe_base->MainCtl = data;


	/* set Filters_x_RouteIdBase */
	data = 0;
	data = (initflow << INIT_FLOW_OFFSET) | (targflow << TARG_FLOW_OFFSET);
	filter_base->Filters_x_RouteIdBase = data;

	/* set Filters_x_RouteIdMask */
	filter_base->Filters_x_RouteIdMask = FILTERS_M_ROUTEIDMASK << FILTERS_M_ROUTEIDMASK_OFFSET;

	/* set Filters_x_AddrBase_Low */
	filter_base->Filters_x_AddrBase_Low = startaddr;

	/* set Filters_x_WindowSize  */
	filter_base->Filters_x_WindowSize = windowsize;

	/* set Filters_x_Opcode to 0x3 for rd/wr */
	filter_base->Filters_x_Opcode = FILTERS_X_OPCODE_RDEN | FILTERS_X_OPCODE_WREN;

	/* set Filters_x_Status to 0x1 for request */
	filter_base->Filters_x_Status = FILTERS_X_STATUS_REQEN;

	/* set Filters_x_Length to 0xf for packet number less than 2^15 */
	filter_base->Filters_x_Length = FILTER_M_LENGTH;

	/* set Counters low Src to 0x14 for packet select by filterx */
	counter_low->Counters_x_Src = FILT_BYTE;

	/* set Counters high Src to 0x10 to chain with counter low */
	counter_high->Counters_x_Src = CHAIN;

	/* set StatPeriod to stat_period, 2^stat_period/probe_clk = time in seconds */
	if(stat_period > 0x1F){
		stat_period = 0x1F;
		k510_logi("stat_period exceed max value, set to 0x1F(31)");
	}
	
	probe_base->StatPeriod = stat_period;

	/* set field GlobalEn of register CfgCtl to start counting */
//	probe_base->CfgCtl = CFGCTL_GLOBALEN;

//	probe_mctlpx_status[port_idx].cpu_cycles = read_cycle();
//	probe_mctlpx_status[port_idx].probe_stat = PROBE_INUSE;
	probe_mctlpx_status[port_idx].filters_inuse = 0x1 << filter_idx;
	probe_mctlpx_status[port_idx].stat_period = stat_period;
	probe_mctlpx_status[port_idx].clk_freq = probe_clk;

//	k510_logi("########  probe_mctlp%d enabled: ########\n", port_idx);
	k510_logi("########  probe_mctlp%d configured: ########\n", port_idx);
	k510_logi("probe_mctlpx_status[%d].probe_stat = %d \n", port_idx, probe_mctlpx_status[port_idx].probe_stat);
	k510_logi("probe_mctlpx_status[%d].filters_inuse = 0x%x \n", port_idx, probe_mctlpx_status[port_idx].filters_inuse);
	k510_logi("probe_mctlpx_status[%d].stat_period = %d \n", port_idx, probe_mctlpx_status[port_idx].stat_period);
	k510_logi("probe_mctlpx_status[%d].clk_freq = %d \n", port_idx, probe_mctlpx_status[port_idx].clk_freq);
	k510_logi("probe_mctlpx_status[%d].cpu_cycles = 0x%x \n", port_idx, probe_mctlpx_status[port_idx].cpu_cycles);

	return port_idx;
}


/* enable probe_mctlpx_main_probe to start statistics.
 *
 * @port_idx:        mctl port index, which is return by noc_probe_mctl_cfg.
 *
 * */
void noc_probe_mctlpx_enable(probe_mctlpx_idx_t port_idx)
{
        probe_mctlpx_main_probe_t *probe_base;

        switch (port_idx) {
                case PROBE_MCTLP0:
                        probe_base = PROBE_MCTLP0_ADDR;
                        break;
                case PROBE_MCTLP1:
                        probe_base = PROBE_MCTLP1_ADDR;
                        break;
                case PROBE_MCTLP2:
                        probe_base = PROBE_MCTLP2_ADDR;
                        break;
                case PROBE_MCTLP3:
                        probe_base = PROBE_MCTLP3_ADDR;
                        break;

        }

	/* set field GlobalEn of register CfgCtl to start counting */
	probe_base->CfgCtl = CFGCTL_GLOBALEN;

	probe_mctlpx_status[port_idx].cpu_cycles = read_cycle();
	probe_mctlpx_status[port_idx].probe_stat = PROBE_INUSE;

	k510_logi("########  probe_mctlp%d enabled: ########\n", port_idx);
	k510_logi("probe_mctlpx_status[%d].probe_stat = %d \n", port_idx, probe_mctlpx_status[port_idx].probe_stat);

}

/* disable probe_mctlpx_main_probe to stop statistics.
 *
 * @port_idx:        mctl port index, which is return by noc_probe_mctl_cfg.
 *
 * */
void noc_probe_mctlpx_disable(probe_mctlpx_idx_t port_idx)
{
        probe_mctlpx_main_probe_t *probe_base;

        switch (port_idx) {
                case PROBE_MCTLP0:
                        probe_base = PROBE_MCTLP0_ADDR;
                        break;
                case PROBE_MCTLP1:
                        probe_base = PROBE_MCTLP1_ADDR;
                        break;
                case PROBE_MCTLP2:
                        probe_base = PROBE_MCTLP2_ADDR;
                        break;
                case PROBE_MCTLP3:
                        probe_base = PROBE_MCTLP3_ADDR;
                        break;

        }

	/* clear bit GlobalEn of register CfgCtl to stop counting */
	probe_base->CfgCtl &= ~CFGCTL_GLOBALEN;
	
	probe_mctlpx_status[port_idx].probe_stat = PROBE_IDLE;

	k510_logi("########  probe_mctlp%d disabled: ########\n", port_idx);
        k510_logi("probe_mctlpx_status[%d].probe_stat = %d \n", port_idx, probe_mctlpx_status[port_idx].probe_stat);

}


/* read counters for all mctl ports, if the counter for high 16bits warps, print the counters value and 
 * calculate the bandwidth.
 * can be called in in loop with short sleep, for example usleep(10), for accuracy.
 *
 * */
void noc_probe_mctl_bandwidth()
{
	int i,j;
	int fs = 0, fl = 0;
	unsigned int counter_low_val = 0, counter_high_val = 0;
	probe_mctlpx_main_probe_t *probe_base;
	mctlpx_filters_t *filter_base;
	mctlpx_counters_t *counter_low;
	mctlpx_counters_t *counter_high;
	unsigned int total_bytes = 0;
	double time = 0;


	for(i=0;i<4;i++){
		if(probe_mctlpx_status[i].probe_stat == PROBE_INUSE){
			fs = ffs(probe_mctlpx_status[i].filters_inuse);
			fl = fls(probe_mctlpx_status[i].filters_inuse);
			
			switch(i) {
				case 0:
					probe_base = PROBE_MCTLP0_ADDR;
					break;
				case 1:
					probe_base = PROBE_MCTLP1_ADDR;
					break;
				case 2:
					probe_base = PROBE_MCTLP2_ADDR;
					break;
				case 3:
					probe_base = PROBE_MCTLP3_ADDR;
					break;
			}

			for(j=fs-1;j<fl;j++){
				counter_low_val = probe_base->counters_0_7[2*j].Counters_x_Val;
				counter_high_val = probe_base->counters_0_7[(2*j)+1].Counters_x_Val;

				if(counter_high_val >= probe_mctlpx_status[i].counters[(2*j)+1]){
					probe_mctlpx_status[i].counters[2*j] = counter_low_val;
					probe_mctlpx_status[i].counters[(2*j)+1] = counter_high_val;
				} else {
					k510_logi("probe_mctlp%d_main_probe: ", i);
					k510_logi("counter_%d_value = 0x%x, counter_%d_value = 0x%x \n", 2*j, counter_low_val, (2*j)+1, probe_mctlpx_status[i].counters[(2*j)+1]);
					
					total_bytes = probe_mctlpx_status[i].counters[(2*j)+1] << 16 | counter_low_val;
					k510_logi("total_bytes = 0x%x \n", total_bytes);

					time = pow(2,probe_mctlpx_status[i].stat_period)/probe_mctlpx_status[i].clk_freq;
					k510_logi("time = %f \n", time);

					k510_logi("bandwidth = %f MB\n", (total_bytes/time)/(1024*1024));

					
					probe_mctlpx_status[i].counters[2*j] = 0;
					probe_mctlpx_status[i].counters[(2*j)+1] = 0;
				}
			}
		}
	}
}

/* get counters value according to the port index and the filter index.
 *
 * @port_idx:		mctl port index, which is return by noc_probe_mctl_cfg.
 * @filter_idx: 	filter index, 
 *
 * return value:	return value of total bytes of the filter
 *
 * */
unsigned int noc_probe_get_counter_val(probe_mctlpx_idx_t port_idx, unsigned int filter_idx)
{
	unsigned int total_bytes = 0;
	unsigned int counter_low = 0;
	unsigned int counter_high = 0;

	probe_mctlpx_main_probe_t *probe_base;

	switch (port_idx) {
		case PROBE_MCTLP0:
			probe_base = PROBE_MCTLP0_ADDR;
			break;
		case PROBE_MCTLP1:
			probe_base = PROBE_MCTLP1_ADDR;
			break;
		case PROBE_MCTLP2:
			probe_base = PROBE_MCTLP2_ADDR;
			break;
		case PROBE_MCTLP3:
			probe_base = PROBE_MCTLP3_ADDR;
			break;

	}

	counter_low = probe_base->counters_0_7[2*filter_idx].Counters_x_Val;
	counter_high = probe_base->counters_0_7[2*filter_idx+1].Counters_x_Val;


	total_bytes = counter_high << 16 | counter_low;

	return total_bytes;

}

void noc_bw_isp_vo_gnne()

{

        unsigned int data;

        //sleep(10);

        //unsigned int data;

        //probe_mctlp2_main_Probe offset 0x3000~0x3400

        data = *(volatile unsigned int *)(0x99900000 +0x3000);

        printf("core ID data = 0x%x\n", data);

        

        if(data == 0xDD60C606)

            printf("good probe_mctlp2 coreID\n");

        else

            printf("wrong probe_mctlp2 coreID\n");

            

        data = *(volatile unsigned int *)(0x99900000 +0x3004);

        printf("revision ID data = 0x%x\n", data);

        

        if(data == 0xB085B900)

            printf("good probe_mctlp2 revision ID\n");

        else

            printf("wrong probe_mctlp2 revision ID\n");

    

        //test filters

        data = *(volatile unsigned int *)(0x99900000 +0x3008); //MainCtl

        data |= 1 << 3; //StaEn to 1

        data |=  1 << 7; //FiltByteAlwaysChainableEn to 1

        *(volatile unsigned int *)(0x99900000 +0x3008) = data;

    

        // set Filters_0_RouteIdBase

        data = 0; //seqid : bit 0 ~5 

        data |= 0 << 6; //targ subrange: bit 6

        data |=  0x36 << 7; // target flow: bit 7~12, 0x36 for mctlAXI2s/T/0

        data |= 0xe << 13; // init flow: bit 13~17, 0xe for F2K

    

       

        //set Filters_0_RouteIdBase to 

        *(volatile unsigned int *)(0x99900000 +0x3044) = data;

    

        //set Filters_0_RouteIdMask    

        *(volatile unsigned int *)(0x99900000 +0x3048) = 0xfff <<6;

    

    

        //set Filters_0_AddrBase_Low    

        *(volatile unsigned int *)(0x99900000 +0x304c) = 0;

    

        //set Filters_0_WindowSize to 30 for 1GB range

        *(volatile unsigned int *)(0x99900000 +0x3054) = 30;

    

        //set Filters_0_Opcode to 0x3 for rd/wr

        *(volatile unsigned int *)(0x99900000 +0x3060) = 3;

    

        //set Filters_0_Status to 0x1 for request

        *(volatile unsigned int *)(0x99900000 +0x3064) = 1;

    

        //set Filters_0_Length to 0xf for packet number less than 2^15

        *(volatile unsigned int *)(0x99900000 +0x3068) = 0xf;

    

        //filter1

        // set Filters_1_RouteIdBase

        data = 0; //seqid : bit 0 ~5 

        data |= 0 << 6; //targ subrange: bit 6

        data |=  0x36 << 7; // target flow: bit 7~12, 0x36 for mctlAXI2s/T/0

        data |= 0x9 << 13; // init flow: bit 13~17, 0x9 for vo

    

       

        //set Filters_1_RouteIdBase to 

        *(volatile unsigned int *)(0x99900000 +0x3080) = data;

    

        //set Filters_1_RouteIdMask    

        *(volatile unsigned int *)(0x99900000 +0x3084) = 0xfff <<6;

    

    

        //set Filters_1_AddrBase_Low    

        *(volatile unsigned int *)(0x99900000 +0x3088) = 0;

    

        //set Filters_1_WindowSize to 30 for 1GB range

        *(volatile unsigned int *)(0x99900000 +0x3090) = 30;

    

        //set Filters_1_Opcode to 0x3 for rd/wr

        *(volatile unsigned int *)(0x99900000 +0x309c) = 3;

    

        //set Filters_1_Status to 0x1 for request

        *(volatile unsigned int *)(0x99900000 +0x30a0) = 1;

    

        //set Filters_1_Length to 0xf for packet number less than 2^15

        *(volatile unsigned int *)(0x99900000 +0x30a4) = 0xf;

    

    

        //set Counters_0_Src to 0xC for packet select by filter0

        *(volatile unsigned int *)(0x99900000 +0x3138) = 0x14;

    

        //set Counters_1_Src to 0x10 to chain with counter0

        *(volatile unsigned int *)(0x99900000 +0x314c) = 0x10;

    

        //set Counters_2_Src to 0xd for packet select by filter1

        *(volatile unsigned int *)(0x99900000 +0x3160) = 0x14;

    

        //set Counters_3_Src to 0x10 to chain with counter0

        *(volatile unsigned int *)(0x99900000 +0x3174) = 0x10;

    

        

    

    

        //set StatPeriod to 31, 2^31 = 2,147,483,648 cycles/500000000 = 4.294967296 s

        *(volatile unsigned int *)(0x99900000 +0x3024) = 31;

    

        //set Counters_0_AlarmMode to 2 MAX and Counters_1_AlarmMode to 0 OFF

        //*(volatile unsigned int *)(0x99900000 +0x313c) = 0; //set me to non-zero to enable alarm

        //*(volatile unsigned int *)(0x99900000 +0x3150) = 0;

    

        //set StatAlarmMin to wanted value to trigger int

        //*(volatile unsigned int *)(0x99900000 +0x302c) = 0x06c20000;

    

    

        //set StatAlarmMax to wanted value to trigger int

        //*(volatile unsigned int *)(0x99900000 +0x3030) = 0x06c00000;

    

        //ensure StatAlarmEn is set to 1

        //*(volatile unsigned int *)(0x99900000 +0x303c) = 0x1;

    

        //set AlarmEn of MainCtrl to 1

        //data = *(volatile unsigned int *)(0x99900000 +0x3008); //MainCtl

        //data |= 0x10; //StatAlarmEn to 1

        //data &= ~(0x10);

        //*(volatile unsigned int *)(0x99900000 +0x3008) = data;

    

    

        //set field GlobalEn of register CfgCtl to start counting

        *(volatile unsigned int *)(0x99900000 +0x300c) = 1;

        //statgo

        //*(volatile unsigned int *)(0x99900000 +0x3028) = 1;


/************** probe_mctlp1_main_Probe for gnne bandwidth ***********************/

        //probe_mctlp1_main_Probe offset 0x2000~0x2400

        data = *(volatile unsigned int *)(0x99900000 +0x2000);

        printf("core ID data = 0x%x\n", data);

        

        if(data == 0x59669906)

            printf("good probe_mctlp1 coreID\n");

        else

            printf("wrong probe_mctlp1 coreID\n");

            

        data = *(volatile unsigned int *)(0x99900000 +0x2004);

        printf("revision ID data = 0x%x\n", data);

        

        if(data == 0xB085B900)

            printf("good probe_mctlp1 revision ID\n");

        else

            printf("wrong probe_mctlp1 revision ID\n");



        //test filters

        data = *(volatile unsigned int *)(0x99900000 +0x2008); //MainCtl

        data |= 1 << 3; //StaEn to 1

        data |=  1 << 7; //FiltByteAlwaysChainableEn to 1

        *(volatile unsigned int *)(0x99900000 +0x2008) = data;

    

        // set Filters_0_RouteIdBase

        data = 0; //seqid : bit 0 ~5 

        data |= 0 << 6; //targ subrange: bit 6

        data |=  0x35 << 7; // target flow: bit 7~12, 0x35 for mctlAXI1s/T/0

        data |= 0xa << 13; // init flow: bit 13~17, 0xa for gnneAXIm/I/0

    

       

        //set Filters_0_RouteIdBase to 

        *(volatile unsigned int *)(0x99900000 +0x2044) = data;

    

        //set Filters_0_RouteIdMask    

        *(volatile unsigned int *)(0x99900000 +0x2048) = 0xfff <<6;

    

    

        //set Filters_0_AddrBase_Low    

        *(volatile unsigned int *)(0x99900000 +0x204c) = 0;

    

        //set Filters_0_WindowSize to 30 for 1GB range

        *(volatile unsigned int *)(0x99900000 +0x2054) = 30;

    

        //set Filters_0_Opcode to 0x3 for rd/wr

        *(volatile unsigned int *)(0x99900000 +0x2060) = 3;

    

        //set Filters_0_Status to 0x1 for request

        *(volatile unsigned int *)(0x99900000 +0x2064) = 1;

    

        //set Filters_0_Length to 0xf for packet number less than 2^15

        *(volatile unsigned int *)(0x99900000 +0x2068) = 0xf;

    

        //set Counters_0_Src to 0xC for packet select by filter0

        *(volatile unsigned int *)(0x99900000 +0x2138) = 0xC;

    

        //set Counters_1_Src to 0x10 to chain with counter0

        *(volatile unsigned int *)(0x99900000 +0x214c) = 0x10;

    

        //set StatPeriod to 31, 2^31 = 2,147,483,648 cycles/500000000 = 4.294967296 s

        *(volatile unsigned int *)(0x99900000 +0x2024) = 31;


        //set field GlobalEn of register CfgCtl to start counting
        *(volatile unsigned int *)(0x99900000 +0x200c) = 1;


/************************************/

        int cnt=1;

        

        unsigned int val0,val1,max1=0, max2=0, max3=0;

        while(1)

        {

            usleep(10);


            //read probe_mctlp2_main_Probe counter_0_val and counter_1_val

            val0 = *(volatile unsigned int *)(0x99900000 +0x3140);

            val1 = *(volatile unsigned int *)(0x99900000 +0x3154);

            if(val1 >= max1)

                max1 = val1;

            else

            {

                printf("probe_mctlp2_main_Probe counter_0_val = 0x%x, counter_1_val = 0x%x, max = 0x%x\n", val0, val1, max1);

                max1 = 0;

    

            }


            //read probe_mctlp2_main_Probe counter_2_val and counter_3_val

            val0 = *(volatile unsigned int *)(0x99900000 +0x3168);

            val1 = *(volatile unsigned int *)(0x99900000 +0x317c);

            if(val1 >= max2)

                max2 = val1;

            else

            {

                printf("probe_mctlp2_main_Probe counter_2_val = 0x%x, counter_3_val = 0x%x, max = 0x%x\n", val0, val1, max2);

                max2 = 0;

         

            }

            //read probe_mctlp1_main_Probe counter_0_val and counter_1_val

            val0 = *(volatile unsigned int *)(0x99900000 +0x2140);

            val1 = *(volatile unsigned int *)(0x99900000 +0x2154);

            if(val1 >= max3)

                max3 = val1;

            else

            {

                printf("probe_mctlp1_main_Probe counter_0_val = 0x%x, counter_1_val = 0x%x, max = 0x%x\n", val0, val1, max3);

                max3 = 0;

         

            }


        }

}

