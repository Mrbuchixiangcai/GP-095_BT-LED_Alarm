/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __LED_DRIVE_H__
#define __LED_DRIVE_H__

/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"

/************************/
/*宏定义macro definition*/
/************************/
#define BIT0   0x01  
#define BIT1   0x02
#define BIT2   0x04
#define BIT3   0x08
#define BIT4   0x10
#define BIT5   0x20
#define BIT6   0x40
#define BIT7   0x80
#define CBIT0  0xFE
#define CBIT1  0xFD
#define CBIT2  0xFB
#define CBIT3  0xF7
#define CBIT4  0xEF
#define CBIT5  0xDF
#define CBIT6  0xBF
#define CBIT7  0x7F

/*******************************************************************************
 *说明：这些"SET"和"CLR"是设置七段数码管的每段的LED亮灭，然后在被调用
 *		高电平通(SET)，低电平灭()CLR
 *******************************************************************************/
#define __SET_1B()   do{P2 |=  BIT2;}while(0)  //P22
#define __CLR_1B()   do{P2 &= CBIT2;}while(0)
#define __SET_1C()   do{P4 |=  BIT0;}while(0)  //P40
#define __CLR_1C()   do{P4 &= CBIT0;}while(0)
#define __SET_2A()   do{P2 |=  BIT4;}while(0)  //P24 
#define __CLR_2A()   do{P2 &= CBIT4;}while(0)
#define __SET_2B()   do{P2 |=  BIT5;}while(0)  //P25
#define __CLR_2B()   do{P2 &= CBIT5;}while(0)
#define __SET_2C()   do{P5 |=  BIT0;}while(0)  //P50
#define __CLR_2C()   do{P5 &= CBIT0;}while(0)
#define __SET_2D()   do{P5 |=  BIT2;}while(0)  //P52
#define __CLR_2D()   do{P5 &= CBIT2;}while(0)
#define __SET_2E()   do{P4 |=  BIT1;}while(0)  //P41
#define __CLR_2E()   do{P4 &= CBIT1;}while(0)
#define __SET_2F()   do{P2 |=  BIT3;}while(0)  //P23
#define __CLR_2F()   do{P2 &= CBIT3;}while(0)
#define __SET_2G()   do{P3 |=  BIT7;}while(0)  //P37
#define __CLR_2G()   do{P3 &= CBIT7;}while(0)
#define __SET_3A()   do{P3 |=  BIT0;}while(0)  //P30
#define __CLR_3A()   do{P3 &= CBIT0;}while(0)
#define __SET_3B()   do{P3 |=  BIT1;}while(0)  //P31
#define __CLR_3B()   do{P3 &= CBIT1;}while(0)
#define __SET_3C()   do{P4 |=  BIT4;}while(0)  //P44
#define __CLR_3C()   do{P4 &= CBIT4;}while(0)
#define __SET_3D()   do{P5 |=  BIT1;}while(0)  //P51
#define __CLR_3D()   do{P5 &= CBIT1;}while(0)
#define __SET_3E()   do{P4 |=  BIT5;}while(0)  //P45
#define __CLR_3E()   do{P4 &= CBIT5;}while(0)
#define __SET_3F()   do{P2 |=  BIT7;}while(0)  //P27
#define __CLR_3F()   do{P2 &= CBIT7;}while(0)
#define __SET_3G()   do{P3 |=  BIT6;}while(0)  //P36
#define __CLR_3G()   do{P3 &= CBIT6;}while(0)
#define __SET_4A()   do{P3 |=  BIT3;}while(0)  //P33
#define __CLR_4A()   do{P3 &= CBIT3;}while(0)
#define __SET_4B()   do{P3 |=  BIT4;}while(0)  //P34
#define __CLR_4B()   do{P3 &= CBIT4;}while(0)
#define __SET_4C()   do{P4 |=  BIT2;}while(0)  //P42
#define __CLR_4C()   do{P4 &= CBIT2;}while(0)
#define __SET_4D()   do{P4 |=  BIT7;}while(0)  //P47
#define __CLR_4D()   do{P4 &= CBIT7;}while(0)
#define __SET_4E()   do{P4 |=  BIT3;}while(0)  //P43
#define __CLR_4E()   do{P4 &= CBIT3;}while(0)
#define __SET_4F()   do{P3 |=  BIT2;}while(0)  //P32
#define __CLR_4F()   do{P3 &= CBIT2;}while(0)
#define __SET_4G()   do{P3 |=  BIT5;}while(0)  //P35
#define __CLR_4G()   do{P3 &= CBIT5;}while(0)
#define __SET_AM()   do{P2 &= CBIT1;}while(0)  //P21 AM为PM灯不亮
#define __SET_PM()   do{P2 |=  BIT1;}while(0)  //P21 
#define __SET_AL()   do{P2 |=  BIT0;}while(0)  //P20 
#define __CLR_AL()   do{P2 &= CBIT0;}while(0)  
#define __SET_COL1() do{P2 |=  BIT6;}while(0)  //P26
#define __CLR_COL1() do{P2 &= CBIT6;}while(0)
#define __SET_COL2() do{P4 |=  BIT6;}while(0)  //P46
#define __CLR_COL2() do{P4 &= CBIT6;}while(0)
#define __SET_BEEP() do{P0 |=  BIT2;}while(0)  //P02
#define __CLR_BEEP() do{P0 &= CBIT2;}while(0)

#define _SET_1B(a)  if(a)                 \
                        P2 |=  BIT2;      \
                    else                  \
                        P2 &= CBIT2;      
