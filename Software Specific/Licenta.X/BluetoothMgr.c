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

