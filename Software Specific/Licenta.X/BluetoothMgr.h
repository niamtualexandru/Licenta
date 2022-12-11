/* 
 * File:   BluetoothMgr.h
 * Author: Alexandru Niamtu
 *
 * Created on December 10, 2022, 6:30 PM
 */

/* Functions declaration */
extern void UART_init(void);

/* Constants definition */

/* Received buffer decodation 
 * xxxx.yyyy
 * 
 * if xxxx == 1111 - motor command
 *   then if yyyy == 1001 - forward
 *   else if yyyy == 0110 - back
 *   else if yyyy == 1000 - left
 *   else if yyyy == 0001 - right
 * 
 * if xxxx == 1001 - system command
 *   then if yyyy == 1111 - open headlights
 *   else if yyyy == 0000 - close headlights
 *   else if yyyy == 1001 - distronic on
 *   else if yyyy == 0110 - distronic off
 */

#define MOTOR_COMMAND 0xF
#define GO_FORWARD 0x9
#define GO_BACKWARD 0x6
#define GO_LEFT 0x8
#define GO_RIGHT 0x1
#define GO_STANDBY 0x0

#define SYSTEM_COMMAND 0x9
#define OPEN_HEADLIGHTS 0xF
#define CLOSE_HEADLIGHTS 0x0
#define ACTIVATE_DISTRONIC 0x9
#define DEACTIVATE_DISTRONIC 0x6




