/* 	Module Initiates all external and Timer based interrupt routines	**
**	Timers timing can be changed through supplementary header 			*/

/* Include Supplementary Header */
#include "interrupt.h"

/* Activates External and Pin Interrupts */
void int_init(void)
{
	gyro_interrupt_init();
	accel_interrupt_init();
	//mag_interrupt_init();
	timer1_interrupt_init();
	timer2_interrupt_init();
}

/* Activates the PCINT Interrupt Used for Gyro */
void gyro_interrupt_init(void)
{
	/* Activates PCINT Interrupts from Pin 0 - 7 that are enabled in PCMSK */
	PCICR |= (1 << PCIE0);

	/* Activates Specific Interrupt */
	PCMSK0 |= (1 << PCINT0);
}

/* Activates the PCINT Interrupt Used for Accel */
void accel_interrupt_init(void)
{
	/* Activates PCINT Interrupts from Pin 0 - 7 that are enabled in PCMSK */
	PCICR |= (1 << PCIE0);

	/* Activates Specific Interrupt */
	PCMSK0 |= (1 << PCINT1);
}

/* Activates the INT1 Interrupt for Magnetometer DRDY */
void mag_interrupt_init(void)
{
	/* Set Interrupt on falling edge */
	EICRA |= (2 << ISC10);

	/* Activate Interrupt */
	EIMSK |= (1 << INT1);
}

/* Initiates Timer that Controls Data Sending Every 1 Second*/
void timer1_interrupt_init(void)
{
	/* Guarantee Pins to be Disconected from Timer */
	TCCR1A = 0x00;

	/* Set 16 bit timer to CTC mode with TOP at OCR1A */
	TCCR1B = (1 << WGM12);

	/* Set TOP Value for Counter */
	OCR1A = TIMER1TOP;	

	/* Resets Timer */
	TCNT1 = 0x0000;

	/* Set Interrupt on TOP Based on OCIE1A */
	TIMSK1 = (1 << OCIE1A);

	/* Set Prescaller to FOSC / 256 */
	TCCR1B |= (4 << CS10);
}

/* Initiates Timer That Will Control Filter Execution Every 16ms */
void timer2_interrupt_init(void)
{
	/* Guarantee Pins to be Disconected from timer */
	TCCR2A = 0x00;

	/* Sets to CTC */
	TCCR2B = (1 << WGM22);

	/* Sets Compare Value */
	OCR2A = TIMER2TOP;

	/* Sets Interrupt */
	TIMSK2 = (1 << OCIE2A);
	
	/* Sets Timer to 0 */
	TCNT2 |= 0x00;

	/* Defines Clock (FOSC / 1024) Therefore Starting timer */
	TCCR2B |= (7 << CS20);
}  
