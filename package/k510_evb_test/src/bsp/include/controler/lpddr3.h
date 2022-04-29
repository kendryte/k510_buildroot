
/* ****************************************************************
 *        CADENCE                    Copyright (c) 2001-2020      *
 *                                   Cadence Design Systems, Inc. *
 *                                   All rights reserved.         *
 ******************************************************************
 *  The values calculated from this script are meant to be        *
 *  representative programmings.   The values may not reflect the *
 *  actual required programming for production use.   Please      *
 *  closely review all programmed values for technical accuracy   *
 *  before use in production parts.                               *
 ******************************************************************
 *
 *   Module:         regconfig.h
 *   Documentation:  Register programming header file
 *
 ******************************************************************
 ******************************************************************
 * WARNING:  This file was automatically generated.  Manual
 * editing may result in undetermined behavior.
 ******************************************************************
 ******************************************************************/
// REL: canaan.beijing.n3-Maix2_DDRC__20200224
#define 	      DDR_MEMC_BASE_ADDR 0x98000000
#define               DDR_BASE_ADDR  0x98000000
#define TB_LPDDR3
#define MBPS_2133


#define DDRC_REGS_BASE 0x98000000
#define DDR_PHY_REGS_OFF 0x1000

#define SYSCTL_BASE_ADDR    0x97000000

#define MEM_CTL_DFS_CFG     SYSCTL_BASE_ADDR+0x116C

#define MEM_CTL_CMD_FIFO    SYSCTL_BASE_ADDR+0x1160

#define MEM_CTL_CLK_CFG     SYSCTL_BASE_ADDR+0x1168

#define PLL3_CFG0           SYSCTL_BASE_ADDR+0x0030

#define PLL3_CTL            SYSCTL_BASE_ADDR+0x0038

#define PLL3_STAT           SYSCTL_BASE_ADDR+0x003c

#define INT2_RAW            SYSCTL_BASE_ADDR+0x00b0

#define MCTL_PWR_CTL        SYSCTL_BASE_ADDR+0x30f0

#define MCTL_PWR_STAT       SYSCTL_BASE_ADDR+0x30f8

#define PLL3_CFG1           SYSCTL_BASE_ADDR+0x0034

#define MCTL_RST_CTL        SYSCTL_BASE_ADDR+0x20f4

#define MCTL_RST_TIM        SYSCTL_BASE_ADDR+0x20f0

#define PHY_RST_CTL         SYSCTL_BASE_ADDR+0x2198

//mailbox control

#define MAILBOX_BASE 0x970E0000

#define DDR_WCOBUF  MAILBOX_BASE +0xf0

#define DDR_INIT_COMPLETE  MAILBOX_BASE +0x164

#define DDR_BASE_ADDR 0x98000000

#define DENALI_CTL_245 245
#define DENALI_CTL_339 339
#define DENALI_CTL_346 346
#define DENALI_CTL_212 212
#define DENALI_CTL_213 213
#define DENALI_CTL_214 214
#define DENALI_CTL_215 215

#define DENALI_CTL_190 190



