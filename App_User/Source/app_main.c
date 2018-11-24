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
bit     AppTick0;
bit     AppTick1;
bit     AppTick2;
bit     AppTick3;
bit     AppTick4;
bit     AppTick5;
bit     AppTick1ms;
uint8_t Flag_DaylightSaving;//�Ƿ���������ʱ��־�������������һ��Сʱֻ�ܼ�һ�Σ�
						    //1Ϊ����һ��Сʱ��2Ϊ����һ��Сʱ
uint8_t Flag_Alarm1_IQ_BTOrBEEp;//����1��Ӧʱ�Ȳ�ѯ��������û���ٲ��ţ�����ڲ��Ų�������Ӱ��
								//����ģʽΪ�������ţ��Ͱ����ӹ���ģʽתΪbeep

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
uint16_t       cntDispStatus;
uint8_t        cntJustPower_AllLED_2s;//���ϵ�ȫ��LED��ʾ2s

uint16_t idata cntBT_Connect_30s;//������ʱ����ģʽ�����û�����ӵ������ͼ���30s
uint8_t  idata cntAlarm_Runing_60Min;//���ӵ�ʱ��60���ӣ�
uint32_t idata cntSnooze_9Min;//
uint8_t  idata cntBeep;//������ʱ����Ϊbeepģʽ������1s����0.5s
uint8_t  idata cntAlarm1_IQ_BTOrBEEp;//����1��Ӧʱ�Ȳ�ѯ��������û���ٲ��ţ�����ڲ��Ų�������Ӱ��
								//����ģʽΪ�������ţ��Ͱ����ӹ���ģʽתΪbeep

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
//	uint8_t cnt;
//	Snooze_Hour = gRTC_Hour;//������RTCʱ�丳��̰˯ʱ�������ټ���9��������RTCʱ��Ա�
//	Snooze_Minute = gRTC_Minute;
//	for (cnt = 0; cnt < 9; cnt++)//����֮���Խ���9��if�ж�
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
* �������ܣ����ϵ�ȫ��LED��ʾ2s�������ǰ�_SET_xx(Flag_SET_xx)�е�Flag_SET_xx��һ��
*			�ڶ�ʱ�����ֵ���ʱ�ͻ�������������Ϊ���
* ����ֵ˵����
* �������ڣ�
* �����ˣ�
* �޸�����
* �޸��ˣ�
* ��N���޸ģ�
* �޸�ԭ��
* ��ע��
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
* ����ԭ�ͣ�
* ���������
* ���������
* �������ܣ����ϵ�ȫ��LED��ʾ2s����,���������Ͼ������־λ���˳�while(cntJustPower_AllLED_2s)
* ����ֵ˵����
* �������ڣ�
* �����ˣ�
* �޸�����
* �޸��ˣ�
* ��N���޸ģ�
* �޸�ԭ��
* ��ע��
*******************************************************************************/
void JustPower_AllLED_2s(void)
{
	cntJustPower_AllLED_2s--;
	if(cntJustPower_AllLED_2s==0)
	{

		WT_init();//����WT�ж�
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
* ����ԭ�ͣ�
* ���������
* ���������
* �������ܣ����ϵ�ȫ��LED��ʾ2s����
* ����ֵ˵����
* �������ڣ�
* �����ˣ�
* �޸�����
* �޸��ˣ�
* ��N���޸ģ�
* �޸�ԭ��
* ��ע��
*******************************************************************************/
void JustPower_AllLED(void)
{
	WT_Def_Init();//�ȹر�WT�жϣ�����RTC���������仯
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
	/*******************************************************************************
	 *���ܣ�
	 *������1s����һ��
	 *******************************************************************************/
	if(gRTC_Sec!=gRTC_Sec_bk)
	{
		gRTC_Sec_bk=gRTC_Sec;
		/*******************************************************************************
		 *���ܣ��������ʱ�䵽���ж��ǲ����������ڲ��ţ������ж�������Ӧ����ģʽ�ǲ���
		 *		����ģʽ�����������ģʽ�������������ڲ���(Flag_Alarm1_IQ_BTOrBEEp��Ϊ2)
		 *		��תΪbeepģʽ���������ڲ��ŵ������ص������û�����ڲ��ţ��ͻ�����������
		 *		�����ӣ����30s��û�����ӵ���������תΪbeep����Ϊ��Flag_Alarm1_IQ_BTOrBEEp
		 *		��ֵΪ1��������ִ�е������ǹ�ȥ��1s�����ڷ��Ͳ�ѯ�ٽ���ʱ���ǹ��ã�����
		 *		�������Flag_Alarm1_IQ_BTOrBEEp��ȻΪ1�Ǿ�������û���ڲ��ţ��Ϳ�����������
		 *������1s����һ��
		 *******************************************************************************/
		if(Flag_Alarm1_IQ_BTOrBEEp==2)//���ӹ���ģʽΪ���������������ڲ���
		{
			Alarm1_TypeDef.Alarm_RingRun=ALARM_RING_RUN_ON;
			Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP;
			Flag_Alarm1_IQ_BTOrBEEp=0;//�����־��Ϊ�´���׼��
			bt_cmd=BT_PAUSE;//�������Ĳ�����ͣ
		}
		else if(Flag_Alarm1_IQ_BTOrBEEp==1)//���ӹ���ģʽΪ����������û���ڲ���
		{
			Alarm1_TypeDef.Alarm_RingRun=ALARM_RING_RUN_ON;
			Flag_Alarm1_IQ_BTOrBEEp=0;//�����־��Ϊ�´���׼��
			//���ﲻ�÷��ͻ�����������
		}
		
		if(gRTC_Minute!=gRTC_Minute_bk)//����
		{
			gRTC_Minute_bk=gRTC_Minute;
			/*******************************************************************************
			 *���ܣ����Ӷ�ʱ����Ƿ����������Ƿ�ʱ�䵽
			 *������1min����һ��
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
			 *���ܣ������ܵ���Ӧʱ��(����̰˯)Ϊ60�֣�����һ��Ϳ�ʼ��ʱ
			 *******************************************************************************/
			if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON))
			{
				cntAlarm_Runing_60Min++;
				if(cntAlarm_Runing_60Min>=60)
				{
					Alarm1_PowerOFF();
				}
				if(Alarm1_TypeDef.Alarm_Snooze == ALARM_SNOOZE_ON)//�����̰˯ģʽ
				{
					cntSnooze_9Min++;
					if(cntSnooze_9Min>=9)
					{
						cntSnooze_9Min=0;
						Alarm1_TypeDef.Alarm_Snooze = ALARM_SNOOZE_OFF;//̰˯ʱ�䵽���ر�̰˯ģʽ
					}
				}
			}
			
			/*******************************************************************************
			 *���ܣ�
			 *������1hour����һ��
			 *******************************************************************************/
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
	/*******************************************************************************
	 *���ܣ����ӿ����������Ѿ���Ӧ
	 *������10ms����һ��
	 *******************************************************************************/
	if((Alarm1_TypeDef.Alarm_OnOff == ALARM_ON) && (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON))
	{
		if(Alarm1_TypeDef.Alarm_Snooze == ALARM_SNOOZE_OFF)//���������̰˯ģʽ
		{
			if(Alarm1_TypeDef.Alarm_WorkMode==ALARM_BT)//���ӹ���ģʽΪ����
			{
				if(Flag_BT_Connect==1)//˵���������ӳɹ�
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
						if((cntBT_Connect_30s%100)==0)//1s����һ�λ�������һ��Ϊ0ʱ����Ҫ��"cntBT_Connect_30s++;"ǰ��
							bt_cmd=BT_PLAY;
						
						//bt_cmd=BT_PLAY;
					}
				}
				else
				{
					if((cntBT_Connect_30s%100)==0)//1s����һ�λ�������һ��Ϊ0ʱ����Ҫ��"cntBT_Connect_30s++;"ǰ��
						bt_cmd=BT_LINK_BACK;	 //��Ȼ"++"֮���Ϊ1�����Ͳ��ˣ�Ҫ�ȵ�100���ܷ�����
					cntBT_Connect_30s++;
					Flag_BT_Play=0;
					if(cntBT_Connect_30s>=3000)//30sʱ�䵽
					{
						cntBT_Connect_30s=0;
						if(Flag_BT_Connect==0)
						{
							Alarm1_TypeDef.Alarm_WorkMode=ALARM_BEEP;//�л���beepģʽ
						}
					}
				}
			}
			else
			{
				if(Alarm1_TypeDef.Alarm_WorkMode==ALARM_BEEP)//���ӹ���ģʽΪbeep
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
		else//�������̰˯ģʽ
		{
			BUZ_OnOff(0);
			__EN_MUTE();
			if(Flag_BT_Play)
			{
				Flag_BT_Play=0;
				bt_cmd=BT_PAUSE;//���������ģʽ����ͣ����
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
			Alarm1_TypeDef.hour   = Alarm1_TypeDef.tempHour;//30s��ʱ�������趨������ʱ�丳����RTC�ȶԵ����ӱ���
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
		if((--uart1_TX_Timeout)==0)//���ͳ�ʱ�����㷢�ͱ�־λ
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
	Music_Mode_TypeDef = MUSIC_OFF;
	__BT_CLR_POWER();
	cntJustPower_AllLED_2s=200;//���ϵ�ȫ��LED��ʾ2s
	sysVolume = 8;//Ĭ��ϵͳ����Ϊ8��
	cntNoFlash = 0;
	gbUser_AdjClk = 1;
	gb12HourDisp = 1;
	gbHalfSecond = 1;
	gRTC_Sec = 0;
	gRTC_Minute = 0;
	gRTC_Hour = 0;
	gZone = 2;
	Flag_DaylightSaving=0;//����ʱ���㣬
//	Alarm1Mode = ALARM_NONE;
//	Alarm2Mode = ALARM_NONE;
//	AlarmingType = ALARM_OFF;

	gbPowerOn = 0;
//	Alarm1_TypeDef.Alarm_OnOff = ALARM_ON;
//	Alarm1_TypeDef.hour=0;
//	Alarm1_TypeDef.minute=40;
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










