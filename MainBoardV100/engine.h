/*
 * Jun 20, 2011
 *
 * Header file for engine.c
 *
 */

// Include files
#include <p32xxxx.h>
#include "plib.h"

// Definitions

#define PPM1 PORTDbits.RD7
#define PPM1TRIS 0x0080 // Port D7: 0000 0000 1000 0000

#define PPM2 PORTDbits.RD6
#define PPM2TRIS 0x0040 // Port D6: 0000 0000 0100 0000

#define PPM3 PORTDbits.RD5
#define PPM3TRIS 0x0020 // Port D5: 0000 0000 0010 0000

#define PPM4 PORTDbits.RD4
#define PPM4TRIS 0x0010 // Port D4: 0000 0000 0001 0000

// Public function declarations

//PPM1 Functions
void PPM1_Init();
void PPM1_On(int);
//PPM2 Functions
void PPM2_Init();
void PPM2_On(int);
//PPM3 Functions
void PPM3_Init();
void PPM3_On(int);
//PPM4 Functions
void PPM4_Init();
void PPM4_On(int);