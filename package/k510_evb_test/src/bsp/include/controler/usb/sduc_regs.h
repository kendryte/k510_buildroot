/**********************************************************************
 * Copyright (C) 2014-2017 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sduc_regs.h
 * Header file describing USB registers for SD USB controllers
 *
 ***********************************************************************/

#ifndef _SDUC_REGS_
#define _SDUC_REGS_

/** Decoding naming convenction
*  UCRM - mask used for HOST and Device mode
*  UCRO - offset used for HOST and Device mode
*  UCRV - value used for HOST and Device mode
*  UCDRM - mask can be used only for Device mode
*  UCDRO - offset can be used only for Device mode
*  UCDRV - value  can be used only for Device mode
*  UCHRM - mask can be used only for Host and OTG mode
*  UCHRO - offset can be used only for Host and OTG mode
*  UCHRV - value can be used only for Host and OTG mode
 */
/*************************************************************************************************************/

/* Bit definitions for USB special function registers */
/* Register lpmctrll, lpmctrlh  */
#define UCRM_LPMCTRLLL_HIRD         0xF0 /*Host Initiated Resume Duration mask*/
#define UCRO_LPMCTRLLL_HIRD         0x04 /*Host Initiated Resume Duration offset*/
#define UCHRM_LPMCTRLLL_BLINKST     0x0F /*BLinkState register*/
#define UCRM_LPMCTRLLH_BREMOTEWAKEUP 0x01 /*LPM bRemoteWakeup register*/
#define UCDRM_LPMCTRLLH_LPMNYET     0x80 /*It reflects value of the lpmnyet bit located in the usbcs(1) register. Only peripheral*/

/*  Register ep0cs(hcep0cs) */
#define UCHM_EP0CS_HCLPM        0x80 /* write only bit, host mode */
#define UCHM_EP0CS_HCSETTOGGLE  0x40 /* Set toggle bit */
#define UCHM_EP0CS_HCCLRTOGGLE  0x20 /* Clear toggle bit */
#define UCHM_EP0CS_HCSET        0x10 /*mask for bit hcset for register  hcoutxcs only in host mode*/
#define UCDM_EP0CS_CHGSET   0x80 /* Setup Buffer contents was changed */
#define UCDM_EP0CS_DSTALL   0x10 /* Send stall in the data stage*/
#define UCDM_EP0CS_HSNAK    0x02 /* If 0 the controller send status stage */
#define UCDM_EP0CS_STALL    0x01 /* Endpoint 0 stall bit*/
#define UCM_EP0CS_RXBSY_MSK 0x08 /* endpoint busy bit for transmitting data */
#define UCM_EP0CS_TXBSY_MSK 0x04 /* endpoint busy bit receiving data */

/** bit definitions for outxcs, hcinxcs registers */
#define UCM_CS_ERR  0x01 /* Error bit */
#define UCM_CS_BUSY 0x02 /* Busy bit */
#define UCM_CS_NPAK 0x0C /* Npak bits mask */
#define UCO_CS_NPAK 0x02 /* Npak bits offset */
#define UCM_CS_AUTO 0x10 /**< Auto-OUT bit, device mode */

/**< definitions for outxcon, hcinxcon registers */
#define UCM_CON_TYPE_ISOC   0x04 /*Type1, type0 = "01" - isochronous endpoint*/
#define UCM_CON_TYPE_BULK   0x08 /*Type1, type0 = "10" - bulk endpoint*/
#define UCM_CON_TYPE_INT    0x0C /*Type1, type0 = "11" - interrupt endpoint*/
#define UCM_CON_ISOD_AUTO   0x30
#define UCM_CON_1_ISOD      0x00 /*hcinisod1, hcinisod0="00" - 1 ISO packet per microframe*/
#define UCM_CON_2_ISOD      0x10 /*hcinisod1, hcinisod0="01" - 2 ISO packets per microframe*/
#define UCM_CON_3_ISOD      0x20 /*hcinisod1, hcinisod0="10" - 3 ISO packets per microframe*/
#define UCDM_CON_STALL      0x40 /*endpoint stall bit.*/
#define UCM_CON_VAL         0x80 /*endpoint valid bit. Disable(0) or Enable(1) endpoint*/

