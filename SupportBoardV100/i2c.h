/*	Header File for "i2c.c" which contains definitions for Clock, Speed and	**
**	necessary comparisons.													**
**	By Paulo Carvalho V2.00													*/

/****************************************************************************/
/* Include AVR Headers for Standard Operation	*/
#include <avr/io.h>
#include <util/delay.h>
#include "i2cmaster.h"

/****************************************************************************/
/* Make Necessary Definitions */

/* Sensor Adresses */

#define GYROADRESS 0xD0 
#define ACCELADRESS 0xA6 

/*******/
/* Gyroscope Related Data */

/* Offsets for Gyro */
#define X_OFFSET 23
#define Y_OFFSET 7
#define Z_OFFSET 10

/* Register Definitions */
#define INT_CFG 0x17 //Gyro Configuration, Interrupt, Etc
#define SMPLRT_DIV 0x15 //Sample Rate Register In Gyro
#define DLPF_FS 0x16 //Full Scale and Filter
#define TEMP_OUT_H 0x1B //First Register Read for Gyro Data
#define PWR_MGM 0x3E //Power Manegement Register In Gyro

/* First Adress to be Read from Gyro */
#define GYROREGADRESS 0x1B 

/* Register Bit Definition */
#define FS_SEL 3 //Scale of Operation Gyro
#define DLPF_CFG 0 //Low Pass Filer and Sample Rate
#define H_RESET 7 //Resets Gyro
#define CLK_SEL 0 //Clock Source for Gyro
#define LATCH_INT_EN 5 
#define INT_ANYRD_2CLEAR 4 //Interrupt Clearing Method Gyro
#define RAW_RDY_EN 0 

/*******/
/* Accelerometer Related Defines */

/* Register Definitions */
#define DATA_FORMAT 0x31 //Data Format Control Accel
#define INT_ENABLE 0x2E //Enable Interrupt and Define Source Accel
#define DATAX0 0x32 //Adress For First Register to Be Read from Accel
#define OFSX 0x1E //Offset Register X Accel Accel
#define ACT_INACT_CTL 0x27 //Axis Enable Control Accel
#define INT_MAP 0x2F //Interrupt Map Accel
#define POWER_CTL 0x2D //Power Saving Features Accel
#define BW_RATE 0x2C //Data Rate and Power Mode Control
#define FIFO_CTL 0x38 //Adress For Accelerometer Stack 

/* Register Bit Definitions */
#define DATA_READY 7 //Source of Interrupt Accel
#define JUSTIFY 2 //Define if MSB or LSB at left
#define RANGE 0 //Define G Range According to Table
#define RATE 0 //Register Place for Data Rate (10 is 100 hz)
#define MEASURE 3 //Puts Device on Measuring Mode
#define AUTO_SLEEP 4 // Turns ON Auto Sleep

/***************************************************************************/
/* Declares Module Specific Functions */

/* Writes Data into Specified Sensor and Register */
void i2c_reg_write(char, char, char);

