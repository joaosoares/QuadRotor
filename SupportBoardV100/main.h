/*		Header File for main.c	    */
/************************************/

/* Include Necessary Headers */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "i2cmaster.h"

/************************************/
/* Declare Functions used in main.c */

/* Serial UART Comunication */
void uart_init(void);
uint8_t uart_read(void);
void uart_write(char);
void uart_write2(int);

/* SPI Comunication */
void spi_init(void);
uint8_t spi_read(void);
void spi_write(char);

/* ADC Comunication */
void adc_init(void);
uint16_t adc_read(char);

/* i2c Comunication */
void gyro_init(void);
void gyro_read(int *);
void accel_read(int *);
void accel_init(void);

/* Watch Dog Timer */
void wdt_init(uint8_t);

/* IMU Functions */
// REQUIRES MORE KNOWLEDGE!!!!!!!!

/* Other Functions */
void initialize(void); //Performs Initialization Routine
void interrupt_init(void); //Performs Initialization of Diverse Interrupts  

/************************************/
/* Makes Necessary Definitions */

/* SCALLER is the number to be shifterd into WDP0 Register
** Of the WatchDog Timer and therefore defines the Prescaller
** The setting of 4 Sets it to a 0.25 ms period				*/
#define SCALLER 4

/* LED Pins */
#define LEDOK 0x40 //PD6
#define LEDS5 0x20 //PD5

/************************************/
/* Declare Global Variables Accessible to All Files */
extern uint16_t Mag_Data; //Read Data from the Magnetometer
extern uint8_t Pic_Data; //Last Received Byte from PIC32MX
int Gyro_Raw[4]; //Gyro Axis Raw Measurement ADC + Temp
int Accel_Raw[3]; //Accel Axis Raw Measurement from ADC
int Acc_Degree; //Variable to Store Degree Data
double AccelX_G; //Raw Gravitational Vectors
double AccelY_G;
double AccelZ_G;
