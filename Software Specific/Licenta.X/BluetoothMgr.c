/*
 * File:   BluetoothMgr.c
 * Author: Alexandru Niamtu
 * 
 * Info : Bluetooth initialization and communication
 */

#include <xc.h>





void UART_init(void)
{
  BRGH = 1; /* high speed configuration */
  SPBRG = 0x0C; /* = 12 for 9600 baud rate calculated at FOSC 8M */
  
  SYNC = 0;
  SPEN = 1; /* Asynchronus mode */
  
  /* UART interrupts init */
  RCIE = 1; /* Receving data */
  PEIE = 1; /* Peripherals interrupt */
  GIE = 1; /* Global interrupts */
  
  CREN = 1; /* Continuous receive */
}

void interrupt ISR (void)
{
    if ( RCIF == 1)
    {
        com_buffer = RCREG;
    
        switch(com_buffer){
            case 0xF9: /* MOTOR_COMMAND GO FORWARD */
                break;
            
            case 0xF6: /* MOTOR_COMMAND GO_BACKWARD */
                break;
                
            case 0xF8: /* MOTOR_COMMAND GO_LEFT */
                break;
                    
            case 0xF1: /* MOTOR_COMMAND GO_RIGT */
                break;
                
            case 0x9F: /* SYSTEM_COMMAND OPEN_HEADLIGHTS */
                break;
                
            case 0x90: /* SYSTEM_COMMAND CLOSE HEADLIGHTS */
                break;
               
            case 0x99: /* SYSTEM COMMAND ACTIVATE_DISTRONIC */
                break;
                
            case 0x96: /* SYSTEM_COMMAND DEACTIVATE_DISTRONIC */
                break;
                
            default: /* TODO : error func */
                break;
        }
        
        RCIF = 0; /* Clearing interrupt flag */
    }
}
