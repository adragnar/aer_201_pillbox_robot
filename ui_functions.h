/* 
 * File:   ui_functions.h
 * Author: RobertAdragna
 *
 * Created on February 20, 2018, 3:32 PM
 */

#ifndef UI_FUNCTIONS_H
#define	UI_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "global_variables.h"
#include "lcd.h"
#include "rtc.h"

    
void setup_main_screen();
void setup_dosage_screen(char screen_base, char* prescrip_list);
void setup_daily_repeat_screen(char repeat);
void setup_weekly_repeat_screen(char repeat);
void standby_screen();
void setup_end_screen();
void cycle_through_options();
void setup_pills_remaining_screen(char* leftover_count);
void setup_run_summary_screen(char* prescrip_list, char repeat_daily, char repeat_weekly);
void modified_setup_dosage_screen(char* prescrip_list); 
void setup_final_time_elapsed_screen(char* initial_setup_list, char* final_setup_list);


#ifdef	__cplusplus
}
#endif

#endif	/* UI_FUNCTIONS_H */