#define UCM_CON_TYPE        0x0c /*mask for bits type1 and type2 */
#define UCM_CON_ISOD        0x30 /*mask for bits  isod1 nad isod2*/

#define UCM_CON_BUF_SINGLE  0x00
#define UCM_CON_BUF_DOUBLE  0x01
#define UCM_CON_BUF_TRIPLE  0x02
#define UCM_CON_BUF_QUAD    0x03
#define UCM_CON_BUF         0x03

/* bit definitions for usbirq, hcusbirq registers **/
#define UCM_USBIR_SOF       0x02 /* Start-of-frame */
#define UCM_USBIR_SUSP      0x08 /* USB suspend interrupt request*/
#define UCM_USBIR_URES      0x10 /* USB reset interrupt request*/
#define UCM_USBIR_HSPPED    0x20 /* USB high-speed mode interrupt request*/

#define UCDM_USBIR_SUDAV    0x01 /* SETUP data valid interrupt request */
#define UCDM_USBIR_SUTOK    0x04 /* SETUP token interrupt request*/
#define UCDM_USBIR_LPMIR    0x80 /* Link Power Management interrupt request*/
/* bit definitions for  usbien, hcusbien registers **/
#define UCM_USBIEN_SOFIE    0x02 /* Start-of-frame interrupt enable*/
#define UCM_USBIEN_URESIE   0x10 /* USB reset interrupt enable*/
#define UCM_USBIEN_HSPIE    0x20 /* USB high speed mode interrupt enable*/

#define UCDM_USBIEN_SUDAVIE 0x01 /* SETUP data valid interrupt enable*/
#define UCDM_USBIEN_SUTOKIE 0x04 /* SETUP token interrupt enable */
#define UCDM_USBIEN_SUSPIE  0x08 /* USB suspend interrupt enable */
#define UCDM_USBIEN_LPMIE   0x80 /* Link Power Management interrupt request */

/* bit definitions for endprst, hcendprst registers*/
#define UCM_ENDPRST_EP      0x0f /* Endpoint number mask */
#define UCM_ENDPRST_IO_TX   0x10 /*  Direction bit for transmitting data */
#define UCM_ENDPRST_TOGRST  0x20 /* Toggle reset bit */
#define UCM_ENDPRST_FIFORST 0x40 /* Fifo reset bit */
#define UCM_ENDPRST_TOGSETQ 0x80 /*  Read access: Data toggle value, Write access: Toggle set bit */

/* bit definitions for usbcs, hcusbcs registers **/
#define UCHM_USBCS_LSMODE   0x01  /* 1 - Peripheral device works in LS mode */
#define UCDM_USBCS_LPMNYET  0x02 /* Send NYET handshake for the LPM transaction*/
#define UCDM_USBCS_SLFPWR   0x04 /* Self powered device status bit*/
#define UCDM_USBCS_RWAKEN   0x08 /* Remote wakeup enable bit */
#define UCDM_USBCS_ENUM     0x08 /* Enumeration bit */
#define UCM_USBCS_SIGRSUME  0x20 /* Remote wakeup bit */
#define UCM_USBCS_DISCON    0x40 /* Software disconnect bit */
#define UCM_USBCS_WAKESRC   0x80 /* Wakeup source*/

/* bit definitions for clkgate, hcclkgate registers*/
#define UCH_CLKGATE_WUIDEN_MSK   0x01 /* Wakeup ID enable */
#define UCH_CLKGATE_WUDPEN_MSK   0x02 /* Wakeup D+ enable */
#define UCH_CLKGATE_WUVBUSEN_MSK 0x04 /* Wakeup VBUS enable */

/* bit definitions for fifoctrl, hcfifoctrl registers*/
#define UCM_FIFOCTRL_EP         0x0f /* Endpoint number mask */
#define UCM_FIFOCTRL_IO_TX      0x10 /* Direction bit for transmitting data */
#define UCM_FIFOCTRL_FIFOAUTO   0x20 /* FIFO auto bit */
#define UCM_FIFOCTRL_FIFOCMIT   0x40 /* FIFO commit bit */
#define UCM_FIFOCTRL_FIFOACC    0x80 /*  FIFO access bit */

