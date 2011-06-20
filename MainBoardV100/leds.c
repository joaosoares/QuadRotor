/*
 * Jun 16th, 2011
 *
 * Quadrotor Main Board
 * LED Control Modules
 *
 * Simple functions for LED Control. There are two LEDs on the board,
 * and each has three functions: initializing, on, and off.
 *
 */

#include "leds.h"

/* Function: LED_Init
 *
 * Sets the data direction of both LEDs through the TRIS register.
 * Also disables the Analog configs on the led on PORTB
 *
 * Usage:
 * LED_init();
 */
void LED_Init()
{
	AD1PCFG = ~LED2;
	TRISBCLR = LED2;
	TRISECLR = LED1;
	
}

/* Function: LED2_On
 *
 * Turns LED2 on.
 *
 * Usage:
 * LED2_On();
 */
void LED2_On()
{
	PORTBSET = LED2;
}

/* Function: LED1_On
 *
 * Turns LED1 on.
 *
 * Usage:
 * LED1_On();
 */
void LED1_On()
{
	PORTESET = LED1;
}

/* Function: LED2_Off
 *
 * Turns LED2 off.
 *
 * Usage:
 * LED2_Off();
 */
void LED2_Off()
{
	PORTBCLR = LED2;
}

/* Function: LED1_Off
 *
 * Turns LED1 off.
 *
 * Usage:
 * LED1_Off();
 */
void LED1_Off()
{
	PORTECLR = LED1;
}