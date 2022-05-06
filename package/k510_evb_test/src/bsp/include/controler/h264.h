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
#ifndef _H264_INCLUDE_
#define _H264_INCLUDE_

#include <stdbool.h>

#define FINAL_RELEASE

#define K510_H264_BASE 0x92740000
#define H264_INTERRUPT_NUM  63

#define H264_CMD_REG_OFFSET 0x8200
#define H264_REG(reg) (K510_H264_BASE + reg)


/* Magic number */
#define UID                 0x30AB6E51
#define HW_ID               0x620000E0
#define DATE                0x20191115
#define VERSION             0xDC4054E7
#define AXIUID              0x41584930


#define AXI_BURST_LEN_64     0x2
#define AXI_BURST_LEN_128    0x1
#define AXI_BURST_LEN_256    0x0
#define AXI_BURST_LEN_512    0x3



/*COMMON REGISTERS*/
#define H264_COMMON_UID             0x8000
#define H264_COMMON_HW_ID           0x8004
#define H264_COMMON_DATE            0x8008
#define H264_COMMON_VERSION         0x800C
#define H264_COMMON_RESET           0x8010
#define H264_COMMON_INT_MASK        0x8014
#define H264_COMMON_INT             0x8018
#define H264_COMMON_INT_DELAY       0x801C
#define H264_COMMON_WDT_CTRL        0x8028
#define H264_COMMON_WDT_TIMEOUT     0x802C
#define H264_COMMON_TIMER           0x8030
#define H264_COMMON_AXI_ADDR_MSB    0x8050
#define H264_COMMON_AXI_UID         0x8100
#define H264_COMMON_AXI_BW          0x8104
#define H264_COMMON_AXI_STATUS      0x8108
#define H264_COMMON_AXI_MAX_BURST   0x810C
#define H264_COMMON_AXI_RBW0        0x8110
#define H264_COMMON_AXI_WBW0        0x8118
#define H264_COMMON_AXI_RBL0        0x8120

/*CORE0 CMD REGISTERS*/
#define H264_CORE0_CMD_00 0x8200
#define H264_CORE0_CMD_01 0x8204
#define H264_CORE0_CMD_02 0x8208
#define H264_CORE0_CMD_03 0x820C
#define H264_CORE0_CMD_04 0x8210
#define H264_CORE0_CMD_05 0x8214
#define H264_CORE0_CMD_06 0x8218
#define H264_CORE0_CMD_07 0x821C
#define H264_CORE0_CMD_08 0x8220
#define H264_CORE0_CMD_09 0x8224
#define H264_CORE0_CMD_10 0x8228
#define H264_CORE0_CMD_11 0x822C
#define H264_CORE0_CMD_12 0x8230
#define H264_CORE0_CMD_13 0x8234
#define H264_CORE0_CMD_14 0x8238
#define H264_CORE0_CMD_15 0x823C
#define H264_CORE0_CMD_16 0x8240
#define H264_CORE0_CMD_17 0x8244
#define H264_CORE0_CMD_18 0x8248
#define H264_CORE0_CMD_19 0x824C
#define H264_CORE0_CMD_20 0x8250
#define H264_CORE0_CMD_21 0x8254
#define H264_CORE0_CMD_22 0x8258
#define H264_CORE0_CMD_23 0x825C
#define H264_CORE0_CMD_24 0x8260
#define H264_CORE0_CMD_25 0x8264
#define H264_CORE0_CMD_26 0x8268
#define H264_CORE0_CMD_27 0x826C
#define H264_CORE0_CMD_28 0x8270
#define H264_CORE0_CMD_29 0x8274
#define H264_CORE0_CMD_30 0x8278
#define H264_CORE0_CMD_31 0x827C


/*CORE0 ADD REGISTERS*/
#define H264_CORE0_ADD_00 0x8280
#define H264_CORE0_ADD_01 0x8284
#define H264_CORE0_ADD_02 0x8288
#define H264_CORE0_ADD_03 0x828C
#define H264_CORE0_ADD_04 0x8290
#define H264_CORE0_ADD_05 0x8294
#define H264_CORE0_ADD_06 0x8298
#define H264_CORE0_ADD_07 0x829C
#define H264_CORE0_ADD_08 0x82A0
#define H264_CORE0_ADD_09 0x82A4
#define H264_CORE0_ADD_12 0x82B0
#define H264_CORE0_ADD_14 0x82B8
#define H264_CORE0_ADD_15 0x828C
#define H264_CORE0_ADD_16 0x82C0
#define H264_CORE0_ADD_17 0x82C4
#define H264_CORE0_ADD_18 0x82C8
#define H264_CORE0_ADD_19 0x82CC
#define H264_CORE0_ADD_23 0x82DC
#define H264_CORE0_ADD_24 0x82E0

/*CORE0 STATUS REGISTERS*/
#define H264_CORE0_STA_01 0x8304
#define H264_CORE0_STA_02 0x8308
#define H264_CORE0_STA_03 0x830C
#define H264_CORE0_STA_04 0x8310
#define H264_CORE0_STA_05 0x8314
#define H264_CORE0_STA_06 0x8318
#define H264_CORE0_STA_07 0x831C
#define H264_CORE0_STA_08 0x8320
#define H264_CORE0_STA_09 0x8324
#define H264_CORE0_STA_10 0x8328
#define H264_CORE0_STA_11 0x832C
#define H264_CORE0_STA_12 0x8330
#define H264_CORE0_STA_13 0x8334
#define H264_CORE0_STA_14 0x8338
#define H264_CORE0_STA_15 0x833C
#define H264_CORE0_STA_16 0x8340
#define H264_CORE0_STA_17 0x8344
#define H264_CORE0_STA_20 0x8350
#define H264_CORE0_STA_22 0x8358
#define H264_CORE0_STA_23 0x835C
#define H264_CORE0_STA_24 0x8360
#define H264_CORE0_STA_25 0x8364
#define H264_CORE0_STA_28 0x8370

