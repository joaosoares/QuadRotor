/* Main Module for Support Board */

/* Declare Used Headers */
#include "main.h"

int main(void)
{	
	initialize(); //Turns on all required Peripherals
	 
	_delay_ms(10); // 10 Millisecond Delay for Transition

	DDRD |= LEDOK | LEDS5; //Define LED Pins as Outputs
	PORTD |= LEDOK;

	/* Main Loop */
	while(1) 
	{
		wdt_reset();
		_delay_ms(100);
	}			
}

/* Routine for Initialization of Microcontroller Peripherals */
void initialize(void)
{
	/* Initialize Required Systems */
	
	/* Comunication */
	uart_init();
	spi_init(); 
	i2c_init();

	/* Sensors */
	gyro_init();
	accel_init();
	adc_init();
	
	/* Other */
	wdt_init(SCALLER); // Initializes WDT at 0.25 seconds
	interrupt_init();
	sei(); //Enable Interrupts
}

/* Gyro and Accelerometer Interrupt */
ISR (PCINT0_vect)
{	
	/* Take Action Based on Source of Interrupt*/ 
	switch(PINB & 0x03)
	{
		case (0x01): //Read Gyro
		gyro_read(&Gyro_Raw[0]);
		uart_write2(adc_read(2));
		break;

		case (0x02): //Read Accel
		accel_read(&Accel_Raw[0]);
		break;

		case (0x03): //Read Gyro + Accel
		gyro_read(&Gyro_Raw[0]);		
		accel_read(&Accel_Raw[0]);
		break;

		default:
		break;
	}
}



