/* Module for Analog to Digital Conversion Functions */

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t stop = 0;

/* Function to Initialize ADC */
void adc_init(void)
{
	ADCSRA = (1 << ADEN) | (7 << ADPS0);
}

/* Function for Reading ADC */
int adc_read(char channel)
{
	int data; //Variable to Store Read Data
	ADMUX = (0x0F & (channel << MUX0)); //Select ADC Pin to Read with Safety Mask
	ADCSRA = (1 << ADSC); //Starts Conversion and Enables Interrupt
	while( ! (ADCSRA & (1 << ADSC))); //Holds Program Until Conversion is Done
	stop = 0;
	/* Read Data */
	data = (ADCL);
	data |= (ADCH << 8);

	return data; //Return Data
}

		 
