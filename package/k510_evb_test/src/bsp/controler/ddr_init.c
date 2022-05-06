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
#include <k510.h>
#include "lpddr3.h"

#define REGWR(addr, data) writel(data, addr)
#define REGREAD(addr)     readl(addr)


static uint32_t read_register(uint32_t reg_off, uint32_t is_dfi_reg)
{
    volatile uint32_t *reg_addr;
    if(is_dfi_reg)
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + DDR_PHY_REGS_OFF + reg_off));
    else
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + reg_off*4));
    return *reg_addr;
}
static uint32_t write_register(uint32_t reg_off, uint32_t value, uint32_t is_dfi_reg)
{
    volatile uint32_t *reg_addr;
    if(is_dfi_reg)
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + DDR_PHY_REGS_OFF + reg_off));
    else
        reg_addr = (uint32_t *)((uint64_t)(DDRC_REGS_BASE + reg_off*4));
    reg_addr[0] = value;
    return 0;
}

static uint64_t read_mode_register(uint8_t mod_register, uint64_t *value)
{
    volatile uint32_t regdata = 0;

    /* Clear INT_STATUS_MODE bits in DENALI_CTL_339 by writing 1 to the
       corresponding INT_ACK_MODE bits in DENALI_CTL_346.
       bit[3] Clear MRW completed interrupt.
       bit[2] Clear MRR completed interrupt.
       bit[0] Clear MRR error interrupt.
    */
    regdata |= 1<<3 | 1<<2 | 1;
    write_register(DENALI_CTL_346, regdata, 0);

    /* Verify the INT_STATUS_MODE bits in DENALI_CTL_339 are clear.
       bit[3] MRW completed.
       bit[2] MRR completed.
       bit[0] MRR error occurred.
    */
    regdata = read_register(DENALI_CTL_339, 0);
    if(regdata & 0xd){
        /////mask for currently k510_logd("Unexpected INT_STATUS_MODE bit set in DENALI_CTL_%0d = 0x%x", DENALI_CTL_339, regdata);
        return 1;
    }

    /*  DENALI_CTL_213
    //  [31:25] - RSVD
    //  [24:8]  - READ_MODEREG
    //  [7:0]   - MRW_STATUS
    //
    //  READMODE_REG
    //  [24]   =>field[16]    - Trigger the mode register read.
    //  [23:16]=>field[15:8]  - chip select for which to read the
    //                          command.
    //  [15:8] =>field[7:0]   - mode register number being
    //                          requested (MRz).
    //  MRW_STATUS
    //  [7:5]  =>field[7:5]   - RSVD
    //  [4]    =>field[4]     - For LPDDR4
    //  [3]    =>field[3]     - Self-refresh or deep power-down error.
    //  [2]    =>field[2]     - RSVD
    //  [1]    =>field[1]     - yada-yada
    //  [0]    =>field[0]     - write_modereg parameter
    //                          programming error.
    =========================================================*/
    /* "Initiate the MRR by writing to READMODE_REG bits in DENALI_CTL_213.",
       "bit[24]    - Trigger the mode register read.",
       "bit[23:16] - Chip select for which to read the command.",
       "bit[15:8]  - Mode register number being requested (MRz).");
    */

    regdata = 0x0;
    regdata |= 1<<24 | mod_register << 8;
    write_register(DENALI_CTL_213, regdata, 0);

    /*  DENALI_CTL_339
    /   Check mode register read complete bit is set in
    /  int_status_mode.
    */
    while(1){
        regdata = read_register(DENALI_CTL_339, 0);
        if((regdata & (0x1 << 2)) || (regdata & 0x1)){
            if(!(regdata & 0x1))
                break;
            else {
                /////mask for currently k510_logd("MRR MR%d Mode register read error\n", DENALI_CTL_339);
                return 1;
            }
        }
       // else
            //usleep(1);
    }


    /*  Get the data from the MRR. */
    *value = read_register(DENALI_CTL_214, 0);
    *value |= (((uint64_t)(read_register(DENALI_CTL_215, 0) & 0xff)) << 32);

    return 0;
}

/* Modify 1020 */
static uint32_t Read_Gate_training(void)
{
    uint32_t regdata = 0;
    uint64_t value = 0;

    uint8_t continue_training;
    int    incr_data;
    double    threshpass;
    int    pass0;
    int    pass1;
    int    pass2;
    int    pass3;
    int    detc0;
    int    detc1;
    int    detc2;
    int    detc3;
    int    detc_cntr0;
    int    detc_cntr1;
    int    detc_cntr2;
    int    detc_cntr3;
    int    rg_dly0;
    int    rg_dly1;
    int    rg_dly2;
    int    rg_dly3;
    // real   avg0;
    // real   avg1;
    // real   avg2;
    // real   avg3;

    k510_logi("Begin LPDDR3 Read Gate Training \n");

    /*
        Set SADJ WRT in TRAINING_CTRL1
    */
    //  First read the value of the TRAINING_CTRL1 register.

    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    // set SADJ WRT
    regdata |= (1 << 10);
    //  Now write the new value to the TRAINING_CTRL1 register to
    //  start read gate training.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /*
        Set IO_DS_PU in DSX8_IO_CTRL
    */
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(DSX8_IO_CTRL_ADDR, 1);
    // set IO_DS_PU
    regdata |= (1 << 7);
    //  Now write the new value to the DSX8_IO_CTRL register to
    //  start read gate training.
    write_register(DSX8_IO_CTRL_ADDR,regdata, 1);

    /* Step 0 of 6 for LPDDR3 Read Gate Training
       w/o Bit Deskew or VREF Training
       Set extend read gate bits.
    */
    regdata = read_register(RGDLY_ADJ_ADDR, 1);

     /* Adjust Read gate deassertion. */

    regdata &= ~(0x3 << 28);
    regdata &= ~(0x3 << 20);
    regdata &= ~(0x3 << 12);
    regdata &= ~(0x3 << 4);

    //  Adjust start of Read Gate assertion.
    regdata &= ~(0xf << 24);   // Default = 4'h6. changed to 4'ha JJD
    regdata &= ~(0xf << 16);   // Default = 4'h6.
    regdata &= ~(0xf << 8);    // Default = 4'h6.
    regdata &= ~(0xf << 0);    // Default = 4'h6.

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    //  Loop until Read Gate Training Complete bit (bit 1) in the
    //  TRAINING_CTRL1 register is set or a Read Gate Training
    //  error status bit (bits 927:24]) is set.

// NOTE this threshold for pass needs to be updated to using a windowing average to find the proper point this is a patch to get the testbenches to pass
    #ifdef CHIP_GLS_SSG
        threshpass = 13; //SSG
    #elif CHIP_GLS_FFG
        threshpass = 13; //TT and FFG
    #else
        threshpass = 12; // updata by hyg
    #endif

    incr_data = 0;
    pass0 = 0;
    pass1 = 0;
    pass2 = 0;
    pass3 = 0;
    detc_cntr0 = 0;
    detc_cntr1 = 0;
    detc_cntr2 = 0;
    detc_cntr3 = 0;
    rg_dly0 = 0;
    rg_dly1 = 0;
    rg_dly2 = 0;
    rg_dly3 = 0;

    /* Set RG_DLY = 0 */
    regdata = read_register(RGDLY_ADDR, 1);
    //  Set the value Read Gate assertion
    regdata = 0;

    regdata |= (incr_data & 0xff) << 24;   // Default = 4'h0.
    regdata |= (incr_data & 0xff) << 16;   // Default = 4'h0.
    regdata |= (incr_data & 0xff) << 8;    // Default = 4'h0.
    regdata |= (incr_data & 0xff) << 0;    // Default = 4'h0.
    write_register(RGDLY_ADDR, regdata, 1);

    continue_training = 1;
    while (continue_training == 1)
    {
        /*
            Force RG_DLY value = 1, Put PHY into read gate training mode bit[0] = 1 in TRAINING_CTRL1
        */
        //  First read the value of the TRAINING_CTRL1 register.
        regdata = read_register(TRAINING_CTRL1_ADDR, 1);
        //  Set bit 0 to 1.
        regdata |= (1 << 0);
        //  Set ds_frc_rg = 1.
        regdata |= (1 << 9);
        //  Now write the new value to the TRAINING_CTRL1 register to
        //  start read gate training.
        write_register(TRAINING_CTRL1_ADDR,regdata, 1);

        /*
            "Step 1 of 6 for LPDDR3 Read Gate Training",
            "Issue MRR MR32"
        */
    #ifndef DFI_AGENT
        read_mode_register(32, &value);  /*  */
    #else
    #endif
        /*
            "Step 2 of 6 for LPDDR3 Read Gate Training",
            "After RL + RU(tDQSCKMAX/tCK) + 8.2 + 1 - WL clock ",
            "cycles, DRAM bursts out the predefined Read",
            "Calibration Pattern"
        */
        // #100ns

        /*
            "Step 3 of 6 for LPDDR3 Read Gate Training",
            "Ensure the tMRR >= 8"
        */
        // #100ns

        /*
            "Step 4 of 6 for LPDDR3 Read Gate Training",
            "Continue Gate Training Calibration Loop until",
            "read gate training is signalled complete by.",
            "Monitoring the TRAINING_CTRL1 Register on the AHB",
            "interface to the PHY."
        */

        regdata = read_register(TRAINING_CTRL1_ADDR, 1);

        if(((regdata >> 1) & 1) && (regdata & (0xf << 2)))
        {
            if( (incr_data < 20) )
            {
			    continue_training = 1;
                //  Read the value of the RDQS_DETC_CNTR register.
                #define RDQS_DETC_CNTR_ADDR  0x118
                regdata = read_register(RDQS_DETC_CNTR_ADDR, 1);
                if(((regdata & 0x1F) <= threshpass) && (pass0 != 1))
                {
                    detc_cntr0 = regdata & 0x1F;
                    rg_dly0 = incr_data;
                    pass0 = 1;
                }
                if((((regdata >> 8) & 0x1F) <= threshpass) && pass1 != 1)
                {
			      detc_cntr1 = (regdata >> 8) & 0x1F;
			      rg_dly1 = incr_data;
			      pass1 = 1;
			    }
                if((((regdata >> 16) & 0x1F) <= threshpass) && (pass2 != 1))
                {
			      detc_cntr2 = (regdata >> 16) & 0x1F;
			      rg_dly2 = incr_data;
			      pass2 = 1;
			    }
                if((((regdata >> 24) & 0x1F) <= threshpass) && (pass3 != 1))
                {
			      detc_cntr3 = (regdata >> 24) & 0x1F;
			      rg_dly3 = incr_data;
			      pass3 = 1;
                }
                if((pass0 == 1) && (pass1 == 1) && (pass2 == 1) && (pass3 == 1))
                {
			      continue_training = 0;
                }
                incr_data += 1;
                /* Set RG_DLY = +1 */
                regdata = read_register(RGDLY_ADDR, 1);
                //  Set the value Read Gate assertion

                regdata = 0;
                regdata |= (incr_data & 0xff) << 24;
                regdata |= (incr_data & 0xff) << 16;
                regdata |= (incr_data & 0xff) << 8;
                regdata |= (incr_data & 0xff) << 0;

                write_register(RGDLY_ADDR, regdata, 1);
            }// if ( (incr_data < 20) )
            else
            {
                continue_training = 0;
            }// else: !if( (incr_data < 20) )
        }// if ((regdata[1] == 1'b1) && (regdata[5:2] !== 4'b0000))
        else if(incr_data < 20)
        {
            continue_training = 1;
            incr_data += 1;
            /* Set RG_DLY = +1 */
            /* Wait 100ns for read gate training to finish. CONTINUE LOOP */
            //  #100ns; //??
            regdata = read_register(RGDLY_ADDR, 1);
            //  Set the value Read Gate assertion
            regdata = 0;
            regdata |= (incr_data & 0xff) << 24;
            regdata |= (incr_data & 0xff) << 16;
            regdata |= (incr_data & 0xff) << 8;
            regdata |= (incr_data & 0xff) << 0;
            write_register(RGDLY_ADDR, regdata, 1);
        }
        else if(incr_data == 20)
        {
            continue_training = 0;
            /* Wait 100ns for read gate training to finish.  END LOOP */
            // #100ns;
        }

    }// while (continue_training == 1)

    // setup final read gate training using the trained values
	// REN

    /* Set RG_DLY to final trained values */
    regdata = read_register(RGDLY_ADDR, 1);
    //  Set the value Read Gate assertion
    regdata = 0;
    regdata |= (rg_dly3 & 0xff) << 24;
    regdata |= (rg_dly2 & 0xff) << 16;
    regdata |= (rg_dly1 & 0xff) << 8;
    regdata |= (rg_dly0 & 0xff) << 0;
    write_register(RGDLY_ADDR, regdata, 1);

    /*
        "Perform FINAL READ GATE Training with final trained value ",
        "w/ final detc_cntr assigned to each RGDLY_ADJ assertion"
    */

    regdata = read_register(RGDLY_ADJ_ADDR, 1);
    // Adjust Read gate deassertion.
    regdata &= ~((0x3 << 28) | (0x3 << 20) | (0x3 << 12) | (0x3 << 4));
    regdata |= (0x2 << 28) | (0x2 << 20) | (0x2 << 12) | (0x2 << 4);

    //  Adjust start of Read Gate assertion.
    regdata &= ~((0xf << 24) | (0xf << 16) | (0xf << 8) | (0xf << 0));
    regdata |= ((detc_cntr3 & 0xf) << 24) | ((detc_cntr2 & 0xf) << 16) | ((detc_cntr1 & 0xf) << 8) | ((detc_cntr0 & 0xf) << 0);

    write_register(RGDLY_ADJ_ADDR, regdata, 1);

    /* Force RG_DLY value = 1, Put PHY into read gate training mode bit[0] = 1 in TRAINING_CTRL1 */
    //  First read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
    //  Set bit 0 to 1.
    regdata |= (1 << 0);
    //  Set ds_frc_rg = 1.
    regdata |= (1 << 9);
    //  Now write the new value to the TRAINING_CTRL1 register to
    //  start read gate training.
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /*
        "Step 1 of 6 for LPDDR3 Read Gate Training",
        "Issue MRR MR32"
    */
#ifndef DFI_AGENT
    read_mode_register(32, &value);
#else

#endif

    /*
        "Step 2 of 6 for LPDDR3 Read Gate Training",
        "After RL + RU(tDQSCKMAX/tCK) + 8.2 + 1 - WL clock ",
        "cycles, DRAM bursts out the predefined Read",
        "Calibration Pattern"
    */
    // #100ns

    /*
        "Step 3 of 6 for LPDDR3 Read Gate Training",
        "Ensure the tMRR >= 8"
    */
    // #100ns

    /*
        "Step 4 of 6 for LPDDR3 Read Gate Training",
        "Continue Gate Training Calibration Loop until",
        "read gate training is signalled complete by.",
        "Monitoring the TRAINING_CTRL1 Register on the AHB",
        "interface to the PHY."
    */
    //  Read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);

    //  Verify that all of the Individual Read Gate Training
    //  Completed per Data Slice bits are 1.
    if(((regdata >> 2) & 0xf) != 0xf)
    {
        k510_logd("All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are not 1.\n");
        return -1;
    }
    else
    {
        k510_logd("All Individual Read Gate Training Completed per Data Slice bits (bits 5:2) are correctly set.\n");
    }

    //  Verify that the Read Gate Training error status
    //  bits (bits 27:24) are 0.
    if((regdata >> 24) & 0xF)
    {
        k510_logd("Some of the Read Gate Training error status bits (bit 27:24) are 1.\n");
        return -1;
    }
    else
    {
        k510_logd("None of the Read Gate Training error status bits (bit 27:24) are set. Exiting Read Gate Training and setting read gate auto training mode\n");
    }

    //  Now write the new value to the TRAINING_CTRL1 register to
    //  clear the read gate training request bit and set continuous mode read gate training
    // this should load the rg_dly value as the default start point for auto training
    // set SADJ WRT = 1 and DS_FRC_RG = 0
    regdata &= ~(1 << 0);
    regdata &= ~(1 << 9);
    regdata &= ~(1 << 8);
    regdata |= (1 << 10);

    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    //  Read the value of the TRAINING_CTRL1 register.
    regdata = read_register(TRAINING_CTRL1_ADDR, 1);
  //  regdata |= (1 << 8);
    write_register(TRAINING_CTRL1_ADDR,regdata, 1);

    /*
        "Step 5 of 6 for LPDDR3 Read Gate Training",
        "After end of last MRR read burst, wait until ",
        "tWR + TRPpb is satisfied."
    */
    // #100ns

    /* LPDDR3 Read Gate Complete */

    /*
        "Step 6 of 6 for LPDDR3 Read Gate Training",
        "Continue with regular DRAM commands."
    */

    k510_logi("LPDDR3 Read Gate Complete\n");

    return 0;
}

