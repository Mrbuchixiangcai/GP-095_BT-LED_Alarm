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
uint8_t  xdata gRTC_Hour_bk_24;//����24Сʱ
uint8_t  idata gRTC_Week; //һ��7��
uint8_t  idata sys_Volume;//ϵͳ����
uint8_t  idata sys_Cmd;//����
uint8_t  idata sys_Name;
uint16_t idata timeCnt_30Sec;//�̰�ALARM��ȱ�����û򲻶���30s�Զ����棬30s��ʱ

u8       idata cntNoFlash;
u8		 idata AlarmingType;//����ʱ�������ǹرգ���Alarm1_TypeDef.Alarm_OnOFF����
u8		 idata Alarm1Mode;//��Alarm1_TypeDef.Alarm_Mode������
u8			   gZone;
u8			   dispStatus;

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
		
		if(gRTC_Minute!=gRTC_Minute_bk)
		{
			gRTC_Minute_bk=gRTC_Minute;
			if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (gRTC_Hour == Alarm1_TypeDef.hour) && (gRTC_Minute == Alarm1_TypeDef.minute))
			{
				if(Alarm1_TypeDef.AlarmWorkMode==ALARM_BT)
				{
					
				}
				else
				{

				}
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
		if (timeCnt_30Sec >= 3000)
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
		if (timeCnt_30Sec >= 3000)
		{
			Alarm1_TypeDef.Flag_Confirm_30Sec = 0;
			FlagKSet_TypeDef = FLAG_KEYSET_OFF;
			timeCnt_30Sec = 0;
			Alarm1_TypeDef.hour   = Alarm1_TypeDef.tempHour;//30s��ʱ�������趨������ʱ�丳����RTC�ȶԵ����ӱ���
			Alarm1_TypeDef.minute = Alarm1_TypeDef.tempMinute;
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
	PlayMode_TypeDef=PLAY_JUST_POWER;//���ϵ磬ģʽ��Ϊ���ϵ�ģʽ
	LED_Brightness_TypeDef=LED_HIGH;//����Ĭ��Ϊ��
	Alarm1_TypeDef.AlarmWorkMode=ALARM_BEEP; //�Լ��ӵ�Ϊ��������ģʽΪbeepģʽ������д����Ҳ��ֹʹ��������������
								//ʱû��ѡ��ģʽ���Ǿ�ѡ��Ĭ����beepģʽ
	sys_Volume = 8;//Ĭ��ϵͳ����Ϊ8��
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