/*CORE0 CMDEXT REGISTERS*/
#define H264_CORE0_CMDEXT_00 0x8380
#define H264_CORE0_CMDEXT_07 0x839C
#define H264_CORE0_CMDEXT_08 0x83A0

/*CORE0 CMD TOP REGISTERS*/
#define H264_CORE0_CMDTOP_00 0x83E0
#define H264_CORE0_CMDTOP_01 0x83E4
#define H264_CORE0_CMDTOP_02 0x83E8
#define H264_CORE0_CMDTOP_04 0x83F0
#define H264_CORE0_CMDTOP_05 0x83F4
#define H264_CORE0_CMDTOP_06 0x83F8

/*JPEG CMD REGISTERS*/
#define H264_JPEG_CMD_00 0x8400
#define H264_JPEG_CMD_01 0x8404
#define H264_JPEG_CMD_02 0x8408
#define H264_JPEG_CMD_03 0x840C
#define H264_JPEG_CMD_04 0x8410
#define H264_JPEG_CMD_05 0x8414
#define H264_JPEG_CMD_06 0x8418
#define H264_JPEG_CMD_07 0x841C
#define H264_JPEG_CMD_08 0x8420
#define H264_JPEG_CMD_09 0x8424
#define H264_JPEG_CMD_10 0x8428

/*JMPEG STATUS REGISTERS*/
#define H264_JPEG_STATUS_01 0x8434
#define H264_JPEG_STATUS_02 0x8438

/*JPEG CMDTOP REGISTERS*/
#define H264_JPEG_CMDTOP_01 0x85E4
#define H264_JPEG_CMDTOP_02 0x85E8
#define H264_JPEG_CMDTOP_04 0x85F0
#define H264_JPEG_CMDTOP_05 0x85F4
#define H264_JPEG_CMDTOP_06 0x85F8

#define MAX_NUM_CPB 32

/****************************************************************************/
#define AL_CS_FLAGS(Flags) (((Flags) & 0xFFFF) << 8)
#define AVC_PROFILE_IDC_CAVLC_444 44 // not supported
#define AVC_PROFILE_IDC_BASELINE 66
#define AVC_PROFILE_IDC_MAIN 77
#define AVC_PROFILE_IDC_EXTENDED 88 // not supported
#define AVC_PROFILE_IDC_HIGH 100
#define AVC_PROFILE_IDC_HIGH10 110
#define AVC_PROFILE_IDC_HIGH_422 122
#define AVC_PROFILE_IDC_HIGH_444_PRED 244 // not supported

/****************************************************************************/
typedef enum AL_e_Codec
{
  /* assign hardware standard value */
  AL_CODEC_AVC = 0,
  AL_CODEC_HEVC = 1,
  AL_CODEC_AV1 = 2,
  AL_CODEC_VP9 = 3,
  AL_CODEC_JPEG = 4,
  AL_CODEC_INVALID, /* sentinel */
}AL_ECodec;

/*************************************************************************//*!
   \brief Profiles identifier
*****************************************************************************/
typedef enum  AL_e_Profile
{
  AL_PROFILE_AVC = (AL_CODEC_AVC << 24),
  AL_PROFILE_AVC_CAVLC_444 = AL_PROFILE_AVC | AVC_PROFILE_IDC_CAVLC_444, // not supported
  AL_PROFILE_AVC_BASELINE = AL_PROFILE_AVC | AVC_PROFILE_IDC_BASELINE,
  AL_PROFILE_AVC_MAIN = AL_PROFILE_AVC | AVC_PROFILE_IDC_MAIN,
  AL_PROFILE_AVC_EXTENDED = AL_PROFILE_AVC | AVC_PROFILE_IDC_EXTENDED, // not supported
  AL_PROFILE_AVC_HIGH = AL_PROFILE_AVC | AVC_PROFILE_IDC_HIGH,
  AL_PROFILE_AVC_HIGH10 = AL_PROFILE_AVC | AVC_PROFILE_IDC_HIGH10,
  AL_PROFILE_AVC_HIGH_422 = AL_PROFILE_AVC | AVC_PROFILE_IDC_HIGH_422,
  AL_PROFILE_AVC_HIGH_444_PRED = AL_PROFILE_AVC | AVC_PROFILE_IDC_HIGH_444_PRED, // not supported

  AL_PROFILE_AVC_C_BASELINE = AL_PROFILE_AVC_BASELINE | AL_CS_FLAGS(0x0002),
  AL_PROFILE_AVC_PROG_HIGH = AL_PROFILE_AVC_HIGH | AL_CS_FLAGS(0x0010),
  AL_PROFILE_AVC_C_HIGH = AL_PROFILE_AVC_HIGH | AL_CS_FLAGS(0x0030),
  AL_PROFILE_AVC_HIGH10_INTRA = AL_PROFILE_AVC_HIGH10 | AL_CS_FLAGS(0x0008),
  AL_PROFILE_AVC_HIGH_422_INTRA = AL_PROFILE_AVC_HIGH_422 | AL_CS_FLAGS(0x0008),
  AL_PROFILE_AVC_HIGH_444_INTRA = AL_PROFILE_AVC_HIGH_444_PRED | AL_CS_FLAGS(0x0008), // not supported

  AL_PROFILE_JPEG = (AL_CODEC_JPEG << 24),
  AL_PROFILE_UNKNOWN = 0xFFFFFFFF
} AL_EProfile;

