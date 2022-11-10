#ifndef __3A_AE_CTL_H__
#define __3A_AE_CTL_H__

#define AE_CTL_MANUAL_SET_EXP_MODE 0
#define AE_CTL_MANUAL_SET_GAIN_MODE 1
#define AE_CTL_MANUAL_SET_TARGET_MODE 2
#define AE_CTL_MANUAL_SET_TARGET_RANGE_MODE 3
#define AE_CTL_MANUAL_SET_FROM_USER 4
enum ae_ctl_isp_pipeline_e
{
	AE_CTL_ISP_F2K_PIPELINE,
	AE_CTL_ISP_R2K_PIPELINE,
	AE_CTL_ISP_TOF_PIPELINE
};

enum ISP_AE_Mode
{
	AE_Auto,
	AE_Manual,
};

enum ISP_AE_Anti_Flicker_Mode
{
	Anti_flicker_50Hz_auto,
	Anti_flicker_60Hz_auto,
	Anti_flicker_50Hz_force,
	Anti_flicker_60Hz_force,
	Anti_flicker_None,
};

enum ISP_Backlight_Mode
{
	Normal,
	Backlight_Compensation,
	Stronglight_Suppression,
};

enum anti_flicker_scl_e
{
	ANTI_FLICKER_ALL_DSIABLE,
	ANTI_FLICKER_F2K_ENABLE,
	ANTI_FLICKER_R2K_ENABLE,
	ANTI_FLICKER_ALL2K_ENABLE,
};

enum ae_attr_page_stat_e
{
	AE_ATTR_PAGE_WAIT,
	AE_ATTR_PAGE_ON,
	AE_ATTR_PAGE_OFF,
	AE_ATTR_PAGE_ON_TO_OFF,
};

struct ISP_AE_Parameters {
	enum ISP_AE_Mode AE_Mode;
	enum ISP_AE_Anti_Flicker_Mode AE_AntiFlicker;	//Anti-flicker mode
	enum ISP_Backlight_Mode AE_Backlight;	//Backlight mode
	int target;		//get from AE_YOBJ
	int LockRange;	//get from AE_AV_RG
	int maxET; //get from AE_EXP_MAX
	int maxGain; //get from AE_AGC_MAX
	int minET;		//get from AE_EXP_MIN
	int minGain;	//get from AE_AGC_MIN
	int Lock_IntNum;	//get from AE_LKIN_SL, AE_LKIN_SL = 0: F2K_Lock_IntNum = 32; AE_LKIN_SL = 1: F2K_Lock_IntNum = 64;
	int Lock_OutNum;	//get from AE_LKOT_SL, AE_LKOT_SL = 0: F2K_Lock_OutNum = 32; AE_LKOT_SL = 1: F2K_Lock_OutNum = 64;

	int ET_Current;	//initial setting: get from AE_EXP_L
	int Gain_Current;	//initial setting: get from AE_AGC
	int ET_New;
	int Gain_New;
	int Def_Gain;
	unsigned long Max_Exposure_Value;	// F2K_maxET*F2K_maxGain
	unsigned long Min_Exposure_Value;	//F2K_minET  * F2K_minGain
	unsigned long  Old_Exposure_Value; // ET_Curren* Gain_Current
	unsigned long New_Exposure_Value;	//New_ET* New_Gain
	unsigned int ET_Set;
	unsigned int Gain_Set;

	int LockStatus;
	int Process;	//0：not in set AE process；1~ AESmoothSteps：in set AE process
	int Change;		//0: in the process of decrease the exposure value；1: in the process of  increasing the exposure value
	int FrameRate;	//Frame rate
	int FrameLines;	//ET lines per frame
	int AntiF_Lines;	//Based ET lines for Anti_Flicker 50Hz/60Hz
	int Anti_50Hz_Lines;	// 1/100s ET lines
	int Anti_60Hz_Lines;	//1/120s ET lines
    int ready_to_write_et; // need write exp time current frame
    int ready_to_write_gain; // need write gain current frame
	int user_re_init; // re init when param is changed
};

typedef struct {
    int nExpTimeLines;
    int nGain;
} AE_CTL_AE_STAT_T;

