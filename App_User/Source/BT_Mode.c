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
BT_STEP  BT_Step_TypeDef;
MUSIC_MODE_TypeDef Music_Mode_TypeDef;

/****************************/
/*标志位定义flags definetion*/
/****************************/
bit Flag_BT_work;
bit Flag_BT_Connect;//蓝牙连接标志位
bit Flag_BT_Play;   //蓝牙播放,1是在播放，0是在暂停(停止)
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
uint8_t  uart1_TransmitBuffer[UART1_LEN_BUFFER];
uint8_t  idata uart1_ReceiveBuffer_A[UART1_LEN_BUFFER];
uint8_t  idata uart1_ReceiveBuffer_B[UART1_LEN_BUFFER];
char  code BT_Command_Tab[][9]= //用于改变歌曲时发送给wifi的第几首歌
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
	"COM+V00\r\n",//音量
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
		if((BT_CMD[0] == 'B') && (BT_CMD[1] == 'T'))
		{
			if ((BT_CMD[3] == 'C') && (BT_CMD[4] == 'N'))
			{
				Flag_BT_Connect = 1;
			}
			//else if ((BT_CMD[3] == '') && (BT_CMD[4] == ''))//没有断开状态发送给MCU
			//{
			//	Flag_BT_Connect = 0;
			//}
			if ((BT_CMD[3] == 'P') && (BT_CMD[4] == 'A'))
			{
				Flag_BT_Play = 1;//蓝牙正在播放
			}
			if ((BT_CMD[3] == ' ') && (BT_CMD[4] == ' '))
			{
				Flag_BT_Play = 1;//蓝牙正在播放
			}
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
	//BlueMode_Receive();
	if (Music_Mode_TypeDef == MUSIC_BT)
	{
		if (Flag_BT_work == 0)//初始化蓝牙
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
				__EN_MUTE();//先静音
				BT_Step_TypeDef++;//每次加1有延时的作用，因为下次再进来是10ms之后
				break;
			case BT_STEP_INITI1:
				UART_Def_Init(); //先清除串口初始化
				__BT_CLR_POWER();  //先使蓝牙芯片断电
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI2:
				BT_Step_TypeDef++;
				break;          
			case BT_STEP_INITI3:
				__BT_SET_POWER();  //让蓝牙上电
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI4:
				UART_init(); //初始化串口
				BT_Step_TypeDef++;
				break;
			default:
				/*这个是蓝牙模式就俩亮起蓝灯，但是有个标志函数Display_Flag()放在了那里,这里也用，不然进不去标志函数*/
				if(BT_LED_BLUE_DET())//上电之后会置起与mcu连接的这个端口，mcu检测蓝牙芯片是否置起
				{
					/* 在设置闹钟的工作模式时，选择beep还是bt时，如果选择bt要让蓝牙标志闪烁，所以在这个设置状态下不能设置gblcd_bt */
					if (FlagKSet_TypeDef != FLAG_KEYSET_SHORT_ALARM_ALWORKMODE)
					{
						//
						gblcd_bt=1;//__BT_SET_LEDRED();//如果检测到蓝牙开机，就置起蓝灯
						gbUser_AdjClk=1;
					}
				}
//				if (sysVolume != btVolume)//这里有问题，会一直复位蓝牙，现写显示，回来再改
//				{
//					btVolume = sysVolume;
//					BT_Send_CMD(BT_VOL); //串口发送音量信息到蓝牙端
//				}
//				else if (bt_cmd)
//				{
//					BT_Send_CMD(bt_cmd);
//					bt_cmd = BT_NONE;  //清零
//				}
				if (BT_MUTE_DET()) //检测蓝牙是否发出静音命令
				{
					if (cntMuteBT > 5)
					{
						__DE_MUTE(); //解除静音
					}
					else
						cntMuteBT++;
				}
				else
				{
					__EN_MUTE(); //静音
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
			if(!(BT_LED_BLUE_DET()))//断电之后会置起与mcu连接的这个端口，mcu检测蓝牙芯片是否置起
				__BT_SET_LEDBLUE();//如果检测到蓝牙关机，就置起蓝灯
		}
		//Flag_BT_work = 0;
		switch (BT_Step_TypeDef)
		{
			case BT_STEP_START:
				__EN_MUTE();//先静音
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI1:
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI2:
				BT_Step_TypeDef++;
				break;
			case BT_STEP_INITI3:
				__BT_SET_POWER();  //让蓝牙上电
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






