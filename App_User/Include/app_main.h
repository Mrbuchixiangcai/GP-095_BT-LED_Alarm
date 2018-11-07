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
#include "bt_mode.h"
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
	PLAY_ALARM,
	PLAY_IN_TIME,//��ʱģʽ
	PLAY_IN_TIME_BT     ,
	//PLAY_IN_TIME_TF_CARD,
}PLAY_MODE_TypeDef;

typedef enum
{
	ALARM_BT  =1,
	ALARM_BEEP  ,
}ALARM_MODE_TypeDef;//��������ģʽѡ���������Դ������������beep

typedef struct
{
	uint8_t  enable;	//�����ܿ���
	uint8_t  week;	
	uint8_t  hour;  //�жϴ˱�����ֵ��ͨ��LED��ʾ������Ҳ����ֱ�ӶԴ˱�����������
	uint8_t  minute;//�жϴ˱�����ֵ��ͨ��LED��ʾ������Ҳ����ֱ�ӶԴ˱�����������
	uint8_t  tempHour;  //��Ϊ���������и�ȷ������(��Ȼ���ò���),������Ҫ�и���ʱ������Ϊ�м�ֵ����
	uint8_t  tempMinute;//��ȱ�����û���30s���Զ�ȷ���ٰ�tempXxx�⼸�������������ӵ�����趨ʱ��
	uint8_t  runing; 
	uint8_t  cntTimer;	
	uint8_t  Flag_Confirm_TimeCnt_30Sec;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1��ȷ���������ñ�
										//־λ),Ϊ2��30s��ʱ��־λ��
	ALARM_MODE_TypeDef  Alarm_Mode;
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
extern uint8_t  idata sys_Volume;
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