/*************************************************************************//*!
   \brief chroma_format_idc
*****************************************************************************/
typedef enum e_ChromaMode
{
  AL_CHROMA_MONO, /*!< Monochrome */
  AL_CHROMA_4_0_0 = AL_CHROMA_MONO, /*!< 4:0:0 = Monochrome */
  AL_CHROMA_4_2_0, /*!< 4:2:0 chroma sampling */
  AL_CHROMA_4_2_2, /*!< 4:2:2 chroma sampling */
  AL_CHROMA_4_4_4, /*!< 4:4:4 chroma sampling : Not supported */
  AL_CHROMA_MAX_ENUM, /* sentinel */
}AL_EChromaMode;


/*************************************************************************//*!
   \brief Mimics structure described in spec sec. E.1.2
*****************************************************************************/
typedef struct t_SubHrdParam
{
  uint32_t bit_rate_value_minus1[MAX_NUM_CPB];
  uint32_t cpb_size_value_minus1[MAX_NUM_CPB];
  uint32_t cpb_size_du_value_minus1[MAX_NUM_CPB];
  uint32_t bit_rate_du_value_minus1[MAX_NUM_CPB];
  uint8_t cbr_flag[MAX_NUM_CPB];
}AL_TSubHrdParam;

/*************************************************************************//*!
   \brief Mimics structure described in spec sec. E.1.2
*****************************************************************************/
typedef struct t_HrdParam
{
  uint8_t nal_hrd_parameters_present_flag;
  uint8_t vcl_hrd_parameters_present_flag;
  uint8_t sub_pic_hrd_params_present_flag;
  uint8_t tick_divisor_minus2;
  uint8_t du_cpb_removal_delay_increment_length_minus1;
  uint8_t sub_pic_cpb_params_in_pic_timing_sei_flag;
  uint8_t dpb_output_delay_du_length_minus1;

  uint8_t bit_rate_scale;
  uint8_t cpb_size_scale;
  uint8_t cpb_size_du_scale;
  uint8_t initial_cpb_removal_delay_length_minus1;
  uint8_t au_cpb_removal_delay_length_minus1;
  uint8_t dpb_output_delay_length_minus1;
  uint8_t time_offset_length;

  uint8_t fixed_pic_rate_general_flag[8];
  uint8_t fixed_pic_rate_within_cvs_flag[8];
  uint32_t elemental_duration_in_tc_minus1[8];
  uint8_t low_delay_hrd_flag[8];
  uint32_t cpb_cnt_minus1[8];

  AL_TSubHrdParam nal_sub_hrd_param;
  AL_TSubHrdParam vcl_sub_hrd_param;
}AL_THrdParam;

/*************************************************************************//*!
   \brief Mimics structure described in spec sec. E.1.1
*****************************************************************************/
typedef struct t_VuiParam
{
  uint8_t aspect_ratio_info_present_flag;
  uint8_t aspect_ratio_idc;
  uint16_t sar_width;
  uint16_t sar_height;

  uint8_t overscan_info_present_flag;
  uint8_t overscan_appropriate_flag;

  uint8_t video_signal_type_present_flag;
  uint8_t video_format;
  uint8_t video_full_range_flag;
  uint8_t colour_description_present_flag;
  uint8_t colour_primaries;
  uint8_t transfer_characteristics;
  uint8_t matrix_coefficients;

  uint8_t chroma_loc_info_present_flag;
  uint8_t chroma_sample_loc_type_top_field;
  uint8_t chroma_sample_loc_type_bottom_field;
  uint8_t neutral_chroma_indication_flag;
  uint8_t field_seq_flag;
  uint8_t frame_field_info_present_flag;

  uint8_t default_display_window_flag;
  uint32_t def_disp_win_left_offset;
  uint32_t def_disp_win_right_offset;
  uint32_t def_disp_win_top_offset;
  uint32_t def_disp_win_bottom_offset;

  uint8_t vui_timing_info_present_flag;
  uint32_t vui_num_units_in_tick;
  uint32_t vui_time_scale;
  uint8_t vui_poc_proportional_to_timing_flag;
  uint32_t vui_num_ticks_poc_diff_one_minus1;

  uint8_t vui_hrd_parameters_present_flag;
  AL_THrdParam hrd_param;

  uint8_t poc_proportional_to_timing_flag;

  uint8_t fixed_frame_rate_flag;

  uint8_t low_delay_hrd_flag;
  uint8_t pic_struct_present_flag;
  uint32_t num_reorder_frames;
  uint32_t max_dec_frame_buffering;

  uint8_t bitstream_restriction_flag;
  uint8_t tiles_fixed_structure_flag;
  uint8_t motion_vectors_over_pic_boundaries_flag;
  uint8_t restricted_ref_pic_lists_flag;
  uint8_t min_spatial_segmentation_idc;
  uint8_t max_bytes_per_pic_denom;
  uint8_t max_bits_per_min_cu_denom;
  uint8_t log2_max_mv_length_horizontal;
  uint8_t log2_max_mv_length_vertical;
}AL_TVuiParam;

/*************************************************************************//*!
   \brief Mimics structure to represent scaling list syntax elements
*****************************************************************************/
typedef struct t_SCLParam
{
  uint8_t scaling_list_pred_mode_flag[4][6];
  uint8_t scaling_list_pred_matrix_id_delta[4][6];
  uint8_t scaling_list_dc_coeff[2][6];
  uint8_t ScalingList[4][6][64]; // [SizeID][MatrixID][Coeffs]
  uint8_t UseDefaultScalingMatrixFlag[20];
}AL_TSCLParam;

