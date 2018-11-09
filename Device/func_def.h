//======================================================
// Function and global variables definition
//======================================================

void port_init();             	// initialize ports
void clock_init();            	// initialize operation clock
void KeyINT_init();           	// initialize KEY interrupt
void LCD_init();              	// initialize LCD
void Timer0_init();           	// initialize Timer0
void Timer3_init();           	// initialize Timer3
void UART_init();             	// initialize UART interface
void UART_Def_Init()
void UART_write(unsigned char dat);	// write UART
unsigned char UART_read();    	// read UART
void WDT_init();              	// initialize Watch-dog timer
void WDT_clear();             	// Clear Watch-dog timer
void WT_init();               	// initialize Watch timer

