/*
 * Jun 16th, 2011
 *
 * Quadrotor Main Board
 * Modules for Engine Control
 *
 * Timer based modules for Pulse Position Modulation.
 * Each engine has its own timer interrupt module.
 * This low level module is used by other modules to form pairs of
 * motors that can do simple actions.
 * Then, these actions will be used for PID control based on the
 * desired angle (received by the Xbee) and the current angle
 * (received from support board).
 * 
 * 
 */

#include "engine.h"

/* Function: PPM1_Init
 *
 * Initializes the 1st PPM, setting data direction as output (TRIS)
 * No arguments. Uses Timer 2, configuring it for interrupts.
 *
 * Usage:
 * PPM1_Init(); 
 */
void PPM1_Init()
{
	mT2ClearIntFlag();
	mT2SetIntPriority(4);
	mT2IntEnable(1);
	TRISDCLR = PPM1TRIS;
	PPM1=0;
	PPM1_On(500);
}

/* Function: PPM1_On
 *
 * Puts the PPM high and after a specified amount of microseconds
 * lowers it again.
 * 
 * Arguments:
 * duration - the amount in microseconds of the pulse
 */
void PPM1_On (int duration)
{
	int period = (duration*20000000)/(1*1000000); //Formula to convert to microseconds: (prescaler)/(pbc)* 10e6
	PR2 = period;
	TMR2 = 0x00;
	T2CONbits.ON = 1; // Turn timer on
	PPM1 = 1; // PPM1 is high
}	

/* Function: PPM1_Interrupt
 *
 * Handles the interrupt created when Timer2 was activated for PPM1. 
 * Then, turns off the timer and resets it.
 */
void __ISR(_TIMER_2_VECTOR, ipl4) PPM1_Interrupt (void)
{
	PPM1 = 0;
	T2CONbits.ON = 0; // Disable timer
	TMR2 = 0; // Clear timer
	mT2ClearIntFlag();
}

/* DEPRECATED FUNCTION -- didn't work
 * 
 * Function: PPM1_Poll
 *
 * If PPM1 is low, start the timer to space between the interrupts.
 * When around an user defined number of milliseconds have ellapsed
 * it calls the PPM1_On function.
 * To calculate the time ellapsed, it "forks" the time from Timer1
 * at some point and constantly compares to the current T1 position.
 * When the difference, converted to milliseconds, is more than the
 * specified, it calls the PPM1_On function, clears the difference
 * counter, waits for the PPM to be low again, and starts over.
 *
 * Arguments:
 * millis - the time in milliseconds between the PPM1_On functions.
 *
 * Usage:
 * while(1){
 *	 PPM1_Poll(20);
 *	 ...
 *
 *
void PPM1_Poll(int millis)
{
	int time = (millis * 20000000) / (64 * 1000); // Formula is Pcb / Prescaler * 10e3 (a millisecond)
	while(TMR1 - delay_fork > time);
	PPM1_On(900);
	delay_fork = TMR1;
}
 */