typedef struct t_Avc_Sps
{
  int profile_idc;
  uint8_t constraint_set0_flag;
  uint8_t constraint_set1_flag;
  uint8_t constraint_set2_flag;
  uint8_t constraint_set3_flag;
  uint8_t constraint_set4_flag;
  uint8_t constraint_set5_flag;
  uint8_t reserved_zero_2bits;
  int level_idc;
  uint8_t seq_parameter_set_id;

  uint8_t chroma_format_idc;
  uint8_t separate_colour_plane_flag;

  uint8_t bit_depth_luma_minus8;
  uint8_t bit_depth_chroma_minus8;

  uint8_t qpprime_y_zero_transform_bypass_flag;

  uint8_t seq_scaling_matrix_present_flag;
  uint8_t seq_scaling_list_present_flag[8]; // we can define eight matrices: Sl_4x4_Intra_Y, Sl_4x4_Intra_Cb, Sl_4x4_Intra_Cr, Sl_4x4_Inter_Y, Sl_4x4_Inter_Cb, Sl_4x4_Inter_Cr, Sl_8x8_Intra_Y, Sl_8x8_Inter_Y.
  uint8_t ScalingList4x4[6][16]; // use in decoding
  uint8_t ScalingList8x8[2][64];
  AL_TSCLParam scaling_list_param;  // use in encoding

  uint8_t log2_max_frame_num_minus4;
  uint8_t pic_order_cnt_type;
  uint8_t log2_max_pic_order_cnt_lsb_minus4;
  uint8_t delta_pic_order_always_zero_flag;
  int offset_for_non_ref_pic;
  int offset_for_top_to_bottom_field;
  uint8_t num_ref_frames_in_pic_order_cnt_cycle;
  int offset_for_ref_frame[256];
  uint32_t max_num_ref_frames;
  uint8_t gaps_in_frame_num_value_allowed_flag;

  uint16_t pic_width_in_mbs_minus1;
  uint16_t pic_height_in_map_units_minus1;
  uint8_t frame_mbs_only_flag;
  uint8_t mb_adaptive_frame_field_flag;
  uint8_t direct_8x8_inference_flag;
  uint8_t frame_cropping_flag;
  int frame_crop_left_offset;
  int frame_crop_right_offset;
  int frame_crop_top_offset;
  int frame_crop_bottom_offset;

  uint8_t vui_parameters_present_flag;
  AL_TVuiParam vui_param;

  int iCurrInitialCpbRemovalDelay; // Used in the current picture buffering_period
  uint8_t UseDefaultScalingMatrix4x4Flag[6];
  uint8_t UseDefaultScalingMatrix8x8Flag[2];
  // TSpsExtMVC mvc_ext;

  // concealment flag
  bool bConceal;
}AL_TAvcSps;


/*************************************************************************//*!
   \brief Scaling List identifier
*****************************************************************************/
typedef enum e_ScalingList
{
  AL_SCL_FLAT, /*!< All matrices coefficients set to 16 */
  AL_SCL_DEFAULT, /*!< Use default matrices coefficients as defined in the codec specification */
  AL_SCL_CUSTOM, /*!< Use custom matrices coefficients */
  AL_SCL_MAX_ENUM, /* sentinel */
}AL_EScalingList;

/*************************************************************************//*!
   \brief Aspect Ratio identifer
*****************************************************************************/
typedef enum e_AspectRatio
{
  AL_ASPECT_RATIO_AUTO,
  AL_ASPECT_RATIO_1_1,
  AL_ASPECT_RATIO_4_3,
  AL_ASPECT_RATIO_16_9,
  AL_ASPECT_RATIO_NONE,
  AL_ASPECT_RATIO_MAX_ENUM, /* sentinel */
}AL_EAspectRatio;


/****************************************************************************/
enum
{
  VIDEO_FORMAT_COMPONENT,
  VIDEO_FORMAT_PAL,
  VIDEO_FORMAT_NTSC,
  VIDEO_FORMAT_SECAM,
  VIDEO_FORMAT_MAC,
  VIDEO_FORMAT_UNSPECIFIED,
} EVUIVideoFormat;

/*************************************************************************//*!
   \brief Colour Description identifer (See ISO/IEC 23091-4 or ITU-T H.273)
*****************************************************************************/
typedef enum e_ColourDescription
{
  AL_COLOUR_DESC_RESERVED,
  AL_COLOUR_DESC_UNSPECIFIED,
  AL_COLOUR_DESC_BT_470_NTSC,
  AL_COLOUR_DESC_BT_601_NTSC,
  AL_COLOUR_DESC_BT_601_PAL,
  AL_COLOUR_DESC_BT_709,
  AL_COLOUR_DESC_BT_2020,
  AL_COLOUR_DESC_SMPTE_240M,
  AL_COLOUR_DESC_SMPTE_ST_428,
  AL_COLOUR_DESC_SMPTE_RP_431,
  AL_COLOUR_DESC_SMPTE_EG_432,
  AL_COLOUR_DESC_EBU_3213,
  AL_COLOUR_DESC_GENERIC_FILM,
  AL_COLOUR_DESC_MAX_ENUM,
}AL_EColourDescription;

/************************************//*!
   \brief Transfer Function identifer
****************************************/
typedef enum e_TransferCharacteristics
{
  AL_TRANSFER_CHARAC_UNSPECIFIED = 2,
  AL_TRANSFER_CHARAC_BT_2100_PQ = 16,
  AL_TRANSFER_CHARAC_MAX_ENUM,
}AL_ETransferCharacteristics;

/*******************************************************************************//*!
   \brief Matrix coefficient identifier used for luma/chroma computation from RGB
***********************************************************************************/
typedef enum e_ColourMatrixCoefficients
{
  AL_COLOUR_MAT_COEFF_UNSPECIFIED = 2,
  AL_COLOUR_MAT_COEFF_BT_2100_YCBCR = 9,
  AL_COLOUR_MAT_COEFF_MAX_ENUM,
}AL_EColourMatrixCoefficients;

/*************************************************************************//*!
   \brief Rate Control Mode
*****************************************************************************/
typedef enum AL_e_RateCtrlMode
{
  AL_RC_CONST_QP = 0x00,
  AL_RC_CBR = 0x01,
  AL_RC_VBR = 0x02,
  AL_RC_CAPPED_VBR = 0x04,
  AL_RC_BYPASS = 0x3F,
  AL_RC_MAX_ENUM,
} AL_ERateCtrlMode;

