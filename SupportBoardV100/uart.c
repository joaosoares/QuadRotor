/* Module for UART comunication */

#include "uart.h"

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

/* Reads Incoming UART Data */
char uart_read(void)
{
	/* Waits for Transmission Complete */
	while ( !(UCSR0A & (1 << RXC0)));
	
	/* Reads Data and Returns */
	return UDR0;
} 

/* Function for Transmiting Through UART */
void uart_write(char data)
{
	/* Waits for completion of previous transmission */
	while( !( UCSR0A & (1 << UDRE0)));

	/* Puts Data on buffer */
	UDR0 = data;
}

/* Function for Writing Ints Into UART */
void uart_write2(int data)
{
	/* Waits for completion of previous transmission */
	while( !( UCSR0A & (1 << UDRE0)));

	/* Puts Data on buffer */
	UDR0 = (char) data;

	/* Waits for completion of previous transmission */
	while( !( UCSR0A & (1 << UDRE0)));

	/* Puts Data on buffer */
	UDR0 = (char) (data >> 8);
}

/* Interrupt For Handling UART Reception (Receive Complete) */	 
ISR (USART_RX_vect)
{
	/*Temporarily Disable Interrupts */
	cli(); 

	/* Declare Variables */
	char Pic_Data = 0;

	/* Read UART Byte */
	Pic_Data = UDR0;		

	/* Only Store Data if First Packet is 255 */
	if (Pic_Data == 0xFF)
	{
		Pic_Data = uart_read();
		switch(Pic_Data)
		{
			case(0x55):
			//51564531
			break;
			case(0x45):
			//1264685135
			break;
			default:
			break;
		}
	}

	/* Reenable Interrupts */
	sei();
}	
