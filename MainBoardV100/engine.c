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

/* Function: PPM2_Init
 *
 * Initializes the 1st PPM, setting data direction as output (TRIS)
 * No arguments. Uses Timer 3, configuring it for interrupts.
 *
 * Usage:
 * PPM2_Init(); 
 */
void PPM2_Init()
{
	mT3ClearIntFlag();
	mT3SetIntPriority(4);
	mT3IntEnable(1);
	TRISDCLR = PPM2TRIS;
	PPM2=0;
	PPM2_On(500);
}

/* Function: PPM2_On
 *
 * Puts the PPM high and after a specified amount of microseconds
 * lowers it again.
 * 
 * Arguments:
 * duration - the amount in microseconds of the pulse
 */
void PPM2_On (int duration)
{
	int period = (duration*20000000)/(1*1000000); //Formula to convert to microseconds: (prescaler)/(pbc)* 10e6
	PR3 = period;
	TMR3 = 0x00;
	T3CONbits.ON = 1; // Turn timer on
	PPM2 = 1; // PPM2 is high
}	

/* Function: PPM2_Interrupt
 *
 * Handles the interrupt created when Timer3 was activated for PPM2. 
 * Then, turns off the timer and resets it.
 */
void __ISR(_TIMER_3_VECTOR, ipl4) PPM2_Interrupt (void)
{
	PPM2 = 0;
	T3CONbits.ON = 0; // Disable timer
	TMR3 = 0; // Clear timer
	mT3ClearIntFlag();
}

/* Function: PPM3_Init
 *
 * Initializes the 1st PPM, setting data direction as output (TRIS)
 * No arguments. Uses Timer 4 configuring it for interrupts.
 *
 * Usage:
 * PPM3_Init(); 
 */
void PPM3_Init() // Some actions deactivated b/c of conflict w/ reset
{
	mT4ClearIntFlag();
	mT4SetIntPriority(4);
	mT4IntEnable(1);
	TRISDCLR = PPM3TRIS;
	PPM3=0;
	PPM3_On(500);
}

/* Function: PPM3_On
 *
 * Puts the PPM high and after a specified amount of microseconds
 * lowers it again.
 * 
 * Arguments:
 * duration - the amount in microseconds of the pulse
 */
void PPM3_On (int duration) // actions off b/c of reset conflict
{
	int period = (duration*20000000)/(1*1000000); //Formula to convert to microseconds: (prescaler)/(pbc)* 10e6
	PR4 = period;
	TMR4 = 0x00;
	T4CONbits.ON = 1; // Turn timer on
	PPM3 = 1; // PPM3 is high
}	

/* Function: PPM3_Interrupt
 *
 * Handles the interrupt created when Timer4 was activated for PPM3. 
 * Then, turns off the timer and resets it.
 */
void __ISR(_TIMER_4_VECTOR, ipl4) PPM3_Interrupt (void)
{
	PPM3 = 0;
	T4CONbits.ON = 0; // Disable timer
	TMR4 = 0; // Clear timer
	mT4ClearIntFlag();
}

/* Function: PPM4_Init
 *
 * Initializes the 4th PPM, setting data direction as output (TRIS)
 * No arguments. Uses Timer 5, configuring it for interrupts.
 *
 * Usage:
 * PPM4_Init(); 
 */
void PPM4_Init()
{
	mT5ClearIntFlag();
	mT5SetIntPriority(4);
	mT5IntEnable(1);
	TRISDCLR = PPM4TRIS;
	PPM4=0;
	PPM4_On(500);
}

/* Function: PPM4_On
 *
 * Puts the PPM high and after a specified amount of microseconds
 * lowers it again.
 * 
 * Arguments:
 * duration - the amount in microseconds of the pulse
 */
void PPM4_On (int duration)
{
	int period = (duration*20000000)/(1*1000000); //Formula to convert to microseconds: (prescaler)/(pbc)* 10e6
	PR5 = period;
	TMR5 = 0x00;
	T5CONbits.ON = 1; // Turn timer on
	PPM4 = 1; // PPM4 is high
}	

/* Function: PPM4_Interrupt
 *
 * Handles the interrupt created when Timer5 was activated for PPM4. 
 * Then, turns off the timer and resets it.
 */
void __ISR(_TIMER_5_VECTOR, ipl4) PPM4_Interrupt (void)
{
	PPM4 = 0;
	T5CONbits.ON = 0; // Disable timer
	TMR5 = 0; // Clear timer
	mT5ClearIntFlag();
}



/* Pairs of engines

	   ------ PAIR B -----
	  /					  \
	 /					   \
	/		(Engine 1) -----\-------
   /			||		     \		 \
  /				||			  \		  \
 /				||			   \	   \
(Engine 2) =====||===== (Engine 4)	 PAIR A
				||					   /
				||					  /
				||					 /
			(Engine 3) -------------

 * Each pair has a set of actions. Each time an function for one
 * of its actions is called, it will adjust each engine of the
 * pair according to the rotation strenght needed. These sets
 * of action then combine to form a higher-level set for the entire
 * QuadRotor (going up, down, yaw, pitch, roll)
 *
 * Actions to be made by each pair:
 * 
 */

/* Function: PairA_Pitch
 Strength in %

*/ 
void PairA_Pitch(int strength, int duration)
{
	int PPM_Max = 1800;
	int PPM_Min = 900;
	PPM1_On(900);
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