#ifdef _SIMU
#define               DENALI_CTL_00_DATA 0x00002020 //
#define               DENALI_CTL_01_DATA 0x00000007 //
#define               DENALI_CTL_02_DATA 0x00000000 //
#define               DENALI_CTL_03_DATA 0x00000000 //
#define               DENALI_CTL_04_DATA 0x00000000 //
#define               DENALI_CTL_05_DATA 0x00000000 //
#define               DENALI_CTL_06_DATA 0x00000000 //
#define               DENALI_CTL_07_DATA 0x00000000 //
#define               DENALI_CTL_08_DATA 0x00000000 //
#define               DENALI_CTL_09_DATA 0x00000000 //
#define               DENALI_CTL_10_DATA 0x00000000 //
#define               DENALI_CTL_11_DATA 0x00000000 //
#define               DENALI_CTL_12_DATA 0x0000002a //
#define               DENALI_CTL_13_DATA 0x00000054 //
#define               DENALI_CTL_14_DATA 0x00000001 //
#define               DENALI_CTL_15_DATA 0x0000002a //
#define               DENALI_CTL_16_DATA 0x00000028 //
#define               DENALI_CTL_17_DATA 0x00000050 //
#define               DENALI_CTL_18_DATA 0x00000001 //
#define               DENALI_CTL_19_DATA 0x00000028 //
#define               DENALI_CTL_20_DATA 0x0000002a //
#define               DENALI_CTL_21_DATA 0x00000054 //
#define               DENALI_CTL_22_DATA 0x00000001 //
#define               DENALI_CTL_23_DATA 0x0000002a //
#define               DENALI_CTL_24_DATA 0x0000002a //
#define               DENALI_CTL_25_DATA 0x00000054 //
#define               DENALI_CTL_26_DATA 0x00000001 //
#define               DENALI_CTL_27_DATA 0x0000002a //
#define               DENALI_CTL_28_DATA 0x00000000 //
#define               DENALI_CTL_29_DATA 0x00001001 //
#define               DENALI_CTL_30_DATA 0x02010000 //
#define               DENALI_CTL_31_DATA 0x02010003 //
#define               DENALI_CTL_32_DATA 0x00000003 //
#define               DENALI_CTL_33_DATA 0x00000054 //
#define               DENALI_CTL_34_DATA 0x000000d1 //
#define               DENALI_CTL_35_DATA 0x00000000 //
#define               DENALI_CTL_36_DATA 0x00000000 //
#define               DENALI_CTL_37_DATA 0x00000000 //
#define               DENALI_CTL_38_DATA 0x00000000 //
#define               DENALI_CTL_39_DATA 0x00020200 //
#define               DENALI_CTL_40_DATA 0x00000000 //
#define               DENALI_CTL_41_DATA 0x00000000 //
#define               DENALI_CTL_42_DATA 0x00000000 //
#define               DENALI_CTL_43_DATA 0x00000000 //
#define               DENALI_CTL_44_DATA 0x00000000 //
#define               DENALI_CTL_45_DATA 0x00000010 //
#define               DENALI_CTL_46_DATA 0x00000000 //
#define               DENALI_CTL_47_DATA 0x00000000 //
#define               DENALI_CTL_48_DATA 0x10000410 //
#define               DENALI_CTL_49_DATA 0x04100004 //
#define               DENALI_CTL_50_DATA 0x00041000 //
#define               DENALI_CTL_51_DATA 0x00050404 //
#define               DENALI_CTL_52_DATA 0x0015001b //
#define               DENALI_CTL_53_DATA 0x00150804 //
#define               DENALI_CTL_54_DATA 0x00001a04 //
#define               DENALI_CTL_55_DATA 0x08040014 //
#define               DENALI_CTL_56_DATA 0x00050014 //
#define               DENALI_CTL_57_DATA 0x0015001b //
#define               DENALI_CTL_58_DATA 0x00150804 //
#define               DENALI_CTL_59_DATA 0x00001b05 //
#define               DENALI_CTL_60_DATA 0x08040015 //
#define               DENALI_CTL_61_DATA 0x04000015 //
#define               DENALI_CTL_62_DATA 0x00000a0a //
#define               DENALI_CTL_63_DATA 0x04007242 //
#define               DENALI_CTL_64_DATA 0x0a0a0407 //
#define               DENALI_CTL_65_DATA 0x03006db0 //
#define               DENALI_CTL_66_DATA 0x0a0a0406 //
#define               DENALI_CTL_67_DATA 0x04007242 //
#define               DENALI_CTL_68_DATA 0x0a0a0407 //
#define               DENALI_CTL_69_DATA 0x04007242 //
#define               DENALI_CTL_70_DATA 0x02030007 //
#define               DENALI_CTL_71_DATA 0x08070800 //
#define               DENALI_CTL_72_DATA 0x08070806 //
#define               DENALI_CTL_73_DATA 0x01000407 //
#define               DENALI_CTL_74_DATA 0x100e1001 //
#define               DENALI_CTL_75_DATA 0x09090310 //
#define               DENALI_CTL_76_DATA 0x01000909 //
#define               DENALI_CTL_77_DATA 0x00000001 //
#define               DENALI_CTL_78_DATA 0x00080301 //
#define               DENALI_CTL_79_DATA 0x00000037 //
#define               DENALI_CTL_80_DATA 0x00000651 //
#define               DENALI_CTL_81_DATA 0x00000034 //
#define               DENALI_CTL_82_DATA 0x00000610 //
#define               DENALI_CTL_83_DATA 0x00000037 //
#define               DENALI_CTL_84_DATA 0x00000651 //
#define               DENALI_CTL_85_DATA 0x00000037 //
#define               DENALI_CTL_86_DATA 0x00000651 //
#define               DENALI_CTL_87_DATA 0x00190000 //
#define               DENALI_CTL_88_DATA 0x001800c3 //
#define               DENALI_CTL_89_DATA 0x001900bb //
#define               DENALI_CTL_90_DATA 0x001900c3 //
#define               DENALI_CTL_91_DATA 0x004000c3 //
#define               DENALI_CTL_92_DATA 0x00120103 //
#define               DENALI_CTL_93_DATA 0x00030004 //
#define               DENALI_CTL_94_DATA 0x00040004 //
#define               DENALI_CTL_95_DATA 0x000a000a //
#define               DENALI_CTL_96_DATA 0x000a000a //
#define               DENALI_CTL_97_DATA 0x08080808 //
#define               DENALI_CTL_98_DATA 0x00000000 //
#define               DENALI_CTL_99_DATA 0x00000100 //
#define              DENALI_CTL_100_DATA 0x01000000 //
#define              DENALI_CTL_101_DATA 0x00000000 //
#define              DENALI_CTL_102_DATA 0x00000100 //
#define              DENALI_CTL_103_DATA 0x01000000 //
#define              DENALI_CTL_104_DATA 0x003b003b //
#define              DENALI_CTL_105_DATA 0x00380038 //
#define              DENALI_CTL_106_DATA 0x003b003b //
#define              DENALI_CTL_107_DATA 0x003b003b //
#define              DENALI_CTL_108_DATA 0x0038003b //
#define              DENALI_CTL_109_DATA 0x003b003b //
#define              DENALI_CTL_110_DATA 0x00000000 //
#define              DENALI_CTL_111_DATA 0x00000400 //
#define              DENALI_CTL_112_DATA 0x00000000 //
#define              DENALI_CTL_113_DATA 0x00000003 //
#define              DENALI_CTL_114_DATA 0x04000000 //
#define              DENALI_CTL_115_DATA 0x00000000 //
#define              DENALI_CTL_116_DATA 0x00040000 //
#define              DENALI_CTL_117_DATA 0x00000000 //
#define              DENALI_CTL_118_DATA 0x00010000 //
#define              DENALI_CTL_119_DATA 0x00010000 //
#define              DENALI_CTL_120_DATA 0x00000000 //
#define              DENALI_CTL_121_DATA 0x00000000 //
#define              DENALI_CTL_122_DATA 0x40020100 //
#define              DENALI_CTL_123_DATA 0x00038010 //
#define              DENALI_CTL_124_DATA 0x00050004 //
#define              DENALI_CTL_125_DATA 0x00000004 //
#define              DENALI_CTL_126_DATA 0x00040003 //
#define              DENALI_CTL_127_DATA 0x00040005 //
#define              DENALI_CTL_128_DATA 0x00030000 //
#define              DENALI_CTL_129_DATA 0x00050004 //
#define              DENALI_CTL_130_DATA 0x00000004 //
#define              DENALI_CTL_131_DATA 0x00040003 //
#define              DENALI_CTL_132_DATA 0x00040005 //
#define              DENALI_CTL_133_DATA 0x00000000 //
#define              DENALI_CTL_134_DATA 0x0000ca20 //
#define              DENALI_CTL_135_DATA 0x0000ca20 //
#define              DENALI_CTL_136_DATA 0x0000ca20 //
#define              DENALI_CTL_137_DATA 0x0000ca20 //
#define              DENALI_CTL_138_DATA 0x0000ca20 //
#define              DENALI_CTL_139_DATA 0x00000000 //
#define              DENALI_CTL_140_DATA 0x00002c37 //
#define              DENALI_CTL_141_DATA 0x0000c200 //
#define              DENALI_CTL_142_DATA 0x0000c200 //
#define              DENALI_CTL_143_DATA 0x0000c200 //
#define              DENALI_CTL_144_DATA 0x0000c200 //
#define              DENALI_CTL_145_DATA 0x0000c200 //
#define              DENALI_CTL_146_DATA 0x00000000 //
#define              DENALI_CTL_147_DATA 0x00002a70 //
#define              DENALI_CTL_148_DATA 0x0000ca20 //
#define              DENALI_CTL_149_DATA 0x0000ca20 //
#define              DENALI_CTL_150_DATA 0x0000ca20 //
#define              DENALI_CTL_151_DATA 0x0000ca20 //
#define              DENALI_CTL_152_DATA 0x0000ca20 //
#define              DENALI_CTL_153_DATA 0x00000000 //
#define              DENALI_CTL_154_DATA 0x00002c37 //
#define              DENALI_CTL_155_DATA 0x0000ca20 //
#define              DENALI_CTL_156_DATA 0x0000ca20 //
#define              DENALI_CTL_157_DATA 0x0000ca20 //
#define              DENALI_CTL_158_DATA 0x0000ca20 //
#define              DENALI_CTL_159_DATA 0x0000ca20 //
#define              DENALI_CTL_160_DATA 0x00000000 //
#define              DENALI_CTL_161_DATA 0x00002c37 //
#define              DENALI_CTL_162_DATA 0x00000000 //
#define              DENALI_CTL_163_DATA 0x00000000 //
#define              DENALI_CTL_164_DATA 0x00000000 //
#define              DENALI_CTL_165_DATA 0x00000000 //
#define              DENALI_CTL_166_DATA 0x00000000 //
#define              DENALI_CTL_167_DATA 0x00000000 //
#define              DENALI_CTL_168_DATA 0x00000000 //
#define              DENALI_CTL_169_DATA 0x00000000 //
#define              DENALI_CTL_170_DATA 0x00000000 //
#define              DENALI_CTL_171_DATA 0x00000000 //
#define              DENALI_CTL_172_DATA 0x00000000 //
#define              DENALI_CTL_173_DATA 0x00000000 //
#define              DENALI_CTL_174_DATA 0x00000000 //
#define              DENALI_CTL_175_DATA 0x00000000 //
#define              DENALI_CTL_176_DATA 0x00000000 //
#define              DENALI_CTL_177_DATA 0x00000000 //
#define              DENALI_CTL_178_DATA 0x02000000 //
#define              DENALI_CTL_179_DATA 0x02020202 //
#define              DENALI_CTL_180_DATA 0x00020202 //
#define              DENALI_CTL_181_DATA 0x0a090000 //
#define              DENALI_CTL_182_DATA 0x0a090701 //
#define              DENALI_CTL_183_DATA 0x0900000e //
#define              DENALI_CTL_184_DATA 0x0907010a //
#define              DENALI_CTL_185_DATA 0x00000e0a //
#define              DENALI_CTL_186_DATA 0x07010a09 //
#define              DENALI_CTL_187_DATA 0x000e0a09 //
#define              DENALI_CTL_188_DATA 0x010a0900 //
#define              DENALI_CTL_189_DATA 0x0e0a0907 //
#define              DENALI_CTL_190_DATA 0x0003012f //
#define              DENALI_CTL_191_DATA 0x00070004 //
#define              DENALI_CTL_192_DATA 0x00000000 //
#define              DENALI_CTL_193_DATA 0x00000000 //
#define              DENALI_CTL_194_DATA 0x00000000 //
#define              DENALI_CTL_195_DATA 0x00000000 //
#define              DENALI_CTL_196_DATA 0x00000000 //
#define              DENALI_CTL_197_DATA 0x00000000 //
#define              DENALI_CTL_198_DATA 0x00000000 //
#define              DENALI_CTL_199_DATA 0x00000000 //
#define              DENALI_CTL_200_DATA 0x00010000 //
#define              DENALI_CTL_201_DATA 0x10000020 //
#define              DENALI_CTL_202_DATA 0x10000020 //
#define              DENALI_CTL_203_DATA 0x10000020 //
#define              DENALI_CTL_204_DATA 0x10000020 //
#define              DENALI_CTL_205_DATA 0x00000000 //
#define              DENALI_CTL_206_DATA 0x00000400 //
#define              DENALI_CTL_207_DATA 0x00000000 //
#define              DENALI_CTL_208_DATA 0x00000001 //
#define              DENALI_CTL_209_DATA 0x00000002 //
#define              DENALI_CTL_210_DATA 0x00000003 //
#define              DENALI_CTL_211_DATA 0x00001000 //
#define              DENALI_CTL_212_DATA 0x00000000 //
#define              DENALI_CTL_213_DATA 0x00000000 //
#define              DENALI_CTL_214_DATA 0x00000000 //
#define              DENALI_CTL_215_DATA 0x00000000 //
#define              DENALI_CTL_216_DATA 0x00540000 //
#define              DENALI_CTL_217_DATA 0x0069002a //
#define              DENALI_CTL_218_DATA 0x00000000 //
#define              DENALI_CTL_219_DATA 0x00000069 //
#define              DENALI_CTL_220_DATA 0x00280050 //
#define              DENALI_CTL_221_DATA 0x00000064 //
#define              DENALI_CTL_222_DATA 0x00000064 //
#define              DENALI_CTL_223_DATA 0x002a0054 //
#define              DENALI_CTL_224_DATA 0x00000069 //
#define              DENALI_CTL_225_DATA 0x00000069 //
#define              DENALI_CTL_226_DATA 0x002a0054 //
#define              DENALI_CTL_227_DATA 0x00000069 //
#define              DENALI_CTL_228_DATA 0x00000069 //
#define              DENALI_CTL_229_DATA 0x00000000 //
#define              DENALI_CTL_230_DATA 0x00000000 //
#define              DENALI_CTL_231_DATA 0x00000000 //
#define              DENALI_CTL_232_DATA 0x00000000 //
#define              DENALI_CTL_233_DATA 0x00000000 //
#define              DENALI_CTL_234_DATA 0x000000c3 //
#define              DENALI_CTL_235_DATA 0x00000006 //
#define              DENALI_CTL_236_DATA 0x00000000 //
#define              DENALI_CTL_237_DATA 0x00000083 //
#define              DENALI_CTL_238_DATA 0x00000006 //
#define              DENALI_CTL_239_DATA 0x00000000 //
#define              DENALI_CTL_240_DATA 0x000000c3 //
#define              DENALI_CTL_241_DATA 0x00000006 //
#define              DENALI_CTL_242_DATA 0x00000000 //
#define              DENALI_CTL_243_DATA 0x000000c3 //
#define              DENALI_CTL_244_DATA 0x00000006 //
#define              DENALI_CTL_245_DATA 0x00000000 //
#define              DENALI_CTL_246_DATA 0x00000001 //
#define              DENALI_CTL_247_DATA 0x00000001 //
#define              DENALI_CTL_248_DATA 0x00000001 //
#define              DENALI_CTL_249_DATA 0x00000001 //
#define              DENALI_CTL_250_DATA 0x00000000 //
#define              DENALI_CTL_251_DATA 0x00000000 //
#define              DENALI_CTL_252_DATA 0x00000000 //
#define              DENALI_CTL_253_DATA 0x00000000 //
#define              DENALI_CTL_254_DATA 0x03000000 //
#define              DENALI_CTL_255_DATA 0x00030303 //
#define              DENALI_CTL_256_DATA 0x00000000 //
#define              DENALI_CTL_257_DATA 0x00000000 //
#define              DENALI_CTL_258_DATA 0x00000000 //
#define              DENALI_CTL_259_DATA 0x00000000 //
#define              DENALI_CTL_260_DATA 0x00000000 //
#define              DENALI_CTL_261_DATA 0x00000000 //
#define              DENALI_CTL_262_DATA 0x00000000 //
#define              DENALI_CTL_263_DATA 0x00000000 //
#define              DENALI_CTL_264_DATA 0x00000000 //
#define              DENALI_CTL_265_DATA 0x00000000 //
#define              DENALI_CTL_266_DATA 0x00000000 //
#define              DENALI_CTL_267_DATA 0x00000000 //
#define              DENALI_CTL_268_DATA 0x00000000 //
#define              DENALI_CTL_269_DATA 0x00000000 //
#define              DENALI_CTL_270_DATA 0x00000020 //
#define              DENALI_CTL_271_DATA 0x00000000 //
#define              DENALI_CTL_272_DATA 0x01000001 //
#define              DENALI_CTL_273_DATA 0x00000000 //
#define              DENALI_CTL_274_DATA 0x00000000 //
#define              DENALI_CTL_275_DATA 0x01010000 //
#define              DENALI_CTL_276_DATA 0x00000000 //
#define              DENALI_CTL_277_DATA 0x00000000 //
#define              DENALI_CTL_278_DATA 0x00000000 //
#define              DENALI_CTL_279_DATA 0x00000000 //
#define              DENALI_CTL_280_DATA 0x00000000 //
#define              DENALI_CTL_281_DATA 0x00000000 //
#define              DENALI_CTL_282_DATA 0x00000000 //
#define              DENALI_CTL_283_DATA 0x00000000 //
#define              DENALI_CTL_284_DATA 0x00000000 //
#define              DENALI_CTL_285_DATA 0x00000000 //
#define              DENALI_CTL_286_DATA 0x11000000 //
#define              DENALI_CTL_287_DATA 0x040c1815 //
#define              DENALI_CTL_288_DATA 0x00000000 //
#define              DENALI_CTL_289_DATA 0x00000000 //
#define              DENALI_CTL_290_DATA 0x00000000 //
#define              DENALI_CTL_291_DATA 0x00000000 //
#define              DENALI_CTL_292_DATA 0x00000000 //
#define              DENALI_CTL_293_DATA 0x00000000 //
#define              DENALI_CTL_294_DATA 0x00000000 //
#define              DENALI_CTL_295_DATA 0x00000000 //
#define              DENALI_CTL_296_DATA 0x00000000 //
#define              DENALI_CTL_297_DATA 0x00000000 //
#define              DENALI_CTL_298_DATA 0x00000000 //
#define              DENALI_CTL_299_DATA 0x00000000 //
#define              DENALI_CTL_300_DATA 0x00000000 //
#define              DENALI_CTL_301_DATA 0x00000000 //
#define              DENALI_CTL_302_DATA 0x00000000 //
#define              DENALI_CTL_303_DATA 0x00000000 //
#define              DENALI_CTL_304_DATA 0x00000000 //
#define              DENALI_CTL_305_DATA 0x00000000 //
#define              DENALI_CTL_306_DATA 0x01a10003 //
#define              DENALI_CTL_307_DATA 0x00260096 //
#define              DENALI_CTL_308_DATA 0x000001a1 //
#define              DENALI_CTL_309_DATA 0x00900190 //
#define              DENALI_CTL_310_DATA 0x01900024 //
#define              DENALI_CTL_311_DATA 0x0001a100 //
#define              DENALI_CTL_312_DATA 0x00260096 //
#define              DENALI_CTL_313_DATA 0x000001a1 //
#define              DENALI_CTL_314_DATA 0x009601a1 //
#define              DENALI_CTL_315_DATA 0x01a10026 //
#define              DENALI_CTL_316_DATA 0x00000000 //
#define              DENALI_CTL_317_DATA 0x00140015 //
#define              DENALI_CTL_318_DATA 0x00150015 //
#define              DENALI_CTL_319_DATA 0x03040000 //
#define              DENALI_CTL_320_DATA 0x0a000000 //
#define              DENALI_CTL_321_DATA 0x0001ffff //
#define              DENALI_CTL_322_DATA 0x01010101 //
#define              DENALI_CTL_323_DATA 0x01180101 //
#define              DENALI_CTL_324_DATA 0x000c0000 //
#define              DENALI_CTL_325_DATA 0x00000100 //
#define              DENALI_CTL_326_DATA 0x00000000 //
#define              DENALI_CTL_327_DATA 0x01010000 //
#define              DENALI_CTL_328_DATA 0x00000000 //
#define              DENALI_CTL_329_DATA 0x00000001 //
#define              DENALI_CTL_330_DATA 0x00000000 //
#define              DENALI_CTL_331_DATA 0x00000000 //
#define              DENALI_CTL_332_DATA 0x00000000 //
#define              DENALI_CTL_333_DATA 0x00000000 //
#define              DENALI_CTL_334_DATA 0x00000000 //
#define              DENALI_CTL_335_DATA 0x00000000 //
#define              DENALI_CTL_336_DATA 0x00000000 //
#define              DENALI_CTL_337_DATA 0x00000000 //
#define              DENALI_CTL_338_DATA 0x00000000 //
#define              DENALI_CTL_339_DATA 0x00000000 //
#define              DENALI_CTL_340_DATA 0x00000000 //
#define              DENALI_CTL_341_DATA 0x00000000 //
#define              DENALI_CTL_342_DATA 0x00000000 //
#define              DENALI_CTL_343_DATA 0x00000000 //
#define              DENALI_CTL_344_DATA 0x00000000 //
#define              DENALI_CTL_345_DATA 0x00000000 //
#define              DENALI_CTL_346_DATA 0x00000000 //
#define              DENALI_CTL_347_DATA 0x00000000 //
#define              DENALI_CTL_348_DATA 0x00000000 //
#define              DENALI_CTL_349_DATA 0x00000000 //
#define              DENALI_CTL_350_DATA 0x00000000 //
#define              DENALI_CTL_351_DATA 0x00000000 //
#define              DENALI_CTL_352_DATA 0x00000000 //
#define              DENALI_CTL_353_DATA 0x00000000 //
#define              DENALI_CTL_354_DATA 0x00000000 //
#define              DENALI_CTL_355_DATA 0x00000000 //
#define              DENALI_CTL_356_DATA 0x00000000 //
#define              DENALI_CTL_357_DATA 0x00000000 //
#define              DENALI_CTL_358_DATA 0x00000000 //
#define              DENALI_CTL_359_DATA 0x00000000 //
#define              DENALI_CTL_360_DATA 0x00000000 //
#define              DENALI_CTL_361_DATA 0x00000000 //
#define              DENALI_CTL_362_DATA 0x00000000 //
#define              DENALI_CTL_363_DATA 0x00000000 //
#define              DENALI_CTL_364_DATA 0x00000000 //
#define              DENALI_CTL_365_DATA 0x00000000 //
#define              DENALI_CTL_366_DATA 0x00000000 //
#define              DENALI_CTL_367_DATA 0x00000000 //
#define              DENALI_CTL_368_DATA 0x00000000 //
#define              DENALI_CTL_369_DATA 0x07020702 //
#define              DENALI_CTL_370_DATA 0x07020702 //
#define              DENALI_CTL_371_DATA 0x01010101 //
#define              DENALI_CTL_372_DATA 0x08020001 //
#define              DENALI_CTL_373_DATA 0x00080808 //
#define              DENALI_CTL_374_DATA 0x02020202 //
#define              DENALI_CTL_375_DATA 0x03030000 //
#define              DENALI_CTL_376_DATA 0x00000303 //
#define              DENALI_CTL_377_DATA 0x00000808 //
#define              DENALI_CTL_378_DATA 0x00080800 //
#define              DENALI_CTL_379_DATA 0x08080000 //
#define              DENALI_CTL_380_DATA 0x08000000 //
#define              DENALI_CTL_381_DATA 0x00010008 //
#define              DENALI_CTL_382_DATA 0x00000000 //
#define              DENALI_CTL_383_DATA 0x00000000 //
#define              DENALI_CTL_384_DATA 0x000fffff //
#define              DENALI_CTL_385_DATA 0x00000000 //
#define              DENALI_CTL_386_DATA 0x000fffff //
#define              DENALI_CTL_387_DATA 0x00000000 //
#define              DENALI_CTL_388_DATA 0x000fffff //
#define              DENALI_CTL_389_DATA 0x00000000 //
#define              DENALI_CTL_390_DATA 0x000fffff //
#define              DENALI_CTL_391_DATA 0x00000000 //
#define              DENALI_CTL_392_DATA 0x000fffff //
#define              DENALI_CTL_393_DATA 0x00000000 //
#define              DENALI_CTL_394_DATA 0x000fffff //
#define              DENALI_CTL_395_DATA 0x00000000 //
#define              DENALI_CTL_396_DATA 0x000fffff //
#define              DENALI_CTL_397_DATA 0x00000000 //
#define              DENALI_CTL_398_DATA 0x000fffff //
#define              DENALI_CTL_399_DATA 0x00000000 //
#define              DENALI_CTL_400_DATA 0x000fffff //
#define              DENALI_CTL_401_DATA 0x00000000 //
#define              DENALI_CTL_402_DATA 0x000fffff //
#define              DENALI_CTL_403_DATA 0x00000000 //
#define              DENALI_CTL_404_DATA 0x000fffff //
#define              DENALI_CTL_405_DATA 0x00000000 //
#define              DENALI_CTL_406_DATA 0x000fffff //
#define              DENALI_CTL_407_DATA 0x00000000 //
#define              DENALI_CTL_408_DATA 0x000fffff //
#define              DENALI_CTL_409_DATA 0x00000000 //
#define              DENALI_CTL_410_DATA 0x000fffff //
#define              DENALI_CTL_411_DATA 0x00000000 //
#define              DENALI_CTL_412_DATA 0x000fffff //
#define              DENALI_CTL_413_DATA 0x00000000 //
#define              DENALI_CTL_414_DATA 0x000fffff //
#define              DENALI_CTL_415_DATA 0x00000000 //
#define              DENALI_CTL_416_DATA 0x000fffff //
#define              DENALI_CTL_417_DATA 0x00000000 //
#define              DENALI_CTL_418_DATA 0x000fffff //
#define              DENALI_CTL_419_DATA 0x00000000 //
#define              DENALI_CTL_420_DATA 0x000fffff //
#define              DENALI_CTL_421_DATA 0x00000000 //
#define              DENALI_CTL_422_DATA 0x000fffff //
#define              DENALI_CTL_423_DATA 0x00000000 //
#define              DENALI_CTL_424_DATA 0x000fffff //
#define              DENALI_CTL_425_DATA 0x00000000 //
#define              DENALI_CTL_426_DATA 0x000fffff //
#define              DENALI_CTL_427_DATA 0x00000000 //
#define              DENALI_CTL_428_DATA 0x000fffff //
#define              DENALI_CTL_429_DATA 0x00000000 //
#define              DENALI_CTL_430_DATA 0x000fffff //
#define              DENALI_CTL_431_DATA 0x00000000 //
#define              DENALI_CTL_432_DATA 0x000fffff //
#define              DENALI_CTL_433_DATA 0x00000000 //
#define              DENALI_CTL_434_DATA 0x000fffff //
#define              DENALI_CTL_435_DATA 0x00000000 //
#define              DENALI_CTL_436_DATA 0x000fffff //
#define              DENALI_CTL_437_DATA 0x00000000 //
#define              DENALI_CTL_438_DATA 0x000fffff //
#define              DENALI_CTL_439_DATA 0x00000000 //
#define              DENALI_CTL_440_DATA 0x000fffff //
#define              DENALI_CTL_441_DATA 0x00000000 //
#define              DENALI_CTL_442_DATA 0x000fffff //
#define              DENALI_CTL_443_DATA 0x00000000 //
#define              DENALI_CTL_444_DATA 0x000fffff //
#define              DENALI_CTL_445_DATA 0x00000000 //
#define              DENALI_CTL_446_DATA 0x000fffff //
#define              DENALI_CTL_447_DATA 0x00000000 //
#define              DENALI_CTL_448_DATA 0x000fffff //
#define              DENALI_CTL_449_DATA 0x00000000 //
#define              DENALI_CTL_450_DATA 0x000fffff //
#define              DENALI_CTL_451_DATA 0x00000000 //
#define              DENALI_CTL_452_DATA 0x000fffff //
#define              DENALI_CTL_453_DATA 0x00000000 //
#define              DENALI_CTL_454_DATA 0x000fffff //
#define              DENALI_CTL_455_DATA 0x00000000 //
#define              DENALI_CTL_456_DATA 0x000fffff //
#define              DENALI_CTL_457_DATA 0x00000000 //
#define              DENALI_CTL_458_DATA 0x000fffff //
#define              DENALI_CTL_459_DATA 0x00000000 //
#define              DENALI_CTL_460_DATA 0x000fffff //
#define              DENALI_CTL_461_DATA 0x00000000 //
#define              DENALI_CTL_462_DATA 0x000fffff //
#define              DENALI_CTL_463_DATA 0x00000000 //
#define              DENALI_CTL_464_DATA 0x000fffff //
#define              DENALI_CTL_465_DATA 0x00000000 //
#define              DENALI_CTL_466_DATA 0x000fffff //
#define              DENALI_CTL_467_DATA 0x00000000 //
#define              DENALI_CTL_468_DATA 0x000fffff //
#define              DENALI_CTL_469_DATA 0x00000000 //
#define              DENALI_CTL_470_DATA 0x000fffff //
#define              DENALI_CTL_471_DATA 0x00000000 //
#define              DENALI_CTL_472_DATA 0x000fffff //
#define              DENALI_CTL_473_DATA 0x00000000 //
#define              DENALI_CTL_474_DATA 0x000fffff //
#define              DENALI_CTL_475_DATA 0x00000000 //
#define              DENALI_CTL_476_DATA 0x000fffff //
#define              DENALI_CTL_477_DATA 0x00000000 //
#define              DENALI_CTL_478_DATA 0x000fffff //
#define              DENALI_CTL_479_DATA 0x00000000 //
#define              DENALI_CTL_480_DATA 0x000fffff //
#define              DENALI_CTL_481_DATA 0x00000000 //
#define              DENALI_CTL_482_DATA 0x000fffff //
#define              DENALI_CTL_483_DATA 0x00000000 //
#define              DENALI_CTL_484_DATA 0x000fffff //
#define              DENALI_CTL_485_DATA 0x00000000 //
#define              DENALI_CTL_486_DATA 0x000fffff //
#define              DENALI_CTL_487_DATA 0x00000000 //
#define              DENALI_CTL_488_DATA 0x000fffff //
#define              DENALI_CTL_489_DATA 0x00000000 //
#define              DENALI_CTL_490_DATA 0x000fffff //
#define              DENALI_CTL_491_DATA 0x00000000 //
#define              DENALI_CTL_492_DATA 0x000fffff //
#define              DENALI_CTL_493_DATA 0x00000000 //
#define              DENALI_CTL_494_DATA 0x000fffff //
#define              DENALI_CTL_495_DATA 0x00000000 //
#define              DENALI_CTL_496_DATA 0x000fffff //
#define              DENALI_CTL_497_DATA 0x00000000 //
#define              DENALI_CTL_498_DATA 0x000fffff //
#define              DENALI_CTL_499_DATA 0x00000000 //
#define              DENALI_CTL_500_DATA 0x000fffff //
#define              DENALI_CTL_501_DATA 0x00000000 //
#define              DENALI_CTL_502_DATA 0x000fffff //
#define              DENALI_CTL_503_DATA 0x00000000 //
#define              DENALI_CTL_504_DATA 0x000fffff //
#define              DENALI_CTL_505_DATA 0x00000000 //
#define              DENALI_CTL_506_DATA 0x000fffff //
#define              DENALI_CTL_507_DATA 0x00000000 //
#define              DENALI_CTL_508_DATA 0x000fffff //
#define              DENALI_CTL_509_DATA 0x00000000 //
#define              DENALI_CTL_510_DATA 0x030fffff //
#define              DENALI_CTL_511_DATA 0xffffffff //
#define              DENALI_CTL_512_DATA 0x00030f0f //
#define              DENALI_CTL_513_DATA 0xffffffff //
#define              DENALI_CTL_514_DATA 0x00030f0f //
#define              DENALI_CTL_515_DATA 0xffffffff //
#define              DENALI_CTL_516_DATA 0x00030f0f //
#define              DENALI_CTL_517_DATA 0xffffffff //
#define              DENALI_CTL_518_DATA 0x00030f0f //
#define              DENALI_CTL_519_DATA 0xffffffff //
#define              DENALI_CTL_520_DATA 0x00030f0f //
#define              DENALI_CTL_521_DATA 0xffffffff //
#define              DENALI_CTL_522_DATA 0x00030f0f //
#define              DENALI_CTL_523_DATA 0xffffffff //
#define              DENALI_CTL_524_DATA 0x00030f0f //
#define              DENALI_CTL_525_DATA 0xffffffff //
#define              DENALI_CTL_526_DATA 0x00030f0f //
#define              DENALI_CTL_527_DATA 0xffffffff //
#define              DENALI_CTL_528_DATA 0x00030f0f //
#define              DENALI_CTL_529_DATA 0xffffffff //
#define              DENALI_CTL_530_DATA 0x00030f0f //
#define              DENALI_CTL_531_DATA 0xffffffff //
#define              DENALI_CTL_532_DATA 0x00030f0f //
#define              DENALI_CTL_533_DATA 0xffffffff //
#define              DENALI_CTL_534_DATA 0x00030f0f //
#define              DENALI_CTL_535_DATA 0xffffffff //
#define              DENALI_CTL_536_DATA 0x00030f0f //
#define              DENALI_CTL_537_DATA 0xffffffff //
#define              DENALI_CTL_538_DATA 0x00030f0f //
#define              DENALI_CTL_539_DATA 0xffffffff //
#define              DENALI_CTL_540_DATA 0x00030f0f //
#define              DENALI_CTL_541_DATA 0xffffffff //
#define              DENALI_CTL_542_DATA 0x00030f0f //
#define              DENALI_CTL_543_DATA 0xffffffff //
#define              DENALI_CTL_544_DATA 0x00030f0f //
#define              DENALI_CTL_545_DATA 0xffffffff //
#define              DENALI_CTL_546_DATA 0x00030f0f //
#define              DENALI_CTL_547_DATA 0xffffffff //
#define              DENALI_CTL_548_DATA 0x00030f0f //
#define              DENALI_CTL_549_DATA 0xffffffff //
#define              DENALI_CTL_550_DATA 0x00030f0f //
#define              DENALI_CTL_551_DATA 0xffffffff //
#define              DENALI_CTL_552_DATA 0x00030f0f //
#define              DENALI_CTL_553_DATA 0xffffffff //
#define              DENALI_CTL_554_DATA 0x00030f0f //
#define              DENALI_CTL_555_DATA 0xffffffff //
#define              DENALI_CTL_556_DATA 0x00030f0f //
#define              DENALI_CTL_557_DATA 0xffffffff //
#define              DENALI_CTL_558_DATA 0x00030f0f //
#define              DENALI_CTL_559_DATA 0xffffffff //
#define              DENALI_CTL_560_DATA 0x00030f0f //
#define              DENALI_CTL_561_DATA 0xffffffff //
#define              DENALI_CTL_562_DATA 0x00030f0f //
#define              DENALI_CTL_563_DATA 0xffffffff //
#define              DENALI_CTL_564_DATA 0x00030f0f //
#define              DENALI_CTL_565_DATA 0xffffffff //
#define              DENALI_CTL_566_DATA 0x00030f0f //
#define              DENALI_CTL_567_DATA 0xffffffff //
#define              DENALI_CTL_568_DATA 0x00030f0f //
#define              DENALI_CTL_569_DATA 0xffffffff //
#define              DENALI_CTL_570_DATA 0x00030f0f //
#define              DENALI_CTL_571_DATA 0xffffffff //
#define              DENALI_CTL_572_DATA 0x00030f0f //
#define              DENALI_CTL_573_DATA 0xffffffff //
#define              DENALI_CTL_574_DATA 0x00030f0f //
#define              DENALI_CTL_575_DATA 0xffffffff //
#define              DENALI_CTL_576_DATA 0x00030f0f //
#define              DENALI_CTL_577_DATA 0xffffffff //
#define              DENALI_CTL_578_DATA 0x00030f0f //
#define              DENALI_CTL_579_DATA 0xffffffff //
#define              DENALI_CTL_580_DATA 0x00030f0f //
#define              DENALI_CTL_581_DATA 0xffffffff //
#define              DENALI_CTL_582_DATA 0x00030f0f //
#define              DENALI_CTL_583_DATA 0xffffffff //
#define              DENALI_CTL_584_DATA 0x00030f0f //
#define              DENALI_CTL_585_DATA 0xffffffff //
#define              DENALI_CTL_586_DATA 0x00030f0f //
#define              DENALI_CTL_587_DATA 0xffffffff //
#define              DENALI_CTL_588_DATA 0x00030f0f //
#define              DENALI_CTL_589_DATA 0xffffffff //
#define              DENALI_CTL_590_DATA 0x00030f0f //
#define              DENALI_CTL_591_DATA 0xffffffff //
#define              DENALI_CTL_592_DATA 0x00030f0f //
#define              DENALI_CTL_593_DATA 0xffffffff //
#define              DENALI_CTL_594_DATA 0x00030f0f //
#define              DENALI_CTL_595_DATA 0xffffffff //
#define              DENALI_CTL_596_DATA 0x00030f0f //
#define              DENALI_CTL_597_DATA 0xffffffff //
#define              DENALI_CTL_598_DATA 0x00030f0f //
#define              DENALI_CTL_599_DATA 0xffffffff //
#define              DENALI_CTL_600_DATA 0x00030f0f //
#define              DENALI_CTL_601_DATA 0xffffffff //
#define              DENALI_CTL_602_DATA 0x00030f0f //
#define              DENALI_CTL_603_DATA 0xffffffff //
#define              DENALI_CTL_604_DATA 0x00030f0f //
#define              DENALI_CTL_605_DATA 0xffffffff //
#define              DENALI_CTL_606_DATA 0x00030f0f //
#define              DENALI_CTL_607_DATA 0xffffffff //
#define              DENALI_CTL_608_DATA 0x00030f0f //
#define              DENALI_CTL_609_DATA 0xffffffff //
#define              DENALI_CTL_610_DATA 0x00030f0f //
#define              DENALI_CTL_611_DATA 0xffffffff //
#define              DENALI_CTL_612_DATA 0x00030f0f //
#define              DENALI_CTL_613_DATA 0xffffffff //
#define              DENALI_CTL_614_DATA 0x00030f0f //
#define              DENALI_CTL_615_DATA 0xffffffff //
#define              DENALI_CTL_616_DATA 0x00030f0f //
#define              DENALI_CTL_617_DATA 0xffffffff //
#define              DENALI_CTL_618_DATA 0x00030f0f //
#define              DENALI_CTL_619_DATA 0xffffffff //
#define              DENALI_CTL_620_DATA 0x00030f0f //
#define              DENALI_CTL_621_DATA 0xffffffff //
#define              DENALI_CTL_622_DATA 0x00030f0f //
#define              DENALI_CTL_623_DATA 0xffffffff //
#define              DENALI_CTL_624_DATA 0x00030f0f //
#define              DENALI_CTL_625_DATA 0xffffffff //
#define              DENALI_CTL_626_DATA 0x00030f0f //
#define              DENALI_CTL_627_DATA 0xffffffff //
#define              DENALI_CTL_628_DATA 0x00030f0f //
#define              DENALI_CTL_629_DATA 0xffffffff //
#define              DENALI_CTL_630_DATA 0x00030f0f //
#define              DENALI_CTL_631_DATA 0xffffffff //
#define              DENALI_CTL_632_DATA 0x00030f0f //
#define              DENALI_CTL_633_DATA 0xffffffff //
#define              DENALI_CTL_634_DATA 0x00030f0f //
#define              DENALI_CTL_635_DATA 0xffffffff //
#define              DENALI_CTL_636_DATA 0x00030f0f //
#define              DENALI_CTL_637_DATA 0xffffffff //
#define              DENALI_CTL_638_DATA 0x320f0f0f //
#define              DENALI_CTL_639_DATA 0x01320001 //
#define              DENALI_CTL_640_DATA 0x00013200 //
#define              DENALI_CTL_641_DATA 0x00000132 //
#define              DENALI_CTL_642_DATA 0x00000000 //
#define              DENALI_CTL_643_DATA 0x12120000 //
#define              DENALI_CTL_644_DATA 0x00001212 //
#define              DENALI_CTL_645_DATA 0x00000015 //
#define              DENALI_CTL_646_DATA 0x00000ca2 //
#define              DENALI_CTL_647_DATA 0x00000200 //
#define              DENALI_CTL_648_DATA 0x00000200 //
#define              DENALI_CTL_649_DATA 0x00000200 //
#define              DENALI_CTL_650_DATA 0x00000200 //
#define              DENALI_CTL_651_DATA 0x00000ca2 //
#define              DENALI_CTL_652_DATA 0x00007e54 //
#define              DENALI_CTL_653_DATA 0x00000408 //
#define              DENALI_CTL_654_DATA 0x00000c20 //
#define              DENALI_CTL_655_DATA 0x00000200 //
#define              DENALI_CTL_656_DATA 0x00000200 //
#define              DENALI_CTL_657_DATA 0x00000200 //
#define              DENALI_CTL_658_DATA 0x00000200 //
#define              DENALI_CTL_659_DATA 0x00000c20 //
#define              DENALI_CTL_660_DATA 0x00007940 //
#define              DENALI_CTL_661_DATA 0x00000408 //
#define              DENALI_CTL_662_DATA 0x00000ca2 //
#define              DENALI_CTL_663_DATA 0x00000200 //
#define              DENALI_CTL_664_DATA 0x00000200 //
#define              DENALI_CTL_665_DATA 0x00000200 //
#define              DENALI_CTL_666_DATA 0x00000200 //
#define              DENALI_CTL_667_DATA 0x00000ca2 //
#define              DENALI_CTL_668_DATA 0x00007e54 //
#define              DENALI_CTL_669_DATA 0x00000408 //
#define              DENALI_CTL_670_DATA 0x00000ca2 //
#define              DENALI_CTL_671_DATA 0x00000200 //
#define              DENALI_CTL_672_DATA 0x00000200 //
#define              DENALI_CTL_673_DATA 0x00000200 //
#define              DENALI_CTL_674_DATA 0x00000200 //
#define              DENALI_CTL_675_DATA 0x00000ca2 //
#define              DENALI_CTL_676_DATA 0x00007e54 //
#define              DENALI_CTL_677_DATA 0x02020408 //
#define              DENALI_CTL_678_DATA 0x05060202 //
#define              DENALI_CTL_679_DATA 0x01010101 //
#define              DENALI_CTL_680_DATA 0x03070307 //
#define              DENALI_CTL_681_DATA 0x03070307 //
#define              DENALI_CTL_682_DATA 0x00010105 //
#define              DENALI_CTL_683_DATA 0x00010101 //
#define              DENALI_CTL_684_DATA 0x00010101 //
#define              DENALI_CTL_685_DATA 0x00010001 //
#define              DENALI_CTL_686_DATA 0x00000101 //
#define              DENALI_CTL_687_DATA 0x02000201 //
#define              DENALI_CTL_688_DATA 0x02010000 //
#define              DENALI_CTL_689_DATA 0x00000200 //
#define              DENALI_CTL_690_DATA 0x00000000 //

