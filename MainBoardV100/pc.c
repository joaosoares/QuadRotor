/*
 * Jun 16th, 2011
 *
 * Quadrotor Main Board
 * Modules for PC Communication
 *
 * These modules are used for UART communication with the
 * Xbee radio for wireless communication between the PC 
 * and the Quadrotor.
 * There is a initialization, a write, a read function.
 * The baud rate can be modified as needed.
 *
 */
#include "pc.h"

//File with definitions and function declarations
char Xbee_Last_Read;

char one_before;
char two_before;
char three_before;
char four_before;

//Structures for data packets
struct SendPacket {
	char infrared_1;
	char infrared_2;
	char infrared_3;
	char infrared_4;
	char sonar;
	char temp_1;
	char temp_2;
	char temp_3;
	char imu_tilt_x;
	char imu_tilt_y;
	char imu_tilt_z;
	char imu_rate_x;
	char imu_rate_y;
	char imu_rate_z;
	char bat_current_pow1;
	char bat_current_pow2;
	char bat_current_res;
	char bat_current_dig;
	char bat_voltage_pow1;
	char bat_voltage_pow2;
	char bat_voltage_res;
	char bat_voltage_dig;
	char sig_strength;
	char gps;
	char feed1_res;
	char feed2_res;
	char feeddig_res;
	char relay1_fail;
	char relay2_fail;
	char supportb_fail;
	char gps_fail;
	char sd_fail;
};

/* Function: Xbee_Serial_Init
 *
 * Xbee initializing routine. Resets the device, configures the
 * UART2B module for use with it, enables the pic RX interrupts,
 * and configures the Sinal Strength ADC.
 * No arguments are required.
 *
 * Usage:
 * main(){
 *	 ...
 *	 Xbee_Init();
 *	 ...
 *
 */
void Xbee_Init()
{
	// Placeholder for Xbee reset (as soon as timer routine is working)
	U2BBRG = XBEE_BAUD; // Set baud rate
	U2BSTA = 0; // Clear control register (reset)
	U2BMODE = 0x8008; //Enable UART for 8-bit, no parity, 1 stop bit
	U2BSTASET = 0x1400;
	mU2BSetIntPriority(3);
	mU2BRXIntEnable(1); // Enable RX interrupts for UART2B
	// Placeholder for ADC initializing
}

/* Function: Xbee_Write
 *
 * Sends a specified byte to the Xbee using UART communication.
 * 
 * Arguments:
 * data - the byte to be sent
 *
 * Usage:
 * if(foo == 0x75){
 *	 ...
 *   Xbee_Write(foo);
 *   ...
 */
void Xbee_Write(char data)
{
	while(U2BSTAbits.UTXBF); // POTENTIAL SOURCE OF ERROR - Wait while the buffer is full
	U2BTXREG = data; // Pass data to the transmit register
}

/* Function: Xbee_Read
 * 
 * When data is available from Xbee, read it and save to a variable.
 * No arguments required
 * Usage is automatic, since it is interrupt based.
 */
void __ISR(_UART_2B_VECTOR, ipl3) PC_Receive (void)
{
	char data = U2BRXREG;
	Xbee_Last_Read = data;
	
	
	
	mU2BRXClearIntFlag();
}	

/* Function: Decide Packet*/


