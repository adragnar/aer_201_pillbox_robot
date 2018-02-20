#include "global_variables.h"

const char keys[16] = "123A456B789C*0#D"; 

//set up navigation through LCD display
char current = 0;  //stages, enum: welcome, R, F, L, Daily, Weekly, Start, Finished
                   //More details, op time, pills left, run summary
char r_screen_base = 2;  //first placeholder on the screen for digits

//Global data structures - user inputted 
char prescription[3] = {0};  //enum round, flat, long. All start off at 0  
char daily_repeat = {0};  //enum morning, afternoon, both
char weekly_repeat = {0};  //enum everyday, alternate sunday, alternate monday
char master_list[14][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                            {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};  //main list, used in dispensing

//Global data structures - machine discovered 
char leftover_pills[3] = {0,0,0};  //leftover resevoir pills counted by machine. R,F,L order

//enums for easy access 
//These are for easy access to labels during the UI printing 
const char daily_options[3][10] = {"Morning", "Afternoon", "Both"};
const char weekly_options[3][16] = {"Everyday", "Alt Start Sunday","Alt Start Monday"};
//These are the enums corresponding to actual values 
//enum daily_options_values {MORNING, AFTERNOON, BOTH};
//enum weekly_options_values {EVERYDAY, ALT_SUNDAY, ALT_MONDAY};

//Timer
#define PILL_REV_TIME 1 //IN SECONDS  
double time_from_timer0 = 0;  //global variable containing time from timer0

//RTC
char start_time_array[3]; 
char final_time_array[3];

//I/O devices
//enum sol_types {SOL_TIME=0, SOL_TUBE_SWITCH=1, SOL_CLOSE_BOX=2};
//enum dc_motor_names {CASEA=0x03, CASEB=0x0C, CASEC=0X30};  //let value be what pins need to be high that control motos
//enum motor_states {REST_DC=0, FORWARD_DC=1, BRAKE_DC=2}; //let value be the 2-pin drive configuration
//enum latx_types {DC_MOTOR,B,C,D,SOLENOID};
