/*	Module for initializing and comunicating through Serial UART with the PIC32MX	**
**	in the main board.																**
**																					**
**	By Paulo Carvalho V2.00															*/

/************************************************************************************/
/* Include Necessary Headers */
#include <avr/io.h>

/* Make Necessary Definitions */
/* Crystal Oscilator in Herts */
#define FOSC 16000000

/* Data Rate for UART comunication */
#define BAUD 250000

/* Calculates Prescaller For UART Speed */
#define MYUBRR FOSC / 16 / BAUD - 1 

/************************************************************************************/
/* Initializes UART	*/
void uart_init(void)
{
	/* Set Baud Rate */
	UBRR0H = (char) (MYUBRR >> 8);
	UBRR0L = (char) (MYUBRR);

	/* Set Frame Format: 8 Data, 1 Stop, No Parity */
	UCSR0C = (0 << UPM00) | (0 << USBS0) | (3 << UCSZ00);

	/* Enable TX and RX + RX Interrupt */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}

/* Reads Uart Data (When Called From Interrupt) */	
char uart_read(void)
{	
	/* Reads Data and Returns */
	return UDR0;
} 

/* Write Data to UART when a "char" */
void uart_write(char data)
{
	/* Waits for completion of previous transmission */
	while( !( UCSR0A & (1 << UDRE0)));

	/* Puts Data on buffer */
	UDR0 = data;
}

/* Write Data to UART when an "int" */
void uart_write2(int data)
{
	/* Waits for completion of previous transmission */
	while( !( UCSR0A & (1 << UDRE0)));

	/* Puts Lower Byte into Buffer */
	UDR0 = (char)(data);

	/* Waits for completion of previous transmission */
	while( !( UCSR0A & (1 << UDRE0)));

	/* Puts Higher Byte into Buffer */
	UDR0 = (char)(data << 8);
}

