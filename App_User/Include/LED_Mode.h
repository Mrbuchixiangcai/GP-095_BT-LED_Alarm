/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __LED_MODE_H__
#define __LED_MODE_H__
/*******************/
/*头文件header file*/
/*******************/

/************************/
/*宏定义macro definition*/
/************************/

/*************************/
/*类型定义byte definition*/
/*************************/
typedef enum
{
	LED_TURN_OFF = 0,
	LED_LOW			,
	LED_MEDIUM   	,
	LED_HIGH	 	,
}LED_BRIGHTNESS;
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

/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/
extern LED_BRIGHTNESS  TYPE_LED_Brightness;

/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/

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




