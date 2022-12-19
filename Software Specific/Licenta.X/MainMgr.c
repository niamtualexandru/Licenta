/*
 * File:   MainMgr.c
 * Author: Alexandru Niamtu
 * 
 * 
 * Info: This is the main source file for the 
 *        final diploma.
 * .
 *       All the code will be divided in different source files
 *        so it can be easily read and explained,
 * 
 * 
 * Created on December 6, 2022, 9:49 PM
 */


// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON    // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>



#include "MainMgr.h"
#include "BluetoothMgr.h"
#include "MotorMgr.h"


#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)



void main(void) {
    project_init();
    __delay_ms(10);
    motor_init();
    UART_init();
    while(TXIF==0);
    TXREG = 0x41;
    /* BACKLIGHTS ON, HEADLIGHTS OFF */
    HEADLIGHTS = OFF;
    BACKLIGHTS = ON;
    while(1)
    {

    }

}


void project_init(void)
{
    IRCF0=1;
    IRCF1=1;
    IRCF2=1;
    /* PIN INIT */

    TRISA = ALL_OUTPUT; /* nothing is used for now, default all outputs */
    TRISB = 0x10; 
    /*
     * RB0 : Headlights control -> output
     * RB4 : Distance data -> input
    */
    
    TRISC = 0xA0;
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
    if(RCIF == 1)
    {
        /* Check command ID */
        switch(com_buffer){
            case 0xF9: /* MOTOR_COMMAND GO FORWARD */
                BACKLIGHTS = OFF;
                motorFault = motor_command(GO_FORWARD);
                break;
            
            case 0xF6: /* MOTOR_COMMAND GO_BACKWARD */
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
                while(TXIF==0);
                TXREG = 0x44;
                break;
        }
        if ( motorFault != COMMAND_UNKNOWN )
        {
            /* Command ok, send the same ID for ack */
            while(TXIF==0);
            TXREG = com_buffer; 
        }
        else
        {
            /* ID unknown, send error ID */
            while(TXIF==0);
            TXREG = COMMAND_UNKNOWN;
        }
        RCIF = 0; /* Clearing interrupt flag */
    }
}