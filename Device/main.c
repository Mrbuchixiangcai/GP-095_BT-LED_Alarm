//======================================================
// Main program routine
// - Device name  : MC96F6508A
// - Package type : 52LQFP
//======================================================
// For XDATA variable : V1.041.00 ~
#define		MAIN	1

// Generated    : Mon, Nov 05, 2018 (15:44:40)
#include	"MC96F6508A.h"
#include	"func_def.h"
#include    "app_main.h"

void main()
{
	cli();          	// disable INT. during peripheral setting
	port_init();    	// initialize ports
	clock_init();   	// initialize operation clock
	KeyINT_init();  	// initialize KEY interrupt
	LCD_init();     	// initialize LCD
	Timer0_init();  	// initialize Timer0
	Timer3_init();  	// initialize Timer3
	UART_init();    	// initialize UART interface
	WDT_init();     	// initialize Watch-dog timer
	WT_init();      	// initialize Watch timer
	sei();          	// enable INT.
	
	// TODO: add your main code here
	app_main();
	while(1);
}

//======================================================
// interrupt routines
//======================================================

void INT_UART_Rx() interrupt 9
{
	// UART Rx interrupt
	// TODO: add your code here
}

void INT_UART_Tx() interrupt 10
{
	// UART Tx interrupt
	// TODO: add your code here
}

void INT_Timer0() interrupt 13
{
	// Timer0 interrupt
	// TODO: add your code here
	Sys_Tick();
}

void INT_WT() interrupt 20
{
	// Watch timer interrupt
	// TODO: add your code here
	//这里变量gbHalfSecong的意思为半秒，是因为这个函数中断一次为0.5秒，
	gbHalfSecong=(!gbHalfSecong);
	if(gbHalfSecong)
	{
		if(++gRTC_Sec>59)
		{
			gRTC_Sec=0;
			if(++gRTC_Minute>59)
			{
				gRTC_Minute=0;
				if(++gRTC_Hour>23)
				{
					gRTC_Hour=0;
					gRTC_Week<<=1;
					if(gRTC_Week==0x80)//如果移位之后等于0x80，说明是第8次移位，这时候就是
						gRTC_Week=0x01;//周一，所以赋值为0x01。
				}
			}
		}
	}
}

//======================================================
// peripheral setting routines
//======================================================

unsigned char UART_read()
{
	unsigned char dat;
	
	while(!(UARTST & 0x20));	// wait
	dat = UARTDR;   	// read
	return	dat;
}

void KeyINT_init()
{
	// initialize KEY interrupt
	KPOL1 = 0x05;   	// edge : KEY INT.7~4
	KPOL0 = 0x55;   	// edge : KEY INT.3~0
}

void LCD_init()
{
	// initialize LCD
	// Frame freq. = 16.000000Hz
	LCDCRH = 0x00;  	// LCD control High
	LCDCRL = 0x00;  	// LCD control Low
	LCDCCR = 0x00;  	// LCD Contrast control
}

void Timer0_init()
{
	// initialize Timer0
	// 8bit timer, period = 1.008000mS
	T0CR = 0x92;    	// timer setting
	T0DR = 0x7D;    	// period count
	IE2 |= 0x02;    	// Enable Timer0 interrupt
	T0CR |= 0x01;   	// clear counter
}

void Timer3_init()
{
	// initialize Timer3
	// 8bit timer, period = 0.050000mS
	T3DR = 0x18;    	// period count
	T3CR = 0x8A;    	// timer setting
	T3CR |= 0x01;   	// clear counter
}

bit  enUart = 0;
void UART_init()
{
	// initialize UART interface
	// UART : 9615bps N 8 1
	if (!enUart)
	{
		UARTCR2  = 0x02; 	// activate UART
		UARTCR1  = 0x06; 	// bit count, parity
		UARTCR2 |= 0xEC;	// interrupt, speed
		UARTCR3  = 0x00; 	// stop bit
		UARTBD   = 0x67;  	// baud rate
		IE1     |= 0x18;    // enable UART interrupt
	}
	enUart = 1;
}

void UART_Def_Init()
{
	// initialize UART interface
	// UART : 9615bps N 8 1
	if (enUart)
	{
		UARTCR2  = 0x00; 	// activate UART
		UARTCR1  = 0x00; 	// bit count, parity
		UARTCR2 |= 0x00;	// interrupt, speed
		UARTCR3  = 0x00; 	// stop bit
		UARTBD   = 0x00;  	// baud rate
		IE1     &= (~0x18); // enable UART interrupt
	}
	enUart = 0;
}

