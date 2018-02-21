/* 
 * File:   actuator_control.h
 * Author: RobertAdragna
 *
 * Created on February 20, 2018, 9:39 PM
 */

#ifndef ACTUATOR_CONTROL_H
#define	ACTUATOR_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "global_variables.h"
#include "information_organization.h"
    
void solenoid_control(char solen_name, char curr_state, char on_off);
void dc_motor_control(char motor_name, char curr_state, char motor_state);
char read_reset_sensor(char sensor_name, char curr_state, char sensor_shift_list[4]);



#ifdef	__cplusplus
}
#endif

#endif	/* ACTUATOR_CONTROL_H */

