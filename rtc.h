/* 
 * File:   rtc.h
 * Author: RobertAdragna
 *
 * Created on February 20, 2018, 4:06 PM
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "global_variables.h"
#include "I2C.h"
#include "lcd.h"

void read_time(char* a);  
char find_operation_time(char* initial, char* final);  
char rtc_test(char* initial, char* final); //to execute test, run with start & final time arrays below setup_main-screen
void print_time_to_lcd(char* write_list);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

