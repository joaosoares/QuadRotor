/* Header Module for uart.c */

/* Include Necessary Headers */

#include <avr/io.h>
#include <avr/interrupt.h>

/* Make Necessary Definitions */

#define FOSC 16000000
#define BAUD 250000
#define MYUBRR FOSC / 16 / BAUD - 1 //Calculates Prescaller For UART Speed
