/*
 * File:   MainMgr.c
 * Author: Alexandru Niamtu
 * 
 * 
 * Info: This is the main source file for the 
 *        final diploma.
 * 
 *       All the code will be divided in different source files
 *        so it can be easily read and explained,
 * 
 * 
 * Created on December 6, 2022, 9:49 PM
 */


#include <xc.h>
#include "MainMgr.h"

void main(void) {
    return;
}


void project_init(void)
{
    /* PIN INIT */
    
    TRISA = NOT_USED; /* nothing is used for now, default all outputs */
    TRISB = NOT_USED; /* nothing is used for now, default all outputs */
    TRISC = 0xA0;
    /*
     * RC7 : RX uC - TX HC-05 -> input
     * RC6 : TX uC - RX HC-05 -> output
     * RC5 : HC-05 state -> input
     */
    TRISD = NOT_USED; /* nothing is used for now, default all outputs */
    
    ANSEL = ALL_DIGITAL;
    ANSELH = ALL_DIGITAL;
}
