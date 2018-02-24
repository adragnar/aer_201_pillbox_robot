/* 
 * File:   tests.h
 * Author: RobertAdragna
 *
 * Created on February 20, 2018, 9:47 PM
 */

#ifndef TESTS_H
#define	TESTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "configBits.h"
#include "eeprom.h"
#include "global_variables.h"  
#include "I2C.h"
#include "information_organization.h"
#include "io_control.h"
#include "lcd.h"
#include "rtc.h"
#include "timer.h"
#include "ui_functions.h"
#include "GLCD_PIC.h"
#include "px_ascii.h"
#include "major_mech_processses.h"
    
void test_populate_master_list(void);
void test_reverse_master_list(void);
void test_solenoid_control(void);
void test_dc_motor_control(void);
void test_timer0(void);
void test_read_reset_sensor(void);
void test_eeprom(void);
void test_stepper_motor_control(void);
void test_glcd(void);
void test_dispense_pills(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TESTS_H */

