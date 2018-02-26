/* 
 * File:   major_mech_processses.h
 * Author: RobertAdragna
 *
 * Created on February 24, 2018, 5:17 PM
 */

#ifndef MAJOR_MECH_PROCESSSES_H
#define	MAJOR_MECH_PROCESSSES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"
#include "timer.h"

#include "global_variables.h"
#include "ui_functions.h"
#include "information_organization.h"
#include "io_control.h"
#include "rtc.h"
    
    
void dispense_pills(char* master_prescription, char* dc_motor_shift_list, 
        char* stepper_shift_list);
void close_box(char close_op_num);


#ifdef	__cplusplus
}
#endif

#endif	/* MAJOR_MECH_PROCESSSES_H */

