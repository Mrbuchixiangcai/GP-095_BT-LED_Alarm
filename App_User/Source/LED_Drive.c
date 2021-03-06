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

/****************************/
/*标志位定义flags definetion*/
/****************************/
bit Flag_SET_1B;
bit Flag_SET_1C;
bit Flag_SET_2A;
bit Flag_SET_2B;
bit Flag_SET_2C;
bit Flag_SET_2D;
bit Flag_SET_2E;
bit Flag_SET_2F;
bit Flag_SET_2G;
bit Flag_SET_3A;
bit Flag_SET_3B;
bit Flag_SET_3C;
bit Flag_SET_3D;
bit Flag_SET_3E;
bit Flag_SET_3F;
bit Flag_SET_3G;
bit Flag_SET_4A;
bit Flag_SET_4B;
bit Flag_SET_4C;
bit Flag_SET_4D;
bit Flag_SET_4E;
bit Flag_SET_4F;
bit Flag_SET_4G;
bit Flag_SET_APM;
bit Flag_SET_AL;
bit Flag_SET_COL1;
bit Flag_SET_COL2;
bit Flag_SET_BT_BLUE;//蓝牙连接没有tf卡
bit Flag_SET_BT_RED;//蓝牙连接有tf卡

/*****************************/
/*变量定义variable definition*/
/*****************************/
uint8_t  Led_Buffer[4];
uint8_t  Led_Buffer_Copy[6];
/**************************/
/*数组定义array definition*/
/**************************/

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
 * 函数功能：
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 * //  AAAAA
 * // F     B
 * // F     B
 * //  GGGGG
 * // E     C
 * // E     C
 * //  DDDDD
 *******************************************************************************/
