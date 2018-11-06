/*******************/
/*ͷ�ļ�header file*/
/*******************/
#include "app_main.h"

/************************/
/*�궨��macro definition*/
/************************/

/*************************/
/*���Ͷ���byte definition*/
/*************************/
BT_STEP  BT_Step;
/****************************/
/*��־λ����flags definetion*/
/****************************/
bit Flag_BT_work;
bit Flag_BT_Connect;//�������ӱ�־λ
bit Flag_BT_Play;   //��������
bit Flag_BT_Pause;  //��ͣ
bit Flag_UART1_RX_Finish_A;
bit Flag_UART1_RX_Finish_B;
bit Flag_UART_ReceiveBuffer_A_B;

/*****************************/
/*��������variable definition*/
/*****************************/
uint8_t  idata bt_cmd;
uint8_t  idata cntMuteBT;
uint8_t  idata btVolume;
uint8_t  idata uart1_RX_Pointer;
uint8_t  idata uart1_TX_Pointer;
uint8_t  idata uart1_EnableSend;
uint8_t  idata uart1_TX_Timeout;
uint8_t  idata uart1_RX_Timeout;

/**************************/
/*���鶨��array definition*/
/**************************/
uint8_t  xdata uart1_TransmitBuffer[UART1_LEN_BUFFER];
uint8_t  xdata uart1_ReceiveBuffer_A[UART1_LEN_BUFFER];
uint8_t  xdata uart1_ReceiveBuffer_B[UART1_LEN_BUFFER];
char  code BT_Command_tab[][8]= //���ڸı����ʱ���͸�wifi�ĵڼ��׸�
{
	"     \r\n",//NONE
	"AT+MT\r\n",//BT_PAUSE
	"AT+MA\r\n",//BT_PALY
	"AT+ME\r\n",//BT_PREV
	"AT+MD\r\n",//BT_NEXT
	"AT+CA\r\n",//BT_PARIR
	"AT+CB\r\n",//BT_PARIR_EXT
	"AT+CC\r\n",//BT_LINK_BACK
	"AT+CP\r\n",//BT_POWER_DOWN
	"AT+CD\r\n",//BT_DISCONN
	"AT+CZ\r\n",//BT_CLEAR_LIST
	"AT+H0\r\n",
	"AT+H1\r\n",
	"AT+H2\r\n",
	"AT+H3\r\n",
	"AT+H4\r\n",
	"AT+H5\r\n",
	"AT+H6\r\n",
	"AT+H7\r\n",
	"AT+H8\r\n",
	"AT+H9\r\n",
	"AT+HA\r\n",
	"AT+HB\r\n",
	"AT+HC\r\n",
	"AT+HD\r\n",	
	"AT+HE\r\n",
	"AT+HF\r\n",	
};
/******************************/
/*��������Function declaration*/
/******************************/

/*****************************/
/*��������function definetion*/
/*****************************/
/*******************************************************************************
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ����ڷ����ַ�
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/
 void Uart1Transmit_SendString(char *str)
 {
	 uint8_t  i;
	 while(uart1_EnableSend);
	 for(i=0;i<UART1_LEN_BUFFER;i++)
	 {
		Uart1_TransmitBuffer[i]=0;
	 }
	 for(i=0;*str!='\0';i++)
	 {
		 Uart1_TransmitBuffer[i]=*str;
		 str++;
	 }
	 uart1_TX_Pointer=0;
	 uart1_EnableSend=1;
	 UARTDR=Uart1_TransmitBuffer[uart1_TX_Pointer++];
 }
 
 
 /*******************************************************************************
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ��������ͨ���������������ж�ѡ���ĸ������
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/
void BT_Send_CMD(uint8_t cmd)
{
	uint8_t  code bt_VOL_Send_Tab[]={0,1,2,3,4,5,6,7};
	if(cmd)
		Uart1Transmit_SendString(&BT_Command_Tab[cmd][0]);
	else
		Uart1Transmit_SendString(&&BT_Command_Tab[0+bt_VOL_Send_Tab[sys_volume]][0]);
}
 
 /*******************************************************************************
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ�
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/
void BlueMode_Receive(void)
{
	uint8_t  i;
	char *BT_CMD;
	if((Flag_UART1_RX_Finish_A) || (Flag_UART1_RX_Finish_B))
	{
		if(Flag_UART1_RX_Finish_A)
		{
			Flag_UART1_RX_Finish_A=0;
			BT_CMD=uart1_ReceiveBuffer_A;
		}
		else 
		{
			Flag_UART1_RX_Finish_B=0;
			BT_CMD=uart1_ReceiveBuffer_B;
		}
		if(BT_CMD[0])
		{
		
		}
		
		for(i=0;i<UART1_LEN_BUFFER;i++)
			BT_CMD[i]=0;
	}
}
 
 /*******************************************************************************
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ�
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/
void BlueMode_Handle(void) //���յ���������Ϣ/״̬���д���
{
	BlueMode_Receive();
	if
}
 
 /*******************************************************************************
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ�
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/






