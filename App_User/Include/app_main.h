/**********************************/
/*ͷ�ļ�����header file definition*/
/**********************************/
#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

//�궨��macro definition//

/*******************/
/*ͷ�ļ�header file*/
/*******************/
#include "app_main.h"
#include "MC96F6508A.h"
#include "user_define.h"
#include "func_def.h"
#include "led_mode.h"
#include "bt_mode.h"
#include "key_mode.h"

/************************/
/*�궨��macro definition*/
/************************/
#define SET_BEEP(a)			if(a)				\  //���÷������컹�ǲ���
								P0 |= 0x04;		\
							else				\
								P0 &= (~0x04);
#define SET_LED_RED(a)		if(a)				\  //
								P5 |= 0x10;		\
							else                \
								P5 &= (~0x10);
#define BT_SET_LED_BLUE(a)  if(a)				\  //������������⵽�����źź󣬾��������1
								P5 |= 0x08;		\
							else				\
								P5 &= (~0x08);

#define TF_CARD_DET()     (P0&0x01)    //���TF���Ƿ����
#define BT_MUTE_DET()     (P6&0x02)    //P62,��������Ƿ񷢳�mute�ź�,1Ϊ������
#define BT_LED_RED_DET()  (P0&0x08)    //P03,��������Ƿ񷢳���ɫLED�ź�
#define BT_LED_BLUE_DET() (P5&0x20)    //P55,��������Ƿ���������������ʹ���һ���˿����һ��Blue LED

#define BT_SET_POWER()	  do{P6 |=  (0x01);}while(0)//P60,ʹ�����������ʹ����ʹ�����ܵ�ͨ������оƬ�ϵ�
#define BT_CLR_POWER()	  do{P6 &= (~0x01);}while(0)
#define __DE_MUTE()		  do{P0 |= ( 0x02);}while(0)//��mute
#define __EN_MUTE()		  do{P0 &= (~0x02);}while(0)//mute

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

enum
{
	DISP_CLK  = 0,
	DISP_AL1,
	ADJ_CLK,
	ADJ_ZONE,
	ADJ_ALARM1,
	ALARM1_DISP,
	ADJ_ALARM1_MIN,
	ADJ_ALARM1_HOUR,
	ADJ_ALARM1_MODE,
	DISP_VOL,
	DISP_SLEEP,
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
extern PLAY_MODE_TypeDef  PlayMode_TypeDef;
extern CONTROL_COMMAND_TypeDef Ctrl_Com_TypeDef;

/************************************/
/*�ⲿ����_��־λ����flags definetion*/
/************************************/
extern BOOL  gb12HourDisp;
extern BOOL  gb0_5s;
extern BOOL  gbUser_AdjClk;
extern BOOL  gbHalfSecond;
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

extern u8       idata cntNoFlash;
extern u8			  gZone;
extern u8			  dispStatus;
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







