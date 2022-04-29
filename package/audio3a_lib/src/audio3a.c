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
#include "AGC/agc.h"
#include "NS/noise_suppression.h"

#include <math.h>
#include <stdbool.h>
#include "audio3a.h"
#include "voice_short_far.h"


#define ENABLE_AEC              1
#define ENABLE_AGC              1
#define ENABLE_NS               1
int debug_aec = 0;

#define PROCESS_320_BYTE

#ifndef nullptr
#define nullptr 0
#endif

#ifndef MIN
#define MIN(A, B)        ((A) < (B) ? (A) : (B))
#endif

extern short voice_short_far[];

// 4 types, the second is the best
void *agcInst = NULL;
int agcInit(int16_t agcMode, int sample_rate)
{
    printf("%s->%s\n", __FILE__, __FUNCTION__);
    WebRtcAgcConfig agcConfig;

    agcConfig.compressionGaindB = 9; // default 9 dB
    agcConfig.limiterEnable = 1; // default kAgcTrue (on)
    agcConfig.targetLevelDbfs = 3; // default 3 (-3 dBOv)
    
    int minLevel = 0;
    int maxLevel = 255;
    int status;

    agcInst = WebRtcAgc_Create();
    if (agcInst == NULL) return -1;

    status = WebRtcAgc_Init(agcInst, minLevel, maxLevel, agcMode, sample_rate);
    printf("%s->%s: agcInst->fs: %u\n", __FILE__, __FUNCTION__, ((LegacyAgc *)agcInst)->fs);
    if (status != 0)
    {
        printf("WebRtcAgc_Init fail\r\n");
        WebRtcAgc_Free(agcInst);
        return -1;
    }
    status = WebRtcAgc_set_config(agcInst, agcConfig);
    if (status != 0)
    {
        printf("WebRtcAgc_set_config fail\r\n");
        WebRtcAgc_Free(agcInst);
        return -1;
    }

    return 0;
}

int agcRun(int16_t *buffer, size_t samplesCount/*160*/)
{
    int inMicLevel = 0;
    int outMicLevel = -1;
    size_t num_bands = 1;
    uint8_t saturationWarning = 1;               //是否有溢出发生，增益放大以后的最大值超过了65536
    int16_t echo = 0;                            //增益放大是否考虑回声影响

    int16_t *input = buffer;
    int16_t out_buffer[320];
    int16_t *out16 = out_buffer;

    int nAgcRet = WebRtcAgc_Process(agcInst, (const int16_t *const *) &input, num_bands, samplesCount,
                                    (int16_t *const *) &out16, inMicLevel, &outMicLevel, echo,
                                    &saturationWarning);
    memcpy(input, out_buffer, samplesCount * sizeof(int16_t));

    if (nAgcRet != 0)
    {
        printf("failed in WebRtcAgc_Process\r\n");
        WebRtcAgc_Free(agcInst);
        return -1;
    }
    return 0;
}

int agcDeInit()
{
    WebRtcAgc_Free(agcInst);
    return 0;
}

NsHandle **NsHandles = NULL;/* only one channel */
int nsInit(enum nsLevel level, int sample_rate)
{
    printf("%s->%s\n", __FILE__, __FUNCTION__);
    int status;

    NsHandles = (NsHandle **) malloc(1 * sizeof(NsHandle *));
    if(NsHandles  == NULL) return -1;

    NsHandles[0] = WebRtcNs_Create();
    if(NULL == NsHandles[0]) return -1;

    status = WebRtcNs_Init(NsHandles[0], sample_rate);

    if (status != 0) 
    {
        WebRtcNs_Free(NsHandles[0]);
        NsHandles[0] = NULL;
        return -1;
    }

    status = WebRtcNs_set_policy(NsHandles[0], level);
    if (status != 0)
    {
        WebRtcNs_Free(NsHandles[0]);
        NsHandles[0] = NULL;
        return -1;
    }

    return 0;
}

int nsRun(int16_t *input, int16_t *output, int samples/*160*/)
{
    uint32_t num_bands = 1;

    if(samples != 160) return -1;

    WebRtcNs_Analyze(NsHandles[0], input);
    WebRtcNs_Process(NsHandles[0], (const int16_t *const *)&input, num_bands, &output);
    return 0;
}

int nsDeInit()
{
    WebRtcNs_Free(NsHandles[0]);
    return 0;
}

#include "../include/speex/speex_echo.h"
#include "../include/speex/speex_preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// #include <core_v5.h>

SpeexEchoState *st;
SpeexPreprocessState *den;

#ifdef PROCESS_320_BYTE
#define AEC_FRAME_SIZE 320
#else
#define AEC_FRAME_SIZE  160
#endif
#define AEC_SAMPLE_RATE 16000
#define PI 3.14159265358979323846264338327