/*************************************************************************//*!
   \brief identifies the entropy coding method
*****************************************************************************/
typedef enum e_EntropyMode
{
  AL_MODE_CAVLC,
  AL_MODE_CABAC,
  AL_MODE_MAX_ENUM, /* sentinel */
}AL_EEntropyMode;

/*************************************************************************//*!
   \brief GDR Mode
*****************************************************************************/
typedef enum AL_e_GdrMode
{
  AL_GDR_OFF = 0x00,
  AL_GDR_ON = 0x02,
  AL_GDR_VERTICAL = AL_GDR_ON | 0x00,
  AL_GDR_HORIZONTAL = AL_GDR_ON | 0x01,
  AL_GDR_MAX_ENUM,
}AL_EGdrMode;

/*************************************************************************//*!
   \brief Encoder Parameters
*****************************************************************************/
typedef  struct t_EncSettings
{
  uint16_t uEncWidth;
  uint16_t uEncHeight;
  uint16_t  uMaxCuSize;
  AL_EProfile eProfile;
  uint32_t uLevel;
  uint32_t bitDepth;
  AL_EChromaMode eChromaMode;
  AL_EAspectRatio eAspectRatio;
  AL_EColourDescription eColourDescription;
  AL_ETransferCharacteristics eTransferCharacteristics;
  AL_EColourMatrixCoefficients eColourMatrixCoeffs;
  uint32_t uClkRatio;
  uint32_t uFrameRate;
  uint32_t uMaxBitRate;
  AL_ERateCtrlMode eRCMode;
  int iCpbSize;
  AL_EEntropyMode eEntropyMode;
  int iCbPicQpOffset;
  int iCrPicQpOffset;
  bool bConstrainedIntraPred;
  int iPpsInitQp;
  uint8_t uCabacInitIdc;
  bool bEnableFrmBufComp;
  int  iTcOffset;
  int  iBetaOffset;
  bool bDisLoopFilter;
  AL_EGdrMode eGdrMode;
  int16_t iSliceQP;
  int iLastIdrId;
  uint8_t uLog2_max_frame_num;
  uint8_t uLog2_max_poc;
  // Stream
  //AL_TEncChanParam tChParam[MAX_NUM_LAYER]; /*!< Specifies the Channel parameters of the correspondong layer. Except for SHVC encoding (when supported) only layer 0 is used.*/
  bool bEnableAUD; /*!< Enable Access Unit Delimiter nal unit in the stream */
  //AL_EFillerCtrlMode eEnableFillerData; /*!< Allows Filler Data Nal unit insertion when needed (CBR) */
  uint32_t uEnableSEI; /*!< Bit-field specifying which SEI message have to be inserted. see AL_SeiFlag for a list of the supported SEI messages */

  //AL_EAspectRatio eAspectRatio; /*!< Specifies the sample aspect ratio of the luma samples. */
  //AL_EColourDescription eColourDescription; /*!< Indicates the chromaticity coordinates of the source primaries in terms of the CIE 1931 definition. */
  //AL_ETransferCharacteristics eTransferCharacteristics; /*!< Specifies the reference opto-electronic transfer characteristic function */
  //AL_EColourMatrixCoefficients eColourMatrixCoeffs; /*!< Specifies the matrix coefficients used in deriving luma and chroma signals from RGB */
  AL_EScalingList eScalingList; /*!< Specifies which kind of scaling matrices is used for encoding. When set to AL_SCL_CUSTOM, the customized value shall be provided int the ScalingList and DCcoeff parameters below*/
  bool bDependentSlice; /*!< Enable the dependent slice mode */

  bool bDisIntra; /*!< Disable Intra preiction Mode in P or B slice (validation purpose only) */
  bool bForceLoad; /*!< Specifies if the, recommended value : true */
  uint16_t uClipHrzRange; /*!< Specifies the Horizontal motion vector range. Note: this range can be further reduce by the encoder accroding to various constraints*/
  uint16_t uClipVrtRange; /*!< Specifies the Vertical motion vector range. Note: this range can be further reduce by the encoder accroding to various constraints*/
  //AL_EQpCtrlMode eQpCtrlMode; /*!< specifies the QP control mode inside a frame; see AL_EQpCtrlMode for available modes */
  //AL_EQpTableMode eQpTableMode; /*!< specifies the QP table mode. See AL_EQpTableMode for available modes */
  int NumView; /*!< specifies the number of view when multi-view encoding is supported. */
  int NumLayer; /*!< specifies the number of layer (1 or 2) when SHVC is supported. */
  uint8_t ScalingList[4][6][64]; /*!< The scaling matrix coeffecients [S][M][C] where S=0 for 4x4, S=1 for 8x8, S=2 for 16x16 and S=3 for 32x32; M=0 for Intra Y, M=1 for Intra U, M=2 for intra V, M=3 for inter Y, M=4 for inter U and M=5 for interV; and where C is the coeffecient index. Note1 in 4x4 only the 16 first coeffecient are used; Note2 in 32x32 only intra Y inter Y matrices are used */
  uint8_t SclFlag[4][6]; /*!< Specifies whether the corresponding ScalingList is valid or not */
  uint8_t DcCoeff[8]; /*!< The DC coeffidients for matrices 16x16 intra Y, 16x16 intra U, 16x16 intra V, 16x16 inter Y, 16x16 inter U, 16x16 inter V, 32x32 intra Y and 32x32 inter Y in that order*/
  uint8_t DcCoeffFlag[8]; /*!< Specifies whether the corresponding DcCoeff is valid or not */
  bool bEnableWatchdog; /*!< Enable the watchdog interrupt. This parameter should be set to 'false' until further advise */
}AL_TEncSettings;


