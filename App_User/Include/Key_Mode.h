/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __KEY_MODE_H__
#define __KEY_MODE_H__
/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"

/************************/
/*宏定义macro definition*/
/************************/
#define	 K_D  		(1<<5) //0010_0000(0x20)
#define	 K_U  		(2<<5) //0100_0000(0x40)//短按
#define	 K_H  		(3<<5) //0110_0000(0x60)//长按保持 hold
#define	 K_R  		(4<<5) //1000_0000(0x80)//连击
#define	 K_L  		(5<<5) //1010_0000(0xA0)//长按
#define	 K_LU  		(6<<5) //1100_0000(0xC0)//超长按
#define	 KD(x)  	(x|K_D)
#define	 KU(x)  	(x|K_U)
#define	 KH(x)  	(x|K_H)
#define	 KR(x)  	(x|K_R)
#define	 KL(x)  	(x|K_L)
#define	 KLU(x)  	(x|K_LU)
#define  cKEY_CLICK     5   //单击时间常数
#define  cKEY_HOLD      50  //按住时间常数
#define  cKEY_RATE_VOL  20  //连击时间常数

/*************************/
/*类型定义byte definition*/
/*************************/
enum
{
	K_NC			 ,
	K_SNOOZE_DIMMER  ,//贪睡按键
	K_VOLINC		 ,//音量加 
	K_PLAY_PAUSE	 ,//暂停/播放
	K_NEXT			 ,//下一曲
	K_ALARM			 ,//闹钟
	K_VOLDEC		 ,//音量减
	K_BT			 ,//蓝牙
	K_PREV			 ,//上一曲
	K_AL_SNOOZE      ,//组合键-闹钟和贪睡-同时2s-时间设置(不是闹钟时间设置)，
	K_AL_VOLINC      ,//组合键-闹钟和音量加-同时2s-RTC时间加一小时，表示开启夏令时
	K_AL_VOLDEC      ,//组合键-闹钟和音量减-同时2s-RTC时间减一小时，表示关闭夏令时
};//按键功能

typedef enum
{
	FLAG_KEYSET_OFF 			   = 0,
	FLAG_KEYSET_SETTIME_HOUR		  ,//(走时模式)长按ALARM键和SNOZE键，进入时间设置模式的小时设置，接着再次
	FLAG_KEYSET_SETTIME_MINUTE		  ,//短按ALARM键，设置分钟，再次短按确认时间或者30s不动作自动保存，并返回
	//FLAG_KEYSET_SETTIME_CONFIRMSET	  ,//走时模式
	FLAG_KEYSET_SHORT_ALARM_HOUR	  ,//(走时模式)短按ALARM按键，进入设置闹钟时间模式，并开启闹钟功能，再次短
	FLAG_KEYSET_SHORT_ALARM_MINUTE	  ,//按ALARM键，进入设置分钟模式，再次短按ALARM键，选择响闹模式，第四次短
	FLAG_KEYSET_SHORT_ALARM_ALWORKMODE,//按ALARM键，确实闹钟时间设置，或者不动作30s自动保存，并返回走时模式
	//FLAG_KEYSET_SHORT_ALARM_CONFIRMSET,//
}FLAG_KEYSET_TypeDef;

typedef struct
{
	uint8_t  temp_RTC_Hour;
	uint8_t  temp_RTC_Minute;
	uint8_t  temp_RTC_Second;

	uint8_t  Flag_Confirm_30Sec;//短按ALARM键确认设置或不动作30s自动保存，(为1是确认闹钟设置标
								//志位),为2是30s计时标志位，
}TIME_TEMP_TypeDef;

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
void KeyScan(void);
void KeyComMsg(void);
/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/
extern FLAG_KEYSET_TypeDef  FlagKSet_TypeDef;//按键的功能设置标志
extern TIME_TEMP_TypeDef    Time_Temp_TypeDef;//设置时间时才把设置的时间先付给这个，然后确认了再赋值到gRTC_xx;
/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/

/*************************************/
/*外部调用_变量定义variable definition*/
/*************************************/

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



