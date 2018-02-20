/* 
 * File:   global_variables.h
 * Author: RobertAdragna
 *
 * Created on February 20, 2018, 3:12 PM
 */

#ifndef GLOBAL_VARIABLES_H
#define	GLOBAL_VARIABLES_H

#ifdef	__cplusplus
extern "C" {
#endif

    
extern const char keys[16]; 

//set up navigation through LCD display
extern char current;  //stages, enum: welcome, R, F, L, Daily, Weekly, Start, Finished
                   //More details, op time, pills left, run summary
extern char r_screen_base;  //first placeholder on the screen for digits

//Global data structures - user inputted 
extern char prescription[3];  //enum round, flat, long. All start off at 0  
extern char daily_repeat;  //enum morning, afternoon, both
extern char weekly_repeat;  //enum everyday, alternate sunday, alternate monday
extern char master_list[14][3];  //main list, used in dispensing

//Global data structures - machine discovered 
extern char leftover_pills[3];  //leftover resevoir pills counted by machine. R,F,L order

//enums for easy access 
//These are for easy access to labels during the UI printing 
extern const char daily_options[3][10];
extern const char weekly_options[3][16];

//These are the enums corresponding to actual values 
enum daily_options_values {MORNING, AFTERNOON, BOTH};
enum weekly_options_values {EVERYDAY, ALT_SUNDAY, ALT_MONDAY};

//Timer
#define PILL_REV_TIME 1 //IN SECONDS  
extern double time_from_timer0;  //global variable containing time from timer0

//RTC
extern char start_time_array[3]; 
extern char final_time_array[3];

//I/O devices
enum sol_types {SOL_TIME=0, SOL_TUBE_SWITCH=1, SOL_CLOSE_BOX=2};
enum dc_motor_names {CASEA=0x03, CASEB=0x0C, CASEC=0X30};  //let value be what pins need to be high that control motos
enum motor_states {REST_DC=0, FORWARD_DC=1, BRAKE_DC=2}; //let value be the 2-pin drive configuration
enum latx_types {DC_MOTOR,B,C,D,SOLENOID};



#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_VARIABLES_H */

