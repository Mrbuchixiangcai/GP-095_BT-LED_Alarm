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
uint8_t  triger;
uint8_t  count;
uint8_t  Matrix_Buttons(void)
 {
	 uint8_t  readData1,readData2;
	 uint8_t  keyValue;
	 keyValue=0;//如果没有按键按下就是返回0
	 
	 /*******************************************************************************
	 *功能："P1=0x2F(0010_1111)"先赋值给P1口，P15为1，P14为0，输入端(P10-P13)为1，然
	 * 后再读P1口电平(P1&0x0F)，并把高四位都清0(P1&0x0F，假如这时候P10被按下，那读到
	 * 的P1口电平为0x0E(0000_1110),然后与0x0F(0000_1111)异或得到0x01(0000_0001),
	 * readData1的范围为1~4，keyValue的范围为1~8。
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
		 case 3:
			 keyValue=3; //TIME-DIM
			 break;
		 case 4:
			 keyValue=4; //NEXT
			 break;
		 default:
			 break;
	 }
	 /*******************************************************************************
	 *功能："P1=0x1F(0001_1111)"先赋值给P1口，P15为0，P14为1，输入端(P10-P13)为1，然
	 * 后再读P1口电平(P1&0x0F)，并把高四位都清0(P1&0x0F，假如这时候P11被按下，那读到
	 * 的P1口电平为0x0D(0000_1101),然后与0x0F(0000_1111)异或得到0x02(0000_0010),
	 * readData2的范围为1~4，keyValue的范围为1~8。
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
		 case 3:
			 keyValue=7; //BT
			 break;
		 case 4:
			 keyValue=8; //PREV
			 break;
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
			case KU(K_SNOOZE_PAUSE)://短按
			{
				
				break;
			}
			case KH(K_SNOOZE_PAUSE)://长按
			{
				
				break;
			}
			case KU(K_VOLINC): //短按//音量加 
			{
				//短按“VOL+/NEXT”键，小时递增，
				//短按“VOL+/NEXT”键，分钟位数递增，
				break;
			}
			case KR(K_VOLINC): //长按//音量加
			{
				//长按“VOL+/NEXT”键，小时快速递增。
				//长按“VOL+/NEXT”键，分钟位数快速递增。
				break;
			}
			case KU(K_TIME_DIM): //短按//短按分钟字符闪烁，
			{					 //短按“TIME/DIM”键，调整显示亮度，可循环调整高、中、低亮（默认为高亮）
				break;
			}
			case KR(K_TIME_DIM) //计时
			{
				if(cntKeylong==10)//长按2s小时字符闪烁
				{
					
				}
				break;
			}
			case KU(K_NEXT): //短按
			{
				//短按“VOL+/NEXT”键，小时递增，
				//短按“VOL+/NEXT”键，分钟位数递增，
				break;
			}
			case KH(K_NEXT): //长按
			{
				//长按“VOL+/NEXT”键，小时快速递增。
				//长按“VOL+/NEXT”键，分钟位数快速递增。
				break;
			}
			case KU(K_ALARM): //短按//闹钟
			{
				//短按“VOL+/NEXT”键，小时递增，
				//短按“VOL+/NEXT”键，分钟位数递增，
				break;
			}
			case KH(K_ALARM): //长按//闹钟
			{
				//长按“VOL+/NEXT”键，小时快速递增。
				//长按“VOL+/NEXT”键，分钟位数快速递增。
				break;
			}
			case KU(K_VOLDEC): //短按//音量减
			{
				//短按“VOL-/PREV”键，小时递减，
				//短按“VOL-/PREV”键，分钟位数递减，
				
				sys
				break;
			}
			case KR(K_VOLDEC): //长按//音量减
			{
				//长按“VOL-/PREV”键，小时快速递减；
				///长按“VOL-/PREV”键，分钟位数快速递减；
				break;
			}
			case KU(K_BT): //短按
			{
				//短按“VOL-/PREV”键，小时递减，
				//短按“VOL-/PREV”键，分钟位数递减，
				break;
			}
			case KH(K_BT): //长按
			{
				//长按“VOL-/PREV”键，小时快速递减；
				//长按“VOL-/PREV”键，分钟位数快速递减；
				break;
			}
			case KU(K_PREV): //短按
			{
				//短按“VOL-/PREV”键，小时递减，
				//短按“VOL-/PREV”键，分钟位数递减，
				break;
			}
			case KH(K_PREV): //长按
			{
				//长按“VOL-/PREV”键，小时快速递减；
				//长按“VOL-/PREV”键，分钟位数快速递减；
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















