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
//#include <k510.h>
//#include <interrupt.h>
#include <h264.h>
//#include <cache.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
// #include <h264.h>




////////////////////////////////////////////
//#define UINT32_MAX (0xFFFFFFFF)
#define AL_MAX_NUM_CPB 32

#define ROUND_UP_POWER_OF_TWO(value, n) (((value) + (1 << (n)) - 1) >> (n))

#define Rtos_Memcpy(d, s, n)         __builtin_memcpy ((d), (s), (n))

#define AL_GET_CS_FLAGS(Prof) ((Prof & 0x00FFFF00) >> 8)
#define AL_AVC_NO_MMCO -1

static __inline int AL_GET_PROFILE_IDC(AL_EProfile eProfile)
{
  return eProfile & 0x000000FF;
}

AL_TEncSettings gEncSetting;

void InitHeaderCfg(uint16_t width, uint16_t height)
{
    gEncSetting.uEncWidth = width;
    gEncSetting.uEncHeight = height;

    gEncSetting.eScalingList = AL_SCL_FLAT;
    
    gEncSetting.eProfile = AL_PROFILE_AVC_HIGH;
    gEncSetting.uLevel = 42; 
    gEncSetting.bitDepth = 8;
    gEncSetting.uMaxCuSize = 4; //16x16
    gEncSetting.eChromaMode = AL_CHROMA_4_2_0;
    gEncSetting.eAspectRatio = AL_ASPECT_RATIO_AUTO;

    gEncSetting.eColourDescription = AL_COLOUR_DESC_BT_709;
    gEncSetting.eTransferCharacteristics = AL_TRANSFER_CHARAC_UNSPECIFIED;
    gEncSetting.eColourMatrixCoeffs = AL_COLOUR_MAT_COEFF_UNSPECIFIED;

    gEncSetting.uFrameRate = 30;
    gEncSetting.uClkRatio = 1000;

    gEncSetting.eRCMode = AL_RC_CONST_QP;
    gEncSetting.uMaxBitRate = 3000000;
    gEncSetting.NumView = 1;

    gEncSetting.iCpbSize = 3;

    gEncSetting.eEntropyMode = AL_MODE_CABAC;

    gEncSetting.iCbPicQpOffset = 0;
    gEncSetting.iCrPicQpOffset = 0;
    gEncSetting.bConstrainedIntraPred = false;

    gEncSetting.iPpsInitQp = 26;
    gEncSetting.uCabacInitIdc = 0;
    gEncSetting.bEnableFrmBufComp = 0;

    gEncSetting.bDisLoopFilter = 0;
    gEncSetting.iTcOffset = -1;
    gEncSetting.iBetaOffset = -1;

    gEncSetting.eGdrMode = AL_GDR_OFF;
    gEncSetting.iSliceQP = 30;

    gEncSetting.iLastIdrId = -1;
    gEncSetting.uLog2_max_frame_num = 4;
    gEncSetting.uLog2_max_poc = 10;
}

/******************************************************************************/
/*************************** Default Scaling List *****************************/
/******************************************************************************/
typedef uint8_t AL_TMtx8x8[8 * 8];
typedef uint8_t AL_TMtx4x4[4 * 4];

// Table 7-3.
static const AL_TMtx4x4 AL_AVC_DefaultScalingLists4x4[2] =
{
  // Intra
  {
    6, 13, 20, 28,
    13, 20, 28, 32,
    20, 28, 32, 37,
    28, 32, 37, 42
  },
  // Inter
  {
    10, 14, 20, 24,
    14, 20, 24, 27,
    20, 24, 27, 30,
    24, 27, 30, 34
  },
};

// Table 7-4.
static const AL_TMtx8x8 AL_AVC_DefaultScalingLists8x8[2] =
{
  // Intra
  {
    6, 10, 13, 16, 18, 23, 25, 27,
    10, 11, 16, 18, 23, 25, 27, 29,
    13, 16, 18, 23, 25, 27, 29, 31,
    16, 18, 23, 25, 27, 29, 31, 33,
    18, 23, 25, 27, 29, 31, 33, 36,
    23, 25, 27, 29, 31, 33, 36, 38,
    25, 27, 29, 31, 33, 36, 38, 40,
    27, 29, 31, 33, 36, 38, 40, 42
  },
  // Inter.
  {
    9, 13, 15, 17, 19, 21, 22, 24,
    13, 13, 17, 19, 21, 22, 24, 25,
    15, 17, 19, 21, 22, 24, 25, 27,
    17, 19, 21, 22, 24, 25, 27, 28,
    19, 21, 22, 24, 25, 27, 28, 30,
    21, 22, 24, 25, 27, 28, 30, 32,
    22, 24, 25, 27, 28, 30, 32, 33,
    24, 25, 27, 28, 30, 32, 33, 35
  },
};


static const int32_t AL_DecScanBlock4x4[2][16] =
{
  { 0, 1, 4, 8, 5, 2, 3, 6, 9, 12, 13, 10, 7, 11, 14, 15 }, // Frame
  { 0, 4, 1, 8, 12, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 } // Field
};

static const int32_t AL_DecScanBlock8x8[2][64] =
{
  {
    0, 1, 8, 16, 9, 2, 3, 10,
    17, 24, 32, 25, 18, 11, 4, 5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13, 6, 7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63
  }, // Frame

  {
    0, 8, 16, 1, 9, 24, 32, 17,
    2, 25, 40, 48, 56, 33, 10, 3,
    18, 41, 49, 57, 26, 11, 4, 19,
    34, 42, 50, 58, 27, 12, 5, 20,
    35, 43, 51, 59, 28, 13, 6, 21,
    36, 44, 52, 60, 29, 14, 22, 37,
    45, 53, 61, 30, 7, 15, 38, 46,
    54, 62, 23, 31, 39, 47, 55, 63
  }, // Field
};

/***************************************************************************/
static __inline size_t BitsToBytes(size_t zBits)
{
  return (zBits + 7) / 8;
}

static __inline void writeData(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  uint32_t byteNum = pBS->iBitCount >> 3;
  uint8_t byteOffset = pBS->iBitCount & 7;

  assert(byteOffset + iNumBits <= 8);

  if(byteOffset == 0)
  {
    pBS->pData[byteNum] = uValue << (8 - iNumBits);
  }
  else
  {
    uint8_t bitsLeft = 8 - byteOffset;
    pBS->pData[byteNum] += uValue << (bitsLeft - iNumBits);
  }
}


/* Assume that iNumBits will be small enough to fit in current byte */
static void PutInByte(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  if(pBS->iBitCount + iNumBits <= pBS->iMaxBits)
    writeData(pBS, iNumBits, uValue);
  else
    pBS->isOverflow = true;
  pBS->iBitCount += iNumBits;
}

/******************************************************************************/
static void AL_BitStreamLite_PutU(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  assert(iNumBits == 32 || (uValue >> iNumBits) == 0);

  uint8_t numBitsToWrite = 8 - (pBS->iBitCount & 7);

  while(iNumBits > numBitsToWrite)
  {
    uint8_t byteValue = uValue >> (iNumBits - numBitsToWrite);
    PutInByte(pBS, numBitsToWrite, byteValue);
    uValue &= (0xffffffff >> numBitsToWrite);
    iNumBits -= numBitsToWrite;
    numBitsToWrite = 8 - (pBS->iBitCount & 7);
  }

  PutInByte(pBS, iNumBits, uValue);
}
/******************************************************************************/
static void AL_BitStreamLite_PutBits(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  assert(iNumBits == 32 || (uValue >> iNumBits) == 0);

  uint8_t numBitsToWrite = 8 - (pBS->iBitCount & 7);

  while(iNumBits > numBitsToWrite)
  {
    uint8_t byteValue = uValue >> (iNumBits - numBitsToWrite);
    PutInByte(pBS, numBitsToWrite, byteValue);
    uValue &= (0xffffffff >> numBitsToWrite);
    iNumBits -= numBitsToWrite;
    numBitsToWrite = 8 - (pBS->iBitCount & 7);
  }

  PutInByte(pBS, iNumBits, uValue);
}


/******************************************************************************/
static void putVclBits(AL_TBitStreamLite* pBS, uint32_t uCodeLength, uint32_t uValue)
{
  if(uCodeLength == 1)
  {
    AL_BitStreamLite_PutU(pBS, 1, 1);
  }
  else
  {
    uint32_t uInfoLength = (uCodeLength - 1) / 2;
    int32_t iBits = uValue + 1 - (1 << uInfoLength);

    AL_BitStreamLite_PutBits(pBS, uInfoLength, 0);
    AL_BitStreamLite_PutBits(pBS, 1, 1);
    AL_BitStreamLite_PutBits(pBS, uInfoLength, iBits);
  }
}

#if defined(__ICL)
#define bit_scan_reverse _bit_scan_reverse
#else
uint32_t bit_scan_reverse_soft(int32_t NN)
{
  int32_t i = -1;

  while(NN)
  {
    NN >>= 1;
    i++;
  }

  return i;
}

#define bit_scan_reverse bit_scan_reverse_soft
#endif

/******************************************************************************/
// Writes one Exp-Golomb code to the bitstream.
// Automatically calculates the required code length.
static void AL_BitStreamLite_PutUE(AL_TBitStreamLite* pBS, uint32_t uValue)
{
  // 1 - Compute code length.
  uint32_t uCodeLength = 1 + (bit_scan_reverse(uValue + 1) << 1);

  // 2 - Write code.
  putVclBits(pBS, uCodeLength, uValue);
}



/******************************************************************************/
static void AL_BitStreamLite_PutSE(AL_TBitStreamLite* pBS, int32_t iValue)
{
  AL_BitStreamLite_PutUE(pBS, 2 * (iValue > 0 ? iValue : -iValue) - (iValue > 0));
}

/****************************************************************************/
static void fillScalingList(AL_TEncSettings const* pSettings, AL_TAvcSps* pSPS, int iSizeId, int iMatrixId, int iDir, uint8_t* uSLpresentFlag)
{
  uint8_t* pSL = pSPS->scaling_list_param.ScalingList[iSizeId][iMatrixId];

  if(pSettings->SclFlag[iSizeId][iMatrixId] != 0)
  {
    *uSLpresentFlag = 1; // scaling list present in file
    Rtos_Memcpy(pSL, pSettings->ScalingList[iSizeId][iMatrixId], iSizeId == 0 ? 16 : 64);
    return;
  }

  *uSLpresentFlag = 0;

  if(iSizeId == 0)
  {
    if(iMatrixId == 0 || iMatrixId == 3)
      Rtos_Memcpy(pSL, AL_AVC_DefaultScalingLists4x4[iDir], 16);
    else
    {
      if(&pSPS->seq_scaling_list_present_flag[iMatrixId - 1])
      {
        *uSLpresentFlag = 1;
        Rtos_Memcpy(pSL, pSPS->scaling_list_param.ScalingList[iSizeId][iMatrixId - 1], 16);
      }
      else
        Rtos_Memcpy(pSL, AL_AVC_DefaultScalingLists4x4[iDir], 16);
    }
  }
  else
    Rtos_Memcpy(pSL, AL_AVC_DefaultScalingLists8x8[iDir], 64);
}

/****************************************************************************/
static void AL_AVC_SelectScalingList(AL_TAvcSps* pSPS, AL_TEncSettings const* pSettings)
{
  AL_EScalingList eScalingList = pSettings->eScalingList;

  if(eScalingList == AL_SCL_FLAT)
  {
    pSPS->seq_scaling_matrix_present_flag = 0;

    for(int i = 0; i < 8; i++)
      pSPS->seq_scaling_list_present_flag[i] = 0;

    return;
  }

  pSPS->seq_scaling_matrix_present_flag = 1;

  if(eScalingList == AL_SCL_CUSTOM)
  {
    for(int iDir = 0; iDir < 2; ++iDir)
    {
      fillScalingList(pSettings, pSPS, 1, iDir * 3, iDir, &pSPS->seq_scaling_list_present_flag[iDir + 6]);
      fillScalingList(pSettings, pSPS, 0, iDir * 3, iDir, &pSPS->seq_scaling_list_present_flag[iDir * 3]);
      fillScalingList(pSettings, pSPS, 0, iDir * 3 + 1, iDir, &pSPS->seq_scaling_list_present_flag[iDir * 3 + 1]);
      fillScalingList(pSettings, pSPS, 0, iDir * 3 + 2, iDir, &pSPS->seq_scaling_list_present_flag[iDir * 3 + 2]);
    }
  }
  else if(eScalingList == AL_SCL_DEFAULT)
  {
    for(int i = 0; i < 8; i++)
      pSPS->seq_scaling_list_present_flag[i] = 0;

    for(int iDir = 0; iDir < 2; ++iDir)
    {
      Rtos_Memcpy(pSPS->scaling_list_param.ScalingList[1][3 * iDir], AL_AVC_DefaultScalingLists8x8[iDir], 64);
      Rtos_Memcpy(pSPS->scaling_list_param.ScalingList[0][3 * iDir], AL_AVC_DefaultScalingLists4x4[iDir], 16);
      Rtos_Memcpy(pSPS->scaling_list_param.ScalingList[0][(3 * iDir) + 1], AL_AVC_DefaultScalingLists4x4[iDir], 16);
      Rtos_Memcpy(pSPS->scaling_list_param.ScalingList[0][(3 * iDir) + 2], AL_AVC_DefaultScalingLists4x4[iDir], 16);
    }
  }
}

