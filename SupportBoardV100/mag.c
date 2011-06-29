/*	This module contains functions for initializing both the Magnetometer and SPI comunicaiton	**
**	it also contains functions for reading and writing to this sensor.							**
**	By Paulo Carvalho	V2.00																	*/

/* Include Necessary Headers */
#include <avr/io.h>
#include <util/delay.h>

/* Make Necessary Definitions */
/* Magnetometer Register Bits */
#define PS0 4
#define AS0 0

/* SPI Pins */
#define MISO 4 //PB4
#define MOSI 3 //PB3
#define SS 2 //PB2
#define SCK 5 //PB5
#define RESET 7 //PD7

/* Function for Initializing SPI */
void spi_init(void)
{
	/* Define Direction for SPI Ports: MOSI, SCK, SS, RESET OUTPUTS; MISO INPUT */
	DDRB |= (1 << MOSI) | (1 << SCK) | (1 << SS);
	DDRB &= ~(1 << MISO);
	DDRD |= (1 << RESET);

	/* SPI Enable, MSB First, Clock Idle Low, Sample First, FOSC / 16 */ 
	SPCR = (1 << SPE) | (0 << DORD) | (1 << MSTR) | (1 << SPR0); 
}

/* Function for Requesting reading. Can take up to 2ms to set interrupt */
void mag_read(char axis)
{
	/* Set Axis According to Table */
	axis++;
	/* Bring SSNOT Low */
	PORTB &= ~(1 << SS);

	/* Pulse Reset */
	PORTB |= (1 << RESET);
	_delay_us(1);
	PORTB &= ~(1 << RESET);
	_delay_us(1);

	/* Write Command */
	SPDR = (3 << PS0) | ((axis << AS0) & 0x03); 
}
