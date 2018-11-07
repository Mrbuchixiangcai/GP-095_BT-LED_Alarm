/**********************************/
/*ͷ�ļ�����header file definition*/
/**********************************/
#ifndef __LED_MODE_H__
#define __LED_MODE_H__
/*******************/
/*ͷ�ļ�header file*/
/*******************/
//#define AL1(a)			if (a)			\  //P20 //����LED��ʾ
//							P2|=0x01;   \
//						else			\
//							P2&=~0x01;
//#define PM(a)			if (a)			\  //P21 //AM/PM LED��ʾ
//							P2|=0x02;   \
//						else			\
//							P2&=~0x02;
//#define HOUR_BIT1_C(a)	if (a)			\  //P22 //ʱ�ӵ�Сʱλ��ʮλLED��ʾ
//							P2|=0x04;   \
//						else			\
//							P2&=~0x04;
//#define HOUR_BIT1_B(a)	if (a)			\  //P23
//							P2|=0x08;   \
//						else			\
//							P2&=~0x08;
//#define HOUR_BIT2_A(a)	if (a)			\  //P24 //ʱ�ӵ�Сʱλ�ĸ�λLED��ʾ
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
//#define COL1(a)			if (a)			\  //P33 //ʱ����ʾ��"xx��xx"������
//							P3|=0x08;   \
//						else			\
//							P3&=~0x08;
//#define COL2(a)			if (a)			\  //P34 //ʱ����ʾ��"xx��xx"������
//							P3|=0x10;   \
//						else			\
//							P3&=~0x10;
//#define MIN_BIT1_A(a)	if (a)			\  //P35 //ʱ�ӵķ���λ��ʮλLED��ʾ
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
//#define MIN_BIT2_A(a)	if (a)			\  //P44 //ʱ�ӵķ���λ�ĸ�λLED��ʾ
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
/*�궨��macro definition*/
/************************/

/*************************/
/*���Ͷ���byte definition*/
/*************************/
typedef enum
{
	LED_TURN_OFF = 0,
	LED_LOW			,
	LED_MEDIUM   	,
	LED_HIGH	 	,
}LED_BRIGHTNESS_TypeDef;
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
extern LED_BRIGHTNESS_TypeDef  TYPE_LED_Brightness;

/************************************/
/*�ⲿ����_��־λ����flags definetion*/
/************************************/

/*************************************/
/*�ⲿ����_��������variable definition*/
/*************************************/
extern uint8_t  ledBrightness;//LED��ʾ������
extern uint8_t  alarmMinute;//�жϴ˱�����ֵ��ͨ��LED��ʾ������Ҳ����ֱ�ӶԴ˱�����������
extern uint8_t  alarmHour;
extern uint8_t  tempAlarmMinute;//��Ϊ���������и�ȷ������(��Ȼ���ò���),������Ҫ�и���ʱ������Ϊ�м�ֵ����
extern uint8_t  tempAlarmHour;  //��ȱ�����û���30s���Զ�ȷ���ٰ�tempXxx�⼸�������������ӵ�����趨ʱ��

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




