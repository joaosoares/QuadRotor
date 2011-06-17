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
void Xbee_Init();
void SupportBoard_Init();
void Timer2_Init();
void PPM_Init();

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
void Set_High(int bit_)
{
	bit_ = 1;
}

/* Function: Init_All
 *
 * Initializes all components of the board.
 * No arguments.
 *
 * Usage:
 * main(){
 *	 Init_All();
 *
 */

void Init_All()
{
	INTEnableSystemMultiVectoredInt();
	Xbee_Init();
	SupportBoard_Init();
	Timer2_Init();
	PPM_Init();
}	
