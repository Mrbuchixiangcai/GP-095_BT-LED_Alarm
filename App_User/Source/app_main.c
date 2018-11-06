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
PLAY_MODE_TypeDef  TYPE_Play_Mode;
ALRAM_TypeDef  TYPE_Alarm1;

/****************************/
/*标志位定义flags definetion*/
/****************************/
bit  AppTick0;
bit  AppTick1;
bit  AppTick2;
bit  AppTick3;
bit  AppTick4;
bit  AppTick5;
bit  AppTick1ms;

bit  Flag_Alarm;  //为1为闹钟开启，为0则关闭
bit  Flag_AlarmSet_Confirm_TimeCnt_30Sec;//短按ALARM键确认设置或不动作30s自动保存，(为1是确认闹钟设置标志位)为2是30s计时标志位，


/*****************************/
/*变量定义variable definition*/
/*****************************/
uint8_t  idata cntAppTick;
bit		 	   gbHalfSecong;
uint8_t  idata gRTC_Sec;//RTC数据 
uint8_t  idata gRTC_Sec_bk;
uint8_t  idata gRTC_Minute;
uint8_t  idata gRTC_Minute_bk;
uint8_t  idata gRTC_Hour;
uint8_t  idata gRTC_Hour_bk;
uint8_t  xdata gRTC_Hour_bk_24;//计数24小时
uint8_t  idata gRTC_Week; //一周7天
uint8_t  idata sys_volume;
uint16_t idata timeCnt_30Sec;//短按ALARM键缺人设置或不动作30s自动保存，30s计时


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
 * 函数功能：时间比较，把RTC时间与某个定时时间比较，比如闹钟
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/
void Compare_1MinutePorc(void)
{
	//static uint8_t  cntSetVolume; //此变量只在上电时初始化一次，再调用此函数时不会执行此语句
	if(gRTC_Sec!=gRTC_Sec_bk)
	{
		gRTC_Sec_bk=gRTC_Sec;
		
		if(gRTC_Minute!=gRTC_Minute_bk)
		{
			gRTC_Minute_bk=gRTC_Minute;
			if(Flag_Alarm==1)
			{
				
			}
				
			if(gRTC_Hour!=gRTC_Hour_bk)
			{
				gRTC_Hour_bk=gRTC_Hour_bk;
				gRTC_Hour_bk_24++;
				if(gRTC_Hour_bk_24>=24)
				{
					gRTC_Hour_bk_24=0;
					
				}
			}
		}
	}
}

/*******************************************************************************
 * 函数原型：
 * 输入参数：
 * 输出参数：
 * 函数功能：其他程序需要用到的计时放在这里进行
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/
void Timing_Handle(void)
{
	if(Flag_AlarmSet_Confirm_TimeCnt_30Sec==2)
	{
		timeCnt_30Sec++;
		if(timeCnt_30Sec>=3000)
		{
			Flag_AlarmSet_Confirm_TimeCnt_30Sec=0;
			timeCnt_30Sec=0;
			alarmHour=tempAlarmHour;	//30s计时结束把设定的闹钟时间赋给与RTC比对的闹钟变量
			alarmMinute=tempAlarmMinute;
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
void Sys_Tick(void)
{
	AppTick1ms=1;
	if(cntAppTick==0)
		AppTick0=1;
	if(cntAppTick==1)
		AppTick1=1;
	if(cntAppTick==2)
		AppTick2=1;
	if(cntAppTick==3)
		AppTick3=1;
	if(cntAppTick==4)
		AppTick4=1;
	if(cntAppTick==5)
		AppTick5=1;
	if(cntAppTick==6)
	{
	
	}
	if(++cntAppTick>=10)
		cntAppTick=0;
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
void PowerON_Reset(void)
{
	TYPE_Play_Mode=PLAY_JUST_POWER;//刚上电，模式设为刚上电模式
	TYPE_LED_Brightness=LED_HIGH;//亮度默认为高
	TYPE_Alarm1.Alarm_Mode=ALARM_BEEP; //自己加的为闹钟响闹模式为beep模式，方便写程序，也防止使用者在设置闹钟
								//时没有选择模式，那就选择默认是beep模式
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
void app_main(void)
{
	PowerON_Reset();
	while(1)
	{
		if(AppTick1ms)
		{
			AppTick1ms=0;
		}
		if(AppTick0)
		{
			AppTick0=0;
			KeyScan();
			KeyComMsg();
		}
		if(AppTick1)
		{
			AppTick1=0;
			
		}
		if(AppTick2)
		{
			AppTick2=0;
			
		}
		if(AppTick3)
		{
			AppTick3=0;
			
		}
		if(AppTick4)
		{
			AppTick4=0;
			
		}
		if(AppTick5)
		{
			AppTick5=0;
			Timing_Handle();
			Compare_1MinutePorc();
		}
		WDT_clear();	
	}
}










