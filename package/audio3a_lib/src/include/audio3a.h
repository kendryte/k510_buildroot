#include <stdio.h>

typedef enum _EAgcMode{
    AgcModeUnchanged,
    AgcModeAdaptiveAnalog,
    AgcModeAdaptiveDigital,
    AgcModeFixedDigital
}EAgcMode;

typedef enum nsLevel
{
    kLow,
    kModerate,
    kHigh,
    kVeryHigh
}ENsLevel;

typedef enum
{
    DSP_TASK_1_AUDIO3A_INIT,
    DSP_TASK_1_AUDIO3A_INIT_DONE,
    DSP_TASK_1_AUDIO3A_PROCESS,
    DSP_TASK_1_AUDIO3A_PROCESS_DONE,
    DSP_TASK_1_AUDIO3A_DEINIT,
    DSP_TASK_1_AUDIO3A_DEINIT_DONE,
    MAX_NUM_DSP_TASK_1_MSG
} Task1MsgID;

//the message should be defined in header file which is included by cpu
typedef struct tTASK1_MSG
{
    Task1MsgID  id;
    // uint32_t src_phyAddr;
    // uint32_t dst_phyAddr;
    // uint32_t data_size;
    int sample_rate;
    EAgcMode agcMode;
    ENsLevel nsLevel;
    int aec_test_en;
    // int init_done;
    int *inbuf;
    int *outbuf;
    int input_size;
    int output_size;
}TASK1_MESSAGE;

void audio_3a_init(int sample_rate, EAgcMode agcMode, ENsLevel nsLevel, int aec_test_en);
void audio_3a_process(int *inbuf, int *outbuf);
void audio_3a_deinit();
