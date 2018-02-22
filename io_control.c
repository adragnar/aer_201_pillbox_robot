#include "io_control.h"

void solenoid_control(char solen_name, char curr_state, char on_off, char sol_shift_list[NUM_SOLEN]) {  //note: on_off only 0,1
    curr_state = curr_state & ~(0x01 << sol_shift_list[solen_name]);  //get curr_state with sol bit = 0
    on_off = on_off << (sol_shift_list[solen_name]);  //get on_off = on_off bit in sol bit position surrounded by 0s  
    //printf("%d", on_off);
    char final = on_off | curr_state;  //this keeps curr state unchanged except sol_bit, set to on_off 
    //printf("%d",final);
    assign_to_latx(SOLENOID, solen_name, final);
    
}

void dc_motor_control(char motor_name, char curr_state, char on_off, char dc_shift_list[NUM_DC_MOTORS]) {
    curr_state = curr_state & ~(0x01 << dc_shift_list[motor_name]);  //get curr_state with sol bit = 0
    on_off = on_off << (dc_shift_list[motor_name]);  //get on_off = on_off bit in sol bit position surrounded by 0s  
    //printf("%d", on_off);
    char final = on_off | curr_state;  //this keeps curr state unchanged except sol_bit, set to on_off 
    //printf("%d",final);
    assign_to_latx(DC_MOTOR, motor_name, final);
}

char read_reset_sensor(char sensor_name, char curr_state, char sensor_shift_list[4]){  //ASSUME sensor name is # of bits which must be shifted for 1st pin
    /*sensor_name os # of bits which must be shifted. Curr state is the register corresponding to the 
           sensor name that we're using */ 
    //Read value of sensor 
    char is_read = (curr_state >> sensor_shift_list[sensor_name]) & (0x01);
    //Write to sensor reset (pulse MSB)
    char old_curr_state = curr_state;
    curr_state = curr_state | (0x2 << sensor_shift_list[sensor_name]);  //set the reset bit high
    __delay_us(SENSOR_HOLD_TIME); 
//    printf("%x", curr_state);
    curr_state = old_curr_state; 
    assign_to_latx(SENSOR, sensor_name, curr_state);
    return is_read;
}