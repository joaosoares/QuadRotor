/*
 * Jun 20th, 2011
 * 
 * Quadrotor Main Board
 * Timer 1 Counter Routines
 *
 * These are the modules for the functioning of Timer 1, which
 * serves as a general purpose timer and also to activate the PID
 * and PPM controllers.
 *
 */

#include "counter.h"

extern char Xbee_Last_Read;

/* Function: Counter_Init
 * 
 * Starts Timer 1 with a high prescaler so it can measure milliseconds
 * and be used as counter.
 * No arguments.
 *
 * Usage:
 * Counter_Init();
 */
void Counter_Init()
{
	T1CON = 0;
	T1CONSET = 0x0020;
	TMR1 = 0x00;
	PR1 = (20 * 20000000) / (64*1000);
	T1CONbits.ON = 1;
	mT1SetIntPriority(7);
	mT1IntEnable(1);
}	
 
/* Function: Counter_Interrupt
 *
 * Handles the interrupt for Timer 1 Counter, updating the PID
 * controller and starting the PPMs.
 * No arguments.
 * Usage is automatic, since it is interrupt-based.
 */
void __ISR(_TIMER_1_VECTOR, ipl7) Counter_Interrupt (void)
{
	//UpdatePID();
	switch (Xbee_Last_Read) {
		case 0x10:
			PPM2_On(1000);
			break;
		case 0x11:
			PPM2_On(1100);
			break;
		case 0x12:
			PPM2_On(1200);
			break;
		case 0x13:
			PPM2_On(1300);
			break;
		case 0x14:
			PPM2_On(1400);
			break;
		case 0x15:
			PPM2_On(1500);
			break;
		case 0x16:
			PPM2_On(1600);
			break;
		case 0x17:
			PPM2_On(1700);
			break;
		case 0x18:
			PPM2_On(1800);
			break;
		case 0x19:
			PPM2_On(1900);
			break;
		default:
			PPM2_On(900);
			break;
	}			
	LED1_On();
	mT1ClearIntFlag();
}