void lpddr3_init()
{

    uint32_t rdata;
    uint32_t wdata;
    /* PLL3 poweroff */
    writel(0x01000001, PLL3_CTL);
    while(1)
    {
        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 0 PLL3 poweroff */
        if(((rdata >> 4) & 0x3) == 0)
            break;
    }

    /*******sysctl module control **********/
    rdata = readl(PLL3_CFG0);   /* fb div config to be 'd127 */
    rdata &= ~(0xFFFU);
    rdata |= 0x3f;
    rdata |= (1 << 28);
    writel(rdata, PLL3_CFG0);

    rdata = readl(PLL3_CFG1);    /* pll3 bwadj value fb_div/2 */
    rdata &= ~(0xFFF);
    rdata |= 0x20;
    rdata |= (1 << 24);
    writel(rdata, PLL3_CFG1);

    rdata = readl(PLL3_CTL);

    rdata |= (1 << 20);

    rdata |= (1 << 28);

    writel(rdata, PLL3_CTL);



    writel(((1 << 25) | (1 << 4)), PLL3_CTL); /* PLL3 init */



    while(1)

    {

        rdata = readl(PLL3_STAT);   /* PLL3_STAT bit[4:5] == 2 PLL3 ready */

        if(((rdata >> 4) & 0x3) == 0x2)

            break;

    }



    rdata = readl(MEM_CTL_CLK_CFG);

    rdata |= 0x3;   //800Mhz from PLL3

    rdata |= (0x3 << 4); //1/4 division

    rdata |= (0x3 << 16);

    writel(rdata, MEM_CTL_CLK_CFG);



    rdata = readl(MEM_CTL_DFS_CFG);

    rdata |= 0x1;

    rdata |= (1 << 20);

    writel(rdata, MEM_CTL_DFS_CFG);



     //cfg the mctl port clk enable

    rdata = readl(MEM_CTL_CLK_CFG);

    rdata &= ~(0x3F << 8);

    rdata |= (0x3F << 19);

    writel(rdata, MEM_CTL_CLK_CFG);



    // soft-reset and then initialization

    wdata = 0;

    wdata &= ~(0xF);

    wdata &= ~(0xF << 8);

    wdata &= ~(0x3 << 24);

    wdata |= 0x8;

    wdata |= (0x8 << 8);

    wdata |= (0x3 << 24);

    writel(wdata, MCTL_RST_TIM);



    //conduct controller core reset

    writel(1, MCTL_RST_CTL);



    rdata = readl(MEM_CTL_CLK_CFG);

    rdata |= (0x3F << 8);

    rdata |= (0x3F << 19);

    writel(rdata, MEM_CTL_CLK_CFG);



    rdata = readl(MCTL_RST_CTL);

    if(rdata & (1 << 31))

    {

        k510_logi("systctl_rest have been removed\n");

    }

    else

    {

        k510_loge("sysctl_reset not removed");

        return -1;

    }



    // Conduct phy reset

    writel(1, PHY_RST_CTL);



    //clear memory controller reseting done status

    writel(0x80000000, MCTL_RST_CTL);



    //==============================================================================

    //  Config PHY for LPDDR3

    //==============================================================================



    REGWR((0x98008000+PHY_CFG_ADDR), 0x00000000);

    ///  Config PHY for LPDDR3



    //  DLL Master Delay Adjustment for all DLLs f0.

    REGWR((0x98008000+DLL_CTRL1_ADDR), 0x00000048);

    //  DLL Master Delay Adjustment for all DLLs f0.

    REGWR((0x98008000+DLL_CTRL10_ADDR), 0x00000048);



    REGWR((0x98008000+DLL_CTRL2_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL3_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL4_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL5_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL11_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL12_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL13_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj

    REGWR((0x98008000+DLL_CTRL14_ADDR), 0x013001320);

    /// [31:24]  Read DQS DLL slave adj

    /// [23:16]  Write DQS Dll slave delay adj

    /// [15:8]   Read DQS_B DLL slave delay adj

    /// [7:0]    Write DQ DLL slave Dealy adj





    //CFG_WR_WL_RESET

   // REGWR((0x98008000+DLL_CTRL6_ADDR), 0x0F090B10);  //update by hyg @2021.2.8
     REGWR((0x98008000+DLL_CTRL6_ADDR), 0x0);  //update by hyg @2021.2.8
    /// [31:24]  Write Level SADJ 3  F0

    /// [23:16]  Write Level SADJ 2

    /// [15:8]   Write Level SADJ 1

    /// [7:0]    Write Level SADJ 0



    REGWR((0x98008000+DLL_CTRL15_ADDR), 0x00000000);

    /// [31:24]  Write Level SADJ 3  F1

    /// [23:16]  Write Level SADJ 2

    /// [15:8]   Write Level SADJ 1

    /// [7:0]    Write Level SADJ 0



    //CFG_RD_RFE_RESET

    REGWR((0x98008000+DLL_CTRL19_ADDR), 0x18181818);
    // REGWR((0x98008000+DLL_CTRL19_ADDR), 0x08080808);



    /// [31:24]  Read FIFO clk edge delay slice 3

    /// [23:16]  Read FIFO clk edge delay slice 2

    /// [15:8]   Read FIFO clk edge delay slice 2

    /// [7:0]    Read FIFO clk edge delay slice 0



    //CFG_CA_CA_RESET

    // ngb REGWR((0x98008000+DLL_CTRL7_ADDR), 0x00000000);



  //  REGWR((0x98008000+DLL_CTRL7_ADDR), 0x001d1d1d);
    REGWR((0x98008000+DLL_CTRL7_ADDR), 0x001d1d1d);



    REGWR((0x98008000+DLL_CTRL16_ADDR), 0x001d1d1d);



    // CFG_CA_CACK_RESET

   REGWR((0x98008000+DLL_CTRL9_ADDR), 0x00000000);
    //  REGWR((0x98008000+DLL_CTRL9_ADDR), 0x000A0A0A);
    /// [31:24]  Reserved    F0

    /// [23:16]  CA CK SADJ 2

    /// [15:8]   CA CK SADJ 1

    /// [7:0]    CA CK SADJ 0

    REGWR((0x98008000+DLL_CTRL18_ADDR), 0x000a0a0a);

    /// [31:24]  Reserved    F1

    /// [23:16]  CA CK SADJ 2

    /// [15:8]   CA CK SADJ 1

    /// [7:0]    CA CK SADJ 0



    // CFG_CA_CAWL_RESET

    REGWR((0x98008000+DLL_CTRL8_ADDR), 0x000a0a0a);

    /// [31:24]  Reserved    F0

    /// [23:16]  Write Level DLL CA slave delay adj slice 2

    /// [15:8]   Write Level DLL CA slave delay adj slice 1

    /// [7:0]    Write Level DLL CA slave delay adj slice 0

    REGWR((0x98008000+DLL_CTRL17_ADDR), 0x000a0a0a);

    /// [31:24] Reserved    F1

    /// [23:16]  Write Level DLL CA slave delay adj slice 2

    /// [15:8]   Write Level DLL CA slave delay adj slice 1

    /// [7:0]    Write Level DLL CA slave delay adj slice 0



    //CFG LPDDR3 DSX8 & CAX10 SADJ Select to 1/2 MADJ - REN
    // REGWR((0x98008000+DLL_CTRL20_ADDR), 0x55555555);
  //  REGWR((0x98008000+DSX8_IO_CTRL_ADDR), 0x700);
    REGWR((0x98008000+DLL_CTRL22_ADDR), 0x2d2d481d);

    /// [31:24]  CAX10 Write Path SADJ Select

    /// [23:16]  DSX8 Write Path SADJ Select

    /// [15:8]   DQS DQ SADJ LIMIT

    /// [7:0]    WL SADJ LIMIT

    // REGWR((0x98008000 + DSX8_IO_CTRL_ADDR), 0x0403);

    // REGWR((0x98008000 + CAX10_IO_CTRL_ADDR), 0x2);  // 00:34  01:40  02:48  03:60  04:80  05:120  06:240

    //==============================================================================

    //==============================================================================

    REGWR((0x98008000+TRAINING_CTRL1_ADDR), 0x00000300);

    /// training ctrl bit 8 -> 0 bit 9 -> 1  DS_FRC_RG use cfg regs for Read Gate



    /// readgate delay set to 0x14 for NoRandomDelay

    REGWR((0x98008000+RGDLY_ADJ_ADDR), 0x0b0b0b0b);



    //unmask all interrupts

    REGWR((0x98008000+INTERRUPT_MASK_ADDR), 0x00000000);



#ifdef DENALI_CTL_00_DATA

REGWR(DDR_BASE_ADDR+4*0,DENALI_CTL_00_DATA);

#endif

#ifdef DENALI_CTL_01_DATA

REGWR(DDR_BASE_ADDR+4*1,DENALI_CTL_01_DATA);

#endif

#ifdef DENALI_CTL_02_DATA

REGWR(DDR_BASE_ADDR+4*2,DENALI_CTL_02_DATA);

#endif

#ifdef DENALI_CTL_03_DATA

REGWR(DDR_BASE_ADDR+4*3,DENALI_CTL_03_DATA);

#endif

#ifdef DENALI_CTL_04_DATA

REGWR(DDR_BASE_ADDR+4*4,DENALI_CTL_04_DATA);

#endif

#ifdef DENALI_CTL_05_DATA

REGWR(DDR_BASE_ADDR+4*5,DENALI_CTL_05_DATA);

#endif

#ifdef DENALI_CTL_06_DATA

REGWR(DDR_BASE_ADDR+4*6,DENALI_CTL_06_DATA);

#endif

#ifdef DENALI_CTL_07_DATA

REGWR(DDR_BASE_ADDR+4*7,DENALI_CTL_07_DATA);

#endif

#ifdef DENALI_CTL_08_DATA

REGWR(DDR_BASE_ADDR+4*8,DENALI_CTL_08_DATA);

#endif

#ifdef DENALI_CTL_09_DATA

REGWR(DDR_BASE_ADDR+4*9,DENALI_CTL_09_DATA);

#endif

#ifdef DENALI_CTL_10_DATA

REGWR(DDR_BASE_ADDR+4*10,DENALI_CTL_10_DATA);

#endif

#ifdef DENALI_CTL_11_DATA

REGWR(DDR_BASE_ADDR+4*11,DENALI_CTL_11_DATA);

#endif

#ifdef DENALI_CTL_12_DATA

REGWR(DDR_BASE_ADDR+4*12,DENALI_CTL_12_DATA);

#endif

#ifdef DENALI_CTL_13_DATA

REGWR(DDR_BASE_ADDR+4*13,DENALI_CTL_13_DATA);

#endif

#ifdef DENALI_CTL_14_DATA

REGWR(DDR_BASE_ADDR+4*14,DENALI_CTL_14_DATA);

#endif

#ifdef DENALI_CTL_15_DATA

REGWR(DDR_BASE_ADDR+4*15,DENALI_CTL_15_DATA);

#endif

#ifdef DENALI_CTL_16_DATA

REGWR(DDR_BASE_ADDR+4*16,DENALI_CTL_16_DATA);

#endif

#ifdef DENALI_CTL_17_DATA

REGWR(DDR_BASE_ADDR+4*17,DENALI_CTL_17_DATA);

#endif

#ifdef DENALI_CTL_18_DATA

REGWR(DDR_BASE_ADDR+4*18,DENALI_CTL_18_DATA);

#endif

#ifdef DENALI_CTL_19_DATA

REGWR(DDR_BASE_ADDR+4*19,DENALI_CTL_19_DATA);

#endif

#ifdef DENALI_CTL_20_DATA

REGWR(DDR_BASE_ADDR+4*20,DENALI_CTL_20_DATA);

#endif

#ifdef DENALI_CTL_21_DATA

REGWR(DDR_BASE_ADDR+4*21,DENALI_CTL_21_DATA);

#endif

#ifdef DENALI_CTL_22_DATA

REGWR(DDR_BASE_ADDR+4*22,DENALI_CTL_22_DATA);

#endif

#ifdef DENALI_CTL_23_DATA

REGWR(DDR_BASE_ADDR+4*23,DENALI_CTL_23_DATA);

#endif

#ifdef DENALI_CTL_24_DATA

REGWR(DDR_BASE_ADDR+4*24,DENALI_CTL_24_DATA);

#endif

#ifdef DENALI_CTL_25_DATA

REGWR(DDR_BASE_ADDR+4*25,DENALI_CTL_25_DATA);

#endif

#ifdef DENALI_CTL_26_DATA

REGWR(DDR_BASE_ADDR+4*26,DENALI_CTL_26_DATA);

#endif

#ifdef DENALI_CTL_27_DATA

REGWR(DDR_BASE_ADDR+4*27,DENALI_CTL_27_DATA);

#endif

#ifdef DENALI_CTL_28_DATA

REGWR(DDR_BASE_ADDR+4*28,DENALI_CTL_28_DATA);

#endif

#ifdef DENALI_CTL_29_DATA

REGWR(DDR_BASE_ADDR+4*29,DENALI_CTL_29_DATA);

#endif

#ifdef DENALI_CTL_30_DATA

REGWR(DDR_BASE_ADDR+4*30,DENALI_CTL_30_DATA);

#endif

#ifdef DENALI_CTL_31_DATA

REGWR(DDR_BASE_ADDR+4*31,DENALI_CTL_31_DATA);

#endif

#ifdef DENALI_CTL_32_DATA

REGWR(DDR_BASE_ADDR+4*32,DENALI_CTL_32_DATA);

#endif

#ifdef DENALI_CTL_33_DATA

REGWR(DDR_BASE_ADDR+4*33,DENALI_CTL_33_DATA);

#endif

#ifdef DENALI_CTL_34_DATA

REGWR(DDR_BASE_ADDR+4*34,DENALI_CTL_34_DATA);

#endif

#ifdef DENALI_CTL_35_DATA

REGWR(DDR_BASE_ADDR+4*35,DENALI_CTL_35_DATA);

#endif

#ifdef DENALI_CTL_36_DATA

REGWR(DDR_BASE_ADDR+4*36,DENALI_CTL_36_DATA);

#endif

#ifdef DENALI_CTL_37_DATA

REGWR(DDR_BASE_ADDR+4*37,DENALI_CTL_37_DATA);

#endif

#ifdef DENALI_CTL_38_DATA

REGWR(DDR_BASE_ADDR+4*38,DENALI_CTL_38_DATA);

#endif

#ifdef DENALI_CTL_39_DATA

REGWR(DDR_BASE_ADDR+4*39,DENALI_CTL_39_DATA);

#endif

#ifdef DENALI_CTL_40_DATA

REGWR(DDR_BASE_ADDR+4*40,DENALI_CTL_40_DATA);

#endif

#ifdef DENALI_CTL_41_DATA

REGWR(DDR_BASE_ADDR+4*41,DENALI_CTL_41_DATA);

#endif

#ifdef DENALI_CTL_42_DATA

REGWR(DDR_BASE_ADDR+4*42,DENALI_CTL_42_DATA);

#endif

#ifdef DENALI_CTL_43_DATA

REGWR(DDR_BASE_ADDR+4*43,DENALI_CTL_43_DATA);

#endif

#ifdef DENALI_CTL_44_DATA

REGWR(DDR_BASE_ADDR+4*44,DENALI_CTL_44_DATA);

#endif

#ifdef DENALI_CTL_45_DATA

REGWR(DDR_BASE_ADDR+4*45,DENALI_CTL_45_DATA);

#endif

#ifdef DENALI_CTL_46_DATA

REGWR(DDR_BASE_ADDR+4*46,DENALI_CTL_46_DATA);

#endif

#ifdef DENALI_CTL_47_DATA

REGWR(DDR_BASE_ADDR+4*47,DENALI_CTL_47_DATA);

#endif

#ifdef DENALI_CTL_48_DATA

REGWR(DDR_BASE_ADDR+4*48,DENALI_CTL_48_DATA);

#endif

#ifdef DENALI_CTL_49_DATA

REGWR(DDR_BASE_ADDR+4*49,DENALI_CTL_49_DATA);

#endif

#ifdef DENALI_CTL_50_DATA

REGWR(DDR_BASE_ADDR+4*50,DENALI_CTL_50_DATA);

#endif

#ifdef DENALI_CTL_51_DATA

REGWR(DDR_BASE_ADDR+4*51,DENALI_CTL_51_DATA);

#endif

#ifdef DENALI_CTL_52_DATA

REGWR(DDR_BASE_ADDR+4*52,DENALI_CTL_52_DATA);

#endif

#ifdef DENALI_CTL_53_DATA

REGWR(DDR_BASE_ADDR+4*53,DENALI_CTL_53_DATA);

#endif

#ifdef DENALI_CTL_54_DATA

REGWR(DDR_BASE_ADDR+4*54,DENALI_CTL_54_DATA);

#endif

#ifdef DENALI_CTL_55_DATA

REGWR(DDR_BASE_ADDR+4*55,DENALI_CTL_55_DATA);

#endif

#ifdef DENALI_CTL_56_DATA

REGWR(DDR_BASE_ADDR+4*56,DENALI_CTL_56_DATA);

#endif

#ifdef DENALI_CTL_57_DATA

REGWR(DDR_BASE_ADDR+4*57,DENALI_CTL_57_DATA);

#endif

#ifdef DENALI_CTL_58_DATA

REGWR(DDR_BASE_ADDR+4*58,DENALI_CTL_58_DATA);

#endif

#ifdef DENALI_CTL_59_DATA

REGWR(DDR_BASE_ADDR+4*59,DENALI_CTL_59_DATA);

#endif

#ifdef DENALI_CTL_60_DATA

REGWR(DDR_BASE_ADDR+4*60,DENALI_CTL_60_DATA);

#endif

#ifdef DENALI_CTL_61_DATA

REGWR(DDR_BASE_ADDR+4*61,DENALI_CTL_61_DATA);

#endif

#ifdef DENALI_CTL_62_DATA

REGWR(DDR_BASE_ADDR+4*62,DENALI_CTL_62_DATA);

#endif

#ifdef DENALI_CTL_63_DATA

REGWR(DDR_BASE_ADDR+4*63,DENALI_CTL_63_DATA);

#endif

#ifdef DENALI_CTL_64_DATA

REGWR(DDR_BASE_ADDR+4*64,DENALI_CTL_64_DATA);

#endif

#ifdef DENALI_CTL_65_DATA

REGWR(DDR_BASE_ADDR+4*65,DENALI_CTL_65_DATA);

#endif

#ifdef DENALI_CTL_66_DATA

REGWR(DDR_BASE_ADDR+4*66,DENALI_CTL_66_DATA);

#endif

#ifdef DENALI_CTL_67_DATA

REGWR(DDR_BASE_ADDR+4*67,DENALI_CTL_67_DATA);

#endif

#ifdef DENALI_CTL_68_DATA

REGWR(DDR_BASE_ADDR+4*68,DENALI_CTL_68_DATA);

#endif

#ifdef DENALI_CTL_69_DATA

REGWR(DDR_BASE_ADDR+4*69,DENALI_CTL_69_DATA);

#endif

#ifdef DENALI_CTL_70_DATA

REGWR(DDR_BASE_ADDR+4*70,DENALI_CTL_70_DATA);

#endif

#ifdef DENALI_CTL_71_DATA

REGWR(DDR_BASE_ADDR+4*71,DENALI_CTL_71_DATA);

#endif

#ifdef DENALI_CTL_72_DATA

REGWR(DDR_BASE_ADDR+4*72,DENALI_CTL_72_DATA);

#endif

#ifdef DENALI_CTL_73_DATA

REGWR(DDR_BASE_ADDR+4*73,DENALI_CTL_73_DATA);

#endif

#ifdef DENALI_CTL_74_DATA

REGWR(DDR_BASE_ADDR+4*74,DENALI_CTL_74_DATA);

#endif

#ifdef DENALI_CTL_75_DATA

REGWR(DDR_BASE_ADDR+4*75,DENALI_CTL_75_DATA);

#endif

#ifdef DENALI_CTL_76_DATA

REGWR(DDR_BASE_ADDR+4*76,DENALI_CTL_76_DATA);

#endif

#ifdef DENALI_CTL_77_DATA

REGWR(DDR_BASE_ADDR+4*77,DENALI_CTL_77_DATA);

#endif

#ifdef DENALI_CTL_78_DATA

REGWR(DDR_BASE_ADDR+4*78,DENALI_CTL_78_DATA);

#endif

#ifdef DENALI_CTL_79_DATA

REGWR(DDR_BASE_ADDR+4*79,DENALI_CTL_79_DATA);

#endif

#ifdef DENALI_CTL_80_DATA

REGWR(DDR_BASE_ADDR+4*80,DENALI_CTL_80_DATA);

#endif

#ifdef DENALI_CTL_81_DATA

REGWR(DDR_BASE_ADDR+4*81,DENALI_CTL_81_DATA);

#endif

#ifdef DENALI_CTL_82_DATA

REGWR(DDR_BASE_ADDR+4*82,DENALI_CTL_82_DATA);

#endif

#ifdef DENALI_CTL_83_DATA

REGWR(DDR_BASE_ADDR+4*83,DENALI_CTL_83_DATA);

#endif

#ifdef DENALI_CTL_84_DATA

REGWR(DDR_BASE_ADDR+4*84,DENALI_CTL_84_DATA);

#endif

#ifdef DENALI_CTL_85_DATA

REGWR(DDR_BASE_ADDR+4*85,DENALI_CTL_85_DATA);

#endif

#ifdef DENALI_CTL_86_DATA

REGWR(DDR_BASE_ADDR+4*86,DENALI_CTL_86_DATA);

#endif

#ifdef DENALI_CTL_87_DATA

REGWR(DDR_BASE_ADDR+4*87,DENALI_CTL_87_DATA);

#endif

#ifdef DENALI_CTL_88_DATA

REGWR(DDR_BASE_ADDR+4*88,DENALI_CTL_88_DATA);

#endif

#ifdef DENALI_CTL_89_DATA

REGWR(DDR_BASE_ADDR+4*89,DENALI_CTL_89_DATA);

#endif

#ifdef DENALI_CTL_90_DATA

REGWR(DDR_BASE_ADDR+4*90,DENALI_CTL_90_DATA);

#endif

#ifdef DENALI_CTL_91_DATA

REGWR(DDR_BASE_ADDR+4*91,DENALI_CTL_91_DATA);

#endif

#ifdef DENALI_CTL_92_DATA

REGWR(DDR_BASE_ADDR+4*92,DENALI_CTL_92_DATA);

#endif

#ifdef DENALI_CTL_93_DATA

REGWR(DDR_BASE_ADDR+4*93,DENALI_CTL_93_DATA);

#endif

#ifdef DENALI_CTL_94_DATA

REGWR(DDR_BASE_ADDR+4*94,DENALI_CTL_94_DATA);

#endif

#ifdef DENALI_CTL_95_DATA

REGWR(DDR_BASE_ADDR+4*95,DENALI_CTL_95_DATA);

#endif

#ifdef DENALI_CTL_96_DATA

REGWR(DDR_BASE_ADDR+4*96,DENALI_CTL_96_DATA);

#endif

#ifdef DENALI_CTL_97_DATA

REGWR(DDR_BASE_ADDR+4*97,DENALI_CTL_97_DATA);

#endif

#ifdef DENALI_CTL_98_DATA

REGWR(DDR_BASE_ADDR+4*98,DENALI_CTL_98_DATA);

#endif

#ifdef DENALI_CTL_99_DATA

REGWR(DDR_BASE_ADDR+4*99,DENALI_CTL_99_DATA);

#endif

#ifdef DENALI_CTL_100_DATA

REGWR(DDR_BASE_ADDR+4*100,DENALI_CTL_100_DATA);

#endif



REGWR(0x97002198,0); // sysctl PHY reset de-asserted.



#ifdef DENALI_CTL_101_DATA

REGWR(DDR_BASE_ADDR+4*101,DENALI_CTL_101_DATA);

#endif

#ifdef DENALI_CTL_102_DATA

REGWR(DDR_BASE_ADDR+4*102,DENALI_CTL_102_DATA);

#endif

#ifdef DENALI_CTL_103_DATA

REGWR(DDR_BASE_ADDR+4*103,DENALI_CTL_103_DATA);

#endif

#ifdef DENALI_CTL_104_DATA

REGWR(DDR_BASE_ADDR+4*104,DENALI_CTL_104_DATA);

#endif

#ifdef DENALI_CTL_105_DATA

REGWR(DDR_BASE_ADDR+4*105,DENALI_CTL_105_DATA);

#endif

#ifdef DENALI_CTL_106_DATA

REGWR(DDR_BASE_ADDR+4*106,DENALI_CTL_106_DATA);

#endif

#ifdef DENALI_CTL_107_DATA

REGWR(DDR_BASE_ADDR+4*107,DENALI_CTL_107_DATA);

#endif

#ifdef DENALI_CTL_108_DATA

REGWR(DDR_BASE_ADDR+4*108,DENALI_CTL_108_DATA);

#endif

#ifdef DENALI_CTL_109_DATA

REGWR(DDR_BASE_ADDR+4*109,DENALI_CTL_109_DATA);

#endif

#ifdef DENALI_CTL_110_DATA

REGWR(DDR_BASE_ADDR+4*110,DENALI_CTL_110_DATA);

#endif

#ifdef DENALI_CTL_111_DATA

REGWR(DDR_BASE_ADDR+4*111,DENALI_CTL_111_DATA);

#endif

#ifdef DENALI_CTL_112_DATA

REGWR(DDR_BASE_ADDR+4*112,DENALI_CTL_112_DATA);

#endif

#ifdef DENALI_CTL_113_DATA

REGWR(DDR_BASE_ADDR+4*113,DENALI_CTL_113_DATA);

#endif

#ifdef DENALI_CTL_114_DATA

REGWR(DDR_BASE_ADDR+4*114,DENALI_CTL_114_DATA);

#endif

#ifdef DENALI_CTL_115_DATA

REGWR(DDR_BASE_ADDR+4*115,DENALI_CTL_115_DATA);

#endif

#ifdef DENALI_CTL_116_DATA

REGWR(DDR_BASE_ADDR+4*116,DENALI_CTL_116_DATA);

#endif

#ifdef DENALI_CTL_117_DATA

REGWR(DDR_BASE_ADDR+4*117,DENALI_CTL_117_DATA);

#endif

#ifdef DENALI_CTL_118_DATA

REGWR(DDR_BASE_ADDR+4*118,DENALI_CTL_118_DATA);

#endif

#ifdef DENALI_CTL_119_DATA

REGWR(DDR_BASE_ADDR+4*119,DENALI_CTL_119_DATA);

#endif

#ifdef DENALI_CTL_120_DATA

REGWR(DDR_BASE_ADDR+4*120,DENALI_CTL_120_DATA);

#endif

#ifdef DENALI_CTL_121_DATA

REGWR(DDR_BASE_ADDR+4*121,DENALI_CTL_121_DATA);

#endif

#ifdef DENALI_CTL_122_DATA

REGWR(DDR_BASE_ADDR+4*122,DENALI_CTL_122_DATA);

#endif

#ifdef DENALI_CTL_123_DATA

REGWR(DDR_BASE_ADDR+4*123,DENALI_CTL_123_DATA);

#endif

#ifdef DENALI_CTL_124_DATA

REGWR(DDR_BASE_ADDR+4*124,DENALI_CTL_124_DATA);

#endif

#ifdef DENALI_CTL_125_DATA

REGWR(DDR_BASE_ADDR+4*125,DENALI_CTL_125_DATA);

#endif

#ifdef DENALI_CTL_126_DATA

REGWR(DDR_BASE_ADDR+4*126,DENALI_CTL_126_DATA);

#endif

#ifdef DENALI_CTL_127_DATA

REGWR(DDR_BASE_ADDR+4*127,DENALI_CTL_127_DATA);

#endif

#ifdef DENALI_CTL_128_DATA

REGWR(DDR_BASE_ADDR+4*128,DENALI_CTL_128_DATA);

#endif

#ifdef DENALI_CTL_129_DATA

REGWR(DDR_BASE_ADDR+4*129,DENALI_CTL_129_DATA);

#endif

#ifdef DENALI_CTL_130_DATA

REGWR(DDR_BASE_ADDR+4*130,DENALI_CTL_130_DATA);

#endif

#ifdef DENALI_CTL_131_DATA

REGWR(DDR_BASE_ADDR+4*131,DENALI_CTL_131_DATA);

#endif

#ifdef DENALI_CTL_132_DATA

REGWR(DDR_BASE_ADDR+4*132,DENALI_CTL_132_DATA);

#endif

#ifdef DENALI_CTL_133_DATA

REGWR(DDR_BASE_ADDR+4*133,DENALI_CTL_133_DATA);

#endif

#ifdef DENALI_CTL_134_DATA

REGWR(DDR_BASE_ADDR+4*134,DENALI_CTL_134_DATA);

#endif

#ifdef DENALI_CTL_135_DATA

REGWR(DDR_BASE_ADDR+4*135,DENALI_CTL_135_DATA);

#endif

#ifdef DENALI_CTL_136_DATA

REGWR(DDR_BASE_ADDR+4*136,DENALI_CTL_136_DATA);

#endif

#ifdef DENALI_CTL_137_DATA

REGWR(DDR_BASE_ADDR+4*137,DENALI_CTL_137_DATA);

#endif

#ifdef DENALI_CTL_138_DATA

REGWR(DDR_BASE_ADDR+4*138,DENALI_CTL_138_DATA);

#endif

#ifdef DENALI_CTL_139_DATA

REGWR(DDR_BASE_ADDR+4*139,DENALI_CTL_139_DATA);

#endif

#ifdef DENALI_CTL_140_DATA

REGWR(DDR_BASE_ADDR+4*140,DENALI_CTL_140_DATA);

#endif

#ifdef DENALI_CTL_141_DATA

REGWR(DDR_BASE_ADDR+4*141,DENALI_CTL_141_DATA);

#endif

#ifdef DENALI_CTL_142_DATA

REGWR(DDR_BASE_ADDR+4*142,DENALI_CTL_142_DATA);

#endif

#ifdef DENALI_CTL_143_DATA

REGWR(DDR_BASE_ADDR+4*143,DENALI_CTL_143_DATA);

#endif

#ifdef DENALI_CTL_144_DATA

REGWR(DDR_BASE_ADDR+4*144,DENALI_CTL_144_DATA);

#endif

#ifdef DENALI_CTL_145_DATA

REGWR(DDR_BASE_ADDR+4*145,DENALI_CTL_145_DATA);

#endif

#ifdef DENALI_CTL_146_DATA

REGWR(DDR_BASE_ADDR+4*146,DENALI_CTL_146_DATA);

#endif

#ifdef DENALI_CTL_147_DATA

REGWR(DDR_BASE_ADDR+4*147,DENALI_CTL_147_DATA);

#endif

#ifdef DENALI_CTL_148_DATA

REGWR(DDR_BASE_ADDR+4*148,DENALI_CTL_148_DATA);

#endif

#ifdef DENALI_CTL_149_DATA

REGWR(DDR_BASE_ADDR+4*149,DENALI_CTL_149_DATA);

#endif

#ifdef DENALI_CTL_150_DATA

REGWR(DDR_BASE_ADDR+4*150,DENALI_CTL_150_DATA);

#endif

#ifdef DENALI_CTL_151_DATA

REGWR(DDR_BASE_ADDR+4*151,DENALI_CTL_151_DATA);

#endif

#ifdef DENALI_CTL_152_DATA

REGWR(DDR_BASE_ADDR+4*152,DENALI_CTL_152_DATA);

#endif

#ifdef DENALI_CTL_153_DATA

REGWR(DDR_BASE_ADDR+4*153,DENALI_CTL_153_DATA);

#endif

#ifdef DENALI_CTL_154_DATA

REGWR(DDR_BASE_ADDR+4*154,DENALI_CTL_154_DATA);

#endif

#ifdef DENALI_CTL_155_DATA

REGWR(DDR_BASE_ADDR+4*155,DENALI_CTL_155_DATA);

#endif

#ifdef DENALI_CTL_156_DATA

REGWR(DDR_BASE_ADDR+4*156,DENALI_CTL_156_DATA);

#endif

#ifdef DENALI_CTL_157_DATA

REGWR(DDR_BASE_ADDR+4*157,DENALI_CTL_157_DATA);

#endif

#ifdef DENALI_CTL_158_DATA

REGWR(DDR_BASE_ADDR+4*158,DENALI_CTL_158_DATA);

#endif

#ifdef DENALI_CTL_159_DATA

REGWR(DDR_BASE_ADDR+4*159,DENALI_CTL_159_DATA);

#endif

#ifdef DENALI_CTL_160_DATA

REGWR(DDR_BASE_ADDR+4*160,DENALI_CTL_160_DATA);

#endif

#ifdef DENALI_CTL_161_DATA

REGWR(DDR_BASE_ADDR+4*161,DENALI_CTL_161_DATA);

#endif

#ifdef DENALI_CTL_162_DATA

REGWR(DDR_BASE_ADDR+4*162,DENALI_CTL_162_DATA);

#endif

#ifdef DENALI_CTL_163_DATA

REGWR(DDR_BASE_ADDR+4*163,DENALI_CTL_163_DATA);

#endif

#ifdef DENALI_CTL_164_DATA

REGWR(DDR_BASE_ADDR+4*164,DENALI_CTL_164_DATA);

#endif

#ifdef DENALI_CTL_165_DATA

REGWR(DDR_BASE_ADDR+4*165,DENALI_CTL_165_DATA);

#endif

#ifdef DENALI_CTL_166_DATA

REGWR(DDR_BASE_ADDR+4*166,DENALI_CTL_166_DATA);

#endif

#ifdef DENALI_CTL_167_DATA

REGWR(DDR_BASE_ADDR+4*167,DENALI_CTL_167_DATA);

#endif

#ifdef DENALI_CTL_168_DATA

REGWR(DDR_BASE_ADDR+4*168,DENALI_CTL_168_DATA);

#endif

#ifdef DENALI_CTL_169_DATA

REGWR(DDR_BASE_ADDR+4*169,DENALI_CTL_169_DATA);

#endif

#ifdef DENALI_CTL_170_DATA

REGWR(DDR_BASE_ADDR+4*170,DENALI_CTL_170_DATA);

#endif

#ifdef DENALI_CTL_171_DATA

REGWR(DDR_BASE_ADDR+4*171,DENALI_CTL_171_DATA);

#endif

#ifdef DENALI_CTL_172_DATA

REGWR(DDR_BASE_ADDR+4*172,DENALI_CTL_172_DATA);

#endif

#ifdef DENALI_CTL_173_DATA

REGWR(DDR_BASE_ADDR+4*173,DENALI_CTL_173_DATA);

#endif

#ifdef DENALI_CTL_174_DATA

REGWR(DDR_BASE_ADDR+4*174,DENALI_CTL_174_DATA);

#endif

#ifdef DENALI_CTL_175_DATA

REGWR(DDR_BASE_ADDR+4*175,DENALI_CTL_175_DATA);

#endif

#ifdef DENALI_CTL_176_DATA

REGWR(DDR_BASE_ADDR+4*176,DENALI_CTL_176_DATA);

#endif

#ifdef DENALI_CTL_177_DATA

REGWR(DDR_BASE_ADDR+4*177,DENALI_CTL_177_DATA);

#endif

#ifdef DENALI_CTL_178_DATA

REGWR(DDR_BASE_ADDR+4*178,DENALI_CTL_178_DATA);

#endif

#ifdef DENALI_CTL_179_DATA

REGWR(DDR_BASE_ADDR+4*179,DENALI_CTL_179_DATA);

#endif

#ifdef DENALI_CTL_180_DATA

REGWR(DDR_BASE_ADDR+4*180,DENALI_CTL_180_DATA);

#endif

#ifdef DENALI_CTL_181_DATA

REGWR(DDR_BASE_ADDR+4*181,DENALI_CTL_181_DATA);

#endif

#ifdef DENALI_CTL_182_DATA

REGWR(DDR_BASE_ADDR+4*182,DENALI_CTL_182_DATA);

#endif

#ifdef DENALI_CTL_183_DATA

REGWR(DDR_BASE_ADDR+4*183,DENALI_CTL_183_DATA);

#endif

#ifdef DENALI_CTL_184_DATA

REGWR(DDR_BASE_ADDR+4*184,DENALI_CTL_184_DATA);

#endif

#ifdef DENALI_CTL_185_DATA

REGWR(DDR_BASE_ADDR+4*185,DENALI_CTL_185_DATA);

#endif

#ifdef DENALI_CTL_186_DATA

REGWR(DDR_BASE_ADDR+4*186,DENALI_CTL_186_DATA);

#endif

#ifdef DENALI_CTL_187_DATA

REGWR(DDR_BASE_ADDR+4*187,DENALI_CTL_187_DATA);

#endif

#ifdef DENALI_CTL_188_DATA

REGWR(DDR_BASE_ADDR+4*188,DENALI_CTL_188_DATA);

#endif

#ifdef DENALI_CTL_189_DATA

REGWR(DDR_BASE_ADDR+4*189,DENALI_CTL_189_DATA);

#endif

#ifdef DENALI_CTL_190_DATA

REGWR(DDR_BASE_ADDR+4*190,DENALI_CTL_190_DATA);

#endif

#ifdef DENALI_CTL_191_DATA

REGWR(DDR_BASE_ADDR+4*191,DENALI_CTL_191_DATA);

#endif

#ifdef DENALI_CTL_192_DATA

REGWR(DDR_BASE_ADDR+4*192,DENALI_CTL_192_DATA);

#endif

#ifdef DENALI_CTL_193_DATA

REGWR(DDR_BASE_ADDR+4*193,DENALI_CTL_193_DATA);

#endif

#ifdef DENALI_CTL_194_DATA

REGWR(DDR_BASE_ADDR+4*194,DENALI_CTL_194_DATA);

#endif

#ifdef DENALI_CTL_195_DATA

REGWR(DDR_BASE_ADDR+4*195,DENALI_CTL_195_DATA);

#endif

#ifdef DENALI_CTL_196_DATA

REGWR(DDR_BASE_ADDR+4*196,DENALI_CTL_196_DATA);

#endif

#ifdef DENALI_CTL_197_DATA

REGWR(DDR_BASE_ADDR+4*197,DENALI_CTL_197_DATA);

#endif

#ifdef DENALI_CTL_198_DATA

REGWR(DDR_BASE_ADDR+4*198,DENALI_CTL_198_DATA);

#endif

#ifdef DENALI_CTL_199_DATA

REGWR(DDR_BASE_ADDR+4*199,DENALI_CTL_199_DATA);

#endif

#ifdef DENALI_CTL_200_DATA

REGWR(DDR_BASE_ADDR+4*200,DENALI_CTL_200_DATA);

#endif

#ifdef DENALI_CTL_201_DATA

REGWR(DDR_BASE_ADDR+4*201,DENALI_CTL_201_DATA);

#endif

#ifdef DENALI_CTL_202_DATA

REGWR(DDR_BASE_ADDR+4*202,DENALI_CTL_202_DATA);

#endif

#ifdef DENALI_CTL_203_DATA

REGWR(DDR_BASE_ADDR+4*203,DENALI_CTL_203_DATA);

#endif

#ifdef DENALI_CTL_204_DATA

REGWR(DDR_BASE_ADDR+4*204,DENALI_CTL_204_DATA);

#endif

#ifdef DENALI_CTL_205_DATA

REGWR(DDR_BASE_ADDR+4*205,DENALI_CTL_205_DATA);

#endif

#ifdef DENALI_CTL_206_DATA

REGWR(DDR_BASE_ADDR+4*206,DENALI_CTL_206_DATA);

#endif

#ifdef DENALI_CTL_207_DATA

REGWR(DDR_BASE_ADDR+4*207,DENALI_CTL_207_DATA);

#endif

#ifdef DENALI_CTL_208_DATA

REGWR(DDR_BASE_ADDR+4*208,DENALI_CTL_208_DATA);

#endif

#ifdef DENALI_CTL_209_DATA

REGWR(DDR_BASE_ADDR+4*209,DENALI_CTL_209_DATA);

#endif

#ifdef DENALI_CTL_210_DATA

REGWR(DDR_BASE_ADDR+4*210,DENALI_CTL_210_DATA);

#endif

#ifdef DENALI_CTL_211_DATA

REGWR(DDR_BASE_ADDR+4*211,DENALI_CTL_211_DATA);

#endif

#ifdef DENALI_CTL_212_DATA

REGWR(DDR_BASE_ADDR+4*212,DENALI_CTL_212_DATA);

#endif

#ifdef DENALI_CTL_213_DATA

REGWR(DDR_BASE_ADDR+4*213,DENALI_CTL_213_DATA);

#endif

#ifdef DENALI_CTL_214_DATA

REGWR(DDR_BASE_ADDR+4*214,DENALI_CTL_214_DATA);

#endif

#ifdef DENALI_CTL_215_DATA

REGWR(DDR_BASE_ADDR+4*215,DENALI_CTL_215_DATA);

#endif

#ifdef DENALI_CTL_216_DATA

REGWR(DDR_BASE_ADDR+4*216,DENALI_CTL_216_DATA);

#endif

#ifdef DENALI_CTL_217_DATA

REGWR(DDR_BASE_ADDR+4*217,DENALI_CTL_217_DATA);

#endif

#ifdef DENALI_CTL_218_DATA

REGWR(DDR_BASE_ADDR+4*218,DENALI_CTL_218_DATA);

#endif

#ifdef DENALI_CTL_219_DATA

REGWR(DDR_BASE_ADDR+4*219,DENALI_CTL_219_DATA);

#endif

#ifdef DENALI_CTL_220_DATA

REGWR(DDR_BASE_ADDR+4*220,DENALI_CTL_220_DATA);

#endif

#ifdef DENALI_CTL_221_DATA

REGWR(DDR_BASE_ADDR+4*221,DENALI_CTL_221_DATA);

#endif

#ifdef DENALI_CTL_222_DATA

REGWR(DDR_BASE_ADDR+4*222,DENALI_CTL_222_DATA);

#endif

#ifdef DENALI_CTL_223_DATA

REGWR(DDR_BASE_ADDR+4*223,DENALI_CTL_223_DATA);

#endif

#ifdef DENALI_CTL_224_DATA

REGWR(DDR_BASE_ADDR+4*224,DENALI_CTL_224_DATA);

#endif

#ifdef DENALI_CTL_225_DATA

REGWR(DDR_BASE_ADDR+4*225,DENALI_CTL_225_DATA);

#endif

#ifdef DENALI_CTL_226_DATA

REGWR(DDR_BASE_ADDR+4*226,DENALI_CTL_226_DATA);

#endif

#ifdef DENALI_CTL_227_DATA

REGWR(DDR_BASE_ADDR+4*227,DENALI_CTL_227_DATA);

#endif

#ifdef DENALI_CTL_228_DATA

REGWR(DDR_BASE_ADDR+4*228,DENALI_CTL_228_DATA);

#endif

#ifdef DENALI_CTL_229_DATA

REGWR(DDR_BASE_ADDR+4*229,DENALI_CTL_229_DATA);

#endif

#ifdef DENALI_CTL_230_DATA

REGWR(DDR_BASE_ADDR+4*230,DENALI_CTL_230_DATA);

#endif

#ifdef DENALI_CTL_231_DATA

REGWR(DDR_BASE_ADDR+4*231,DENALI_CTL_231_DATA);

#endif

#ifdef DENALI_CTL_232_DATA

REGWR(DDR_BASE_ADDR+4*232,DENALI_CTL_232_DATA);

#endif

#ifdef DENALI_CTL_233_DATA

REGWR(DDR_BASE_ADDR+4*233,DENALI_CTL_233_DATA);

#endif

#ifdef DENALI_CTL_234_DATA

REGWR(DDR_BASE_ADDR+4*234,DENALI_CTL_234_DATA);

#endif

#ifdef DENALI_CTL_235_DATA

REGWR(DDR_BASE_ADDR+4*235,DENALI_CTL_235_DATA);

#endif

#ifdef DENALI_CTL_236_DATA

REGWR(DDR_BASE_ADDR+4*236,DENALI_CTL_236_DATA);

#endif

#ifdef DENALI_CTL_237_DATA

REGWR(DDR_BASE_ADDR+4*237,DENALI_CTL_237_DATA);

#endif

#ifdef DENALI_CTL_238_DATA

REGWR(DDR_BASE_ADDR+4*238,DENALI_CTL_238_DATA);

#endif

#ifdef DENALI_CTL_239_DATA

REGWR(DDR_BASE_ADDR+4*239,DENALI_CTL_239_DATA);

#endif

#ifdef DENALI_CTL_240_DATA

REGWR(DDR_BASE_ADDR+4*240,DENALI_CTL_240_DATA);

#endif

#ifdef DENALI_CTL_241_DATA

REGWR(DDR_BASE_ADDR+4*241,DENALI_CTL_241_DATA);

#endif

#ifdef DENALI_CTL_242_DATA

REGWR(DDR_BASE_ADDR+4*242,DENALI_CTL_242_DATA);

#endif

#ifdef DENALI_CTL_243_DATA

REGWR(DDR_BASE_ADDR+4*243,DENALI_CTL_243_DATA);

#endif

#ifdef DENALI_CTL_244_DATA

REGWR(DDR_BASE_ADDR+4*244,DENALI_CTL_244_DATA);

#endif

#ifdef DENALI_CTL_245_DATA

REGWR(DDR_BASE_ADDR+4*245,DENALI_CTL_245_DATA);

#endif

#ifdef DENALI_CTL_246_DATA

REGWR(DDR_BASE_ADDR+4*246,DENALI_CTL_246_DATA);

#endif

#ifdef DENALI_CTL_247_DATA

REGWR(DDR_BASE_ADDR+4*247,DENALI_CTL_247_DATA);

#endif

#ifdef DENALI_CTL_248_DATA

REGWR(DDR_BASE_ADDR+4*248,DENALI_CTL_248_DATA);

#endif

#ifdef DENALI_CTL_249_DATA

REGWR(DDR_BASE_ADDR+4*249,DENALI_CTL_249_DATA);

#endif

#ifdef DENALI_CTL_250_DATA

REGWR(DDR_BASE_ADDR+4*250,DENALI_CTL_250_DATA);

#endif

#ifdef DENALI_CTL_251_DATA

REGWR(DDR_BASE_ADDR+4*251,DENALI_CTL_251_DATA);

#endif

#ifdef DENALI_CTL_252_DATA

REGWR(DDR_BASE_ADDR+4*252,DENALI_CTL_252_DATA);

#endif

#ifdef DENALI_CTL_253_DATA

REGWR(DDR_BASE_ADDR+4*253,DENALI_CTL_253_DATA);

#endif

#ifdef DENALI_CTL_254_DATA

REGWR(DDR_BASE_ADDR+4*254,DENALI_CTL_254_DATA);

#endif

#ifdef DENALI_CTL_255_DATA

REGWR(DDR_BASE_ADDR+4*255,DENALI_CTL_255_DATA);

#endif

#ifdef DENALI_CTL_256_DATA

REGWR(DDR_BASE_ADDR+4*256,DENALI_CTL_256_DATA);

#endif

#ifdef DENALI_CTL_257_DATA

REGWR(DDR_BASE_ADDR+4*257,DENALI_CTL_257_DATA);

#endif

#ifdef DENALI_CTL_258_DATA

REGWR(DDR_BASE_ADDR+4*258,DENALI_CTL_258_DATA);

#endif

#ifdef DENALI_CTL_259_DATA

REGWR(DDR_BASE_ADDR+4*259,DENALI_CTL_259_DATA);

#endif

#ifdef DENALI_CTL_260_DATA

REGWR(DDR_BASE_ADDR+4*260,DENALI_CTL_260_DATA);

#endif

#ifdef DENALI_CTL_261_DATA

REGWR(DDR_BASE_ADDR+4*261,DENALI_CTL_261_DATA);

#endif

#ifdef DENALI_CTL_262_DATA

REGWR(DDR_BASE_ADDR+4*262,DENALI_CTL_262_DATA);

#endif

#ifdef DENALI_CTL_263_DATA

REGWR(DDR_BASE_ADDR+4*263,DENALI_CTL_263_DATA);

#endif

#ifdef DENALI_CTL_264_DATA

REGWR(DDR_BASE_ADDR+4*264,DENALI_CTL_264_DATA);

#endif

#ifdef DENALI_CTL_265_DATA

REGWR(DDR_BASE_ADDR+4*265,DENALI_CTL_265_DATA);

#endif

#ifdef DENALI_CTL_266_DATA

REGWR(DDR_BASE_ADDR+4*266,DENALI_CTL_266_DATA);

#endif

#ifdef DENALI_CTL_267_DATA

REGWR(DDR_BASE_ADDR+4*267,DENALI_CTL_267_DATA);

#endif

#ifdef DENALI_CTL_268_DATA

REGWR(DDR_BASE_ADDR+4*268,DENALI_CTL_268_DATA);

#endif

#ifdef DENALI_CTL_269_DATA

REGWR(DDR_BASE_ADDR+4*269,DENALI_CTL_269_DATA);

#endif

#ifdef DENALI_CTL_270_DATA

REGWR(DDR_BASE_ADDR+4*270,DENALI_CTL_270_DATA);

#endif

#ifdef DENALI_CTL_271_DATA

REGWR(DDR_BASE_ADDR+4*271,DENALI_CTL_271_DATA);

#endif

#ifdef DENALI_CTL_272_DATA

REGWR(DDR_BASE_ADDR+4*272,DENALI_CTL_272_DATA);

#endif

#ifdef DENALI_CTL_273_DATA

REGWR(DDR_BASE_ADDR+4*273,DENALI_CTL_273_DATA);

#endif

#ifdef DENALI_CTL_274_DATA

REGWR(DDR_BASE_ADDR+4*274,DENALI_CTL_274_DATA);

#endif

#ifdef DENALI_CTL_275_DATA

REGWR(DDR_BASE_ADDR+4*275,DENALI_CTL_275_DATA);

#endif

#ifdef DENALI_CTL_276_DATA

REGWR(DDR_BASE_ADDR+4*276,DENALI_CTL_276_DATA);

#endif

#ifdef DENALI_CTL_277_DATA

REGWR(DDR_BASE_ADDR+4*277,DENALI_CTL_277_DATA);

#endif

#ifdef DENALI_CTL_278_DATA

REGWR(DDR_BASE_ADDR+4*278,DENALI_CTL_278_DATA);

#endif

#ifdef DENALI_CTL_279_DATA

REGWR(DDR_BASE_ADDR+4*279,DENALI_CTL_279_DATA);

#endif

#ifdef DENALI_CTL_280_DATA

REGWR(DDR_BASE_ADDR+4*280,DENALI_CTL_280_DATA);

#endif

#ifdef DENALI_CTL_281_DATA

REGWR(DDR_BASE_ADDR+4*281,DENALI_CTL_281_DATA);

#endif

#ifdef DENALI_CTL_282_DATA

REGWR(DDR_BASE_ADDR+4*282,DENALI_CTL_282_DATA);

#endif

#ifdef DENALI_CTL_283_DATA

REGWR(DDR_BASE_ADDR+4*283,DENALI_CTL_283_DATA);

#endif

#ifdef DENALI_CTL_284_DATA

REGWR(DDR_BASE_ADDR+4*284,DENALI_CTL_284_DATA);

#endif

#ifdef DENALI_CTL_285_DATA

REGWR(DDR_BASE_ADDR+4*285,DENALI_CTL_285_DATA);

#endif

#ifdef DENALI_CTL_286_DATA

REGWR(DDR_BASE_ADDR+4*286,DENALI_CTL_286_DATA);

#endif

#ifdef DENALI_CTL_287_DATA

REGWR(DDR_BASE_ADDR+4*287,DENALI_CTL_287_DATA);

#endif

#ifdef DENALI_CTL_288_DATA

REGWR(DDR_BASE_ADDR+4*288,DENALI_CTL_288_DATA);

#endif

#ifdef DENALI_CTL_289_DATA

REGWR(DDR_BASE_ADDR+4*289,DENALI_CTL_289_DATA);

#endif

#ifdef DENALI_CTL_290_DATA

REGWR(DDR_BASE_ADDR+4*290,DENALI_CTL_290_DATA);

#endif

#ifdef DENALI_CTL_291_DATA

REGWR(DDR_BASE_ADDR+4*291,DENALI_CTL_291_DATA);

#endif

#ifdef DENALI_CTL_292_DATA

REGWR(DDR_BASE_ADDR+4*292,DENALI_CTL_292_DATA);

#endif

#ifdef DENALI_CTL_293_DATA

REGWR(DDR_BASE_ADDR+4*293,DENALI_CTL_293_DATA);

#endif

#ifdef DENALI_CTL_294_DATA

REGWR(DDR_BASE_ADDR+4*294,DENALI_CTL_294_DATA);

#endif

#ifdef DENALI_CTL_295_DATA

REGWR(DDR_BASE_ADDR+4*295,DENALI_CTL_295_DATA);

#endif

#ifdef DENALI_CTL_296_DATA

REGWR(DDR_BASE_ADDR+4*296,DENALI_CTL_296_DATA);

#endif

#ifdef DENALI_CTL_297_DATA

REGWR(DDR_BASE_ADDR+4*297,DENALI_CTL_297_DATA);

#endif

#ifdef DENALI_CTL_298_DATA

REGWR(DDR_BASE_ADDR+4*298,DENALI_CTL_298_DATA);

#endif

#ifdef DENALI_CTL_299_DATA

REGWR(DDR_BASE_ADDR+4*299,DENALI_CTL_299_DATA);

#endif

#ifdef DENALI_CTL_300_DATA

REGWR(DDR_BASE_ADDR+4*300,DENALI_CTL_300_DATA);

#endif

#ifdef DENALI_CTL_301_DATA

REGWR(DDR_BASE_ADDR+4*301,DENALI_CTL_301_DATA);

#endif

#ifdef DENALI_CTL_302_DATA

REGWR(DDR_BASE_ADDR+4*302,DENALI_CTL_302_DATA);

#endif

#ifdef DENALI_CTL_303_DATA

REGWR(DDR_BASE_ADDR+4*303,DENALI_CTL_303_DATA);

#endif

#ifdef DENALI_CTL_304_DATA

REGWR(DDR_BASE_ADDR+4*304,DENALI_CTL_304_DATA);

#endif

#ifdef DENALI_CTL_305_DATA

REGWR(DDR_BASE_ADDR+4*305,DENALI_CTL_305_DATA);

#endif

#ifdef DENALI_CTL_306_DATA

REGWR(DDR_BASE_ADDR+4*306,DENALI_CTL_306_DATA);

#endif

#ifdef DENALI_CTL_307_DATA

REGWR(DDR_BASE_ADDR+4*307,DENALI_CTL_307_DATA);

#endif

#ifdef DENALI_CTL_308_DATA

REGWR(DDR_BASE_ADDR+4*308,DENALI_CTL_308_DATA);

#endif

#ifdef DENALI_CTL_309_DATA

REGWR(DDR_BASE_ADDR+4*309,DENALI_CTL_309_DATA);

#endif

#ifdef DENALI_CTL_310_DATA

REGWR(DDR_BASE_ADDR+4*310,DENALI_CTL_310_DATA);

#endif

#ifdef DENALI_CTL_311_DATA

REGWR(DDR_BASE_ADDR+4*311,DENALI_CTL_311_DATA);

#endif

#ifdef DENALI_CTL_312_DATA

REGWR(DDR_BASE_ADDR+4*312,DENALI_CTL_312_DATA);

#endif

#ifdef DENALI_CTL_313_DATA

REGWR(DDR_BASE_ADDR+4*313,DENALI_CTL_313_DATA);

#endif

#ifdef DENALI_CTL_314_DATA

REGWR(DDR_BASE_ADDR+4*314,DENALI_CTL_314_DATA);

#endif

#ifdef DENALI_CTL_315_DATA

REGWR(DDR_BASE_ADDR+4*315,DENALI_CTL_315_DATA);

#endif

#ifdef DENALI_CTL_316_DATA

REGWR(DDR_BASE_ADDR+4*316,DENALI_CTL_316_DATA);

#endif

#ifdef DENALI_CTL_317_DATA

REGWR(DDR_BASE_ADDR+4*317,DENALI_CTL_317_DATA);

#endif

#ifdef DENALI_CTL_318_DATA

REGWR(DDR_BASE_ADDR+4*318,DENALI_CTL_318_DATA);

#endif

#ifdef DENALI_CTL_319_DATA

REGWR(DDR_BASE_ADDR+4*319,DENALI_CTL_319_DATA);

#endif

#ifdef DENALI_CTL_320_DATA

REGWR(DDR_BASE_ADDR+4*320,DENALI_CTL_320_DATA);

#endif

#ifdef DENALI_CTL_321_DATA

REGWR(DDR_BASE_ADDR+4*321,DENALI_CTL_321_DATA);

#endif

#ifdef DENALI_CTL_322_DATA

REGWR(DDR_BASE_ADDR+4*322,DENALI_CTL_322_DATA);

#endif

#ifdef DENALI_CTL_323_DATA

REGWR(DDR_BASE_ADDR+4*323,DENALI_CTL_323_DATA);

#endif

#ifdef DENALI_CTL_324_DATA

REGWR(DDR_BASE_ADDR+4*324,DENALI_CTL_324_DATA);

#endif

#ifdef DENALI_CTL_325_DATA

REGWR(DDR_BASE_ADDR+4*325,DENALI_CTL_325_DATA);

#endif

#ifdef DENALI_CTL_326_DATA

REGWR(DDR_BASE_ADDR+4*326,DENALI_CTL_326_DATA);

#endif

#ifdef DENALI_CTL_327_DATA

REGWR(DDR_BASE_ADDR+4*327,DENALI_CTL_327_DATA);

#endif

#ifdef DENALI_CTL_328_DATA

REGWR(DDR_BASE_ADDR+4*328,DENALI_CTL_328_DATA);

#endif

#ifdef DENALI_CTL_329_DATA

REGWR(DDR_BASE_ADDR+4*329,DENALI_CTL_329_DATA);

#endif

#ifdef DENALI_CTL_330_DATA

REGWR(DDR_BASE_ADDR+4*330,DENALI_CTL_330_DATA);

#endif

#ifdef DENALI_CTL_331_DATA

REGWR(DDR_BASE_ADDR+4*331,DENALI_CTL_331_DATA);

#endif

#ifdef DENALI_CTL_332_DATA

REGWR(DDR_BASE_ADDR+4*332,DENALI_CTL_332_DATA);

#endif

#ifdef DENALI_CTL_333_DATA

REGWR(DDR_BASE_ADDR+4*333,DENALI_CTL_333_DATA);

#endif

#ifdef DENALI_CTL_334_DATA

REGWR(DDR_BASE_ADDR+4*334,DENALI_CTL_334_DATA);

#endif

#ifdef DENALI_CTL_335_DATA

REGWR(DDR_BASE_ADDR+4*335,DENALI_CTL_335_DATA);

#endif

#ifdef DENALI_CTL_336_DATA

REGWR(DDR_BASE_ADDR+4*336,DENALI_CTL_336_DATA);

#endif

#ifdef DENALI_CTL_337_DATA

REGWR(DDR_BASE_ADDR+4*337,DENALI_CTL_337_DATA);

#endif

#ifdef DENALI_CTL_338_DATA

REGWR(DDR_BASE_ADDR+4*338,DENALI_CTL_338_DATA);

#endif

#ifdef DENALI_CTL_339_DATA

REGWR(DDR_BASE_ADDR+4*339,DENALI_CTL_339_DATA);

#endif

#ifdef DENALI_CTL_340_DATA

REGWR(DDR_BASE_ADDR+4*340,DENALI_CTL_340_DATA);

#endif

#ifdef DENALI_CTL_341_DATA

REGWR(DDR_BASE_ADDR+4*341,DENALI_CTL_341_DATA);

#endif

#ifdef DENALI_CTL_342_DATA

REGWR(DDR_BASE_ADDR+4*342,DENALI_CTL_342_DATA);

#endif

#ifdef DENALI_CTL_343_DATA

REGWR(DDR_BASE_ADDR+4*343,DENALI_CTL_343_DATA);

#endif

#ifdef DENALI_CTL_344_DATA

REGWR(DDR_BASE_ADDR+4*344,DENALI_CTL_344_DATA);

#endif

#ifdef DENALI_CTL_345_DATA

REGWR(DDR_BASE_ADDR+4*345,DENALI_CTL_345_DATA);

#endif

#ifdef DENALI_CTL_346_DATA

REGWR(DDR_BASE_ADDR+4*346,DENALI_CTL_346_DATA);

#endif

#ifdef DENALI_CTL_347_DATA

REGWR(DDR_BASE_ADDR+4*347,DENALI_CTL_347_DATA);

#endif

#ifdef DENALI_CTL_348_DATA

REGWR(DDR_BASE_ADDR+4*348,DENALI_CTL_348_DATA);

#endif

#ifdef DENALI_CTL_349_DATA

REGWR(DDR_BASE_ADDR+4*349,DENALI_CTL_349_DATA);

#endif

#ifdef DENALI_CTL_350_DATA

REGWR(DDR_BASE_ADDR+4*350,DENALI_CTL_350_DATA);

#endif

#ifdef DENALI_CTL_351_DATA

REGWR(DDR_BASE_ADDR+4*351,DENALI_CTL_351_DATA);

#endif

#ifdef DENALI_CTL_352_DATA

REGWR(DDR_BASE_ADDR+4*352,DENALI_CTL_352_DATA);

#endif

#ifdef DENALI_CTL_353_DATA

REGWR(DDR_BASE_ADDR+4*353,DENALI_CTL_353_DATA);

#endif

#ifdef DENALI_CTL_354_DATA

REGWR(DDR_BASE_ADDR+4*354,DENALI_CTL_354_DATA);

#endif

#ifdef DENALI_CTL_355_DATA

REGWR(DDR_BASE_ADDR+4*355,DENALI_CTL_355_DATA);

#endif

#ifdef DENALI_CTL_356_DATA

REGWR(DDR_BASE_ADDR+4*356,DENALI_CTL_356_DATA);

#endif

#ifdef DENALI_CTL_357_DATA

REGWR(DDR_BASE_ADDR+4*357,DENALI_CTL_357_DATA);

#endif

#ifdef DENALI_CTL_358_DATA

REGWR(DDR_BASE_ADDR+4*358,DENALI_CTL_358_DATA);

#endif

#ifdef DENALI_CTL_359_DATA

REGWR(DDR_BASE_ADDR+4*359,DENALI_CTL_359_DATA);

#endif

#ifdef DENALI_CTL_360_DATA

REGWR(DDR_BASE_ADDR+4*360,DENALI_CTL_360_DATA);

#endif

#ifdef DENALI_CTL_361_DATA

REGWR(DDR_BASE_ADDR+4*361,DENALI_CTL_361_DATA);

#endif

#ifdef DENALI_CTL_362_DATA

REGWR(DDR_BASE_ADDR+4*362,DENALI_CTL_362_DATA);

#endif

#ifdef DENALI_CTL_363_DATA

REGWR(DDR_BASE_ADDR+4*363,DENALI_CTL_363_DATA);

#endif

#ifdef DENALI_CTL_364_DATA

REGWR(DDR_BASE_ADDR+4*364,DENALI_CTL_364_DATA);

#endif

#ifdef DENALI_CTL_365_DATA

REGWR(DDR_BASE_ADDR+4*365,DENALI_CTL_365_DATA);

#endif

#ifdef DENALI_CTL_366_DATA

REGWR(DDR_BASE_ADDR+4*366,DENALI_CTL_366_DATA);

#endif

#ifdef DENALI_CTL_367_DATA

REGWR(DDR_BASE_ADDR+4*367,DENALI_CTL_367_DATA);

#endif

#ifdef DENALI_CTL_368_DATA

REGWR(DDR_BASE_ADDR+4*368,DENALI_CTL_368_DATA);

#endif

#ifdef DENALI_CTL_369_DATA

REGWR(DDR_BASE_ADDR+4*369,DENALI_CTL_369_DATA);

#endif

#ifdef DENALI_CTL_370_DATA

REGWR(DDR_BASE_ADDR+4*370,DENALI_CTL_370_DATA);

#endif

#ifdef DENALI_CTL_371_DATA

REGWR(DDR_BASE_ADDR+4*371,DENALI_CTL_371_DATA);

#endif

#ifdef DENALI_CTL_372_DATA

REGWR(DDR_BASE_ADDR+4*372,DENALI_CTL_372_DATA);

#endif

#ifdef DENALI_CTL_373_DATA

REGWR(DDR_BASE_ADDR+4*373,DENALI_CTL_373_DATA);

#endif

#ifdef DENALI_CTL_374_DATA

REGWR(DDR_BASE_ADDR+4*374,DENALI_CTL_374_DATA);

#endif

#ifdef DENALI_CTL_375_DATA

REGWR(DDR_BASE_ADDR+4*375,DENALI_CTL_375_DATA);

#endif

#ifdef DENALI_CTL_376_DATA

REGWR(DDR_BASE_ADDR+4*376,DENALI_CTL_376_DATA);

#endif

#ifdef DENALI_CTL_377_DATA

REGWR(DDR_BASE_ADDR+4*377,DENALI_CTL_377_DATA);

#endif

#ifdef DENALI_CTL_378_DATA

REGWR(DDR_BASE_ADDR+4*378,DENALI_CTL_378_DATA);

#endif

#ifdef DENALI_CTL_379_DATA

REGWR(DDR_BASE_ADDR+4*379,DENALI_CTL_379_DATA);

#endif

#ifdef DENALI_CTL_380_DATA

REGWR(DDR_BASE_ADDR+4*380,DENALI_CTL_380_DATA);

#endif

#ifdef DENALI_CTL_381_DATA

REGWR(DDR_BASE_ADDR+4*381,DENALI_CTL_381_DATA);

#endif

#ifdef DENALI_CTL_382_DATA

REGWR(DDR_BASE_ADDR+4*382,DENALI_CTL_382_DATA);

#endif

#ifdef DENALI_CTL_383_DATA

REGWR(DDR_BASE_ADDR+4*383,DENALI_CTL_383_DATA);

#endif

#ifdef DENALI_CTL_384_DATA

REGWR(DDR_BASE_ADDR+4*384,DENALI_CTL_384_DATA);

#endif

#ifdef DENALI_CTL_385_DATA

REGWR(DDR_BASE_ADDR+4*385,DENALI_CTL_385_DATA);

#endif

#ifdef DENALI_CTL_386_DATA

REGWR(DDR_BASE_ADDR+4*386,DENALI_CTL_386_DATA);

#endif

#ifdef DENALI_CTL_387_DATA

REGWR(DDR_BASE_ADDR+4*387,DENALI_CTL_387_DATA);

#endif

#ifdef DENALI_CTL_388_DATA

REGWR(DDR_BASE_ADDR+4*388,DENALI_CTL_388_DATA);

#endif

#ifdef DENALI_CTL_389_DATA

REGWR(DDR_BASE_ADDR+4*389,DENALI_CTL_389_DATA);

#endif

#ifdef DENALI_CTL_390_DATA

REGWR(DDR_BASE_ADDR+4*390,DENALI_CTL_390_DATA);

#endif

#ifdef DENALI_CTL_391_DATA

REGWR(DDR_BASE_ADDR+4*391,DENALI_CTL_391_DATA);

#endif

#ifdef DENALI_CTL_392_DATA

REGWR(DDR_BASE_ADDR+4*392,DENALI_CTL_392_DATA);

#endif

#ifdef DENALI_CTL_393_DATA

REGWR(DDR_BASE_ADDR+4*393,DENALI_CTL_393_DATA);

#endif

#ifdef DENALI_CTL_394_DATA

REGWR(DDR_BASE_ADDR+4*394,DENALI_CTL_394_DATA);

#endif

#ifdef DENALI_CTL_395_DATA

REGWR(DDR_BASE_ADDR+4*395,DENALI_CTL_395_DATA);

#endif

#ifdef DENALI_CTL_396_DATA

REGWR(DDR_BASE_ADDR+4*396,DENALI_CTL_396_DATA);

#endif

#ifdef DENALI_CTL_397_DATA

REGWR(DDR_BASE_ADDR+4*397,DENALI_CTL_397_DATA);

#endif

#ifdef DENALI_CTL_398_DATA

REGWR(DDR_BASE_ADDR+4*398,DENALI_CTL_398_DATA);

#endif

#ifdef DENALI_CTL_399_DATA

REGWR(DDR_BASE_ADDR+4*399,DENALI_CTL_399_DATA);

#endif

#ifdef DENALI_CTL_400_DATA

REGWR(DDR_BASE_ADDR+4*400,DENALI_CTL_400_DATA);

#endif

#ifdef DENALI_CTL_401_DATA

REGWR(DDR_BASE_ADDR+4*401,DENALI_CTL_401_DATA);

#endif

#ifdef DENALI_CTL_402_DATA

REGWR(DDR_BASE_ADDR+4*402,DENALI_CTL_402_DATA);

#endif

#ifdef DENALI_CTL_403_DATA

REGWR(DDR_BASE_ADDR+4*403,DENALI_CTL_403_DATA);

#endif

#ifdef DENALI_CTL_404_DATA

REGWR(DDR_BASE_ADDR+4*404,DENALI_CTL_404_DATA);

#endif

#ifdef DENALI_CTL_405_DATA

REGWR(DDR_BASE_ADDR+4*405,DENALI_CTL_405_DATA);

#endif

#ifdef DENALI_CTL_406_DATA

REGWR(DDR_BASE_ADDR+4*406,DENALI_CTL_406_DATA);

#endif

#ifdef DENALI_CTL_407_DATA

REGWR(DDR_BASE_ADDR+4*407,DENALI_CTL_407_DATA);

#endif

#ifdef DENALI_CTL_408_DATA

REGWR(DDR_BASE_ADDR+4*408,DENALI_CTL_408_DATA);

#endif

#ifdef DENALI_CTL_409_DATA

REGWR(DDR_BASE_ADDR+4*409,DENALI_CTL_409_DATA);

#endif

#ifdef DENALI_CTL_410_DATA

REGWR(DDR_BASE_ADDR+4*410,DENALI_CTL_410_DATA);

#endif

#ifdef DENALI_CTL_411_DATA

REGWR(DDR_BASE_ADDR+4*411,DENALI_CTL_411_DATA);

#endif

#ifdef DENALI_CTL_412_DATA

REGWR(DDR_BASE_ADDR+4*412,DENALI_CTL_412_DATA);

#endif

#ifdef DENALI_CTL_413_DATA

REGWR(DDR_BASE_ADDR+4*413,DENALI_CTL_413_DATA);

#endif

#ifdef DENALI_CTL_414_DATA

REGWR(DDR_BASE_ADDR+4*414,DENALI_CTL_414_DATA);

#endif

#ifdef DENALI_CTL_415_DATA

REGWR(DDR_BASE_ADDR+4*415,DENALI_CTL_415_DATA);

#endif

#ifdef DENALI_CTL_416_DATA

REGWR(DDR_BASE_ADDR+4*416,DENALI_CTL_416_DATA);

#endif

#ifdef DENALI_CTL_417_DATA

REGWR(DDR_BASE_ADDR+4*417,DENALI_CTL_417_DATA);

#endif

#ifdef DENALI_CTL_418_DATA

REGWR(DDR_BASE_ADDR+4*418,DENALI_CTL_418_DATA);

#endif

#ifdef DENALI_CTL_419_DATA

REGWR(DDR_BASE_ADDR+4*419,DENALI_CTL_419_DATA);

#endif

#ifdef DENALI_CTL_420_DATA

REGWR(DDR_BASE_ADDR+4*420,DENALI_CTL_420_DATA);

#endif

#ifdef DENALI_CTL_421_DATA

REGWR(DDR_BASE_ADDR+4*421,DENALI_CTL_421_DATA);

#endif

#ifdef DENALI_CTL_422_DATA

REGWR(DDR_BASE_ADDR+4*422,DENALI_CTL_422_DATA);

#endif

#ifdef DENALI_CTL_423_DATA

REGWR(DDR_BASE_ADDR+4*423,DENALI_CTL_423_DATA);

#endif

#ifdef DENALI_CTL_424_DATA

REGWR(DDR_BASE_ADDR+4*424,DENALI_CTL_424_DATA);

#endif

#ifdef DENALI_CTL_425_DATA

REGWR(DDR_BASE_ADDR+4*425,DENALI_CTL_425_DATA);

#endif

#ifdef DENALI_CTL_426_DATA

REGWR(DDR_BASE_ADDR+4*426,DENALI_CTL_426_DATA);

#endif

#ifdef DENALI_CTL_427_DATA

REGWR(DDR_BASE_ADDR+4*427,DENALI_CTL_427_DATA);

#endif

#ifdef DENALI_CTL_428_DATA

REGWR(DDR_BASE_ADDR+4*428,DENALI_CTL_428_DATA);

#endif

#ifdef DENALI_CTL_429_DATA

REGWR(DDR_BASE_ADDR+4*429,DENALI_CTL_429_DATA);

#endif

#ifdef DENALI_CTL_430_DATA

REGWR(DDR_BASE_ADDR+4*430,DENALI_CTL_430_DATA);

#endif

#ifdef DENALI_CTL_431_DATA

REGWR(DDR_BASE_ADDR+4*431,DENALI_CTL_431_DATA);

#endif

#ifdef DENALI_CTL_432_DATA

REGWR(DDR_BASE_ADDR+4*432,DENALI_CTL_432_DATA);

#endif

#ifdef DENALI_CTL_433_DATA

REGWR(DDR_BASE_ADDR+4*433,DENALI_CTL_433_DATA);

#endif

#ifdef DENALI_CTL_434_DATA

REGWR(DDR_BASE_ADDR+4*434,DENALI_CTL_434_DATA);

#endif

#ifdef DENALI_CTL_435_DATA

REGWR(DDR_BASE_ADDR+4*435,DENALI_CTL_435_DATA);

#endif

#ifdef DENALI_CTL_436_DATA

REGWR(DDR_BASE_ADDR+4*436,DENALI_CTL_436_DATA);

#endif

#ifdef DENALI_CTL_437_DATA

REGWR(DDR_BASE_ADDR+4*437,DENALI_CTL_437_DATA);

#endif

#ifdef DENALI_CTL_438_DATA

REGWR(DDR_BASE_ADDR+4*438,DENALI_CTL_438_DATA);

#endif

#ifdef DENALI_CTL_439_DATA

REGWR(DDR_BASE_ADDR+4*439,DENALI_CTL_439_DATA);

#endif

#ifdef DENALI_CTL_440_DATA

REGWR(DDR_BASE_ADDR+4*440,DENALI_CTL_440_DATA);

#endif

#ifdef DENALI_CTL_441_DATA

REGWR(DDR_BASE_ADDR+4*441,DENALI_CTL_441_DATA);

#endif

#ifdef DENALI_CTL_442_DATA

REGWR(DDR_BASE_ADDR+4*442,DENALI_CTL_442_DATA);

#endif

#ifdef DENALI_CTL_443_DATA

REGWR(DDR_BASE_ADDR+4*443,DENALI_CTL_443_DATA);

#endif

#ifdef DENALI_CTL_444_DATA

REGWR(DDR_BASE_ADDR+4*444,DENALI_CTL_444_DATA);

#endif

#ifdef DENALI_CTL_445_DATA

REGWR(DDR_BASE_ADDR+4*445,DENALI_CTL_445_DATA);

#endif

#ifdef DENALI_CTL_446_DATA

REGWR(DDR_BASE_ADDR+4*446,DENALI_CTL_446_DATA);

#endif

#ifdef DENALI_CTL_447_DATA

REGWR(DDR_BASE_ADDR+4*447,DENALI_CTL_447_DATA);

#endif

#ifdef DENALI_CTL_448_DATA

REGWR(DDR_BASE_ADDR+4*448,DENALI_CTL_448_DATA);

#endif

#ifdef DENALI_CTL_449_DATA

REGWR(DDR_BASE_ADDR+4*449,DENALI_CTL_449_DATA);

#endif

#ifdef DENALI_CTL_450_DATA

REGWR(DDR_BASE_ADDR+4*450,DENALI_CTL_450_DATA);

#endif

#ifdef DENALI_CTL_451_DATA

REGWR(DDR_BASE_ADDR+4*451,DENALI_CTL_451_DATA);

#endif

#ifdef DENALI_CTL_452_DATA

REGWR(DDR_BASE_ADDR+4*452,DENALI_CTL_452_DATA);

#endif

#ifdef DENALI_CTL_453_DATA

REGWR(DDR_BASE_ADDR+4*453,DENALI_CTL_453_DATA);

#endif

#ifdef DENALI_CTL_454_DATA

REGWR(DDR_BASE_ADDR+4*454,DENALI_CTL_454_DATA);

#endif

#ifdef DENALI_CTL_455_DATA

REGWR(DDR_BASE_ADDR+4*455,DENALI_CTL_455_DATA);

#endif

#ifdef DENALI_CTL_456_DATA

REGWR(DDR_BASE_ADDR+4*456,DENALI_CTL_456_DATA);

#endif

#ifdef DENALI_CTL_457_DATA

REGWR(DDR_BASE_ADDR+4*457,DENALI_CTL_457_DATA);

#endif

#ifdef DENALI_CTL_458_DATA

REGWR(DDR_BASE_ADDR+4*458,DENALI_CTL_458_DATA);

#endif

#ifdef DENALI_CTL_459_DATA

REGWR(DDR_BASE_ADDR+4*459,DENALI_CTL_459_DATA);

#endif

#ifdef DENALI_CTL_460_DATA

REGWR(DDR_BASE_ADDR+4*460,DENALI_CTL_460_DATA);

#endif

#ifdef DENALI_CTL_461_DATA

REGWR(DDR_BASE_ADDR+4*461,DENALI_CTL_461_DATA);

#endif

#ifdef DENALI_CTL_462_DATA

REGWR(DDR_BASE_ADDR+4*462,DENALI_CTL_462_DATA);

#endif

#ifdef DENALI_CTL_463_DATA

REGWR(DDR_BASE_ADDR+4*463,DENALI_CTL_463_DATA);

#endif

#ifdef DENALI_CTL_464_DATA

REGWR(DDR_BASE_ADDR+4*464,DENALI_CTL_464_DATA);

#endif

#ifdef DENALI_CTL_465_DATA

REGWR(DDR_BASE_ADDR+4*465,DENALI_CTL_465_DATA);

#endif

#ifdef DENALI_CTL_466_DATA

REGWR(DDR_BASE_ADDR+4*466,DENALI_CTL_466_DATA);

#endif

#ifdef DENALI_CTL_467_DATA

REGWR(DDR_BASE_ADDR+4*467,DENALI_CTL_467_DATA);

#endif

#ifdef DENALI_CTL_468_DATA

REGWR(DDR_BASE_ADDR+4*468,DENALI_CTL_468_DATA);

#endif

#ifdef DENALI_CTL_469_DATA

REGWR(DDR_BASE_ADDR+4*469,DENALI_CTL_469_DATA);

#endif

#ifdef DENALI_CTL_470_DATA

REGWR(DDR_BASE_ADDR+4*470,DENALI_CTL_470_DATA);

#endif

#ifdef DENALI_CTL_471_DATA

REGWR(DDR_BASE_ADDR+4*471,DENALI_CTL_471_DATA);

#endif

#ifdef DENALI_CTL_472_DATA

REGWR(DDR_BASE_ADDR+4*472,DENALI_CTL_472_DATA);

#endif

#ifdef DENALI_CTL_473_DATA

REGWR(DDR_BASE_ADDR+4*473,DENALI_CTL_473_DATA);

#endif

#ifdef DENALI_CTL_474_DATA

REGWR(DDR_BASE_ADDR+4*474,DENALI_CTL_474_DATA);

#endif

#ifdef DENALI_CTL_475_DATA

REGWR(DDR_BASE_ADDR+4*475,DENALI_CTL_475_DATA);

#endif

#ifdef DENALI_CTL_476_DATA

REGWR(DDR_BASE_ADDR+4*476,DENALI_CTL_476_DATA);

#endif

#ifdef DENALI_CTL_477_DATA

REGWR(DDR_BASE_ADDR+4*477,DENALI_CTL_477_DATA);

#endif

#ifdef DENALI_CTL_478_DATA

REGWR(DDR_BASE_ADDR+4*478,DENALI_CTL_478_DATA);

#endif

#ifdef DENALI_CTL_479_DATA

REGWR(DDR_BASE_ADDR+4*479,DENALI_CTL_479_DATA);

#endif

#ifdef DENALI_CTL_480_DATA

REGWR(DDR_BASE_ADDR+4*480,DENALI_CTL_480_DATA);

#endif

#ifdef DENALI_CTL_481_DATA

REGWR(DDR_BASE_ADDR+4*481,DENALI_CTL_481_DATA);

#endif

#ifdef DENALI_CTL_482_DATA

REGWR(DDR_BASE_ADDR+4*482,DENALI_CTL_482_DATA);

#endif

#ifdef DENALI_CTL_483_DATA

REGWR(DDR_BASE_ADDR+4*483,DENALI_CTL_483_DATA);

#endif

#ifdef DENALI_CTL_484_DATA

REGWR(DDR_BASE_ADDR+4*484,DENALI_CTL_484_DATA);

#endif

#ifdef DENALI_CTL_485_DATA

REGWR(DDR_BASE_ADDR+4*485,DENALI_CTL_485_DATA);

#endif

#ifdef DENALI_CTL_486_DATA

REGWR(DDR_BASE_ADDR+4*486,DENALI_CTL_486_DATA);

#endif

#ifdef DENALI_CTL_487_DATA

REGWR(DDR_BASE_ADDR+4*487,DENALI_CTL_487_DATA);

#endif

#ifdef DENALI_CTL_488_DATA

REGWR(DDR_BASE_ADDR+4*488,DENALI_CTL_488_DATA);

#endif

#ifdef DENALI_CTL_489_DATA

REGWR(DDR_BASE_ADDR+4*489,DENALI_CTL_489_DATA);

#endif

#ifdef DENALI_CTL_490_DATA

REGWR(DDR_BASE_ADDR+4*490,DENALI_CTL_490_DATA);

#endif

#ifdef DENALI_CTL_491_DATA

REGWR(DDR_BASE_ADDR+4*491,DENALI_CTL_491_DATA);

#endif

#ifdef DENALI_CTL_492_DATA

REGWR(DDR_BASE_ADDR+4*492,DENALI_CTL_492_DATA);

#endif

#ifdef DENALI_CTL_493_DATA

REGWR(DDR_BASE_ADDR+4*493,DENALI_CTL_493_DATA);

#endif

#ifdef DENALI_CTL_494_DATA

REGWR(DDR_BASE_ADDR+4*494,DENALI_CTL_494_DATA);

#endif

#ifdef DENALI_CTL_495_DATA

REGWR(DDR_BASE_ADDR+4*495,DENALI_CTL_495_DATA);

#endif

#ifdef DENALI_CTL_496_DATA

REGWR(DDR_BASE_ADDR+4*496,DENALI_CTL_496_DATA);

#endif

#ifdef DENALI_CTL_497_DATA

REGWR(DDR_BASE_ADDR+4*497,DENALI_CTL_497_DATA);

#endif

#ifdef DENALI_CTL_498_DATA

REGWR(DDR_BASE_ADDR+4*498,DENALI_CTL_498_DATA);

#endif

#ifdef DENALI_CTL_499_DATA

REGWR(DDR_BASE_ADDR+4*499,DENALI_CTL_499_DATA);

#endif

#ifdef DENALI_CTL_500_DATA

REGWR(DDR_BASE_ADDR+4*500,DENALI_CTL_500_DATA);

#endif

#ifdef DENALI_CTL_501_DATA

REGWR(DDR_BASE_ADDR+4*501,DENALI_CTL_501_DATA);

#endif

#ifdef DENALI_CTL_502_DATA

REGWR(DDR_BASE_ADDR+4*502,DENALI_CTL_502_DATA);

#endif

#ifdef DENALI_CTL_503_DATA

REGWR(DDR_BASE_ADDR+4*503,DENALI_CTL_503_DATA);

#endif

#ifdef DENALI_CTL_504_DATA

REGWR(DDR_BASE_ADDR+4*504,DENALI_CTL_504_DATA);

#endif

#ifdef DENALI_CTL_505_DATA

REGWR(DDR_BASE_ADDR+4*505,DENALI_CTL_505_DATA);

#endif

#ifdef DENALI_CTL_506_DATA

REGWR(DDR_BASE_ADDR+4*506,DENALI_CTL_506_DATA);

#endif

#ifdef DENALI_CTL_507_DATA

REGWR(DDR_BASE_ADDR+4*507,DENALI_CTL_507_DATA);

#endif

#ifdef DENALI_CTL_508_DATA

REGWR(DDR_BASE_ADDR+4*508,DENALI_CTL_508_DATA);

#endif

#ifdef DENALI_CTL_509_DATA

REGWR(DDR_BASE_ADDR+4*509,DENALI_CTL_509_DATA);

#endif

#ifdef DENALI_CTL_510_DATA

REGWR(DDR_BASE_ADDR+4*510,DENALI_CTL_510_DATA);

#endif

#ifdef DENALI_CTL_511_DATA

REGWR(DDR_BASE_ADDR+4*511,DENALI_CTL_511_DATA);

#endif

#ifdef DENALI_CTL_512_DATA

REGWR(DDR_BASE_ADDR+4*512,DENALI_CTL_512_DATA);

#endif

#ifdef DENALI_CTL_513_DATA

REGWR(DDR_BASE_ADDR+4*513,DENALI_CTL_513_DATA);

#endif

#ifdef DENALI_CTL_514_DATA

REGWR(DDR_BASE_ADDR+4*514,DENALI_CTL_514_DATA);

#endif

#ifdef DENALI_CTL_515_DATA

REGWR(DDR_BASE_ADDR+4*515,DENALI_CTL_515_DATA);

#endif

#ifdef DENALI_CTL_516_DATA

REGWR(DDR_BASE_ADDR+4*516,DENALI_CTL_516_DATA);

#endif

#ifdef DENALI_CTL_517_DATA

REGWR(DDR_BASE_ADDR+4*517,DENALI_CTL_517_DATA);

#endif

#ifdef DENALI_CTL_518_DATA

REGWR(DDR_BASE_ADDR+4*518,DENALI_CTL_518_DATA);

#endif

#ifdef DENALI_CTL_519_DATA

REGWR(DDR_BASE_ADDR+4*519,DENALI_CTL_519_DATA);

#endif

#ifdef DENALI_CTL_520_DATA

REGWR(DDR_BASE_ADDR+4*520,DENALI_CTL_520_DATA);

#endif

#ifdef DENALI_CTL_521_DATA

REGWR(DDR_BASE_ADDR+4*521,DENALI_CTL_521_DATA);

#endif

#ifdef DENALI_CTL_522_DATA

REGWR(DDR_BASE_ADDR+4*522,DENALI_CTL_522_DATA);

#endif

#ifdef DENALI_CTL_523_DATA

REGWR(DDR_BASE_ADDR+4*523,DENALI_CTL_523_DATA);

#endif

#ifdef DENALI_CTL_524_DATA

REGWR(DDR_BASE_ADDR+4*524,DENALI_CTL_524_DATA);

#endif

#ifdef DENALI_CTL_525_DATA

REGWR(DDR_BASE_ADDR+4*525,DENALI_CTL_525_DATA);

#endif

#ifdef DENALI_CTL_526_DATA

REGWR(DDR_BASE_ADDR+4*526,DENALI_CTL_526_DATA);

#endif

#ifdef DENALI_CTL_527_DATA

REGWR(DDR_BASE_ADDR+4*527,DENALI_CTL_527_DATA);

#endif

#ifdef DENALI_CTL_528_DATA

REGWR(DDR_BASE_ADDR+4*528,DENALI_CTL_528_DATA);

#endif

#ifdef DENALI_CTL_529_DATA

REGWR(DDR_BASE_ADDR+4*529,DENALI_CTL_529_DATA);

#endif

#ifdef DENALI_CTL_530_DATA

REGWR(DDR_BASE_ADDR+4*530,DENALI_CTL_530_DATA);

#endif

#ifdef DENALI_CTL_531_DATA

REGWR(DDR_BASE_ADDR+4*531,DENALI_CTL_531_DATA);

#endif

#ifdef DENALI_CTL_532_DATA

REGWR(DDR_BASE_ADDR+4*532,DENALI_CTL_532_DATA);

#endif

#ifdef DENALI_CTL_533_DATA

REGWR(DDR_BASE_ADDR+4*533,DENALI_CTL_533_DATA);

#endif

#ifdef DENALI_CTL_534_DATA

REGWR(DDR_BASE_ADDR+4*534,DENALI_CTL_534_DATA);

#endif

#ifdef DENALI_CTL_535_DATA

REGWR(DDR_BASE_ADDR+4*535,DENALI_CTL_535_DATA);

#endif

#ifdef DENALI_CTL_536_DATA

REGWR(DDR_BASE_ADDR+4*536,DENALI_CTL_536_DATA);

#endif

#ifdef DENALI_CTL_537_DATA

REGWR(DDR_BASE_ADDR+4*537,DENALI_CTL_537_DATA);

#endif

#ifdef DENALI_CTL_538_DATA

REGWR(DDR_BASE_ADDR+4*538,DENALI_CTL_538_DATA);

#endif

#ifdef DENALI_CTL_539_DATA

REGWR(DDR_BASE_ADDR+4*539,DENALI_CTL_539_DATA);

#endif

#ifdef DENALI_CTL_540_DATA

REGWR(DDR_BASE_ADDR+4*540,DENALI_CTL_540_DATA);

#endif

#ifdef DENALI_CTL_541_DATA

REGWR(DDR_BASE_ADDR+4*541,DENALI_CTL_541_DATA);

#endif

#ifdef DENALI_CTL_542_DATA

REGWR(DDR_BASE_ADDR+4*542,DENALI_CTL_542_DATA);

#endif

#ifdef DENALI_CTL_543_DATA

REGWR(DDR_BASE_ADDR+4*543,DENALI_CTL_543_DATA);

#endif

#ifdef DENALI_CTL_544_DATA

REGWR(DDR_BASE_ADDR+4*544,DENALI_CTL_544_DATA);

#endif

#ifdef DENALI_CTL_545_DATA

REGWR(DDR_BASE_ADDR+4*545,DENALI_CTL_545_DATA);

#endif

#ifdef DENALI_CTL_546_DATA

REGWR(DDR_BASE_ADDR+4*546,DENALI_CTL_546_DATA);

#endif

#ifdef DENALI_CTL_547_DATA

REGWR(DDR_BASE_ADDR+4*547,DENALI_CTL_547_DATA);

#endif

#ifdef DENALI_CTL_548_DATA

REGWR(DDR_BASE_ADDR+4*548,DENALI_CTL_548_DATA);

#endif

#ifdef DENALI_CTL_549_DATA

REGWR(DDR_BASE_ADDR+4*549,DENALI_CTL_549_DATA);

#endif

#ifdef DENALI_CTL_550_DATA

REGWR(DDR_BASE_ADDR+4*550,DENALI_CTL_550_DATA);

#endif

#ifdef DENALI_CTL_551_DATA

REGWR(DDR_BASE_ADDR+4*551,DENALI_CTL_551_DATA);

#endif

#ifdef DENALI_CTL_552_DATA

REGWR(DDR_BASE_ADDR+4*552,DENALI_CTL_552_DATA);

#endif

#ifdef DENALI_CTL_553_DATA

REGWR(DDR_BASE_ADDR+4*553,DENALI_CTL_553_DATA);

#endif

#ifdef DENALI_CTL_554_DATA

REGWR(DDR_BASE_ADDR+4*554,DENALI_CTL_554_DATA);

#endif

#ifdef DENALI_CTL_555_DATA

REGWR(DDR_BASE_ADDR+4*555,DENALI_CTL_555_DATA);

#endif

#ifdef DENALI_CTL_556_DATA

REGWR(DDR_BASE_ADDR+4*556,DENALI_CTL_556_DATA);

#endif

#ifdef DENALI_CTL_557_DATA

REGWR(DDR_BASE_ADDR+4*557,DENALI_CTL_557_DATA);

#endif

#ifdef DENALI_CTL_558_DATA

REGWR(DDR_BASE_ADDR+4*558,DENALI_CTL_558_DATA);

#endif

#ifdef DENALI_CTL_559_DATA

REGWR(DDR_BASE_ADDR+4*559,DENALI_CTL_559_DATA);

#endif

#ifdef DENALI_CTL_560_DATA

REGWR(DDR_BASE_ADDR+4*560,DENALI_CTL_560_DATA);

#endif

#ifdef DENALI_CTL_561_DATA

REGWR(DDR_BASE_ADDR+4*561,DENALI_CTL_561_DATA);

#endif

#ifdef DENALI_CTL_562_DATA

REGWR(DDR_BASE_ADDR+4*562,DENALI_CTL_562_DATA);

#endif

#ifdef DENALI_CTL_563_DATA

REGWR(DDR_BASE_ADDR+4*563,DENALI_CTL_563_DATA);

#endif

#ifdef DENALI_CTL_564_DATA

REGWR(DDR_BASE_ADDR+4*564,DENALI_CTL_564_DATA);

#endif

#ifdef DENALI_CTL_565_DATA

REGWR(DDR_BASE_ADDR+4*565,DENALI_CTL_565_DATA);

#endif

#ifdef DENALI_CTL_566_DATA

REGWR(DDR_BASE_ADDR+4*566,DENALI_CTL_566_DATA);

#endif

#ifdef DENALI_CTL_567_DATA

REGWR(DDR_BASE_ADDR+4*567,DENALI_CTL_567_DATA);

#endif

#ifdef DENALI_CTL_568_DATA

REGWR(DDR_BASE_ADDR+4*568,DENALI_CTL_568_DATA);

#endif

#ifdef DENALI_CTL_569_DATA

REGWR(DDR_BASE_ADDR+4*569,DENALI_CTL_569_DATA);

#endif

#ifdef DENALI_CTL_570_DATA

REGWR(DDR_BASE_ADDR+4*570,DENALI_CTL_570_DATA);

#endif

#ifdef DENALI_CTL_571_DATA

REGWR(DDR_BASE_ADDR+4*571,DENALI_CTL_571_DATA);

#endif

#ifdef DENALI_CTL_572_DATA

REGWR(DDR_BASE_ADDR+4*572,DENALI_CTL_572_DATA);

#endif

#ifdef DENALI_CTL_573_DATA

REGWR(DDR_BASE_ADDR+4*573,DENALI_CTL_573_DATA);

#endif

#ifdef DENALI_CTL_574_DATA

REGWR(DDR_BASE_ADDR+4*574,DENALI_CTL_574_DATA);

#endif

#ifdef DENALI_CTL_575_DATA

REGWR(DDR_BASE_ADDR+4*575,DENALI_CTL_575_DATA);

#endif

#ifdef DENALI_CTL_576_DATA

REGWR(DDR_BASE_ADDR+4*576,DENALI_CTL_576_DATA);

#endif

#ifdef DENALI_CTL_577_DATA

REGWR(DDR_BASE_ADDR+4*577,DENALI_CTL_577_DATA);

#endif

#ifdef DENALI_CTL_578_DATA

REGWR(DDR_BASE_ADDR+4*578,DENALI_CTL_578_DATA);

#endif

#ifdef DENALI_CTL_579_DATA

REGWR(DDR_BASE_ADDR+4*579,DENALI_CTL_579_DATA);

#endif

#ifdef DENALI_CTL_580_DATA

REGWR(DDR_BASE_ADDR+4*580,DENALI_CTL_580_DATA);

#endif

#ifdef DENALI_CTL_581_DATA

REGWR(DDR_BASE_ADDR+4*581,DENALI_CTL_581_DATA);

#endif

#ifdef DENALI_CTL_582_DATA

REGWR(DDR_BASE_ADDR+4*582,DENALI_CTL_582_DATA);

#endif

#ifdef DENALI_CTL_583_DATA

REGWR(DDR_BASE_ADDR+4*583,DENALI_CTL_583_DATA);

#endif

#ifdef DENALI_CTL_584_DATA

REGWR(DDR_BASE_ADDR+4*584,DENALI_CTL_584_DATA);

#endif

#ifdef DENALI_CTL_585_DATA

REGWR(DDR_BASE_ADDR+4*585,DENALI_CTL_585_DATA);

#endif

#ifdef DENALI_CTL_586_DATA

REGWR(DDR_BASE_ADDR+4*586,DENALI_CTL_586_DATA);

#endif

#ifdef DENALI_CTL_587_DATA

REGWR(DDR_BASE_ADDR+4*587,DENALI_CTL_587_DATA);

#endif

#ifdef DENALI_CTL_588_DATA

REGWR(DDR_BASE_ADDR+4*588,DENALI_CTL_588_DATA);

#endif

#ifdef DENALI_CTL_589_DATA

REGWR(DDR_BASE_ADDR+4*589,DENALI_CTL_589_DATA);

#endif

#ifdef DENALI_CTL_590_DATA

REGWR(DDR_BASE_ADDR+4*590,DENALI_CTL_590_DATA);

#endif

#ifdef DENALI_CTL_591_DATA

REGWR(DDR_BASE_ADDR+4*591,DENALI_CTL_591_DATA);

#endif

#ifdef DENALI_CTL_592_DATA

REGWR(DDR_BASE_ADDR+4*592,DENALI_CTL_592_DATA);

#endif

#ifdef DENALI_CTL_593_DATA

REGWR(DDR_BASE_ADDR+4*593,DENALI_CTL_593_DATA);

#endif

#ifdef DENALI_CTL_594_DATA

REGWR(DDR_BASE_ADDR+4*594,DENALI_CTL_594_DATA);

#endif

#ifdef DENALI_CTL_595_DATA

REGWR(DDR_BASE_ADDR+4*595,DENALI_CTL_595_DATA);

#endif

#ifdef DENALI_CTL_596_DATA

REGWR(DDR_BASE_ADDR+4*596,DENALI_CTL_596_DATA);

#endif

#ifdef DENALI_CTL_597_DATA

REGWR(DDR_BASE_ADDR+4*597,DENALI_CTL_597_DATA);

#endif

#ifdef DENALI_CTL_598_DATA

REGWR(DDR_BASE_ADDR+4*598,DENALI_CTL_598_DATA);

#endif

#ifdef DENALI_CTL_599_DATA

REGWR(DDR_BASE_ADDR+4*599,DENALI_CTL_599_DATA);

#endif

#ifdef DENALI_CTL_600_DATA

REGWR(DDR_BASE_ADDR+4*600,DENALI_CTL_600_DATA);

#endif

#ifdef DENALI_CTL_601_DATA

REGWR(DDR_BASE_ADDR+4*601,DENALI_CTL_601_DATA);

#endif

#ifdef DENALI_CTL_602_DATA

REGWR(DDR_BASE_ADDR+4*602,DENALI_CTL_602_DATA);

#endif

#ifdef DENALI_CTL_603_DATA

REGWR(DDR_BASE_ADDR+4*603,DENALI_CTL_603_DATA);

#endif

#ifdef DENALI_CTL_604_DATA

REGWR(DDR_BASE_ADDR+4*604,DENALI_CTL_604_DATA);

#endif

#ifdef DENALI_CTL_605_DATA

REGWR(DDR_BASE_ADDR+4*605,DENALI_CTL_605_DATA);

#endif

#ifdef DENALI_CTL_606_DATA

REGWR(DDR_BASE_ADDR+4*606,DENALI_CTL_606_DATA);

#endif

#ifdef DENALI_CTL_607_DATA

REGWR(DDR_BASE_ADDR+4*607,DENALI_CTL_607_DATA);

#endif

#ifdef DENALI_CTL_608_DATA

REGWR(DDR_BASE_ADDR+4*608,DENALI_CTL_608_DATA);

#endif

#ifdef DENALI_CTL_609_DATA

REGWR(DDR_BASE_ADDR+4*609,DENALI_CTL_609_DATA);

#endif

#ifdef DENALI_CTL_610_DATA

REGWR(DDR_BASE_ADDR+4*610,DENALI_CTL_610_DATA);

#endif

#ifdef DENALI_CTL_611_DATA

REGWR(DDR_BASE_ADDR+4*611,DENALI_CTL_611_DATA);

#endif

#ifdef DENALI_CTL_612_DATA

REGWR(DDR_BASE_ADDR+4*612,DENALI_CTL_612_DATA);

#endif

#ifdef DENALI_CTL_613_DATA

REGWR(DDR_BASE_ADDR+4*613,DENALI_CTL_613_DATA);

#endif

#ifdef DENALI_CTL_614_DATA

REGWR(DDR_BASE_ADDR+4*614,DENALI_CTL_614_DATA);

#endif

#ifdef DENALI_CTL_615_DATA

REGWR(DDR_BASE_ADDR+4*615,DENALI_CTL_615_DATA);

#endif

#ifdef DENALI_CTL_616_DATA

REGWR(DDR_BASE_ADDR+4*616,DENALI_CTL_616_DATA);

#endif

#ifdef DENALI_CTL_617_DATA

REGWR(DDR_BASE_ADDR+4*617,DENALI_CTL_617_DATA);

#endif

#ifdef DENALI_CTL_618_DATA

REGWR(DDR_BASE_ADDR+4*618,DENALI_CTL_618_DATA);

#endif

#ifdef DENALI_CTL_619_DATA

REGWR(DDR_BASE_ADDR+4*619,DENALI_CTL_619_DATA);

#endif

#ifdef DENALI_CTL_620_DATA

REGWR(DDR_BASE_ADDR+4*620,DENALI_CTL_620_DATA);

#endif

#ifdef DENALI_CTL_621_DATA

REGWR(DDR_BASE_ADDR+4*621,DENALI_CTL_621_DATA);

#endif

#ifdef DENALI_CTL_622_DATA

REGWR(DDR_BASE_ADDR+4*622,DENALI_CTL_622_DATA);

#endif

#ifdef DENALI_CTL_623_DATA

REGWR(DDR_BASE_ADDR+4*623,DENALI_CTL_623_DATA);

#endif

#ifdef DENALI_CTL_624_DATA

REGWR(DDR_BASE_ADDR+4*624,DENALI_CTL_624_DATA);

#endif

#ifdef DENALI_CTL_625_DATA

REGWR(DDR_BASE_ADDR+4*625,DENALI_CTL_625_DATA);

#endif

#ifdef DENALI_CTL_626_DATA

REGWR(DDR_BASE_ADDR+4*626,DENALI_CTL_626_DATA);

#endif

#ifdef DENALI_CTL_627_DATA

REGWR(DDR_BASE_ADDR+4*627,DENALI_CTL_627_DATA);

#endif

#ifdef DENALI_CTL_628_DATA

REGWR(DDR_BASE_ADDR+4*628,DENALI_CTL_628_DATA);

#endif

#ifdef DENALI_CTL_629_DATA

REGWR(DDR_BASE_ADDR+4*629,DENALI_CTL_629_DATA);

#endif

#ifdef DENALI_CTL_630_DATA

REGWR(DDR_BASE_ADDR+4*630,DENALI_CTL_630_DATA);

#endif

#ifdef DENALI_CTL_631_DATA

REGWR(DDR_BASE_ADDR+4*631,DENALI_CTL_631_DATA);

#endif

#ifdef DENALI_CTL_632_DATA

REGWR(DDR_BASE_ADDR+4*632,DENALI_CTL_632_DATA);

#endif

#ifdef DENALI_CTL_633_DATA

REGWR(DDR_BASE_ADDR+4*633,DENALI_CTL_633_DATA);

#endif

#ifdef DENALI_CTL_634_DATA

REGWR(DDR_BASE_ADDR+4*634,DENALI_CTL_634_DATA);

#endif

#ifdef DENALI_CTL_635_DATA

REGWR(DDR_BASE_ADDR+4*635,DENALI_CTL_635_DATA);

#endif

#ifdef DENALI_CTL_636_DATA

REGWR(DDR_BASE_ADDR+4*636,DENALI_CTL_636_DATA);

#endif

#ifdef DENALI_CTL_637_DATA

REGWR(DDR_BASE_ADDR+4*637,DENALI_CTL_637_DATA);

#endif

#ifdef DENALI_CTL_638_DATA

REGWR(DDR_BASE_ADDR+4*638,DENALI_CTL_638_DATA);

#endif

#ifdef DENALI_CTL_639_DATA

REGWR(DDR_BASE_ADDR+4*639,DENALI_CTL_639_DATA);

#endif

#ifdef DENALI_CTL_640_DATA

REGWR(DDR_BASE_ADDR+4*640,DENALI_CTL_640_DATA);

#endif

#ifdef DENALI_CTL_641_DATA

REGWR(DDR_BASE_ADDR+4*641,DENALI_CTL_641_DATA);

#endif

#ifdef DENALI_CTL_642_DATA

REGWR(DDR_BASE_ADDR+4*642,DENALI_CTL_642_DATA);

#endif

#ifdef DENALI_CTL_643_DATA

REGWR(DDR_BASE_ADDR+4*643,DENALI_CTL_643_DATA);

#endif

#ifdef DENALI_CTL_644_DATA

REGWR(DDR_BASE_ADDR+4*644,DENALI_CTL_644_DATA);

#endif

#ifdef DENALI_CTL_645_DATA

REGWR(DDR_BASE_ADDR+4*645,DENALI_CTL_645_DATA);

#endif

#ifdef DENALI_CTL_646_DATA

REGWR(DDR_BASE_ADDR+4*646,DENALI_CTL_646_DATA);

#endif

#ifdef DENALI_CTL_647_DATA

REGWR(DDR_BASE_ADDR+4*647,DENALI_CTL_647_DATA);

#endif

#ifdef DENALI_CTL_648_DATA

REGWR(DDR_BASE_ADDR+4*648,DENALI_CTL_648_DATA);

#endif

#ifdef DENALI_CTL_649_DATA

REGWR(DDR_BASE_ADDR+4*649,DENALI_CTL_649_DATA);

#endif

#ifdef DENALI_CTL_650_DATA

REGWR(DDR_BASE_ADDR+4*650,DENALI_CTL_650_DATA);

#endif

#ifdef DENALI_CTL_651_DATA

REGWR(DDR_BASE_ADDR+4*651,DENALI_CTL_651_DATA);

#endif

#ifdef DENALI_CTL_652_DATA

REGWR(DDR_BASE_ADDR+4*652,DENALI_CTL_652_DATA);

#endif

#ifdef DENALI_CTL_653_DATA

REGWR(DDR_BASE_ADDR+4*653,DENALI_CTL_653_DATA);

#endif

#ifdef DENALI_CTL_654_DATA

REGWR(DDR_BASE_ADDR+4*654,DENALI_CTL_654_DATA);

#endif

#ifdef DENALI_CTL_655_DATA

REGWR(DDR_BASE_ADDR+4*655,DENALI_CTL_655_DATA);

#endif

#ifdef DENALI_CTL_656_DATA

REGWR(DDR_BASE_ADDR+4*656,DENALI_CTL_656_DATA);

#endif

#ifdef DENALI_CTL_657_DATA

REGWR(DDR_BASE_ADDR+4*657,DENALI_CTL_657_DATA);

#endif

#ifdef DENALI_CTL_658_DATA

REGWR(DDR_BASE_ADDR+4*658,DENALI_CTL_658_DATA);

#endif

#ifdef DENALI_CTL_659_DATA

REGWR(DDR_BASE_ADDR+4*659,DENALI_CTL_659_DATA);

#endif

#ifdef DENALI_CTL_660_DATA

REGWR(DDR_BASE_ADDR+4*660,DENALI_CTL_660_DATA);

#endif

#ifdef DENALI_CTL_661_DATA

REGWR(DDR_BASE_ADDR+4*661,DENALI_CTL_661_DATA);

#endif

#ifdef DENALI_CTL_662_DATA

REGWR(DDR_BASE_ADDR+4*662,DENALI_CTL_662_DATA);

#endif

#ifdef DENALI_CTL_663_DATA

REGWR(DDR_BASE_ADDR+4*663,DENALI_CTL_663_DATA);

#endif

#ifdef DENALI_CTL_664_DATA

REGWR(DDR_BASE_ADDR+4*664,DENALI_CTL_664_DATA);

#endif

#ifdef DENALI_CTL_665_DATA

REGWR(DDR_BASE_ADDR+4*665,DENALI_CTL_665_DATA);

#endif

#ifdef DENALI_CTL_666_DATA

REGWR(DDR_BASE_ADDR+4*666,DENALI_CTL_666_DATA);

#endif

#ifdef DENALI_CTL_667_DATA

REGWR(DDR_BASE_ADDR+4*667,DENALI_CTL_667_DATA);

#endif

#ifdef DENALI_CTL_668_DATA

REGWR(DDR_BASE_ADDR+4*668,DENALI_CTL_668_DATA);

#endif

#ifdef DENALI_CTL_669_DATA

REGWR(DDR_BASE_ADDR+4*669,DENALI_CTL_669_DATA);

#endif

#ifdef DENALI_CTL_670_DATA

REGWR(DDR_BASE_ADDR+4*670,DENALI_CTL_670_DATA);

#endif

#ifdef DENALI_CTL_671_DATA

REGWR(DDR_BASE_ADDR+4*671,DENALI_CTL_671_DATA);

#endif

#ifdef DENALI_CTL_672_DATA

REGWR(DDR_BASE_ADDR+4*672,DENALI_CTL_672_DATA);

#endif

#ifdef DENALI_CTL_673_DATA

REGWR(DDR_BASE_ADDR+4*673,DENALI_CTL_673_DATA);

#endif

#ifdef DENALI_CTL_674_DATA

REGWR(DDR_BASE_ADDR+4*674,DENALI_CTL_674_DATA);

#endif

#ifdef DENALI_CTL_675_DATA

REGWR(DDR_BASE_ADDR+4*675,DENALI_CTL_675_DATA);

#endif

#ifdef DENALI_CTL_676_DATA

REGWR(DDR_BASE_ADDR+4*676,DENALI_CTL_676_DATA);

#endif

#ifdef DENALI_CTL_677_DATA

REGWR(DDR_BASE_ADDR+4*677,DENALI_CTL_677_DATA);

#endif

#ifdef DENALI_CTL_678_DATA

REGWR(DDR_BASE_ADDR+4*678,DENALI_CTL_678_DATA);

#endif

#ifdef DENALI_CTL_679_DATA

REGWR(DDR_BASE_ADDR+4*679,DENALI_CTL_679_DATA);

#endif

#ifdef DENALI_CTL_680_DATA

REGWR(DDR_BASE_ADDR+4*680,DENALI_CTL_680_DATA);

#endif

#ifdef DENALI_CTL_681_DATA

REGWR(DDR_BASE_ADDR+4*681,DENALI_CTL_681_DATA);

#endif

#ifdef DENALI_CTL_682_DATA

REGWR(DDR_BASE_ADDR+4*682,DENALI_CTL_682_DATA);

#endif

#ifdef DENALI_CTL_683_DATA

REGWR(DDR_BASE_ADDR+4*683,DENALI_CTL_683_DATA);

#endif

#ifdef DENALI_CTL_684_DATA

REGWR(DDR_BASE_ADDR+4*684,DENALI_CTL_684_DATA);

#endif

#ifdef DENALI_CTL_685_DATA

REGWR(DDR_BASE_ADDR+4*685,DENALI_CTL_685_DATA);

#endif

#ifdef DENALI_CTL_686_DATA

REGWR(DDR_BASE_ADDR+4*686,DENALI_CTL_686_DATA);

#endif

#ifdef DENALI_CTL_687_DATA

REGWR(DDR_BASE_ADDR+4*687,DENALI_CTL_687_DATA);

#endif

#ifdef DENALI_CTL_688_DATA

REGWR(DDR_BASE_ADDR+4*688,DENALI_CTL_688_DATA);

#endif

#ifdef DENALI_CTL_689_DATA
REGWR(DDR_BASE_ADDR+4*689,DENALI_CTL_689_DATA);
#endif

#ifdef DENALI_CTL_690_DATA
REGWR(DDR_BASE_ADDR+4*690,DENALI_CTL_690_DATA);
#endif

//==============================================================================

//  Make Memory Controller configuration register changes here.

//==============================================================================

    //  Memory Controller configuration changes for LPDDR3 memory
    uint32_t regdata;
    regdata = DENALI_CTL_653_DATA;
    regdata &=0xffff0000;
#ifdef _SIMU
    regdata |=0x00000308;
#else
    regdata |=0x0000030a;
#endif
    REGWR(DDR_BASE_ADDR+4*653,regdata);

    regdata = DENALI_CTL_679_DATA;
    regdata=regdata & 0xf8f8f8f8; //TDFI_PHY_WRDATA_F3 //TDFI_PHY_WRDATA_F2 //TDFI_PHY_WRDATA_F1 //TDFI_PHY_WRDATA_F0
    REGWR(DDR_BASE_ADDR+4*679,regdata);

    //  ODT Control .. disable ODT
    regdata = DENALI_CTL_254_DATA;
  //  regdata =regdata & 0x00ffffff;                    //MR11_DATA was 0x3
    regdata =regdata & 0x00ffffff;                    //1/2 Rzq setting ODT
    REGWR(DDR_BASE_ADDR+4*254,regdata);

    //  twrlat dram we cmd to data?
    //  regdata = DENALI_CTL_48_DATA;
    //  regdata[14:8] = 7'h0A;                    //WRLAT_F0 was 0x8
    //  REGWR(DDR_BASE_ADDR+4*48,regdata);
    //  Keep the init freq same as boot freq.

    regdata = DENALI_CTL_375_DATA;
    regdata &=0xffffe0ff;
    // regdata |=0x00000f00;
    // regdata =regdata | 0x00000000;             //w2w_samecs_dly

    REGWR(DDR_BASE_ADDR+4*375,regdata);

    regdata = DENALI_CTL_373_DATA;
    regdata &=0xe0ffffff;
    // regdata =regdata | 0x00000000;             //r2r_samecs_dly
    REGWR(DDR_BASE_ADDR+4*373,regdata);

    regdata = DENALI_CTL_374_DATA;
    regdata &=0xfffffff0;
    regdata =regdata | 0x00000007;             //r2w_samecs_dly
    REGWR(DDR_BASE_ADDR+4*374,regdata);


        regdata = DENALI_CTL_27_DATA;
        regdata &=0xfeffffff;
        regdata =regdata | 0x01000000;             //disable auto read during initialization
        REGWR(DDR_BASE_ADDR+4*27,regdata);



        regdata=DENALI_CTL_161_DATA;
        regdata|=0x01000000;
        REGWR(DDR_BASE_ADDR+4*161,regdata);

        regdata=DENALI_CTL_327_DATA;
        regdata&=0xfffeffff;
        REGWR(DDR_BASE_ADDR+4*327,regdata);

        regdata=REGREAD(DDR_BASE_ADDR);
        regdata|=0x1000000;
        REGWR(DDR_BASE_ADDR,regdata);

     while(1) {
         usleep(50);
         regdata=REGREAD(DDR_BASE_ADDR+4*338);
         if(regdata & 0x200)
           break;
     }

       Read_Gate_training();
}