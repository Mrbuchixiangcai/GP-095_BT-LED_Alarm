/**********************************/
/*ͷ�ļ�����header file definition*/
/**********************************/
#ifndef __BT_MODE_H__
#define __BT_MODE_H__
/*******************/
/*ͷ�ļ�header file*/
/*******************/

/************************/
/*�궨��macro definition*/
/************************/
#define UART1_LEN_BUFFER 10

/*************************/
/*���Ͷ���byte definition*/
/*************************/
typedef enum
{
	MUSIC_OFF = 0,
	MUSIC_BT,
	MUSIC_TF,
}MUSIC_MODE_TypeDef;

enum
{
	BT_NONE    = 0,
	BT_PAIR       ,//���//8�ַ�
	BT_LINK_BACK  ,//����
	
	BT_PLAY       ,//����//9�ַ�
	BT_PAUSE      ,//��ͣ
	BT_PLAY_PAUSE ,//����/��ͣ
	BT_PREV       ,//��һ��
	BT_NEXT       ,//��һ��
	BT_IQ		  ,//��ѯ״̬
	BT_DISCONN    ,//�Ͽ�����
	BT_QUERY_VOL  ,//��ȡ����ֵ
	
	BT_POWER_DOWN ,//10//�ػ�//10�ַ�
	BT_SDO		  ,//TF�������������
	BT_SDF		  ,//TF���γ���������
	BT_TF_CARD	  ,//�л���TF��ģʽ
	BT_MODE		  ,//��TF��ģʽ�л�����ģʽ
	BT_VOL	      ,//����
};

typedef enum
{
	BT_STEP_START = 0,
	BT_STEP_INITI1,
	BT_STEP_INITI2,
	BT_STEP_INITI3,
	BT_STEP_INITI4,
	BT_STEP_INITI5,
	BT_STEP_INITI6,
	BT_STEP_INITI7,
	BT_STEP_INITI8,
	BT_STEP_INITI9,
	BT_STEP_INITI10,
	BT_STEP_INITI11,
	BT_STEP_INITI12,
} BT_STEP;

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
void BlueMode_Handle(void);
/*****************************/
/*��������function definetion*/
/*****************************/

/********************************/
/*�ⲿ����_�궨��macro definition*/
/********************************/

/*********************************/
/*�ⲿ����_���Ͷ���byte definition*/
/*********************************/
extern MUSIC_MODE_TypeDef Music_Mode_TypeDef;
/************************************/
/*�ⲿ����_��־λ����flags definetion*/
/************************************/
extern bit Flag_BT_work;
extern bit Flag_BT_Connect;//�������ӱ�־λ
extern uint8_t Flag_BT_Play;   //��������,1���ڲ��ţ�0������ͣ(ֹͣ)
extern bit Flag_BT_Pause;  //��ͣ
extern bit Flag_UART1_RX_Finish_A;
extern bit Flag_UART1_RX_Finish_B;
extern bit Flag_UART_ReceiveBuffer_A_B;
extern bit Flag_BT_TF_Play;//����TF������ģʽ��1���ڲ��ţ�0������ͣ(ֹͣ)
/*************************************/
/*�ⲿ����_��������variable definition*/
/*************************************/
extern uint8_t  idata bt_cmd;
extern uint8_t  idata uart1_RX_Pointer;
extern uint8_t  idata uart1_TX_Pointer;
extern uint8_t  idata uart1_EnableSend;
extern uint8_t  idata uart1_TX_Timeout;
extern uint8_t  idata uart1_RX_Timeout;
/**********************************/
/*�ⲿ����_���鶨��array definition*/
/**********************************/
extern uint8_t   uart1_TransmitBuffer[UART1_LEN_BUFFER];
extern uint8_t  idata uart1_ReceiveBuffer_A[UART1_LEN_BUFFER];
extern uint8_t  idata uart1_ReceiveBuffer_B[UART1_LEN_BUFFER];
/**************************************/
/*�ⲿ����_��������Function declaration*/
/**************************************/
void BT_Send_CMD(uint8_t cmd);
/*************************************/
/*�ⲿ����_��������function definetion*/
/*************************************/


#endif




