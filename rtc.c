#include "rtc.h"
   
char rtc_test(char initial[6], char final[6]) {
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

void read_time(char a[6]) {  //read the RTC to find out what time it is   
    
    /* Declare local variables. */  
    unsigned char time[7]; // Create a byte array to hold time read from RTC  
    unsigned char i; // Loop counter  
    //printf("t1");  
    I2C_Master_Start(); // Start condition  
    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write  
    I2C_Master_Write(0x00); // Set memory pointer to seconds  
    I2C_Master_Stop(); // Stop condition  
    //printf("t2"); 
    /* Read current time. */  
    I2C_Master_Start(); // Start condition  
    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read  
    for(i = 0; i < 6; i++){  
        time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading  
    }  
    time[6] = I2C_Master_Read(NACK); // Final Read with NACK  
    I2C_Master_Stop(); // Stop condition       
    //printf("t4"); 
    a[0] = time[0];
    a[1] = time[1];
    a[2] = time[2];
    a[3] = time[3];
    a[4] = time[4];
    a[5] = time[5];
}

char find_operation_time(char initial[6], char final[6]) {  
    char elapsed_time_list[2];  
    elapsed_time_list[0] = final[0] - initial[0];  
    elapsed_time_list[1] = final[1] - initial[1];  
//    printf("%d, %d", initial[0], final[0]);  
    char elapsed_time = 60*elapsed_time_list[1] + elapsed_time_list[0];  
    return elapsed_time;  
}  

void print_time_to_lcd(char write_list[6]) {  //modifies input list     
    I2C_Master_Init(100000); //Initialize I2C Master with 100 kHz clock  
    read_time(write_list);
    __lcd_home();
    printf("%02x/%02x/%02x", write_list[5],write_list[4],write_list[3]); // Print date in YY/MM/DD
    __lcd_newline();
    printf("%02x:%02x:%02x", write_list[2],write_list[1],write_list[0]); // HH:MM:SS
    __delay_ms(RTC_DELAY);
}