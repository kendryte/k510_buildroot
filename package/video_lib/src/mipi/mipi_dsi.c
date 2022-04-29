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

/**
 * @brief 
 * 
 */
static void aml550_1v8_power_en(void)
{
    //no io control of 1v8 on EVB, just use a jumper  

}
/*
*
*/
static void aml550_2v8_power_en(void)
{
    //no io control of 2v8 on EVB, just use a jumper    
}
/*
*
*/
void Release_aml550_fpga_reset()
{
    //on EVB, lcd reset is controlled by io expander PCAL6418 P0_3.
    //wait for io expander IC driver ready
    //add code here !!!
    //pcal6416_mipi_dsi_reset(1);    
}
/*
*
*/
static void Active_aml550_fpga_reset(void)
{
    //on EVB, lcd reset is controlled by io expander PCAL6418 P0_3.
    //wait for io expander IC driver ready
    //add code here !!!
    //pcal6416_mipi_dsi_reset(0);
}
/*
*
*/
void dsi_power_en(void)
{
    //on EVB, need to enable dsi daughter board 5v power, io expander P0_5
    //wait for io expander IC driver ready
    //add code here !!!

    //pcal6416_gpio_dsi_en(1);

}
/*
*
*/
void aml550_power_on_seq(void)
{
    //pcal6416_init(0);

    dsi_power_en();
    sleep(1);

    printf("aml550_power_on_seq start\n");
    aml550_1v8_power_en();
    sleep(1);
    aml550_2v8_power_en();
    sleep(1);
    Release_aml550_fpga_reset();
    sleep(1);
    Active_aml550_fpga_reset();
    sleep(1);
    Release_aml550_fpga_reset();
    sleep(1);
//   aml550_22v_power_en();
    sleep(1);

    printf("aml550_power_on_seq end\n");    
}
/*
*
*/
void aml550_22v_power_en(void)
{
     //on EVB, lcd reset is controlled by io expander PCAL6418 P1_4.
    //wait for io expander IC driver ready
    //add code here !!!
    //pcal6416_mipi_dsi_io(1);
}