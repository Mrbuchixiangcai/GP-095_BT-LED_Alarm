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
  uint8_t tmp1=0;	
  uint8_t tmp2=0;		
  if((P1&0x0F)!=0x0F)	
  {
   P1|=0X20;  
   P1|=0X20; 
   P1|=0X20; 
   P1|=0X20;
   tmp1=P1&0x0F;	  
   P1&=~0X30; 
   P1|=0X10;  
   P1|=0X10; 
   P1|=0X10;	
   P1|=0X10; 
   tmp2=P1&0x0F;		  
  }
  P1&=~0X30;
  if((tmp1==0x0E)&&(tmp2==0x0F))
  {
	return 1; //K_SNOOZE_DIMMER
  }
  if((tmp1==0x0D)&&(tmp2==0x0F))
  {
	return 2; //K_VOLINC
  }
  if((tmp1==0x0B)&&(tmp2==0x0F))
  {
	return 3; //K_PLAY_PAUSE
  }
  if((tmp1==0x07)&&(tmp2==0x0F))
  {
	return 4; //K_NEXT
  }
  if((tmp1==0x0F)&&(tmp2==0x0E))
  {
	return 5; //K_ALARM
  }
  if((tmp1==0x0F)&&(tmp2==0x0D))
  {
	return 6; //K_VOLDEC
  }
  if((tmp1==0x0F)&&(tmp2==0x0B))
  {
	return 7; //K_BT
  }
  if((tmp1==0x0F)&&(tmp2==0x07))
  {
	return 8; //K_PREV
  }
  if((tmp1==0x0E)&&(tmp2==0x0E))
  {
	return 9; //K_AL_SNOOZE
  }
  if((tmp1==0x0D)&&(tmp2==0x0E))
  {
	return 10; //K_AL_VOLINC
  }
  if((tmp1==0x0F)&&(tmp2==0x0C))
  {
	return 11; //K_AL_VOLDEC
  }
	return 0;   
