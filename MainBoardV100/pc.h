/*
 * Jun 26th, 2011
 *
 * Quadrotor Main Board
 * PC Communication Library
 */
//Necessary inclusions
#include <p32xxxx.h>
#include "plib.h"

/* DEFINITIONS */

//For the Xbee
#define XBEE_RESET PORTEbits.RE6
#define XBBEE_STRENGHT PORTBbits.RB9
#define XBEE_BAUD 129 // [ 20000000 (fpb) / 4 * 250000 (desired baud) ]- 1 = ??

//Definitions for packet order
#define START 0
#define INFRARED_1 1
#define INFRARED_2 2
#define INFRARED_3 3
#define INFRARED_4 4
#define SONAR 5
#define TEMP_1 6
#define TEMP_2 7
#define TEMP_3 8
#define IMU_TILT_X 9
#define IMU_TILT_Y 10
#define IMU_TILT_Z 11
#define IMU_RATE_X 12
#define IMU_RATE_Y 13
#define IMU_RATE_Z 14
#define BAT_CURRENT_POW1 15
#define BAT_CURRENT_POW2 16
#define BAT_CURRENT_RES 17
#define BAT_CURRENT_DIG 18
#define BAT_VOLTAGE_POW1 19
#define BAT_VOLTAGE_POW2 20
#define BAT_VOLTAGE_RES 21
#define BAT_VOLTAGE_DIG 22
#define SIG_STRENGTH 23
#define GPS 24
#define FEED1_RES 30
#define FEED2_RES 31
#define FEEDDIG_RES 32
#define RELAY1_FAIL 33
#define RELAY2_FAIL 34
#define SUPPORTB_FAIL 35
#define GPS_FAIL 36 
#define SD_FAIL 37
#define END 100

/* FUNCTION DECLARATIONS */
void Xbee_Init();
