/*
 * Quadrotor Main Board
 * Main Module
 * 
 * Jun 16th, 2011
 */

#include "main.h"

main()
{
	//Config LED1 for output
	TRISECLR = 0x0020;
	//Config PORTb for LED2 digital output
	AD1PCFG = 0x7fff;
	TRISBCLR = 0x8000;
	Init_All();
	Set_High(&PORTE);
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
}	
