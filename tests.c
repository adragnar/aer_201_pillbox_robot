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

void test_stepper_motor_control(void) {
    //Assume for test that Stepper at RB0-3
    //test artificially increases stepper actuate time 
    //Assumes stepper in RB2-3
    //Remember - often different pulses are too hard to see cause fast 
    __lcd_clear();
    __lcd_home();
    
    TRISB = 0X00;
    LATB = 0X00;
    char test_stepper_shift_list[NUM_STEPPERS] = {2}; 
    while (1) {
        stepper_motor_control(0, PORTB, 2, 0, test_stepper_shift_list);
        __delay_ms(5000);
        stepper_motor_control(0, PORTB, 2, 1, test_stepper_shift_list);
    }
}

void test_glcd(void) {
    
    /* Initialize GLCD. */
    initGLCD();
    
    /* Declare local variables. */
    unsigned char rotation = 0, x = 0, y = 0;
    
    /* Main loop. */
    while(1){
        /* Fill screen with red. */
        glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, RED);
        __delay_ms(1000);
        
        /* Fill screen with rainbow colors. */
        glcdDrawRectangle(0, 18, 0, GLCD_SIZE_VERT, RED);
        glcdDrawRectangle(18, 36, 0, GLCD_SIZE_VERT, ORANGE);
        glcdDrawRectangle(36, 54, 0, GLCD_SIZE_VERT, YELLOW);
        glcdDrawRectangle(54, 72, 0, GLCD_SIZE_VERT, GREEN);
        glcdDrawRectangle(72, 90, 0, GLCD_SIZE_VERT, BLUE);
        glcdDrawRectangle(90, 108, 0, GLCD_SIZE_VERT, INDIGO);
        glcdDrawRectangle(108, 128, 0, GLCD_SIZE_VERT, VIOLET);
        
        /* Demonstrate inversion. */
        __delay_ms(500);
        __INVON(); // Turn on color inversion
        __delay_ms(500);
        __INVOFF(); // Turn off color inversion
        __delay_ms(500);
        
        /* Draw white in the four corners pixels. */
        glcdDrawPixel(0, 0, WHITE);
        __delay_ms(500);
        glcdDrawPixel(GLCD_SIZE_HORZ, 0, WHITE);
        __delay_ms(500);
        glcdDrawPixel(GLCD_SIZE_HORZ, GLCD_SIZE_VERT, WHITE);
        __delay_ms(500);
        glcdDrawPixel(0, GLCD_SIZE_VERT, WHITE);
        __delay_ms(500);
        
        /* Place 128 pixels in accordance with some arbitrarily-chosen math. */
        for(x = 0; x < GLCD_SIZE_HORZ; x++){
            if(x % (GLCD_SIZE_VERT/16) == 0){
                glcdDrawPixel(GLCD_SIZE_VERT - (x * 8), (x % 3) * 33, x * 2048);
            }
            else{
                glcdDrawPixel(x, GLCD_SIZE_VERT - x, x * 2048);
            }
            __delay_ms(10);
        }
        
        /* Fill screen with blue/pink pattern, pixel-by-pixel. */
        for(y = 0; y < GLCD_SIZE_VERT; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, x*y*16);
            }
        }
        
        /* Fill screen with blue pattern, pixel-by-pixel. */
        for(y = 0; y < GLCD_SIZE_VERT; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, (x+8)*(y+8));
            }
        }
        
        /* Fill screen with green, pixel-by-pixel. Note the difference in speed
         * when using this method and when using the first method 
         * (glcdDrawRectangle). The first method is faster because we only have
         * to define the drawing window once, as the entire screen. The method
         * below re-defines the drawing window once per iteration, so
         * 128 * 128 = 16, 384 times. Thus, it is slower for filling the screen.
         * */
        for(y = 0; y < GLCD_SIZE_VERT; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, GREEN);
            }
        }
        
        /* Fill screen with black, and then demonstrate the pixel-by-pixel
         * addressing by drawing 5 lines slowly in white. The pixel-by-pixel
         * drawing is slower here intentionally so that you can see that each
         * pixel is indeed being addressed separately. */
        glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
        for(y = 0; y < 5; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, WHITE);
                __delay_ms(5);
            }
        }
        
        /* Rotate display at the end of each iteration. */
        switch(rotation % 4){
            case 0:
                glcdSetOrigin(ORIGIN_TOP_RIGHT);
                break;
            case 1:
                glcdSetOrigin(ORIGIN_BOTTOM_RIGHT);
                break;
            case 2:
                glcdSetOrigin(ORIGIN_BOTTOM_LEFT);
                break;
            case 3:
                glcdSetOrigin(ORIGIN_TOP_LEFT);
                break;
        }
        rotation++;
    }
}