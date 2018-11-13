/*******************/
/*头文件header file*/
/*******************/
#include "app_main.h"

/************************/
/*宏定义macro definition*/
/************************/
u8 dispBuff[5];
#define DIG_NUM1 dispBuff[0]
#define DIG_NUM2 dispBuff[1]
#define DIG_NUM3 dispBuff[2]
#define DIG_NUM4 dispBuff[3]
#define DIG_NUM5 dispBuff[4]
/*************************/
/*类型定义byte definition*/
/*************************/
LED_BRIGHTNESS_TypeDef  LED_Brightness_TypeDef;
ALRAM_TypeDef  Alarm1_TypeDef;

/****************************/
/*标志位定义flags definetion*/
/****************************/
BOOL  gbDispSetA1;

//变量定义
u8 bdata lcd_BitRam0;
u8 bdata lcd_BitRam1;

sbit  gblcd_buz1   = lcd_BitRam0 ^ 0;
sbit  gblcd_al     = lcd_BitRam0 ^ 1;//原来是gblcd_radio1
sbit  gblcd_buz2   = lcd_BitRam0 ^ 2;
sbit  gblcd_radio2 = lcd_BitRam0 ^ 3;
sbit  gblcd_dot    = lcd_BitRam0 ^ 4;//
sbit  gblcd_colon  = lcd_BitRam0 ^ 5;//
sbit  gblcd_sleep  = lcd_BitRam0 ^ 6;//
sbit  gblcd_aux    = lcd_BitRam0 ^ 7;
sbit  gblcd_am     = lcd_BitRam1 ^ 0;//
sbit  gblcd_pm     = lcd_BitRam1 ^ 1;//
sbit  gblcd_fm     = lcd_BitRam1 ^ 2;
sbit  gblcd_mw     = lcd_BitRam1 ^ 3;
sbit  gblcd_mhz    = lcd_BitRam1 ^ 4;
sbit  gblcd_khz    = lcd_BitRam1 ^ 5;
sbit  gblcd_five   = lcd_BitRam1 ^ 6;
sbit  gblcd_bt	   = lcd_BitRam1 ^ 7;
//                                                                                                                                                                                                                                           sbit  gblcd_al	   = lcd_BitRam1 ^ 7; //al:alarm
/*****************************/
/*变量定义variable definition*/
/*****************************/
u8		 dispStatusNum;//cntDispStatus;


