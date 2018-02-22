#include "information_organization.h"


void assign_to_latx(char latx, char dev_name, char pin_to_write) {
    switch (latx) {
        case DC_MOTOR :
            LATA = pin_to_write;
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
        
        case SOLENOID : 
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
