/*
 * Jun 21st, 2011
 *
 * Quadrotor Main Board
 * SD Card Log Routines
 *
 * These functions are responsible for saving info on the SD.
 *
 */


#include <p32xxxx.h>
#include "sdcard.h"

// I/O definitions
#define SDCS	_RB8

#define readSPI()	writeSPI(0xFF)
#define clockSPI()	writeSPI(0xFF)

//SD card commands

#define RESET			0
#define INIT			1
#define READ_SINGLE		17
#define WRITE_SINGLE	24

#define disableSD()		SDCS = 1; clockSPI()
#define enableSD()		SDCS = 0;

// Data
#define DATA_ACCEPT			0x05
#define DATA_START	0xFE

// Timeouts
#define I_TIMEOUT	10000	//init timeout
#define R_TIMEOUT	10000	//read timeout
#define W_TIMEOUT	250000	//write timeout

void initSD(void)
{
	SDCS = 1;
	AD1PCFG |= ~0x0100;// 0000 0001 0000 0000
	_TRISB8 = 0;
	// init the SPI2 module for a slow (safe) clock speed first
	SPI3ACON = 0x8120; // ON, CKE = 1, CKP = 0, sample middle
	SPI3ABRG = 399; // clock = Fpb/400 = 250kHz
}	// initSD

// send one byte of data and receive one back at the same time
unsigned char writeSPI(unsigned char b)
{
	SPI3ABUF = b;					// write to buffer for the TX
	while( !SPI3ASTATbits.SPIRBF);	// wait transfer complete
	return SPI3ABUF;
}	// writeSPI

int sendSDCmd ( unsigned char c, unsigned a)
// c command code
// a bte address of data block
{
	int i, r;
	
	//enable SD card
	enableSD();
	
	// send a command packet (6 bytes)
	writeSPI( c | 0x40);	//send command
	writeSPI( a>>24);		//msb of the address
	writeSPI( a>>16);
	writeSPI( a>>8);
	writeSPI( a);			//lsb
	
	writeSPI(0x95);			//send CMD0 CRC
	
	// now wait for a response, allow to 8 bytes delay
	for( i=0; i<8; i++)
	{
		r=readSPI();
		if ( r != 0xFF)
			break;
	}	
	return ( r);
	
	// NOTE SDCS is still low!
} // sendSDCmd

int initMedia( void)
//returns 0 if succesful
//		E_COMMAND_ACK	failed to acknowledge reset command
//		E_INIT_TIMEOUT	failed to initialize
{
	int i, r;
	;
	// 1. with the card NOT selected
	disableSD();
	
	// 2. send 80 clock cycles start up
	for(i=0;i<80;i++)
		clockSPI();
	
	// 3. now select the card
	enableSD();
	
	// 4. send a single RESET commmand
	r = sendSDCmd( RESET, 0);
	disableSD();
	if ( r != 1)			// must return Idle
		return E_COMMAND_ACK;
	
	// 5. send repeatedly INIT until Idle terminates
	for (i=0; i<I_TIMEOUT; i++)
	{
		r = sendSDCmd( INIT, 0); disableSD();
		if ( !r)
			break;
	}
	if ( i == I_TIMEOUT)
		return E_INIT_TIMEOUT; // init timed out
	
	// 6. increase speed
	SPI3ACON = 0;		// disable the SPI2 module
	SPI3ABRG = 0;		// Fpb/(2*(0+1)) = 20/2 = 10MHz
	SPI3ACON = 0x8120;	// re-enable the SPI2 module
	
	return 0;
} //init media

int readSECTOR( LBA a, char *p)
// a		LBA (logic block address) of sector requested
// p		ponter to sector buffer
// returns	TRUE if succesful
{
	int r, i;
	
	// 1. send READ command
	sendSDCmd(READ_SINGLE, (a <<9));
	if ( r == 0) //check if command was received
	{
		// 2. wait for a response
		for( i=0; i<R_TIMEOUT; i++)
		{
			r = readSPI();
			if ( r == DATA_START)
				break;
		}	
	
		// 3. if it did not timeout, read 512 byte of data
		if ( i != R_TIMEOUT)
		{
			i = 512
			do {
				*p++ = readSPI();
			} while (---i>0);
			
			// 4. ignore CRC
			readSPI();
			readSPI();
			
		} // data arrived
	} // command accepted
	
	// 5. remember to disable the card
	disableSD();
	
	return ( r == DATA_START ); // return TRUE if succesful
	
} //readSECTOR

int writeSECTOR( LBA a, char * p)
// a		LBA of sector requested
// p		pointer to sector buffer
// returns	TRUE if succesful
{
	unsigned r, i;
	
	// 1. send WRITE command
	r = sendSDCmd(WRITE_SINGLE, (a<<9));
	if ( r == 0)	// check if command was accepted
	{
		
		// 2. send data
		writeSPI(DATA_START);
		
		// send 512 bytes of data
		for(i = 0; i< 512; i++)
			writeSPI(*pp++);
		
		// 3. send dummy CRC
		clockSPI();
		clockSPI();
		
		// 4. check if data accepted
		r = readSPI();
		if ( (r & 0xf) == DATA_ACCEPT)
		{
			
			// 5. wait for write completion
			for (i = 0; i < W_TIMEOUT; i++)
			{
				r = readSPI();
				if ( r != 0)
					break;
			}
		} // accepted
		else
			r = FAIL;
					
	}	
	
	// 6. remember to disable the card
	disableSD();
	
	return( r);
	
} // writeSECTOR


