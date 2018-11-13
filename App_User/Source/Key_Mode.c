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
FLAG_KEYSET_TypeDef  FlagKSet_TypeDef;//按键的功能设置标志
TIME_TEMP_TypeDef    Time_Temp_TypeDef;//设置时间时才把设置的时间先付给这个，然后确认了再赋值到gRTC_xx;

/****************************/
/*标志位定义flags definetion*/
/****************************/

/*****************************/
/*变量定义variable definition*/
/*****************************/
uint8_t  gbKeyPress;//按键按下
uint8_t  gbKeyNone; //没有按键按下
uint8_t  KeyValue;  //按键值
uint8_t  KeyEvent;  //按键事件
uint8_t  cntKeyLoop;//计数按键循环，短按，长按，超长按的按下时间
uint8_t  cntKeylong;
uint8_t  KeyCurValueBK;//现在按键备份
uint8_t  KeyCurValue;//按键现在值
uint8_t  KeyLastValue;//按键上一次的值

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
 * 备注："P1=0x2F(0010_1111)"先赋值给P1口，P15为1，P14为0，输入端(P10-P13)为1，
 * 然后再读P1口电平(P1&0x0F)，并把高四位都清0，假如这时候P10被按下，那读到的P1
 * 口电平为(P1&0x0f)为0x0E(0000_1110),然后与0x0F(0000_1111)异或得到0x01(0000_0001),
 * 
 *******************************************************************************/
