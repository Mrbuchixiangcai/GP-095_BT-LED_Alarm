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
bit     AppTick0;
bit     AppTick1;
bit     AppTick2;
bit     AppTick3;
bit     AppTick4;
bit     AppTick5;
bit     AppTick1ms;
uint8_t Flag_DaylightSaving;//是否设置夏令时标志，这样，如果加一个小时只能加一次，
						    //1为加了一个小时，2为减了一个小时
uint8_t Flag_Alarm1_IQ_BTOrBEEp;//闹钟1响应时先查询是蓝牙有没有再播放，如果在播放并且闹钟影响
								//工作模式为蓝牙播放，就把闹钟工作模式转为beep

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
uint16_t       cntDispStatus;
uint8_t        cntJustPower_AllLED_2s;//刚上电全部LED显示2s

uint16_t idata cntBT_Connect_30s;//闹钟响时蓝牙模式下如果没有连接到蓝牙就计数30s
uint8_t  idata cntAlarm_Runing_60Min;//闹钟到时响60分钟；
uint32_t idata cntSnooze_9Min;//
uint8_t  idata cntBeep;//闹钟响时并且为beep模式，就响1s，关0.5s
uint8_t  idata cntAlarm1_IQ_BTOrBEEp;//闹钟1响应时先查询是蓝牙有没有再播放，如果在播放并且闹钟影响
								//工作模式为蓝牙播放，就把闹钟工作模式转为beep

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
//	uint8_t cnt;
//	Snooze_Hour = gRTC_Hour;//把现在RTC时间赋给贪睡时间这样再计数9分钟再与RTC时间对比
//	Snooze_Minute = gRTC_Minute;
//	for (cnt = 0; cnt < 9; cnt++)//这里之所以进行9次if判断
//	{
//		if (++Snooze_Minute >= 60)
//		{
//			Snooze_Minute = 0;
//			if (++Snooze_Hour >= 24)
//			{
//				Snooze_Hour = 0;
//			}
//		}
//	}
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
* 函数功能：刚上电全部LED显示2s，这里是把_SET_xx(Flag_SET_xx)中的Flag_SET_xx置一，
*			在定时器三种调用时就会亮，并且亮度为最高
* 返回值说明：
* 创建日期：
* 创建人：
* 修改日期
* 修改人：
* 第N次修改：
* 修改原因：
* 备注：
*******************************************************************************/
void JustPower_AllLED_Flag(void)
{
	LED_Brightness_TypeDef = LED_HIGH;
	Flag_SET_1B=1;
	Flag_SET_1C=1;
	Flag_SET_2A=1;
	Flag_SET_2B=1;
	Flag_SET_2C=1;
	Flag_SET_2D=1;
	Flag_SET_2E=1;
	Flag_SET_2F=1;
	Flag_SET_2G=1;
	Flag_SET_3A=1;
	Flag_SET_3B=1;
	Flag_SET_3C=1;
	Flag_SET_3D=1;
	Flag_SET_3E=1;
	Flag_SET_3F=1;
	Flag_SET_3G=1;
	Flag_SET_4A=1;
	Flag_SET_4B=1;
	Flag_SET_4C=1;
	Flag_SET_4D=1;
	Flag_SET_4E=1;
	Flag_SET_4F=1;
	Flag_SET_4G=1;
	Flag_SET_APM=1;
	Flag_SET_AL=1;
	Flag_SET_COL1=1;
	Flag_SET_COL2=1;
	Flag_SET_BT_BLUE=1;
	Flag_SET_BT_RED=1;
}

/*******************************************************************************
* 函数原型：
* 输入参数：
* 输出参数：
* 函数功能：刚上电全部LED显示2s计数,如果计数完毕就清除标志位，退出while(cntJustPower_AllLED_2s)
* 返回值说明：
* 创建日期：
* 创建人：
* 修改日期
* 修改人：
* 第N次修改：
* 修改原因：
* 备注：
*******************************************************************************/
void JustPower_AllLED_2s(void)
{
	cntJustPower_AllLED_2s--;
	if(cntJustPower_AllLED_2s==0)
	{

		WT_init();//开启WT中断
		Flag_SET_1B=0;
		Flag_SET_1C=0;
		Flag_SET_2A=0;
		Flag_SET_2B=0;
		Flag_SET_2C=0;
		Flag_SET_2D=0;
		Flag_SET_2E=0;
		Flag_SET_2F=0;
		Flag_SET_2G=0;
		Flag_SET_3A=0;
		Flag_SET_3B=0;
		Flag_SET_3C=0;
		Flag_SET_3D=0;
		Flag_SET_3E=0;
		Flag_SET_3F=0;
		Flag_SET_3G=0;
		Flag_SET_4A=0;
		Flag_SET_4B=0;
		Flag_SET_4C=0;
		Flag_SET_4D=0;
		Flag_SET_4E=0;
		Flag_SET_4F=0;
		Flag_SET_4G=0;
		Flag_SET_APM=0;
		Flag_SET_AL=0;
		Flag_SET_COL1=0;
		Flag_SET_COL2=0;
		Flag_SET_BT_BLUE=0;
	}
}

