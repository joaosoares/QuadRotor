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
	
	Init_All();
	
	while(1);
	
} 