/*register otgirq  - describe of mask*/
#define UCHM_OTGIRQ_IDLEIRQ     0x01 /*Interrupt request on OTG FSM entering a_idle or b_idle state*/
#define UCHM_OTGIRQ_SRPDETIRQ   0x02 /*Interrupt request on SRP detection */
#define UCHM_OTGIRQ_CONIRQ      0x04 /*Interrupt request on a a_host or b_host state entering*/
#define UCHM_OTGIRQ_LOCSOFIRQ   0x04 /*Interrupt request on a a_host or b_host state entering*/
#define UCHM_OTGIRQ_VBUSERRIRQ  0x08 /*Interrupt request on a_vbus_err state entering*/
#define UCHM_OTGIRQ_PERIPHIRQ   0x10 /*Interrupt request on a_peripheral or b_peripheral state entering*/
#define UCHM_OTGIRQ_IDCHANGEIRQ 0x20 /*Interrupt request on ID change*/
#define UCHM_OTGIRQ_HOSTDISCON  0x40 /*Interrupt request on host disconnect*/
#define UCHM_OTGIRQ_BSE0SRPIRQ  0x80 /*Interrupt request on B SE0 SRP*/

/*register otgctrl - describe of mask*/
#define UCHM_OTGCTRL_BUSREQ         0x01 /*Bit used to start or end the session*/
#define UCHM_OTGCTRL_ABUSDROP       0x02 /*This bit controls OTG FSM. It forces the bus power-down.*/
#define UCHM_OTGCTRL_ASETBHNPEN     0x04 /*This bit should be set by microcontroller after receiving acknowledge that
                                        B-device has set bhnpen bit.*/
#define UCHM_OTGCTRL_BHNPEN         0x08   /*This bit should be set by microcontroller after receiving SetFeature(b_hnp_enable)
                                        command. It is cleared on the bus reset and end of the session.*/
#define UCHM_OTGCTRL_SRPVBUSDETEN   0x10  /*SRP VBUS pulse detection enable.*/
#define UCHM_OTGCTRL_SRPDATDETEN    0x20  /*SRP Data pulse detection enable*/
#define UCHM_OTGCTRL_FORCEBCONN     0x80  /*Bit used for the core testing purpose. */


/*register otgstatus - describe of mask*/
#define UCHM_OTGCTRL_BSE0SRP    0x01
#define UCHM_OTGSTATUS_CONN     0x02 /*Device connection to USB line has been detected*/
#define UCHM_OTGSTATUS_BSESSVAL 0x04
#define UCHM_OTGSTATUS_ASESSVAL 0x08
#define UCHM_OTGSTATUS_BSESSEND 0x10
#define UCHM_OTGSTATUS_AVBUSVAL 0x20
#define UCHM_OTGSTATUS_ID       0x40 /*Type of plug: 0' - Mini-A, '1' - Mini-B*/

/*below macros describes error code for hcinxerr/hcouterr register */
#define UCHM_ERR_TYPE       0x1C /*mask for bits errtyp*/
#define UCHM_ERR_COUNT      0x03 /*mask for bits errcount*/
#define UCHM_ERR_RESEND     0x40
#define UCHM_ERR_UNDERRIEN  0x80 /*Packet shorter than maximal*/

#define UCHV_ERR_NONE                  0 /*000 - reserved (no error)*/
#define UCHV_ERR_CRC                   1 /*001 - CRC error*/
#define UCHV_ERR_DATA_TOGGLE_MISMATCH  2 /*010 - data toggle mismatch*/
#define UCHV_ERR_STALL                 3 /*011 - endpoint sent STALL handshake*/
#define UCHV_ERR_TIMEOUT               4 /*100 - no endpoint handshake (timeout)*/
#define UCHV_ERR_PID                   5 /*101 - PID error (pid check=error or unknown PID)*/
#define UCHV_ERR_TOO_LONG_PACKET       6 /*110 - Data Overrun (too long packet - babble)*/
#define UCHV_ERR_DATA_UNDERRUN         7 /*111 - Data Underrun (packet shorter than MaxPacketSize)*/

/*Below macro describe speedctrl register field*/
#define UCM_SPEEDCTRL_LS        0x01 /*Host works in Low Speed*/
#define UCM_SPEEDCTRL_FS        0x02 /*Host works in Full Speed*/
#define UCM_SPEEDCTRL_HS        0x04 /*Host works in High Speed*/
#define UCM_SPEEDCTRL_HSDISABLE 0x80 /*If set to 1 then CUSB Controller works only in FS/LS*/

