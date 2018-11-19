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
PLAY_MODE_TypeDef  PlayMode_TypeDef;
CONTROL_COMMAND_TypeDef Ctrl_Com_TypeDef;

/****************************/
/*��־λ����flags definetion*/
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
/*��������variable definition*/
/*****************************/
uint8_t  idata cntAppTick;
bit		 	   gbHalfSecond;
uint8_t  idata gRTC_Sec;//RTC���� 
uint8_t  idata gRTC_Sec_bk;
uint8_t  idata gRTC_Minute;
uint8_t  idata gRTC_Minute_bk;
uint8_t  idata gRTC_Hour;
uint8_t  idata gRTC_Hour_bk;
uint8_t  idata gRTC_Hour_bk_24;//����24Сʱ
uint8_t  idata gRTC_Week; //һ��7��
uint8_t  idata Snooze_Hour;//̰˯Сʱʱ��
uint8_t  idata Snooze_Minute;//̰˯����ʱ��
uint8_t  idata sysVolume;//ϵͳ����
uint8_t  idata sys_Cmd;//����
uint8_t  idata sys_Name;
uint16_t idata timeCnt_30Sec;//�̰�ALARM��ȱ�����û򲻶���30s�Զ����棬30s��ʱ

uint8_t  idata cntAlarm;
uint8_t  idata cntSleep;
uint8_t  idata sleepTimeSet;
uint8_t  idata cntNoFlash;
uint8_t  idata AlarmingType;//����ʱ�������ǹرգ���Alarm1_TypeDef.Alarm_OnOFF����
uint8_t	 idata Alarm1Mode;//��Alarm1_TypeDef.Alarm_Mode������
uint8_t		   gZone;
uint8_t	 idata cnt0_5s;//ͨ����������ļ�������gb0_5s��״̬����ȡ����ÿ��ȡ��0.5s
uint32_t        cntDispStatus;

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
 * �������ܣ�����ʾ״̬����
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/
void ClearDisplayStatus(void)
{
	Flag_DispStatus = 0;
	cntDispStatus = 0;
}

 /*******************************************************************************
  * ����ԭ�ͣ�
  * ���������
  * ���������
  * �������ܣ�˯�߻���֮�������ر�־λ�ͼ���ʲô�ı���
  * ����ֵ˵����
  * �������ڣ�
  * �����ˣ�
  * �޸�����
  * �޸��ˣ�
  * ��N���޸ģ�
  * �޸�ԭ��
  * ��ע��
  *******************************************************************************/
void Clear_Sleep(void)
{
	cntSleep = 0;
	sleepTimeSet = 0;
	gbSleepEnable = 0;
}

  /*******************************************************************************
   * ����ԭ�ͣ�
   * ���������
   * ���������
   * �������ܣ��˳���ʾ״̬
   * ����ֵ˵����
   * �������ڣ�
   * �����ˣ�
   * �޸�����
   * �޸��ˣ�
   * ��N���޸ģ�
   * �޸�ԭ��
   * ��ע��
   *******************************************************************************/
void DisplayStatusExit(void)
{
	if (cntDispStatus)
	{
		if (++cnt0_5s >= cDISP_DELAY__500ms)//10ms����һ�Σ�������500ms�ͽ���
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
*******************************************************************************/
void Snooze_9Min(void)
{
	uint8_t cnt;
	Snooze_Hour = gRTC_Hour;//������RTCʱ�丳��̰˯ʱ�������ټ���9��������RTCʱ��Ա�
	Snooze_Minute = gRTC_Minute;
	for (cnt = 0; cnt < 9; cnt++)//����֮���Խ���9��if�ж�
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
* ����ԭ�ͣ�
* ���������
* ���������
* �������ܣ�������ʱ����SNOOZE(̰˯)����������̰˯9����
* ����ֵ˵����
* �������ڣ�
* �����ˣ�
* �޸�����
* �޸��ˣ�
* ��N���޸ģ�
* �޸�ԭ��
* ��ע��
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
			//BuzzEventPorc(eAL_AL_IDLE);//���������û��д��
			gbSnoozeEnable = 1;//̰˯��־λ��1������̰˯
		}
	}
}

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
*******************************************************************************/



/*******************************************************************************
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ�ʱ��Ƚϣ���RTCʱ����ĳ����ʱʱ��Ƚϣ���������
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
 *******************************************************************************/
void Compare_1MinutePorc(void)
{
	//static uint8_t  cntSetVolume; //�˱���ֻ���ϵ�ʱ��ʼ��һ�Σ��ٵ��ô˺���ʱ����ִ�д����
	if(gRTC_Sec!=gRTC_Sec_bk)
	{
		gRTC_Sec_bk=gRTC_Sec;
		
		if(gRTC_Minute!=gRTC_Minute_bk)//����
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
				
			if(gRTC_Hour!=gRTC_Hour_bk)//Сʱ
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
 * ����ԭ�ͣ�
 * ���������
 * ���������
 * �������ܣ�����������Ҫ�õ��ļ�ʱ�����������
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��
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
			gRTC_Hour   = Time_Temp_TypeDef.temp_RTC_Hour; //30s��ʱ�������趨����ʱRTCʱ�丶��һֱ�����е�RTCʱ��
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
			Alarm1_TypeDef.hour   = Alarm1_TypeDef.tempHour;//30s��ʱ�������趨������ʱ�丳����RTC�ȶԵ����ӱ���
			Alarm1_TypeDef.minute = Alarm1_TypeDef.tempMinute;
			Alarm1_TypeDef.Flag_Again=1;
			cntDispStatus=0;
		}
	}
	//else
	//	timeCnt_30Sec = 0;
}

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
		if((--uart1_TX_Timeout)==0)//���ͳ�ʱ�����㷢�ͱ�־λ
			uart1_EnableSend=0;
		if((--uart1_RX_Timeout)==0)
			uart1_RX_Pointer=0;
	}
	if(++cntAppTick>=10)
		cntAppTick=0;
}

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
 *******************************************************************************/
void PowerON_Reset(void)
{
	//WDT_init();     	// initialize Watch-dog timer
	PlayMode_TypeDef=PLAY_IN_TIME;//PLAY_JUST_POWER;//���ϵ磬ģʽ��Ϊ���ϵ�ģʽ
	LED_Brightness_TypeDef=LED_HIGH;//����Ĭ��Ϊ��
	Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP; //�Լ��ӵ�Ϊ��������ģʽΪbeepģʽ������д����Ҳ��ֹʹ��������������
								//ʱû��ѡ��ģʽ���Ǿ�ѡ��Ĭ����beepģʽ
	Music_Mode_TypeDef = MUSIC_BT;
	sysVolume = 8;//Ĭ��ϵͳ����Ϊ8��
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










