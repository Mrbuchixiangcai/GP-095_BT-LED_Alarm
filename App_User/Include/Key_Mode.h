/**********************************/
/*ͷ�ļ�����header file definition*/
/**********************************/
#ifndef __KEY_MODE_H__
#define __KEY_MODE_H__
/*******************/
/*ͷ�ļ�header file*/
/*******************/
#include "app_main.h"

/************************/
/*�궨��macro definition*/
/************************/
#define	 K_D  		(1<<5) //0010_0000(0x20)
#define	 K_U  		(2<<5) //0100_0000(0x40)//�̰�
#define	 K_H  		(3<<5) //0110_0000(0x60)//�������� hold
#define	 K_R  		(4<<5) //1000_0000(0x80)//����
#define	 K_L  		(5<<5) //1010_0000(0xA0)//����
#define	 K_LU  		(6<<5) //1100_0000(0xC0)//������
#define	 KD(x)  	(x|K_D)
#define	 KU(x)  	(x|K_U)
#define	 KH(x)  	(x|K_H)
#define	 KR(x)  	(x|K_R)
#define	 KL(x)  	(x|K_L)
#define	 KLU(x)  	(x|K_LU)
#define  cKEY_CLICK     5   //����ʱ�䳣��
#define  cKEY_HOLD      50  //��סʱ�䳣��
#define  cKEY_RATE_VOL  20  //����ʱ�䳣��

/*************************/
/*���Ͷ���byte definition*/
/*************************/
enum
{
	K_NC			 ,
	K_SNOOZE_DIMMER  ,//̰˯����
	K_VOLINC		 ,//������ 
	K_PLAY_PAUSE	 ,//��ͣ/����
	K_NEXT			 ,//��һ��
	K_ALARM			 ,//����
	K_VOLDEC		 ,//������
	K_BT			 ,//����
	K_PREV			 ,//��һ��
	K_AL_SNOOZE      ,//��ϼ�-���Ӻ�̰˯-ͬʱ2s-ʱ������(��������ʱ������)��
	K_AL_VOLINC      ,//��ϼ�-���Ӻ�������-ͬʱ2s-RTCʱ���һСʱ����ʾ��������ʱ
	K_AL_VOLDEC      ,//��ϼ�-���Ӻ�������-ͬʱ2s-RTCʱ���һСʱ����ʾ�ر�����ʱ
};//��������

typedef enum
{
	FLAG_KEYSET_OFF 			   = 0,
	FLAG_KEYSET_SETTIME_HOUR		  ,//(��ʱģʽ)����ALARM����SNOZE��������ʱ������ģʽ��Сʱ���ã������ٴ�
	FLAG_KEYSET_SETTIME_MINUTE		  ,//�̰�ALARM�������÷��ӣ��ٴζ̰�ȷ��ʱ�����30s�������Զ����棬������
	//FLAG_KEYSET_SETTIME_CONFIRMSET	  ,//��ʱģʽ
	FLAG_KEYSET_SHORT_ALARM_HOUR	  ,//(��ʱģʽ)�̰�ALARM������������������ʱ��ģʽ�����������ӹ��ܣ��ٴζ�
	FLAG_KEYSET_SHORT_ALARM_MINUTE	  ,//��ALARM�����������÷���ģʽ���ٴζ̰�ALARM����ѡ������ģʽ�����Ĵζ�
	FLAG_KEYSET_SHORT_ALARM_ALWORKMODE,//��ALARM����ȷʵ����ʱ�����ã����߲�����30s�Զ����棬��������ʱģʽ
	//FLAG_KEYSET_SHORT_ALARM_CONFIRMSET,//
}FLAG_KEYSET_TypeDef;

typedef struct
{
	uint8_t  temp_RTC_Hour;
	uint8_t  temp_RTC_Minute;
	uint8_t  temp_RTC_Second;

	uint8_t  Flag_Confirm_30Sec;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1��ȷ���������ñ�
								//־λ),Ϊ2��30s��ʱ��־λ��
}TIME_TEMP_TypeDef;

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
void KeyScan(void);
void KeyComMsg(void);
/*****************************/
/*��������function definetion*/
/*****************************/

/********************************/
/*�ⲿ����_�궨��macro definition*/
/********************************/

/*********************************/
/*�ⲿ����_���Ͷ���byte definition*/
/*********************************/
extern FLAG_KEYSET_TypeDef  FlagKSet_TypeDef;//�����Ĺ������ñ�־
extern TIME_TEMP_TypeDef    Time_Temp_TypeDef;//����ʱ��ʱ�Ű����õ�ʱ���ȸ��������Ȼ��ȷ�����ٸ�ֵ��gRTC_xx;
/************************************/
/*�ⲿ����_��־λ����flags definetion*/
/************************************/

/*************************************/
/*�ⲿ����_��������variable definition*/
/*************************************/

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



