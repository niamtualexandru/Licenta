/* 
 * File:   MotorMgr.h
 * Author: Alexandru Niamtu
 *
 * Created on December 11, 2022, 8:12 PM
 */


extern void motor_init(void);
extern uint8_t motor_command(uint8_t);

#define MOTOR1_FORWARD RD1
#define MOTOR1_BACKWARD RD0
#define MOTOR2_FORWARD RD3
#define MOTOR2_BACKWARD RD2

#define GO_FORWARD 0xF
#define GO_BACKWARD 0x6
#define GO_LEFT 0x8
#define GO_RIGHT 0x1
#define GO_STANDBY 0x0

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#ifndef E_OK
#define E_OK 1
#endif

#ifndef E_NOT_OK
#define E_NOT_OK 0
#endif

#define COMMAND_UNKNOWN 0xAA