short simulate_far[AEC_FRAME_SIZE];
short far_mute[AEC_FRAME_SIZE]={0};

void wy_aec_init(int sample_rate)
{
    printf("%s->%s\n", __FILE__, __FUNCTION__);
    int sampleRate = sample_rate;
    int aec_frame_size = (10 * sample_rate * 1.0)/1000;
    int filterLen = (10 * sample_rate * 1.0)/1000;;

    // st = speex_echo_state_init(aec_frame_size, filterLen);
    st = speex_echo_state_init_mc(aec_frame_size, filterLen, 2, 2);
    aec_frame_size *= 2;
    den = speex_preprocess_state_init(aec_frame_size, sampleRate);
    speex_echo_ctl(st, SPEEX_ECHO_SET_SAMPLING_RATE, &sampleRate);
    speex_preprocess_ctl(den, SPEEX_PREPROCESS_SET_ECHO_STATE, st);
    return;
}

uint64_t aec_one_second_cycles = 0;
uint32_t aec_rcv_cnt           = 0;

void wy_aec_process(short *near, short *out)
{
    // printf("%s->%s\n", __FILE__, __FUNCTION__);

    static uint32_t index = 0;

    for(int i = 0; i < AEC_FRAME_SIZE; i++)
    {
        //near[i] += simulate_far[i];
        near[i]+=voice_short_far[index*AEC_FRAME_SIZE+i];
        //out[i]=near[i];
    }

    //speex_echo_cancellation(st, near, &far_mute, out);
#if 1
    speex_echo_cancellation(st, near,&voice_short_far[index*AEC_FRAME_SIZE], out);
#else
    memcpy(out, near, 640);
#endif
    index++;
    if(index >= (120000/AEC_FRAME_SIZE)) index=0;
}

void wy_aec_deinit()
{
    speex_echo_state_destroy(st);
    speex_preprocess_state_destroy(den);
    debug_aec = 0;
}

#define EVB_BOARD_PDM_MIC

/*---------------------配置说明------------------------------- */
#define AUDIO_PRINT_ENABLE                  //控制打印
#define AUDIO_PDM_SAMPLE             16000           /*参数为16000时,FPGA_AUDIO_SCLK需要1024000以上
                                                      参数为44100时,FPGA_AUDIO_SCLK任意*/
#ifdef EVB_BOARD_PDM_MIC
#define AUDIO_PDM_RX_CH_NUM          1
#define AUDIO_PDM_RX_EDGE            AUDIO_IN_PDM_RISING
#else
#define AUDIO_PDM_RX_CH_NUM          2                      /*通道为1/2/8,CPU收发只能配置2*/ /*I2S指的是多少个双声道,1是1路左右声道, PDM指的是多少个单声道*/
#define AUDIO_PDM_RX_EDGE            AUDIO_IN_PDM_BOTH      /*FPGA_PDM_RX_CH_NUM=1，配置RISING*/
#endif

#define AUDIO_I2S_TX_CH_NUM          1               //固定配置 /*I2S指的是多少个双声道,1是1路左右声道, PDM指的是多少个单声道*/ 
#define AUDIO_PDM_RX_DMA_EN          true
#define AUDIO_I2S_TX_DMA_EN          true
#define AUDIO_PDM_RX_DMA_CH          DMA_CHANNEL_0
#define AUDIO_I2S_TX_DMA_CH          DMA_CHANNEL_1

#define AUDIO_PDM_RX_ALIGH           AUDIO_IN_RIGHT_ALIGN

#define AUDIO_PDM_CH_PLAY_ID         0//0 for id 0, 1 for id 1, 2 for both

#define AUDIO_I2S_WORD_LEN           32

//如果缓冲区太小，会处理错乱，对数据比较多，pingpong处理消耗时间，如果缓冲区大，则处理时间足够，但是延迟大
#if USE_ALSA_FRAME_SIZE
#define AUDIO_PDM_DMA_BUFFER_SIZE 64
#else
#ifdef PROCESS_320_BYTE
#define AUDIO_PDM_DMA_BUFFER_SIZE    320
#else
#define AUDIO_PDM_DMA_BUFFER_SIZE    160             /*注意:修改这玩意不能乱改,需要和dma burst有整数倍关系才行, 内部DMA burst先搞成1*/
#endif
#endif

/*备注:
  1.PDM sample 为16K(线路2.048MHz), 128降采样; 现在用i2s master来拖output, 但是I2S的线路时钟in=out同源;
    在此种模式下，I2S的采样率为: 2.048MHz/64(sclk双声道) = 32K, 但是PDM只有16K, 需要内插数据,resample,即插入双倍数据

  2.PDM sample 为44.1K(线路2.8224MHz), 64降采样, I2S输出则刚好是44.1K*/


