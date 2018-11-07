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
FLAG_KEYSET_TypeDef  TYPE_Flag_KSet;//�����Ĺ������ñ�־

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
	 uint8_t  readData1,readData2;
	 uint8_t  keyValue;
	 keyValue=0;//���û�а������¾��Ƿ���0
	 
	 /*******************************************************************************
	 *���ܣ�"P1=0x2F(0010_1111)"�ȸ�ֵ��P1�ڣ�P15Ϊ1��P14Ϊ0�������(P10-P13)Ϊ1��Ȼ
	 * ���ٶ�P1�ڵ�ƽ(P1&0x0F)�����Ѹ���λ����0(P1&0x0F��������ʱ��P10�����£��Ƕ���
	 * ��P1�ڵ�ƽΪ0x0E(0000_1110),Ȼ����0x0F(0000_1111)���õ�0x01(0000_0001),
	 * readData1�ķ�ΧΪ1��2��4��8��keyValue�ķ�ΧΪ1~8��
	 *******************************************************************************/
	 P1=0x2F;			
	 readData1=(P1&0x0F)^0x0F;
	 switch(readData1)
	 {
		 case 1:
			 keyValue=1; //SNOOZE-PAUSE
			 break;
		 case 2:
			 keyValue=2; //VOL+
			 break;
		 case 4:
			 keyValue=3; //TIME-DIM
			 break;
		 case 8:
			 keyValue=4; //NEXT
			 break;
		 default:
			 break;
	 }
	 /*******************************************************************************
	 *���ܣ�"P1=0x1F(0001_1111)"�ȸ�ֵ��P1�ڣ�P15Ϊ0��P14Ϊ1�������(P10-P13)Ϊ1��Ȼ
	 * ���ٶ�P1�ڵ�ƽ(P1&0x0F)�����Ѹ���λ����0(P1&0x0F��������ʱ��P11�����£��Ƕ���
	 * ��P1�ڵ�ƽΪ0x0D(0000_1101),Ȼ����0x0F(0000_1111)���õ�0x02(0000_0010),
	 * readData2�ķ�ΧΪ1��2��4��8��keyValue�ķ�ΧΪ1~8��
	 *******************************************************************************/
	 P1=0x1F;
	 readData2=(P1&0x0F)^0x0F;
	 switch(readData2)
	 {
		 case 1:
			 keyValue=5; //ALARM
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
		 default:
			 break;
	 }
	 
	 return keyValue;
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
			case KU(K_SNOOZE_PAUSE)://�̰�
			{
				
				break;
			}
			case KH(K_SNOOZE_PAUSE)://����
			{
				
				break;
			}
			case KU(K_VOLINC): //�̰�//������ 
			case KR(K_VOLINC): //����//������
			{
				//������VOL+/NEXT������Сʱ���ٵ�����
				//������VOL+/NEXT����������λ�����ٵ�����
				if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_LONG_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Hour < 12)
					{
						gRTC_Hour++;
					}
				}
				else if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_SHORT_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Minute < 59)
					{
						gRTC_Minute++;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_LONG_ALARM_HOUR)
				{
					if (TYPE_Alarm1.tempHour < 12)
					{
						TYPE_Alarm1.tempHour++;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_MINUTE)
				{
					if (TYPE_Alarm1.tempMinute < 59)
					{
						TYPE_Alarm1.tempMinute++;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_ALMODE)
				{
					if (TYPE_Alarm1.Alarm_Mode == ALARM_BEEP)
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BT;
					}
					else
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BEEP;
					}
				}

				if (TYPE_Play_Mode == PLAY_IN_TIME)//����ʱģʽ������״̬��TF��
				{
					if (sys_Volume < 15)
					{
						sys_Volume++;
					}
				}
				break;
			}
			case KU(K_TIME_DIM): //�̰�//�̰������ַ���˸��
			{					
				if (TYPE_Play_Mode == PLAY_JUST_POWER)
				{
					TYPE_Flag_KSet = FLAG_KEYSET_JUST_POWER_SHORT_TIME;
				}
				else if (TYPE_Play_Mode == PLAY_IN_TIME)
				{
					TYPE_LED_Brightness--;
					if (TYPE_LED_Brightness == LED_TURN_OFF)//���������γ�ѭ��
					{
						TYPE_LED_Brightness = LED_HIGH;
					}
				}
				//�̰���TIME/DIM������������ʾ���ȣ���ѭ�������ߡ��С�������Ĭ��Ϊ������
				break;
			}
			case KR(K_TIME_DIM): //��ʱ
			{
				if (TYPE_Play_Mode == PLAY_JUST_POWER)
				{
					if (cntKeylong == 10)//����2sСʱ�ַ���˸
					{
						TYPE_Flag_KSet = FLAG_KEYSET_JUST_POWER_LONG_TIME;
					}
				}
				break;
			}
			case KU(K_NEXT): //�̰�
			case KR(K_NEXT): //����
			{
				//������VOL+/NEXT������Сʱ���ٵ�����
				//������VOL+/NEXT����������λ�����ٵ�����
				if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_LONG_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Hour < 12)
					{
						gRTC_Hour++;
					}
				}
				else if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_SHORT_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Minute < 59)
					{
						gRTC_Minute++;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_LONG_ALARM_HOUR)
				{
					if (TYPE_Alarm1.tempHour < 12)
					{
						TYPE_Alarm1.tempHour++;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_MINUTE)
				{
					if (TYPE_Alarm1.tempMinute < 59)
					{
						TYPE_Alarm1.tempMinute++;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_ALMODE)
				{
					if (TYPE_Alarm1.Alarm_Mode == ALARM_BEEP)
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BT;
					}
					else
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BEEP;
					}
				}
				break;
			}
			case KU(K_ALARM): //�̰�//����
			{
				//�̰���VOL+/NEXT������Сʱ������
				//�̰���VOL+/NEXT����������λ��������
				if (TYPE_Play_Mode == PLAY_IN_TIME)
				{
					//������ʾALARMʱ�䣬���ڻ�û��д������д������
					TYPE_Alarm1.enable = 1;//������
				}
				if (TYPE_Flag_KSet == FLAG_KEYSET_LONG_ALARM_HOUR)
				{
					//Ҫ�ȳ���ALARM��2s���ٶ̰�ALARM�������if���ܣ�Ϊ�������ӷ���ʱ��
					TYPE_Flag_KSet = FLAG_KEYSET_SHORT_ALARM_MINUTE;
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_MINUTE)
				{
					//Ҫ�ȶ̰�ALARM��������������Ū���ӹ��ܣ��ٶ̰�ALARM�������else-if���ܣ�Ϊѡ������ģʽ
					TYPE_Flag_KSet = FLAG_KEYSET_SHORT_ALARM_ALMODE;
					TYPE_Alarm1.Flag_Confirm_TimeCnt_30Sec = 2;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1
															   //��ȷ���������ñ�־λ)Ϊ2��30s��ʱ��־λ��
					timeCnt_30Sec = 0;
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_ALMODE)
				{
					//Ҫ�ȶ̰�ALARM������ѡ����������ģʽ���ٶ̰�ALARM�������else-if���ܣ�Ϊȷ���������û�
					//������30s�Զ����棬��������ʱģʽ������ʱ��60min
					//TYPE_Alarm1.Flag_Confirm_TimeCnt_30Sec = 1;//�̰�ALARM��ȷ�����û򲻶���30s�Զ����棬(Ϊ1
															   //��ȷ���������ñ�־λ)Ϊ2��30s��ʱ��־λ��
					TYPE_Alarm1.hour=TYPE_Alarm1.tempHour;    //ֱ��ȷ�ϰ���ʱ��alarmʱ�����������RTCʱ�ӶԱȵı���
					TYPE_Alarm1.minute=TYPE_Alarm1.tempMinute;
					timeCnt_30Sec = 0;
				}
				break;
			}
			case KH(K_ALARM): //����//����
			{
				//������VOL+/NEXT������Сʱ���ٵ�����
				//������VOL+/NEXT����������λ�����ٵ�����
				if (TYPE_Play_Mode == PLAY_IN_TIME)
				{
					if (cntKeylong > 10)
					{
						//ͬʱ�ַ���˸����û��д
						TYPE_Play_Mode = PLAY_ALARM;
						TYPE_Flag_KSet = FLAG_KEYSET_LONG_ALARM_HOUR;//Ϊ��������Сʱʱ��
					}
				}
				break;
			}
			case KU(K_VOLDEC): //�̰�//������
			case KR(K_VOLDEC): //����//������
			{
				//������VOL-/PREV������Сʱ���ٵݼ���
				//������VOL-/PREV����������λ�����ٵݼ���
				if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_LONG_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Hour > 0)
					{
						gRTC_Hour--;
					}
				}
				else if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_SHORT_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Minute > 0)
					{
						gRTC_Minute--;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_LONG_ALARM_HOUR)
				{
					if (TYPE_Alarm1.tempHour > 0)
					{
						TYPE_Alarm1.tempHour--;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_MINUTE)
				{
					if (TYPE_Alarm1.tempMinute > 0)
					{
						TYPE_Alarm1.tempMinute--;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_ALMODE)
				{
					if (TYPE_Alarm1.Alarm_Mode == ALARM_BEEP)
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BT;
					}
					else
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BEEP;
					}
				}

				if (TYPE_Play_Mode == PLAY_IN_TIME)//����ʱģʽ������״̬��TF��
				{
					if (sys_Volume > 0)
					{
						sys_Volume--;
					}
				}
				break;
			}
			case KU(K_BT): //�̰�
			{
				//�̰���VOL-/PREV������Сʱ�ݼ���
				//�̰���VOL-/PREV����������λ���ݼ���
				if (TYPE_Play_Mode != PLAY_IN_TIME_BT)
				{
					TYPE_Play_Mode = PLAY_IN_TIME_BT;
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
				//������VOL-/PREV������Сʱ���ٵݼ���
				//������VOL-/PREV����������λ�����ٵݼ���
				if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_LONG_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Hour > 0)
					{
						gRTC_Hour--;
					}
				}
				else if ((TYPE_Flag_KSet == FLAG_KEYSET_JUST_POWER_SHORT_TIME) && (TYPE_Play_Mode == PLAY_JUST_POWER))
				{
					if (gRTC_Minute > 0)
					{
						gRTC_Minute--;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_LONG_ALARM_HOUR)
				{
					if (TYPE_Alarm1.tempHour > 0)
					{
						TYPE_Alarm1.tempHour--;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_MINUTE)
				{
					if (TYPE_Alarm1.tempMinute > 0)
					{
						TYPE_Alarm1.tempMinute--;
					}
				}
				else if (TYPE_Flag_KSet == FLAG_KEYSET_SHORT_ALARM_ALMODE)
				{
					if (TYPE_Alarm1.Alarm_Mode == ALARM_BEEP)
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BT;
					}
					else
					{
						TYPE_Alarm1.Alarm_Mode = ALARM_BEEP;
					}
				}
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