void UART_write(unsigned char dat)
{
	while(!(UARTST & 0x80));	// wait
	UARTDR = dat;   	// write
}

void WDT_clear()
{
	WDTCR |= 0x20;  	// Clear Watch-dog timer
}

void WDT_init()
{
	// initialize Watch-dog timer
	WDTDR = 0x01;   	// period
	WDTCR = 0xC0;   	// setting
	//WDTCR |= 0x02;	// Use WDTRC
	WDT_clear();
}

void WT_init()
{
	// initialize Watch timer
	WTCR = 0x88;    	// setting
	WTDR = 0x01;    	// set duty
	WTDR = 0x81;    	// clear WT
	IE3 |= 0x04;    	// Enable WT interrupt
}

void clock_init()
{
	// internal RC clock (16.000000MHz)
	OSCCR = 0x28;   	// Set Int. OSC
	SCCR = 0x00;    	// Use Int. OSC
}

void port_init()
{
	// initialize ports
	//   1 : P13      in  
	//   2 : P14      out 
	//   3 : P15      out 
	//   8 : P60      out 
	//   9 : P61      out 
	//  11 : SXIN     out 
	//  12 : SXOUT    out 
	//  14 : P20      out 
	//  15 : P21      out 
	//  16 : P22      out 
	//  17 : P23      out 
	//  18 : P24      out 
	//  19 : P25      out 
	//  20 : P26      out 
	//  21 : P27      out 
	//  22 : P30      out 
	//  23 : P31      out 
	//  24 : P32      out 
	//  25 : P33      out 
	//  26 : P34      out 
	//  27 : P35      out 
	//  28 : P36      out 
	//  29 : P37      out 
	//  30 : P40      out 
	//  31 : P41      out 
	//  32 : P42      out 
	//  33 : P43      out 
	//  34 : P44      out 
	//  35 : P45      out 
	//  36 : P46      out 
	//  37 : P47      out 
	//  38 : P50      out 
	//  39 : P51      out 
	//  40 : P52      out 
	//  41 : P53      out BT_RED_OUTPUT
	//  42 : P54      out BT_RED_OUTPUT
	//  43 : P55      out BT_BLUE_INPUT
	//  44 : TXD      out 
	//  45 : RXD      in  
	//  46 : P00      in  
	//  47 : P01      out 
	//  48 : P02      out 
	//  49 : P03      out BT_RED_INPUT
	//  50 : P10      in  
	//  51 : P11      in  
	//  52 : P12      in  
	P0IO = 0xFE;    	// direction
	P0PU = 0x00;    	// pullup
	P0OD = 0x00;    	// open drain
	P0DB = 0x00;    	// bit7~6(debounce clock), bit1~0=P01~00 debounce
	P0   = 0x00;    	// port initial value

	P1IO = 0xF0;    	// direction
	P1PU = 0x3F;    	// pullup
	P1OD = 0x00;    	// open drain
	P1DB = 0x00;    	// P17~10 debounce
	P1   = 0x00;    	// port initial value

	P2IO = 0xFF;    	// direction
	P2PU = 0xFF;    	// pullup
	P2OD = 0x00;    	// open drain
	P2   = 0x00;    	// port initial value

	P3IO = 0xFF;    	// direction
	P3PU = 0xFF;    	// pullup
	P3OD = 0x00;    	// open drain
	P3   = 0x00;    	// port initial value

	P4IO = 0xFF;    	// direction
	P4PU = 0xFF;    	// pullup
	P4OD = 0x00;    	// open drain
	P4   = 0x00;    	// port initial value

	P5IO = 0x7F;    	// direction
	P5PU = 0x00;    	// pullup
	P5OD = 0x00;    	// open drain
	P5   = 0x00;    	// port initial value

	P6IO = 0xFF;    	// direction
	P6PU = 0x01;    	// pullup
	P6OD = 0x00;    	// open drain
	P6   = 0x00;    	// port initial value

	// Set port functions
	P0FSR = 0x00;   	// P0 selection
	P2FSR = 0x00;   	// P2 selection
	P3FSR = 0x00;   	// P3 selection
	P4FSR = 0x00;   	// P4 selection
	P5FSRH = 0x18;  	// P5 selection High
	P5FSRL = 0x00;  	// P5 selection Low
	P6FSR = 0x0C;   	// P6 selection
}

