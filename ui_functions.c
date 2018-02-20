#include "ui_functions.h"

//Initial UI setup 
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
