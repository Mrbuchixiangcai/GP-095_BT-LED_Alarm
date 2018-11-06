/**********************************/
/*ͷ�ļ�����header file definition*/
/**********************************/
#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

//�궨��macro definition//
#define uint8_t  unsigned char
#define uint16_t unsigned int

/*******************/
/*ͷ�ļ�header file*/
/*******************/
#include "app_main.h"
#include "MC96F6508A.h"
#include "func_def.h"
#include "led_mode.h"
//#include "bt_mode.h"
#include "key_mode.h"

/************************/
/*�궨��macro definition*/
/************************/

/*************************/
/*���Ͷ���byte definition*/
/*************************/
typedef enum
{
	PLAY_OFF = 0,
	PLAY_JUST_POWER,//���ϵ磬ȫ��2s������ʱ��
	PLAY_IN_TIME,//��ʱģʽ
	PLAY_ALARM  ,
	PLAY_BT     ,
	PLAY_TF_CARD,
}PLAY_MODE_TypeDef;

typedef enum
{
	ALARM_BT  =1,
	ALARM_BEEP  ,
}ALARM_MODE_TypeDef;//��������ģʽѡ���������Դ������������beep

typedef struct
{
	uint8_t  Enable;	//�����ܿ���
	uint8_t  Week;	
	uint8_t  Hour;
	uint8_t  Minute;	
	uint8_t  Runing; 
	uint8_t  cntTimer;	
	ALARM_MODE_TypeDef Alarm_Mode;
}ALRAM_TypeDef;


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
void app_main(void);
void Sys_Tick(void);
/*****************************/
/*��������function definetion*/
/*****************************/

/********************************/
/*�ⲿ����_�궨��macro definition*/
/********************************/

/*********************************/
/*�ⲿ����_���Ͷ���byte definition*/
/*********************************/
extern PLAY_MODE_TypeDef  TYPE_Play_Mode;
extern ALRAM_TypeDef  TYPE_Alarm1;

/************************************/
/*�ⲿ����_��־λ����flags definetion*/
/************************************/
extern bit  Flag_Alarm;  //Ϊ1Ϊ���ӿ�����Ϊ0��ر�
extern bit  Flag_AlarmSet_Confirm_TimeCnt_30Sec;
/*************************************/
/*�ⲿ����_��������variable definition*/
/*************************************/
extern bit			  gbHalfSecong;
extern uint8_t  idata gRTC_Sec;//RTC���� 
extern uint8_t  idata gRTC_Sec_bk;
extern uint8_t  idata gRTC_Minute;
extern uint8_t  idata gRTC_Minute_bk;
extern uint8_t  idata gRTC_Hour;
extern uint8_t  idata gRTC_Hour_bk;
extern uint8_t  xdata gRTC_Hour_bk_24;//����24Сʱ
extern uint8_t  idata gRTC_Week; 
extern uint8_t  idata sys_volume;
extern uint16_t idata timeCnt_30Sec;
/**********************************/
/*�ⲿ����_���鶨��array definition*/
/**********************************/

/**************************************/
/*�ⲿ����_��������Function declaration*/
/**************************************/
//extern void app_main(void);
//extern void Sys_Tick(void);
/*************************************/
/*�ⲿ����_��������function definetion*/
/*************************************/





#endif







