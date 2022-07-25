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

#pragma once

#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VENC_MAX_CHANNELS (8)

typedef void* EncoderHandle;

typedef enum
{
    Enc_SUCCESS = 0, 
    Enc_ERR = 1,
}EncStatus;

typedef enum
{
    B_SLICE,
    P_SLICE,
    I_SLICE,
    IDR_SLICE
}EncSliceType;


typedef enum
{
    CONST_QP, 
    CBR, 
    VBR
} RateCtrlMode;

typedef enum
{
    AVC_C_BASELINE, 
    AVC_MAIN, 
    AVC_HIGH,
    JPEG
} AVC_Profile;

typedef enum
{
    ASPECT_RATIO_AUTO, 
    ASPECT_RATIO_4_3, 
    ASPECT_RATIO_16_9, 
    ASPECT_RATIO_NONE
} AVC_AspectRatio;

typedef struct
{
    unsigned int          s32X;
    unsigned int          s32Y;
    unsigned int          u32Width;
    unsigned int          u32Height;
}RECT_S;

typedef struct 
{
    unsigned int          uIndex;//index[0-7]
    bool                  bEnable;
    int                   uQpValue;
    RECT_S                stRect;
}EncROICfg;

typedef enum
{
    ROI_QP_TABLE_NONE,
    ROI_QP_TABLE_RELATIVE,//[-31,31],6 LSBs effective
    ROI_QP_TABLE_ABSOLUTE,//[0,51],6 LSBs effective
} ROICtrlMode;

typedef enum
{
    GDR_VERTICAL = 0,
    GDR_HORIZONTAL ,
    GDR_CTRLMAX,
}GDRCtrlMode;

typedef struct
{
    bool bSplitEnable;
    unsigned int u32SplitMode; // 0:splite by byte; 1:splite by slice count
    unsigned int u32SliceSize;
}EncSliceSplitCfg;

typedef enum
{
    ENTROPY_MODE_CABAC = 0,
    ENTROPY_MODE_CAVLC,
    ENTROPY_MODE_MAX,
}EncEntropyMode;

typedef struct
{
    unsigned int  disable_deblocking_filter_idc;//[0,2]
    int  slice_alpha_c0_offset_div2;//[-6,6]
    int  slice_beta_offset_div2;//[-6,6]
}EncDblkCfg;

typedef enum
{
    SECTION_SEI_PREFIX_FLAG = 0x80000000, /*< this section data is from a SEI prefix */
    SECTION_SYNC_FLAG = 0x40000000, /*< this section data is from an IDR */
    SECTION_END_FRAME_FLAG = 0x20000000, /*< this section denotes the end of a frame */
    SECTION_CONFIG_FLAG = 0x10000000, /*< section data is an sps, pps, vps, aud */
    SECTION_FILLER_FLAG = 0x08000000, /*< section data contains filler data */
    SECTION_APP_FILLER_FLAG = 0x04000000, /*< section data contains uninitialized filler data that should be filled by the application layer*/
}SectionFlags;

typedef struct
{
    int                       channel;  //encode channel number
    unsigned short            width;
    unsigned short            height;
    unsigned char             FrameRate;
    RateCtrlMode              rcMode;
    unsigned int              BitRate;
    unsigned int              MaxBitRate;
    int                       SliceQP;  //auto: -1, or from 0 to 51
    int                       MinQP;//from 0 to SliceQP
    int                       MaxQP;//from SliceQP to 51
    AVC_Profile               profile;
    unsigned int              level;  //1 .. 51, 51 is 5.1
    AVC_AspectRatio           AspectRatio;
    int                       FreqIDR; //default value  : -1,IDR:number of frames between two IDR pictures;GDR:refresh period
    unsigned int              gopLen;  
    bool                      bEnableGDR;//gdr
    GDRCtrlMode               gdrMode;
    bool                      bEnableLTR;//Long Term reference
    bool                      lossless; //jpeg lossless encode

    ROICtrlMode               roiCtrlMode;
    EncSliceSplitCfg          sliceSplitCfg;
    EncEntropyMode            entropyMode;//Profile is set to AVC_MAIN or AVC_HIGH is valid
    EncDblkCfg                encDblkCfg;
}EncSettings;	

typedef struct
{
    unsigned short width;
    unsigned short height;
    unsigned short stride;
    unsigned char *data;
}EncInputFrame;

typedef struct
{
    unsigned int uOffset; /*!< Start offset of the section (in bytes from the beginning of the buffer) */
    unsigned int uLength; /*!< Length in bytes of the section */
    SectionFlags uFlags; /*!< Flags associated with the section; see macro SectionFlags*/
}StreamSection;

typedef enum 
{
    EM_VIDEO_PACKET_UNKOWN = 0,
    EM_VIDEO_PACKET_IDR,
    EM_VIDEO_PACKET_P,
}EncVideoPacketType;

typedef struct
{
    unsigned char *bufAddr;
    unsigned int bufSize;  
    EncVideoPacketType packetType;
}EncOutputStream;

typedef struct
{
    unsigned char *bufAddr;
    unsigned int bufSize; 
    unsigned int uNumSection; /*!< number of sections inside the buffer */ 
    StreamSection* pSections;  /*!< Array of sections */
}EncOutputStreamSection;

EncoderHandle* VideoEncoder_Create(EncSettings *pCfg);
EncStatus      VideoEncoder_SetRoiCfg(EncoderHandle *hEnc,const EncROICfg*pEncRoiCfg);

EncStatus      VideoEncoder_SetLongTerm(EncoderHandle *hEnc);
EncStatus      VideoEncoder_UseLongTerm(EncoderHandle *hEnc);  
EncStatus      VideoEncoder_InsertUserData(EncoderHandle *hEnc,char*pUserData,unsigned int nlen);




EncStatus VideoEncoder_Destroy(EncoderHandle *hEnc);

EncStatus VideoEncoder_EncodeOneFrame(EncoderHandle *hEnc, EncInputFrame *input);


EncStatus VideoEncoder_EncodeOneFrame_Async(EncoderHandle *hEnc, EncInputFrame *input, void (*callback)());

EncStatus VideoEncoder_GetStream(EncoderHandle *hEnc, EncOutputStream *output);
EncStatus VideoEncoder_GetStream_ByExtBuf(EncoderHandle *hEnc,EncOutputStream *output);


EncStatus VideoEncoder_GetStreamSection(EncoderHandle *hEnc, EncOutputStreamSection *output);

EncStatus VideoEncoder_ReleaseStream(EncoderHandle *hEnc, EncOutputStream *output);

EncStatus VideoEncoder_ReleaseStreamSection(EncoderHandle *hEnc, EncOutputStreamSection *output);

#ifdef __cplusplus
}
#endif