/*******************************************************************************
* 函数原型：
* 输入参数：
* 输出参数：
* 函数功能：刚上电全部LED显示2s计数
* 返回值说明：
* 创建日期：
* 创建人：
* 修改日期
* 修改人：
* 第N次修改：
* 修改原因：
* 备注：
*******************************************************************************/
void JustPower_AllLED(void)
{
	WT_Def_Init();//先关闭WT中断，不让RTC变量有所变化
	if(AppTick1ms)
	{
		AppTick1ms=0;
	}
	if(AppTick0)
	{
		//CheckDC();
		AppTick0=0;
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
		JustPower_AllLED_Flag();
	}
	if(AppTick5)
	{
		AppTick5=0;
		JustPower_AllLED_2s();
	}
	WDT_clear();
}


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
	/*******************************************************************************
	 *功能：
	 *这里是1s进来一次
	 *******************************************************************************/
	if(gRTC_Sec!=gRTC_Sec_bk)
	{
		gRTC_Sec_bk=gRTC_Sec;
		/*******************************************************************************
		 *功能：如果闹钟时间到先判断是不是蓝牙正在播放，并且判断闹钟响应工作模式是不是
		 *		蓝牙模式，如果是蓝牙模式，并且蓝牙正在播放(Flag_Alarm1_IQ_BTOrBEEp就为2)
		 *		就转为beep模式，并把正在播放的蓝牙关掉。如果没有正在播放，就回连蓝牙，开
		 *		启闹钟，如果30s内没有连接到蓝牙，就转为beep。因为从Flag_Alarm1_IQ_BTOrBEEp
		 *		赋值为1，再重新执行到这里是过去了1s，串口发送查询再接受时间是够得，所以
		 *		如果这里Flag_Alarm1_IQ_BTOrBEEp依然为1那就是蓝牙没有在播放，就开启蓝牙回连
		 *这里是1s进来一次
		 *******************************************************************************/
		if(Flag_Alarm1_IQ_BTOrBEEp==2)//闹钟工作模式为蓝牙，并且蓝牙在播放
		{
			Alarm1_TypeDef.Alarm_RingRun=ALARM_RING_RUN_ON;
			Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP;
			Flag_Alarm1_IQ_BTOrBEEp=0;//清掉标志，为下次做准备
			bt_cmd=BT_PAUSE;//把蓝牙的播放暂停
		}
		else if(Flag_Alarm1_IQ_BTOrBEEp==1)//闹钟工作模式为蓝牙，蓝牙没有在播放
		{
			Alarm1_TypeDef.Alarm_RingRun=ALARM_RING_RUN_ON;
			Flag_Alarm1_IQ_BTOrBEEp=0;//清掉标志，为下次做准备
			//这里不用发送回连，下面有
		}
		
		if(gRTC_Minute!=gRTC_Minute_bk)//分钟
		{
			gRTC_Minute_bk=gRTC_Minute;
			/*******************************************************************************
			 *功能：闹钟定时检测是否开启，并且是否时间到
			 *这里是1min进来一次
			 *******************************************************************************/
			if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (gRTC_Hour == Alarm1_TypeDef.hour) && (gRTC_Minute == Alarm1_TypeDef.minute))
			{
				if(Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_OFF)
				{
					//Alarm1_TypeDef.Alarm_RingRun=ALARM_RING_RUN_ON;
					if(Alarm1_TypeDef.Alarm_WorkMode==ALARM_BT)
					{
						bt_cmd=BT_IQ;
						Flag_Alarm1_IQ_BTOrBEEp=1;
					}
					
				}
			}
			/*******************************************************************************
			 *功能：闹钟总的响应时间(包括贪睡)为60分，闹钟一响就开始计时
			 *******************************************************************************/
			if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON))
			{
				cntAlarm_Runing_60Min++;
				if(cntAlarm_Runing_60Min>=60)
				{
					Alarm1_PowerOFF();
				}
				if(Alarm1_TypeDef.Alarm_Snooze == ALARM_SNOOZE_ON)//如果是贪睡模式
				{
					cntSnooze_9Min++;
					if(cntSnooze_9Min>=9)
					{
						cntSnooze_9Min=0;
						Alarm1_TypeDef.Alarm_Snooze = ALARM_SNOOZE_OFF;//贪睡时间到，关闭贪睡模式
					}
				}
			}
			
			/*******************************************************************************
			 *功能：
			 *这里是1hour进来一次
			 *******************************************************************************/
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
	/*******************************************************************************
	 *功能：闹钟开启，并且已经响应
	 *这里是10ms进来一次
	 *******************************************************************************/
	if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON))
	{
		if(Alarm1_TypeDef.Alarm_Snooze == ALARM_SNOOZE_OFF)//如果不等于贪睡模式
		{
			if(Alarm1_TypeDef.Alarm_WorkMode==ALARM_BT)//闹钟工作模式为蓝牙
			{
				if(Flag_BT_Connect==1)//说明蓝牙连接成功
				{
					//if(!Flag_BT_Play)
					if(Flag_BT_Play==0)
					{
						Flag_BT_Play=1;
						cntBT_Connect_30s=0;
						bt_cmd=BT_PLAY;
					}
					else if(Flag_BT_Play==1)
					{
						//Flag_BT_Play=2;
						cntBT_Connect_30s++;
						if((cntBT_Connect_30s%100)==0)//1s发送一次回连，第一次为0时发送要在"cntBT_Connect_30s++;"前面
							bt_cmd=BT_PLAY;
						
						//bt_cmd=BT_PLAY;
					}
				}
				else
				{
					if((cntBT_Connect_30s%100)==0)//1s发送一次回连，第一次为0时发送要在"cntBT_Connect_30s++;"前面
						bt_cmd=BT_LINK_BACK;	 //不然"++"之后就为1，发送不了，要等到100才能发送了
					cntBT_Connect_30s++;
					Flag_BT_Play=0;
					if(cntBT_Connect_30s>=3000)//30s时间到
					{
						cntBT_Connect_30s=0;
						if(Flag_BT_Connect==0)
						{
							Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP;//切换到beep模式
						}
					}
				}
			}
			else
			{
				if(Alarm1_TypeDef.Alarm_WorkMode==ALARM_BEEP)//闹钟工作模式为beep
				{
					//BUZ_OnOff(1);
					__DE_MUTE();
					cntBeep++;
					if(cntBeep<40)//0.3s
						BUZ_OnOff(1);
					else if((cntBeep>=40) && (cntBeep<80))//0.5s-0.7s
						BUZ_OnOff(0);
					else
						cntBeep=0;
				}
			}
		}
		else//如果等于贪睡模式
		{
			BUZ_OnOff(0);
			__EN_MUTE();
			if(Flag_BT_Play)
			{
				Flag_BT_Play=0;
				bt_cmd=BT_PAUSE;//如果是蓝牙模式就暂停播放
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
			Flag_DispStatus=0;
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
			Flag_DispStatus=0;
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
uint16_t cnt_num;
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
	{
		cntAppTick=0;
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
void PowerON_Reset(void)
{
	//WDT_init();     	// initialize Watch-dog timer
	PlayMode_TypeDef=PLAY_IN_TIME;//PLAY_JUST_POWER;//刚上电，模式设为刚上电模式
	LED_Brightness_TypeDef=LED_HIGH;//亮度默认为高
	Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP; //自己加的为闹钟响闹模式为beep模式，方便写程序，也防止使用者在设置闹钟
											//时没有选择模式，那就选择默认是beep模式
	Music_Mode_TypeDef = MUSIC_OFF;
	__BT_CLR_POWER();
	cntJustPower_AllLED_2s=200;//刚上电全部LED显示2s
	sysVolume = 8;//默认系统音量为8级
	cntNoFlash = 0;
	gbUser_AdjClk = 1;
	gb12HourDisp = 1;
	gbHalfSecond = 1;
	gRTC_Sec = 0;
	gRTC_Minute = 0;
	gRTC_Hour = 0;
	gZone = 2;
	Flag_DaylightSaving=0;//夏令时清零，
//	Alarm1Mode = ALARM_NONE;
//	Alarm2Mode = ALARM_NONE;
//	AlarmingType = ALARM_OFF;

	gbPowerOn = 0;
//	Alarm1_TypeDef.Alarm_OnOff = ALARM_ON;
//	Alarm1_TypeDef.hour=0;
//	Alarm1_TypeDef.minute=40;
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
	while(cntJustPower_AllLED_2s)
	{
		
		JustPower_AllLED();
	}
	
	while(1)
	{
		//CheckDC();
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
		if((AppTick1) || (AppTick2))
		{
			AppTick1=0;
			AppTick2=0;
			BlueMode_Handle();
			
		}
		if(AppTick3)
		{
			AppTick3=0;
			Display();
			//BUZ_OnOff(1);
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
			TF_Check();
		}
		WDT_clear();	
	}
}










