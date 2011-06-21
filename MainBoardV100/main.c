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
	LED1_Off();
	LED2_Off();
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
	LED_Init();
	INTEnableSystemMultiVectoredInt();
	Xbee_Init();
	SupportBoard_Init();
	PPM1_Init();
	PPM2_Init();
	PPM4_Init();
	PPM3_Init();
	Counter_Init();
	
}	
