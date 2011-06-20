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

#define LED1 0x0020 // 0000 0000 0000 0010 0000
#define LED2 0x8000 

void LED_Init();
void LED1_On();
void LED2_On();
void LED2_Off();
void LED1_Off();