/*	Header file for main.c													**
**	Declares all functions, definitions and includes necessary modules for	**
**	respective functions.													**
**																			**
**	By Paulo Carvalho V2.00													*/

/****************************************************************************/
/*	Make necessary Inclusions	*/
#include <avr/io.h>
#include <avr/interrupt.h>

/****************************************************************************/
/*	Declares Functions from all modules that might be called on main	*/

/*	Initialization	*/
void gyro_init(void);
void accel_init(void);
void int_init(void);
void uart_init(void);
void i2c_init(void);
void adc_init(void);
void wdt_init(void);
void spi_init(void);
 
/*	Sensor Reading	*/
int gyro_read(int *);
int accel_read(int *);
int mag_read(int);
int adc_read(int *);

/*	Supplementary Functions	*/
void wdt_reset(void);
void uart_write(char);
void uart_write2(int);
char uart_read(void);
void filter(int *, int *, int *, int*); 
void initialize(void);

/******************************************************************************/
/*	Make Necessary Definitions	*/

/*	LED	*/
#define LEDOK 0x40;
#define LEDS5 0x20;

/******************************************************************************/
/*	Declare Global Variables	*/

/*	Stores Filtered Data (x100) Converted into integer	*/  
int Angle[3];
int Rate[3];

/*	Stored Data Received from Sensors as Analog to Digital Conversion	*/
/* 	16 Bit Reading	*/
int Gyro_Adc[4];

/*	10 Bit Reading	*/
int Accel_Adc[3];
int Adc_Adc[6];
int Mag_Adc[3];

/* Current Axis Being Read in Magnetometer */
int Axis = 0;










