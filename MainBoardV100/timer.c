/*
 * Jun 16th, 2011
 * 
 * Quadrotor Main Board
 * Timer Routine
 *
 * This has to be a strong timer routine that allows other functions
 * to base their internal timers on it. It has got to have good
 * overflow handling, and be effective. No interrupts are needed.
 *
 */
 
 
/* Function: Timer1_Init
 *
 * Initializes Timer 1 for 16-bit operation.
 * No arguments.
 * 
 * Usage:
 * Timer1_Init();
 *
 */
void Timer1_init(void)
{
	TMR1 = 0;
}	
 
/* Function: Delay_Ms
 *
 * This function serves mostly testing and debugging purposes.
 * It does nothing for the specified amount of milliseconds.
 *
 * Arguments:
 * time - the amount of milliseconds to wait
 *
 * Usage:
 * Led1_On();
 * Delay_Ms(500);
 * Led1_Off();
 */
void Delay_Ms(int time)
{
	
}	
//void __ISR( _TIMER_1_VECTOR, ipl1)