/*************************************************************************//*!
   \brief simplified bitstream structure
*****************************************************************************/
typedef struct AL_t_BitStreamLite
{
  uint8_t* pData; /*!< Pointer to an array of bytes used as bistream */
  int iBitCount; /*!< Bits already written */
  int iMaxBits;
  bool isOverflow;
}AL_TBitStreamLite;

/*************************************************************************//*!
   \brief Nal unit type enum
 *************************************************************************/
typedef enum e_NalUnitType
{
  AL_AVC_UNDEF_NUT = 0,
  AL_AVC_NUT_VCL_NON_IDR = 1,
  AL_AVC_NUT_VCL_IDR = 5,
  AL_AVC_NUT_PREFIX_SEI = 6,
  AL_AVC_NUT_SPS = 7,
  AL_AVC_NUT_PPS = 8,
  AL_AVC_NUT_AUD = 9,
  AL_AVC_NUT_EOS = 10,
  AL_AVC_NUT_EOB = 11,
  AL_AVC_NUT_FD = 12,
  AL_AVC_NUT_SPS_EXT = 13,
  AL_AVC_NUT_PREFIX = 14,
  AL_AVC_NUT_SUB_SPS = 15,
  AL_AVC_NUT_SUFFIX_SEI = 24, /* nal_unit_type : [24..31] -> Content Unspecified */
  AL_AVC_NUT_ERR = 32,
  AL_NUT_ERR = 0xFFFFFFFF
}AL_ENut;

/****************************************************************************/
typedef struct t_NalHeader
{
  uint8_t bytes[2];
  int size;
}AL_TNalHeader;


/*************************************************************************//*!
   \brief Mimics structure described in spec sec. 7.3.2.2.
*****************************************************************************/
typedef struct t_Avc_Pps
{
  uint8_t pic_parameter_set_id;
  uint8_t seq_parameter_set_id;
  uint8_t entropy_coding_mode_flag;
  uint8_t bottom_field_pic_order_in_frame_present_flag;

  int num_slice_groups_minus1;
  uint8_t slice_group_map_type;
  uint16_t run_length_minus1[8]; // num_slice_groups_minus1 range 0 to 7 inclusive
  uint16_t top_left[8]; // num_slice_groups_minus1 range 0 to 7 inclusive
  uint16_t bottom_right[8]; // num_slice_groups_minus1 range 0 to 7 inclusive
  uint8_t slice_group_change_direction_flag;
  uint16_t slice_group_change_rate_minus1;
  uint16_t pic_size_in_map_units_minus1;
  int slice_group_id[8160]; // the max of pic_size_in_map_units in Full-HD is 8160(120*68)

  uint8_t num_ref_idx_l0_active_minus1;
  uint8_t num_ref_idx_l1_active_minus1;

  uint8_t weighted_pred_flag;
  uint8_t weighted_bipred_idc;

  int8_t pic_init_qp_minus26;
  int8_t pic_init_qs_minus26;
  int8_t chroma_qp_index_offset;
  int8_t second_chroma_qp_index_offset;

  uint8_t deblocking_filter_control_present_flag;
  uint8_t constrained_intra_pred_flag;
  uint8_t redundant_pic_cnt_present_flag;

  uint8_t transform_8x8_mode_flag;

  uint8_t pic_scaling_matrix_present_flag;
  uint8_t pic_scaling_list_present_flag[8];
  uint8_t ScalingList4x4[6][16];
  uint8_t ScalingList8x8[2][64];
  uint8_t UseDefaultScalingMatrix4x4Flag[6];
  uint8_t UseDefaultScalingMatrix8x8Flag[2];

  AL_TAvcSps* pSPS;

  // concealment flag
  bool bConceal;
}AL_TAvcPps;


/**********slice header *************/

/*************************************************************************//*!
   \brief Identifies the slice coding type
*****************************************************************************/
typedef enum e_SliceType
{
  AL_SLICE_SI = 4, /*!< AVC SI Slice */
  AL_SLICE_SP = 3, /*!< AVC SP Slice */
  AL_SLICE_GOLDEN = 3, /*!< Golden Slice */
  AL_SLICE_I = 2,  /*!< I Slice (can contain I blocks) */
  AL_SLICE_P = 1,  /*!< P Slice (can contain I and P blocks) */
  AL_SLICE_B = 0,  /*!< B Slice (can contain I, P and B blocks) */
  AL_SLICE_CONCEAL = 6, /*!< Conceal Slice (slice was concealed) */
  AL_SLICE_SKIP = 7, /*!< Skip Slice */
  AL_SLICE_REPEAT = 8, /*!< VP9 Repeat Slice (repeats the content of its reference) */
  AL_SLICE_MAX_ENUM, /* sentinel */
}AL_ESliceType;

/*************************************************************************//*!
   \brief Indentifies pic_struct (subset of table D-2)
*****************************************************************************/
typedef enum e_PicStruct
{
  AL_PS_FRM = 0,
  AL_PS_FRM_x2 = 7,
  AL_PS_FRM_x3 = 8,
  AL_PS_MAX_ENUM, /* sentinel */
}AL_EPicStruct;

/*************************************************************************//*!
   \brief Reference picture status
 ***************************************************************************/
typedef enum e_MarkingRef
{
  SHORT_TERM_REF,
  LONG_TERM_REF,
  UNUSED_FOR_REF,
  NON_EXISTING_REF,
  AL_MARKING_REF_MAX_ENUM, /* sentinel */
}AL_EMarkingRef;



/****************************************************************************/
static const uint32_t AL_PICT_INFO_IS_IDR = 0x00000001;
static const uint32_t AL_PICT_INFO_IS_REF = 0x00000002;
static const uint32_t AL_PICT_INFO_SCN_CHG = 0x00000004;
static const uint32_t AL_PICT_INFO_BEG_FRM = 0x00000008;
static const uint32_t AL_PICT_INFO_END_FRM = 0x00000010;
static const uint32_t AL_PICT_INFO_END_SRC = 0x00000020;
static const uint32_t AL_PICT_INFO_USE_LT = 0x00000040;
static const uint32_t AL_PICT_INFO_IS_GOLDREF = 0x0000080;
static const uint32_t AL_PICT_INFO_IS_SKIP = 0x0000100;

