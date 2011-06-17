/*
 * Jul 16th, 2011
 * 
 * Quadrotor Main Board
 * LED Control Modules Header
 *
 * Necessary definitions for proper LED control.
 *
 */
 
#include <p32xxxx.h>
#include "plib.h"

#define LED1 PORTEbits.RE5 //Location of LED 1
#define LED2 PORTBbits.RB15 // Location of LED 2

#define LED1TRIS 0x0010 // port 5, so 0001 0000
#define LED2TRIS 0x8000 // port 15, 1000 0000 0000 0000

void Set_High(int);