/*
 * Quadrotor Main Board
 * Main Module
 * 
 * Jun 16th, 2011
 */

#include "main.h"

main()
{
	Init_All();
	
	//LED1_On();
	while(1)
	{
		
	}	
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
	Timer1_Init();
	PPM_Init();
	LED_Init();
	
}	