/*bit definition for portctrl register (USB spec 7.1.20) */
#define UCRV_PORTCTRL_TESTM_TEST_J       0x01 /*Test_J*/
#define UCRV_PORTCTRL_TESTM_TEST_K       0x02 /*Test_K*/
#define UCRV_PORTCTRL_TESTM_TEST_SE0_NAK 0x04 /*Test_SE0_NAK*/
#define UCRV_PORTCTRL_TESTM_TEST_PACKET  0x08 /*Test_Packet*/
#define UCRV_PORTCTRL_TESTM_TEST_FORCE_ENABLE 0x16 /*Test_Force_Enable*/
#define UCRM_PORTCTRL_PORRST 0x20 /*Port Reset*/
#define UCRM_PORTCTRL_HCPORTCTRL 0xC0 /*USB reset Length control*/
#define UCRV_PORTCTRL_HCPORTCTRL_10MS  0x00 /*10 ms USB reset (testing purpose)*/
#define UCRV_PORTCTRL_HCPORTCTRL_55MS  0x40 /*55 ms USB reset (default state)*/
#define UCRV_PORTCTRL_HCPORTCTRL_1_6MS 0x80 /*1,6 ms USB reset (testing purpose)*/

/* bit definition for otg2ctrl register*/
#define UCRM_OTG2CTRL_OTG2EN     0x01 /*OTG v2.0 enable bit*/
#define UCRM_OTG2CTRL_ADP_CHANGE 0x02

/*bit definition for adpbcctr0, adpbcctr1 and adpbcctr2 */
#define UCRM_ADPBCCTRL0_ADP_EN                  0x01 /*ADP Feature Enable*/
#define UCRM_ADPBCCTRL0_ADP_PROBE_EN            0x02 /*Enable probe mode of the ADP*/
#define UCRM_ADPBCCTRL0_ADP_SENSE_EN            0x04 /*Enable probe mode of the ADP*/
#define UCRM_ADPBCCTRL0_ADP_SINK_CURRENT_EN     0x08 /*VBUS is discharged to ground*/
#define UCRM_ADPBCCTRL0_ADP_SOURCE_CURRENT_EN   0x10 /*VBUS is charged to the probe threshold*/
#define UCRM_ADPBCCTRL0_R3SWITCH                0x20 /*VBUS voltage divider enable*/
#define UCRM_ADPBCCTRL0_R3SWITCH_AUTOSET        0x40 /*r3switch auto set enable*/

#define UCRM_ADPBCCTRL1_BC_EN           0x01 /*Battery Charging Circuits Master Enable*/
#define UCRM_ADPBCCTRL1_IDM_SINK_EN     0x02 /*Current Sink on DM Enable*/
#define UCRM_ADPBCCTRL1_IDP_SINK_EN     0x04 /*Current sink on DP Enable*/
#define UCRM_ADPBCCTRL1_IDP_SRC_EN      0x08 /*Current source on DP ENABLE*/
#define UCRM_ADPBCCTRL1_VDM_SRC_EN      0x10 /*Voltage Source on DM Enable*/
#define UCRM_ADPBCCTRL1_VDP_SRC_EN      0x20 /*Voltage Source on DP Enable*/

#define UCRM_ADPBCCTRL2_DM_VDAT_REF_COMPP_EN    0x01 /*DM to VDAT_REF Comparator Enable*/
#define UCRM_ADPBCCTRL2_DM_VLGC_COMP_EN         0x02 /*DM to VLGC Comparator Enable*/
#define UCRM_ADPBCCTRL2_DP_VDAT_REF_COMP_EN     0x04 /*DP to VDAT_REF Comparator Enable*/
#define UCRM_ADPBCCTRL2_RID_FLOAT_COMP_EN       0x08 /*RID Float Comparator Enable*/
#define UCRM_ADPBCCTRL2_RID_NONFLOAT_COMP_EN    0x10 /*RID Non-Float Comparator Enable*/
#define UCRM_ADPBCCTRL2_BC_DMPULLDOWN           0x20 /*BC dmpulldown Enable*/
#define UCRM_ADPBCCTRL2_BC_DPPULLDOWN           0x40 /*BC dppulldown Enable*/
#define UCRM_ADPBCCTRL2_BC_PULLDOWNCTRL         0x80 /*BC pulldown control enable*/


