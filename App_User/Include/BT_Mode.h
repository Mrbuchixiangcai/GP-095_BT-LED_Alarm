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
#define UART1_LEN_BUFFER 8

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
	BT_PAUSE      ,//暂停
	BT_PLAY       ,//播放
	BT_PREV       ,//上一曲
	BT_NEXT       ,//下一曲
	BT_PAIR       ,//配对
	//BT_PAIR_EXT   ,//退出配对
	BT_LINK_BACK  ,//回连
	BT_POWER_DOWN ,//关机
	BT_DISCONN    ,//断开连接
	//BT_CLEAR_LIST ,//断开连接
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

/*************************************/
/*外部调用_变量定义variable definition*/
/*************************************/

/**********************************/
/*外部调用_数组定义array definition*/
/**********************************/

/**************************************/
/*外部调用_函数声明Function declaration*/
/**************************************/

/*************************************/
/*外部调用_函数定义function definetion*/
/*************************************/


#endif