/* define pin accodring to schematic */
#ifdef EVB_BOARD_PDM_MIC
/*3.3V*/
#define AUDIO_PDM_MIC_SCLK_PIN      110
#define AUDIO_PDM_MIC_IN0_PIN       111
#else 
/* mic array */
#define AUDIO_PDM_MIC_SCLK_PIN      103 /* 原理图 MIC_BCK j16-3*/
#define AUDIO_PDM_MIC_IN0_PIN       102 /* 原理图 MIC_BCK j16-11*/
#define AUDIO_PDM_MIC_IN1_PIN       101 /* 原理图 MIC_BCK j16-9*/
#define AUDIO_PDM_MIC_IN2_PIN       100 /* 原理图 MIC_BCK j16-7*/
#define AUDIO_PDM_MIC_IN3_PIN       99  /* 原理图 MIC_BCK j16-5*/
#endif

/* I2S codec */
#define AUDIO_I2S_CODEC_WS_PIN      106
#define AUDIO_I2S_CODEC_SCLK_PIN    121
#define AUDIO_I2S_CODEC_OUT0_PIN    107

/* dma */
static bool pdm_rx_half_done = false;
static bool i2s_tx_half_done = false;
static bool pdm_rx_timeout  = false;
static bool pdm_rx_done     = false;
static bool i2s_tx_timeout  = false;
static bool i2s_tx_done     = false;
static int audio_pdm_rx_buffer_ping[AUDIO_PDM_DMA_BUFFER_SIZE*8];
static int audio_pdm_rx_buffer_pong[AUDIO_PDM_DMA_BUFFER_SIZE*8];

static int audio_i2s_tx_buffer_ping[AUDIO_PDM_DMA_BUFFER_SIZE*4]; //最大数据量
static int audio_i2s_tx_buffer_pong[AUDIO_PDM_DMA_BUFFER_SIZE*4]; //最大数据量


static int *audio_pdm_rx_buffer_ping_bit33;
static int *audio_pdm_rx_buffer_pong_bit33;

static int *audio_i2s_tx_buffer_ping_bit33;
static int *audio_i2s_tx_buffer_pong_bit33;

static int *audio_pdm_rx_buffer_bit33_current;
static int *audio_pdm_rx_buffer_bit33_backup;

static int *audio_i2s_tx_buffer_bit33_current;

static int audio_pdm_rx_buffer_index = 0;

static bool pdm_rx_parse_done = false;

uint32_t audio_3a_rcv_cnt                 = 0;

void audio_3a_process(int *inbuf, int *outbuf)
{
    // printf("%s-%s\n", __FILE__, __FUNCTION__);
    short aec_out[AUDIO_PDM_DMA_BUFFER_SIZE];
    uint64_t now;
    uint64_t last;
    short *pOut = (short *)outbuf;

#if ENABLE_AEC
    if(debug_aec)
    {
        wy_aec_process(inbuf, aec_out);
    }
#endif

#if ENABLE_AGC
    else
    {
        memcpy(aec_out, inbuf, 640);
    }
    agcRun(aec_out, 160);
#ifdef PROCESS_320_BYTE
    agcRun(&aec_out[160],160);
#endif

#endif
    // printf("1\n");
#if ENABLE_NS
    nsRun(aec_out, pOut, 160);
#ifdef PROCESS_320_BYTE
    nsRun(&aec_out[160], &pOut[160], 160);
#endif
#else
#ifdef PROCESS_320_BYTE
    memcpy(pOut, aec_out, 320);
#else
    memcpy(pOut, aec_out, 160);
#endif
#endif
    // printf("2\n");
}


void audio_3a_init(int sample_rate, EAgcMode agcMode, ENsLevel nsLevel, int aec_test_en)
{
    // printf("%s->%s\n", __FILE__, __FUNCTION__);
    //wy_aec_init(aec_sample_rate, aec_frame_size);

#if ENABLE_AEC
    if (aec_test_en)
    {
	    wy_aec_init(sample_rate);
        debug_aec = 1;
    }
#endif

#if ENABLE_AGC
    if(0 != agcInit(agcMode, sample_rate))
    {
        printf("agc init error!\r\n");
        while(1);
    }
#endif

#if ENABLE_NS
    if(0 != nsInit(nsLevel, sample_rate))
    {
        printf("ns init error!\r\n");
        while(1);
    }
#endif
}

void audio_3a_deinit()
{
    if(debug_aec)
    {
        wy_aec_deinit();
    }
    agcDeInit();
    nsDeInit();
}
