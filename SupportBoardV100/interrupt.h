/* Header File for interrupt.c */

/* Include Necessary Headers */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Declare Functions */
void accel_interrupt_init(void);
void gyro_interrupt_init(void);
void mag_interrupt_init(void);
void timer1_interrupt_init(void);
void timer2_interrupt_init(void);

/* Make Necessary Definitions */

/* Defines Timer Interrupt Period in ms for 16 bit Timer 1 */
#define PERIOD1 1000
#define TIMER1TOP (PERIOD1 / 256 * 16000)

/* Defines for Timer Interrupt Period in ms for 8 bit timer 2 */
#define PERIOD2 16
#define TIMER2TOP (PERIOD2 / 1024 * 16000)