typedef struct {
	/* modify param */
	bool bDualCameraSync;
	int nSingleSensorETDelayFrame[2];
	int nSingleSensorSetMode[2];
	int nDualSensorETDelayFrame[2];
	int nDualSensorSetMode[2];
	int nFrameRate[2];
	/* fix param */
	int nAeSmoothSteps;	//将AE收敛分为9步完成,可设置, >=7 // internal

} AE_CTL_INIT_CFG_T;

typedef struct {
    char * cSensor0Name;
    char * cSensor1Name;
    AE_CTL_INIT_CFG_T * tAeCtlInitCfg;
} AE_CTL_SENSOR_NAME_T;

typedef struct {
	int nSize;
    AE_CTL_SENSOR_NAME_T * tAeCtlSensorName;
} AE_CTL_SENSOR_NAME_S_T;

typedef struct {
	int nAttePageEn;
	int nAeModeSwitch;
} AE_CTL_ATTR_PARAM;

typedef struct {
	int nAeTarBright;
	int nAeTarBrightRange;
	int nAeExValueMax;
	int nAeGainValueMax;
	int nAeExValueMin;
	int nAeGainValueMin;
	int nAeEnterLsSel;
	int nAeLExTime;
	int nAeAgc;
	int nTotalHeight;
} AE_CTL_ISP_INIT_PARAM;

extern bool Sensor1_Sync;
extern int AESmoothSteps;	//将AE收敛分为9步完成,可设置, >=7
extern int ETDelayFrameNumber[2];		//Sensor ET设置生效所需帧数
extern struct ISP_AE_Parameters AE_Para_Inf[2];

/* callback */
typedef int (* manual_set_callback)(enum ae_ctl_isp_pipeline_e pipeline, int value);

/* main functions */
int Anti_Flicker_ETL(enum ae_ctl_isp_pipeline_e pipeline);
int Set_AE_Value(enum ae_ctl_isp_pipeline_e pipeline, struct media_entity * pipe, AE_CTL_AE_STAT_T * ae_stat_callback);

/* user enable*/
int anti_flicker_scl(int scl);

/* user init */
int ae_ctl_cfg_init(int pipeline_en_f2k, int pipeline_en_r2k, AE_CTL_SENSOR_NAME_S_T ae_ctl_sensor_name_s, char * sensor0_name, char * sensor1_name);
int ae_ctl_init(enum ae_ctl_isp_pipeline_e pipeline, struct isp_core_cfg_info * isp_core_cfg);
// re init when param change online
int ae_ctl_reinit(enum ae_ctl_isp_pipeline_e pipeline);
// n: number of devices, ...  &(struct media_entity) f2k r2k sensor0 sensor1
int ae_ctl_device_init(int n, ...);

/* user functions */
int ae_ctl_calc(enum ae_ctl_isp_pipeline_e pipeline, struct k510isp_ae_stats ae_stats, struct media_entity * pipe, AE_CTL_AE_STAT_T * ae_stat_callback);
int ae_ctl_limit_range(enum ae_ctl_isp_pipeline_e pipeline, int min_et, int max_et, int max_gain);
int ae_ctl_manual_set(int set_mode, manual_set_callback userfunc, enum ae_ctl_isp_pipeline_e pipeline, int value,  AE_CTL_AE_STAT_T * ae_stat_callback);
int et_line_time_convert(enum ae_ctl_isp_pipeline_e pipeline, int exp_time);
int line_time_et_convert(enum ae_ctl_isp_pipeline_e pipeline, int et);
int anti_flicker_switch(enum ae_ctl_isp_pipeline_e pipeline, int scl);
int ae_ctl_sync_setting(enum ae_ctl_isp_pipeline_e pipeline, int ae_sync);
int ae_ctl_attr_page_stat_set_v2(enum ae_ctl_isp_pipeline_e pipeline, int stat);
int ae_ctl_attr_page_param_set(enum ae_ctl_isp_pipeline_e pipeline, AE_CTL_ATTR_PARAM page_attr);

/* user get version */
char * ae_ctl_get_version();

#endif