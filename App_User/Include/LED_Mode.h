/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __LED_MODE_H__
#define __LED_MODE_H__
/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"

/************************/
/*宏定义macro definition*/
/************************/
#define S_NC  7
#define S_A   0		//  AAAAA
#define S_B   1		// F     B
#define S_C   2		// F     B
#define S_D   3		//  GGGGG
#define S_E   4		// E     C
#define S_F   5		// E     C
#define S_G   6		//  DDDDD

//#define S_NC  7
//#define S_A   0		//  AAAAA
//#define S_B   4		// F     B
//#define S_C   5		// F     B
//#define S_D   6		//  GGGGG
//#define S_E   3		// E     C
//#define S_F   1		// E     C
//#define S_G   2		//  DDDDD

#define DIG_0   (1<<S_A)|(1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)  //0是6个段，上面的是对应的端口
#define DIG_1            (1<<S_B)|(1<<S_C)
#define DIG_2   (1<<S_A)|(1<<S_B)         |(1<<S_D)|(1<<S_E)         |(1<<S_G)
#define DIG_3   (1<<S_A)|(1<<S_B)|(1<<S_C)|(1<<S_D)                  |(1<<S_G)
#define DIG_4            (1<<S_B)|(1<<S_C)                  |(1<<S_F)|(1<<S_G)
#define DIG_5   (1<<S_A)         |(1<<S_C)|(1<<S_D)         |(1<<S_F)|(1<<S_G)
#define DIG_6   (1<<S_A)         |(1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)|(1<<S_G)
#define DIG_7   (1<<S_A)|(1<<S_B)|(1<<S_C)
#define DIG_8   (1<<S_A)|(1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)|(1<<S_G)
#define DIG_9   (1<<S_A)|(1<<S_B)|(1<<S_C)|(1<<S_D)         |(1<<S_F)|(1<<S_G)
#define DIG_NONE  0x00                    // SPACE
#define CH_a    (1<<S_A)|(1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)         |(1<<S_G)
#define CH_b                      (1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_c                               (1<<S_D)|(1<<S_E)         |(1<<S_G)
#define CH_d             (1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)         |(1<<S_G)
#define CH_h                      (1<<S_C)         |(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_l             (1<<S_B)|(1<<S_C)
#define CH_n                      (1<<S_C)         |(1<<S_E)         |(1<<S_G)
#define CH_o                      (1<<S_C)|(1<<S_D)|(1<<S_E)         |(1<<S_G)
#define CH_r                                        (1<<S_E)         |(1<<S_G)
#define CH_t                               (1<<S_D)|(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_u                      (1<<S_C)|(1<<S_D)|(1<<S_E)
#define CH_y             (1<<S_B)|(1<<S_C)|(1<<S_D)         |(1<<S_F)|(1<<S_G)
#define CH_A    (1<<S_A)|(1<<S_B)|(1<<S_C)         |(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_C    (1<<S_A)                  |(1<<S_D)|(1<<S_E)|(1<<S_F)
#define CH_E    (1<<S_A)                  |(1<<S_D)|(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_F    (1<<S_A)                           |(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_G    (1<<S_A)         |(1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)
#define CH_H             (1<<S_B)|(1<<S_C)         |(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_I             (1<<S_B)|(1<<S_C)
#define CH_J             (1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)
#define CH_L                               (1<<S_D)|(1<<S_E)|(1<<S_F)
#define CH_N    (1<<S_A)|(1<<S_B)|(1<<S_C)         |(1<<S_E)|(1<<S_F)
#define CH_O    (1<<S_A)|(1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)
#define CH_P    (1<<S_A)|(1<<S_B)                  |(1<<S_E)|(1<<S_F)|(1<<S_G)
#define CH_S    (1<<S_A)         |(1<<S_C)|(1<<S_D)         |(1<<S_F)|(1<<S_G)
#define CH_U             (1<<S_B)|(1<<S_C)|(1<<S_D)|(1<<S_E)|(1<<S_F)
#define CH__    (1<<S_G)

enum
{
	eD_0 = 0,  //D:display
	eD_1,
	eD_2,
	eD_3,
	eD_4,
	eD_5,
	eD_6,
	eD_7,
	eD_8,
	eD_9,
	eD_NONE,
	eD_a,
	eD_b,
	eD_c,
	eD_d,
	eD_e,
	eD_f,
	eD_g,
	eD_h,
	eD_i,
	eD_j,
	eD_k,
	eD_l,
	eD_m,
	eD_n,
	eD_o,
	eD_p,
	eD_q,
	eD_r,
	eD_s,
	eD_t,
	eD_u,
	eD_v,
	eD_w,
	eD_x,
	eD_y,
	eD_z,
	eD_A,
	eD_B,
	eD_C,
	eD_D,
	eD_E,
	eD_F,
	eD_G,
	eD_H,
	eD_I,
	eD_J,
	eD_K,
	eD_L,
	eD_M,
	eD_N,
	eD_O,
	eD_P,
	eD_Q,
	eD_R,
	eD_S,
	eD_T,
	eD_U,
	eD_V,
	eD_W,
	eD_X,
	eD_Y,
	eD_Z,
	eD__,
};

enum
{
	eDS_RTC = 0, //DS:display segment
	eDS_AL1,
};

