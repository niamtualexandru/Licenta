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
#include "BluetoothMgr.h"
#include "MotorMgr.h"

void main(void) {
    project_init();
    motor_init();
    UART_init();
    __delay_ms(100);
    
    /* BACKLIGHTS ON, HEADLIGHTS OFF */
    HEADLIGHTS = OFF;
    BACKLIGHTS = ON;
    
    while(1)
    {
    
    }

}


void project_init(void)
{
    /* PIN INIT */
    
    TRISA = ALL_OUTPUT; /* nothing is used for now, default all outputs */
    TRISB = 0x10; 
    /*
     * RB0 : Headlights control -> output
     * RB4 : Distance data -> input
    */
    
    TRISC = 0xB0;
    /*
     * RC7 : RX uC - TX HC-05 -> input
     * RC6 : TX uC - RX HC-05 -> output
     * RC5 : HC-05 state -> input
     * RC4 : Backlights control -> output
     */
    
    TRISD = ALL_OUTPUT; 
    /*
     * RD0 : Motor 1 backward -> output
     * RD1 : Motor 1 forward -> output
     * RD2 : Motor 2 backward -> output
     * RD3 : Motor 1 forkward -> output
    */
    
    
    ANSEL = ALL_DIGITAL;
    ANSELH = 0x08; /* RB4 - AN11 used as analog input */
    
    ADCON0 = 0x2D;
    /*
     * 0010 1101
     * Fosc/2 ; AN11 ; DONE ; ADC is enabled
    */
    ADCON1 = 0x00;
    
}

void __interrupt() ISR_treatment (void)
{
    if ( RCIF == 1)
    {
        com_buffer = RCREG;
    
        switch(com_buffer){
            case 0xF9: /* MOTOR_COMMAND GO FORWARD */
                BACKLIGHTS = OFF;
                motorFault = motor_command(GO_FORWARD);
                break;
            
            case 0xF6: /* MOTOR_COMMAND GO_BACKWARD */
                BACKLIGHTS = OFF;
                motorFault = motor_command(GO_BACKWARD);
                break;
                
            case 0xF8: /* MOTOR_COMMAND GO_LEFT */
                BACKLIGHTS = OFF;
                motorFault = motor_command(GO_LEFT);
                break;
                    
            case 0xF1: /* MOTOR_COMMAND GO_RIGHT */
                BACKLIGHTS = OFF;
                motorFault = motor_command(GO_RIGHT);
                break;
               
            case 0xF0: /* MOTOR_COMMAND GO_STANDBY */
                BACKLIGHTS = ON;
                motorFault = motor_command(GO_STANDBY);
                break;
                
            case 0x9F: /* SYSTEM_COMMAND OPEN_HEADLIGHTS */
                HEADLIGHTS = ON;
                break;
                
            case 0x90: /* SYSTEM_COMMAND CLOSE HEADLIGHTS */
                HEADLIGHTS = OFF;
                break;
               
            case 0x99: /* SYSTEM COMMAND ACTIVATE_DISTRONIC */
                break;
                
            case 0x96: /* SYSTEM_COMMAND DEACTIVATE_DISTRONIC */
                break;
                
            default: /* TODO : error func */
                break;
        }
        if ( motorFault != COMMAND_UNKNOWN )
        {
            /* TODO : Send command ok */
        }
        else
        {
            /* TODO : Send motor fault */
        }
        RCIF = 0; /* Clearing interrupt flag */
    }
}