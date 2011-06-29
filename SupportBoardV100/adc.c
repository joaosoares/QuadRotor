/*	Module for Analog to Digital Conversion Initialization and Read Functions 	**
**	By Paulo Carvalho V2.00														*/ 

/* Make Necessary Inclusions of Headers */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Declare Variable */
/* Variable to Store Read Data */
int data; 

/* Function to Initialize ADC */
void adc_init(void)
{
	ADCSRA = (1 << ADEN) | (7 << ADPS0);
}

/* Function for Reading ADC */
int adc_read(char channel)
{
	/* Select ADC Pin to Read with Safety Mask */
	ADMUX = (0x0F & (channel << MUX0)); 

	/* Starts Conversion and Enables Interrupt */
	ADCSRA = (1 << ADSC); 

	/* Holds Program Until Conversion is Done */
	while( ! (ADCSRA & (1 << ADSC))); 

	/* Read Data */
	data = (char)(ADCL);
	data |= (char)(ADCH << 8);
	
	/* Return ADC Data */
	return data; 
}

		 
