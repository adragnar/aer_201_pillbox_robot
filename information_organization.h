/* 
 * File:   information_organization.h
 * Author: RobertAdragna
 *
 * Created on February 20, 2018, 9:31 PM
 */

#ifndef INFORMATION_ORGANIZATION_H
#define	INFORMATION_ORGANIZATION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "configBits.h"
#include "global_variables.h"
#include "lcd.h"
    
//Internal Data Structure Functions 
void assign_to_latx(char latx, char dev_name, char pin_to_write);
void populate_master_list (char master_list[14][3], char* prescrip_list, char daily, char weekly);
void reverse_master_list(char master_list[14][3]);
void deep_copy(char* copy_list, char* template_list, char sizeof_lists);
void pill_dispense_logic_list(char* prescrip_list, char* logic_list, char sizeof_lists); 
void decrement_remaining_pill_list(char* prescrip_list, char* was_dispensed_list, char sizeof_lists);


#ifdef	__cplusplus
}
#endif

#endif	/* INFORMATION_ORGANIZATION_H */

