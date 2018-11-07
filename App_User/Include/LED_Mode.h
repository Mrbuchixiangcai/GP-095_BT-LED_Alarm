/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __LED_MODE_H__
#define __LED_MODE_H__
/*******************/
/*头文件header file*/
/*******************/
//#define AL1(a)			if (a)			\  //P20 //闹钟LED显示
//							P2|=0x01;   \
//						else			\
//							P2&=~0x01;
//#define PM(a)			if (a)			\  //P21 //AM/PM LED显示
//							P2|=0x02;   \
//						else			\
//							P2&=~0x02;
//#define HOUR_BIT1_C(a)	if (a)			\  //P22 //时钟的小时位的十位LED显示
//							P2|=0x04;   \
//						else			\
//							P2&=~0x04;
//#define HOUR_BIT1_B(a)	if (a)			\  //P23
//							P2|=0x08;   \
//						else			\
//							P2&=~0x08;
//#define HOUR_BIT2_A(a)	if (a)			\  //P24 //时钟的小时位的个位LED显示
//							P2|=0x10;   \
//						else			\
//							P2&=~0x10;
//#define HOUR_BIT2_B(a)	if (a)			\  //P25
//							P2|=0x20;   \
//						else			\
//							P2&=~0x20;
//#define HOUR_BIT2_C(a)	if (a)			\  //P26
//							P2|=0x40;   \
//						else			\
//							P2&=~0x40;
//#define HOUR_BIT2_D(a)	if (a)			\  //P27
//							P2|=0x80;   \
//						else			\
//							P2&=~0x80;
//#define HOUR_BIT2_E(a)	if (a)			\  //P30
//							P3|=0x01;   \
//						else			\
//							P3&=~0x01;
//#define HOUR_BIT2_F(a)	if (a)			\  //P31
//							P3|=0x02;   \
//						else			\
//							P3&=~0x02;
//#define HOUR_BIT2_G(a)	if (a)			\  //P32
//							P3|=0x04;   \
//						else			\
//							P3&=~0x04;
//#define COL1(a)			if (a)			\  //P33 //时间显示中"xx：xx"的两点
//							P3|=0x08;   \
//						else			\
//							P3&=~0x08;
//#define COL2(a)			if (a)			\  //P34 //时间显示中"xx：xx"的两点
//							P3|=0x10;   \
//						else			\
//							P3&=~0x10;
//#define MIN_BIT1_A(a)	if (a)			\  //P35 //时钟的分钟位的十位LED显示
//							P3|=0x20;   \
//						else			\
//							P3&=~0x20;
//#define MIN_BIT1_B(a)	if (a)			\  //P36
//							P3|=0x40;   \
//						else			\
//							P3&=~0x40;
//#define MIN_BIT1_C(a)	if (a)			\  //P37
//							P3|=0x80;   \
//						else			\
//							P3&=~0x80;
//#define MIN_BIT1_D(a)	if (a)			\  //P40
//							P4|=0x01;   \
//						else			\
//							P4&=~0x01;
//#define MIN_BIT1_E(a)	if (a)			\  //P41
//							P4|=0x02;   \
//						else			\
//							P4&=~0x02;
//#define MIN_BIT1_F(a)	if (a)			\  //P42
//							P4|=0x04;   \
//						else			\
//							P4&=~0x04;
//#define MIN_BIT1_G(a)	if (a)			\  //P43
//							P4|=0x08;   \
//						else			\
//							P4&=~0x08;
//#define MIN_BIT2_A(a)	if (a)			\  //P44 //时钟的分钟位的个位LED显示
//							P4|=0x10;   \
//						else			\
//							P4&=~0x10;
//#define MIN_BIT2_B(a)	if (a)			\  //P45
//							P4|=0x20;   \
//						else			\
//							P4&=~0x20;
//#define MIN_BIT2_C(a)	if (a)			\  //P46
//							P4|=0x40;   \
//						else			\
//							P4&=~0x40;
//#define MIN_BIT2_D(a)	if (a)			\  //P47
//							P4|=0x80;   \
//						else			\
//							P4&=~0x80;
//#define MIN_BIT2_E(a)	if (a)			\  //P50
//							P5|=0x01;   \
//						else			\
//							P5&=~0x01;
//#define MIN_BIT2_F(a)	if (a)			\  //P51
//							P5|=0x02;   \
//						else			\
//							P5&=~0x02;
//#define MIN_BIT2_G(a)	if (a)			\  //P52
//							P5|=0x04;   \
//						else			\
//							P5&=~0x04;

#define S_NC  7
#define S_A   0		// AAAAA
#define S_B   4		//F     B
#define S_C   5		//F     B
#define S_D   6		// GGGGG
#define S_E   3		//E     C
#define S_F   1		//E     C
#define S_G   2		// DDDDD


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
}LED_BRIGHTNESS_TypeDef;
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
extern LED_BRIGHTNESS_TypeDef  TYPE_LED_Brightness;

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