uint8_t  Matrix_Buttons(void)
{
	uint8_t  readData1,readData2;
	uint8_t  keyValue;
	keyValue=0;//如果没有按键按下就是返回0
	 
	/*******************************************************************************
	*功能："P1=0x2F(0010_1111)"先赋值给P1口，P15为1，P14为0，输入端(P10-P13)为1，然
	* 后再读P1口电平(P1&0x0F)，并把高四位都清0(P1&0x0F，假如这时候P10被按下，那读到
	* 的P1口电平为0x0E(0000_1110),然后与0x0F(0000_1111)异或得到0x01(0000_0001),
	* readData1的范围为1、2、4、8，keyValue的范围为1~9,9是组合键。
	*******************************************************************************/
	P1=0x2F;			
	readData1=(P1&0x0F)^0x0F;
	switch(readData1)
	{
		case 1:
			keyValue=1; //K_SNOOZE_DIMMER
			break;
		case 2:
			keyValue=2; //VOL+
			break;
		case 4:
			keyValue=3; //K_PLAY_PAUSE
			break;
		case 8:
			keyValue=4; //NEXT
			break;
		default:
			break;
	}
	/*******************************************************************************
	*功能："P1=0x1F(0001_1111)"先赋值给P1口，P15为0，P14为1，输入端(P10-P13)为1，然
	* 后再读P1口电平(P1&0x0F)，并把高四位都清0(P1&0x0F，假如这时候P11被按下，那读到
	* 的P1口电平为0x0D(0000_1101),然后与0x0F(0000_1111)异或得到0x02(0000_0010),
	* readData2的范围为1、2、4、8，keyValue的范围为1~9，9是组合键。
	*******************************************************************************/
	P1=0x1F;
	readData2=(P1&0x0F)^0x0F;
	switch(readData2)
	{
		case 1:
			keyValue=5; //ALARM
			if (keyValue == 1)//为1说明刚才alarm键被按下，因为每次调用这个函数都会初始化
			{				  //keyValue，所以不会是上次调用函数留下的值
				keyValue = 9;  //K_AL_SNOOZE
			}
			else if (keyValue == 1)
				keyValue = 10; //K_AL_VOLINC,
			break;
		case 2:
			keyValue=6; //VOL-
			break;
		case 4:
			keyValue=7; //BT
			break;
		case 8:
			keyValue=8; //PREV
			break;
		case 0x0C:
			keyValue = 11; //K_AL_VOLDEC,
		default:
			break;
	}
	 
	return keyValue;
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
uint8_t GetKeyValue(void) 
{
	uint8_t  keyNum;
	keyNum=Matrix_Buttons();
	return keyNum; //返回按键
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
void KeyEventPorc(uint8_t KeyTmp) //被调用时接收的是GetKeyValue()的返回值  一般固定，不更改
{
	gbKeyPress=0;
	if(KeyCurValue!=KeyTmp) //这个if语句是去抖，会被执行两次，第三次进来时直接跳过
	{//KeyTmp为临时值，
		if(KeyCurValueBK!=KeyTmp)
			KeyCurValueBK=KeyTmp;
		else //第二次进来时执行这一条
			KeyCurValue=KeyTmp; //
		return;
	}
	if(KeyCurValue==KeyLastValue)
	{
		if((KeyLastValue==0) || (cntKeyLoop==0))
			return;
		if(--cntKeyLoop==0) //这个在第二次进KeyEventPorc()函数（第一次进“if(KeyCurValue==KeyLastValue)”之前）时被下面赋值为5
		{ //cntKeyLoop为5就是50ms时间
			KeyValue=KeyLastValue; //防抖之后把确定的按键赋值给KeyValue
			if(gbKeyNone==0)
				gbKeyPress=1;
			switch(KeyEvent)
			{
				case 0:
					KeyEvent=1;
					KeyValue |= K_D;
					cntKeyLoop=cKEY_HOLD;
					break;
				case 1:
					KeyEvent=2;
					KeyValue |= K_H;
					cntKeyLoop=cKEY_RATE_VOL;
					break;
					case 2:
				case 3:
					KeyEvent=3;
					KeyValue |= K_R;
					cntKeyLoop=cKEY_RATE_VOL;
					if(cntKeylong<250)
						cntKeylong++;
					break;
			}
		}
	}
	else
	{
		if(KeyLastValue)
		{
			KeyValue=KeyLastValue;
			if(gbKeyNone==0)
				gbKeyPress=1;
			switch(KeyEvent)
			{
				case 1:KeyValue |= K_U; break;
				case 2:KeyValue |= K_LU;break;
				case 3:KeyValue |= K_LU;break;
			}
			KeyEvent=0;
		}
		else
		{
			gbKeyNone=0;
			cntKeylong=0;
		}
		cntKeyLoop=cKEY_CLICK;
		KeyLastValue=KeyCurValue;
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
void KeyScan(void) //被主函数调用
{
	KeyEventPorc(GetKeyValue());
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
 * 备注：2.、长按“TIME”键2S，小时字符闪烁，短按“VOL-/PREV”键，小时递减，长按
 * “VOL-/PREV”键，小时快速递减；短按“VOL+/NEXT”键，小时递增，长按“VOL+/NEXT”键，
 * 小时快速递增。
 * 3、短按“TIME”键，分字符闪烁，短按“VOL-/PREV”键，分位数递减，长按“VOL-/PREV”键，
 * 分位数快速递减；短按“VOL+/NEXT”键，分位数递增，长按“VOL+/NEXT”键，分位数快速递
 * 增。
 * 4、在走时模式下，短按“TIME/DIM”键，调整显示亮度，可循环调整高、中、低亮（默认
 * 为高亮）
 *******************************************************************************/
void KeyComMsg(void) 
{
	if(gbKeyPress)
	{ 
		//Flag_data_bk=1;//数据改变时备份
	   	switch(KeyValue)
		{
			case KU(K_SNOOZE_DIMMER)://短按
			{//Alarm_Ring_Run
				if (Alarm1_TypeDef.Alarm_Ring_Run == ALARM_RING_RUN_ON)
				{
					Alarm1_TypeDef.Alarm_Snooze = ALARM_SNOOZE_ON;//进入贪睡模式，为9分钟
				}
				else//正常走时模式下，短按SNOOZE键，调节LED平亮度，可循环调节高、中、低亮度(默认为高)
				{
					LED_Brightness_TypeDef--;
					if (LED_Brightness_TypeDef == LED_TURN_OFF)//三档循环
						LED_Brightness_TypeDef = LED_HIGH;
				}
				break;
			}
			case KH(K_SNOOZE_DIMMER)://长按
			{
				
				break;
			}
			case KU(K_VOLINC): //短按//音量加 
			case KR(K_VOLINC): //长按//音量加
			{
				//长按“VOL+/NEXT”键，小时快速递增。
				//长按“VOL+/NEXT”键，分钟位数快速递增。
				if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Hour < 12)
					{
						Time_Temp_TypeDef.temp_RTC_Hour++;
					}
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Minute < 59)
					{
						Time_Temp_TypeDef.temp_RTC_Minute++;
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempHour < 12)
					{
						Alarm1_TypeDef.tempHour++;
					}
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempMinute < 59)
					{
						Alarm1_TypeDef.tempMinute++;
					}
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_ALWORKMODE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.AlarmWorkMode == ALARM_BEEP)
					{
						Alarm1_TypeDef.AlarmWorkMode = ALARM_BT;
					}
					else
					{
						Alarm1_TypeDef.AlarmWorkMode = ALARM_BEEP;
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else//在蓝牙或TF状态下，音量功能
				{
					if (sys_Volume < 15)
					{
						sys_Volume++;
					}
				}

				break;
			}
			case KU(K_PLAY_PAUSE): //短按//短按分钟字符闪烁，
			{					
				if (Music_Mode_TypeDef > MUSIC_OFF)//在蓝牙和TF卡模式
				{
					Ctrl_Com_TypeDef = CTRL_NEXT;
				}
				break;
			}
			case KR(K_PLAY_PAUSE): //计时
			{
				
				break;
			}
			case KU(K_NEXT): //短按
			case KR(K_NEXT): //长按
			{
				
				break;
			}
			case KU(K_ALARM): //短按//闹钟
			{
				/* 设置RTC时间 */
				if (FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR)
				{
					//在长按ALARM键和SNOOZE键进入设置时间模式-小时设置，在短按ALARM键设置分钟时间
					FlagKSet_TypeDef = FLAG_KEYSET_SETTIME_MINUTE;
					Time_Temp_TypeDef.Flag_Confirm_30Sec=2;//短按ALARM键确认设置或不动作30s自动保存，(为1是确
														   //认闹钟设置标志位),为2是30s计时标志位，
					timeCnt_30Sec = 0;//校准，以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
				}
				else if (FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE)
				{
					//在长按ALARM键和SNOOZE键进入设置时间模式-小时设置，在短按ALARM键设置分钟时间
					//在短按ALRM键确认时间设置，或者在进入分钟设置时间之后不动作30s即自动保存
					FlagKSet_TypeDef = FLAG_KEYSET_OFF;
					gRTC_Hour   = Time_Temp_TypeDef.temp_RTC_Hour;
					gRTC_Minute = Time_Temp_TypeDef.temp_RTC_Minute;
					//Time_Temp_TypeDef.Flag_Confirm_30Sec = 1;//短按ALARM键确认设置或不动作30s自动保存，(为1是确
															 //认闹钟设置标志位),为2是30s计时标志位，
				}

				/* 设置闹钟时间 */
				if ((PlayMode_TypeDef == PLAY_IN_TIME) && (FlagKSet_TypeDef == FLAG_KEYSET_OFF))
				{
					//只有在走时和没有其他设置模式下(比如时间设置，因为短按ALARM有其他功能)，才会进入此if功能
					//设置脑中时间并开启闹钟
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_HOUR;
					Alarm1_TypeDef.Alarm_OnOff = ALARM_ON;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//第二次开启闹钟，并且不修改脑中时间，不动作30s自动保
														  //存，(为1是确认闹钟设置标志位)为2是30s计时标志位，
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))  
				{
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_MINUTE;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 0;//第二次开启闹钟，并且修改脑中时间，把不动作自动保存关闭
					//timeCnt_30Sec = 0;					  //并校准时间为0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_ALWORKMODE;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//短按ALARM键确认设置或不动作30s自动保存，(为1
														  //是确认闹钟设置标志位)为2是30s计时标志位，
					timeCnt_30Sec = 0;//校准，以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
				}

				break;
			}
			case KH(K_ALARM): //长按//闹钟
			{
				
				break;
			}
			case KU(K_VOLDEC): //短按//音量减
			case KR(K_VOLDEC): //长按//音量减
			{
				//长按“VOL-/PREV”键，小时快速递减；
				//长按“VOL-/PREV”键，分钟位数快速递减；
				if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Hour > 0)
					{
						Time_Temp_TypeDef.temp_RTC_Hour--;
					}
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Minute > 0)
					{
						Time_Temp_TypeDef.temp_RTC_Minute--;
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempHour > 0)
					{
						Alarm1_TypeDef.tempHour--;
					}
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempMinute > 0)
					{
						Alarm1_TypeDef.tempMinute--;
					}
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_ALWORKMODE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.AlarmWorkMode == ALARM_BEEP)
					{
						Alarm1_TypeDef.AlarmWorkMode = ALARM_BT;
					}
					else
					{
						Alarm1_TypeDef.AlarmWorkMode = ALARM_BEEP;
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else//在蓝牙或TF状态下，音量功能
				{
					if (sys_Volume > 0)
					{
						sys_Volume--;
					}
				}

				break;
			}
			case KU(K_BT): //短按
			{
				//短按“VOL-/PREV”键，小时递减，
				//短按“VOL-/PREV”键，分钟位数递减，
				if (Music_Mode_TypeDef != MUSIC_BT)
				{
					Music_Mode_TypeDef = MUSIC_BT;
				}
				break;
			}
			case KH(K_BT): //长按
			{
				//长按“VOL-/PREV”键，小时快速递减；
				//长按“VOL-/PREV”键，分钟位数快速递减；
				break;
			}
			case KU(K_PREV): //短按
			case KR(K_PREV): //长按
			{
				if (Music_Mode_TypeDef > MUSIC_OFF)//在蓝牙和TF卡模式
				{
					Ctrl_Com_TypeDef = CTRL_PREV;
				}
				break;
			}
			case KU(K_AL_SNOOZE): //短按
			{

				break;
			}
			case KR(K_AL_SNOOZE): //长按
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if (cntKeylong == 10)//2s
					{
						//长按ALARM和SNOOZE键2s进入时间设置模式-小事设置
						FlagKSet_TypeDef = FLAG_KEYSET_SETTIME_HOUR;
					}
				}
				break;
			}
			case KU(K_AL_VOLINC): //短按
			case KR(K_AL_VOLINC): //长按
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if (cntKeylong == 10)//2s
						gRTC_Hour = gRTC_Hour + 1;//组合键-闹钟和音量加-同时2s-RTC时间加一小时，表示开启夏令时
				}
				break;
			}
			case KU(K_AL_VOLDEC): //短按
			case KR(K_AL_VOLDEC): //长按
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if (cntKeylong == 10)//2s
						gRTC_Hour = gRTC_Hour - 1;//组合键-闹钟和音量减-同时2s-RTC时间减一小时，表示关闭夏令时
				}
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















