#include "eeprom.h"

void read_eeprom(char run_num, char eeprom_list[NUM_ENTRIES_LOG]) {
    di(); //disable all interrupts 
    EECON1bits.EEPGD = 0;  //enable the eeprom 
    char start_address = run_num * NUM_ENTRIES_LOG;  //EEPROM starts from 0x00
    
    int i; 
    for (i=0; i<NUM_ENTRIES_LOG; i++) {
        EEADRH = 0; //set higher bits = 0
        EEADR = start_address + i;  // set address to correct place 
        EECON1bits.RD = 1; 
        eeprom_list[i]= EEDATA;
    }
    ei(); //enable all interrupts
}

void write_eeprom(char run_num, char data[NUM_ENTRIES_LOG]) {
    EECON1bits.EEPGD = 0;  //enable the eeprom 
    EECON1bits.WREN = 1; //Enable write 
    di();  //disable interrupts
    
    char start_address = run_num * NUM_ENTRIES_LOG;  //EEPROM starts from 0x00
    int i; 
    for (i=0; i<NUM_ENTRIES_LOG; i++) {
        EEADRH = 0; //set higher bits = 0
        EEADR = start_address + i;  // set write address to correct place
        EEDATA = data[i]; //input data to be written
        
        EECON2 = 0x55; 
        EECON2 = 0xAA; //Magic start sequence
        EECON1bits.WR = 1;  //Set write bit = 1
        
        while (EEIF == 0) {}  //EEIF is the finish write cycle bit: poll for when hits 1
        EEIF = 0;  //clear the interrupt bit     
    }
    ei();  //re-enable interrrupts 
    
}