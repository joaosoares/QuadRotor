/* Module for Serial Peripheral Interface */

/* Include Proprietary Header File */
#include "spi.h"

/* Function for Initializing SPI */
void spi_init(void)
{
	/* Define Direction for SPI Ports: MOSI, SCK, SS, RESET OUTPUTS; MISO INPUT */
	DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
	DDRB &= ~(1 << MISO);
	DDRD |= (1 << RESET);

	/* Enable Interrupt, SPI Enable, MSB First, Clock Idle Low, Sample First, FOSC / 4 */ 
	SPCR = (1 << SPE) | (0 << DORD) | (1 << MSTR) | (0 << SPR0);
	
	/* Enable External Interrupt 1 for DRDY from MAG */
	EICRA |= (2 << ISC10); //Set to Falling Edge
	EIMSK |= (1 << INT1); //Turn on Interrupt 
}

/* Function for Sending Serial Data */
void spi_write(char data)
{
	/* Reset Magnetometer and Bring SS LOW */
	PORTD |= (1 << RESET);
	PORTB &= ~(1 << SS);
	_delay_us(5);
	PORTD &= ~(1 << RESET);
	_delay_us(5);
	
	/* Write Data on Register */
	SPDR = data;
	while( !(SPSR & (1 << SPIF)));
	// REQUIRES CHECKING AND COMPLETION!!!!!!!!!!!!!
}

uint16_t spi_read(void)
{
	uint16_t data = 0;
	/* Waits for Data to be Received */
	while( !(SPSR & (1 << SPIF)));

	/* Reads Received Data */
	data = (SPDR << 8);

	/* Wait for Second Byte and Read */
	while( !(SPSR & (1 << SPIF)));
	data |= (SPDR);

	/* Return Value */
	return data;
}

ISR (INT1_vect)
{
	/* Redeclare External Variable for Usage */
	uint16_t Mag_Data = 0;
	Mag_Data = spi_read();
}

