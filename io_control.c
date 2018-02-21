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
    assign_to_latx(SOLENOID,0, final);
    
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
    assign_to_latx(DC_MOTOR,0, final);
}

char read_reset_sensor(char sensor_name, char curr_state, char sensor_shift_list[4]){  //ASSUME sensor name is # of bits which must be shifted for 1st pin
    /*sensor_name os # of bits which must be shifted. Curr state is the register corresponding to the 
           sensor name that we're using */ 
    //Read value of sensor 
    char is_read = (curr_state >> sensor_shift_list[sensor_name]) & (0x01);
    //Write to sensor reset (pulse MSB)
    char old_curr_state = curr_state;
    curr_state = curr_state | (0x2 << sensor_shift_list[sensor_name]);
    __delay_us(SENSOR_HOLD_TIME); 
    printf("%x", curr_state);
    curr_state = old_curr_state; 
    assign_to_latx(SENSOR, sensor_name, curr_state);
    return is_read;
}