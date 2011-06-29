/*
 * Jun 29th, 2011
 * 
 * SD Library
 *
 */
 
#define FAIL FALSE
// Init ERROR code definitions
#define E_COMMAND_ACK	0x80
#define E_INIT_TIMEOUT	0x81

typedef unsigned LBA; //logic block address, 32 bit wide

void initSD( void);
int initMedia( void);
int readSECTOR( LBA, char *);
int writeSECTOR( LBA, char *);
