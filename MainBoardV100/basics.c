/*
 * Jun 16th, 2011
 *
 * Quadrotor Main Board
 * Basic Control Functions
 *
 * Some basic functions.
 *
 */

#include <p32xxxx.h>
#include "plib.h"

/* Function: Set_High
 *
 * Sets a specified bit as high
 *
 * Arguments:
 * bit_ - the bit to be set high
 *
 * Usage:
 * Set_High(LED1);
 *
 */
void Set_High(int *thebit)
{
	*thebit = 0x0010;
}

