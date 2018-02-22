/* 
 * File:   eeprom.h
 * Author: RobertAdragna
 *
 * Created on February 21, 2018, 2:30 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "configBits.h"
#include "global_variables.h"  
 
void read_eeprom(char run_num, char eeprom_list[NUM_ENTRIES_LOG]);
void write_eeprom(char run_num, char data[NUM_ENTRIES_LOG]);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

