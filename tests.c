#include "tests.h"

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
    //assumes solenoids are E0,E1,E2
    __lcd_clear();
    __lcd_home();
    TRISE = 0X00;
    
    char test_sol_shift_list[3] = {0,1,2};
    LATE = 0XFF;
    while (1) {
        solenoid_control(SOL_TIME, PORTE, 0, test_sol_shift_list); 
        __delay_ms(1000); 
        solenoid_control(SOL_TIME, PORTE, 1, test_sol_shift_list);
        __delay_ms(1000);
        solenoid_control(SOL_TUBE_SWITCH, PORTE, 0, test_sol_shift_list); 
        __delay_ms(1000); 
        solenoid_control(SOL_TUBE_SWITCH, PORTE, 1, test_sol_shift_list);
        __delay_ms(1000);
        solenoid_control(SOL_CLOSE_BOX, PORTE, 0, test_sol_shift_list); 
        __delay_ms(1000); 
        solenoid_control(SOL_CLOSE_BOX, PORTE, 1, test_sol_shift_list);
        __delay_ms(1000);
    }
}

void test_dc_motor_control(void) {
    __lcd_clear();
    __lcd_home();
    
    TRISA = 0X00;
    LATA = 0X00;
    char test_dc_shift_list[3] = {0,1,2};
    while (1) {
        dc_motor_control(CASEA, PORTA, 1, test_dc_shift_list); 
        __delay_ms(1000); 
        dc_motor_control(CASEA, PORTA, 0, test_dc_shift_list); 
        __delay_ms(1000);
        dc_motor_control(CASEB, PORTA, 1, test_dc_shift_list); 
        __delay_ms(1000);
        dc_motor_control(CASEB, PORTA, 0, test_dc_shift_list); 
        __delay_ms(1000);
        dc_motor_control(CASEC, PORTA, 1, test_dc_shift_list); 
        __delay_ms(1000);
        dc_motor_control(CASEC, PORTA, 0, test_dc_shift_list);
    }
    while(1){}
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

void test_read_reset_sensor(void) {
    __lcd_clear();
    __lcd_home();
    
    TRISA = 0x10;
    char test_sensor_shift_list[4] = {4,4,4,4};
    char ans = read_reset_sensor(0, PORTA, test_sensor_shift_list);
    printf("%d",ans);
    while(1){}
}

void test_eeprom(void) {
    //Assume for test that NUM_LOG_ENTRIES = 1
    __lcd_clear();
    __lcd_home();
    
    char data[1] = {5};
    write_eeprom(0,data);
    char read_data[1];
    read_eeprom(0,read_data);
    printf("%d",read_data[0]);
    
    //now at different address
    char data[1] = {8};
    write_eeprom(32,data);
    char read_data[1];
    read_eeprom(32,read_data);
    printf("%d",read_data[0]);
    while(1){}
    
}