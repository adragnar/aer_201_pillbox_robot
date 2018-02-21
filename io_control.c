#include "io_control.h"

void solenoid_control(char solen_name, char curr_state, char on_off) {  //note: on_off only 0,1
    //assumes that solenoids are in the X0, X1, X2 positions
    if (on_off == 1) {  //check to see whether to turn off or not
        on_off = on_off >> solen_name; //on+off is all 0s except 1 in pin position we want on
        //printf("%d",on_off);
    }
    else{
        on_off = 0; }
    
    curr_state = curr_state & ~solen_name;
    char final = on_off | curr_state; 
    assign_to_latx(SOLENOID, final);
    
}

void dc_motor_control(char motor_name, char curr_state, char motor_state) {
    curr_state = curr_state & ~motor_name; 
    switch(motor_name){
        case CASEA:
            motor_state = motor_state >> 0;
            break;
        case CASEB:
            motor_state = motor_state >> 2;
            break;
        case CASEC:
            motor_state = motor_state >> 4;
            break;
    }
    char final = motor_state | curr_state;
    assign_to_latx(DC_MOTOR, final);
}
