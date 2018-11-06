/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"

/************************/
/*宏定义macro definition*/
/************************/

/*************************/
/*类型定义byte definition*/
/*************************/
BT_STEP  BT_Step;
/****************************/
/*标志位定义flags definetion*/
/****************************/
bit Flag_BT_work;
bit Flag_BT_Connect;//蓝牙连接标志位
bit Flag_BT_Play;   //蓝牙播放
bit Flag_BT_Pause;  //暂停
bit Flag_UART1_RX_Finish_A;
bit Flag_UART1_RX_Finish_B;
bit Flag_UART_ReceiveBuffer_A_B;

/*****************************/
/*变量定义variable definition*/
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
/*数组定义array definition*/
/**************************/
uint8_t  xdata uart1_TransmitBuffer[UART1_LEN_BUFFER];
uint8_t  xdata uart1_ReceiveBuffer_A[UART1_LEN_BUFFER];
uint8_t  xdata uart1_ReceiveBuffer_B[UART1_LEN_BUFFER];
char  code BT_Command_tab[][8]= //用于改变歌曲时发送给wifi的第几首歌
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
/*函数声明Function declaration*/
/******************************/

/*****************************/
/*函数定义function definetion*/
/*****************************/
/*******************************************************************************
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：串口发送字符
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
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
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：发送命令，通过传进来的数据判断选择哪个命令发送
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
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
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
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
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/
void BlueMode_Handle(void) //接收到的数据信息/状态进行处理
{
	BlueMode_Receive();
	if
}
 
 /*******************************************************************************
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/






