/*
 * File:   main.c
 * Author: Tyler Gamvrelis
 * 
 * Created on August 12, 2017, 5:40 PM
 * 
 * Description: Demonstration of some of the character LCD capabilities. Note
 *              that the more you use the standard print formatting library, the
 *              more memory your program will take up!
 * 
 * Precondition:
 *   1. Character LCD is in a PIC socket
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"
#include "timer.h"

#include "global_variables.h"
#include "ui_functions.h"
#include "information_organization.h"
#include "io_control.h"
#include "GLCD_PIC.h"
#include "px_ascii.h"

#include "major_mech_processses.h"
#include "tests.h"


void interrupt interruptHandler(void){
    /* This function is mapped to the interrupt vector, and so is called when
     * any interrupt occurs to handle it. Note that if any interrupt is enabled,
     * and it does not have a handler to clear it, then unexpected behavior will
     * occur, perhaps even causing the PIC to reset.
     *
     * Arguments: none
     * 
     * Returns: none
     */
    
    if(INT1IF){
        /* Interrupt on change handler for RB1. */
        
        //Interrupt handling for initial UI
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        if ((keypress == 11) && (current != 0) && (current != 1) && (current < 6)) {  //button C, back
            current -= 1;
            switch(current){
                case 1 : 
                    setup_dosage_screen(r_screen_base, prescription);
                case 2 :  
                    setup_dosage_screen(r_screen_base, prescription);
                case 3 :  
                    setup_dosage_screen(r_screen_base, prescription);
                case 4 : 
                    setup_daily_repeat_screen(daily_repeat); 
                case 5 : 
                    setup_weekly_repeat_screen(weekly_repeat);
                default :
                    break;
            }
        }
        
        if ((keypress == 10) && (current < 6)) {  //button 9 
            //deal with sum of pills > 4
            if (prescription[0] + prescription[1] + prescription[2] > 4){
                __lcd_clear();
                __lcd_home();
                printf("Too many pills");
                __lcd_newline();
                printf("Select < 4");
                __delay_ms(2000);
                setup_dosage_screen(r_screen_base, prescription); 
            }
            else {        
                current += 1;
                if ((current >= 1) && (current <= 3)){
                    lcd_set_cursor(r_screen_base + 4*(current-1),1);
                    }
                }
            }
        
        if ((keypress == 15) && (current >= 1) && (current <= 3)){  //button D, dosage screen
            switch(current){
                case 1 : 
                    if (prescription[current-1] == 2) {
                        prescription[current-1] = -1; 
                        break;
                    }
                case 2 :  
                     if (prescription[current-1] == 2) {
                        prescription[current-1] = -1; 
                        break;
                    }
                case 3 : 
                      if (prescription[current-1] == 3) {
                      prescription[current-1] = -1; 
                      break;
                    }   
            }
            prescription[current-1] += 1 ;
            printf("%d", prescription[current-1]);
            lcd_set_cursor(r_screen_base + 4*(current-1),1);
        }
        
        if ((keypress == 15) && (current == 4)){  //button D, daily repeat screen
            daily_repeat = (daily_repeat + 1) % 3;
            setup_daily_repeat_screen(daily_repeat);
        }
        
        if ((keypress == 15) && (current == 5)){ //button D, weekly repeat screen
            weekly_repeat = (weekly_repeat + 1) % 3; 
            setup_weekly_repeat_screen(weekly_repeat);
        }
        
        //Interrupt Handling for Final UI
        if ((keypress == 10) && (current > 6)) { //button 9, toggling thru final menu
            current += 1;  //note: may not give accurate values for some of the diverging screens 9-11
                           //but that's okay, corrected in while loop 
        }
        
        if (((keypress == 0) || (keypress == 1) || (keypress == 2))
                && (current == 8)){  //key 1-3, display final options screens
            switch (keypress) {
                case 0:  //key 1
                    current = 9;
                    break;
                case 1:  //key 2 
                    current = 10;
                    break;
                case 2:  //key 3
                    current = 11;
                    break;
             }
         } 
        INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
    }
    
    else if (TMR0IF) {
        time_from_timer0 += 0.0065536; //increment time 
        printf("%f",time_from_timer0);
        if (time_from_timer0 >= PILL_REV_TIME) {  //If enough time has passed to re-go through dispense cycle
            T0CONbits.TMR0ON = 0;  //Turn off timer0
        }
        TMR0IF = 0;
    }
    
}