/****************************************************************************/
static void AL_Reduction(uint32_t* pN, uint32_t* pD)
{
  static const int Prime[] =
  {
    2, 3, 5, 7, 11, 13, 17, 19, 23
  };
  const int iNumPrime = sizeof(Prime) / sizeof(int);

  for(int i = 0; i < iNumPrime; i++)
  {
    while(((*pN % Prime[i]) == 0) && ((*pD % Prime[i]) == 0))
    {
      *pN /= Prime[i];
      *pD /= Prime[i];
    }
  }
}
/****************************************************************************/
static void AL_Decomposition(uint32_t* y, uint8_t* x)
{
  *x = 0;

  while(*y != 0 && *x < 15)
  {
    if(*y % 2 == 0)
    {
      *y >>= 1;
      (*x)++;
    }
    else
      break;
  }

  (*y)--;
}

/***************************************************************************/
static __inline int RoundUp(int iVal, int iRnd)
{
  return iVal >= 0 ? ((iVal + iRnd - 1) / iRnd) * iRnd : (iVal / iRnd) * iRnd;
}

/****************************************************************************/
static void AL_UpdateAspectRatio(AL_TVuiParam* pVuiParam, uint32_t uWidth, uint32_t uHeight, AL_EAspectRatio eAspectRatio)
{
  bool bAuto = (eAspectRatio == AL_ASPECT_RATIO_AUTO);
  uint32_t uHeightRnd = RoundUp(uHeight, 16);

  pVuiParam->aspect_ratio_info_present_flag = 0;
  pVuiParam->aspect_ratio_idc = 0;
  pVuiParam->sar_width = 0;
  pVuiParam->sar_height = 0;

  if(eAspectRatio == AL_ASPECT_RATIO_NONE)
    return;

  if(bAuto)
  {
    if(uWidth <= 720)
      eAspectRatio = AL_ASPECT_RATIO_4_3;
    else
      eAspectRatio = AL_ASPECT_RATIO_16_9;
  }

  if(eAspectRatio == AL_ASPECT_RATIO_4_3)
  {
    if(uWidth == 352)
    {
      if(uHeight == 240)
        pVuiParam->aspect_ratio_idc = 3;
      else if(uHeight == 288)
        pVuiParam->aspect_ratio_idc = 2;
      else if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 7;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 6;
    }
    else if(uWidth == 480)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 11;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 10;
    }
    else if(uWidth == 528)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 5;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 4;
    }
    else if(uWidth == 640)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 1;
    }
    else if(uWidth == 720)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 3;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 2;
    }
    else if(uWidth == 1440)
    {
      if(uHeightRnd == 1088)
        pVuiParam->aspect_ratio_idc = 1;
    }
  }
  else if(eAspectRatio == AL_ASPECT_RATIO_16_9)
  {
    if(uWidth == 352)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 8;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 9;
    }
    else if(uWidth == 480)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 7;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 6;
    }
    else if(uWidth == 528)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 13;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 12;
    }
    else if(uWidth == 720)
    {
      if(uHeight == 480)
        pVuiParam->aspect_ratio_idc = 5;
      else if(uHeight == 576)
        pVuiParam->aspect_ratio_idc = 4;
    }
    else if(uWidth == 960)
    {
      if(uHeightRnd == 1088)
        pVuiParam->aspect_ratio_idc = 16;
    }
    else if(uWidth == 1280)
    {
      if(uHeight == 720)
        pVuiParam->aspect_ratio_idc = 1;
      else if(uHeightRnd == 1088)
        pVuiParam->aspect_ratio_idc = 15;
    }
    else if(uWidth == 1440)
    {
      if(uHeightRnd == 1088)
        pVuiParam->aspect_ratio_idc = 14;
    }
    else if(uWidth == 1920)
    {
      if(uHeightRnd == 1088)
        pVuiParam->aspect_ratio_idc = 1;
    }
  }
  else if(eAspectRatio == AL_ASPECT_RATIO_1_1)
    pVuiParam->aspect_ratio_idc = 1;

  if((pVuiParam->aspect_ratio_idc == 0) && !bAuto)
  {
    uint32_t uW = uWidth;
    uint32_t uH = uHeight;

    if(eAspectRatio == AL_ASPECT_RATIO_4_3)
    {
      uW *= 3;
      uH *= 4;
    }
    else if(eAspectRatio == AL_ASPECT_RATIO_16_9)
    {
      uW *= 9;
      uH *= 16;
    }

    if(uH != uW)
    {
      AL_Reduction(&uW, &uH);

      pVuiParam->sar_width = uH;
      pVuiParam->sar_height = uW;
      pVuiParam->aspect_ratio_idc = 255;
    }
    else
      pVuiParam->aspect_ratio_idc = 1;
  }

  if(pVuiParam->aspect_ratio_idc)
    pVuiParam->aspect_ratio_info_present_flag = 1;
}

/****************************************************************************/
static void AL_AVC_GenerateSPS_Resolution(AL_TAvcSps* pSPS, uint16_t uWidth, uint16_t uHeight, uint8_t uMaxCuSize, AL_EAspectRatio eAspectRatio)
{
  int iMBWidth = ROUND_UP_POWER_OF_TWO(uWidth, uMaxCuSize);
  int iMBHeight = ROUND_UP_POWER_OF_TWO(uHeight, uMaxCuSize);

  int iWidthDiff = (iMBWidth << uMaxCuSize) - uWidth;
  int iHeightDiff = (iMBHeight << uMaxCuSize) - uHeight;

  AL_EChromaMode eChromaMode = gEncSetting.eChromaMode;

  int iCropUnitX = eChromaMode == AL_CHROMA_4_2_0 || eChromaMode == AL_CHROMA_4_2_2 ? 2 : 1;
  int iCropUnitY = eChromaMode == AL_CHROMA_4_2_0 ? 2 : 1;

  pSPS->pic_width_in_mbs_minus1 = iMBWidth - 1;

  // When frame_mbs_only_flag == 0, height in MB is always counted for a *field* picture,
  // even if we are encoding frame pictures
  // (see spec sec.7.4.2.1 and eq.7-15)
  pSPS->pic_height_in_map_units_minus1 = iMBHeight - 1;

  pSPS->frame_crop_left_offset = 0;
  pSPS->frame_crop_right_offset = iWidthDiff / iCropUnitX;
  pSPS->frame_crop_top_offset = 0;
  pSPS->frame_crop_bottom_offset = iHeightDiff / iCropUnitY;
  pSPS->frame_cropping_flag = ((pSPS->frame_crop_right_offset > 0)
                               || (pSPS->frame_crop_bottom_offset > 0)) ? 1 : 0;

  AL_UpdateAspectRatio(&pSPS->vui_param, uWidth, uHeight, eAspectRatio);
}

static int AL_H273_ColourDescToColourPrimaries(AL_EColourDescription colourDesc)
{
  switch(colourDesc)
  {
  case AL_COLOUR_DESC_RESERVED: return 0;
  case AL_COLOUR_DESC_BT_709: return 1;
  case AL_COLOUR_DESC_UNSPECIFIED: return 2;
  case AL_COLOUR_DESC_BT_470_NTSC: return 4;
  case AL_COLOUR_DESC_BT_601_PAL: return 5;
  case AL_COLOUR_DESC_BT_601_NTSC: return 6;
  case AL_COLOUR_DESC_SMPTE_240M: return 7;
  case AL_COLOUR_DESC_GENERIC_FILM: return 8;
  case AL_COLOUR_DESC_BT_2020: return 9;
  case AL_COLOUR_DESC_SMPTE_ST_428: return 10;
  case AL_COLOUR_DESC_SMPTE_RP_431: return 11;
  case AL_COLOUR_DESC_SMPTE_EG_432: return 12;
  case AL_COLOUR_DESC_EBU_3213: return 22;
  case AL_COLOUR_DESC_MAX_ENUM: assert(0);
  }

  return 2;
}



/****************************************************************************/
static void AL_AVC_UpdateHrdParameters(AL_TAvcSps* pSPS, AL_TSubHrdParam* pSubHrdParam, int const iCpbSize)
{
  pSubHrdParam->bit_rate_value_minus1[0] = (gEncSetting.uMaxBitRate / gEncSetting.NumView) >> 6;
  pSPS->vui_param.hrd_param.cpb_cnt_minus1[0] = 0;
  AL_Decomposition(&(pSubHrdParam->bit_rate_value_minus1[0]), &pSPS->vui_param.hrd_param.bit_rate_scale);

  assert(pSubHrdParam->bit_rate_value_minus1[0] <= (UINT32_MAX - 1));

  pSubHrdParam->cpb_size_value_minus1[0] = iCpbSize >> 4;
  AL_Decomposition(&(pSubHrdParam->cpb_size_value_minus1[0]), &pSPS->vui_param.hrd_param.cpb_size_scale);

  assert(pSubHrdParam->cpb_size_value_minus1[0] <= (UINT32_MAX - 1));

  pSubHrdParam->cbr_flag[0] = (gEncSetting.eRCMode == AL_RC_CBR) ? 1 : 0;

  pSPS->vui_param.hrd_param.initial_cpb_removal_delay_length_minus1 = 31; // int(log((double)iCurrDelay) / log(2.0));
  pSPS->vui_param.hrd_param.au_cpb_removal_delay_length_minus1 = 31;
  pSPS->vui_param.hrd_param.dpb_output_delay_length_minus1 = 31;
  pSPS->vui_param.hrd_param.time_offset_length = 0;
}


static const int AL_AVC_SLICE_TYPE[3] =
{
  1, 0, 2
};

/******************************************************************************/
static void AL_BitStreamLite_PutBit(AL_TBitStreamLite* pBS, uint8_t iBit)
{
  assert((iBit == 0) || (iBit == 1));
  AL_BitStreamLite_PutBits(pBS, 1, iBit);
}

/******************************************************************************/
static void AL_BitStreamLite_AlignWithBits(AL_TBitStreamLite* pBS, uint8_t iBit)
{
  while(pBS->iBitCount % 8 != 0)
    AL_BitStreamLite_PutBit(pBS, iBit);
}

/******************************************************************************/
static uint32_t SliceHdrFlushNAL(uint8_t* pStream, AL_ECodec eCodec, uint8_t uNUT, uint8_t* pData, int uNumBytes, uint8_t uNalIdc, bool bFirstSliceInAU)
{
  uint8_t uNalHdrFstByte = 0, uNalHdrSecByte = 0;

#if (defined(ANDROID) || defined(__ANDROID_API__))
  bool bZeroByte = true;
#else
  bool bZeroByte = bFirstSliceInAU;
#endif
  switch(eCodec)
  {
  case AL_CODEC_AVC:
    uNalHdrFstByte = ((uNalIdc & 0x03) << 5) | (uNUT & 0x1F);
    bZeroByte |= ((eCodec == AL_CODEC_AVC) && (uNUT >= AL_AVC_NUT_SPS) && (uNUT <= AL_AVC_NUT_SUB_SPS));
    break;
  default:
    break;
  }

  pData += uNumBytes - 1;

  uint8_t* pTmp = --pStream;

  while(uNumBytes >= 3)
  {
    if(pData[-2] == 0 && pData[-1] == 0 && (pData[0] & 0xFC) == 0)
    {
      *pTmp-- = *pData--;
      *pTmp-- = 0x03;
      *pTmp-- = *pData--;
      *pTmp-- = *pData--;
      uNumBytes -= 3;
    }
    else
    {
      *pTmp-- = *pData--;
      --uNumBytes;
    }
  }

  while(uNumBytes-- > 0)
    *pTmp-- = *pData--;

  if(eCodec == AL_CODEC_HEVC)
    *pTmp-- = uNalHdrSecByte;
  *pTmp-- = uNalHdrFstByte;

  *pTmp-- = 0x01;
  *pTmp-- = 0x00;
  *pTmp-- = 0x00;

  if(bZeroByte)
    *pTmp-- = 0x00;

  return pStream - pTmp;
}

