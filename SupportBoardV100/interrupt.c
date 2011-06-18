/* Module For dealing with Interrupt Routines */

#include "interrupt.h"

/* Activates External and Pin Interrupts */
void interrupt_init(void)
{
	gyro_interrupt_init();
	accel_interrupt_init();
}

/* Activates the PCINT Interrupt Used for Gyro */
void gyro_interrupt_init()
{
	/* Activates PCINT Interrupts from Pin 0 - 7 that are enabled in PCMSK */
	PCICR |= (1 << PCIE0);

	/* Activates Specific Interrupt */
	PCMSK0 |= (1 << PCINT0);
}

/* Activates the PCINT Interrupt Used for Accel */
void accel_interrupt_init()
{
	/* Activates PCINT Interrupts from Pin 0 - 7 that are enabled in PCMSK */
	PCICR |= (1 << PCIE0);

	/* Activates Specific Interrupt */
	PCMSK0 |= (1 << PCINT1);
}