/**************************/
/*数组定义array definition*/
/**************************/
code u8 dispCode_Arr[]=  //arr:array
{
	DIG_0,DIG_1,DIG_2,DIG_3,DIG_4,DIG_5,DIG_6,DIG_7,DIG_8,DIG_9,DIG_NONE,		//数字
	CH_a,CH_b,CH_c,CH_d,CH_h,CH_l,CH_n,CH_o,CH_r,CH_t,CH_u,CH_y,				//小写字母
	CH_A,CH_C,CH_E,CH_F,CH_G,CH_H,CH_I,CH_J,CH_L,CH_N,CH_O,CH_P,CH_S,CH_U,CH__,	//大写字母
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
 * 函数功能：把要更新的值赋给DIG_NUMx，
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：把要更新的值赋给DIG_NUMx，然后相当于赋值给了dispBuff[x]，dispBuff被调用
 *		 在Led_Buffer[i] = dispCode_Arr[dispBuff[i]]这里被赋给个Led_Buffer,
 *		 Led_Buffer会被与上一次调用Led_Buffer时判断，，然后置位相应的LED端口。
 *******************************************************************************/
void DisplayNum12(u8 dat)
{
	DIG_NUM1 = (dat / 10); //相当于赋值给了dispBuff[0]，最后判断是否与对应的LED，
	DIG_NUM2 = (dat % 10);
	if (!DIG_NUM1)
		DIG_NUM1 = eD_NONE;
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
void DisplayNum34(u8 dat)
{
	DIG_NUM3 = (dat / 10);
	DIG_NUM4 = (dat % 10);
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
BOOL NoFlash(void)
{
	if (cntNoFlash != 0)
	{
		//cntNoFlash--;
		return 1;
	}
	return 0;
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
void Display_HH_MM(u8 hh_mm_TypeDef)
{
	u8  tmpHour, tmpMinute;
	switch (hh_mm_TypeDef)
	{
		case eDS_RTC:
			tmpHour=gRTC_Hour;
			tmpMinute=gRTC_Minute;
			break;
		case eDS_AL1:
			tmpHour = Alarm1_TypeDef.hour;
			tmpMinute = Alarm1_TypeDef.minute;
			break;
	}
	if (gb12HourDisp)//12小时制显示
	{
		if (tmpHour < 12)  //如果小于12则是凌晨0点到11:59，为上午
		{
			gblcd_am = 1;  //标志位为1，设置对应的LED是否亮起
		}
		else
		{
			gblcd_pm = 1; //如果大于12则是12:00到23:59，为下午//标志位为1，设置对应的LED是否亮起
			tmpHour -= 12;//因为是12小时制，所以下午的时间也是12小时制显示，要减12
		}
		if (tmpHour == 0) //零点是显示12的，中午12点也是显示12的
		{
			tmpHour = 12;
		}
		DisplayNum12(tmpHour);
		DisplayNum34(tmpMinute);
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
void Display_ALarm1(void)
{
	gblcd_colon = 1;
	Display_HH_MM(eDS_AL1);
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
void Display_SetAlarm1(void)
{
	if ((gb0_5s) || (NoFlash()))
	{
		gblcd_colon = 1;
		Display_HH_MM(eDS_AL1);
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
 * 备注：之所以gb0_5s大于0时才能进入if代码，是因为这个是设置RTC，要每隔0.5s闪烁，
 *       而cntNoFlash()是要常亮，比如在设置时时间在闪，但是要按下加或者减时要常
 *		 亮1是，这样让设置的人看到，所以要gb0_5s为大于0和常亮时进入
 *******************************************************************************/
void Display_SetRTC(void)
{
	if ((gb0_5s) || (NoFlash()))
	{
		gblcd_colon = 1;
		Display_HH_MM(eDS_RTC);
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
void Display_RTC(void)
{
	if ((!gbUser_AdjClk) || (gbHalfSecond))
	{
		gblcd_colon = 1;
		Display_HH_MM(eDS_RTC);
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
void Display_Zone(void) //什么意思
{
	if ((gb0_5s) || (NoFlash()))
	{
		DisplayNum34(gZone);
	}
}

/*******************************************************************************
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：清除显示缓存
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/
void ClearDisplayBuff(void)
{
	u8  clearCnt;
	for (clearCnt = 0; clearCnt < 5; clearCnt++)
	{
		dispBuff[clearCnt] = eD_NONE;
	}
	lcd_BitRam0 = 0;
	lcd_BitRam1 = 0;
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
void Display_Off(void)
{
	DIG_NUM1 = eD_NONE;
	DIG_NUM2 = eD_O;
	DIG_NUM3 = eD_F;
	DIG_NUM4 = eD_F;
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
void Display_Al1Flag(void)
{
	if (Alarm1_TypeDef.AlarmWorkMode == ALARM_BEEP)//闹钟响时的工作模式，
		gblcd_buz1 = 1;//闹钟响时工作铃声为beep
	else if (Alarm1_TypeDef.AlarmWorkMode == ALARM_BT)
	{
		if ((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (Alarm1_TypeDef.AlarmSnooze == ALARM_SNOOZE_OFF))
		{
			gblcd_bt = 1;//如果是蓝牙就显示蓝牙或者连接到蓝牙
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
void UpdateDisplay(u8 dispStatus)
{
	switch (dispStatus)
	{
		case DISP_AL1:
			Display_ALarm1();   
			break;
		case ADJ_CLK:
			Display_SetRTC(); //设置RTC时的显示
			break;
		case ADJ_ZONE:
			Display_Zone();
			break; 
		case ADJ_ALARM1:
			Display_SetAlarm1(); //设置闹钟时的显示
			break; 
		case POWER_OFF_DISP:
			Display_Off();
			break; 
		default:
			Display_RTC();    //RTC走时状态显示
			break;
	}
	if (cntNoFlash != 0)
		cntNoFlash--;
}

/*******************************************************************************
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：各种显示标志，比如两点(xx：xx)，buzz，am，pm
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/
void Display_Flag(void)
{
	if (dispStatus == ADJ_CLK)
		return;
	if ((dispStatus == ADJ_ALARM1) || (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
	{
		if (dispStatus == ADJ_ALARM1)
		{
			if ((gb0_5s) || (NoFlash())) //NoFlash()不闪烁
				Display_Al1Flag();
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
void Display(void)
{
	u8  cnt;
	if ((gbUser_AdjClk) || (dispStatusNum))
	{
		ClearDisplayBuff(); //清除显示缓存
		UpdateDisplay(dispStatus);
		Display_Flag();
		for (cnt = 0; cnt < 4; cnt++)
		{
			Led_Buffer[i] = dispCode_Arr[dispBuff[i]];
		}
		Display_LED();
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