/******************************************************************************/
static void WriteAvcSliceSegmentHdr(AL_TBitStreamLite* pBS, AL_TAvcSliceHdr const* pSH)
{

  AL_BitStreamLite_PutUE(pBS, pSH->first_mb_in_slice);
  assert(pSH->slice_type < 3);
  int iSliceType = AL_AVC_SLICE_TYPE[pSH->slice_type];
  AL_BitStreamLite_PutUE(pBS, iSliceType);
  AL_BitStreamLite_PutUE(pBS, pSH->pic_parameter_set_id);

  uint32_t uLog2FrameNum = 4;
  bool bIsIDR = (pSH->nal_unit_type == AL_AVC_NUT_VCL_IDR);
  uint32_t uFrameNum = bIsIDR ? 0 : (pSH->frame_num & ((1 << uLog2FrameNum) - 1));
  AL_BitStreamLite_PutU(pBS, uLog2FrameNum, uFrameNum);

  if(bIsIDR)
    AL_BitStreamLite_PutUE(pBS, pSH->idr_pic_id);

  AL_BitStreamLite_PutU(pBS, 10, pSH->pic_order_cnt_lsb); // PEY

  if(pSH->slice_type == AL_SLICE_B)
    AL_BitStreamLite_PutU(pBS, 1, pSH->direct_spatial_mv_pred_flag);

  if(pSH->slice_type != AL_SLICE_I)
  {
    AL_BitStreamLite_PutU(pBS, 1, pSH->num_ref_idx_active_override_flag);

    if(pSH->num_ref_idx_active_override_flag)
    {
      AL_BitStreamLite_PutUE(pBS, pSH->num_ref_idx_l0_active_minus1);

      if(pSH->slice_type == AL_SLICE_B)
        AL_BitStreamLite_PutUE(pBS, pSH->num_ref_idx_l1_active_minus1);
    }
  }

  if(pSH->slice_type != AL_SLICE_I)
  {
    AL_BitStreamLite_PutU(pBS, 1, pSH->ref_pic_list_reordering_flag_l0);

    if(pSH->ref_pic_list_reordering_flag_l0)
    {
      //AL_TReorderInfo const* pInfo = pRI->tReorder[0].tReorderList;
      //WriteAvcReorderList(pBS, pInfo);
    }
  }

  if(pSH->nal_ref_idc != 0)
  {
    if(bIsIDR)
    {
      AL_BitStreamLite_PutU(pBS, 1, pSH->no_output_of_prior_pics_flag);
      AL_BitStreamLite_PutU(pBS, 1, pSH->long_term_reference_flag);
    }
    else
    {
      AL_BitStreamLite_PutU(pBS, 1, pSH->adaptive_ref_pic_marking_mode_flag);

      if(pSH->adaptive_ref_pic_marking_mode_flag)
      {
          assert(0);
      /*
        if(pRI->iMMCORemovePicNum != AL_AVC_NO_MMCO)
        {
          AL_BitStreamLite_PutUE(pBS, 1);
          AL_BitStreamLite_PutUE(pBS, pPP->tPicInfo.iFrameNum - pRI->iMMCORemovePicNum - 1);
        }

        if(pSH->long_term_reference_flag || pRI->bRmLT)
        {
          AL_BitStreamLite_PutUE(pBS, 4); // transmit max_long_term_frame_idx_plus1
          AL_BitStreamLite_PutUE(pBS, 1); // max_long_term_frame_idx_plus1

          if(pRI->bRmLT)
          {
            AL_BitStreamLite_PutUE(pBS, 2); // force long_term removal
            AL_BitStreamLite_PutUE(pBS, 0); // long_term_pic_num
          }

          if(pSH->long_term_reference_flag)
          {
            AL_BitStreamLite_PutUE(pBS, 6); // replace older long term
            AL_BitStreamLite_PutUE(pBS, 0); // long_term_frame_idx
          }
        }
        AL_BitStreamLite_PutUE(pBS, 0); // end MMCO
        */
      }
      
    }
  }

  if((gEncSetting.eEntropyMode == AL_MODE_CABAC) && pSH->slice_type != AL_SLICE_I)
  {
    /*m_iLastQP = pPps->pic_init_qp_minus26 + 26 + pSH->slice_qp_delta;
       // Update contexts: choose a cabac_init_idc
       UpdateCabacInitIdc(sh, Clip3(m_iLastQP, 0, 51));*/
    AL_BitStreamLite_PutUE(pBS, pSH->cabac_init_idc);
  }
  AL_BitStreamLite_PutSE(pBS, pSH->slice_qp_delta);

  if(1)//PPS->deblocking_filter_control_present_flag
  {
    AL_BitStreamLite_PutUE(pBS, pSH->disable_deblocking_filter_idc);

    if(pSH->disable_deblocking_filter_idc != 1)
    {
      AL_BitStreamLite_PutSE(pBS, pSH->slice_alpha_c0_offset_div2);
      AL_BitStreamLite_PutSE(pBS, pSH->slice_beta_offset_div2);
    }
  }

  if(gEncSetting.eEntropyMode == AL_MODE_CABAC)
    AL_BitStreamLite_AlignWithBits(pBS, 1);
}



/****************************************************************************/
static const size_t AL_SL_INTRA = 0;
static const size_t AL_SL_INTER = 1;
/******************************************************************************/
static int writeScalingList(AL_TBitStreamLite* pBS, uint8_t const* pScalingList, int iSize)
{
  int32_t const* pDecScanBlock = (iSize == 16) ? AL_DecScanBlock4x4[0] : AL_DecScanBlock8x8[0];
  int32_t iLastScale = 8;
  uint8_t iNextScale = 8;
  /* if iSize == 0, we return an error code */
  int iUseDefault = -1;

  for(int j = 0; j < iSize; j++)
  {
    int i = pDecScanBlock[j];

    if(iNextScale != 0)
    {
      int32_t iDeltaScale = pScalingList[i] - iLastScale;

      if(iDeltaScale > 127)
        iDeltaScale -= 256;
      else if(iDeltaScale < -128)
        iDeltaScale += 256;

      AL_BitStreamLite_PutSE(pBS, iDeltaScale);
      iNextScale = pScalingList[i];
      iUseDefault = (i == 0 && iNextScale == 0);
    }
    // pScalingList[i] = (iNextScale == 0) ? iLastScale : iNextScale;
    iLastScale = pScalingList[i];
  }

  return iUseDefault;
}

/******************************************************************************/
static void writeScalingMatrix(AL_TBitStreamLite* pBS, uint8_t isScalingMatrixPresent, AL_TAvcSps const* pSps)
{
  if(isScalingMatrixPresent == 0)
    return;

  for(int i = 0; i < 8; i++)
  {
    AL_BitStreamLite_PutU(pBS, 1, pSps->seq_scaling_list_present_flag[i]);

    if(pSps->seq_scaling_list_present_flag[i] == 0)
      continue;

    int row = i < 6 ? 0 : 1;
    int size = i < 6 ? 16 : 64;

    int column = 0;
    switch(i)
    {
    case 0:
    case 1:
    case 2:
      column = 3 * AL_SL_INTRA + i;
      break;
    case 3:
    case 4:
    case 5:
      column = 3 * AL_SL_INTER + (i - 3);
      break;
    case 6:
      column = 3 * AL_SL_INTRA;
      break;
    case 7:
      column = 3 * AL_SL_INTER;
      break;
    default:
      assert(0);
    }

    writeScalingList(pBS, pSps->scaling_list_param.ScalingList[row][column], size);
  }
}

/******************************************************************************/
static void writeHrdParam(AL_TBitStreamLite* pBS, AL_THrdParam const* pHrd, AL_TSubHrdParam const* pSubHrd)
{
  assert(pHrd->cpb_cnt_minus1[0] < AL_MAX_NUM_CPB);

  AL_BitStreamLite_PutUE(pBS, pHrd->cpb_cnt_minus1[0]);
  AL_BitStreamLite_PutU(pBS, 4, pHrd->bit_rate_scale);
  AL_BitStreamLite_PutU(pBS, 4, pHrd->cpb_size_scale);

  for(uint32_t uSchedSelIdx = 0; uSchedSelIdx <= pHrd->cpb_cnt_minus1[0]; uSchedSelIdx++)
  {
    AL_BitStreamLite_PutUE(pBS, pSubHrd->bit_rate_value_minus1[uSchedSelIdx]);
    AL_BitStreamLite_PutUE(pBS, pSubHrd->cpb_size_value_minus1[uSchedSelIdx]);
    AL_BitStreamLite_PutU(pBS, 1, pSubHrd->cbr_flag[uSchedSelIdx]);
  }

  AL_BitStreamLite_PutU(pBS, 5, pHrd->initial_cpb_removal_delay_length_minus1);
  AL_BitStreamLite_PutU(pBS, 5, pHrd->au_cpb_removal_delay_length_minus1);
  AL_BitStreamLite_PutU(pBS, 5, pHrd->dpb_output_delay_length_minus1);
  AL_BitStreamLite_PutU(pBS, 5, pHrd->time_offset_length);
}

/******************************************************************************/
static void writeSpsData(AL_TBitStreamLite* pBS, AL_TAvcSps const* pSps)
{
  // 1 - Write SPS following spec 7.3.2.1.1

  AL_BitStreamLite_PutU(pBS, 8, pSps->profile_idc);
  AL_BitStreamLite_PutU(pBS, 1, pSps->constraint_set0_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->constraint_set1_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->constraint_set2_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->constraint_set3_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->constraint_set4_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->constraint_set5_flag);
  AL_BitStreamLite_PutU(pBS, 2, 0);
  AL_BitStreamLite_PutU(pBS, 8, pSps->level_idc);
  AL_BitStreamLite_PutUE(pBS, pSps->seq_parameter_set_id);

  if(
    (pSps->profile_idc == AVC_PROFILE_IDC_HIGH)
    || (pSps->profile_idc == AVC_PROFILE_IDC_HIGH10)
    || (pSps->profile_idc == AVC_PROFILE_IDC_HIGH_422)
    || (pSps->profile_idc == AVC_PROFILE_IDC_HIGH_444_PRED)
    || (pSps->profile_idc == AVC_PROFILE_IDC_CAVLC_444)
    || (pSps->profile_idc == 83) || (pSps->profile_idc == 86)
    || (pSps->profile_idc == 118) || (pSps->profile_idc == 128)
    )
  {
    AL_BitStreamLite_PutUE(pBS, pSps->chroma_format_idc);
    assert(pSps->chroma_format_idc != 3);
    AL_BitStreamLite_PutUE(pBS, pSps->bit_depth_luma_minus8);
    AL_BitStreamLite_PutUE(pBS, pSps->bit_depth_chroma_minus8);
    AL_BitStreamLite_PutU(pBS, 1, pSps->qpprime_y_zero_transform_bypass_flag);
    AL_BitStreamLite_PutU(pBS, 1, pSps->seq_scaling_matrix_present_flag);

    writeScalingMatrix(pBS, pSps->seq_scaling_matrix_present_flag, pSps);
  }

  AL_BitStreamLite_PutUE(pBS, pSps->log2_max_frame_num_minus4);
  AL_BitStreamLite_PutUE(pBS, pSps->pic_order_cnt_type);

  if(pSps->pic_order_cnt_type == 0)
    AL_BitStreamLite_PutUE(pBS, pSps->log2_max_pic_order_cnt_lsb_minus4);

  assert(pSps->pic_order_cnt_type != 1);

  AL_BitStreamLite_PutUE(pBS, pSps->max_num_ref_frames);
  AL_BitStreamLite_PutU(pBS, 1, pSps->gaps_in_frame_num_value_allowed_flag);
  AL_BitStreamLite_PutUE(pBS, pSps->pic_width_in_mbs_minus1);
  AL_BitStreamLite_PutUE(pBS, pSps->pic_height_in_map_units_minus1);
  AL_BitStreamLite_PutU(pBS, 1, pSps->frame_mbs_only_flag);

  if(!pSps->frame_mbs_only_flag)
    AL_BitStreamLite_PutU(pBS, 1, pSps->mb_adaptive_frame_field_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->direct_8x8_inference_flag);
  AL_BitStreamLite_PutU(pBS, 1, pSps->frame_cropping_flag);

  if(pSps->frame_cropping_flag)
  {
    AL_BitStreamLite_PutUE(pBS, pSps->frame_crop_left_offset);
    AL_BitStreamLite_PutUE(pBS, pSps->frame_crop_right_offset);
    AL_BitStreamLite_PutUE(pBS, pSps->frame_crop_top_offset);
    AL_BitStreamLite_PutUE(pBS, pSps->frame_crop_bottom_offset);
  }
  AL_BitStreamLite_PutU(pBS, 1, pSps->vui_parameters_present_flag);

  // 2 - Write VUI following spec E.1.1.

  if(pSps->vui_parameters_present_flag)
  {
    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.aspect_ratio_info_present_flag);

    if(pSps->vui_param.aspect_ratio_info_present_flag)
    {
      AL_BitStreamLite_PutU(pBS, 8, pSps->vui_param.aspect_ratio_idc);

      if(pSps->vui_param.aspect_ratio_idc == 255) // Extended_SAR
      {
        AL_BitStreamLite_PutU(pBS, 16, pSps->vui_param.sar_width);
        AL_BitStreamLite_PutU(pBS, 16, pSps->vui_param.sar_height);
      }
    }
    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.overscan_info_present_flag);

    if(pSps->vui_param.overscan_info_present_flag)
      AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.overscan_appropriate_flag);
    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.video_signal_type_present_flag);

    if(pSps->vui_param.video_signal_type_present_flag)
    {
      AL_BitStreamLite_PutU(pBS, 3, pSps->vui_param.video_format);
      AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.video_full_range_flag);
      AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.colour_description_present_flag);

      if(pSps->vui_param.colour_description_present_flag)
      {
        AL_BitStreamLite_PutU(pBS, 8, pSps->vui_param.colour_primaries);
        AL_BitStreamLite_PutU(pBS, 8, pSps->vui_param.transfer_characteristics);
        AL_BitStreamLite_PutU(pBS, 8, pSps->vui_param.matrix_coefficients);
      }
    }
    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.chroma_loc_info_present_flag);

    if(pSps->vui_param.chroma_loc_info_present_flag)
    {
      AL_BitStreamLite_PutUE(pBS, pSps->vui_param.chroma_sample_loc_type_top_field);
      AL_BitStreamLite_PutUE(pBS, pSps->vui_param.chroma_sample_loc_type_bottom_field);
    }

    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.vui_timing_info_present_flag);

    if(pSps->vui_param.vui_timing_info_present_flag)
    {
      AL_BitStreamLite_PutU(pBS, 32, pSps->vui_param.vui_num_units_in_tick);
      AL_BitStreamLite_PutU(pBS, 32, pSps->vui_param.vui_time_scale);
      AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.fixed_frame_rate_flag);
    }

    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.hrd_param.nal_hrd_parameters_present_flag);

    if(pSps->vui_param.hrd_param.nal_hrd_parameters_present_flag)
      writeHrdParam(pBS, &pSps->vui_param.hrd_param, &pSps->vui_param.hrd_param.nal_sub_hrd_param);

    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.hrd_param.vcl_hrd_parameters_present_flag);

    if(pSps->vui_param.hrd_param.vcl_hrd_parameters_present_flag)
      writeHrdParam(pBS, &pSps->vui_param.hrd_param, &pSps->vui_param.hrd_param.vcl_sub_hrd_param);

    if(pSps->vui_param.hrd_param.nal_hrd_parameters_present_flag || pSps->vui_param.hrd_param.vcl_hrd_parameters_present_flag)
      AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.hrd_param.low_delay_hrd_flag[0]);

    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.pic_struct_present_flag);
    AL_BitStreamLite_PutU(pBS, 1, pSps->vui_param.bitstream_restriction_flag);
    assert(pSps->vui_param.bitstream_restriction_flag == 0);
  }
}


