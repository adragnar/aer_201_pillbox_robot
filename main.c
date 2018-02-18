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

void setup_main_screen();
void setup_dosage_screen(char screen_base, char* prescrip_list);
void setup_daily_repeat_screen(char repeat);
void setup_weekly_repeat_screen(char repeat);
void standby_screen();
void setup_end_screen();
void cycle_through_options();
void setup_pills_remaining_screen(char* leftover_count);
void setup_run_summary_screen(char* prescrip_list, char repeat_daily, char repeat_weekly);
void modified_setup_dosage_screen(char* prescrip_list); 
void setup_final_time_elapsed_screen(char* initial_setup_list, char* final_setup_list);

const char keys[] = "123A456B789C*0#D"; 

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
enum daily_options_values {MORNING, AFTERNOON, BOTH};
enum weekly_options_values {EVERYDAY, ALT_SUNDAY, ALT_MONDAY};

//RTC
char start_time_array[3]; 
char final_time_array[3];
void read_time(char* a);  
char find_operation_time(char* initial, char* final);  
char rtc_test(char* initial, char* final); //to execute test, run with start & final time arrays below setup_main-screen

//Tests
void test_populate_master_list(void);

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
    TRISA = 0xFF; // All inputs (this is the default, but is explicated here for learning purposes)
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
    while( current < 6) {
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
}

//Final UI Setup 
void setup_end_screen() {  //First completion screen user sees after operation finished
    __lcd_clear();
    __lcd_home(); 
    printf("Done Dispensing");
    __lcd_newline();
    printf("9:-> 1-3:toggle");

}

void cycle_through_options() {  //show user all options that they can access
    __lcd_clear();
    __lcd_home(); 
    printf("1:Operation Time");
    __lcd_newline();
    printf("2:Pills Left");
    __delay_ms(2000);
    __lcd_clear();
    __lcd_home(); 
    printf("3:Run Summary");
    __delay_ms(2000);
}

void setup_pills_remaining_screen(char* leftover_count) {  //print counted # of leftover pills 
    __lcd_clear();
    __lcd_home(); 
    printf("Leftover Count");
    __lcd_newline();
    printf("R:%d F:%d L:%d", leftover_count[0], leftover_count[1], leftover_count[2]);
}

void setup_run_summary_screen(char* prescrip_list, char repeat_daily, char repeat_weekly) {  //print full user prescription information
    modified_setup_dosage_screen(prescrip_list);
    __delay_ms(2000);
    setup_daily_repeat_screen(repeat_daily);
    __delay_ms(2000);
    setup_weekly_repeat_screen(repeat_weekly);
    __delay_ms(2000);
}

void modified_setup_dosage_screen(char* prescrip_list){  //setup_dosage without cursor
    __lcd_clear();
    __lcd_home(); 
    printf("Dosage");
    __lcd_newline();
    printf("R:%d F:%d L:%d", prescrip_list[0], prescrip_list[1], prescrip_list[2]); 
}

void setup_final_time_elapsed_screen(char* initial_setup_list, char* final_setup_list) {  //setup the final time screen
    char time_elapsed = find_operation_time(initial_setup_list, final_setup_list);  //get the final; time
    __lcd_clear();
    __lcd_home(); 
    printf("Time Elapsed");
    __lcd_newline();
    printf("%d seconds", time_elapsed);
}



//First UI setup 
//setup main screen of UI 
void setup_main_screen() {
    /* Initialize character LCD. */
    initLCD();
   
    /* Initial run sequence */
    __lcd_display_control(1, 0, 0);
    printf("Welcome");
    __delay_ms(1000);
    __lcd_clear();
    printf("9:forward c:back");
     __lcd_newline();
    printf("D:toggle");
    
}

//sets up the dosage screen with stored settings 
void setup_dosage_screen(char screen_base, char *prescrip_list) {
     __lcd_clear();
     __lcd_home(); 
      __lcd_display_control(1, 1, 1);
     printf("Choose Dosage");
     __lcd_newline();
     printf("R:%d F:%d L:%d", prescrip_list[0], prescrip_list[1], prescrip_list[2]); 
     lcd_set_cursor(screen_base + 4*(current-1),1);
}

void setup_daily_repeat_screen(char repeat) {    
    __lcd_clear();
    __lcd_home(); 
    printf("Day Repetition:");
    __lcd_newline();
    printf(daily_options[repeat]);
}

void setup_weekly_repeat_screen(char repeat) {    
    __lcd_clear();
    __lcd_home(); 
    printf("Week Repetition:");
    __lcd_newline();
    printf(weekly_options[repeat]);
}

void standby_screen() {
    __lcd_clear();
    __lcd_home(); 
    __lcd_display_control(1, 0, 0);
    printf("Please Wait");
    __lcd_newline();
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
//RTC Functions   
char rtc_test(char* initial, char* final) {
    __lcd_clear();
     __lcd_home();
    read_time(initial); 
    printf("%02x/%02x/%02x", initial[0],initial[1],initial[2]);
    __delay_ms(3000); 
    read_time(final);
    printf("%02x/%02x/%02x", final[0],final[1],final[2]);
    __lcd_newline();
    char final_time = find_operation_time(initial, final);
    printf("final_time %d", final_time);
    while(1){}
}

void read_time(char* a) {  //read the RTC to find out what time it is   
    
    /* Declare local variables. */  
    unsigned char time[7]; // Create a byte array to hold time read from RTC  
    unsigned char i; // Loop counter  
      
    I2C_Master_Start(); // Start condition  
    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write  
    I2C_Master_Write(0x00); // Set memory pointer to seconds  
    I2C_Master_Stop(); // Stop condition  

    /* Read current time. */  
    I2C_Master_Start(); // Start condition  
    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read  
    for(i = 0; i < 6; i++){  
        time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading  
    }  
    time[6] = I2C_Master_Read(NACK); // Final Read with NACK  
    I2C_Master_Stop(); // Stop condition       
    
    a[0] = time[0];
    a[1] = time[1];
    a[2] = time[2];
  
}  
 
char find_operation_time(char* initial, char* final) {  
    char elapsed_time_list[2];  
    elapsed_time_list[0] = final[0] - initial[0];  
    elapsed_time_list[1] = final[1] - initial[1];  
//    printf("%d, %d", initial[0], final[0]);  
    char elapsed_time = 60*elapsed_time_list[1] + elapsed_time_list[0];  
    return elapsed_time;  
}  