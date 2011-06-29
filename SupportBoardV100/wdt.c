/*	This Module Starts the Watch Dog Timer and Contains the Function	**
**	for reseting the timer to impede a reset condition.					**
**	By Paulo Carvalho V2.00												*/

/* Include Required Headers */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Define Scaller Through Calculation */
/* A 4 defines WDT to 0.25ms		  */
#define SCALLER 4

/* Initializes WDT */
void wdt_init(void)
{
	WDTCSR |= (1 << WDE) | (1 << WDCE); // First Step in Setting Timer
	WDTCSR = (1 << WDE) | (SCALLER << WDP0); //Enables WDT and Sets Prescaller
}

/* Resets Watch Dog Timer */
void wdt_reset(void)
{
	__asm__ __volatile__ ("wdr");
}
