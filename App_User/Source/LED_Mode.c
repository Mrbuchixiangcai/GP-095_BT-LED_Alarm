/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"

/************************/
/*宏定义macro definition*/
/************************/

/*************************/
/*类型定义byte definition*/
/*************************/
LED_BRIGHTNESS  TYPE_LED_Brightness;
/****************************/
/*标志位定义flags definetion*/
/****************************/

/*****************************/
/*变量定义variable definition*/
/*****************************/
//uint8_t  displaySecond; //判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
//uint8_t  displayMinute;
//uint8_t  displayHour;
uint8_t  ledBrightness;//LED显示的亮度
uint8_t  alarmMinute;//判断此变量的值，通过LED显示出来，也可以直接对此变量进行设置
uint8_t  alarmHour;
uint8_t  tempAlarmMinute;//因为设置闹钟有个确认设置(虽然作用不大),所以需要有个临时变量作为中间值，等
uint8_t  tempAlarmHour;  //到缺人设置或者30s后自动确认再把tempXxx这几个变量赋给闹钟的最后设定时间

/**************************/
/*数组定义array definition*/
/**************************/

/******************************/
/*函数声明Function declaration*/
/******************************/

/*****************************/
/*函数定义function definetion*/
/*****************************/






