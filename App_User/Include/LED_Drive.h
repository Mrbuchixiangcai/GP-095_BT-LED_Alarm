/**********************************/
/*ͷ�ļ�����header file definition*/
/**********************************/
#ifndef __LED_DRIVE_H__
#define __LED_DRIVE_H__

/*******************/
/*ͷ�ļ�header file*/
/*******************/
#include "app_main.h"

/************************/
/*�궨��macro definition*/
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
 *˵������Щ"SET"��"CLR"�������߶�����ܵ�ÿ�ε�LED����Ȼ���ڱ�����
 *		�ߵ�ƽͨ(SET)���͵�ƽ��()CLR
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
#define __SET_AM()   do{P2 &= CBIT1;}while(0)  //P21 AMΪPM�Ʋ���
#define __SET_PM()   do{P2 |=  BIT1;}while(0)  //P21 
#define __SET_AL()   do{P2 |=  BIT0;}while(0)  //P20 
#define __CLR_AL()   do{P2 &= CBIT0;}while(0)  
#define __SET_COL1() do{P2 |=  BIT6;}while(0)  //P26
#define __CLR_COL1() do{P2 &= CBIT6;}while(0)
#define __SET_COL2() do{P4 |=  BIT6;}while(0)  //P46
#define __CLR_COL2() do{P4 &= CBIT6;}while(0)
#define __SET_BEEP() do{P0 |=  BIT2;}while(0)  //P02
#define __CLR_BEEP() do{P0 &= CBIT2;}while(0)
/*************************/
/*���Ͷ���byte definition*/
/*************************/

/****************************/
/*��־λ����flags definetion*/
/****************************/

/*****************************/
/*��������variable definition*/
/*****************************/

/**************************/
/*���鶨��array definition*/
/**************************/

/******************************/
/*��������Function declaration*/
/******************************/

/*****************************/
/*��������function definetion*/
/*****************************/

/********************************/
/*�ⲿ����_�궨��macro definition*/
/********************************/

/*********************************/
/*�ⲿ����_���Ͷ���byte definition*/
/*********************************/

/************************************/
/*�ⲿ����_��־λ����flags definetion*/
/************************************/

/*************************************/
/*�ⲿ����_��������variable definition*/
/*************************************/
extern uint8_t  Led_Buffer[];
/**********************************/
/*�ⲿ����_���鶨��array definition*/
/**********************************/

/**************************************/
/*�ⲿ����_��������Function declaration*/
/**************************************/

/*************************************/
/*�ⲿ����_��������function definetion*/
/*************************************/






#endif



