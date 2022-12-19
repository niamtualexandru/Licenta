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
  SPBRG = 0x33; /* = 51 for 9600 baud rate calculated at FOSC 8M */
  
  SYNC = 0;
  SPEN = 1; /* Asynchronus mode */
  
  /* UART interrupts init */
  RCIE = 1; /* Receving data */
  TXIE = 0;
  PEIE = 1; /* Peripherals interrupt */
  GIE = 1; /* Global interrupts */
  TX9 = 0; /* 8 bit data transmit */
  RX9 = 0; /* 8 bit data receive */
  CREN = 1; /* Continuous receive */
  TXEN = 1;
}