/*bit definition for  adpbc1ien and  adpbc1irq*/
#define UCRM_ADPBC1IRQ_PROBE_RISE           0x01 /*Probe valid comparator rise interrupt enable*/
#define UCRM_ADPBC1IRQ_SENSE_RISE           0x02 /*Sense valid comparator rise interrupt enable*/
#define UCRM_ADPBC1IRQ_OTGSESSVALID_RISE    0x04 /*Otgsessvalid (bvalid0 valid comparator rise interrupt*/
#define UCRM_ADPBC1IRQ_SESSEND_RISE         0x08 /*Session end valid comparator rise interrupt enable*/
#define UCRM_ADPBC1IRQ_DM_VDAT_REF_RISE     0x10 /*dm_vdat_ref comparator rise interrupt enable*/
#define UCRM_ADPBC1IRQ_DP_VDAT_REF_RISE     0x20 /*dp_vdat_ref rise comparator rise interrupt enable*/
#define UCRM_ADPBC1IRQ_DCD_COMP_RISE        0x40 /*DCD_comparator_rise comparator rise interrupt enable*/
#define UCRM_ADPBC1IRQ_DCD_COMP_FALL        0x80 /*DCD_comparator_fall comparator rise interrupt enable*/

/*bit definition for adpbc2ien and adpbc2irq */
#define UCRV_ADPBC2IRQ_RID_A_RISE           0x01 /*clear adpbc_rid_a_rise bit */
#define UCRV_ADPBC2IRQ_RID_B_RISE           0x02 /*clear rid_b_rise bit*/
#define UCRV_ADPBC2IRQ_RID_C_RISE           0x04 /*clear rid_c_rise bit*/
#define UCRV_ADPBC2IRQ_RID_GND_RISE         0x08 /*clear rid_gnd_rise bit*/
#define UCRV_ADPBC2IRQ_RID_FLOAT_RISE       0x10 /*clear rid_float_rise bit*/
#define UCRV_ADPBC2IRQ_RID_FLOAT_FALL       0x20 /*clear rid_float_fall bit*/
#define UCRV_ADPBC2IRQ_DM_VLGC_COMP_RISE    0x40 /*clear dm_vlgc_comp_rise bit*/

/*bit definition for adpbc0status, adpbc1status and adpbc2status */
#define UCRM_ADPBCSTATUS0_DP_VDAT_REF_COMP_STS  0x01 /*dpd_vdat comparator status*/
#define UCRM_ADPBCSTATUS0_DM_VLGC_COMP_STS      0x02 /*dm_vlgc_comparator status*/
#define UCRM_ADPBCSTATUS0_DM_VDAT_REF_COMP_STS  0x04 /*dm_vdat comparator status*/
#define UCRM_ADPBCSTATUS0_DCD_COMP_STS          0x08 /*DCD comparator status*/
#define UCRM_ADPBCSTATUS0_OTGSESSVALID          0x10 /*otgsessvalid comparator status*/
#define UCRM_ADPBCSTATUS0_ADP_PROBE_ANA         0x20 /*probe comparator status*/
#define UCRM_ADPBCSTATUS0_ADP_SENSE_ANA         0x40 /*sense comparator status*/
#define UCRM_ADPBCSTATUS0_SESSEND               0x80 /*sessend comparator status*/

#define UCRM_ADPBCSTATUS1_RID_FLOAT_COMP_STS    0x01 /*rid_float comparator status*/
#define UCRM_ADPBCSTATUS1_RID_GND_COMP_STS      0x02 /*rid_gnd comparator status*/
#define UCRM_ADPBCSTATUS1_RID_C_COMP_STS        0x04 /*rid_c comparator status*/
#define UCRM_ADPBCSTATUS1_RID_B_COMP_STS        0x08 /*rid_b comparator status*/
#define UCRM_ADPBCSTATUS1_RID_A_COMP_STS        0x10 /*rid_a comparator status*/
#define UCRM_ADPBCSTATUS1_LINESTATE0            0x40 /*Linestate[0] status*/
#define UCRM_ADPBCSTATUS1_LINESTATE1            0x80 /*Linestate[1] status*/