#else /* 800 for evb */

#define               DENALI_CTL_00_DATA 0x00002020 //
#define               DENALI_CTL_01_DATA 0x00000007 //
#define               DENALI_CTL_02_DATA 0x00000000 //
#define               DENALI_CTL_03_DATA 0x00000000 //
#define               DENALI_CTL_04_DATA 0x00000000 //
#define               DENALI_CTL_05_DATA 0x00000000 //
#define               DENALI_CTL_06_DATA 0x00000000 //
#define               DENALI_CTL_07_DATA 0x00000000 //
#define               DENALI_CTL_08_DATA 0x00000000 //
#define               DENALI_CTL_09_DATA 0x00000000 //
#define               DENALI_CTL_10_DATA 0x00000000 //
#define               DENALI_CTL_11_DATA 0x00000000 //
#define               DENALI_CTL_12_DATA 0x0000002a //
#define               DENALI_CTL_13_DATA 0x00014586 //
#define               DENALI_CTL_14_DATA 0x000001a1 //
#define               DENALI_CTL_15_DATA 0x00001047 //
#define               DENALI_CTL_16_DATA 0x00000028 //
#define               DENALI_CTL_17_DATA 0x00013880 //
#define               DENALI_CTL_18_DATA 0x00000190 //
#define               DENALI_CTL_19_DATA 0x00000fa0 //
#define               DENALI_CTL_20_DATA 0x0000002a //
#define               DENALI_CTL_21_DATA 0x00014586 //
#define               DENALI_CTL_22_DATA 0x000001a1 //
#define               DENALI_CTL_23_DATA 0x00001047 //
#define               DENALI_CTL_24_DATA 0x0000002a //
#define               DENALI_CTL_25_DATA 0x00014586 //
#define               DENALI_CTL_26_DATA 0x000001a1 //
#define               DENALI_CTL_27_DATA 0x00001047 //
#define               DENALI_CTL_28_DATA 0x00000000 //
#define               DENALI_CTL_29_DATA 0x00001001 //
#define               DENALI_CTL_30_DATA 0x02010000 //
#define               DENALI_CTL_31_DATA 0x02010003 //
#define               DENALI_CTL_32_DATA 0x00000003 //
#define               DENALI_CTL_33_DATA 0x00000054 //
#define               DENALI_CTL_34_DATA 0x000000d1 //
#define               DENALI_CTL_35_DATA 0x00000000 //
#define               DENALI_CTL_36_DATA 0x00000000 //
#define               DENALI_CTL_37_DATA 0x00000000 //
#define               DENALI_CTL_38_DATA 0x00000000 //
#define               DENALI_CTL_39_DATA 0x00020200 //
#define               DENALI_CTL_40_DATA 0x00000000 //
#define               DENALI_CTL_41_DATA 0x00000000 //
#define               DENALI_CTL_42_DATA 0x00000000 //
#define               DENALI_CTL_43_DATA 0x00000000 //
#define               DENALI_CTL_44_DATA 0x00000000 //
#define               DENALI_CTL_45_DATA 0x00000010 //
#define               DENALI_CTL_46_DATA 0x00000000 //
#define               DENALI_CTL_47_DATA 0x00000000 //
#define               DENALI_CTL_48_DATA 0x10000410 //
#define               DENALI_CTL_49_DATA 0x04100004 //
#define               DENALI_CTL_50_DATA 0x00041000 //
#define               DENALI_CTL_51_DATA 0x00050404 //
#define               DENALI_CTL_52_DATA 0x0015001b //
#define               DENALI_CTL_53_DATA 0x00150804 //
#define               DENALI_CTL_54_DATA 0x00001a04 //
#define               DENALI_CTL_55_DATA 0x08040014 //
#define               DENALI_CTL_56_DATA 0x00050014 //
#define               DENALI_CTL_57_DATA 0x0015001b //
#define               DENALI_CTL_58_DATA 0x00150804 //
#define               DENALI_CTL_59_DATA 0x00001b05 //
#define               DENALI_CTL_60_DATA 0x08040015 //
#define               DENALI_CTL_61_DATA 0x04000015 //
#define               DENALI_CTL_62_DATA 0x00000a0a //
#define               DENALI_CTL_63_DATA 0x04007242 //
#define               DENALI_CTL_64_DATA 0x0a0a0407 //
#define               DENALI_CTL_65_DATA 0x03006db0 //
#define               DENALI_CTL_66_DATA 0x0a0a0406 //
#define               DENALI_CTL_67_DATA 0x04007242 //
#define               DENALI_CTL_68_DATA 0x0a0a0407 //
#define               DENALI_CTL_69_DATA 0x04007242 //
#define               DENALI_CTL_70_DATA 0x02030007 //
#define               DENALI_CTL_71_DATA 0x08070800 //
#define               DENALI_CTL_72_DATA 0x08070806 //
#define               DENALI_CTL_73_DATA 0x01000407 //
#define               DENALI_CTL_74_DATA 0x100e1001 //
#define               DENALI_CTL_75_DATA 0x09090310 //
#define               DENALI_CTL_76_DATA 0x01000909 //
#define               DENALI_CTL_77_DATA 0x00000001 //
#define               DENALI_CTL_78_DATA 0x00080301 //
#define               DENALI_CTL_79_DATA 0x00000037 //
#define               DENALI_CTL_80_DATA 0x00000651 //
#define               DENALI_CTL_81_DATA 0x00000034 //
#define               DENALI_CTL_82_DATA 0x00000610 //
#define               DENALI_CTL_83_DATA 0x00000037 //
#define               DENALI_CTL_84_DATA 0x00000651 //
#define               DENALI_CTL_85_DATA 0x00000037 //
#define               DENALI_CTL_86_DATA 0x00000651 //
#define               DENALI_CTL_87_DATA 0x00190000 //
#define               DENALI_CTL_88_DATA 0x001800c3 //
#define               DENALI_CTL_89_DATA 0x001900bb //
#define               DENALI_CTL_90_DATA 0x001900c3 //
#define               DENALI_CTL_91_DATA 0x004000c3 //
#define               DENALI_CTL_92_DATA 0x00120103 //
#define               DENALI_CTL_93_DATA 0x00030004 //
#define               DENALI_CTL_94_DATA 0x00040004 //
#define               DENALI_CTL_95_DATA 0x000a000a //
#define               DENALI_CTL_96_DATA 0x000a000a //
#define               DENALI_CTL_97_DATA 0x08080808 //
#define               DENALI_CTL_98_DATA 0x00000000 //
#define               DENALI_CTL_99_DATA 0x00000100 //
#define              DENALI_CTL_100_DATA 0x01000000 //
#define              DENALI_CTL_101_DATA 0x00000000 //
#define              DENALI_CTL_102_DATA 0x00000100 //
#define              DENALI_CTL_103_DATA 0x01000000 //
#define              DENALI_CTL_104_DATA 0x003b003b //
#define              DENALI_CTL_105_DATA 0x00380038 //
#define              DENALI_CTL_106_DATA 0x003b003b //
#define              DENALI_CTL_107_DATA 0x003b003b //
#define              DENALI_CTL_108_DATA 0x0038003b //
#define              DENALI_CTL_109_DATA 0x003b003b //
#define              DENALI_CTL_110_DATA 0x00000000 //
#define              DENALI_CTL_111_DATA 0x00000400 //
#define              DENALI_CTL_112_DATA 0x00000000 //
#define              DENALI_CTL_113_DATA 0x00000003 //
#define              DENALI_CTL_114_DATA 0x04000000 //
#define              DENALI_CTL_115_DATA 0x00000000 //
#define              DENALI_CTL_116_DATA 0x00040000 //
#define              DENALI_CTL_117_DATA 0x00000000 //
#define              DENALI_CTL_118_DATA 0x00010000 //
#define              DENALI_CTL_119_DATA 0x00010000 //
#define              DENALI_CTL_120_DATA 0x00000000 //
#define              DENALI_CTL_121_DATA 0x00000000 //
#define              DENALI_CTL_122_DATA 0x40020100 //
#define              DENALI_CTL_123_DATA 0x00038010 //
#define              DENALI_CTL_124_DATA 0x00050004 //
#define              DENALI_CTL_125_DATA 0x00000004 //
#define              DENALI_CTL_126_DATA 0x00040003 //
#define              DENALI_CTL_127_DATA 0x00040005 //
#define              DENALI_CTL_128_DATA 0x00030000 //
#define              DENALI_CTL_129_DATA 0x00050004 //
#define              DENALI_CTL_130_DATA 0x00000004 //
#define              DENALI_CTL_131_DATA 0x00040003 //
#define              DENALI_CTL_132_DATA 0x00040005 //
#define              DENALI_CTL_133_DATA 0x00000000 //
#define              DENALI_CTL_134_DATA 0x0000ca20 //
#define              DENALI_CTL_135_DATA 0x0000ca20 //
#define              DENALI_CTL_136_DATA 0x0000ca20 //
#define              DENALI_CTL_137_DATA 0x0000ca20 //
#define              DENALI_CTL_138_DATA 0x0000ca20 //
#define              DENALI_CTL_139_DATA 0x00000000 //
#define              DENALI_CTL_140_DATA 0x00002c37 //
#define              DENALI_CTL_141_DATA 0x0000c200 //
#define              DENALI_CTL_142_DATA 0x0000c200 //
#define              DENALI_CTL_143_DATA 0x0000c200 //
#define              DENALI_CTL_144_DATA 0x0000c200 //
#define              DENALI_CTL_145_DATA 0x0000c200 //
#define              DENALI_CTL_146_DATA 0x00000000 //
#define              DENALI_CTL_147_DATA 0x00002a70 //
#define              DENALI_CTL_148_DATA 0x0000ca20 //
#define              DENALI_CTL_149_DATA 0x0000ca20 //
#define              DENALI_CTL_150_DATA 0x0000ca20 //
#define              DENALI_CTL_151_DATA 0x0000ca20 //
#define              DENALI_CTL_152_DATA 0x0000ca20 //
#define              DENALI_CTL_153_DATA 0x00000000 //
#define              DENALI_CTL_154_DATA 0x00002c37 //
#define              DENALI_CTL_155_DATA 0x0000ca20 //
#define              DENALI_CTL_156_DATA 0x0000ca20 //
#define              DENALI_CTL_157_DATA 0x0000ca20 //
#define              DENALI_CTL_158_DATA 0x0000ca20 //
#define              DENALI_CTL_159_DATA 0x0000ca20 //
#define              DENALI_CTL_160_DATA 0x00000000 //
#define              DENALI_CTL_161_DATA 0x00002c37 //
#define              DENALI_CTL_162_DATA 0x00000000 //
#define              DENALI_CTL_163_DATA 0x00000000 //
#define              DENALI_CTL_164_DATA 0x00000000 //
#define              DENALI_CTL_165_DATA 0x00000000 //
#define              DENALI_CTL_166_DATA 0x00000000 //
#define              DENALI_CTL_167_DATA 0x00000000 //
#define              DENALI_CTL_168_DATA 0x00000000 //
#define              DENALI_CTL_169_DATA 0x00000000 //
#define              DENALI_CTL_170_DATA 0x00000000 //
#define              DENALI_CTL_171_DATA 0x00000000 //
#define              DENALI_CTL_172_DATA 0x00000000 //
#define              DENALI_CTL_173_DATA 0x00000000 //
#define              DENALI_CTL_174_DATA 0x00000000 //
#define              DENALI_CTL_175_DATA 0x00000000 //
#define              DENALI_CTL_176_DATA 0x00000000 //
#define              DENALI_CTL_177_DATA 0x00000000 //
#define              DENALI_CTL_178_DATA 0x02000000 //
#define              DENALI_CTL_179_DATA 0x02020202 //
#define              DENALI_CTL_180_DATA 0x00020202 //
#define              DENALI_CTL_181_DATA 0x0a090000 //
#define              DENALI_CTL_182_DATA 0x0a090701 //
#define              DENALI_CTL_183_DATA 0x0900000e //
#define              DENALI_CTL_184_DATA 0x0907010a //
#define              DENALI_CTL_185_DATA 0x00000e0a //
#define              DENALI_CTL_186_DATA 0x07010a09 //
#define              DENALI_CTL_187_DATA 0x000e0a09 //
#define              DENALI_CTL_188_DATA 0x010a0900 //
#define              DENALI_CTL_189_DATA 0x0e0a0907 //
#define              DENALI_CTL_190_DATA 0x0003012f //
#define              DENALI_CTL_191_DATA 0x00070004 //
#define              DENALI_CTL_192_DATA 0x00000000 //
#define              DENALI_CTL_193_DATA 0x00000000 //
#define              DENALI_CTL_194_DATA 0x00000000 //
#define              DENALI_CTL_195_DATA 0x00000000 //
#define              DENALI_CTL_196_DATA 0x00000000 //
#define              DENALI_CTL_197_DATA 0x00000000 //
#define              DENALI_CTL_198_DATA 0x00000000 //
#define              DENALI_CTL_199_DATA 0x00000000 //
#define              DENALI_CTL_200_DATA 0x00010000 //
#define              DENALI_CTL_201_DATA 0x10000020 //
#define              DENALI_CTL_202_DATA 0x10000020 //
#define              DENALI_CTL_203_DATA 0x10000020 //
#define              DENALI_CTL_204_DATA 0x10000020 //
#define              DENALI_CTL_205_DATA 0x00000000 //
#define              DENALI_CTL_206_DATA 0x00000400 //
#define              DENALI_CTL_207_DATA 0x00000000 //
#define              DENALI_CTL_208_DATA 0x00000001 //
#define              DENALI_CTL_209_DATA 0x00000002 //
#define              DENALI_CTL_210_DATA 0x00000003 //
#define              DENALI_CTL_211_DATA 0x00001000 //
#define              DENALI_CTL_212_DATA 0x00000000 //
#define              DENALI_CTL_213_DATA 0x00000000 //
#define              DENALI_CTL_214_DATA 0x00000000 //
#define              DENALI_CTL_215_DATA 0x00000000 //
#define              DENALI_CTL_216_DATA 0x00540000 //
#define              DENALI_CTL_217_DATA 0x0069002a //
#define              DENALI_CTL_218_DATA 0x00000000 //
#define              DENALI_CTL_219_DATA 0x00000069 //
#define              DENALI_CTL_220_DATA 0x00280050 //
#define              DENALI_CTL_221_DATA 0x00000064 //
#define              DENALI_CTL_222_DATA 0x00000064 //
#define              DENALI_CTL_223_DATA 0x002a0054 //
#define              DENALI_CTL_224_DATA 0x00000069 //
#define              DENALI_CTL_225_DATA 0x00000069 //
#define              DENALI_CTL_226_DATA 0x002a0054 //
#define              DENALI_CTL_227_DATA 0x00000069 //
#define              DENALI_CTL_228_DATA 0x00000069 //
#define              DENALI_CTL_229_DATA 0x00000000 //
#define              DENALI_CTL_230_DATA 0x00000000 //
#define              DENALI_CTL_231_DATA 0x00000000 //
#define              DENALI_CTL_232_DATA 0x00000000 //
#define              DENALI_CTL_233_DATA 0x00000000 //
#define              DENALI_CTL_234_DATA 0x000000c3 //
#define              DENALI_CTL_235_DATA 0x00000006 //
#define              DENALI_CTL_236_DATA 0x00000000 //
#define              DENALI_CTL_237_DATA 0x00000083 //
#define              DENALI_CTL_238_DATA 0x00000006 //
#define              DENALI_CTL_239_DATA 0x00000000 //
#define              DENALI_CTL_240_DATA 0x000000c3 //
#define              DENALI_CTL_241_DATA 0x00000006 //
#define              DENALI_CTL_242_DATA 0x00000000 //
#define              DENALI_CTL_243_DATA 0x000000c3 //
#define              DENALI_CTL_244_DATA 0x00000006 //
#define              DENALI_CTL_245_DATA 0x00000000 //
#define              DENALI_CTL_246_DATA 0x00000001 // default 01
#define              DENALI_CTL_247_DATA 0x00000001 //
#define              DENALI_CTL_248_DATA 0x00000001 //
#define              DENALI_CTL_249_DATA 0x00000001 //
#define              DENALI_CTL_250_DATA 0x00000000 //
#define              DENALI_CTL_251_DATA 0x00000000 //
#define              DENALI_CTL_252_DATA 0x00000000 //
#define              DENALI_CTL_253_DATA 0x00000000 //
#define              DENALI_CTL_254_DATA 0x03000000 // default 03
#define              DENALI_CTL_255_DATA 0x00030303 //
#define              DENALI_CTL_256_DATA 0x00000000 //
#define              DENALI_CTL_257_DATA 0x00000000 //
#define              DENALI_CTL_258_DATA 0x00000000 //
#define              DENALI_CTL_259_DATA 0x00000000 //
#define              DENALI_CTL_260_DATA 0x00000000 //
#define              DENALI_CTL_261_DATA 0x00000000 //
#define              DENALI_CTL_262_DATA 0x00000000 //
#define              DENALI_CTL_263_DATA 0x00000000 //
#define              DENALI_CTL_264_DATA 0x00000000 //
#define              DENALI_CTL_265_DATA 0x00000000 //
#define              DENALI_CTL_266_DATA 0x00000000 //
#define              DENALI_CTL_267_DATA 0x00000000 //
#define              DENALI_CTL_268_DATA 0x00000000 //
#define              DENALI_CTL_269_DATA 0x00000000 //
#define              DENALI_CTL_270_DATA 0x00000020 //
#define              DENALI_CTL_271_DATA 0x00000000 //
#define              DENALI_CTL_272_DATA 0x01000001 //
#define              DENALI_CTL_273_DATA 0x00000000 //
#define              DENALI_CTL_274_DATA 0x00000000 //
#define              DENALI_CTL_275_DATA 0x01010000 //
#define              DENALI_CTL_276_DATA 0x00000000 //
#define              DENALI_CTL_277_DATA 0x00000000 //
#define              DENALI_CTL_278_DATA 0x00000000 //
#define              DENALI_CTL_279_DATA 0x00000000 //
#define              DENALI_CTL_280_DATA 0x00000000 //
#define              DENALI_CTL_281_DATA 0x00000000 //
#define              DENALI_CTL_282_DATA 0x00000000 //
#define              DENALI_CTL_283_DATA 0x00000000 //
#define              DENALI_CTL_284_DATA 0x00000000 //
#define              DENALI_CTL_285_DATA 0x00000000 //
#define              DENALI_CTL_286_DATA 0x11000000 //
#define              DENALI_CTL_287_DATA 0x040c1815 //
#define              DENALI_CTL_288_DATA 0x00000000 //
#define              DENALI_CTL_289_DATA 0x00000000 //
#define              DENALI_CTL_290_DATA 0x00000000 //
#define              DENALI_CTL_291_DATA 0x00000000 //
#define              DENALI_CTL_292_DATA 0x00000000 //
#define              DENALI_CTL_293_DATA 0x00000000 //
#define              DENALI_CTL_294_DATA 0x00000000 //
#define              DENALI_CTL_295_DATA 0x00000000 //
#define              DENALI_CTL_296_DATA 0x00000000 //
#define              DENALI_CTL_297_DATA 0x00000000 //
#define              DENALI_CTL_298_DATA 0x00000000 //
#define              DENALI_CTL_299_DATA 0x00000000 //
#define              DENALI_CTL_300_DATA 0x00000000 //
#define              DENALI_CTL_301_DATA 0x00000000 //
#define              DENALI_CTL_302_DATA 0x00000000 //
#define              DENALI_CTL_303_DATA 0x00000000 //
#define              DENALI_CTL_304_DATA 0x00000000 //
#define              DENALI_CTL_305_DATA 0x00000000 //
#define              DENALI_CTL_306_DATA 0x01a10003 //
#define              DENALI_CTL_307_DATA 0x00260096 //
#define              DENALI_CTL_308_DATA 0x000001a1 //
#define              DENALI_CTL_309_DATA 0x00900190 //
#define              DENALI_CTL_310_DATA 0x01900024 //
#define              DENALI_CTL_311_DATA 0x0001a100 //
#define              DENALI_CTL_312_DATA 0x00260096 //
#define              DENALI_CTL_313_DATA 0x000001a1 //
#define              DENALI_CTL_314_DATA 0x009601a1 //
#define              DENALI_CTL_315_DATA 0x01a10026 //
#define              DENALI_CTL_316_DATA 0x00000000 //
#define              DENALI_CTL_317_DATA 0x00140015 //
#define              DENALI_CTL_318_DATA 0x00150015 //
#define              DENALI_CTL_319_DATA 0x03040000 //
#define              DENALI_CTL_320_DATA 0x0a000000 //
#define              DENALI_CTL_321_DATA 0x0001ffff //
#define              DENALI_CTL_322_DATA 0x01010101 //
#define              DENALI_CTL_323_DATA 0x01180101 //
#define              DENALI_CTL_324_DATA 0x000c0000 //
#define              DENALI_CTL_325_DATA 0x00000100 //
#define              DENALI_CTL_326_DATA 0x00000000 //
#define              DENALI_CTL_327_DATA 0x01010000 //
#define              DENALI_CTL_328_DATA 0x00000000 //
#define              DENALI_CTL_329_DATA 0x00000001 //
#define              DENALI_CTL_330_DATA 0x00000000 //
#define              DENALI_CTL_331_DATA 0x00000000 //
#define              DENALI_CTL_332_DATA 0x00000000 //
#define              DENALI_CTL_333_DATA 0x00000000 //
#define              DENALI_CTL_334_DATA 0x00000000 //
#define              DENALI_CTL_335_DATA 0x00000000 //
#define              DENALI_CTL_336_DATA 0x00000000 //
#define              DENALI_CTL_337_DATA 0x00000000 //
#define              DENALI_CTL_338_DATA 0x00000000 //
#define              DENALI_CTL_339_DATA 0x00000000 //
#define              DENALI_CTL_340_DATA 0x00000000 //
#define              DENALI_CTL_341_DATA 0x00000000 //
#define              DENALI_CTL_342_DATA 0x00000000 //
#define              DENALI_CTL_343_DATA 0x00000000 //
#define              DENALI_CTL_344_DATA 0x00000000 //
#define              DENALI_CTL_345_DATA 0x00000000 //
#define              DENALI_CTL_346_DATA 0x00000000 //
#define              DENALI_CTL_347_DATA 0x00000000 //
#define              DENALI_CTL_348_DATA 0x00000000 //
#define              DENALI_CTL_349_DATA 0x00000000 //
#define              DENALI_CTL_350_DATA 0x00000000 //
#define              DENALI_CTL_351_DATA 0x00000000 //
#define              DENALI_CTL_352_DATA 0x00000000 //
#define              DENALI_CTL_353_DATA 0x00000000 //
#define              DENALI_CTL_354_DATA 0x00000000 //
#define              DENALI_CTL_355_DATA 0x00000000 //
#define              DENALI_CTL_356_DATA 0x00000000 //
#define              DENALI_CTL_357_DATA 0x00000000 //
#define              DENALI_CTL_358_DATA 0x00000000 //
#define              DENALI_CTL_359_DATA 0x00000000 //
#define              DENALI_CTL_360_DATA 0x00000000 //
#define              DENALI_CTL_361_DATA 0x00000000 //
#define              DENALI_CTL_362_DATA 0x00000000 //
#define              DENALI_CTL_363_DATA 0x00000000 //
#define              DENALI_CTL_364_DATA 0x00000000 //
#define              DENALI_CTL_365_DATA 0x00000000 //
#define              DENALI_CTL_366_DATA 0x00000000 //
#define              DENALI_CTL_367_DATA 0x00000000 //
#define              DENALI_CTL_368_DATA 0x00000000 //
#define              DENALI_CTL_369_DATA 0x07020702 //
#define              DENALI_CTL_370_DATA 0x07020702 //
#define              DENALI_CTL_371_DATA 0x01010101 //
#define              DENALI_CTL_372_DATA 0x08020001 //
#define              DENALI_CTL_373_DATA 0x00080808 //
#define              DENALI_CTL_374_DATA 0x02020202 //
#define              DENALI_CTL_375_DATA 0x03030000 //
#define              DENALI_CTL_376_DATA 0x00000303 //
#define              DENALI_CTL_377_DATA 0x00000808 //
#define              DENALI_CTL_378_DATA 0x00080800 //
#define              DENALI_CTL_379_DATA 0x08080000 //
#define              DENALI_CTL_380_DATA 0x08000000 //
#define              DENALI_CTL_381_DATA 0x00010008 //
#define              DENALI_CTL_382_DATA 0x00000000 //
#define              DENALI_CTL_383_DATA 0x00000000 //
#define              DENALI_CTL_384_DATA 0x000fffff //
#define              DENALI_CTL_385_DATA 0x00000000 //
#define              DENALI_CTL_386_DATA 0x000fffff //
#define              DENALI_CTL_387_DATA 0x00000000 //
#define              DENALI_CTL_388_DATA 0x000fffff //
#define              DENALI_CTL_389_DATA 0x00000000 //
#define              DENALI_CTL_390_DATA 0x000fffff //
#define              DENALI_CTL_391_DATA 0x00000000 //
#define              DENALI_CTL_392_DATA 0x000fffff //
#define              DENALI_CTL_393_DATA 0x00000000 //
#define              DENALI_CTL_394_DATA 0x000fffff //
#define              DENALI_CTL_395_DATA 0x00000000 //
#define              DENALI_CTL_396_DATA 0x000fffff //
#define              DENALI_CTL_397_DATA 0x00000000 //
#define              DENALI_CTL_398_DATA 0x000fffff //
#define              DENALI_CTL_399_DATA 0x00000000 //
#define              DENALI_CTL_400_DATA 0x000fffff //
#define              DENALI_CTL_401_DATA 0x00000000 //
#define              DENALI_CTL_402_DATA 0x000fffff //
#define              DENALI_CTL_403_DATA 0x00000000 //
#define              DENALI_CTL_404_DATA 0x000fffff //
#define              DENALI_CTL_405_DATA 0x00000000 //
#define              DENALI_CTL_406_DATA 0x000fffff //
#define              DENALI_CTL_407_DATA 0x00000000 //
#define              DENALI_CTL_408_DATA 0x000fffff //
#define              DENALI_CTL_409_DATA 0x00000000 //
#define              DENALI_CTL_410_DATA 0x000fffff //
#define              DENALI_CTL_411_DATA 0x00000000 //
#define              DENALI_CTL_412_DATA 0x000fffff //
#define              DENALI_CTL_413_DATA 0x00000000 //
#define              DENALI_CTL_414_DATA 0x000fffff //
#define              DENALI_CTL_415_DATA 0x00000000 //
#define              DENALI_CTL_416_DATA 0x000fffff //
#define              DENALI_CTL_417_DATA 0x00000000 //
#define              DENALI_CTL_418_DATA 0x000fffff //
#define              DENALI_CTL_419_DATA 0x00000000 //
#define              DENALI_CTL_420_DATA 0x000fffff //
#define              DENALI_CTL_421_DATA 0x00000000 //
#define              DENALI_CTL_422_DATA 0x000fffff //
#define              DENALI_CTL_423_DATA 0x00000000 //
#define              DENALI_CTL_424_DATA 0x000fffff //
#define              DENALI_CTL_425_DATA 0x00000000 //
#define              DENALI_CTL_426_DATA 0x000fffff //
#define              DENALI_CTL_427_DATA 0x00000000 //
#define              DENALI_CTL_428_DATA 0x000fffff //
#define              DENALI_CTL_429_DATA 0x00000000 //
#define              DENALI_CTL_430_DATA 0x000fffff //
#define              DENALI_CTL_431_DATA 0x00000000 //
#define              DENALI_CTL_432_DATA 0x000fffff //
#define              DENALI_CTL_433_DATA 0x00000000 //
#define              DENALI_CTL_434_DATA 0x000fffff //
#define              DENALI_CTL_435_DATA 0x00000000 //
#define              DENALI_CTL_436_DATA 0x000fffff //
#define              DENALI_CTL_437_DATA 0x00000000 //
#define              DENALI_CTL_438_DATA 0x000fffff //
#define              DENALI_CTL_439_DATA 0x00000000 //
#define              DENALI_CTL_440_DATA 0x000fffff //
#define              DENALI_CTL_441_DATA 0x00000000 //
#define              DENALI_CTL_442_DATA 0x000fffff //
#define              DENALI_CTL_443_DATA 0x00000000 //
#define              DENALI_CTL_444_DATA 0x000fffff //
#define              DENALI_CTL_445_DATA 0x00000000 //
#define              DENALI_CTL_446_DATA 0x000fffff //
#define              DENALI_CTL_447_DATA 0x00000000 //
#define              DENALI_CTL_448_DATA 0x000fffff //
#define              DENALI_CTL_449_DATA 0x00000000 //
#define              DENALI_CTL_450_DATA 0x000fffff //
#define              DENALI_CTL_451_DATA 0x00000000 //
#define              DENALI_CTL_452_DATA 0x000fffff //
#define              DENALI_CTL_453_DATA 0x00000000 //
#define              DENALI_CTL_454_DATA 0x000fffff //
#define              DENALI_CTL_455_DATA 0x00000000 //
#define              DENALI_CTL_456_DATA 0x000fffff //
#define              DENALI_CTL_457_DATA 0x00000000 //
#define              DENALI_CTL_458_DATA 0x000fffff //
#define              DENALI_CTL_459_DATA 0x00000000 //
#define              DENALI_CTL_460_DATA 0x000fffff //
#define              DENALI_CTL_461_DATA 0x00000000 //
#define              DENALI_CTL_462_DATA 0x000fffff //
#define              DENALI_CTL_463_DATA 0x00000000 //
#define              DENALI_CTL_464_DATA 0x000fffff //
#define              DENALI_CTL_465_DATA 0x00000000 //
#define              DENALI_CTL_466_DATA 0x000fffff //
#define              DENALI_CTL_467_DATA 0x00000000 //
#define              DENALI_CTL_468_DATA 0x000fffff //
#define              DENALI_CTL_469_DATA 0x00000000 //
#define              DENALI_CTL_470_DATA 0x000fffff //
#define              DENALI_CTL_471_DATA 0x00000000 //
#define              DENALI_CTL_472_DATA 0x000fffff //
#define              DENALI_CTL_473_DATA 0x00000000 //
#define              DENALI_CTL_474_DATA 0x000fffff //
#define              DENALI_CTL_475_DATA 0x00000000 //
#define              DENALI_CTL_476_DATA 0x000fffff //
#define              DENALI_CTL_477_DATA 0x00000000 //
#define              DENALI_CTL_478_DATA 0x000fffff //
#define              DENALI_CTL_479_DATA 0x00000000 //
#define              DENALI_CTL_480_DATA 0x000fffff //
#define              DENALI_CTL_481_DATA 0x00000000 //
#define              DENALI_CTL_482_DATA 0x000fffff //
#define              DENALI_CTL_483_DATA 0x00000000 //
#define              DENALI_CTL_484_DATA 0x000fffff //
#define              DENALI_CTL_485_DATA 0x00000000 //
#define              DENALI_CTL_486_DATA 0x000fffff //
#define              DENALI_CTL_487_DATA 0x00000000 //
#define              DENALI_CTL_488_DATA 0x000fffff //
#define              DENALI_CTL_489_DATA 0x00000000 //
#define              DENALI_CTL_490_DATA 0x000fffff //
#define              DENALI_CTL_491_DATA 0x00000000 //
#define              DENALI_CTL_492_DATA 0x000fffff //
#define              DENALI_CTL_493_DATA 0x00000000 //
#define              DENALI_CTL_494_DATA 0x000fffff //
#define              DENALI_CTL_495_DATA 0x00000000 //
#define              DENALI_CTL_496_DATA 0x000fffff //
#define              DENALI_CTL_497_DATA 0x00000000 //
#define              DENALI_CTL_498_DATA 0x000fffff //
#define              DENALI_CTL_499_DATA 0x00000000 //
#define              DENALI_CTL_500_DATA 0x000fffff //
#define              DENALI_CTL_501_DATA 0x00000000 //
#define              DENALI_CTL_502_DATA 0x000fffff //
#define              DENALI_CTL_503_DATA 0x00000000 //
#define              DENALI_CTL_504_DATA 0x000fffff //
#define              DENALI_CTL_505_DATA 0x00000000 //
#define              DENALI_CTL_506_DATA 0x000fffff //
#define              DENALI_CTL_507_DATA 0x00000000 //
#define              DENALI_CTL_508_DATA 0x000fffff //
#define              DENALI_CTL_509_DATA 0x00000000 //
#define              DENALI_CTL_510_DATA 0x030fffff //
#define              DENALI_CTL_511_DATA 0xffffffff //
#define              DENALI_CTL_512_DATA 0x00030f0f //
#define              DENALI_CTL_513_DATA 0xffffffff //
#define              DENALI_CTL_514_DATA 0x00030f0f //
#define              DENALI_CTL_515_DATA 0xffffffff //
#define              DENALI_CTL_516_DATA 0x00030f0f //
#define              DENALI_CTL_517_DATA 0xffffffff //
#define              DENALI_CTL_518_DATA 0x00030f0f //
#define              DENALI_CTL_519_DATA 0xffffffff //
#define              DENALI_CTL_520_DATA 0x00030f0f //
#define              DENALI_CTL_521_DATA 0xffffffff //
#define              DENALI_CTL_522_DATA 0x00030f0f //
#define              DENALI_CTL_523_DATA 0xffffffff //
#define              DENALI_CTL_524_DATA 0x00030f0f //
#define              DENALI_CTL_525_DATA 0xffffffff //
#define              DENALI_CTL_526_DATA 0x00030f0f //
#define              DENALI_CTL_527_DATA 0xffffffff //
#define              DENALI_CTL_528_DATA 0x00030f0f //
#define              DENALI_CTL_529_DATA 0xffffffff //
#define              DENALI_CTL_530_DATA 0x00030f0f //
#define              DENALI_CTL_531_DATA 0xffffffff //
#define              DENALI_CTL_532_DATA 0x00030f0f //
#define              DENALI_CTL_533_DATA 0xffffffff //
#define              DENALI_CTL_534_DATA 0x00030f0f //
#define              DENALI_CTL_535_DATA 0xffffffff //
#define              DENALI_CTL_536_DATA 0x00030f0f //
#define              DENALI_CTL_537_DATA 0xffffffff //
#define              DENALI_CTL_538_DATA 0x00030f0f //
#define              DENALI_CTL_539_DATA 0xffffffff //
#define              DENALI_CTL_540_DATA 0x00030f0f //
#define              DENALI_CTL_541_DATA 0xffffffff //
#define              DENALI_CTL_542_DATA 0x00030f0f //
#define              DENALI_CTL_543_DATA 0xffffffff //
#define              DENALI_CTL_544_DATA 0x00030f0f //
#define              DENALI_CTL_545_DATA 0xffffffff //
#define              DENALI_CTL_546_DATA 0x00030f0f //
#define              DENALI_CTL_547_DATA 0xffffffff //
#define              DENALI_CTL_548_DATA 0x00030f0f //
#define              DENALI_CTL_549_DATA 0xffffffff //
#define              DENALI_CTL_550_DATA 0x00030f0f //
#define              DENALI_CTL_551_DATA 0xffffffff //
#define              DENALI_CTL_552_DATA 0x00030f0f //
#define              DENALI_CTL_553_DATA 0xffffffff //
#define              DENALI_CTL_554_DATA 0x00030f0f //
#define              DENALI_CTL_555_DATA 0xffffffff //
#define              DENALI_CTL_556_DATA 0x00030f0f //
#define              DENALI_CTL_557_DATA 0xffffffff //
#define              DENALI_CTL_558_DATA 0x00030f0f //
#define              DENALI_CTL_559_DATA 0xffffffff //
#define              DENALI_CTL_560_DATA 0x00030f0f //
#define              DENALI_CTL_561_DATA 0xffffffff //
#define              DENALI_CTL_562_DATA 0x00030f0f //
#define              DENALI_CTL_563_DATA 0xffffffff //
#define              DENALI_CTL_564_DATA 0x00030f0f //
#define              DENALI_CTL_565_DATA 0xffffffff //
#define              DENALI_CTL_566_DATA 0x00030f0f //
#define              DENALI_CTL_567_DATA 0xffffffff //
#define              DENALI_CTL_568_DATA 0x00030f0f //
#define              DENALI_CTL_569_DATA 0xffffffff //
#define              DENALI_CTL_570_DATA 0x00030f0f //
#define              DENALI_CTL_571_DATA 0xffffffff //
#define              DENALI_CTL_572_DATA 0x00030f0f //
#define              DENALI_CTL_573_DATA 0xffffffff //
#define              DENALI_CTL_574_DATA 0x00030f0f //
#define              DENALI_CTL_575_DATA 0xffffffff //
#define              DENALI_CTL_576_DATA 0x00030f0f //
#define              DENALI_CTL_577_DATA 0xffffffff //
#define              DENALI_CTL_578_DATA 0x00030f0f //
#define              DENALI_CTL_579_DATA 0xffffffff //
#define              DENALI_CTL_580_DATA 0x00030f0f //
#define              DENALI_CTL_581_DATA 0xffffffff //
#define              DENALI_CTL_582_DATA 0x00030f0f //
#define              DENALI_CTL_583_DATA 0xffffffff //
#define              DENALI_CTL_584_DATA 0x00030f0f //
#define              DENALI_CTL_585_DATA 0xffffffff //
#define              DENALI_CTL_586_DATA 0x00030f0f //
#define              DENALI_CTL_587_DATA 0xffffffff //
#define              DENALI_CTL_588_DATA 0x00030f0f //
#define              DENALI_CTL_589_DATA 0xffffffff //
#define              DENALI_CTL_590_DATA 0x00030f0f //
#define              DENALI_CTL_591_DATA 0xffffffff //
#define              DENALI_CTL_592_DATA 0x00030f0f //
#define              DENALI_CTL_593_DATA 0xffffffff //
#define              DENALI_CTL_594_DATA 0x00030f0f //
#define              DENALI_CTL_595_DATA 0xffffffff //
#define              DENALI_CTL_596_DATA 0x00030f0f //
#define              DENALI_CTL_597_DATA 0xffffffff //
#define              DENALI_CTL_598_DATA 0x00030f0f //
#define              DENALI_CTL_599_DATA 0xffffffff //
#define              DENALI_CTL_600_DATA 0x00030f0f //
#define              DENALI_CTL_601_DATA 0xffffffff //
#define              DENALI_CTL_602_DATA 0x00030f0f //
#define              DENALI_CTL_603_DATA 0xffffffff //
#define              DENALI_CTL_604_DATA 0x00030f0f //
#define              DENALI_CTL_605_DATA 0xffffffff //
#define              DENALI_CTL_606_DATA 0x00030f0f //
#define              DENALI_CTL_607_DATA 0xffffffff //
#define              DENALI_CTL_608_DATA 0x00030f0f //
#define              DENALI_CTL_609_DATA 0xffffffff //
#define              DENALI_CTL_610_DATA 0x00030f0f //
#define              DENALI_CTL_611_DATA 0xffffffff //
#define              DENALI_CTL_612_DATA 0x00030f0f //
#define              DENALI_CTL_613_DATA 0xffffffff //
#define              DENALI_CTL_614_DATA 0x00030f0f //
#define              DENALI_CTL_615_DATA 0xffffffff //
#define              DENALI_CTL_616_DATA 0x00030f0f //
#define              DENALI_CTL_617_DATA 0xffffffff //
#define              DENALI_CTL_618_DATA 0x00030f0f //
#define              DENALI_CTL_619_DATA 0xffffffff //
#define              DENALI_CTL_620_DATA 0x00030f0f //
#define              DENALI_CTL_621_DATA 0xffffffff //
#define              DENALI_CTL_622_DATA 0x00030f0f //
#define              DENALI_CTL_623_DATA 0xffffffff //
#define              DENALI_CTL_624_DATA 0x00030f0f //
#define              DENALI_CTL_625_DATA 0xffffffff //
#define              DENALI_CTL_626_DATA 0x00030f0f //
#define              DENALI_CTL_627_DATA 0xffffffff //
#define              DENALI_CTL_628_DATA 0x00030f0f //
#define              DENALI_CTL_629_DATA 0xffffffff //
#define              DENALI_CTL_630_DATA 0x00030f0f //
#define              DENALI_CTL_631_DATA 0xffffffff //
#define              DENALI_CTL_632_DATA 0x00030f0f //
#define              DENALI_CTL_633_DATA 0xffffffff //
#define              DENALI_CTL_634_DATA 0x00030f0f //
#define              DENALI_CTL_635_DATA 0xffffffff //
#define              DENALI_CTL_636_DATA 0x00030f0f //
#define              DENALI_CTL_637_DATA 0xffffffff //
#define              DENALI_CTL_638_DATA 0x320f0f0f //
#define              DENALI_CTL_639_DATA 0x01320001 //
#define              DENALI_CTL_640_DATA 0x00013200 //
#define              DENALI_CTL_641_DATA 0x00000132 //
#define              DENALI_CTL_642_DATA 0x00000000 //
#define              DENALI_CTL_643_DATA 0x12120000 //
#define              DENALI_CTL_644_DATA 0x00001212 //
#define              DENALI_CTL_645_DATA 0x00000015 //
#define              DENALI_CTL_646_DATA 0x00000ca2 //
#define              DENALI_CTL_647_DATA 0x00000200 //
#define              DENALI_CTL_648_DATA 0x00000200 //
#define              DENALI_CTL_649_DATA 0x00000200 //
#define              DENALI_CTL_650_DATA 0x00000200 //
#define              DENALI_CTL_651_DATA 0x00000ca2 //
#define              DENALI_CTL_652_DATA 0x00007e54 //
#define              DENALI_CTL_653_DATA 0x00000408 //
#define              DENALI_CTL_654_DATA 0x00000c20 //
#define              DENALI_CTL_655_DATA 0x00000200 //
#define              DENALI_CTL_656_DATA 0x00000200 //
#define              DENALI_CTL_657_DATA 0x00000200 //
#define              DENALI_CTL_658_DATA 0x00000200 //
#define              DENALI_CTL_659_DATA 0x00000c20 //
#define              DENALI_CTL_660_DATA 0x00007940 //
#define              DENALI_CTL_661_DATA 0x00000408 //
#define              DENALI_CTL_662_DATA 0x00000ca2 //
#define              DENALI_CTL_663_DATA 0x00000200 //
#define              DENALI_CTL_664_DATA 0x00000200 //
#define              DENALI_CTL_665_DATA 0x00000200 //
#define              DENALI_CTL_666_DATA 0x00000200 //
#define              DENALI_CTL_667_DATA 0x00000ca2 //
#define              DENALI_CTL_668_DATA 0x00007e54 //
#define              DENALI_CTL_669_DATA 0x00000408 //
#define              DENALI_CTL_670_DATA 0x00000ca2 //
#define              DENALI_CTL_671_DATA 0x00000200 //
#define              DENALI_CTL_672_DATA 0x00000200 //
#define              DENALI_CTL_673_DATA 0x00000200 //
#define              DENALI_CTL_674_DATA 0x00000200 //
#define              DENALI_CTL_675_DATA 0x00000ca2 //
#define              DENALI_CTL_676_DATA 0x00007e54 //
#define              DENALI_CTL_677_DATA 0x02020408 //
#define              DENALI_CTL_678_DATA 0x05060202 //
#define              DENALI_CTL_679_DATA 0x01010101 //
#define              DENALI_CTL_680_DATA 0x03070307 //
#define              DENALI_CTL_681_DATA 0x03070307 //
#define              DENALI_CTL_682_DATA 0x00010105 //
#define              DENALI_CTL_683_DATA 0x00010101 //
#define              DENALI_CTL_684_DATA 0x00010101 //
#define              DENALI_CTL_685_DATA 0x00010001 //
#define              DENALI_CTL_686_DATA 0x00000101 //
#define              DENALI_CTL_687_DATA 0x02000201 //
#define              DENALI_CTL_688_DATA 0x02010000 //
#define              DENALI_CTL_689_DATA 0x00000200 //
#define              DENALI_CTL_690_DATA 0x00000000 //

