/* 
 * File:   MotorMgr.c
 * Author: Alexandru Niamtu
 *
 * Created on December 11, 2022, 8:12 PM
 */

#include <xc.h>
#include "MotorMgr.h"



void motor_init(void)
{
    MOTOR1_FORWARD = OFF;
    MOTOR1_BACKWARD = OFF;
    MOTOR2_FORWARD = OFF;
    MOTOR2_BACKWARD = OFF;
}

uint8_t motor_command(uint8_t command)
{
    uint8_t return_value;
    switch(command)
    {
        case GO_FORWARD :
            MOTOR1_FORWARD = ON;
            MOTOR1_BACKWARD = OFF;
            MOTOR2_FORWARD = ON;
            MOTOR2_BACKWARD = OFF;
            return_value = E_OK;
        break;
        
        case GO_BACKWARD :
            MOTOR1_FORWARD = OFF;
            MOTOR1_BACKWARD = ON;
            MOTOR2_FORWARD = OFF;
            MOTOR2_BACKWARD = ON;
            return_value = E_OK;
        break;
        
        case GO_LEFT :
            MOTOR1_FORWARD = OFF;
            MOTOR1_BACKWARD = ON;
            MOTOR2_FORWARD = ON;
            MOTOR2_BACKWARD = OFF;
            return_value = E_OK;
        break;
        
        case GO_RIGHT :
            MOTOR1_FORWARD = ON;
            MOTOR1_BACKWARD = OFF;
            MOTOR2_FORWARD = OFF;
            MOTOR2_BACKWARD = ON;
            return_value = E_OK;
        break;
        
        case GO_STANDBY:
            MOTOR1_FORWARD = OFF;
            MOTOR1_BACKWARD = OFF;
            MOTOR2_FORWARD = OFF;
            MOTOR2_BACKWARD = OFF;
            return_value = E_OK;
        break;
        
        default:
            return_value = COMMAND_UNKNOWN;
        break;
    }
    return return_value;
}