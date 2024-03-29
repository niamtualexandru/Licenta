/* 
 * File: MainMgr.c
 * Author: Alexandru Niamtu
 * Comments: Header file for MainMgr
 * Revision history: 1.0
 */

#include <xc.h>

/* Functions declaration */
static void project_init(void);



/* Variable declaration */
static uint8_t com_buffer = 0;
static uint8_t motorFault = 1;


#define _XTAL_FREQ 8000000

/* not used ports */
#define ALL_OUTPUT 0x00

#define ALL_DIGITAL 0x00

/* HEADLIGHT CONTROL */
#define HEADLIGHTS RB0
#define BACKLIGHTS RC4
#define ON 0b1
#define OFF 0b0

#define INIT_OK 0x11


#ifndef E_OK
#define E_OK 0b1
#endif

#ifndef E_NOT_OK
#define E_NOT_OK 0b0
#endif


