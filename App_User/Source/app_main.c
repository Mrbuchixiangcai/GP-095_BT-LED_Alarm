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
PLAY_MODE_TypeDef  TYPE_Play_Mode;
ALRAM_TypeDef  TYPE_Alarm1;

/****************************/
/*��־λ����flags definetion*/
/****************************/
bit  AppTick0;
bit  AppTick1;
bit  AppTick2;
bit  AppTick3;
bit  AppTick4;
bit  AppTick5;
bit  AppTick1ms;

bit  Flag_Alarm;  //Ϊ1Ϊ���ӿ�����Ϊ0��ر�
bit  Flag_AlarmSet_Confirm_TimeCnt_30Sec;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1��ȷ���������ñ�־λ)Ϊ2��30s��ʱ��־λ��


/*****************************/
/*��������variable definition*/
/*****************************/
uint8_t  idata cntAppTick;
bit		 	   gbHalfSecong;
uint8_t  idata gRTC_Sec;//RTC���� 
uint8_t  idata gRTC_Sec_bk;
uint8_t  idata gRTC_Minute;
uint8_t  idata gRTC_Minute_bk;
uint8_t  idata gRTC_Hour;
uint8_t  idata gRTC_Hour_bk;
uint8_t  xdata gRTC_Hour_bk_24;//����24Сʱ
uint8_t  idata gRTC_Week; //һ��7��
uint8_t  idata sys_volume;
uint16_t idata timeCnt_30Sec;//�̰�ALARM��ȱ�����û򲻶���30s�Զ����棬30s��ʱ


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
	if(Flag_AlarmSet_Confirm_TimeCnt_30Sec==2)
	{
		timeCnt_30Sec++;
		if(timeCnt_30Sec>=3000)
		{
			Flag_AlarmSet_Confirm_TimeCnt_30Sec=0;
			timeCnt_30Sec=0;
			alarmHour=tempAlarmHour;	//30s��ʱ�������趨������ʱ�丳����RTC�ȶԵ����ӱ���
			alarmMinute=tempAlarmMinute;
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
	TYPE_Play_Mode=PLAY_JUST_POWER;//���ϵ磬ģʽ��Ϊ���ϵ�ģʽ
	TYPE_LED_Brightness=LED_HIGH;//����Ĭ��Ϊ��
	TYPE_Alarm1.Alarm_Mode=ALARM_BEEP; //�Լ��ӵ�Ϊ��������ģʽΪbeepģʽ������д����Ҳ��ֹʹ��������������
								//ʱû��ѡ��ģʽ���Ǿ�ѡ��Ĭ����beepģʽ
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










