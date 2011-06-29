/* 	Main Module for the support board for the QuadRotor V2.  This module will call all functions in	  	**
** 	supplementary modules in correct order of execution to: Get Data from analog sensors, Gyro, Mag,  	**
** 	And Accelerometer; Process all data using designated filter to get reasonable tilt and rate data; 	**
**	Send all data to the MAIN board through a UART bus.  											  	**
**																										**
**	Notice that functions are all written in lower case letter, Definitions are all Capital Letter, 	**
**	and variables start with a capital letter at each segment.											**
**																										**
**	By Paulo Carvalho V2.00																				*/

/* Include Supplementary Header */
#include "main.h"

/* Main Execution Loop */
int main(void)
{
	/*	Starts all essential hardware features	*/
	initialize();

	/* Light Signal LED */
	PORTD = LEDOK; 

	/*	Sgnals Correct Execution of Previous Step	*/
	while(1)
	{
		/*	Resets WatchDog Timer to impede	program from stalling.	*/
		wdt_reset();
	}
}

/* Function for Initializing Essential Hardware Features */
void initialize(void)
{
	/* Initiates Comunication */
	uart_init();
	i2c_init();
	//spi_init();

	/* Initiates Sensors */
	gyro_init();
	accel_init();
	int_init();

	/* Starts WDT */
	wdt_reset();

	/* Set LED pins as Outputs */
	DDRD |= LEDOK;
	DDRD |= LEDS5;

	/* Make First Reading in Magnetometer */
	mag_read(Axis);
	
	/* Turn on Interrupts */
	sei();
}

/* Routine For Handling Received Serial Comunication */
ISR (USART_RX_vect)
{
	/*Temporarily Disable Interrupts */
	cli(); 		

	/* Only Store Data if First Packet is 255 */
	if (uart_read() == 0xFF)
	{
		switch(uart_read())
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

/* Gyro and Accelerometer Read Interrupt */
ISR (PCINT0_vect)
{	
	/* Temporarily Turn off Interrupts */
	cli();

	/* Take Action Based on Source of Interrupt*/ 
	switch(PINB & 0x03)
	{
		case (0x01): //Read Gyro
		gyro_read(&Gyro_Adc[0]);
		break;

		case (0x02): //Read Accel
		accel_read(&Accel_Adc[0]);
		break;

		case (0x03): //Read Gyro + Accel
		gyro_read(&Gyro_Adc[0]);		
		accel_read(&Accel_Adc[0]);
		break;

		default:
		break;
	}

	/* Turn Interrupts Back on */
	sei();
}
	
/* Timer Interrupt: Sends Data through UART every 1 second	*/
ISR (TIMER1_COMPA_vect)
{
	/* Temprorarily Turn Off Interrupts */
	cli();

	/* Declares Iterator Variable */
	int i;
	
	/* Send Data via UART to PIC */
	/* Refer to Serial Packet */
	/* Start Byte */
	uart_write(255);
	uart_write(255);
	uart_write(0);
	uart_write(255);
	uart_write(255);
	
	/* Tilt Rate */
	uart_write(1);
	for(i = 0; i < 3; i++)
	{
		uart_write2(Rate[i]);
	}

	/* Gyro Temperature */
	uart_write(2);
	uart_write2(Gyro_Adc[3]);

	/* Raw Data from Sensors */
	/* Gyro ADC */
	uart_write(3);
	for(i = 0; i < 3; i++)
	{
		uart_write2(Gyro_Adc[i]);
	}
	/* Accel ADC */
	uart_write(4);
	for(i = 0; i < 3; i++)
	{
		uart_write2(Accel_Adc[i]);
	}
	/* Magnetometer ADC */
	uart_write(5);
	for(i = 0; i < 3; i++)
	{
		uart_write2(Mag_Adc[i]);
	}

	/* Turn Interrupts Back on */
	sei();
}

/* Timer Interrupt: Runs Filter and Sends Data every 16ms	*/
ISR (TIMER2_COMPA_vect)
{
	PORTD |= LEDS5;
	/* Declares Iterator Variable */
	int i;

	/* Run Filter for Correcting Data */
	filter(&Angle[0], &Rate[0], &Gyro_Adc[0], &Accel_Adc[0]);
	
	/* Send Data via UART to PIC */
	/* Refer to Serial Packet */
	uart_write(255);
	uart_write(255);
	uart_write(255);
	
	for(i = 0; i < 3; i++)
	{
		uart_write2(Angle[i]);
	}

	PORTD &= ~LEDS5;
}
/* External Interrupt: Reads Magnetometer Data and sets to read next axis */
ISR (INT1_vect)
{	
	/* Read Data */
	Mag_Adc[Axis] = SPDR;

	/* Increment or Restart Axis Measurement */
	if(Axis >= 2) 
		Axis = 0;
	else
		Axis++;
	
	/* Order New Reading */
	mag_read(Axis);
}

	