/****************************************************************************/
static void writeByte(AL_TBitStreamLite* pStream, uint8_t uByte)
{
  AL_BitStreamLite_PutBits(pStream, 8, uByte);
}



static void writeStartCode(AL_TBitStreamLite* pStream, AL_ECodec eCodec, int nut)
{
  (void)nut;
#if (defined(ANDROID) || defined(__ANDROID_API__))
  bool bZeroByte = true;
#else
  bool bZeroByte = false;
#endif
  // If this is a SPS, a PPS, an AUD or a SEI, add an extra zero_byte (spec. B.1.2).
  switch(eCodec)
  {
  case AL_CODEC_AVC:
    bZeroByte |= (nut >= AL_AVC_NUT_PREFIX_SEI && nut <= AL_AVC_NUT_SUB_SPS);
    break;
  default:
    break;
  }

  if(bZeroByte)
    writeByte(pStream, 0x00);

  // don't count start code in case of "VCL Compliance"
  writeByte(pStream, 0x00);
  writeByte(pStream, 0x00);
  writeByte(pStream, 0x01);
}

/****************************************************************************/
static bool Matches(uint8_t const* pData)
{
  return !((pData[0] & 0xFF) || (pData[1] & 0xFF) || pData[2] & 0xFC);
}

/****************************************************************************/
static void AntiEmul(AL_TBitStreamLite* pStream, uint8_t const* pData, int iNumBytes)
{
  // Write all but the last two bytes.
  int iByte;

  for(iByte = 2; iByte < iNumBytes; iByte++)
  {
    writeByte(pStream, *pData);

    // Check for start code emulation
    if(Matches(pData++))
    {
      writeByte(pStream, *pData++);
      iByte++;
      writeByte(pStream, 0x03); // Emulation Prevention uint8_t
    }
  }

  if(iByte <= iNumBytes)
    writeByte(pStream, *pData++);
  writeByte(pStream, *pData);
}

/******************************************************************************/
void AL_BitStreamLite_Reset(AL_TBitStreamLite* pBS)
{
  pBS->iBitCount = 0;
}

/******************************************************************************/
void writeSps(AL_TBitStreamLite* pBS, AL_TAvcSps const* pSps)
{
  writeSpsData(pBS, pSps);

  // Write rbsp_trailing_bits.
  AL_BitStreamLite_PutU(pBS, 1, 1);
  AL_BitStreamLite_AlignWithBits(pBS, 0);
}

/*****************************************************************************/
void writePps(AL_TBitStreamLite* pBS, AL_TAvcPps const* pPps)
{

  // 1 - Write PPS following spec 7.3.2.2.

  AL_BitStreamLite_PutUE(pBS, pPps->pic_parameter_set_id);
  AL_BitStreamLite_PutUE(pBS, pPps->seq_parameter_set_id);
  AL_BitStreamLite_PutU(pBS, 1, pPps->entropy_coding_mode_flag);
  AL_BitStreamLite_PutU(pBS, 1, pPps->bottom_field_pic_order_in_frame_present_flag);
  AL_BitStreamLite_PutUE(pBS, pPps->num_slice_groups_minus1);
  assert(pPps->num_slice_groups_minus1 == 0);
  AL_BitStreamLite_PutUE(pBS, pPps->num_ref_idx_l0_active_minus1);
  AL_BitStreamLite_PutUE(pBS, pPps->num_ref_idx_l1_active_minus1);
  AL_BitStreamLite_PutU(pBS, 1, pPps->weighted_pred_flag);
  AL_BitStreamLite_PutU(pBS, 2, pPps->weighted_bipred_idc);
  AL_BitStreamLite_PutSE(pBS, pPps->pic_init_qp_minus26);
  AL_BitStreamLite_PutSE(pBS, pPps->pic_init_qs_minus26);
  assert(pPps->chroma_qp_index_offset >= -12 && pPps->chroma_qp_index_offset <= 12);
  AL_BitStreamLite_PutSE(pBS, pPps->chroma_qp_index_offset);
  AL_BitStreamLite_PutU(pBS, 1, pPps->deblocking_filter_control_present_flag);
  AL_BitStreamLite_PutU(pBS, 1, pPps->constrained_intra_pred_flag);
  AL_BitStreamLite_PutU(pBS, 1, pPps->redundant_pic_cnt_present_flag);

  if(pPps->transform_8x8_mode_flag
     || (pPps->second_chroma_qp_index_offset != pPps->chroma_qp_index_offset))
  {
    AL_BitStreamLite_PutU(pBS, 1, pPps->transform_8x8_mode_flag);
    AL_BitStreamLite_PutU(pBS, 1, pPps->pic_scaling_matrix_present_flag);
    assert(pPps->pSPS != NULL);
    writeScalingMatrix(pBS, pPps->pic_scaling_matrix_present_flag, pPps->pSPS);
    assert(pPps->second_chroma_qp_index_offset >= -12 && pPps->second_chroma_qp_index_offset <= 12);
    AL_BitStreamLite_PutSE(pBS, pPps->second_chroma_qp_index_offset);
  }

  // 2 - Write rbsp_trailing_bits.

  AL_BitStreamLite_PutU(pBS, 1, 1);
  AL_BitStreamLite_AlignWithBits(pBS, 0);
}


/****************************************************************************/
void FlushNAL(AL_TBitStreamLite* pStream, uint8_t uNUT, AL_TNalHeader const* pHeader, uint8_t* pDataInNAL, int iBitsInNAL)
{
  writeStartCode(pStream, AL_CODEC_AVC, uNUT);

  for(int i = 0; i < pHeader->size; i++)
    writeByte(pStream, pHeader->bytes[i]);

  int iBytesInNAL = BitsToBytes(iBitsInNAL);

  if(pDataInNAL && iBytesInNAL)
    AntiEmul(pStream, pDataInNAL, iBytesInNAL);
}


void generateSPS(AL_TAvcSps* pSPS)
{

  AL_EChromaMode eChromaMode = gEncSetting.eChromaMode;
  AL_EProfile eProfile = gEncSetting.eProfile;
  
  uint32_t uCSFlags = AL_GET_CS_FLAGS(eProfile);
  // --------------------------------------------------------------------------
  pSPS->profile_idc = AL_GET_PROFILE_IDC(eProfile);

  pSPS->constraint_set0_flag = (uCSFlags) & 1;
  pSPS->constraint_set1_flag = (uCSFlags >> 1) & 1;
  pSPS->constraint_set2_flag = (uCSFlags >> 2) & 1;
  pSPS->constraint_set3_flag = (uCSFlags >> 3) & 1;
  pSPS->constraint_set4_flag = (uCSFlags >> 4) & 1;
  pSPS->constraint_set5_flag = (uCSFlags >> 5) & 1;
  pSPS->chroma_format_idc = eChromaMode;
  pSPS->bit_depth_luma_minus8 = gEncSetting.bitDepth - 8;
  pSPS->bit_depth_chroma_minus8 = gEncSetting.bitDepth - 8;
  pSPS->qpprime_y_zero_transform_bypass_flag = 0;

  AL_AVC_SelectScalingList(pSPS, &gEncSetting);

  pSPS->level_idc = gEncSetting.uLevel;
  pSPS->seq_parameter_set_id = 0;
  pSPS->pic_order_cnt_type = 0; // TDMB = 2;

  pSPS->max_num_ref_frames = 1;
  pSPS->gaps_in_frame_num_value_allowed_flag = 0;
  //hard code to 6 and 0, need to change log2_max_frame_num_minus4 to 6 for gdr case??
  pSPS->log2_max_pic_order_cnt_lsb_minus4 = gEncSetting.uLog2_max_poc - 4;//AL_GET_SPS_LOG2_MAX_POC(pChannel->uSpsParam) - 4;
  pSPS->log2_max_frame_num_minus4 = gEncSetting.uLog2_max_frame_num - 4;

  // frame_mbs_only_flag:
  // - is set to 0 whenever possible (we allow field pictures).
  // - must be set to 1 in Baseline (sec. A.2.1), or for certain levels (Table A-4).

  // m_SPS.frame_mbs_only_flag = ((cp.iProfile == 66) || (cp.iLevel <= 20) || (cp.iLevel >= 42)) ? 1 : 0;
  pSPS->frame_mbs_only_flag = 1;// (bFrameOnly) ? 1 : 0;

  // direct_8x8_inference_flag:
  // - is set to 1 whenever possible.
  // - must be set to 1 when level >= 3.0 (Table A-4), or when frame_mbs_only_flag == 0 (sec. 7.4.2.1).
  pSPS->direct_8x8_inference_flag = 1;

  pSPS->mb_adaptive_frame_field_flag = 0;

  pSPS->vui_parameters_present_flag = 1;
#if defined(ANDROID) || defined(__ANDROID_API__)
  pSPS->vui_parameters_present_flag = 0;
#endif

  pSPS->vui_param.chroma_loc_info_present_flag = (eChromaMode == AL_CHROMA_4_2_0) ? 1 : 0;
  pSPS->vui_param.chroma_sample_loc_type_top_field = 0;
  pSPS->vui_param.chroma_sample_loc_type_bottom_field = 0;

  AL_AVC_GenerateSPS_Resolution(pSPS, gEncSetting.uEncWidth, gEncSetting.uEncHeight, gEncSetting.uMaxCuSize, gEncSetting.eAspectRatio);

  pSPS->vui_param.overscan_info_present_flag = 0;

  pSPS->vui_param.video_signal_type_present_flag = 1;

  pSPS->vui_param.video_format = VIDEO_FORMAT_UNSPECIFIED;
  pSPS->vui_param.video_full_range_flag = 0;

  // Colour parameter information
  pSPS->vui_param.colour_description_present_flag = 1;
  pSPS->vui_param.colour_primaries = AL_H273_ColourDescToColourPrimaries(gEncSetting.eColourDescription);
  pSPS->vui_param.transfer_characteristics = gEncSetting.eTransferCharacteristics;
  pSPS->vui_param.matrix_coefficients = gEncSetting.eColourMatrixCoeffs;

  // Timing information
  // When fixed_frame_rate_flag = 1, num_units_in_tick/time_scale should be equal to
  // a duration of one field both for progressive and interlaced sequences.
  pSPS->vui_param.vui_timing_info_present_flag = 1;
  pSPS->vui_param.vui_num_units_in_tick = gEncSetting.uClkRatio;
  pSPS->vui_param.vui_time_scale = gEncSetting.uFrameRate * 1000 * 2;

  AL_Reduction(&pSPS->vui_param.vui_time_scale, &pSPS->vui_param.vui_num_units_in_tick);

  pSPS->vui_param.fixed_frame_rate_flag = 0;

  // NAL HRD
  pSPS->vui_param.hrd_param.nal_hrd_parameters_present_flag = 0;

  if(pSPS->vui_param.hrd_param.nal_hrd_parameters_present_flag)
    AL_AVC_UpdateHrdParameters(pSPS, &(pSPS->vui_param.hrd_param.nal_sub_hrd_param), gEncSetting.iCpbSize * gEncSetting.uMaxBitRate);

  // VCL HRD
  pSPS->vui_param.hrd_param.vcl_hrd_parameters_present_flag = 1;

  if(pSPS->vui_param.hrd_param.vcl_hrd_parameters_present_flag)
    AL_AVC_UpdateHrdParameters(pSPS, &(pSPS->vui_param.hrd_param.vcl_sub_hrd_param), gEncSetting.iCpbSize * gEncSetting.uMaxBitRate);

  // low Delay
  pSPS->vui_param.hrd_param.low_delay_hrd_flag[0] = 0;

  // Picture structure information
  pSPS->vui_param.pic_struct_present_flag = 1;

  pSPS->vui_param.bitstream_restriction_flag = 0;

  // MVC Extension
}



