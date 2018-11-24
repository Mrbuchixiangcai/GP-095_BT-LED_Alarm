/*******************/
/*ͷ�ļ�header file*/
/*******************/
#include "app_main.h"
#include "led_drive.h"
/************************/
/*�궨��macro definition*/
/************************/

/*************************/
/*���Ͷ���byte definition*/
/*************************/

/****************************/
/*��־λ����flags definetion*/
/****************************/

/*****************************/
/*��������variable definition*/
/*****************************/
uint8_t  value;
uint8_t  cur_Value;
uint8_t  user_Value;
uint8_t  sum_Value;
uint8_t  light_Brightness;//����
uint8_t  cntBT_BTTF_Switchover;//�л�tf������������ʱ���50ms�����������
uint16_t  cntJustPower_Delay;//�����ϵ���ʱ����5s
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
* ��ע��
*******************************************************************************/
void LED_Deive(void)
{
    if (--value == 0)
    {
        _SET_1B(0);
        _SET_1C(0);
        _SET_2A(0);
        _SET_2B(0);
        _SET_2C(0);
        _SET_2D(0);
        _SET_2E(0);
        _SET_2F(0);
        _SET_2G(0);
        _SET_3A(0);
        _SET_3B(0);
        _SET_3C(0);
        _SET_3D(0);
        _SET_3E(0);
        _SET_3F(0);
        _SET_3G(0);
        _SET_4A(0);
        _SET_4B(0);
        _SET_4C(0);
        _SET_4D(0);
        _SET_4E(0);
        _SET_4F(0);
        _SET_4G(0);
        _SET_APM(0);
        _SET_AL(0);
        _SET_COL1(0);
        _SET_COL2(0);
        _SET_BT_BLUE(0);
		_SET_BT_RED(0);
    }
    if(--sum_Value==0)
    {
        if(LED_Brightness_TypeDef == LED_LOW)
        {
			
          value=100;
        }
        else if (LED_Brightness_TypeDef == LED_MEDIUM)
        {
            value = 175;
        }
        else if (LED_Brightness_TypeDef == LED_HIGH)
        {
            value = 255;
        }
        if (value)
        {
            _SET_1B(Flag_SET_1B);
            _SET_1C(Flag_SET_1C);
            _SET_2A(Flag_SET_2A);
            _SET_2B(Flag_SET_2B);
            _SET_2C(Flag_SET_2C);
            _SET_2D(Flag_SET_2D);
            _SET_2E(Flag_SET_2E);
            _SET_2F(Flag_SET_2F);
            _SET_2G(Flag_SET_2G);
            _SET_3A(Flag_SET_3A);
            _SET_3B(Flag_SET_3B);
            _SET_3C(Flag_SET_3C);
            _SET_3D(Flag_SET_3D);
            _SET_3E(Flag_SET_3E);
            _SET_3F(Flag_SET_3F);
            _SET_3G(Flag_SET_3G);
            _SET_4A(Flag_SET_4A);
            _SET_4B(Flag_SET_4B);
            _SET_4C(Flag_SET_4C);
            _SET_4D(Flag_SET_4D);
            _SET_4E(Flag_SET_4E);
            _SET_4F(Flag_SET_4F);
            _SET_4G(Flag_SET_4G);
            _SET_APM(Flag_SET_APM);
            _SET_AL(Flag_SET_AL);
            _SET_COL1(Flag_SET_COL1);
            _SET_COL2(Flag_SET_COL2);
			_SET_BT_BLUE(Flag_SET_BT_BLUE);
			_SET_BT_RED(Flag_SET_BT_RED);
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
void TF_Check(void)
{
	cntJustPower_Delay++;
	if(cntJustPower_Delay<500)//5s�������ϵ��ӳ�5s
		return;
	cntJustPower_Delay=500;
	if((TF_CARD_DET())==0)//Ϊ0˵��������TF��
	{
		if(Music_Mode_TypeDef == MUSIC_BT)
		{
			//Music_Mode_TypeDef=MUSIC_TF;
			bt_cmd=BT_SDO;//��������TF������
			//BT_Send_CMD(BT_TF_CARD);//�л���TF��ģʽ
			cntBT_BTTF_Switchover++;
			if(cntBT_BTTF_Switchover>=5)//50ms//BT_TF_CARD��BT_SDO����������30ms����
			{
				cntBT_BTTF_Switchover=0;
				Music_Mode_TypeDef=MUSIC_TF;
				bt_cmd=BT_TF_CARD;//�л���TF��ģʽ
			}
		}
	}
	else
	{
		if(Music_Mode_TypeDef == MUSIC_TF)//תΪ��������û��tf��ģʽֻ����һ�Σ���ΪҪ�������ݣ�����һֱ����
		{
			//Music_Mode_TypeDef=MUSIC_BT;
			bt_cmd=BT_SDF;//��������TF������
			//BT_Send_CMD(BT_MODE);//�л�������ģʽ
			cntBT_BTTF_Switchover++;
			if(cntBT_BTTF_Switchover>=5)//50ms//BT_TF_CARD��BT_SDO����������30ms����
			{
				cntBT_BTTF_Switchover=0;
				Music_Mode_TypeDef=MUSIC_BT;
				bt_cmd=BT_MODE;//�л�������ģʽ
			}
		}
	}
}











