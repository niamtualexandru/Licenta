/* 
 * File: MainMgr.c
 * Author: Alexandru Niamtu
 * Comments: Header file for MainMgr
 * Revision history: 1.0
 */

#include <xc.h>

/* Functions declaration */
void project_init(void);

#pragma config WDTE = OFF

#define _XTAL_FREQ 8000000

/* not used ports */
#define NOT_USED 0x00

#define ALL_DIGITAL 0x00


#ifndef E_OK
#define E_OK 1
#endif

#ifndef E_NOT_OK
#define E_NOT_OK 0
#endif


