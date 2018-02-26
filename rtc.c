#include "rtc.h"
   
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
    printf("t1");  
    I2C_Master_Start(); // Start condition  
    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write  
    I2C_Master_Write(0x00); // Set memory pointer to seconds  
    I2C_Master_Stop(); // Stop condition  
    printf("t2"); 
    /* Read current time. */  
    I2C_Master_Start(); // Start condition  
    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read  
    for(i = 0; i < 6; i++){  
        time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading  
    }  
    time[6] = I2C_Master_Read(NACK); // Final Read with NACK  
    I2C_Master_Stop(); // Stop condition       
     printf("t4"); 
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