//	uint8_t  readData1=0;
//	uint8_t  readData2=0;
//	uint8_t  temp_ReakData1=0;
//	uint8_t  temp_ReakData2=0;
//	uint8_t  scanKeyValue;
//	scanKeyValue=0;//如果没有按键按下就是返回0
//	 
//	/*******************************************************************************
//	*功能："P1=0x2F(0010_1111)"先赋值给P1口，P15为1，P14为0，输入端(P10-P13)为1，然
//	* 后再读P1口电平(P1&0x0F)，并把高四位都清0(P1&0x0F，假如这时候P10被按下，那读到
//	* 的P1口电平为0x0E(0000_1110),然后与0x0F(0000_1111)异或得到0x01(0000_0001),
//	* readData1的范围为1、2、4、8，scanKeyValue的范围为1~9,9是组合键。
////	*******************************************************************************/
////	P1=0x2F;			
////	readData1=(P1&0x0F)^0x0F;
//	if((P1&0x0F)!=0x0F)
//	{
//		readData1=P1;
//		P1=0x2F;
//		temp_ReakData1=(P1&0x2F)^0x0F;
//		switch(temp_ReakData1)
//		{
//			case 0x21:
//				scanKeyValue=1; //K_SNOOZE_DIMMER
//				break;
//			case 0x22:
//				scanKeyValue=2; //VOL+(实际VOL-)
//				break;
//			case 0x24:
//				scanKeyValue=3; //K_PLAY_PAUSE
//				break;
//			case 0x28:
//				scanKeyValue=4; //NEXT
//				break;
//			default:
//				break;
//		}
//	}
//	/*******************************************************************************
//	*功能："P1=0x1F(0001_1111)"先赋值给P1口，P15为0，P14为1，输入端(P10-P13)为1，然
//	* 后再读P1口电平(P1&0x0F)，并把高四位都清0(P1&0x0F，假如这时候P11被按下，那读到
//	* 的P1口电平为0x0D(0000_1101),然后与0x0F(0000_1111)异或得到0x02(0000_0010),
//	* readData2的范围为1、2、4、8，scanKeyValue的范围为1~9，9是组合键。
//	*******************************************************************************/
////	P1=0x1F;
////	readData2=(P1&0x0F)^0x0F;
//	if((P1&0x0F)!=0x0F)
//	{
//		readData2=P1;
//		P1=0x1F;
//		temp_ReakData2=(P1&0x1F)^0x0F;
//		switch(temp_ReakData2)
//		{
//			case 0x11:
////				if (scanKeyValue == 1)//为1说明刚才alarm键被按下，因为每次调用这个函数都会初始化
////				{				  	  //keyValue，所以不会是上次调用函数留下的值
////					scanKeyValue = 9; //K_AL_SNOOZE//ALARM+SNOOZE
////				}
////				else if (scanKeyValue == 2)
////					scanKeyValue = 10;//K_AL_VOLINC,//ALARM+VOLINC
////				else
//					scanKeyValue=5; //ALARM
//				break;
//			case 0x12:
//				scanKeyValue=6; //VOL-
//				break;
//			case 0x14:
//				scanKeyValue=7; //BT
//				break;
//			case 0x18:
//				scanKeyValue=8; //PREV
//				break;
//			case 0x0C:
//				scanKeyValue = 11; //K_AL_VOLDEC,
//			default:
//				break;
//		}
//	}
//	readData1=0;
//	readData2=0;
//	P1=0x0F;
//	return scanKeyValue;
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
		/**************************************************************
		*功能：如果闹钟响应，按下出snooze的按键都关闭闹钟
		***************************************************************/
		if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON))
		{
			
			if((KeyValue & 0x0F) != K_SNOOZE_DIMMER)
			{
				Alarm1_PowerOFF();
			}
		}
	   	switch(KeyValue)
		{
			/*******************************************************************************
			*功能：贪睡按键
			*
			*******************************************************************************/
			case KU(K_SNOOZE_DIMMER)://短按
			{//Alarm_Ring_Run
				if (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON)
				{
					Alarm1_TypeDef.Alarm_Snooze = ALARM_SNOOZE_ON;//进入贪睡模式，为9分钟
					//Flag_BT_Play=0;//短按之后进入贪睡，并把播放标志清掉，因为在"Compare_1MinutePorc()"
								   //里面有个判断这个标志位，发送暂停命令的
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
			/*******************************************************************************
			*功能：音量加
			*
			*******************************************************************************/
			case KU(K_VOLINC): //短按//音量加 
			case KR(K_VOLINC): //长按//音量加
			{
				//长按“VOL+”键，小时快速递增。
				//长按“VOL+”键，分钟位数快速递增。
				if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Hour <= 24)
					{
						Time_Temp_TypeDef.temp_RTC_Hour++;
					}
					else
					{
						if (Time_Temp_TypeDef.temp_RTC_Hour > 24)
						{
							Time_Temp_TypeDef.temp_RTC_Hour=0;
						}
					}
					timeCnt_30Sec = 0;
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Minute <= 59)
					{
						Time_Temp_TypeDef.temp_RTC_Minute++;
					}
					else
					{
						if (Time_Temp_TypeDef.temp_RTC_Minute > 59)
						{
							Time_Temp_TypeDef.temp_RTC_Minute=0;
						}
					}
					gRTC_Minute=0;
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempHour <= 24)
					{
						Alarm1_TypeDef.tempHour++;
					}
					else
					{
						if (Alarm1_TypeDef.tempHour > 24)
						{
							Alarm1_TypeDef.tempHour=0;
						}
					}
					timeCnt_30Sec = 0;
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempMinute <= 59)
					{
						Alarm1_TypeDef.tempMinute++;
					}
					else
					{
						if (Alarm1_TypeDef.tempMinute > 59)
						{
							Alarm1_TypeDef.tempMinute=0;
						}
					}
					timeCnt_30Sec = 0;
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_ALWORKMODE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.Alarm_WorkMode == ALARM_BEEP)
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BT;
					}
					else
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BEEP;
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else//在蓝牙或TF状态下，音量功能
				{
					if (sysVolume < 15)
					{
						sysVolume++;
					}
				}
				break;
			}
			/*******************************************************************************
			*功能：暂停播放
			*
			*******************************************************************************/
			case KU(K_PLAY_PAUSE): //短按
			{					
				/* 这部分是在蓝牙和TF卡模式下短按播放/暂停 */
//				if (Music_Mode_TypeDef == MUSIC_BT)//在蓝牙模式
//				{
//					if(!Flag_BT_Play)
//					{
//						Flag_BT_Play=1;//如果是暂停状态就播放，并置1
//						Flag_BT_TF_Play=0;//清楚TF卡播放标志
//						bt_cmd=BT_PLAY;
//					}
//					else
//					{
//						Flag_BT_Play=0;//如果是播放状态就暂停，并置0
//						Flag_BT_TF_Play=0;//清楚TF卡播放标志
//						bt_cmd=BT_PAUSE;
//					}
//				}
//				else if(Music_Mode_TypeDef == MUSIC_TF)//在TF卡模式
//				{
//					if(!Flag_BT_TF_Play)
//					{
//						Flag_BT_TF_Play=1;//如果是暂停状态就播放，并置1
//						Flag_BT_Play=0;
//						bt_cmd=BT_PLAY;
//					}
//					else
//					{
//						Flag_BT_TF_Play=0;//如果是播放状态就暂停，并置0
//						Flag_BT_Play=0;
//						bt_cmd=BT_PAUSE;
//					}
//				}
				bt_cmd=BT_PLAY_PAUSE;
				break;
			}
			case KR(K_PLAY_PAUSE): //计时
			{
				if (cntKeylong == 10)//2s
					bt_cmd=BT_IQ;
				break;
			}
			/*******************************************************************************
			*功能：下一曲
			*
			*******************************************************************************/
			case KU(K_NEXT): //短按
			{
				if (Music_Mode_TypeDef > MUSIC_OFF)//在蓝牙和TF卡模式
				{
					bt_cmd=BT_NEXT;//下一曲
				}
			}
			case KR(K_NEXT): //长按
			{
				
				break;
			}
			/*******************************************************************************
			*功能：闹钟
			*
			*******************************************************************************/
			case KU(K_ALARM): //短按//闹钟
			{
				/* 设置RTC时间 从"K_AL_SNOOZE"键哪里过来的*/
				if (FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR)
				{
					/*在长按ALARM键和SNOOZE键进入设置时间模式-小时设置，在短按ALARM键设置分钟时间*/
					SetDisplayState10s(ADJ_CLK_MIN);//配置为设置RTC的状态-闪
					FlagKSet_TypeDef = FLAG_KEYSET_SETTIME_MINUTE;
					Time_Temp_TypeDef.Flag_Confirm_30Sec=2;//短按ALARM键确认设置或不动作30s自动保存，(为1是确
														   //认闹钟设置标志位),为2是30s计时标志位，
					timeCnt_30Sec = 0;//校准，以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
					break;
				}
				else if (FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE)
				{
					//在长按ALARM键和SNOOZE键进入设置时间模式-小时设置，在短按ALARM键设置分钟时间
					//在短按ALRM键确认时间设置，或者在进入分钟设置时间之后不动作30s即自动保存
					FlagKSet_TypeDef = FLAG_KEYSET_OFF;
					gRTC_Hour   = Time_Temp_TypeDef.temp_RTC_Hour;
					gRTC_Minute = Time_Temp_TypeDef.temp_RTC_Minute;
					Time_Temp_TypeDef.Flag_Confirm_30Sec = 0;//短按ALARM键确认设置
					timeCnt_30Sec = 0;//校准,以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
					cntDispStatus=0;
					Flag_DispStatus=0;
					break;
				}

				/* 设置闹钟时间 */
				if(((PlayMode_TypeDef == PLAY_IN_TIME) && (FlagKSet_TypeDef == FLAG_KEYSET_OFF)) || (Alarm1_TypeDef.Flag_Again==1))
				{
					//只有在走时和没有其他设置模式下(比如时间设置，因为短按ALARM有其他功能)，才会进入此if功能
					//设置脑中时间并开启闹钟
					Alarm1_TypeDef.tempHour   = Alarm1_TypeDef.hour;//把原来设置的闹钟时间赋值给临时变量用于显示
					Alarm1_TypeDef.tempMinute = Alarm1_TypeDef.minute;
					SetDisplayState10s(ADJ_ALARM1_HOUR);//闹钟小时闪烁
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_HOUR;
					Alarm1_TypeDef.Alarm_OnOff = ALARM_ON;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//第二次开启闹钟，并且不修改脑中时间，不动作30s自动保
														  //存，(为1是确认闹钟设置标志位)为2是30s计时标志位，
					Alarm1_TypeDef.Flag_Again=0;//设置好闹钟后重新进来，如果30s不操作就会被置为1
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))  
				{
					SetDisplayState10s(ADJ_ALARM1_MIN);//闹钟分钟闪烁
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_MINUTE;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//第二次开启闹钟，并且修改脑中时间，把不动作自动保存关闭
					timeCnt_30Sec = 0;				  //并校准时间为0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					SetDisplayState10s(ADJ_ALARM1_WORK);//闹钟工作模式闪烁，beep响或者蓝牙标志闪
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_ALWORKMODE;
					//Alarm1_TypeDef.Alarm_WorkMode=ALARM_BT&ALARM_BEEP;//工作模式，在音量加和音量减那里设置
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//短按ALARM键确认设置或不动作30s自动保存，(为1
														  //是确认闹钟设置标志位)为2是30s计时标志位，
					timeCnt_30Sec = 0;//校准，以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_ALWORKMODE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					//FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_CONFIRMSET;
					FlagKSet_TypeDef = FLAG_KEYSET_OFF;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 0;//短按ALARM键确认设置或不动作30s自动保存，(为1
														  //是确认闹钟设置标志位)为2是30s计时标志位，
					timeCnt_30Sec = 0;//校准，以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
					Alarm1_TypeDef.hour   = Alarm1_TypeDef.tempHour;//短按ALARM键确认设置
					Alarm1_TypeDef.minute = Alarm1_TypeDef.tempMinute;
					Alarm1_TypeDef.Flag_Again=1;
					cntDispStatus=0;
					Flag_DispStatus=0;
				}

				break;
			}
			case KH(K_ALARM): //长按//闹钟
			{
				
				break;
			}
			/*******************************************************************************
			*功能：音量减
			*
			*******************************************************************************/
			case KU(K_VOLDEC): //短按//音量减
			case KR(K_VOLDEC): //长按//音量减
			{
				//长按“VOL-”键，小时快速递减；
				//长按“VOL-”键，分钟位数快速递减；
				if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Hour > 0)
					{
						Time_Temp_TypeDef.temp_RTC_Hour--;
					}
					else //形成循环
					{
						if (Time_Temp_TypeDef.temp_RTC_Hour == 0)
							Time_Temp_TypeDef.temp_RTC_Hour=24;
					}
					timeCnt_30Sec = 0;
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE) && (PlayMode_TypeDef == PLAY_IN_TIME))
				{
					if (Time_Temp_TypeDef.temp_RTC_Minute > 0)
					{
						Time_Temp_TypeDef.temp_RTC_Minute--;
					}
					else//形成循环
					{
						if (Time_Temp_TypeDef.temp_RTC_Minute == 0)
						{
							Time_Temp_TypeDef.temp_RTC_Minute=59;
						}
					}
					gRTC_Minute=0;
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempHour > 0)
					{
						Alarm1_TypeDef.tempHour--;
					}
					else//形成循环
					{
						if (Alarm1_TypeDef.tempHour == 0)
						{
							Alarm1_TypeDef.tempHour=24;
						}
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.tempMinute > 0)
					{
						Alarm1_TypeDef.tempMinute--;
					}
					else//形成循环
					{
						if (Alarm1_TypeDef.tempMinute == 0)
						{
							Alarm1_TypeDef.tempMinute=59;
						}
					}
					timeCnt_30Sec = 0;
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_ALWORKMODE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					if (Alarm1_TypeDef.Alarm_WorkMode == ALARM_BEEP)
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BT;
					}
					else
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BEEP;
					}
					timeCnt_30Sec = 0;//开启了不动作30s自动保存，这里动作了，所以重新置0
				}
				else//在蓝牙或TF状态下，音量功能
				{
					if (sysVolume > 0)
					{
						sysVolume--;
					}
				}

				break;
			}
			/*******************************************************************************
			*功能：蓝牙
			*
			*******************************************************************************/
			case KU(K_BT): //短按
			{
				//短按“VOL-/PREV”键，小时递减，
				//短按“VOL-/PREV”键，分钟位数递减，
				if (Music_Mode_TypeDef == MUSIC_OFF)
				{
					Music_Mode_TypeDef = MUSIC_BT;//如果已经插入TF卡，在TF_Check()里面也会立马转为TF卡模式
				}
				else
				{
					Music_Mode_TypeDef = MUSIC_OFF;
				}
				break;
			}
			case KR(K_BT): //长按
			{
				if (cntKeylong == 10)//2s
					bt_cmd=BT_PAIR;
				break;
			}
			/*******************************************************************************
			*功能：上一曲
			*
			*******************************************************************************/
			case KU(K_PREV): //短按
			{
				if (Music_Mode_TypeDef > MUSIC_OFF)//在蓝牙和TF卡模式
				{
					bt_cmd=BT_PREV;//上一曲
				}
			}
			case KR(K_PREV): //长按
			{
				
				break;
			}
			/*******************************************************************************
			*功能：设置RTC时间     组合键=闹钟+贪睡
			*
			*******************************************************************************/
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
						//长按ALARM和SNOOZE键2s进入时间设置模式-小时设置
						Time_Temp_TypeDef.temp_RTC_Hour   = gRTC_Hour;
						Time_Temp_TypeDef.temp_RTC_Minute = gRTC_Minute;
						SetDisplayState10s(ADJ_CLK_HOUR);//配置为设置RTC的状态-闪
						FlagKSet_TypeDef = FLAG_KEYSET_SETTIME_HOUR;
						Time_Temp_TypeDef.Flag_Confirm_30Sec=2;//短按ALARM键确认设置或不动作30s自动保存，(为1是确
														   //认闹钟设置标志位),为2是30s计时标志位，
						timeCnt_30Sec = 0;//校准，以防以前设置的时间或者其他功能使用时timeCnt_30Sec有大于0的值
					}
				}
				break;
			}
			/*******************************************************************************
			*功能：增加一小时夏令时      组合键=闹钟+音量加
			*
			*******************************************************************************/
			case KU(K_AL_VOLINC): //短按
			case KR(K_AL_VOLINC): //长按
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if(Flag_DaylightSaving != 1)//只进来1次，除非减了夏令时
					{
						if (cntKeylong == 10)//2s
						{
							gRTC_Hour = gRTC_Hour + 1;//组合键-闹钟和音量加-同时2s-RTC时间加一小时，表示开启夏令时
							Flag_DaylightSaving=1;
						}
					}
				}
				break;
			}
			/*******************************************************************************
			*功能：减少一小时夏令时      组合键=闹钟+音量减
			*
			*******************************************************************************/
			case KU(K_AL_VOLDEC): //短按
			case KR(K_AL_VOLDEC): //长按
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if(Flag_DaylightSaving != 2)//纸巾来一次，除非加了夏令时
					{
						if (cntKeylong == 10)//2s
						{
							gRTC_Hour = gRTC_Hour - 1;//组合键-闹钟和音量加-同时2s-RTC时间加一小时，表示开启夏令时
							Flag_DaylightSaving=2;
						}
					}
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















