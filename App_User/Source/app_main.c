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
PLAY_MODE_TypeDef  PlayMode_TypeDef;
CONTROL_COMMAND_TypeDef Ctrl_Com_TypeDef;

/****************************/
/*标志位定义flags definetion*/
/****************************/
bit   AppTick0;
bit   AppTick1;
bit   AppTick2;
bit   AppTick3;
bit   AppTick4;
bit   AppTick5;
bit   AppTick1ms;

BOOL  gb12HourDisp;
BOOL  gb0_5s;
BOOL  gbUser_AdjClk;
BOOL  gbHalfSecond;
BOOL  gbTestMode;
BOOL  gbSnoozeEnable;
BOOL  gbPowerOn;
BOOL  gbSleepEnable;

uint8_t Flag_DispStatus;

/*****************************/
/*变量定义variable definition*/
/*****************************/
uint8_t  idata cntAppTick;
bit		 	   gbHalfSecond;
uint8_t  idata gRTC_Sec;//RTC数据 
uint8_t  idata gRTC_Sec_bk;
uint8_t  idata gRTC_Minute;
uint8_t  idata gRTC_Minute_bk;
uint8_t  idata gRTC_Hour;
uint8_t  idata gRTC_Hour_bk;
uint8_t  idata gRTC_Hour_bk_24;//计数24小时
uint8_t  idata gRTC_Week; //一周7天
uint8_t  idata Snooze_Hour;//贪睡小时时间
uint8_t  idata Snooze_Minute;//贪睡分钟时间
uint8_t  idata sysVolume;//系统音量
uint8_t  idata sys_Cmd;//命令
uint8_t  idata sys_Name;
uint16_t idata timeCnt_30Sec;//短按ALARM键缺人设置或不动作30s自动保存，30s计时

uint8_t  idata cntAlarm;
uint8_t  idata cntSleep;
uint8_t  idata sleepTimeSet;
uint8_t  idata cntNoFlash;
uint8_t  idata AlarmingType;//闹钟时开启还是关闭，用Alarm1_TypeDef.Alarm_OnOFF代替
uint8_t	 idata Alarm1Mode;//用Alarm1_TypeDef.Alarm_Mode代替了
uint8_t		   gZone;
uint8_t	 idata cnt0_5s;//通过这个变量的计数来对gb0_5s的状态连续取反，每次取反0.5s
uint32_t        cntDispStatus;

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
 * 函数功能：把显示状态清零
 * 返回值说明：
 * 创建日期：
 * 创建人：
 * 修改日期
 * 修改人：
 * 第N次修改：
 * 修改原因：
 * 备注：
 *******************************************************************************/
void ClearDisplayStatus(void)
{
	Flag_DispStatus = 0;
	cntDispStatus = 0;
}

 /*******************************************************************************
  * 函数原型：
  * 输入参数：
  * 输出参数：
  * 函数功能：睡眠唤醒之后清除相关标志位和计数什么的变量
  * 返回值说明：
  * 创建日期：
  * 创建人：
  * 修改日期
  * 修改人：
  * 第N次修改：
  * 修改原因：
  * 备注：
  *******************************************************************************/
void Clear_Sleep(void)
{
	cntSleep = 0;
	sleepTimeSet = 0;
	gbSleepEnable = 0;
}

  /*******************************************************************************
   * 函数原型：
   * 输入参数：
   * 输出参数：
   * 函数功能：退出显示状态
   * 返回值说明：
   * 创建日期：
   * 创建人：
   * 修改日期
   * 修改人：
   * 第N次修改：
   * 修改原因：
   * 备注：
   *******************************************************************************/