void Display_LED(void)
{
	if (gbTestMode)//GP-095没有测试模式
	{
		Led_Buffer[0] = 0xff;
		Led_Buffer[1] = 0xff;
		Led_Buffer[2] = 0xff;
		Led_Buffer[3] = 0xff;
	}
	if (Led_Buffer_Copy[0] != Led_Buffer[0])
	{
		if (Led_Buffer[0] & 0x02)  //1b:7段数码管中'b'的位段，如果Led_Buffer[0]=0x30,那就是“1”
			Flag_SET_1B=1; //__SET_1B();
		else
			Flag_SET_1B=0; //__CLR_1B();
		if (Led_Buffer[0] & 0x04)  //1c:7段数码管中'c'的位段
			Flag_SET_1C=1; //__SET_1C();
		else
			Flag_SET_1C=0; //__CLR_1C();
		Led_Buffer_Copy[0] = Led_Buffer[0];
	}
	if (Led_Buffer_Copy[1] != Led_Buffer[1])
	{
		if (Led_Buffer[1] & 0x01)  //a:7段数码管中'a'的位段，如果Led_Buffer[0]=
			Flag_SET_2A=1; //__SET_2A();
		else
			Flag_SET_2A=0; //__CLR_2A();
		if (Led_Buffer[1] & 0x02)  //b:7段数码管中'b'的位段
			Flag_SET_2B=1; //__SET_2B();
		else
			Flag_SET_2B=0; //__CLR_2B();
		if (Led_Buffer[1] & 0x04)  //c
			Flag_SET_2C=1; //__SET_2C();
		else
			Flag_SET_2C=0; //__CLR_2C();
		if (Led_Buffer[1] & 0x08)  //d
			Flag_SET_2D=1; //__SET_2D();
		else
			Flag_SET_2D=0; //__CLR_2D();
		if (Led_Buffer[1] & 0x10)  //e
			Flag_SET_2E=1; //__SET_2E();
		else
			Flag_SET_2E=0; //__CLR_2E();
		if (Led_Buffer[1] & 0x20)  //f
			Flag_SET_2F=1; //__SET_2F();
		else
			Flag_SET_2F=0; //__CLR_2F();
		if (Led_Buffer[1] & 0x40)  //g
			Flag_SET_2G=1; //__SET_2G();
		else
			Flag_SET_2G=0; //__CLR_2G();
		Led_Buffer_Copy[1] = Led_Buffer[1];
	}
	if (Led_Buffer_Copy[2] != Led_Buffer[2])
	{
		if (Led_Buffer[2] & 0x01)  //a:7段数码管中'a'的位段，如果Led_Buffer[0]=
			Flag_SET_3A=1; //__SET_3A();
		else
			Flag_SET_3A=0; //__CLR_3A();
		if (Led_Buffer[2] & 0x02)  //b:7段数码管中'b'的位段
			Flag_SET_3B=1; //__SET_3B();
		else
			Flag_SET_3B=0; //__CLR_3B();
		if (Led_Buffer[2] & 0x04)  //c
			Flag_SET_3C=1; //__SET_3C();
		else
			Flag_SET_3C=0; //__CLR_3C();
		if (Led_Buffer[2] & 0x08)  //d
			Flag_SET_3D=1; //__SET_3D();
		else
			Flag_SET_3D=0; //__CLR_3D();
		if (Led_Buffer[2] & 0x10)  //e
			Flag_SET_3E=1; //__SET_3E();
		else
			Flag_SET_3E=0; //__CLR_3E();
		if (Led_Buffer[2] & 0x20)  //f
			Flag_SET_3F=1; //__SET_3F();
		else
			Flag_SET_3F=0; //__CLR_3F();
		if (Led_Buffer[2] & 0x40)  //g
			Flag_SET_3G=1; //__SET_3G();
		else
			Flag_SET_3G=0; //__CLR_3G();
		Led_Buffer_Copy[2] = Led_Buffer[2];
	}
	if (Led_Buffer_Copy[3] != Led_Buffer[3])
	{
		if (Led_Buffer[3] & 0x01)  //a:7段数码管中'a'的位段，如果Led_Buffer[0]=
			Flag_SET_4A=1; //__SET_4A();
		else
			Flag_SET_4A=0; //__CLR_4A();
		if (Led_Buffer[3] & 0x02)  //b:7段数码管中'b'的位段
			Flag_SET_4B=1; //__SET_4B();
		else
			Flag_SET_4B=0; //__CLR_4B();
		if (Led_Buffer[3] & 0x04)  //c
			Flag_SET_4C=1; //__SET_4C();
		else
			Flag_SET_4C=0; //__CLR_4C();
		if (Led_Buffer[3] & 0x08)  //d
			Flag_SET_4D=1; //__SET_4D();
		else
			Flag_SET_4D=0; //__CLR_4D();
		if (Led_Buffer[3] & 0x10)  //e
			Flag_SET_4E=1; //__SET_4E();
		else
			Flag_SET_4E=0; //__CLR_4E();
		if (Led_Buffer[3] & 0x20)  //f
			Flag_SET_4F=1; //__SET_4F();
		else
			Flag_SET_4F=0; //__CLR_4F();
		if (Led_Buffer[3] & 0x40)  //g
			Flag_SET_4G=1; //__SET_4G();
		else
			Flag_SET_4G=0; //__CLR_4G();
		Led_Buffer_Copy[3] = Led_Buffer[3];
	}
	if (lcd_BitRam0 != Led_Buffer_Copy[4])
	{
//		if (lcd_BitRam0 & 0x01)  //buzz响
//			BUZ_OnOff(1);//Flag_SET_BEEP=1;
//		else
//			BUZ_OnOff(0);//Flag_SET_BEEP=0;
		if (lcd_BitRam0 & 0x02)  //ALARM1
			Flag_SET_AL=1; //__AL1_SET_FLAG();
		else
			Flag_SET_AL=0; //__AL1_CLR_FLAG();
		if (lcd_BitRam0 & 0x08)//蓝牙连接有tf卡
			Flag_SET_BT_RED=1;
		else
			Flag_SET_BT_RED=0;
		if (lcd_BitRam0 & 0x10)  //dot:点，
		{
			Flag_SET_COL1=1; //__SET_COL1();
			Flag_SET_COL2=1; //__SET_COL2();
		}
		else
		{
			Flag_SET_COL1=0; //__CLR_COL1();
			Flag_SET_COL2=0; //__CLR_COL2();
		}
		if (lcd_BitRam0 & 0x40)
		{
			//睡眠
		}
		else
		{
			//解除睡眠
		}
		Led_Buffer_Copy[4] = Led_Buffer[4];
	}
	if (lcd_BitRam1 != Led_Buffer_Copy[5])
	{
		if (lcd_BitRam1 & 0x01)  //am亮,因为am/pm共用一个led，所以led不亮就是am
			Flag_SET_APM=0; //__SET_AM();//为0是上午，led不亮，为1是下午，led亮
		if (lcd_BitRam1 & 0x02)  //pm亮
			Flag_SET_APM=1; //__SET_PM();
		if(lcd_BitRam1&0x80)//蓝牙连接没有tf卡
			Flag_SET_BT_BLUE=1; //__BT_SET_LEDBLUE();
		else
			Flag_SET_BT_BLUE=0; //__BT_CLR_LEDBLUE();
		Led_Buffer_Copy[5] = Led_Buffer[5];
	}
}
















