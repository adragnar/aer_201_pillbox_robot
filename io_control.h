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
    
void solenoid_control(char solen_name, char curr_state, char on_off, char sol_shift_list[NUM_SOLEN]);
void dc_motor_control(char motor_name, char curr_state, char on_off, char dc_shift_list[NUM_DC_MOTORS]);
char read_reset_sensor(char sensor_name, char curr_state, char sensor_shift_list[4]);
void stepper_motor_control(char motor_name, char curr_state, char num_steps, char dir, char stepper_shift_list[NUM_STEPPERS]);
void reset_stepper(char motor_name, char curr_state, char is_reset, char stepper_shift_list[NUM_STEPPERS]);
void enable_stepper(char motor_name, char curr_state, char on_off, char stepper_shift_list[NUM_STEPPERS]);

#ifdef	__cplusplus
}
#endif

#endif	/* ACTUATOR_CONTROL_H */