void DisplayStatusExit(void)
{
	if (cntDispStatus)
	{
		if (++cnt0_5s >= cDISP_DELAY__500ms)//10ms调用一次，计数到500ms就进入
		{
			cnt0_5s = 0;
			gb0_5s = ~gb0_5s;
		}
		if (--cntDispStatus == 0)
		{
			switch (Flag_DispStatus)
			{
				case DISP_CLK:
					break;
				case DISP_GET_MEN:
					SetDisplayState10s(DISP_RADIO);
					break;
				default:
					cntDispStatus = cDISP_DELAY__60ms;
					Flag_DispStatus = DISP_CLK;
					break;
			}
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
void Snooze_9Min(void)
{
	uint8_t cnt;
	Snooze_Hour = gRTC_Hour;//把现在RTC时间赋给贪睡时间这样再计数9分钟再与RTC时间对比
	Snooze_Minute = gRTC_Minute;
	for (cnt = 0; cnt < 9; cnt++)//这里之所以进行9次if判断
	{
		if (++Snooze_Minute >= 60)
		{
			Snooze_Minute = 0;
			if (++Snooze_Hour >= 24)
			{
				Snooze_Hour = 0;
			}
		}
	}
}

/*******************************************************************************
* 函数原型：
* 输入参数：
* 输出参数：
* 函数功能：闹钟响时按下SNOOZE(贪睡)按键，继续贪睡9分钟
* 返回值说明：
* 创建日期：
* 创建人：
* 修改日期
* 修改人：
* 第N次修改：
* 修改原因：
* 备注：
*******************************************************************************/
void SnoozeEnable(void)
{
	if (!gbSnoozeEnable)
	{
		if (cntAlarm)
		{
			//__enMute();
			gbPowerOn = 0;
			Snooze_9Min();
			SetDisplayState10s(DISP_CLK);
			//BuzzEventPorc(eAL_AL_IDLE);//这个函数还没有写呢
			gbSnoozeEnable = 1;//贪睡标志位置1，启动贪睡
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
		
		if(gRTC_Minute!=gRTC_Minute_bk)//分钟
		{
			gRTC_Minute_bk=gRTC_Minute;
			if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (gRTC_Hour == Alarm1_TypeDef.hour) && (gRTC_Minute == Alarm1_TypeDef.minute))
			{
				if(Alarm1_TypeDef.Alarm_WorkMode==ALARM_BT)
				{
					
				}
				else
				{

				}
			}
				
			if(gRTC_Hour!=gRTC_Hour_bk)//小时
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
	if (Time_Temp_TypeDef.Flag_Confirm_30Sec == 2)
	{
		timeCnt_30Sec++;
		if (timeCnt_30Sec >= 3000)//30s
		{
			Time_Temp_TypeDef.Flag_Confirm_30Sec = 0;
			FlagKSet_TypeDef = FLAG_KEYSET_OFF;
			timeCnt_30Sec = 0;
			gRTC_Hour   = Time_Temp_TypeDef.temp_RTC_Hour; //30s计时结束把设定的临时RTC时间付给一直在运行的RTC时间
			gRTC_Minute = Time_Temp_TypeDef.temp_RTC_Minute;
		}
	}
	else if (Alarm1_TypeDef.Flag_Confirm_30Sec == 2)
	{
		timeCnt_30Sec++;
		if (timeCnt_30Sec >= 3000)//30s
		{
			Alarm1_TypeDef.Flag_Confirm_30Sec = 0;
			FlagKSet_TypeDef = FLAG_KEYSET_OFF;
			timeCnt_30Sec = 0;
			Alarm1_TypeDef.hour   = Alarm1_TypeDef.tempHour;//30s计时结束把设定的闹钟时间赋给与RTC比对的闹钟变量
			Alarm1_TypeDef.minute = Alarm1_TypeDef.tempMinute;
			Alarm1_TypeDef.Flag_Again=1;
			cntDispStatus=0;
		}
	}
	//else
	//	timeCnt_30Sec = 0;
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
		if((--uart1_TX_Timeout)==0)//发送超时就清零发送标志位
			uart1_EnableSend=0;
		if((--uart1_RX_Timeout)==0)
			uart1_RX_Pointer=0;
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
	//WDT_init();     	// initialize Watch-dog timer
	PlayMode_TypeDef=PLAY_IN_TIME;//PLAY_JUST_POWER;//刚上电，模式设为刚上电模式
	LED_Brightness_TypeDef=LED_HIGH;//亮度默认为高
	Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP; //自己加的为闹钟响闹模式为beep模式，方便写程序，也防止使用者在设置闹钟
								//时没有选择模式，那就选择默认是beep模式
	Music_Mode_TypeDef = MUSIC_BT;
	sysVolume = 8;//默认系统音量为8级
	cntNoFlash = 0;
	gbUser_AdjClk = 1;
	gb12HourDisp = 1;
	gbHalfSecond = 1;
	gRTC_Sec = 0;
	gRTC_Minute = 0;
	gRTC_Hour = 0;
	gZone = 2;
//	Alarm1Mode = ALARM_NONE;
//	Alarm2Mode = ALARM_NONE;
//	AlarmingType = ALARM_OFF;

	gbPowerOn = 0;
	//WDT_clear();
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
			BlueMode_Handle();
		}
		if(AppTick2)
		{
			AppTick2=0;
			
		}
		if(AppTick3)
		{
			AppTick3=0;
			Display();
		}
		if(AppTick4)
		{
			AppTick4=0;
			DisplayStatusExit();
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