#define UCRM_ADPBCSTATUS2_RID_FLOAT 0x01 /*rid_float status fixed*/
#define UCRM_ADPBCSTATUS2_RID_GND   0x02 /*rid_gnd status fixed*/
#define UCRM_ADPBCSTATUS2_RID_C     0x04 /*rid_c status fixed*/
#define UCRM_ADPBCSTATUS2_RID_B     0x08 /*rid_b status fixed*/
#define UCRM_ADPBCSTATUS2_RID_A     0x10 /*rid_a status fixed*/
#define UCRM_WA1_CNT 0x0F /*PHY workaround 1 counter register*/

#define UCRM_ENDIAN_SFR_CS_LENDIAN 0x01 /*set Little Endian order for SFR*/
#define UCRM_ENDIAN_SFR_CS_BENDIAN 0x02 /*set Big endian order for SFR*/
#define UCRM_ENDIAN_SFR_CS_ENDIAN  0x80 /*Current endian order*/
/*---------------------------------------------------------------------------*/

typedef struct __attribute__((packed)) {
    uint8_t ep0Rxbc;        /*address 0x00*/
    uint8_t ep0Txbc;        /*address 0x01*/
    uint8_t ep0cs;          /*address 0x02*/
    int8_t reserved0;       /*address 0x03*/
    uint8_t lpmctrll;       /*address 0x04*/
    uint8_t lpmctrlh;       /*address 0x04*/
    uint8_t lpmclock;
    uint8_t ep0fifoctrl;
    struct ep {             /*address 0x08*/
        uint16_t rxbc;        //outbc (hcinbc)
        uint8_t rxcon;
        uint8_t rxcs;
        uint16_t txbc;         //inbc  (hcoutbc
        uint8_t txcon;
        uint8_t txcs;
    } ep[15];
    uint8_t reserved1[4];
    uint32_t fifodat[15];   /*address 0x84*/
    uint8_t ep0ctrl;        /*address 0xC0*/
    uint8_t tx0err;         /*address 0xC1*/
    uint8_t reserved2;
    uint8_t rx0err;         /*address 0xC3*/
    struct epExt {
        uint8_t txctrl;
        uint8_t txerr;
        uint8_t rxctrl;
        uint8_t rxerr;
    } epExt[15];
    uint8_t ep0datatx[64]; /*address 0x100*/
    uint8_t ep0datarx[64]; /*address 0x140*/
    uint8_t setupdat[8];    /*address 0x180*/
    uint16_t txirq;         /*address 0x188*/
    uint16_t rxirq;         /*address 0x18A*/
    uint8_t usbirq;         /*address 0x18C*/
    uint8_t reserved4;
    uint16_t rxpngirq;      /*address 0x18E*/
    uint16_t txfullirq;     /*address 0x190*/
    uint16_t rxemptirq;     /*address 0x192*/
    uint16_t txien;         /*address 0x194*/
    uint16_t rxien;         /*address 0x196*/
    uint8_t usbien;         /*address 0x198*/
    uint8_t reserved6;
    uint16_t rxpngien;      /*address 0x19A*/
    uint16_t txfullien;     /*address 0x19C*/
    uint16_t rxemptien;     /*address 0x19E*/
    uint8_t usbivect;       /*address 0x1A0*/
    uint8_t fifoivect;      /*address 0x1A1*/
    uint8_t endprst;        /*address 0x1A2*/
    uint8_t usbcs;          /*address 0x1A3*/
    uint16_t frmnr;         /*address 0x1A4*/
    uint8_t fnaddr;         /*address 0x1A6*/
    uint8_t clkgate;        /*address 0x1A7*/
    uint8_t fifoctrl;       /*address 0x1A8*/
    uint8_t speedctrl;      /*address 0x1A9*/
    uint8_t reserved8[1];   /*address 0x1AA*/
    uint8_t portctrl;       /*address 0x1AB*/
    uint16_t hcfrmnr;       /*address 0x1AC*/
    uint16_t hcfrmremain;   /*address 0x1AE*/
    uint8_t reserved9[4];   /*address 0x1B0*/
    uint16_t rxerrirq;      /*address 0x1B4*/
    uint16_t txerrirq;      /*address 0x1B6*/
    uint16_t rxerrien;      /*address 0x1B8*/
    uint16_t txerrien;      /*address 0x1BA*/
    /*OTG extension*/
    uint8_t otgirq;         /*address 0x1BC*/
    uint8_t otgstate;       /*address 0x1BD*/
    uint8_t otgctrl;        /*address 0x1BE*/
    uint8_t otgstatus;      /*address 0x1BF*/
    uint8_t otgien;         /*address 0x1C0*/
    uint8_t taaidlbdis;     /*address 0x1C1*/
    uint8_t tawaitbcon;     /*address 0x1C2*/
    uint8_t tbvbuspls;      /*address 0x1C3*/
    uint8_t otg2ctrl;       /*address 0x1C4*/
    uint8_t reserved10[2];  /*address 0x1C5*/
    uint8_t tbvbusdispls;   /*address 0x1C7*/
    uint8_t traddr;         /*address 0x1C8*/
    uint8_t trwdata;        /*address 0x1C9*/
    uint8_t trrdata;        /*address 0x1CA*/
    uint8_t trctrl;         /*address 0x1CB*/
    uint16_t isoautoarm;    /*address 0x1CC*/
    uint8_t adpbc1ien;      /*address 0x1CE*/
    uint8_t adpbc2ien;      /*address 0x1CF*/
    uint8_t adpbcctr0;      /*address 0x1D0*/
    uint8_t adpbcctr1;      /*address 0x1D1*/
    uint8_t adpbcctr2;      /*address 0x1D2*/
    uint8_t adpbc1irq;      /*address 0x1D3*/
    uint8_t adpbc0status;   /*address 0x1D4*/
    uint8_t adpbc1status;   /*address 0x1D5*/
    uint8_t adpbc2status;   /*address 0x1D6*/
    uint8_t adpbc2irq;      /*address 0x1D7*/
    uint16_t isodctrl;      /*address 0x1D8*/
    uint8_t reserved11[2];
    uint16_t isoautodump;   /*address 0x1DC*/
    uint8_t reserved12[2];
    uint8_t ep0maxpack;     /*address 0x1E0*/
    uint8_t reserved13;
    uint16_t rxmaxpack[15]; /*address 0x1E2*/
    uint32_t rxsoftimer[16]; /*address 0x200 to  0x23F*/
    uint32_t txsoftimer[16]; /*address 0x240 to  0x27F*/
    uint8_t reserved14[132];
    struct rxstaddr {       /*address 0x304*/
        uint16_t addr;
        uint16_t reserved;
    } rxstaddr[15];
    uint8_t reserved15[4];
    struct txstaddr {       /*address 0x344*/
        uint16_t addr;
        uint16_t reserved;
    } txstaddr[15];
    int8_t reserved16[64];
    /*The Microprocessor control*/
    uint8_t cpuctrl;         /*address 0x3C0*/
    int8_t reserved17[15];
    /*The debug counters and workarounds*/
    uint8_t debug_rx_bcl;    /*address 0x3D0*/
    uint8_t debug_rx_bch;    /*address 0x3D1*/
    uint8_t debug_rx_status; /*address 0x3D2*/
    uint8_t debug_irq;       /*address 0x3D3*/
    uint8_t debug_tx_bcl;    /*address 0x3D4*/
    uint8_t debug_tx_bch;    /*address 0x3D5*/
    uint8_t debug_tx_status; /*address 0x3D6*/
    uint8_t debug_ien;       /*address 0x3D7*/
    uint8_t phywa_en;        /*address 0x3D8*/
    /*endian*/
    uint8_t wa1_cnt;       /*address 0x3D9*/
    int8_t reserved18[2];  /*address 0x3DA*/
    uint8_t endian_sfr_cs; /*address 0x3DC*/
    int8_t reserved19[2];    /*address 0x3DD*/
    uint8_t endian_sfr_s;  /*address 0x3DF*/
    int8_t reserved20[2];    /*address 0x3E0*/
    uint16_t txmaxpack[15]; /*address 0x3E2*/
} UCRegs ;

/*************************************************************/
#endif /*end _SDUC_REGS_*/

