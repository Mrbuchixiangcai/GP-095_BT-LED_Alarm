/**********************************/
/*头文件定义header file definition*/
/**********************************/
#ifndef __BT_MODE_H__
#define __BT_MODE_H__
/*******************/
/*头文件header file*/
/*******************/

/************************/
/*宏定义macro definition*/
/************************/
#define UART1_LEN_BUFFER 10

/*************************/
/*类型定义byte definition*/
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
	BT_PAIR       ,//配对//8字符
	BT_LINK_BACK  ,//回连
	
	BT_PLAY       ,//播放//9字符
	BT_PAUSE      ,//暂停
	BT_PLAY_PAUSE ,//播放/暂停
	BT_PREV       ,//上一曲
	BT_NEXT       ,//下一曲
	BT_IQ		  ,//查询状态
	BT_DISCONN    ,//断开连接
	BT_QUERY_VOL  ,//获取音量值
	
	BT_POWER_DOWN ,//10//关机//10字符
	BT_SDO		  ,//TF卡插入告诉蓝牙
	BT_SDF		  ,//TF卡拔出告诉蓝牙
	BT_TF_CARD	  ,//切换到TF卡模式
	BT_MODE		  ,//从TF卡模式切回蓝牙模式
	BT_VOL	      ,//音量
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
/*标志位定义flags definetion*/
/****************************/

/*****************************/
/*变量定义variable definition*/
/*****************************/

/**************************/
/*数组定义array definition*/
/**************************/

/******************************/
/*函数声明Function declaration*/
/******************************/
void BlueMode_Handle(void);
/*****************************/
/*函数定义function definetion*/
/*****************************/

/********************************/
/*外部调用_宏定义macro definition*/
/********************************/

/*********************************/
/*外部调用_类型定义byte definition*/
/*********************************/
extern MUSIC_MODE_TypeDef Music_Mode_TypeDef;
/************************************/
/*外部调用_标志位定义flags definetion*/
/************************************/
extern bit Flag_BT_work;
extern bit Flag_BT_Connect;//蓝牙连接标志位
extern uint8_t Flag_BT_Play;   //蓝牙播放,1是在播放，0是在暂停(停止)
extern bit Flag_BT_Pause;  //暂停
extern bit Flag_UART1_RX_Finish_A;
extern bit Flag_UART1_RX_Finish_B;
extern bit Flag_UART_ReceiveBuffer_A_B;
extern bit Flag_BT_TF_Play;//蓝牙TF卡播放模式，1正在播放，0是在暂停(停止)
/*************************************/
/*外部调用_变量定义variable definition*/
/*************************************/
extern uint8_t  idata bt_cmd;
extern uint8_t  idata uart1_RX_Pointer;
extern uint8_t  idata uart1_TX_Pointer;
extern uint8_t  idata uart1_EnableSend;
extern uint8_t  idata uart1_TX_Timeout;
extern uint8_t  idata uart1_RX_Timeout;
/**********************************/
/*外部调用_数组定义array definition*/
/**********************************/
extern uint8_t   uart1_TransmitBuffer[UART1_LEN_BUFFER];
extern uint8_t  idata uart1_ReceiveBuffer_A[UART1_LEN_BUFFER];
extern uint8_t  idata uart1_ReceiveBuffer_B[UART1_LEN_BUFFER];
/**************************************/
/*外部调用_函数声明Function declaration*/
/**************************************/
void BT_Send_CMD(uint8_t cmd);
/*************************************/
/*外部调用_函数定义function definetion*/
/*************************************/


#endif