/****************************************************************************/
void generatePPS(AL_TAvcPps* pPPS, AL_TAvcSps const* pSPS)
{

  pPPS->pic_parameter_set_id = 0;
  pPPS->seq_parameter_set_id = 0;

  pPPS->entropy_coding_mode_flag = (gEncSetting.eEntropyMode == AL_MODE_CABAC) ? 1 : 0;
  pPPS->bottom_field_pic_order_in_frame_present_flag = 0;

  pPPS->num_slice_groups_minus1 = 0;
  pPPS->num_ref_idx_l0_active_minus1 = 0;//iMaxRef - 1;
  pPPS->num_ref_idx_l1_active_minus1 = 0;//iMaxRef - 1;

  pPPS->weighted_pred_flag = 0;//(pChannel->eWPMode == AL_WP_EXPLICIT) ? 1 : 0;
  pPPS->weighted_bipred_idc = 0;//pChannel->eWPMode;

  pPPS->pic_init_qp_minus26 = gEncSetting.iPpsInitQp - 26;
  pPPS->pic_init_qs_minus26 = gEncSetting.iPpsInitQp - 26;
  pPPS->chroma_qp_index_offset = gEncSetting.iCbPicQpOffset;
  pPPS->second_chroma_qp_index_offset = gEncSetting.iCrPicQpOffset;

  pPPS->deblocking_filter_control_present_flag = 1; // TDMB = 0;

  pPPS->constrained_intra_pred_flag = gEncSetting.bConstrainedIntraPred;
  pPPS->redundant_pic_cnt_present_flag = 0;
  pPPS->transform_8x8_mode_flag = 1;
  pPPS->pic_scaling_matrix_present_flag = 0;

  pPPS->pSPS = (AL_TAvcSps*)pSPS;
}

/******************************************************************************/
void FillSliceParam(AL_TEncSliceParam* pSP, AL_TPictureInfo* pPI, AL_ESliceType SliceType, int32_t CurPOC, int32_t FrameNo, bool bIDR)
{
  pPI->eType = SliceType;
  pPI->iPOC = CurPOC % (1 << gEncSetting.uLog2_max_poc); //?
  pPI->iFrameNum = FrameNo % (1 << gEncSetting.uLog2_max_frame_num);
  pPI->uFlags = bIDR? AL_PICT_INFO_IS_IDR:0;  
  if(bIDR)
    gEncSetting.iLastIdrId++;

  pPI->iLastIdrId = gEncSetting.iLastIdrId;
    
  pPI->eMarking = SHORT_TERM_REF;

  
  pSP->SliceType = SliceType;

  // Control 0
  pSP->MinTUSize = 2;
  pSP->MaxTUSize = 3;
  pSP->MinCUSize = 2;
  pSP->Codec = AL_CODEC_HEVC;
  pSP->MaxCUSize = gEncSetting.uMaxCuSize;

  // Control 1
  pSP->PicWidth = (gEncSetting.uEncWidth + 7) / 8;
  pSP->PicHeight = (gEncSetting.uEncHeight + 7) / 8;
  pSP->LcuWidth = (gEncSetting.uEncWidth + (1 << pSP->MaxCUSize) - 1) >> pSP->MaxCUSize;
  pSP->LcuHeight = (gEncSetting.uEncHeight + (1 << pSP->MaxCUSize) - 1) >> pSP->MaxCUSize;

  // Control 2
  pSP->CuQpDeltaDepth = 0;
  pSP->CabacInitIdc = gEncSetting.uCabacInitIdc;
  pSP->EntropyMode = gEncSetting.eEntropyMode;
  pSP->EnableFrmBufComp = gEncSetting.bEnableFrmBufComp;
  //pSP->eSrcFmt = pChParam->eSrcMode;
  pSP->BitDepthLuma = gEncSetting.bitDepth;
  pSP->BitDepthChroma = gEncSetting.bitDepth;

  //pSP->IntraPCM = (pChParam->eEncTools & AL_OPT_PCM);
  pSP->TemporalMVP = true;
  //pSP->SkipTransfo = (pChParam->eEncTools & AL_OPT_TRANSFO_SKIP);
  //pSP->HighFreq = (pChParam->eEncOptions & AL_OPT_HIGH_FREQ);

  // Control 3
  pSP->CbQpOffset = 0;
  pSP->CrQpOffset = 0;
  pSP->ChromaMode = gEncSetting.eChromaMode;

  /*
  // Auto QP Control table
  {
    uint8_t* pEP2 = (uint8_t*)(uintptr_t)pBufferAddrs->tBasic.pEP2_v;

    if(pChParam->eEncOptions & AL_OPT_ADAPT_AUTO_QP || pChParam->eEncOptions & AL_OPT_ENABLE_AUTO_QP
       )
    {
      int iNumLCU = getNumLCU(pChParam);

      uint8_t* pQpCtrl = pEP2 + EP2_BUF_QP_CTRL.Offset;
      bool bUseDefault = !(pChParam->eEncOptions & AL_OPT_ADAPT_AUTO_QP) || (pCtx->uFrameCnt == 0);
      bool bVP9 = pSP->Codec == AL_CODEC_VP9;
      bool SetDeltaToZero = false;
      AL_UpdateAutoQpCtrl(pQpCtrl, pReq->status.uSumCplx, iNumLCU, pChParam->tRCParam.iInitialQP, pChParam->tRCParam.iMinQP, pChParam->tRCParam.iMaxQP, bUseDefault, bVP9, SetDeltaToZero);
    }
  }
*/
  //pSP->RdoCostMode = (pChParam->eEncOptions & AL_OPT_RDO_COST_MODE);
  //pSP->WaveFront = isWaveFront(pChParam->eEncTools);
  //pSP->Tile = isTile(pChParam->eEncTools);
  //pSP->DependentSlice = false;

  // Control 4
  pSP->tc_offset_div2 = gEncSetting.iTcOffset;
  pSP->beta_offset_div2 = gEncSetting.iBetaOffset;
  pSP->DisLoopFilter = gEncSetting.bDisLoopFilter;
  pSP->XSliceLoopFilter = 0;//pChParam->eEncTools & AL_OPT_LF_X_SLICE;
  pSP->InterPFilter = 0;

  // Control 5
  // see FillSliceParamFromPicParam

  // Control 6
  pSP->CrossTileLoopFilter = 0;//pChParam->eEncTools & AL_OPT_LF_X_TILE;

  // Control 7
  pSP->FixPredictor = 0;//pChParam->eEncOptions & AL_OPT_FIX_PREDICTOR;

  // Control 8
  pSP->PicCbQpOffset = gEncSetting.iCbPicQpOffset;
  pSP->PicCrQpOffset = gEncSetting.iCrPicQpOffset;

  pSP->DisPCMLoopFilter = 0;
  pSP->StrongIntraSmooth = true;
  pSP->ConstrainedIntraPred = gEncSetting.bConstrainedIntraPred;
  pSP->DisableRecOut = 0;
  pSP->DisableMVsOut = 0;
  pSP->QPTableRelative = 0;
  pSP->UseQPTable = 0;
  pSP->EnableAutoQp = 0;

  pSP->UseSclMtx = 0;
  pSP->UseLambdaTable = 0;
  pSP->LoadLambdaTable = 0;

  pSP->LoadAutoQpCtrl = 0;

  // Control 9
  pSP->WeightedPred = 0;
  pSP->WeightedBiPred = 0;
  {
    uint32_t uLumaSize = ((1 << gEncSetting.uMaxCuSize) << gEncSetting.uMaxCuSize) * 8;
    uint32_t uChromaSize = 0;

      uChromaSize = (((1 << gEncSetting.uMaxCuSize) << gEncSetting.uMaxCuSize) >> 1) * 8;


      pSP->MaxBitPerLCU = (uLumaSize + uChromaSize) + 128;

  }

  // Control 12 to 17
  // see FillSliceParamFromPicParam

  // Control 18
  pSP->ForceClip = 0;//pChParam->eEncOptions & AL_OPT_FORCE_MV_CLIP;
  pSP->UseL2 = 0;//pEI->eEncOptions & AL_OPT_USE_L2;

  // Control 24
  pSP->Direct8x8Infer = true; // only mode supported by the IP encoder



  pSP->EnableMVPerBlock = false;

  //FillSliceParamFromPicParam
  bool bAutoDisableFilters = false;

  if(gEncSetting.eGdrMode)
    bAutoDisableFilters = true;

  // Control 2

  pSP->MaxMergeCand = 2;
  pSP->DisIntra = ( pSP->SliceType != AL_SLICE_I && gEncSetting.bDisIntra);
  pSP->ColocFromL0 = 0;//??pRI->bColocFromL0;

  // Control 3
  if(pSP->SliceType == AL_SLICE_SKIP)
  {
    pSP->SliceType = AL_SLICE_P;
    pSP->SliceQP = 26;
  }
  else
  {
    pSP->SliceQP = gEncSetting.iSliceQP;
  }

  // Control 4
  if(bAutoDisableFilters)
  {
    pSP->DisLoopFilter = 1;
  }

  // Control 5
  pSP->FirstSliceLCU = 0; // Will be over written for each slice later
  pSP->NumRefIdxL0Minus1 = 0;//pRI->uNumRefIdxL0 ? pRI->uNumRefIdxL0 - 1 : 0;
  pSP->NumRefIdxL1Minus1 = 0;//pRI->uNumRefIdxL1 ? pRI->uNumRefIdxL1 - 1 : 0;
  //pSP->RefA.bIsLongTerm = 0;//(pRI->RefA.eRefMode == LONG_TERM_REF);
  //pSP->RefB.bIsLongTerm = 0;//(pRI->RefB.eRefMode == LONG_TERM_REF);
  //pSP->RefA.RefIdx = 0;//pRI->uRefIdxA;
  //pSP->RefB.RefIdx = 0;//pRI->uRefIdxB;

  // Control 8
  pSP->NoBackwardPredFlag = 0;//pRI->bNoBackwardPredFlag;
  pSP->RefColocL0Flag = 0;//pRI->bRefColocL0Flag;
  pSP->RefColocL0LTFlag = 0;//pRI->bRefColocL0LTFlag;
  pSP->RefColocL1LTFlag = 0;//pRI->bRefColocL1LTFlag;


  // Control 12 to 17
  pSP->CurrentPOC = CurPOC;
//  pSP->RefA.POC = 0;//NormativeDefaultValue(pRI->RefA.iPOC);
//  pSP->RefB.POC = 0;//NormativeDefaultValue(pRI->RefB.iPOC);
//  pSP->Coloc.POC = 0;//NormativeDefaultValue(pRI->RefColoc.iPOC);
  pSP->ColRef0POC = 0;//pRI->RefColoc.iRefAPOC;
  pSP->ColRef1POC = 0;//pRI->RefColoc.iRefBPOC;

  // Control 24
  pSP->GdrMode = gEncSetting.eGdrMode;
  pSP->GdrPos = 0;//???pPI->uGdrPos;

  //if(pSP->SliceType != AL_SLICE_I || pCtx->ChanParam.iLayerID > 0)
  {
  //  pSP->RefA.bIsAvail = (pRI->RefA.eRefMode != UNUSED_FOR_REF);
  //  pSP->RefB.bIsAvail = (pRI->RefB.eRefMode != UNUSED_FOR_REF);
  }

}

