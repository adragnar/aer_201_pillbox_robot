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

//Timer 
void setup_timer0(void);

//actuator_control_functions
void solenoid_control(char solen_name, char curr_state, char on_off);
void dc_motor_control(char motor_name, char curr_state, char motor_state);

//I/O Pin Enums 
void assign_to_latx(char latx, char pin_to_write);



//Internal Data Structure Functions 
void populate_master_list (char master_list[14][3], char* prescrip_list, char daily, char weekly);
void reverse_master_list(char master_list[14][3]);

//Tests
void test_populate_master_list(void);
void test_reverse_master_list(void);
void test_solenoid_control(void);
void test_dc_motor_control(void);
void test_timer0(void);

void assign_to_latx(char latx, char pin_to_write) {
    switch (latx) {
        case DC_MOTOR :
            LATA = pin_to_write;
            break;
        case SOLENOID : 
            LATE = pin_to_write;
            break;
    }
}

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

//Information Organization Functions 
void populate_master_list (char master_list[14][3], char* prescrip_list, char daily, char weekly) { //initialize master list from UI data
    
    int i,j;
    switch(weekly) {
        case EVERYDAY:
            switch(daily) {
                case MORNING: 
                    //printf("hi");
                    //
                    //master_list[0][0] = 3;
                    //printf("%d",master_list[0][0]);
                    //
                    for (i=0; i<14; i=i+2){
                        for (j=0; j<3; j++) {
                            master_list[i][j] = prescrip_list[j];
                            //printf("%d", prescrip_list[j]);
                            //printf("%d",master_list[i][j]);
                        }   
                    }     
                    break;
                    
                case AFTERNOON:
                    for (i=1; i<14; i=i+2){
                        for (j=0; j<3; j++) {
                            master_list[i][j]=prescrip_list[j];
                        }
                    }    
                    break;
                    
                case BOTH:
                    for (i=0; i<14; i++){
                        for (j=0; j<3; j++) {
                            master_list[i][j]=prescrip_list[j];
                        }   
                    }
                    break;
            }   
        case ALT_SUNDAY:   
            switch(daily) {
                case MORNING: 
                    for (i=0; i<14; i=i+4){
                        for (j=0; j<3; j++) {
                            master_list[i][j]=prescrip_list[j];
                        }
                    }  
                    break;
                    
                case AFTERNOON:
                    for (i=1; i<14; i=i+4){
                        for (j=0; j<3; j++) {
                            master_list[i][j]=prescrip_list[j];
                        }
                    }                      
                    break;
                
                case BOTH:
                    i = 0;
                    while (i < 13) {  //while loop to increment by different amounts 
                        if (i%2 == 0) {
                           master_list[i][j]=prescrip_list[j];
                           i += 1; 
                        }
                        else {
                            master_list[i][j]=prescrip_list[j];
                            i += 3;
                        }
                    }
                    break;
                }
        
        case ALT_MONDAY:
             switch(daily) {
                case MORNING: 
                    for (i=2; i<14; i=i+4){
                        for (j=0; j<3; j++) {
                            master_list[i][j]=prescrip_list[j];
                        }
                    }  
                    break;
                    
                case AFTERNOON:
                    for (i=3; i<14; i=i+4){
                        for (j=0; j<3; j++) {
                            master_list[i][j]=prescrip_list[j];
                        }
                    }                      
                    break;
                
                case BOTH:
                    i = 2;
                    while (i < 14) {  //while loop to increment by different amounts 
                        if (i%2 == 0) {
                           master_list[i][j]=prescrip_list[j];
                           i += 1; 
                        }
                        else {
                            master_list[i][j]=prescrip_list[j];
                            i += 3;
                        }
                    }
                    break;
                }         
            
            
        }      
    }

void reverse_master_list(char master_list[14][3]) {
    __lcd_clear();
    __lcd_home();
    
    char i,j;
    char temp[14][3];
    
    //copy values of master list into temp copy 
    for (i=0; i<14; i++) {  //swap the values of master list
        for (j=0; j<3; j++) {
            temp[i][j] = master_list[i][j];
        }
    }
    for (i=0; i<14; i++) {  //swap the values of master list
        for (j=0; j<3; j++) {
            master_list[i][j] = temp[13-i][j];
        }
    }
}

void test_populate_master_list (void) {
    __lcd_clear();
    __lcd_home();
    
    char test_master_list[14][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                            {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    char test_daily = 1;
    char test_weekly = 2;
    char test_prescrip_list[3] = {1,1,1};
    
    populate_master_list(test_master_list, test_prescrip_list, test_daily, test_weekly);
    printf("%d:", test_master_list[0][0]);
    printf("%d:", test_master_list[1][0]);
    printf("%d:", test_master_list[2][0]);
    printf("%d:", test_master_list[3][0]);
    __lcd_newline();
    printf("%d:", test_master_list[4][0]);
    printf("%d:", test_master_list[5][0]);
    printf("%d:", test_master_list[6][0]);
    printf("%d:", test_master_list[7][0]);
    printf("%d:", test_master_list[8][0]);   
}   

void test_reverse_master_list(void) {
    char test_master_list[14][3] = {{1,1,1}, {2,2,2}, {3,3,3}, {4,4,4}, {5,5,5}, {6,6,6},
        {7,7,7}, {8,8,8},{9,9,9}, {10,10,10},{11,11,11}, {12,12,12},{13,13,13}, {14,14,14}};
    reverse_master_list(test_master_list);
    printf("%d,%d", test_master_list[0][0], test_master_list[13][0]);
}

void test_solenoid_control(void) {
    __lcd_clear();
    __lcd_home();
    
    LATE = 0XFF;
    while (1) {
        solenoid_control(SOL_TIME, PORTE, 0); 
        __delay_ms(1000); 
        solenoid_control(SOL_TIME, PORTE, 1);
        __delay_ms(1000);
    }
}

void test_dc_motor_control(void) {
    __lcd_clear();
    __lcd_home();
    initLCD();
   
    /* Initial run sequence */
    __lcd_display_control(1, 0, 0);
    
    
    LATA = 0XFF;
    while (1) {
        dc_motor_control(CASEA, PORTA, BRAKE_DC); 
        printf("1");
        __delay_ms(1000); 
        dc_motor_control(CASEA, PORTA, REST_DC);
        printf("2");
        __delay_ms(1000);
        dc_motor_control(CASEA, PORTA, FORWARD_DC);
        printf("3");
        __delay_ms(1000);
    }
}

void test_timer0(void) {
    __lcd_clear();
    __lcd_home();
    setup_timer0();
    while(1) {
        if (time_from_timer0 >= PILL_REV_TIME){
            break;
        }
    }
    __lcd_clear();
    __lcd_home();
    printf("%f",time_from_timer0);
    while(1){}
}

//Actuator Control Functions 
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
    TRISA = 0x00; 
    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x00;
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    ////
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
    //while (1){}  //execute program operations of actual microcontroller 
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