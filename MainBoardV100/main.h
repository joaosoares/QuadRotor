#pragma config POSCMOD=XT, FNOSC=PRIPLL //xt mode for posc since its below 10mhz, activate pll
#pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1
#pragma config FPBDIV=DIV_4
//pll pre-divider 1:2, multiplier x20, no post-divider
#pragma config FWDTEN=OFF, CP=OFF, BWP=OFF

#include <p32xxxx.h>
#include <plib.h>
#include "leds.h"
void Timer2_Micros(int);
void Init_All();
void PPM1_Poll(int);
void Xbee_Init();
void SupportBoard_Init();
void Timer1_Init();
void PPM_Init();
void Set_High(int);