/***************************************************************************/
uint32_t generateSliceHeader(AL_TBitStreamLite* pBS, AL_TPictureInfo* pPI, AL_TEncSliceParam* pSP, uint8_t* pBufAddrs, uint32_t uSliceOffset, bool bOverwriteHeader)
{

  int iNUT = AL_IS_IDR(*pPI) ? AL_AVC_NUT_VCL_IDR : AL_AVC_NUT_VCL_NON_IDR;

  AL_TAvcSliceHdr sh;

  sh.nal_ref_idc = 1;
  sh.nal_unit_type = iNUT;
  sh.num_line_in_slice = (((pSP->LcuHeight + 1) >> 1) << 4);

  sh.first_mb_in_slice = pSP->FirstSliceLCU;

  sh.slice_type = pSP->SliceType;
  sh.pic_parameter_set_id = 0;
  sh.frame_num = pPI->iFrameNum;
  sh.field_pic_flag = 0;
  sh.bottom_field_flag = 0;
  sh.idr_pic_id = pPI->iLastIdrId;
  sh.pic_order_cnt_lsb = pPI->iPOC & ((1 << 10) - 1);
  sh.delta_pic_order_cnt_bottom = 0;
  sh.direct_spatial_mv_pred_flag = 0;

//  if(pSP->NumRefIdxL0Minus1 != AL_GET_PPS_NUM_ACT_REF_L0(pCtx->ChanParam.uPpsParam))
//    sh.num_ref_idx_active_override_flag = 1;
//  else
    sh.num_ref_idx_active_override_flag = 0;
  sh.num_ref_idx_l0_active_minus1 = pSP->NumRefIdxL0Minus1;
  sh.num_ref_idx_l1_active_minus1 = pSP->NumRefIdxL1Minus1;

  sh.ref_pic_list_reordering_flag_l0 = 0;//no long term ref yet
  sh.ref_pic_list_reordering_flag_l1 = 0;

  sh.no_output_of_prior_pics_flag = 0;

  sh.long_term_reference_flag = (pPI->eMarking == LONG_TERM_REF);
  sh.adaptive_ref_pic_marking_mode_flag = 0;//(!sh.long_term_reference_flag && pRI->iMMCORemovePicNum == AL_AVC_NO_MMCO && !pRI->bRmLT) ? 0 : 1;

  sh.cabac_init_idc = pSP->CabacInitIdc;
  sh.slice_qp_delta = pSP->SliceQP - gEncSetting.iPpsInitQp;

//  if((pCtx->ChanParam.eEncTools & AL_OPT_LF) && (pSP->DisLoopFilter == 0))
//    sh.disable_deblocking_filter_idc = (pCtx->ChanParam.eEncTools & AL_OPT_LF_X_SLICE) ? 0 : 2;
//  else
//    sh.disable_deblocking_filter_idc = 1;

  sh.disable_deblocking_filter_idc = pSP->DisLoopFilter;

  sh.slice_alpha_c0_offset_div2 = pSP->tc_offset_div2;
  sh.slice_beta_offset_div2 = pSP->beta_offset_div2;

  pBS->iBitCount = 0;
  
  WriteAvcSliceSegmentHdr(pBS, &sh);

  uint16_t uHdrSize = pBS->iBitCount;
  int iBytesLen = BitsToBytes(uHdrSize);
//printf("zxj, current hdr byteslen=%d\n", iBytesLen);
  pSP->SliceHdrLength = 0;

  if(gEncSetting.eEntropyMode == AL_MODE_CAVLC)
  {
    int AL_MAX_SLICE_HEADER_LENGTH = 24;
    int AL_MIN_SLICE_HEADER_LENGTH = 16;
    pSP->SliceHdrLength = (uHdrSize < AL_MAX_SLICE_HEADER_LENGTH) ? uHdrSize : AL_MIN_SLICE_HEADER_LENGTH + (uHdrSize % 8);
  }

  uint32_t uOffset = 0;

  if(bOverwriteHeader)
    uOffset = BitsToBytes(pSP->SliceHdrLength);
  else
    iBytesLen -= BitsToBytes(pSP->SliceHdrLength);

  if(pPI->eType == AL_SLICE_SKIP && gEncSetting.eEntropyMode == AL_MODE_CAVLC)
  {
    AL_BitStreamLite_PutUE(pBS, pSP->LcuWidth * pSP->LcuHeight);
    AL_BitStreamLite_PutU(pBS, 1, 1);
    AL_BitStreamLite_AlignWithBits(pBS, 0);

    iBytesLen = BitsToBytes(pBS->iBitCount);
  }

  uint8_t* pCurStream = (uint8_t*)pBufAddrs + uSliceOffset;
  uint8_t uAEByte = SliceHdrFlushNAL(pCurStream + uOffset, AL_CODEC_AVC,
                             iNUT, pBS->pData,
                             iBytesLen, sh.nal_ref_idc, 1);


  uAEByte -= uOffset;

  if(pSP->SliceHdrLength > 0)
  {
    uint32_t uData = pCurStream[2] | (pCurStream[1] << 8) | (pCurStream[0] << 16) | ((unsigned int)pCurStream[-1] << 24);
    pSP->SliceHdrData = uData >> (8 - (uHdrSize % 8));
  }
  else
  {
    pSP->SliceHdrData = 0;
  }

  //printf("zxj, current pSP->SliceHdrData =%d\n", pSP->SliceHdrData );




  int i=0;
  // for(i=uAEByte;i>0;i--)
      // printf("0x%02x  ", *(pCurStream + uOffset - i));
  // printf("\n");
  
  return uAEByte;
}

void h264_noc_config()
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
    
#if 1
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
        data |= 0xb << 13; // init flow: bit 13~17, 0x9 for vo, 0xb for h264
    
       
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
        *(volatile unsigned int *)(0x99900000 +0x3024) = 30;
    
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
#endif
}


#if 0

static uint32_t  __attribute__((aligned(32))) PIC0_BITSTREAM_LTRP[]=
{
    0xCC8FB7D2,0xA509F552,0x453AF207,0x55F5A4CB,0x70578F05,0x775A62AC,0x51C36673,0x866FE74A,0x461D6B9B,0xDFDCB2F2,0x447BE948,0xC459435C,0xB63ADC6A,0x36806131,0x9D1208E7,0x38EACFBC,0x535A85DB,0xF19D1F4D,0x375E3BC5,0x6684AFB7,0x5E23F63C,0x6400EE87,0x073E9BFD,0x57794E83,0x25BDC46D,0x924692B3,0xD5F6D2AB,0x9845F67A,0x718D8E4A,0xBCE3EB2B,0x985DD655,0x51E93819,0x7EB8C407,0x027C7BEE,0x3B20CE14,0x0B4492B2,0x248741C7,0x71FC9EB1,0x4B8BA3A3,0x78721CF9,0x967E2532,0x008716BB,0x46B6F6DA,0x3C62A86A,0x4C6BA6AC,0x1113AC1B,0xD083FFAF,0x806BDD87,0xD08DDADF,0x640DFE67,0x6F47B165,0x8517136A,0x13A081AE,0x513121E9,0x1033CF0C,0xADD3280C,0xB67B45BB,0x9715FEF6,0x83C6563A,0xF2484DA8,0x6CF8CC7F,0x8939D647,0x95EB5613,0xE90BD9B8,0x92E54D12,0xC6C9EDAC,0x5FD00850,0x1B52A351,0xF28F8383,0x69411897,0xD8B4D273,0x68B8D90C,0x1AA04D3A,0xADA0AF34,0x79A491AD,0x3FD721F7,0x5A407B90,0xCD591892,0xC5E06EAC,0xB78E2DE9,0xD4D7D5F3,0xF606214B,0xC6A754C2,0x5D1CF37C,0xDA796D6B,0xA61C49E0,0x90AD26F0,0x3356BE05,0x29F16DF6,0x72779052,0xE29F9390,0x451FAA64,0x8C8D199A,0x0749F74B,0x6C152341,0x9A248C49,0x45717F18,0xE5AD7B99,0x7627114B,0x003D4A2F,0xC6ADA0A8,0x770E9FE4,0x2AE30FB1,0x005612FB,0x66AC69CE,0x5F699F5B,0xC9983CB3,0x43DA62B5,0xE491BC11,0xF8AC2D4B,0x5CCB2C0A,0xBBBC3C4E,0xAA33AFF4,0xF25E319C,0x9D9AAC7E,0x3D7262FE,0xB3F7BCD0,0x54F135E0,0x432CEC4A,0x33F43BC5,0xB426757F,0x93ABBC84,0x91DA7EFB,0x200574A0,0x9A15F264,0xB3851AEC,0x3922B1BB,0xACAB0C06,0xD286A104,0x3727A4FD,0x3FC2F8A6,0x155BF748,0xCECBE16D,0x722C8689,0x331108BC,0x16B87DA2,0xA66AF81F,0x54DA98CF,0xCFE48970,0x7E8CC4DF,0xD101FBA9,0x35377F2B,0x63D21FD5,0xF4AFC0BB,0x0FCE8B7D,0x1B0872E5,0x8E8EF2D0,0x13867193,0xCF4D4AF2,0xF739F0A0,0x694B8693,0x4A4F9D41,0x27644D08,0x88D7D0C3,0xA8B35FCD,0xC987EAF8,0xD197B2E3,0x240A2028,0x3585EE7F,0x0304A18B,0xA1C7F50B,0xF31D0EEA,0x2F3768E9,0x6E5BA97F,0x7A3641C3,0x98B28573,0xE5B75B52,0x750BC510,0x407A1C4C,0xD5B3BF01,0x44324BC9,0xDCCA9981,0x1E053F97,0xFEBF35C9,0x0E766191,0xA3E4BA10,0x41E4FE1E,0x4F95EE93,0x4642421F,0x9C46BEB3,0x6DD1BDB3,0xE2B3F773,0x72939B8E,0xF7A09199,0x78876240,0xC1DF8E6A,0xBA52AFA5,0xA8150B97,0x2B2F05D2,0x67941B54,0x30DE74E4,0x628B24B8,0x0AB60B0E,0xA93AB212,0xD55B08DC,0x3D92CDED,0xAE5D6A41,0x941F1D5D,0x84A4FA24,0x81D1706C,0xB20A8CBE,0x782532DD,0x8DF4FC35,0x1C887399,0x6EE12323,0xE1FEEC43,0xFB9C8C34,0x610832EB,0x265E9B28,0xC25354F4,0xD8D56F54,0x8330700C,0x8C34D091,0x1A1114B3,0x77E93A0E,0x68B08EDB,0x7B526EC4,0x49EFD9CA,0x142B792D,0xB7D0ED2A,0x5EDEF1BE,0x267E2B6B,0xB881566B,0x401CC01F,0x5ED77D44,0xA440F400,0x6A274296,0x94649EC8,0xC9F2F502,0x7FF90B77,0x88464B3D,0xC6EA6C36,0x064E2DB1,0x2F43F25C,0xF5C3ADA1,0x1C6EE83F,0x0476C44E,0x3EC63D2A,0xA029EE21,0xF44E3CC1,0xB5297C76,0x782F9EC8,0x2AAF2FFA,0xF3C9932C,0x86ADF8D4,0x3B780B44,0x146308CA,0x3DD2741C,0x5A04FF2B,0x47490135,0xF22E0F8A,0x4073F351,0x9938EFD5,0x02E0306D,0xDF5365BA,0x53A30DAF,0xAD7285E5,0x33F9B04A,0xECB4FD20,0x4308478A,0xAEDDE452,0x8A90D1B6,0x6ACAA91D,0xD9DC8A65,0x8EDF3CD1,0x3CF8327F,0x37F84155,0x206D7295,0x6A69AB20,0x3EC512B1,0xA99F3754,0xAF2F7F92,0x602F2C69,0x58B462B1,0xF1239A46,0x035FD636,0x3653AE51,0x235D652E,0x043E270D,0x0C80C545,0x52BB9578,0xB6BC1651,0x9289269A,0x0A452ED6,0xF36D76F0,0x3390B529,0xF5C52739,0xE0DCF0E8,0x710C9A07,0x10FD8615,0x20C0BE64,0xED1ECF32,0x964068F4,0x03C40565,0xE6A508C7,0x41FC1F13,0x481C797F,0x1CA2EEB1,0x6DB96DCF,0xFB5A896A,0xE882E7D0,0x1E40FCDF,0xF08FCB45,0x9E2CCF11,0x11D58D7B,0x2150969A,0xA1D00A0A,0x028A3D3B,0x5CD2C339,0x65AC208A,0x0D1A186C,0xC5EE4F33,0x1920EF65,0x4B53C5A4,0x55730829,0x29D7CF92,0x73231C4B,0xF0EB8534,0x1B616F87,0xCFC4A77B,0x2E3E3781,0x8CF9A7F0,0xC589C038,0x332494E6,0x7D4C5913,0xADC8007C,0x1AC0B0E5,0x220D7D47,0xA3F7A1FF,0x35F8BBBB,0x0B6FAB10,0x31ED0AAF,0x83F04EF1,0xA5BDB9C0,0x0F407246,0x0ED547FC,0x07D5BDC0,0x264138A1,0x41544A6A,0xE94F1F00,0xCF092603,0x66A6D7F6,0x3AF8ABAC,0xC771911D,0x90AC3D7F,0x6180E680,0x623EC4ED,0xB1DA8BE4,0x9D4FFFD7,0xA4BE3150,0xC1398D40,0x27F0EC25,0xED0BF020,0x2F170DFD,0x796765DB,0xFB13AC85,0xA5117B1A,0x556FE334,0xD2A1DADC,0x28A6703D,0x792808F9,0x007D9E8C,0x6F2D3775,0xFD416C29,0x31DDE409,0x3EF1E9A8,0x72EC1719,0x3110855B,0x110CEA86,0x0C5B3C01,0x43183E89,
    0x4A55DC77,0x21AEB627,0xA82EA10C,0x037AB5A8,0x4979D3AF,0x317FA726,0xDE63D4F4,0x00973156,0x32905B0F,0x0B0B22ED,0x9DCED13C,0x44A81DBB,0xA8A1A731,0x5F159435,0x030D1C05,0x56D424A5,0x2EFA9C70,0xC930E600,0x3D52FC07,0x2F3C64CC,0xAB8253EA,0xD236AD0E,0x110B72B1,0xCAE14C5D,0xD5B1484F,0x6579BBAA,0x1235AE99,0x2E6B9D17,0x9EA40750,0xB52CF253,0xA7189881,0x32F0633A,0x7A715AB0,0xB6196FCE,0x3DE54FC4,0x87486CE2,0xB62C1DFA,0x604E076A,0xB1EC2D7F,0x1F30F3A2,0x4E28CDFC,0x6A9ABE70,0xB68C3A91,0xEF709742,0x0D6F7E45,0xE0121F96,0x75DD76A2,0xEE84BDD3,0x3CBCEA2A,0x0151E19E,0x9A213844,0xE7726ACD,0xB0F385C3,0x91E6E930,0x4E0D45F3,0x839EFAA2,0x10979E1A,0x56B77FA4,0x55089DD7,0xC016A1F0,0xE8C1F44C,0xFDE2D976,0xE955041B,0x7F7873B6,0x30972EC8,0xE60CBF1E,0xB905998F,0x5171EC28,0xD77D0247,0x0E13F710,0x3B5F8F99,0x207EE16A,0x1EE2E566,0x44D90164,0x93D70BDE,0x2C57F0BF,0xC6C35271,0x049F3AAD,0x37CE6D04,0x1F5B89D5,0xD13EA503,0x3F541C8C,0xD7F0BED2,0xEF1D8412,0x91CA19BD,0x97AB70D1,0xFDB6EA86,0x8F6FFCDF,0x4AFF4BA4,0x7E0D95D7,0xA008E633,0xD29AB6B4,0xF542D0CB,0xEA49DAFD,0x887FE6D6,0x6373B5D8,0x6FF7696C,0x457D0A88,0x5F10DBEB,0x2A08DCD8,0x0226EFFD,0xF28DBA02,0xC5DD1B4A,0x4F5BAEF9,0x2EEE3674,0x9089BB27,0x4D87A49F,0x15DA5311,0x9B8F647F,0xF9EA9024,0x380977CB,0xEF3A0E22,0x40D42244,0x5A7018CE,0x6FC6CEFF,0x776C7596,0x2FF5E7A8,0xD35DEC41,0xC1AE6EA6,0xC28D69B8,0xAFC28EA9,0xD254CED0,0x075ABD3B,0x9F58D00A,0xD6EA67B4,0x49B9969B,0xC2E3D70C,0xAE225880,0x227F79A2,0xD6510C1D,0x64B61D33,0x83D6A9DB,0x30CA65F7,0x8B7E972F,0x3B7ACB9E,0x50B53202,0x2F769A15,0xBC08F475,0x79ED43D3,0x0927E688,0x10963559,0xD26A4E7D,0xB2B307C1,0xC71B36DF,0xBF5DE15F,0x02C4267A,0xD6406281,0xEDAA818F,0x70C756C5,0xBC63E272,0x7458B76E,0x17032ED8,0x87F357B6,0xD1CDC268,0x8DBEF617,0x275643D3,0x0C449A41,0x26887721,0x087456F5,0x636BF80B,0x4193826C,0x6C385BB1,0xF8D11165,0xECC4725A,0x0FEC423A,0xF512EF66,0x47F1E060,0xFE0916BE,
};

