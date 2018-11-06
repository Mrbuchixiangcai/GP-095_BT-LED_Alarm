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
#define	 K_D  		(1<<5) //
#define	 K_U  		(2<<5) //短按
#define	 K_H  		(3<<5) //长按保持 hold
#define	 K_R  		(4<<5) //连击
#define	 K_L  		(5<<5) //长按
#define	 K_LU  		(6<<5) //超长按
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
	K_SNOOZE_PAUSE=1,
	K_VOLINC		,
	K_TIME_DIM		,
	K_NEXT			,
	K_ALARM			,
	K_VOLDEC		,
	K_BT			,
	K_PREV			,
};//按键功能

typedef enum
{
	FLAG_KEYSET_OFF 			   = 0,
	FLAG_KEYSET_JUST_POWER_LONG_TIME  ,//长按time标志，其他按键设置小时
	FLAG_KEYSET_JUST_POWER_SHORT_TIME ,//短按time标志，其他按键设置分钟
	//FLAG_KEYSET_IN_TIME_SHORT_TIME_DIM,//走时模式短按time标志，调整亮度
	FLAG_KEYSET_LONG_ALARM_HOUR		  ,//走时模式长按ALARM标志，其他按键设置小时
	FLAG_KEYSET_SHORT_ALARM_MINUTE	  ,//(走时模式)继续短按ALARM，其他按键设置分钟
	FLAG_KEYSET_SHORT_ALARM_ALMODE	  ,//(走时模式)继续短按ALARM，其他按键设置响闹模式
	FLAG_KEYSET_SHORT_ALARM_CONFIRMSET,//(走时模式)继续短按ALARM,缺人设置或不动作30s自动保存并返回走时模式，
									   //响闹时间为60min
}FLAG_KEYSET_TypeDef;

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
extern FLAG_KEYSET_TypeDef  TYPE_Flag_KSet;//按键的功能设置标志
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



