/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

//宏定义macro definition//

/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"
#include "MC96F6508A.h"
#include "func_def.h"
#include "user_define.h"
#include "led_mode.h"
#include "bt_mode.h"
#include "key_mode.h"
#include "led_drive.h"

/************************/
/*宏定义macro definition*/
/************************/
//设置蜂鸣器响还是不响
#define SET_BEEP(a)			if(a)				\  
								P0 |= 0x04;		\
							else				\
								P0 &= (~0x04);
#define SET_LED_RED(a)		if(a)				\  
								P5 |= 0x10;		\
							else                \
								P5 &= (~0x10);
//蓝牙开机，检测到蓝牙信号后，就设置输出1
#define BT_SET_LED_BLUE(a)  if(a)				\  
								P5 |= 0x08;		\
							else				\
								P5 &= (~0x08);

#define TF_CARD_DET()     (P0&0x01)    //检测TF卡是否插入
#define BT_MUTE_DET()     (P6&0x02)    //P62,检测蓝牙是否发出mute信号,1为不静音
#define BT_LED_RED_DET()  (P0&0x08)    //P03,检测蓝牙是否发出红色LED信号
#define BT_LED_BLUE_DET() (P5&0x20)    //P55,检测蓝牙是否开启，如果开启，就从另一个端口输出一个Blue LED

#define BT_SET_POWER()	  do{P6 |=  (0x01);}while(0)//P60,使能蓝牙，如果使能了使三极管导通，蓝牙芯片上电
#define BT_CLR_POWER()	  do{P6 &= (~0x01);}while(0)
#define __DE_MUTE()		  do{P0 |= ( 0x02);}while(0)//解mute
#define __EN_MUTE()		  do{P0 &= (~0x02);}while(0)//mute

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

enum
{
	DISP_CLK = 0,
	DISP_AL1,
	DISP_AL2,
	ADJ_CLK,
	ADJ_ZONE,
	ADJ_YEAR,
	ADJ_DATE,
	ADJ_ALARM1,
	ADJ_ALARM2,
	ALARM1_DISP,
	ALARM2_DISP,
	ADJ_ALARM1_MIN,
	ADJ_ALARM2_MIN,
	ADJ_ALARM1_HOUR,
	ADJ_ALARM2_HOUR,
	ADJ_ALARM1_MODE,
	ADJ_ALARM2_MODE,
	DISP_VOL,
	DISP_SLP,
	DISP_AUX,
	DISP_RADIO,
	DISP_GET_MEN,
	DISP_SAVE_MEN,
	POWER_OFF_DISP,
};

typedef enum
{
	CTRL_NONE = 0,
	CTRL_VOL0,
	CTRL_VOL15,
	CTRL_PAUSE,
	CTRL_PALY,
	CTRL_PREV,
	CTRL_NEXT,
}CONTROL_COMMAND_TypeDef;

#define   CNT_DELAY__15ms625        1    
#define   CNT_DELAY__31ms25         2    
#define   CNT_DELAY__62ms5          4   
#define   CNT_DELAY__78ms125        5 
#define   CNT_DELAY__93ms75         6 
#define   CNT_DELAY__109ms375       7      
#define   CNT_DELAY__125ms          8   
#define   CNT_DELAY__156ms25        10   
#define   CNT_DELAY__187ms5         12   
#define   CNT_DELAY__250ms          16  
#define   CNT_DELAY__359ms375       23   
#define   CNT_DELAY__500ms          32   
#define   CNT_DELAY_1000MS          64  
#define   CNT_DELAY_1500MS          96 
#define   CNT_DELAY_2000MS         128  
#define   CNT_DELAY_2500MS         160
#define   CNT_DELAY_3000MS         192  
#define   CNT_DELAY_4000MS         255   

#define   CNT_VOL__500ms           1 
#define   CNT_VOL__1000ms          2 
#define   CNT_VOL__1500ms          3 
#define   CNT_VOL__2000ms          4 
#define   CNT_VOL__2500ms          5 
#define   CNT_VOL__3000ms          6 
#define   CNT_VOL__3500ms          7 
#define   CNT_VOL__4000ms          8 

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
//void app_main(void);
//void Sys_Tick(void);
/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/
extern PLAY_MODE_TypeDef  PlayMode_TypeDef;
extern CONTROL_COMMAND_TypeDef Ctrl_Com_TypeDef;

/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/
extern BOOL  gb12HourDisp;
extern BOOL  gb0_5s;
extern BOOL  gbUser_AdjClk;
extern BOOL  gbHalfSecond;
extern BOOL  gbTestMode;
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
extern uint8_t  idata Snooze_Hour;//贪睡小时时间
extern uint8_t  idata Snooze_Minute;//贪睡分钟时间
extern uint8_t  idata sysVolume;
extern uint16_t idata timeCnt_30Sec;

extern uint8_t  idata cntNoFlash;
extern uint8_t		  gZone;
extern uint8_t    	  dispStatus;
extern uint8_t  idata cntAlarm;
extern int 			  testINT;
/**********************************/
/*外部调用_数组定义array definition*/
/**********************************/

/**************************************/
/*外部调用_函数声明Function declaration*/
/**************************************/
extern void app_main(void);
extern void Sys_Tick(void);
/*************************************/
/*外部调用_函数定义function definetion*/
/*************************************/
extern void UART_Def_Init();




#endif