static uint32_t  __attribute__((aligned(32))) PIC1_BITSTREAM_LTRP[]=
{
    0x00EA52E4,0xC88E7462,0x0B7C236C,0x4CBA1114,0x95755030,0xB35B8840,0xE952BAC5,0xAF5A7101,0xC4A1F790,0x33BA7CF6,0x6FDF9051,0x710C7B37,0xEF216DFC,0x575427C7,0x34EE607A,0xD7637D2F,0x43379FBE,0x1DA1A2E7,0xA1783BB9,0x00E4A96E,0x7D6A05E4,0xB3CCC619,0x7CCE3D1C,0x6B97590F,0x3C1D65E3,0x467A80BB,0xBD50D021,0xD64EC21B,0xF176AC95,0x959A227F,0x37F2E982,0xB5CED4D6,0xA7FE8ECA,0xD42B15F4,0x18757983,0xC37874A6,0x6DAEAA67,0x3245E9DD,0x71F8B1EE,0x2DA3F099,0xB6EBF55D,0xAA6C008A,0x62AEC855,0x21232974,0x0651E449,0x2FA0FAC2,0x1E67A2AF,0x22B0E0E4,0xE4694A8E,0xB3CED66D,0x4FA368B1,0xCA396963,0xBD3AF247,0xDF4747BC,0x1DF188C8,0x66065581,0x87BC3920,0xDBC72E23,0x966D8E36,0x17F7F756,0x39A3DB95,0xE436E567,0x8816FDF2,0x936B2C87,0x36973C80,0x22BAC3EA,0x1EA3DB9D,0x514AC3BD,0x5060D843,0x0CDC724B,0xAF1B8CA4,0x720F99A9,0x5CE82295,0x949F85F1,0xE58E46A9,0x43D88427,0x3B203352,0x24039CD5,0x50667646,0xB4CF9C47,0x76C4BB67,0x2BAD92A6,0xB4560793,0xD8D16090,0x50DF830E,0x266ECA48,0x470E1D4D,0xBBDA6CAE,0x5ABC1FC9,0xAA0B229C,0x00000070,

};

static uint32_t  __attribute__((aligned(32))) PIC2_BITSTREAM_LTRP[]=
{
    0x2A8E4FE4,0xF97D8ACB,0x93981B75,0x660DCBA0,0xBC504004,0x1583C62C,0xF0BFAD97,0xA19055D2,0x706EE894,0x04079E05,0xBAF58DCF,0x194073C4,0x26CA5F8E,0x63B4D2E2,0xA024347F,0xDD19A742,0x3999BB82,0x236ACCAA,0xFBF95B03,0x34AE1800,0xD214B20E,0xFDBFA7F0,0x75CA2BF9,0x52A02942,0x410A24EC,0x4F63276A,0xB27F0DDE,0xFE5F0544,0xAE70A5E7,0xB3F06BF7,0x039351D2,0xACA3E234,0xD8C6B03A,0x5C63D0F7,0x323E462F,0xF548A0E4,0x355FBDA9,0x06BE026F,0x0D43BEE4,0xBF481224,0xBBA18438,0xABF4990D,0x9CBA1D62,0xCC464664,0x5CFD0C11,0x4E8BDECE,0xB4C5494E,0x419BF6E2,0x7955BB37,0x092A48E9,0x39637BB3,0x3E6A6382,0x554A45BE,0x9F566F49,0x1D43D410,0x62331E9F,0x9864AC54,0x4F4ADA02,0x32A6ABF8,0x7629F127,0x72B91324,0x504464D7,0x3BBD1678,0x2A1ED4A7,0x4BCBB379,0xAA3EA4C6,0x689CD322,0x81F3DA3A,0x94B24B9E,0x57D54E30,0x220F931E,0xF945F0E9,0x43E58D23,0x79AD155C,0xC242A001,0x6A95C34A,0xD4883AA0,0x62A9B1F1,0x2C6D7BAA,0x64FB9193,0xA2EEBB02,0x39207AB3,0x42595948,0x78FA9309,0x132A3AA0,0x74649CE0,0x313F2BD4,0x5991EB94,0xD71F35D0,0x93922803,0xA18B4A4F,0x607C13C5,0x394D72E4,0xDE7F5B30,0xF3AC4FE3,0x02EDD700,0x3236EB1F,0xB8A3358C,0xFC30D47B,0x98F47AA3,0x775180F7,0xF0BC6DB4,0xE2B62FA7,0x2D3CBD66,0x1EF321CA,0xA2C9E79F,0x4E4AF451,0x99F6101B,0xCE9A9E7B,0xE904C226,0x4FF3B92B,0xE07FFB0C,0xDA073AFD,0xD964AD71,0x02B444F2,
};

static uint32_t  __attribute__((aligned(32))) PIC3_BITSTREAM_LTRP[]=
{
    0x26E954E4,0x853A47BF,0xE2E7D814,0xE41EB18B,0x533B803A,0x03109A35,0x12E6FB81,0x9152FA26,0x16BA630E,0x1D0CDEEA,0x3197B52B,0xF0DB8D02,0xCBFEF9B9,0xA65E2694,0x6BEF8F6B,0x5D5E2167,0xFBDB06B6,0x85E0DD35,0xCA8C4606,0xD18F8A99,0xA0D628C2,0xFC5E1F8E,0xC288251D,0xBF036410,0x44A1329D,0xD1360D8B,0x81FF1C8F,0x0A0928A0,0x087A6FE1,0x36659FA1,0x45171B0E,0xF353AF0B,0xA60D8B04,0x506C2546,0x9983D38B,0x4475FCAB,0x6FECFB39,0x489C897D,0x81869854,0x1B7A1BFF,0xB5D8C0A9,0xE31E178F,0xAECF0E31,0x95EE2829,0xD26FC92E,0x1D7371EF,0x0BA01EC3,0xC828E879,0x15A1771C,0x4C4FDAFA,0xD866F51E,0x1BA9544E,0x6E1A81E9,0x3D7B9C4D,0x3C435629,0x3CD72D86,0x0ADE0607,0x6FAFE545,0xCBC405A2,0x594A5F3F,0x80B23D54,0x351D9975,0x6E17DDF8,0x6CEC5BF8,0x3D7DE31E,0x02469080,0xEA5201C4,0x32B44B3A,0x5164A88E,0x70A173A6,0x993C0678,0x116240F8,0x1A26E3DB,0xD5193298,0x4C96C832,0xDC933F94,0x4B1BEF39,0xBDFC3823,0xEAEEDFBA,0x6756ACE8,0x070E343C,0x73ECE83E,0x3D635A0B,0x2439D7ED,0xFC5B8E60,0x92AFE4DF,0xF2885BB9,0x2C9F53A4,0xE192F2F9,0xA41EF4EC,0x0F94ADDF,0x6C4C6D41,0x53A24750,0x7AFD86C7,0x2DD54A42,0xE0F64285,0x5BE61B58,0xA87B2A30,0x4647084C,0x3D677719,0x08F26FC2,0x93E16EC2,0x1B93A340,0x96BE23B9,0x6A6D9D55,0xCE7F3547,0x54E74BE2,0xB62B122A,0x44C1A562,0x579295F9,0xA6F92280,0xC412ACF6,0x91D3C7C1,0x3800780C,0xA9F6B354,0xA643D806,0x7ADF8A7C,0xB65B1685,0x47E8B6E8,0x50DF0AE1,0x6CAC982B,0x0DBD4AE2,0x627339F2,0xE2D759B6,0xB32DBEFA,0x69D43D01,0x91085E6F,0xC26F9F77,0xABB16BCD,0x065E08DB,
};

