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
#define FINISHED_NUM 5
extern char leftover_pills[3];  //leftover resevoir pills counted by machine. R,F,L order
extern char in_operation; 

//enums for easy access 
//These are for easy access to labels during the UI printing 
extern const char daily_options[3][10];
extern const char weekly_options[3][16];

//These are the enums corresponding to actual values 
enum daily_options_values {MORNING, AFTERNOON, BOTH};
enum weekly_options_values {EVERYDAY, ALT_SUNDAY, ALT_MONDAY};

//Pill Dispensing
#define PILL_REV_TIME_FIRST 1200 //IN SECONDS
#define PILL_REV_TIME 1000

//Timer
extern double time_from_timer0;  //global variable containing time from timer0

//RTC
extern char start_time_array[6]; 
extern char final_time_array[6];

//Solenoids
#define NUM_SOLEN 3
enum sol_names {SOL_TIME, SOL_TUBE_SWITCH, SOL_CLOSE_BOX};
extern char sol_shift_list[NUM_SOLEN];

//DC Motors 
#define NUM_DC_MOTORS 3
enum dc_motor_names {CASEA, CASEB, CASEC};  
extern char dc_shift_list[NUM_DC_MOTORS];

//Steppers
#define NUM_STEPPERS 1
#define STEPPER_ACTUATE_TIME 500  //ms
enum stepper_motor_names {RACK};
extern char stepper_shift_list[NUM_STEPPERS];
enum stepper_direction {FORWARD_STEPPER, BACKWARD_STEPPER};

enum latx_types {DC_MOTOR,SENSOR,SOLENOID,STEPPER};

//Sensors
enum sensor_names {COLOR_SENSOR, BREAK1, BREAK2, BREAK3};
extern char sensor_shift_list[4]; //indexed by above enum values 
#define SENSOR_HOLD_TIME 1000

//Closing 
enum close_box_operations{STEP_BACK, CLOSE_LID_CLOSE, CLOSE_LID_OPEN};
extern char closing_op_num;
#define NUM_CLOSING_OPS 21

//EEPROM
#define NUM_ENTRIES_LOG 1

//GLCD 
#define NUM_DIVISIONS 18 
#define GLCD_MARGIN 5
enum op_states {USER_INPUT, CHECK_DIR, DISP1, DISP2, DISP3, DISP4, DISP5, DISP6, DISP7, START_DISP,
                    CLOSE1, CLOSE2, CLOSE3, CLOSE4, CLOSE5, CLOSE6, CLOSE7, FINISH};
extern const char op_names[NUM_DIVISIONS][32]; 
extern char glcd_op_num;
                    
                    
                    
                    
                    
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_VARIABLES_H */

