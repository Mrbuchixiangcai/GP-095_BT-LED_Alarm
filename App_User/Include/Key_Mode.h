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
#define	 K_D  		(1<<5) //
#define	 K_U  		(2<<5) //�̰�
#define	 K_H  		(3<<5) //�������� hold
#define	 K_R  		(4<<5) //����
#define	 K_L  		(5<<5) //����
#define	 K_LU  		(6<<5) //������
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
	K_SNOOZE_PAUSE=1,
	K_VOLINC		,
	K_TIME_DIM		,
	K_NEXT			,
	K_ALARM			,
	K_VOLDEC		,
	K_BT			,
	K_PREV			,
};//��������

typedef enum
{
	FLAG_KEYSET_OFF 			   = 0,
	FLAG_KEYSET_JUST_POWER_LONG_TIME  ,//����time��־��������������Сʱ
	FLAG_KEYSET_JUST_POWER_SHORT_TIME ,//�̰�time��־�������������÷���
	//FLAG_KEYSET_IN_TIME_SHORT_TIME_DIM,//��ʱģʽ�̰�time��־����������
	FLAG_KEYSET_LONG_ALARM_HOUR		  ,//��ʱģʽ����ALARM��־��������������Сʱ
	FLAG_KEYSET_SHORT_ALARM_MINUTE	  ,//(��ʱģʽ)�����̰�ALARM�������������÷���
	FLAG_KEYSET_SHORT_ALARM_ALMODE	  ,//(��ʱģʽ)�����̰�ALARM������������������ģʽ
	FLAG_KEYSET_SHORT_ALARM_CONFIRMSET,//(��ʱģʽ)�����̰�ALARM,ȱ�����û򲻶���30s�Զ����沢������ʱģʽ��
									   //����ʱ��Ϊ60min
}FLAG_KEYSET_TypeDef;

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
extern FLAG_KEYSET_TypeDef  TYPE_Flag_KSet;//�����Ĺ������ñ�־
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



