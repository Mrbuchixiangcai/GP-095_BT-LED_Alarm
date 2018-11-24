/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"
#include "led_drive.h"
/************************/
/*宏定义macro definition*/
/************************/

/*************************/
/*类型定义byte definition*/
/*************************/

/****************************/
/*标志位定义flags definetion*/
/****************************/

/*****************************/
/*变量定义variable definition*/
/*****************************/
uint8_t  value;
uint8_t  cur_Value;
uint8_t  user_Value;
uint8_t  sum_Value;
uint8_t  light_Brightness;//亮度
uint8_t  cntBT_BTTF_Switchover;//切换tf卡和蓝牙连接时间隔50ms发送两条命令，
uint16_t  cntJustPower_Delay;//用作上电延时计数5s
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
*******************************************************************************/
void LED_Deive(void)
{
    if (--value == 0)
    {
        _SET_1B(0);
        _SET_1C(0);
        _SET_2A(0);
        _SET_2B(0);
        _SET_2C(0);
        _SET_2D(0);
        _SET_2E(0);
        _SET_2F(0);
        _SET_2G(0);
        _SET_3A(0);
        _SET_3B(0);
        _SET_3C(0);
        _SET_3D(0);
        _SET_3E(0);
        _SET_3F(0);
        _SET_3G(0);
        _SET_4A(0);
        _SET_4B(0);
        _SET_4C(0);
        _SET_4D(0);
        _SET_4E(0);
        _SET_4F(0);
        _SET_4G(0);
        _SET_APM(0);
        _SET_AL(0);
        _SET_COL1(0);
        _SET_COL2(0);
        _SET_BT_BLUE(0);
		_SET_BT_RED(0);
    }
    if(--sum_Value==0)
    {
        if(LED_Brightness_TypeDef == LED_LOW)
        {
			
          value=100;
        }
        else if (LED_Brightness_TypeDef == LED_MEDIUM)
        {
            value = 175;
        }
        else if (LED_Brightness_TypeDef == LED_HIGH)
        {
            value = 255;
        }
        if (value)
        {
            _SET_1B(Flag_SET_1B);
            _SET_1C(Flag_SET_1C);
            _SET_2A(Flag_SET_2A);
            _SET_2B(Flag_SET_2B);
            _SET_2C(Flag_SET_2C);
            _SET_2D(Flag_SET_2D);
            _SET_2E(Flag_SET_2E);
            _SET_2F(Flag_SET_2F);
            _SET_2G(Flag_SET_2G);
            _SET_3A(Flag_SET_3A);
            _SET_3B(Flag_SET_3B);
            _SET_3C(Flag_SET_3C);
            _SET_3D(Flag_SET_3D);
            _SET_3E(Flag_SET_3E);
            _SET_3F(Flag_SET_3F);
            _SET_3G(Flag_SET_3G);
            _SET_4A(Flag_SET_4A);
            _SET_4B(Flag_SET_4B);
            _SET_4C(Flag_SET_4C);
            _SET_4D(Flag_SET_4D);
            _SET_4E(Flag_SET_4E);
            _SET_4F(Flag_SET_4F);
            _SET_4G(Flag_SET_4G);
            _SET_APM(Flag_SET_APM);
            _SET_AL(Flag_SET_AL);
            _SET_COL1(Flag_SET_COL1);
            _SET_COL2(Flag_SET_COL2);
			_SET_BT_BLUE(Flag_SET_BT_BLUE);
			_SET_BT_RED(Flag_SET_BT_RED);
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
void TF_Check(void)
{
	cntJustPower_Delay++;
	if(cntJustPower_Delay<500)//5s，这里上电延迟5s
		return;
	cntJustPower_Delay=500;
	if((TF_CARD_DET())==0)//为0说明插入了TF卡
	{
		if(Music_Mode_TypeDef == MUSIC_BT)
		{
			//Music_Mode_TypeDef=MUSIC_TF;
			bt_cmd=BT_SDO;//告诉蓝牙TF卡插入
			//BT_Send_CMD(BT_TF_CARD);//切换到TF卡模式
			cntBT_BTTF_Switchover++;
			if(cntBT_BTTF_Switchover>=5)//50ms//BT_TF_CARD和BT_SDO两个命令间隔30ms发送
			{
				cntBT_BTTF_Switchover=0;
				Music_Mode_TypeDef=MUSIC_TF;
				bt_cmd=BT_TF_CARD;//切换到TF卡模式
			}
		}
	}
	else
	{
		if(Music_Mode_TypeDef == MUSIC_TF)//转为蓝牙连接没有tf卡模式只进来一次，因为要发送数据，不能一直发送
		{
			//Music_Mode_TypeDef=MUSIC_BT;
			bt_cmd=BT_SDF;//告诉蓝牙TF卡拨出
			//BT_Send_CMD(BT_MODE);//切换回蓝牙模式
			cntBT_BTTF_Switchover++;
			if(cntBT_BTTF_Switchover>=5)//50ms//BT_TF_CARD和BT_SDO两个命令间隔30ms发送
			{
				cntBT_BTTF_Switchover=0;
				Music_Mode_TypeDef=MUSIC_BT;
				bt_cmd=BT_MODE;//切换回蓝牙模式
			}
		}
	}
}











