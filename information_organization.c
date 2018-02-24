#include "information_organization.h"


void assign_to_latx(char latx, char dev_name, char pin_to_write) {
    switch (latx) {
        case DC_MOTOR :
           switch(dev_name){
                case CASEA : 
                    LATA = pin_to_write;
                    break;
                
                case CASEB : 
                    LATA = pin_to_write;
                    break;
                
               case CASEC : 
                    LATA = pin_to_write;
                    break;
            }
           break;
        
        case SENSOR : 
            switch(dev_name){
                case COLOR_SENSOR : 
                    LATA = pin_to_write;
                    break;
                
                case BREAK1 : 
                    LATA = pin_to_write;
                    break;
            }
            break;
        
        case SOLENOID : 
//            printf("0");
            switch(dev_name){
                case SOL_TIME : 
                    LATE = pin_to_write;
                    break;
                
                case SOL_TUBE_SWITCH : 
                    LATE = pin_to_write;
                    break;
                
                case SOL_CLOSE_BOX : 
                    LATE = pin_to_write;
                    break;
               
            }
            break;
        
        case STEPPER : 
            switch(dev_name) {
                case RACK :
                    LATB = pin_to_write;
                    break;
            }
            break;
    }
}

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

void deep_copy(char* copy_list, char* template_list, char sizeof_lists) {
    int i;
    for(i=0; i<sizeof_lists; i++) {
        copy_list[i] = template_list[i];
    }
}

void pill_dispense_logic_list(char* prescrip_list, char* logic_list, char sizeof_lists) {
    int i;
    for(i=0; i<sizeof_lists; i++) {
        if (prescrip_list[i] > 0) {
            logic_list[i] = 1;
        }
        else { logic_list[i] = 0; } 
    }
}

void decrement_remaining_pill_list(char* prescrip_list, char* was_dispensed_list, char sizeof_lists){
    int i;
    for(i=0; i<sizeof_lists; i++) {
        if (was_dispensed_list[i] > 0) {
            prescrip_list[i] -= 1;  //Note - later add error tolerance for debugging multiple pills @ once bug
        }
    }
}