static const uint32_t AL_PICT_INFO_NOT_SHOWABLE = 0x80000000;
#define AL_IS_SHOWABLE(PicInfo) (!((PicInfo).uFlags & AL_PICT_INFO_NOT_SHOWABLE))

#define AL_IS_IDR(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_IS_IDR)
#define AL_IS_REF(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_IS_REF)
#define AL_SCN_CHG(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_SCN_CHG)
#define AL_USE_LT(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_USE_LT)
#define AL_END_SRC(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_END_SRC)
#define AL_IS_GOLDREF(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_IS_GOLDREF)
#define AL_IS_SKIP(PicInfo) ((PicInfo).uFlags & AL_PICT_INFO_IS_SKIP)

/*************************************************************************//*!
   \brief Picture informations
*****************************************************************************/
typedef struct AL_t_PictureInfo
{
  uint32_t uSrcOrder; /*!< Source picture number in display order */
  uint32_t uFlags; /*! IsIDR, IsRef, SceneChange ... */
  int32_t iPOC;
  int32_t iFrameNum;
  AL_ESliceType eType;
  AL_EPicStruct ePicStruct;
  AL_EMarkingRef eMarking;
  uint8_t uTempId;

  bool bForceLT[2]; /*!< Specifies if a following reference picture need to be markes as long-term */

  int32_t iDpbOutputDelay;
  uint8_t uRefPicSetIdx;
  int8_t iQpOffset;
  int iRecoveryCnt;

  uint16_t uGdrPos; /*!< Gradual Refresh position */
  AL_EGdrMode eGdrMode; /*!< Gradual Refresh Mode */

  int iLastIdrId;

}AL_TPictureInfo;


/*************************************************************************//*!
   \brief Slice Parameters : Mimics structure for AVC IP registers
*****************************************************************************/
typedef struct AL_t_EncSliceParam
{
  // Reg 0
  uint8_t MinTUSize; // HEVC only
  uint8_t MaxTUSize;
  int8_t MinCUSize; // HEVC only
  uint8_t MaxCUSize;
  AL_ECodec Codec;
  bool bIsLastCmd;
  // Reg 1
  uint16_t PicWidth;
  uint16_t PicHeight;

  // Reg 2
  int8_t CuQpDeltaDepth;
  uint8_t MaxMergeCand;
  uint8_t CabacInitIdc;  // = CabacInitFlag in HEVC
  uint8_t EntropyMode; // unused for HEVC
  bool EntropySync;
//  AL_ESrcMode eSrcFmt;
  bool EnableFrmBufComp;
  uint8_t BitDepthLuma;
  uint8_t BitDepthChroma;
  AL_EChromaMode ChromaMode;
  bool ColocFromL0;
  bool DisIntra; // Debug only
  bool IntraPCM; // unused for encoder
  bool TemporalMVP; // = Direct temporal in AVC
  bool SkipTransfo;
  bool HighFreq;

  // Reg 3
  int8_t CbQpOffset; // VP9 iDCQpOffsetY
  int8_t CrQpOffset;
  int16_t SliceQP;
  bool ColocShow;
  bool RdoCostMode;
  bool WaveFront;
  bool Tile;
  AL_ESliceType SliceType;
  bool FullSkip;
  bool DependentSlice;

  // Reg 4
  int8_t tc_offset_div2; // = Alpha_offset_dic2 in AVC
  int8_t beta_offset_div2;
  bool DisLoopFilter;
  bool XSliceLoopFilter;
  uint8_t CoreId;

  // Reg 5
  uint32_t FirstSliceLCU;
  uint8_t NumRefIdxL1Minus1;
  uint8_t NumRefIdxL0Minus1;

  // Reg 6
  uint32_t LastLCU;
  bool MergeLTL0;
  bool MergeLTL1;
  // See Reg13 & 14 for RefIdx

  // Reg 7
  uint16_t TileWidth;
  uint16_t TileHeight;
  uint8_t TileNgbA;
  uint8_t TileNgbB;
  uint8_t TileNgbC;
  uint8_t TileNgbD;
  uint8_t TileNgbE;
  bool CrossTileLoopFilter;

  // Reg 8
  uint32_t FirstCoreLCU;
  uint16_t MeHrzRange;
  uint16_t MeVrtRange;
  bool FixPredictor; // Debug only

  // Reg 9
  int8_t PicCbQpOffset; // VP9 iDCQpOffsetUV
  int8_t PicCrQpOffset; // VP9 iACQpOffsetUV
  bool NoBackwardPredFlag; // HEVC only
  bool RefColocL0Flag; // AVC only
  bool RefColocL0LTFlag; // AVC only
  bool RefColocL1LTFlag; // AVC only
  bool EnableHwRateCtrl;
  bool DisPCMLoopFilter;
  bool StrongIntraSmooth; // HEVC only
  bool ConstrainedIntraPred;
  uint8_t WeightedPred; // unused for encoder yet
  uint8_t WeightedBiPred; // unused for encoder
  bool EnableMVPerBlock;
  bool DisableRecOut;
  bool DisableMVsOut;
  bool QPTableRelative;
  bool UseQPTable;
  bool EnableAutoQp;
  bool LoadAutoQpCtrl;
  bool UseLambdaTable;
  bool LoadLambdaTable;
  bool UseSclMtx;
  bool LoadSclMtx;

  // Reg 10
  uint32_t MaxBitPerLCU;
  uint16_t HdrSize; // SW only
  uint16_t L2CacheCapThreshold;

  // Reg 11
  uint16_t ClmnOffset;
  uint16_t ClmnWidth;
  uint8_t NumCore;
  bool SyncLeft;
  bool SyncRight;

  // Reg 12
  int32_t CurrentPOC;

  // Reg 13
  //TSliceRef RefA; // contains also the RefidxL0 of Reg 6

  // Reg 14
  //TSliceRef RefB; // contains also the RefidxL1 of Reg 6

  // Reg 15
  //TSliceRef Coloc;

  // Reg 16
  int32_t ColRef0POC;

  // Reg 17
  int32_t ColRef1POC;

  // Reg 18
  uint16_t MVHRange;
  uint16_t MVVRange;
  bool UseL2;
  bool ForceClip;
  // Reg 19
  uint8_t L2CacheTileHeight;
  uint32_t L2CacheMemOffset;
  uint8_t L2CacheXMin;
  uint8_t L2CacheXMax;

  // Reg 25
  uint16_t SliceSize;
  uint8_t HdrMaxSize;  // Number byte reserved between slice for header insertion

  // Reg 26
  AL_EGdrMode GdrMode;
  uint16_t GdrPos;



  // Reg 28
  bool Direct8x8Infer;
  bool Transform8x8;

  // Reg 30
  uint8_t SliceHdrLength; // AVC CAVLC only
  uint32_t NumLcuBlk2;

  // Reg 31
  uint32_t SliceHdrData;

  // Shortcuts

  uint32_t LastTileLcu;
  uint16_t LcuWidth;
  uint16_t LcuHeight;
  uint8_t BitDepth; // max(BitDepthLuma, BitDepthChroma)

  uint8_t InterPFilter;
  bool UseGMV;
  int16_t GMV[2][2];

}AL_TEncSliceParam;