void main(void){
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /********************************* PIN I/O ********************************/
    /* Write outputs to LATx, read inputs from PORTx. Here, all latches (LATx)
     * are being cleared (set low) to ensure a controlled start-up state. */  
    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    /* After the states of LATx are known, the data direction registers, TRISx
     * are configured. 0 --> output; 1 --> input. Default is  1. */
    TRISA = 0x40;  //Connected: Col sensor A6-7
    TRISB = 0xFF;  //Connected: Stepper B0-3
    TRISC = 0x40;
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x01;
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    ////
    //test_read_reset_sensor();
    ////
    setup_main_screen(); 
    while (current < 6) {
        switch(current) {
            case 0 :
                while(current == 0) {}  //Do nothing until external interrupt changes current
                break;
            
            case 1 :
                setup_dosage_screen(r_screen_base, prescription); 
                while(current == 1) {}  //Do nothing until external interrupt changes current
                break;   
            
            case 2 :
                setup_dosage_screen(r_screen_base, prescription); 
                while(current == 2) {}  //Do nothing until external interrupt changes current
                break;  
            
            case 3 :
                setup_dosage_screen(r_screen_base, prescription); 
                while(current == 3) {}  //Do nothing until external interrupt changes current
                break;
            
            case 4 :
                setup_daily_repeat_screen(daily_repeat); 
                while(current == 4) {}  //Do nothing until external interrupt changes current
                break;
            
            case 5 :
                setup_weekly_repeat_screen(weekly_repeat); 
                while(current == 5) {}  //Do nothing until external interrupt changes current
                break;   
            
            default :
                break;
                
        }
    }
    standby_screen(); 
    
    //Read from RTC 
    I2C_Master_Init(100000); //Initialize I2C Master with 100 kHz clock  
    di(); // Disable all interrupts  
    read_time(start_time_array);
    //////////////// Microcontroler Operation
    //Step 1: Data structures 
    populate_master_list(master_list, prescription, daily_repeat,weekly_repeat);  //setup internal structure
    char orient_val = read_reset_sensor(COLOR_SENSOR, PORTA, sensor_shift_list);  //read sensor value and reset colour sensor
    if (orient_val) {  //orient_val = 0, blue. =1, pink
        reverse_master_list(master_list);  //reverse list if needed 
        //printf("reverse");
    }
    //while(1){}
    
    //Testing populate master list 
//    printf("%d,%d,%d", master_list[0][0], master_list[0][1], master_list[0][2]);
//    printf("%d,%d,%d", master_list[1][0], master_list[1][1], master_list[1][2]);
//    __lcd_newline();
//    printf("%d,%d,%d", master_list[2][0], master_list[2][1], master_list[2][2]);
//    printf("%d,%d,%d", master_list[3][0], master_list[3][1], master_list[3][2]);
    ////////////////////
    
    //Step 2 The dispensing cycle 
    TRISB = 0x40;
    enable_stepper(RACK, PORTB, 1, stepper_shift_list); //turn on and bring stepper to starting point
    //while(1){}
    int i; 
    for(i=0; i<14; i=i+2) {  //day based dispense loop
        stepper_motor_control(RACK, PORTB, 1, FORWARD_STEPPER, stepper_shift_list);  //shift box forward
        //while(1){}
        __delay_ms(1000);
        dispense_pills(master_list[i], dc_shift_list, sensor_shift_list); //dispense all pills for first compartment
        solenoid_control(SOL_TIME, PORTA, 1, sol_shift_list);  //shift to other time
        __delay_ms(1000);
        dispense_pills(master_list[i+1], dc_shift_list, sensor_shift_list);  //dispense all pills for 2nd compartment
        solenoid_control(SOL_TIME, PORTA, 0, sol_shift_list);  //return solenoid home
    }
    //while(1){}
    
    //STEP 3 THE CLOSING CYCLE
    solenoid_control(SOL_TUBE_SWITCH, PORTA, 1, sol_shift_list);  //Switch to tube resevoir dispensing
    char was_dispensed_list[3]; //WERE PILLS DISPENSED ON LAST CYCLE
    char consec_no_drop[3] = {0,0,0};  //HOW MANY IN A ROW NOT DROPPRED FOR ALL PILLS
    //TURN ON CASE FEEDERS and WAIT
    dc_motor_control(CASEA, PORTA, 1, dc_shift_list);
    dc_motor_control(CASEB, PORTA, 1, dc_shift_list);
    dc_motor_control(CASEC, PORTA, 1, dc_shift_list);  
    __delay_ms(PILL_REV_TIME_FIRST); 
    //while(1){}
    while ((consec_no_drop[0] < FINISHED_NUM) || (consec_no_drop[1] < FINISHED_NUM)
            || (consec_no_drop[2] < FINISHED_NUM)) {  //WHILE SITLL PILLS IN RESEVOIRS 
        
        was_dispensed_list[0] = read_reset_sensor(BREAK1, PORTB, sensor_shift_list);
        was_dispensed_list[1] = read_reset_sensor(BREAK2, PORTC, sensor_shift_list);
        was_dispensed_list[2] = read_reset_sensor(BREAK3, PORTE, sensor_shift_list);
        update_leftover_count(was_dispensed_list, leftover_pills, 3);
        update_consecutive_no_drop(was_dispensed_list, consec_no_drop, 3);
        //close_box_step(closing_op_num); 
        __delay_ms(PILL_REV_TIME);
    }
    ///TEST CLOSING CYCLE 
    printf("%d,%d,%d:", consec_no_drop[0], consec_no_drop[1], consec_no_drop[2]);
    printf("%d,%d,%d", leftover_pills[0], leftover_pills[1], leftover_pills[2]);
    while(1){}
    ////////////////////
    //////////////////////////////
    __delay_ms(2000);
    read_time(final_time_array);
    ei(); //enable all interrupts
    /////////////////////////////////

    current = 7;
    while (1) {  // while loop to run final UI 
        switch(current) {
        case 7:   //initial done screen
            setup_end_screen();
            while (current == 7){}
            break;
            
        case 8: //present all additional info
            while (current == 8) {
                cycle_through_options();
            }
            printf("hello");
            break;
            
        case 9: 
            setup_final_time_elapsed_screen(start_time_array, final_time_array);
            while (current == 9){}
            current = 7;
            break;
            
        case 10: //info screen: leftover pills
            setup_pills_remaining_screen(leftover_pills);
            while (current == 10){}
            current = 7;
            break;
        
        case 11:   //info screen: prescription information
            while (current == 11){
                setup_run_summary_screen(prescription, daily_repeat, weekly_repeat);
            }
            current = 7;
            break;
        
        default: 
            break;
        }     
    }
}