#define _SET_1C(a)  if(a)                 \
                        P4 |=  BIT0;      \
                    else                  \
                        P4 &= CBIT0;      
#define _SET_2A(a)  if(a)                 \
                        P2 |=  BIT4;      \
                    else                  \
                        P2 &= CBIT4;      
#define _SET_2B(a)  if(a)                 \
                        P2 |=  BIT5;      \
                    else                  \
                        P2 &= CBIT5;      
#define _SET_2C(a)  if(a)                 \
                        P5 |=  BIT0;      \
                    else                  \
                        P5 &= CBIT0;      
#define _SET_2D(a)  if(a)                 \
                        P5 |=  BIT2;      \
                    else                  \
                        P5 &= CBIT2;      
#define _SET_2E(a)  if(a)                 \
                        P4 |=  BIT1;      \
                    else                  \
                        P4 &= CBIT1;      
#define _SET_2F(a)  if(a)                 \
                        P2 |=  BIT3;      \
                    else                  \
                        P2 &= CBIT3;      
#define _SET_2G(a)  if(a)                 \
                        P3 |=  BIT7;      \
                    else                  \
                        P3 &= CBIT7;      
#define _SET_3A(a)  if(a)                 \
                        P3 |=  BIT0;      \
                    else                  \
                        P3 &= CBIT0;      
#define _SET_3B(a)  if(a)                 \
                        P3 |=  BIT1;      \
                    else                  \
                        P3 &= CBIT1;      
#define _SET_3C(a)  if(a)                 \
                        P4 |=  BIT4;      \
                    else                  \
                        P4 &= CBIT4;      
#define _SET_3D(a)  if(a)                 \
                        P5 |=  BIT1;      \
                    else                  \
                        P5 &= CBIT1;      
#define _SET_3E(a)  if(a)                 \
                        P4 |=  BIT5;      \
                    else                  \
                        P4 &= CBIT5;      
#define _SET_3F(a)   if(a)                 \
                        P2 |=  BIT7;      \
                    else                  \
                        P2 &= CBIT7;      
#define _SET_3G(a)  if(a)                 \
                        P3 |=  BIT6;      \
                    else                  \
                        P3 &= CBIT6;      
#define _SET_4A(a)  if(a)                 \
                        P3 |=  BIT3;      \
                    else                  \
                        P3 &= CBIT3;      
#define _SET_4B(a)  if(a)                 \
                        P3 |=  BIT4;      \
                    else                  \
                        P3 &= CBIT4;      
#define _SET_4C(a)  if(a)                 \
                        P4 |=  BIT2;      \
                    else                  \
                        P4 &= CBIT2;      
#define _SET_4D(a)  if(a)                 \
                        P4 |=  BIT7;      \
                    else                  \
                        P4 &= CBIT7;      
#define _SET_4E(a)  if(a)                 \
                        P4 |=  BIT3;      \
                    else                  \
                        P4 &= CBIT3;      
#define _SET_4F(a)  if(a)                 \
                        P3 |=  BIT2;      \
                    else                  \
                        P3 &= CBIT2;      
#define _SET_4G(a)  if(a)                 \
                        P3 |=  BIT5;      \
                    else                  \
                        P3 &= CBIT5;      
#define _SET_APM(a) if(a)                 \
                        P2 |=  BIT1;      \
                    else                  \
                        P2 &=  CBIT1;      
#define _SET_AL(a)  if(a)                 \
                        P2 |=  BIT0;      \
                    else                  \
                        P2 &= CBIT0;      
#define _SET_COL1(a)if(a)                 \
                        P2 |=  BIT6;      \
                     else                 \
                        P2 &= CBIT6;      
#define _SET_COL2(a)if(a)                 \
                        P4 |=  BIT6;      \
                    else                  \
                        P4 &= CBIT6;      
//蓝牙开机，检测到蓝牙信号后，并且没有tf卡就设置输出1
#define _SET_BT_BLUE(a) if(a)			  \  
							P5 |= BIT3;	  \
					    else			  \
							P5 &= CBIT3;
//蓝牙开机，检测到蓝牙信号后，并且有tf卡就设置输出1
#define _SET_BT_RED(a)	if(a)			  \  
							P5 |= BIT4;	  \
						else              \
							P5 &= CBIT4;

/*************************/
/*类型定义byte definition*/
/*************************/

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
void Display_LED(void);
/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/

/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/
extern bit Flag_SET_1B;
extern bit Flag_SET_1C;
extern bit Flag_SET_2A;
extern bit Flag_SET_2B;
extern bit Flag_SET_2C;
extern bit Flag_SET_2D;
extern bit Flag_SET_2E;
extern bit Flag_SET_2F;
extern bit Flag_SET_2G;
extern bit Flag_SET_3A;
extern bit Flag_SET_3B;
extern bit Flag_SET_3C;
extern bit Flag_SET_3D;
extern bit Flag_SET_3E;
extern bit Flag_SET_3F;
extern bit Flag_SET_3G;
extern bit Flag_SET_4A;
extern bit Flag_SET_4B;
extern bit Flag_SET_4C;
extern bit Flag_SET_4D;
extern bit Flag_SET_4E;
extern bit Flag_SET_4F;
extern bit Flag_SET_4G;
extern bit Flag_SET_APM;
extern bit Flag_SET_AL;
extern bit Flag_SET_COL1;
extern bit Flag_SET_COL2;
extern bit Flag_SET_BT_BLUE;
extern bit Flag_SET_BT_RED;

/*************************************/
/*外部调用_变量定义variable definition*/
/*************************************/
extern uint8_t  Led_Buffer[];
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