#define cDISP_DELAY__0SEC    0
#define cDISP_DELAY__60ms    6     //cDISP_DELAY__62ms5   1
#define cDISP_DELAY__125ms   2
#define cDISP_DELAY__500ms   50    // 50  ×10ms  = 500ms
#define cDISP_DELAY__1SEC    16    // 16 ×62ms50 = 1000ms
#define cDISP_DELAY__2SEC    32    // 32 ×62ms50 = 2000ms
#define cDISP_DELAY__3SEC    48    // 48 ×62ms50 = 3000ms
#define cDISP_DELAY__4SEC    64    // 48 ×62ms50 = 3000ms
#define cDISP_DELAY__5SEC    80    // 80 ×62ms50 = 5000ms
#define cDISP_DELAY__6SEC    96    // 80 ×62ms50 = 5000ms
#define cDISP_DELAY__6_5SEC  104   // 80 ×62ms50 = 5000ms
#define cDISP_DELAY_10SEC    10000  // 1000×10ms  = 10000ms
#define cDISP_DELAY_14SEC    224   // 240×62ms50 = 15000ms
#define cDISP_DELAY_14_5SEC  232   // 240×62ms50 = 15000ms
#define cDISP_DELAY_15SEC    240   // 240×62ms50 = 15000ms


/*************************/
/*类型定义byte definition*/
/*************************/
typedef enum
{
	LED_TURN_OFF = 0,
	LED_LOW			,
	LED_MEDIUM   	,
	LED_HIGH	 	,
}LED_BRIGHTNESS_TypeDef;

typedef enum
{
	ALARM_NONE = 0,
	ALARM_BT 	  ,
	ALARM_BEEP	  ,
}ALARM_WORK_MODE_TypeDef;//闹钟响闹模式选择的声音来源，是蓝牙还是beep

typedef enum
{
	ALARM_OFF = 0,
	ALARM_ON    ,
}ALARM_ONOFF_TypeDef;

typedef enum
{
	ALARM_SNOOZE_OFF = 0, //闹钟响了之后有没有贪睡，0是没有
	ALARM_SNOOZE_ON  = 1, //1是在贪睡
}ALARM_SNOOZE_TypeDef;

typedef enum
{
	ALARM_RING_TIME_OFF =0 ,
	ALARM_RING_TIME_ONE =60,//闹钟响闹时间60分钟
}ALARM_RING_TIMER_TypeDef;

typedef enum
{
	ALARM_RING_RUN_OFF = 0,//闹钟还没有响
	ALARM_RING_RUN_ON  = 1,//闹钟响了
}ALARM_RING_RUN_TypeDef;


typedef struct
{
	ALARM_ONOFF_TypeDef Alarm_OnOff;//闹钟总开关
	uint8_t  week;
	uint8_t  hour;  //判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
	uint8_t  minute;//判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
	uint8_t  tempHour;  //因为设置闹钟有个确认设置(虽然作用不大),所以需要有个临时变量作为中间值，等
	uint8_t  tempMinute;//到缺人设置或者30s后自动确认再把tempXxx这几个变量赋给闹钟的最后设定时间
	ALARM_RING_RUN_TypeDef Alarm_RingRun;
	ALARM_RING_TIMER_TypeDef Alarm_RingTimer;//闹钟响闹时间为60分钟
	uint8_t  Flag_Confirm_30Sec;//短按ALARM键确认设置或不动作30s自动保存，(为1是确认闹钟设置标
								//志位),为2是30s计时标志位，
	ALARM_WORK_MODE_TypeDef Alarm_WorkMode;
	ALARM_SNOOZE_TypeDef Alarm_Snooze;
	uint8_t  Flag_Again;
}ALRAM_TypeDef;

/****************************/
/*标志位定义flags definetion*/
/****************************/

/*****************************/
/*变量定义variable definition*/
/*****************************/

/**************************/
/*数组定义array definition*/
/**************************/

/******************************/
/*函数声明Function declaration*/
/******************************/
void Alarm1_PowerOFF(void);
void Display(void);
void SetDisplayState10s(uint8_t status);

/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/
extern LED_BRIGHTNESS_TypeDef  LED_Brightness_TypeDef;
extern ALRAM_TypeDef  Alarm1_TypeDef;
extern ALRAM_TypeDef  BK_Alarm1_TypeDef;

/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/
extern u8 bdata lcd_BitRam0;
extern u8 bdata lcd_BitRam1;
extern bit  gblcd_buz1;
extern bit  gblcd_al;//原来是gblcd_radio1
extern bit  gblcd_buz2;
extern bit  gblcd_radio2;
extern bit  gblcd_dot;//
extern bit  gblcd_colon;//
extern bit  gblcd_sleep;//
extern bit  gblcd_aux;
extern bit  gblcd_am ;//
extern bit  gblcd_pm;//
extern bit  gblcd_fm;
extern bit  gblcd_mw;
extern bit  gblcd_mhz;
extern bit  gblcd_khz;
extern bit  gblcd_five;
extern bit  gblcd_bt;
/*************************************/
/*外部调用_变量定义variable definition*/
/*************************************/
extern uint8_t  ledBrightness;//LED显示的亮度
extern uint8_t  alarmMinute;//判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
extern uint8_t  alarmHour;
extern uint8_t  tempAlarmMinute;//因为设置闹钟有个确认设置(虽然作用不大),所以需要有个临时变量作为中间值，等
extern uint8_t  tempAlarmHour;  //到缺人设置或者30s后自动确认再把tempXxx这几个变量赋给闹钟的最后设定时间

/**********************************/
/*外部调用_数组定义array definition*/
/**********************************/

/**************************************/
/*外部调用_函数声明Function declaration*/
/**************************************/

/*************************************/
/*外部调用_函数定义function definetion*/
/*************************************/

#endif




