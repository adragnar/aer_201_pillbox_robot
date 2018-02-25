#include "major_mech_processses.h"

void dispense_pills(char* master_prescription, char* dc_motor_shift_list, char* stepper_shift_list) {
        char is_first = 1;
        char prescrip_x[3];
        char logic_list[3];
        char was_dispensed_list[3];
        deep_copy(prescrip_x, master_prescription, 3); //make a copy of data in prescrip_x
        
        while ((prescrip_x[0]>0) || (prescrip_x[1]>0) || (prescrip_x[2]>0)) {  //whule not all dispensed 
            create_pill_dispense_logic_list(prescrip_x, logic_list, 3); //generate the control signals 
            //Control the motors
            dc_motor_control(CASEA, PORTA, logic_list[0], dc_shift_list);
            dc_motor_control(CASEB, PORTA, logic_list[1], dc_shift_list);
            dc_motor_control(CASEC, PORTA, logic_list[2], dc_shift_list);
            //while(1){}
            if (is_first) {  //DIFFERENT DELAYS DEPEND ON WHETHER MOTOR HAS INTERTIA
                is_first = 0;
                __delay_ms(PILL_REV_TIME_FIRST);
            }
            else{ __delay_ms(PILL_REV_TIME); }
            //Check whether pills dispensed and decrement accordingly
            was_dispensed_list[0] = read_reset_sensor(BREAK1, PORTB, sensor_shift_list);
            was_dispensed_list[1] = read_reset_sensor(BREAK2, PORTC, sensor_shift_list);
            was_dispensed_list[2] = read_reset_sensor(BREAK3, PORTE, sensor_shift_list);
            decrement_remaining_pill_list(prescrip_x, was_dispensed_list, 3);
            //printf("%d,%d,%d", prescrip_x[0], prescrip_x[1], prescrip_x[2]);  
            //__delay_ms(5000);
        }   
}   
        
