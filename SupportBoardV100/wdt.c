/* Module for Setting WDT */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Initializes WDT */
void wdt_init(uint8_t scaller)
{
	WDTCSR |= (1 << WDE) | (1 << WDCE); // First Step in Setting Timer
	WDTCSR = (1 << WDE) | (scaller << WDP0); //Enables WDT and Sets Prescaller
}

void wdt_reset(void)
{
	__asm__ __volatile__ ("wdr");
}
	
	 
