/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

//宏定义macro definition//
#define uint8_t  unsigned char
#define uint16_t unsigned int

/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"
#include "MC96F6508A.h"
#include "func_def.h"
#include "led_mode.h"
#include "bt_mode.h"
#include "key_mode.h"

/************************/
/*宏定义macro definition*/
/************************/

/*************************/
/*类型定义byte definition*/
/*************************/
typedef enum
{
	PLAY_OFF = 0,
	PLAY_JUST_POWER,//刚上电，全显2s和设置时间
	PLAY_ALARM,
	PLAY_IN_TIME,//走时模式
	PLAY_IN_TIME_BT     ,
	//PLAY_IN_TIME_TF_CARD,
}PLAY_MODE_TypeDef;

typedef enum
{
	ALARM_BT  =1,
	ALARM_BEEP  ,
}ALARM_MODE_TypeDef;//闹钟响闹模式选择的声音来源，是蓝牙还是beep

typedef struct
{
	uint8_t  enable;	//闹钟总开关
	uint8_t  week;	
	uint8_t  hour;  //判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
	uint8_t  minute;//判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
	uint8_t  tempHour;  //因为设置闹钟有个确认设置(虽然作用不大),所以需要有个临时变量作为中间值，等
	uint8_t  tempMinute;//到缺人设置或者30s后自动确认再把tempXxx这几个变量赋给闹钟的最后设定时间
	uint8_t  runing; 
	uint8_t  cntTimer;	
	uint8_t  Flag_Confirm_TimeCnt_30Sec;//短按ALARM键确认设置或不动作30s自动保存，(为1是确认闹钟设置标
										//志位),为2是30s计时标志位，
	ALARM_MODE_TypeDef  Alarm_Mode;
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
void app_main(void);
void Sys_Tick(void);
/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/
extern PLAY_MODE_TypeDef  TYPE_Play_Mode;
extern ALRAM_TypeDef  TYPE_Alarm1;

/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/

/*************************************/
/*外部调用_变量定义variable definition*/
/*************************************/
extern bit			  gbHalfSecong;
extern uint8_t  idata gRTC_Sec;//RTC数据 
extern uint8_t  idata gRTC_Sec_bk;
extern uint8_t  idata gRTC_Minute;
extern uint8_t  idata gRTC_Minute_bk;
extern uint8_t  idata gRTC_Hour;
extern uint8_t  idata gRTC_Hour_bk;
extern uint8_t  xdata gRTC_Hour_bk_24;//计数24小时
extern uint8_t  idata gRTC_Week; 
extern uint8_t  idata sys_Volume;
extern uint16_t idata timeCnt_30Sec;
/**********************************/
/*外部调用_数组定义array definition*/
/**********************************/

/**************************************/
/*外部调用_函数声明Function declaration*/
/**************************************/
//extern void app_main(void);
//extern void Sys_Tick(void);
/*************************************/
/*外部调用_函数定义function definetion*/
/*************************************/





#endif







