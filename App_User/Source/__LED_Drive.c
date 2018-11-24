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

/****************************/
/*��־λ����flags definetion*/
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
bit Flag_SET_AM;
bit Flag_SET_PM;
bit Flag_SET_AL;
bit Flag_SET_COL1;
bit Flag_SET_COL2;
bit Flag_SET_BEEP;
/*****************************/
/*��������variable definition*/
/*****************************/
uint8_t  Led_Buffer[4];
uint8_t  Led_Buffer_Copy[6];
/**************************/
/*���鶨��array definition*/
/**************************/

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
 * �������ܣ�
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
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
	if (gbTestMode)//GP-095û�в���ģʽ
	{
		Led_Buffer[0] = 0xff;
		Led_Buffer[1] = 0xff;
		Led_Buffer[2] = 0xff;
		Led_Buffer[3] = 0xff;
	}
	if (Led_Buffer_Copy[0] != Led_Buffer[0])
	{
		if (Led_Buffer[0] & 0x10)  //1b:7���������'b'��λ�Σ����Led_Buffer[0]=0x30,�Ǿ��ǡ�1��
			__SET_1B();
		else
			__CLR_1B();
		if (Led_Buffer[0] & 0x20)  //1c:7���������'c'��λ��
			__SET_1C();
		else
			__CLR_1C();
		Led_Buffer_Copy[0] = Led_Buffer[0];
	}
	if (Led_Buffer_Copy[1] != Led_Buffer[1])
	{
		if (Led_Buffer[1] & 0x01)  //a:7���������'a'��λ�Σ����Led_Buffer[0]=
			__SET_2A();
		else
			__CLR_2A();
		if (Led_Buffer[1] & 0x02)  //b:7���������'b'��λ��
			__SET_2B();
		else
			__CLR_2B();
		if (Led_Buffer[1] & 0x04)  //c
			__SET_2C();
		else
			__CLR_2C();
		if (Led_Buffer[1] & 0x08)  //d
			__SET_2D();
		else
			__CLR_2D();
		if (Led_Buffer[1] & 0x10)  //e
			__SET_2E();
		else
			__CLR_2E();
		if (Led_Buffer[1] & 0x20)  //f
			__SET_2F();
		else
			__CLR_2F();
		if (Led_Buffer[1] & 0x40)  //g
			__SET_2G();
		else
			__CLR_2G();
		Led_Buffer_Copy[1] = Led_Buffer[1];
	}
	if (Led_Buffer_Copy[2] != Led_Buffer[2])
	{
		if (Led_Buffer[2] & 0x01)  //a:7���������'a'��λ�Σ����Led_Buffer[0]=
			__SET_3A();
		else
			__CLR_3A();
		if (Led_Buffer[2] & 0x02)  //b:7���������'b'��λ��
			__SET_3B();
		else
			__CLR_3B();
		if (Led_Buffer[2] & 0x04)  //c
			__SET_3C();
		else
			__CLR_3C();
		if (Led_Buffer[2] & 0x08)  //d
			__SET_3D();
		else
			__CLR_3D();
		if (Led_Buffer[2] & 0x10)  //e
			__SET_3E();
		else
			__CLR_3E();
		if (Led_Buffer[2] & 0x20)  //f
			__SET_3F();
		else
			__CLR_3F();
		if (Led_Buffer[2] & 0x40)  //g
			__SET_3G();
		else
			__CLR_3G();
		Led_Buffer_Copy[2] = Led_Buffer[2];
	}
	if (Led_Buffer_Copy[3] != Led_Buffer[3])
	{
		if (Led_Buffer[3] & 0x01)  //a:7���������'a'��λ�Σ����Led_Buffer[0]=
			__SET_4A();
		else
			__CLR_4A();
		if (Led_Buffer[3] & 0x02)  //b:7���������'b'��λ��
			__SET_4B();
		else
			__CLR_4B();
		if (Led_Buffer[3] & 0x04)  //c
			__SET_4C();
		else
			__CLR_4C();
		if (Led_Buffer[3] & 0x08)  //d
			__SET_4D();
		else
			__CLR_4D();
		if (Led_Buffer[3] & 0x10)  //e
			__SET_4E();
		else
			__CLR_4E();
		if (Led_Buffer[3] & 0x20)  //f
			__SET_4F();
		else
			__CLR_4F();
		if (Led_Buffer[3] & 0x40)  //g
			__SET_4G();
		else
			__CLR_4G();
		Led_Buffer_Copy[3] = Led_Buffer[3];
	}
	if (lcd_BitRam0 != Led_Buffer_Copy[4])
	{
		if (lcd_BitRam0 & 0x01)  //buzz��
			__SET_BEEP();
		else
			__CLR_BEEP();
		if (lcd_BitRam0 & 0x02)
			__AL1_SET_FLAG();
		else
			__AL1_CLR_FLAG();
		if (lcd_BitRam0 & 0x10)  //dot:�㣬
		{
			__SET_COL1();
			__SET_COL2();
		}
		else
		{
			__CLR_COL1();
			__CLR_COL2();
		}
		if (lcd_BitRam0 & 0x40)
		{
			//˯��
		}
		else
		{
			//���˯��
		}
		Led_Buffer_Copy[4] = Led_Buffer[4];
	}
	if (lcd_BitRam1 != Led_Buffer_Copy[5])
	{
		if (lcd_BitRam1 & 0x01)  //am��
			__SET_AM();//
		else
		{

		}
		if (lcd_BitRam1 & 0x02)  //pm��
			__SET_PM();
		else
		{

		}
		if(lcd_BitRam1&0x80)
			__BT_SET_LEDBLUE();
		else
			__BT_CLR_LEDBLUE();
		Led_Buffer_Copy[5] = Led_Buffer[5];
	}
}
