/*************************************************************************//*!
   \brief Mimics structure described in spec sec. 7.3.3
*****************************************************************************/
#define AL_MAX_REFERENCE_PICTURE_REORDER 1
typedef struct t_AvcSliceHeader
{
  uint16_t num_line_in_slice;
  int first_mb_in_slice;
  uint8_t slice_type; // 0 = P, 1 = B, 2 = I.
  uint8_t pic_parameter_set_id;
  uint8_t field_pic_flag;
  int frame_num;
  int redundant_pic_cnt;
  int idr_pic_id;
  uint32_t pic_order_cnt_lsb;
  int delta_pic_order_cnt_bottom;
  int delta_pic_order_cnt[2];
  uint8_t bottom_field_flag;
  uint8_t nal_ref_idc;
  uint8_t direct_spatial_mv_pred_flag;
  uint8_t num_ref_idx_active_override_flag;
  int num_ref_idx_l0_active_minus1; // This member should always contain the current num_ref_idx_l0_active_minus1 applicable for this slice, even when num_ref_idx_active_override_flag == 1.
  int num_ref_idx_l1_active_minus1; // This member should always contain the current num_ref_idx_l1_active_minus1 applicable for this slice, even when num_ref_idx_active_override_flag == 1.

  // reference picture list reordering syntax elements
  uint8_t reordering_of_pic_nums_idc_l0[AL_MAX_REFERENCE_PICTURE_REORDER];
  uint8_t reordering_of_pic_nums_idc_l1[AL_MAX_REFERENCE_PICTURE_REORDER];
  int abs_diff_pic_num_minus1_l0[AL_MAX_REFERENCE_PICTURE_REORDER];
  int abs_diff_pic_num_minus1_l1[AL_MAX_REFERENCE_PICTURE_REORDER];
  int long_term_pic_num_l0[AL_MAX_REFERENCE_PICTURE_REORDER];
  int long_term_pic_num_l1[AL_MAX_REFERENCE_PICTURE_REORDER];
  uint8_t ref_pic_list_reordering_flag_l0;
  uint8_t ref_pic_list_reordering_flag_l1;

  // prediction weight table syntax elements
  //AL_TWPTable pred_weight_table;

  // reference picture marking syntax elements
  uint8_t memory_management_control_operation[32];
  int difference_of_pic_nums_minus1[32];
  int long_term_pic_num[32];
  int long_term_frame_idx[32];
  int max_long_term_frame_idx_plus1[32];

  uint8_t no_output_of_prior_pics_flag;
  uint8_t long_term_reference_flag;
  uint8_t adaptive_ref_pic_marking_mode_flag;
  uint8_t cabac_init_idc;
  int slice_qp_delta;
  uint8_t disable_deblocking_filter_idc;
  uint8_t nal_unit_type;
  int8_t slice_alpha_c0_offset_div2;
  int8_t slice_beta_offset_div2;
  int slice_header_length;

  const AL_TAvcPps* pPPS;
  const AL_TAvcSps* pSPS;
}AL_TAvcSliceHdr;

void InitHeaderCfg(uint16_t width, uint16_t height);
void generateSPS(AL_TAvcSps* pSPS);
void writeSps(AL_TBitStreamLite* pBS, AL_TAvcSps const* pSps);
void generatePPS(AL_TAvcPps* pPPS, AL_TAvcSps const* pSPS);
void writePps(AL_TBitStreamLite* pBS, AL_TAvcPps const* pPps);
void FlushNAL(AL_TBitStreamLite* pStream, uint8_t uNUT, AL_TNalHeader const* pHeader, uint8_t* pDataInNAL, int iBitsInNAL);
void FillSliceParam(AL_TEncSliceParam* pSP, AL_TPictureInfo* pPI, AL_ESliceType SliceType, int32_t CurPOC, int32_t FrameNo, bool bIDR);
uint32_t generateSliceHeader(AL_TBitStreamLite* pBS, AL_TPictureInfo* pPI, AL_TEncSliceParam* pSP, uint8_t* pBufAddrs, uint32_t uSliceOffset, bool bOverwriteHeader);



#endif