#endif

#define PLL_CTRL1_ADDR       0x000   // cfg word addresses
#define PLL_CTRL2_ADDR       0x004
#define PLL_DLL_CTRL1_ADDR   0x008
#define DLL_CTRL1_ADDR       0x00C
#define DLL_CTRL2_ADDR       0x010
#define DLL_CTRL3_ADDR       0x014
#define DLL_CTRL4_ADDR       0x018
#define DLL_CTRL5_ADDR       0x01C
#define DLL_CTRL6_ADDR       0x020
#define DLL_CTRL7_ADDR       0x024
#define DLL_CTRL8_ADDR       0x028
#define DLL_CTRL9_ADDR       0x02C
#define DLL_CTRL10_ADDR      0x030
#define DLL_CTRL11_ADDR      0x034
#define DLL_CTRL12_ADDR      0x038
#define DLL_CTRL13_ADDR      0x03C
#define DLL_CTRL14_ADDR      0x040
#define DLL_CTRL15_ADDR      0x044
#define DLL_CTRL16_ADDR      0x048
#define DLL_CTRL17_ADDR      0x04C
#define DLL_CTRL18_ADDR      0x050
#define DLL_CTRL19_ADDR      0x054
#define DLL_CTRL20_ADDR      0x058
#define DLL_CTRL21_ADDR      0x05C
#define DLL_CTRL22_ADDR      0x060
#define RGDLY_ADDR           0x064
#define RGDLY_ADJ_ADDR       0x068
#define IO_CAL0_ADDR         0x06C
#define DSX8_IO_CTRL_ADDR    0x070
#define CAX10_IO_CTRL_ADDR   0x074
#define PHY_CFG_ADDR         0x078
#define PHY_DSDIS_ADDR       0x07C
#define TRAINING_CTRL1_ADDR  0x080
#define TRAINING_CTRL2_ADDR  0x084
#define TRAINING_CTRL3_ADDR  0x088
#define TRAINING_CTRL4_ADDR  0x08C
#define TRAINING_CTRL5_ADDR  0x090
#define TRAINING_CTRL6_ADDR  0x094
#define CADQ_ADDR            0x098
#define RBURST_0_P0_ADDR     0x09C
#define RBURST_0_P1_ADDR     0x0A0
#define RBURST_0_P2_ADDR     0x0A4
#define RBURST_0_P3_ADDR     0x0A8
#define RBURST_1_P0_ADDR     0x0AC
#define RBURST_1_P1_ADDR     0x0B0
#define RBURST_1_P2_ADDR     0x0B4
#define RBURST_1_P3_ADDR     0x0B8
#define BIT_RDLY_DS0_ADDR    0x0BC
#define BIT_WDLY_DS0_ADDR    0x0C0
#define BIT_RDLY_DS1_ADDR    0x0C4
#define BIT_WDLY_DS1_ADDR    0x0C8
#define BIT_RDLY_DS2_ADDR    0x0CC
#define BIT_WDLY_DS2_ADDR    0x0D0
#define BIT_RDLY_DS3_ADDR    0x0D4
#define BIT_WDLY_DS3_ADDR    0x0D8
#define BIT_WDLY_CA0_ADDR    0x0DC
#define BIT_WDLY_CA1_ADDR    0x0E0
#define BIT_WDLY_CA2_ADDR    0x0E4
#define BIT_WDLY_CACK_ADDR   0x0E8
#define DQS_DRIFT_GAIN_ADDR  0x0EC
#define DQS_DRIFT_CFG_ADDR   0x0F0
#define DQS_DRIFT_COR_ADDR   0x0F4
#define DQS_DRIFT_COR_EXT_ADDR   0x0F8
#define INTERRUPT_MASK_ADDR    0x0FC
#define INTERRUPT_STATUS_ADDR  0x100
#define BIST_CTRL1_ADDR       0x104
#define BIST_CTRL2_ADDR       0x108
#define BIST_STATUS1_ADDR     0x10C
#define BIST_STATUS2_ADDR     0x110
#define LP_STATUS_CTRL_ADDR   0x114
#define RDQS_DETC_CNTR_ADDR   0x118
#define SPARE_ADDR            0x11c
void lpddr3_init();
