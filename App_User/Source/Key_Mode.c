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
FLAG_KEYSET_TypeDef  FlagKSet_TypeDef;//�����Ĺ������ñ�־
TIME_TEMP_TypeDef    Time_Temp_TypeDef;//����ʱ��ʱ�Ű����õ�ʱ���ȸ��������Ȼ��ȷ�����ٸ�ֵ��gRTC_xx;

/****************************/
/*��־λ����flags definetion*/
/****************************/

/*****************************/
/*��������variable definition*/
/*****************************/
uint8_t  gbKeyPress;//��������
uint8_t  gbKeyNone; //û�а�������
uint8_t  KeyValue;  //����ֵ
uint8_t  KeyEvent;  //�����¼�
uint8_t  cntKeyLoop;//��������ѭ�����̰����������������İ���ʱ��
uint8_t  cntKeylong;
uint8_t  KeyCurValueBK;//���ڰ�������
uint8_t  KeyCurValue;//��������ֵ
uint8_t  KeyLastValue;//������һ�ε�ֵ

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
 * �������ܣ�
 * ����ֵ˵����
 * �������ڣ�
 * �����ˣ�
 * �޸�����
 * �޸��ˣ�
 * ��N���޸ģ�
 * �޸�ԭ��
 * ��ע��"P1=0x2F(0010_1111)"�ȸ�ֵ��P1�ڣ�P15Ϊ1��P14Ϊ0�������(P10-P13)Ϊ1��
 * Ȼ���ٶ�P1�ڵ�ƽ(P1&0x0F)�����Ѹ���λ����0��������ʱ��P10�����£��Ƕ�����P1
 * �ڵ�ƽΪ(P1&0x0f)Ϊ0x0E(0000_1110),Ȼ����0x0F(0000_1111)���õ�0x01(0000_0001),
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
//	scanKeyValue=0;//���û�а������¾��Ƿ���0
//	 
//	/*******************************************************************************
//	*���ܣ�"P1=0x2F(0010_1111)"�ȸ�ֵ��P1�ڣ�P15Ϊ1��P14Ϊ0�������(P10-P13)Ϊ1��Ȼ
//	* ���ٶ�P1�ڵ�ƽ(P1&0x0F)�����Ѹ���λ����0(P1&0x0F��������ʱ��P10�����£��Ƕ���
//	* ��P1�ڵ�ƽΪ0x0E(0000_1110),Ȼ����0x0F(0000_1111)���õ�0x01(0000_0001),
//	* readData1�ķ�ΧΪ1��2��4��8��scanKeyValue�ķ�ΧΪ1~9,9����ϼ���
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
//				scanKeyValue=2; //VOL+(ʵ��VOL-)
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
//	*���ܣ�"P1=0x1F(0001_1111)"�ȸ�ֵ��P1�ڣ�P15Ϊ0��P14Ϊ1�������(P10-P13)Ϊ1��Ȼ
//	* ���ٶ�P1�ڵ�ƽ(P1&0x0F)�����Ѹ���λ����0(P1&0x0F��������ʱ��P11�����£��Ƕ���
//	* ��P1�ڵ�ƽΪ0x0D(0000_1101),Ȼ����0x0F(0000_1111)���õ�0x02(0000_0010),
//	* readData2�ķ�ΧΪ1��2��4��8��scanKeyValue�ķ�ΧΪ1~9��9����ϼ���
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
////				if (scanKeyValue == 1)//Ϊ1˵���ղ�alarm�������£���Ϊÿ�ε���������������ʼ��
////				{				  	  //keyValue�����Բ������ϴε��ú������µ�ֵ
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
uint8_t GetKeyValue(void) 
{
	uint8_t  keyNum;
	keyNum=Matrix_Buttons();
	return keyNum; //���ذ���
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
void KeyEventPorc(uint8_t KeyTmp) //������ʱ���յ���GetKeyValue()�ķ���ֵ  һ��̶���������
{
	gbKeyPress=0;
	if(KeyCurValue!=KeyTmp) //���if�����ȥ�����ᱻִ�����Σ������ν���ʱֱ������
	{//KeyTmpΪ��ʱֵ��
		if(KeyCurValueBK!=KeyTmp)
			KeyCurValueBK=KeyTmp;
		else //�ڶ��ν���ʱִ����һ��
			KeyCurValue=KeyTmp; //
		return;
	}
	if(KeyCurValue==KeyLastValue)
	{
		if((KeyLastValue==0) || (cntKeyLoop==0))
			return;
		if(--cntKeyLoop==0) //����ڵڶ��ν�KeyEventPorc()��������һ�ν���if(KeyCurValue==KeyLastValue)��֮ǰ��ʱ�����渳ֵΪ5
		{ //cntKeyLoopΪ5����50msʱ��
			KeyValue=KeyLastValue; //����֮���ȷ���İ�����ֵ��KeyValue
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
void KeyScan(void) //������������
{
	KeyEventPorc(GetKeyValue());
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
 * ��ע��2.��������TIME����2S��Сʱ�ַ���˸���̰���VOL-/PREV������Сʱ�ݼ�������
 * ��VOL-/PREV������Сʱ���ٵݼ����̰���VOL+/NEXT������Сʱ������������VOL+/NEXT������
 * Сʱ���ٵ�����
 * 3���̰���TIME���������ַ���˸���̰���VOL-/PREV��������λ���ݼ���������VOL-/PREV������
 * ��λ�����ٵݼ����̰���VOL+/NEXT��������λ��������������VOL+/NEXT��������λ�����ٵ�
 * ����
 * 4������ʱģʽ�£��̰���TIME/DIM������������ʾ���ȣ���ѭ�������ߡ��С�������Ĭ��
 * Ϊ������
 *******************************************************************************/
void KeyComMsg(void) 
{
	if(gbKeyPress)
	{ 
		//Flag_data_bk=1;//���ݸı�ʱ����
	   	switch(KeyValue)
		{
			case KU(K_SNOOZE_DIMMER)://�̰�
			{//Alarm_Ring_Run
				if (Alarm1_TypeDef.Alarm_RingRun == ALARM_RING_RUN_ON)
				{
					Alarm1_TypeDef.Alarm_Snooze = ALARM_SNOOZE_ON;//����̰˯ģʽ��Ϊ9����
				}
				else//������ʱģʽ�£��̰�SNOOZE��������LEDƽ���ȣ���ѭ�����ڸߡ��С�������(Ĭ��Ϊ��)
				{
					LED_Brightness_TypeDef--;
					if (LED_Brightness_TypeDef == LED_TURN_OFF)//����ѭ��
						LED_Brightness_TypeDef = LED_HIGH;
				}
				break;
			}
			case KH(K_SNOOZE_DIMMER)://����
			{
				
				break;
			}
			case KU(K_VOLINC): //�̰�//������ 
			case KR(K_VOLINC): //����//������
			{
				//������VOL+/NEXT������Сʱ���ٵ�����
				//������VOL+/NEXT����������λ�����ٵ�����
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
					timeCnt_30Sec = 0;//�����˲�����30s�Զ����棬���ﶯ���ˣ�����������0
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
					if (Alarm1_TypeDef.Alarm_WorkMode == ALARM_BEEP)
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BT;
					}
					else
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BEEP;
					}
					timeCnt_30Sec = 0;//�����˲�����30s�Զ����棬���ﶯ���ˣ�����������0
				}
				else//��������TF״̬�£���������
				{
					if (sysVolume < 15)
					{
						sysVolume++;
					}
				}

				break;
			}
			case KU(K_PLAY_PAUSE): //�̰�//�̰������ַ���˸��
			{					
				if (Music_Mode_TypeDef > MUSIC_OFF)//��������TF��ģʽ
				{
					Ctrl_Com_TypeDef = CTRL_NEXT;
				}
				break;
			}
			case KR(K_PLAY_PAUSE): //��ʱ
			{
				
				break;
			}
			case KU(K_NEXT): //�̰�
			case KR(K_NEXT): //����
			{
				
				break;
			}
			case KU(K_ALARM): //�̰�//����
			{
				/* ����RTCʱ�� */
				if (FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_HOUR)
				{
					//�ڳ���ALARM����SNOOZE����������ʱ��ģʽ-Сʱ���ã��ڶ̰�ALARM�����÷���ʱ��
					FlagKSet_TypeDef = FLAG_KEYSET_SETTIME_MINUTE;
					Time_Temp_TypeDef.Flag_Confirm_30Sec=2;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1��ȷ
														   //���������ñ�־λ),Ϊ2��30s��ʱ��־λ��
					timeCnt_30Sec = 0;//У׼���Է���ǰ���õ�ʱ�������������ʹ��ʱtimeCnt_30Sec�д���0��ֵ
				}
				else if (FlagKSet_TypeDef == FLAG_KEYSET_SETTIME_MINUTE)
				{
					//�ڳ���ALARM����SNOOZE����������ʱ��ģʽ-Сʱ���ã��ڶ̰�ALARM�����÷���ʱ��
					//�ڶ̰�ALRM��ȷ��ʱ�����ã������ڽ����������ʱ��֮�󲻶���30s���Զ�����
					FlagKSet_TypeDef = FLAG_KEYSET_OFF;
					gRTC_Hour   = Time_Temp_TypeDef.temp_RTC_Hour;
					gRTC_Minute = Time_Temp_TypeDef.temp_RTC_Minute;
					//Time_Temp_TypeDef.Flag_Confirm_30Sec = 1;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1��ȷ
															 //���������ñ�־λ),Ϊ2��30s��ʱ��־λ��
				}

				/* ��������ʱ�� */
				if ((PlayMode_TypeDef == PLAY_IN_TIME) && (FlagKSet_TypeDef == FLAG_KEYSET_OFF))
				{
					//ֻ������ʱ��û����������ģʽ��(����ʱ�����ã���Ϊ�̰�ALARM����������)���Ż�����if����
					//��������ʱ�䲢��������
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_HOUR;
					Alarm1_TypeDef.Alarm_OnOff = ALARM_ON;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//�ڶ��ο������ӣ����Ҳ��޸�����ʱ�䣬������30s�Զ���
														  //�棬(Ϊ1��ȷ���������ñ�־λ)Ϊ2��30s��ʱ��־λ��
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_HOUR) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))  
				{
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_MINUTE;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 0;//�ڶ��ο������ӣ������޸�����ʱ�䣬�Ѳ������Զ�����ر�
					//timeCnt_30Sec = 0;					  //��У׼ʱ��Ϊ0
				}
				else if ((FlagKSet_TypeDef == FLAG_KEYSET_SHORT_ALARM_MINUTE) && (Alarm1_TypeDef.Alarm_OnOff == ALARM_ON))
				{
					FlagKSet_TypeDef = FLAG_KEYSET_SHORT_ALARM_ALWORKMODE;
					Alarm1_TypeDef.Flag_Confirm_30Sec = 2;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1
														  //��ȷ���������ñ�־λ)Ϊ2��30s��ʱ��־λ��
					timeCnt_30Sec = 0;//У׼���Է���ǰ���õ�ʱ�������������ʹ��ʱtimeCnt_30Sec�д���0��ֵ
				}

				break;
			}
			case KH(K_ALARM): //����//����
			{
				
				break;
			}
			case KU(K_VOLDEC): //�̰�//������
			case KR(K_VOLDEC): //����//������
			{
				//������VOL-/PREV������Сʱ���ٵݼ���
				//������VOL-/PREV����������λ�����ٵݼ���
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
					timeCnt_30Sec = 0;//�����˲�����30s�Զ����棬���ﶯ���ˣ�����������0
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
					if (Alarm1_TypeDef.Alarm_WorkMode == ALARM_BEEP)
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BT;
					}
					else
					{
						Alarm1_TypeDef.Alarm_WorkMode = ALARM_BEEP;
					}
					timeCnt_30Sec = 0;//�����˲�����30s�Զ����棬���ﶯ���ˣ�����������0
				}
				else//��������TF״̬�£���������
				{
					if (sysVolume > 0)
					{
						sysVolume--;
					}
				}

				break;
			}
			case KU(K_BT): //�̰�
			{
				//�̰���VOL-/PREV������Сʱ�ݼ���
				//�̰���VOL-/PREV����������λ���ݼ���
				if (Music_Mode_TypeDef != MUSIC_BT)
				{
					Music_Mode_TypeDef = MUSIC_BT;
				}
				break;
			}
			case KH(K_BT): //����
			{
				//������VOL-/PREV������Сʱ���ٵݼ���
				//������VOL-/PREV����������λ�����ٵݼ���
				break;
			}
			case KU(K_PREV): //�̰�
			case KR(K_PREV): //����
			{
				if (Music_Mode_TypeDef > MUSIC_OFF)//��������TF��ģʽ
				{
					Ctrl_Com_TypeDef = CTRL_PREV;
				}
				break;
			}
			case KU(K_AL_SNOOZE): //�̰�
			{

				break;
			}
			case KR(K_AL_SNOOZE): //����
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if (cntKeylong == 10)//2s
					{
						//����ALARM��SNOOZE��2s����ʱ������ģʽ-С������
						FlagKSet_TypeDef = FLAG_KEYSET_SETTIME_HOUR;
					}
				}
				break;
			}
			case KU(K_AL_VOLINC): //�̰�
			case KR(K_AL_VOLINC): //����
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if (cntKeylong == 10)//2s
						gRTC_Hour = gRTC_Hour + 1;//��ϼ�-���Ӻ�������-ͬʱ2s-RTCʱ���һСʱ����ʾ��������ʱ
				}
				break;
			}
			case KU(K_AL_VOLDEC): //�̰�
			case KR(K_AL_VOLDEC): //����
			{
				if (PlayMode_TypeDef == PLAY_IN_TIME)
				{
					if (cntKeylong == 10)//2s
						gRTC_Hour = gRTC_Hour - 1;//��ϼ�-���Ӻ�������-ͬʱ2s-RTCʱ���һСʱ����ʾ�ر�����ʱ
				}
				break;
			}
		}
		testINT=KeyValue;
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















