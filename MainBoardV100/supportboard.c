/*
 * Jun 16th, 2011
 *
 * Quadrotor Main Board
 * Support Board Communication Modules
 *
 * These modules serve to receive data from the Support Board (an
 * Atmega 328) via UART.
 *
 * There are two packet handlers:
 * One receives the data from the support board and the other sends data
 * to the support board as necessary.
 *
 * How I will implement the packet:
 * - Create a structure where every piece of data has its own variable
 * - Have a 
 *
 */


#include<p32xxxx.h>
#include "plib.h" 
#include "leds.h"

void Xbee_Write(char);
void PPM1_On(int);
//void LED1_On();

#define SUPPORT_BAUD 19 // 250kHz

char * datapacket;

/* Function: SupportBoard_Init
 *
 * Initialize the support board.
 * No arguments.
 *
 * Usage:
 * main(){
 *	 ...
 *	 SupportBoard_Init();
 *
 */
void SupportBoard_Init (void)
{
	// Placeholder for Xbee reset (as soon as timer routine is working)
	U1ABRG = SUPPORT_BAUD; // Set baud rate
	U1ASTA = 0; // Clear control register (reset)
	U1AMODE = 0x8008; //Enable UART for 8-bit, no parity, 1 stop bit
	U1ASTASET = 0x1400;
	mU1ASetIntPriority(3);
	INTEnableSystemMultiVectoredInt();
	mU1ARXIntEnable(1); // Enable RX interrupts for UART1A
	// Placeholder for ADC initializing
}

/* Function: SupportBoard_Write
 *
 * Sends a value to the Support Board via UART.
 * 
 * Arguments:
 * data - the data to be sent
 * 
 * Usage:
 * SupportBoard_Write('c');
 *
 */
void SupportBoard_Write(char data)
{
	while(U1ASTAbits.UTXBF);
	U1ATXREG = data;
}	

void __ISR(_UART_1A_VECTOR, ipl3) SupportBoard_Receive( void)
{
	char data = U1ARXREG;
//	Xbee_Write(data);
	//LED2_On();
	mU1ARXClearIntFlag();
}	

