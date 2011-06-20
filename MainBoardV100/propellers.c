/*
 * Jun 16th, 2011
 *
 * Quadrotor Main Board
 * Modules for Propeller Control
 *
 * Timer based modules for Pulse Position Modulation.
 * Each propeller has its own timer interrupt module.
 * This low level module is used by other modules to form pairs of
 * motors that can do simple actions.
 * Then, these actions will be used for PID control based on the
 * desired angle (received by the Xbee) and the current angle
 * (received from support board).
 * 
 * 
 */

//Necessary includes
#include <p32xxxx.h>
#include "plib.h"
#include "pid.h"

#define PRESCALER 4
#define PPM1 PORTDbits.RD7
#define PPM1TRIS 0x0080 // Port D 7: 0000 0000 1000 0000

void PPM1_On(int);
//Variables for PPM
int delay_fork = 0;

/* Function: Timer1_Init
 *
 * Starts Timer 1, with interrupts disabled and period register maximum
 *
 */

/* Function: Timer2_Interrupt
 *
 * Handles the interrupt created when Timer2 was activated. Then, turns
 * off the timer and resets it.
 * 
 */
void __ISR(_TIMER_2_VECTOR, ipl4) Timer2_Interrupt (void)
{
	PPM1 = 0;
	T2CONbits.ON = 0; // Disable timer
	TMR2 = 0; // Clear timer
	mT2ClearIntFlag();
}	

/* Function: Timer1_Interrupt
 *
 * Handles the interrupt for Timer 1, turning PPM high.
 *
 */
void __ISR(_TIMER_1_VECTOR, ipl4) Timer1_Interrupt (void)
{
	PPM1 = 1;
	PPM1_On(1500);
	mT1ClearIntFlag();
}	

/* Function: PPM_Init
 *
 * Initializes the 4 PPM, setting data direction as output (TRIS)
 * No arguments.
 *
 * Usage:
 * PPM_Init();
 *
 */
void PPM_Init()
{
	mT2ClearIntFlag();
	mT2SetIntPriority(4);
	mT2IntEnable(1);
	TRISDCLR = PPM1TRIS;
	PPM1=0;
}	

/* Function: PPM1_On
 *
 * Puts the PPM high and after a specified amount of microseconds
 * lowers it again.
 * 
 * Arguments:
 * duration - the amount in microseconds of the pulse
 *
 */
void PPM1_On (int duration)
{
	int period = (duration*20000000)/(1*1000000); //Formula to convert to microseconds: (prescaler)/(pbc)* 10e6
	PR2 = period;
	TMR2 = 0x00;
	T2CONbits.ON = 1; // Turn timer on
	PPM1 = 1; // PPM1 is high
}	

/* Function: Timer1_Init
 * 
 * Starts Timer 1 with a high prescaler so it can measure milliseconds.
 * No arguments
 *
 * Usage:
 * Timer1_Init();
 *
 */
void Timer1_Init()
{
	T1CON = 0;
	T1CONSET = 0x0020;
	TMR1 = 0x00;
	PR1 = (20 * 20000000) / (64*1000);
	T1CONbits.ON = 1;
	mT1SetIntPriority(4);
	mT1IntEnable(1);
}	

/* Function: PPM1_Poll
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
 */
void PPM1_Poll(int millis)
{
	int time = (millis * 20000000) / (64 * 1000); // Formula is Pcb / Prescaler * 10e3 (a millisecond)
	while(TMR1 - delay_fork > time);
	PPM1_On(900);
	delay_fork = TMR1;
}	