static uint32_t  __attribute__((aligned(32))) PIC4_BITSTREAM_LTRP[]=
{
    0xB7EA52E4,0x8E29A13B,0x861E1B8D,0x70CF2396,0x0154D14B,0xD6EECB93,0x54B7175A,0x655781B5,0x30ADCC17,0x767ECDFC,0xFEF658C4,0x4C3F5A6D,0x94FE1E36,0x30A4B5FB,0x5C425577,0x50277AD7,0xC20E379D,0x69A1E63A,0xADAD6942,0x5A7051CC,0xB8A02622,0x5E26F7D8,0x1236AABD,0xF36CBBA0,0xB832CF8B,0x6E7E55E7,0xE9F650AB,0x10EF5E50,0xDC4FEA10,0xD513D048,0x4EC0BD7B,0x6B1D1362,0xFCD5776D,0xCE0E4F29,0x2C0527A9,0x555FA362,0x6A1865C1,0x65D9C3E1,0xEBA7C5EF,0xBDBA1575,0x42E33ED3,0x61B5347E,0xEBBB020A,0x5FF9267B,0x7B6F6E71,0x13947335,0xFB441443,0x5598F2AC,0xED2927DD,0x604FC74B,0xDC23BA86,0x68B1556E,0x029309FE,0x87ACEAD5,0xFCB95042,0x071CD564,0xA10A5238,0xC7C03AD7,0x1329D437,0xA7688869,0xBB1B0D7B,0xE871DA46,0x63E88D79,0xC72A6DD8,0x1CA12C3B,0x80D2F91C,0x59767EA6,0x8968C12E,0x528EF124,0x1F1C402C,0xF76F50AC,0x10752064,0x3BB62C50,0x13B2CB1C,0x3226519E,0xA86FB3C5,0xE91C2CCF,0xB1870CFA,0x00000094,

};
static uint32_t  __attribute__((aligned(32))) PIC5_BITSTREAM_LTRP[]=
{
    0x1D784FE4,0xB371E3FC,0x1AEC5EC5,0xCBA17814,0x65081366,0x34420121,0x06BD4558,0x959ABC53,0x5894DD3B,0x903F1A5E,0xFBC02B62,0x0AA94BC6,0x42E920EC,0x8434D1AA,0x2E53B1B8,0x1314B788,0x3CE100CD,0x5C2AB612,0x65C433A0,0xC3FABAEB,0x322F0B13,0x9728999B,0xF019F22B,0x0C091742,0x0EF2C3B2,0x5D524435,0xAD8505BC,0x1BFC2BE9,0x686B4367,0xF0C51058,0xCB5CF349,0xCAD77442,0xAF19D22B,0x9663384E,0x7914ADE0,0xE5313AD5,0x2B12D99F,0x9B3012D5,0x69A20CEA,0x68FF7C12,0xC1B11E74,0x65927E8D,0x71FE387C,0x434A56D1,0x3A54F0EC,0xB0B7FC5B,0x849D0D16,0x61DC8C79,0x396E5E07,0x9927B108,0xB1A1BF00,0x1F6D72EB,0xF3715EDA,0x574D8F70,0x0463ABB0,0x1B5819E5,0xF71A84BF,0xD076CFD0,0xDB8D3094,0x0F61A8E3,0x60B8A63A,0x6EBD28A6,0xB9CDF40E,0xB21A0A47,0x166058CA,0xAA5E1443,0x23F56DDF,0x6E1AE2A9,0x53A789CF,0x95F1DCDE,0xE4D38BC1,0x38773164,0x0DD0E706,0x0C3AD766,0x7C88C6A8,0xCB8B9D4D,0x160127A7,0xF7A58111,0x898B2AA0,0xC15C9FC2,0xC48FF48C,0x11CE1574,0xDC356BBF,0xF144A8B4,0x59BA56D5,0xC17354E6,0xA0572CF6,0x85835F3F,0x30640CD3,0x8BE76EEF,0xEF80C511,0xD040D8A6,0x8FC4F6CA,0x60A39FD3,0x50B8CEA3,0x1554C2F8,0x44E82E57,0xA5AD29D1,0x8BF6F043,0x66252C13,0xEF99B8E2,0x93E5911D,0x524CB0A1,0xF4C31B5E,0xA38CB335,0xD717B336,0x084D705B,0x7D7A3E05,0x00807EA2,
};
static uint32_t  __attribute__((aligned(32))) PIC6_BITSTREAM_LTRP[]=
{
    0x9BE954E4,0x8F04E9CE,0x9EB07130,0xC0C412AB,0xC03A557E,0x7D640CEF,0x8F89EC2A,0xDB4D6985,0x5394A3AA,0xB84F838A,0x20531709,0x5EBD4B7A,0x51C69E31,0xDC3B6C87,0x22A460B9,0xDC1805EB,0x43259A0E,0xCF6E7DE5,0xC8EF28FC,0xEDD03B5D,0x2C41C80D,0x7437B79A,0x04D8577C,0x2BC8FC50,0x681CDDE3,0x614E04C6,0x80897C53,0x60E15299,0x8F4F021C,0x53926556,0x19692AD2,0xFC8DBFC7,0x4D22C265,0xADCE73EC,0xE405ED6F,0xB32260ED,0x58B09004,0x55F58785,0x96A97AA6,0x95B0C672,0x04D7DAE7,0x9824C63B,0x91F2C231,0x4A900E24,0xD980375A,0x098D4727,0x0AAC3032,0x06A0BFF3,0xDCA7B3A4,0x6EE70BC0,0x77D15A54,0x279DF82F,0x4F59586F,0x6CEC121C,0x04AA51AF,0x4829B1E6,0x0FA1A267,0xACE7C30D,0x6713F491,0xB34818D0,0xA8EB59BA,0xEA2E2D63,0x807E92B9,0x6C37BBFC,0xC817CBBD,0x4C1FDDE7,0x6501DDDE,0xC47F3C2B,0x8D678E71,0x789F8FEF,0x1F55D559,0x78BCDDE9,0x0C7CBC03,0x815E9883,0x66BBD35A,0xAB631B11,0xEEC44E06,0xCBCF62E3,0x845A67B6,0x97989D48,0x13CE37AE,0x30255432,0x897F3833,0x8505D150,0xF97561DB,0xCCE0C96B,0xF6D93D76,0xE2C547B6,0x24BC266E,0xEB4585DB,0x782ECB28,0x8B67CAF7,0x3D2D4D0A,0xABDF0F43,0xE5759475,0xBAAEC4D4,0x6BDDBE34,0x7EFFF8C0,0x3FFFF1DA,0xCCC3CE19,0x3E10E37A,0x5F823618,0x176472D8,0x0B54C82E,0x4220A4F6,0xA60D9C25,0xFE884BD9,0xE849718C,0x857CE990,0x34FA243B,0xE1305901,0x1D547D1A,0x3C91ABAC,0x9467AA39,0xB303C8FE,0xBDE84CEF,0x26233F28,0x0090A576,

};


int main(int argc, char** argv)
{
    printf("generateSPS start\n");

    InitHeaderCfg(176,144);

    AL_TAvcSps sps;
    AL_TBitStreamLite bsSps, bsPps, bsSliceHdr,nalBs;
    bsSps.pData = (uint8_t *)malloc(1000);
    bsSps.iBitCount = 0;
    bsSps.iMaxBits = 1000*8;
    bsSps.isOverflow = 0;

    bsPps.pData = (uint8_t *)malloc(1000);
    bsPps.iBitCount = 0;
    bsPps.iMaxBits = 1000*8;
    bsPps.isOverflow = 0;

    bsSliceHdr.pData = (uint8_t *)malloc(1000);
    bsSliceHdr.iBitCount = 0;
    bsSliceHdr.iMaxBits = 1000*8;
    bsSliceHdr.isOverflow = 0;

    nalBs.pData = (uint8_t *)malloc(40000);
    nalBs.iBitCount = 0;
    nalBs.iMaxBits = 40000*8;
    nalBs.isOverflow = 0;
        
    
    generateSPS(&sps);
    writeSps(&bsSps, &sps);

int i=0;
printf("iBitCount = %d, sps data\n", bsSps.iBitCount);
for(i=0;i<(bsSps.iBitCount +7)/8;i++)
    printf("0x%02x ", bsSps.pData[i]);

printf("\n");

    AL_TAvcPps pps;

    generatePPS(&pps, &sps);
    
    writePps(&bsPps, &pps);

    printf("iBitCount = %d, pps data\n", bsPps.iBitCount);
    for(i=0;i<(bsPps.iBitCount +7)/8;i++)
        printf("0x%02x ", bsPps.pData[i]);
    
    printf("\n");

    AL_TNalHeader spsNalHdr;
    spsNalHdr.bytes[0] = 0x27;
    spsNalHdr.size = 1;

    FlushNAL(&nalBs, AL_AVC_NUT_SPS, &spsNalHdr, bsSps.pData, bsSps.iBitCount);

    spsNalHdr.bytes[0] = 0x28;
    spsNalHdr.size = 1;

    FlushNAL(&nalBs, AL_AVC_NUT_PPS, &spsNalHdr, bsPps.pData, bsPps.iBitCount);




    AL_TEncSliceParam sp;
    AL_TPictureInfo pi;
    uint32_t hdrSize = 0;
    
    //first frame
    FillSliceParam(&sp, &pi, AL_SLICE_I, 0, 0, true);
    uint8_t sliceHdrData[2000];
    hdrSize = generateSliceHeader(&bsSliceHdr, &pi, &sp, sliceHdrData+1000,0, true);
    Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, sliceHdrData + 1000 - hdrSize, hdrSize);
    nalBs.iBitCount += hdrSize *8;

printf("nal size = %d, NAL data\n", (nalBs.iBitCount+7)/8);
for(i=0;i<(nalBs.iBitCount +7)/8;i++)
    printf("0x%02x ", nalBs.pData[i]);

printf("\n");    

    hdrSize = sizeof(PIC0_BITSTREAM_LTRP);
    Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, PIC0_BITSTREAM_LTRP, hdrSize);
    nalBs.iBitCount += hdrSize *8;
#if 0
    //second
    AL_BitStreamLite_Reset(&bsSliceHdr);
    FillSliceParam(&sp, &pi, AL_SLICE_P, 2, 1, false);

    hdrSize = generateSliceHeader(&bsSliceHdr, &pi, &sp, sliceHdrData+1000,0, true);
    Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, sliceHdrData + 1000 - hdrSize, hdrSize);
    nalBs.iBitCount += hdrSize *8;
    
    hdrSize = sizeof(PIC1_BITSTREAM_LTRP);
    Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, PIC1_BITSTREAM_LTRP, hdrSize);
    nalBs.iBitCount += hdrSize *8;


    //3rd
    AL_BitStreamLite_Reset(&bsSliceHdr);
    FillSliceParam(&sp, &pi, AL_SLICE_P, 4, 2, false);

    hdrSize = generateSliceHeader(&bsSliceHdr, &pi, &sp, sliceHdrData+1000,0, true);
    Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, sliceHdrData + 1000 - hdrSize, hdrSize);
    nalBs.iBitCount += hdrSize *8;

    hdrSize = sizeof(PIC2_BITSTREAM_LTRP);    
    Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, PIC2_BITSTREAM_LTRP, hdrSize);
    nalBs.iBitCount += hdrSize *8;
#endif
    uint32_t bitstreamSize[10];
    uint32_t  *bitstreamData[10];   
    bitstreamSize[0] = sizeof(PIC1_BITSTREAM_LTRP);
    bitstreamSize[1] = sizeof(PIC2_BITSTREAM_LTRP);
    bitstreamSize[2] = sizeof(PIC3_BITSTREAM_LTRP);
    bitstreamSize[3] = sizeof(PIC4_BITSTREAM_LTRP);
    bitstreamSize[4] = sizeof(PIC5_BITSTREAM_LTRP);
    bitstreamSize[5] = sizeof(PIC6_BITSTREAM_LTRP);

    bitstreamData[0] = PIC1_BITSTREAM_LTRP;
    bitstreamData[1] = PIC2_BITSTREAM_LTRP;
    bitstreamData[2] = PIC3_BITSTREAM_LTRP;
    bitstreamData[3] = PIC4_BITSTREAM_LTRP;
    bitstreamData[4] = PIC5_BITSTREAM_LTRP;
    bitstreamData[5] = PIC6_BITSTREAM_LTRP;

    int frame=0;
    int frame_no = 0;
    int curPOC = 0;
    for(frame=0;frame<6;frame++)
    {
        frame_no++;
        curPOC += 2;
        AL_BitStreamLite_Reset(&bsSliceHdr);
        FillSliceParam(&sp, &pi, AL_SLICE_P, curPOC, frame_no, false);
        
        hdrSize = generateSliceHeader(&bsSliceHdr, &pi, &sp, sliceHdrData+1000,0, true);
        Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, sliceHdrData + 1000 - hdrSize, hdrSize);
        nalBs.iBitCount += hdrSize *8;
        
        hdrSize = bitstreamSize[frame];
        Rtos_Memcpy(nalBs.pData + nalBs.iBitCount/8, bitstreamData[frame], hdrSize);
        nalBs.iBitCount += hdrSize *8;

    }


    FILE *fp = fopen("./stream.264", "wb");
    if(fp == NULL)
        printf("open file failed\n");

    fwrite(nalBs.pData, nalBs.iBitCount/8,1,fp);

    if(fp)
        fclose(fp);
    free(bsSliceHdr.pData);
    free(nalBs.pData);
    free(bsSps.pData);
    free(bsPps.pData);

    return 0;
}
#endif
