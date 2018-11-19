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
BT_STEP  BT_Step_TypeDef;
MUSIC_MODE_TypeDef Music_Mode_TypeDef;

/****************************/
/*��־λ����flags definetion*/
/****************************/
bit Flag_BT_work;
bit Flag_BT_Connect;//�������ӱ�־λ
bit Flag_BT_Play;   //��������,1���ڲ��ţ�0������ͣ(ֹͣ)
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
uint8_t  uart1_TransmitBuffer[UART1_LEN_BUFFER];
uint8_t  idata uart1_ReceiveBuffer_A[UART1_LEN_BUFFER];
uint8_t  idata uart1_ReceiveBuffer_B[UART1_LEN_BUFFER];
char  code BT_Command_Tab[][9]= //���ڸı����ʱ���͸�wifi�ĵڼ��׸�
{
	"      \r\n ",//NONE
	"COM+PA\r\n ",//BT_PALY
	"COM+PU\r\n ",//BT_PAUSE
	"COM+PV\r\n ",//BT_PREV
	"COM+PN\r\n ",//BT_NEXT
	"COM+PR\r\n ",//BT_PARIR
	"COM+AC\r\n ",//BT_LINK_BACK
	"COM+PWD\r\n",//BT_POWER_DOWN
	"COM+DC\r\n ",//BT_DISCONN
	"COM+V00\r\n",//����
	"COM+V01\r\n",
	"COM+V02\r\n",
	"COM+V03\r\n",
	"COM+V04\r\n",
	"COM+V05\r\n",
	"COM+V06\r\n",
	"COM+V07\r\n",
	"COM+V08\r\n",
	"COM+V09\r\n",
	"COM+V10\r\n",
	"COM+V11\r\n",
	"COM+V12\r\n",
	"COM+V13\r\n",	
	"COM+V14\r\n",
	"COM+V15\r\n",	
	"COM+V16\r\n",
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
		uart1_TransmitBuffer[i]=0;
	}
	for(i=0;*str!='\0';i++)
	{
		uart1_TransmitBuffer[i]=*str;
		str++;
	}
	uart1_TX_Pointer=0;
	uart1_EnableSend=1;
	UARTDR=uart1_TransmitBuffer[uart1_TX_Pointer++];
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
char  temp1,temp2,temp3,temp4;
void BT_Send_CMD(uint8_t cmd)
{
	uint8_t  code bt_VOL_Send_Tab[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	if(cmd<BT_VOL)
		Uart1Transmit_SendString(&BT_Command_Tab[cmd][0]);
	else
	{
		Uart1Transmit_SendString(&BT_Command_Tab[BT_VOL+bt_VOL_Send_Tab[sysVolume]][0]);
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
		if((BT_CMD[0] == 'B') && (BT_CMD[1] == 'T'))
		{
			if ((BT_CMD[3] == 'C') && (BT_CMD[4] == 'N'))
			{
				Flag_BT_Connect = 1;
			}
			//else if ((BT_CMD[3] == '') && (BT_CMD[4] == ''))//û�жϿ�״̬���͸�MCU
			//{
			//	Flag_BT_Connect = 0;
			//}
			if ((BT_CMD[3] == 'P') && (BT_CMD[4] == 'A'))
			{
				Flag_BT_Play = 1;//�������ڲ���
			}
			if ((BT_CMD[3] == ' ') && (BT_CMD[4] == ' '))
			{
				Flag_BT_Play = 1;//�������ڲ���
			}
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
	//BlueMode_Receive();
	if (Music_Mode_TypeDef == MUSIC_BT)
	{
		if (Flag_BT_work == 0)//��ʼ������
		{
			cntMuteBT = 0;
			Flag_BT_Connect = 0;
			Flag_BT_Play = 0;
			btVolume = ~sysVolume;
			BT_Step_TypeDef = BT_STEP_START;
		}
		Flag_BT_work = 1;
		switch (BT_Step_TypeDef)
		{
			case BT_STEP_START:
				__EN_MUTE();//�Ⱦ���
				BT_Step_TypeDef++;//ÿ�μ�1����ʱ�����ã���Ϊ�´��ٽ�����10ms֮��
				break;
			case BT_STEP_INITI1:
				UART_Def_Init(); //��������ڳ�ʼ��
				__BT_CLR_POWER();  //��ʹ����оƬ�ϵ�
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI2:
				BT_Step_TypeDef++;
				break;          
			case BT_STEP_INITI3:
				__BT_SET_POWER();  //�������ϵ�
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI4:
				UART_init(); //��ʼ������
				BT_Step_TypeDef++;
				break;
			default:
				/*���������ģʽ�����������ƣ������и���־����Display_Flag()����������,����Ҳ�ã���Ȼ����ȥ��־����*/
				if(BT_LED_BLUE_DET())//�ϵ�֮���������mcu���ӵ�����˿ڣ�mcu�������оƬ�Ƿ�����
				{
					/* ���������ӵĹ���ģʽʱ��ѡ��beep����btʱ�����ѡ��btҪ��������־��˸���������������״̬�²�������gblcd_bt */
					if (FlagKSet_TypeDef != FLAG_KEYSET_SHORT_ALARM_ALWORKMODE)
					{
						//
						gblcd_bt=1;//__BT_SET_LEDRED();//�����⵽��������������������
						gbUser_AdjClk=1;
					}
				}
//				if (sysVolume != btVolume)//���������⣬��һֱ��λ��������д��ʾ�������ٸ�
//				{
//					btVolume = sysVolume;
//					BT_Send_CMD(BT_VOL); //���ڷ���������Ϣ��������
//				}
//				else if (bt_cmd)
//				{
//					BT_Send_CMD(bt_cmd);
//					bt_cmd = BT_NONE;  //����
//				}
				if (BT_MUTE_DET()) //��������Ƿ񷢳���������
				{
					if (cntMuteBT > 5)
					{
						__DE_MUTE(); //�������
					}
					else
						cntMuteBT++;
				}
				else
				{
					__EN_MUTE(); //����
				}
				break;
		}
	}
	else
	{
		if (Flag_BT_work == 1)
		{
			cntMuteBT = 0;
			BT_Step_TypeDef = BT_STEP_START;
			if(!(BT_LED_BLUE_DET()))//�ϵ�֮���������mcu���ӵ�����˿ڣ�mcu�������оƬ�Ƿ�����
				__BT_SET_LEDBLUE();//�����⵽�����ػ�������������
		}
		//Flag_BT_work = 0;
		switch (BT_Step_TypeDef)
		{
			case BT_STEP_START:
				__EN_MUTE();//�Ⱦ���
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI1:
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI2:
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI3:
				__BT_SET_POWER();  //�������ϵ�
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI4:
				BT_Step_TypeDef++;
				break;
			default:
				break;
		}
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






