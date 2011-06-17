/*
 * Jun 16th, 2011
 * 
 * Quadrotor Main Board
 * Timer Routine
 *
 * This has to be a strong timer routine that allows other functions
 * to base their internal timers on it. It has got to have good
 * overflow handling, and be effective. No interrupts are needed.
 * It has a 32-bit timer function, 
 */
 
// void __ISR( _TIMER_1_VECTOR, ipl1) T