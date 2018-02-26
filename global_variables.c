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
char in_operation = 0;
char leftover_pills[3] = {0,0,0};  //leftover resevoir pills counted by machine. R,F,L order
char closing_op_num = 0;

//enums for easy access 
//These are for easy access to labels during the UI printing 
const char daily_options[3][10] = {"Morning", "Afternoon", "Both"};
const char weekly_options[3][16] = {"Everyday", "Alt Start Sunday","Alt Start Monday"};

//Solenoids 
char sol_shift_list[NUM_SOLEN] = {0,1,2}; //Position of each solenoid pin

//DC MOTORS 
char dc_shift_list[NUM_DC_MOTORS] = {3,4,5}; //Position of each motor pin RA3-5

//STEPPERS
char stepper_shift_list[NUM_STEPPERS] = {2};  //Position of least significant motor pin

//Timer
#define PILL_REV_TIME 1 //IN SECONDS  
double time_from_timer0 = 0;  //global variable containing time from timer0

//RTC
char start_time_array[6]; 
char final_time_array[6];

//Sensors 
char sensor_shift_list[4] = {6,6,6,0}; //positions of each sensor pins LSB: RA6-7,RB6-7,RD6-7,RE0-1

//GLCD 
char glcd_op_num = 0;
const char op_names[NUM_DIVISIONS][32] = {"User Input", "Check Orientation", 
"Dispensing Pills", "Dispensing Pills", "Dispensing Pills", "Dispensing Pills", "Dispensing Pills", 
"Dispensing Pills", "Dispensing Pills", "Start Pill Return", "Closing Lids", "Closing Lids", "Closing Lids",
"Closing Lids", "Closing Lids", "Closing Lids", "Closing Lids", "Operation Complete"}; 