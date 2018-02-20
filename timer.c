#include "timer.h"

void setup_timer0(void){
    T0CONbits.T08BIT = 0;  //configure as 16 bit counter 
    T0CONbits.T0CS = 0;  //set timer clock to internal CPU's
    T0CONbits.PSA = 0;  //enable the prescalar
    //Set prescalar factor of 256. Since XTAL = 40000000Hz, Fcpu = FOSC/4/ = 10Mhz. tCPU = 0.1us
    //Since each tick takes 256x as long, overflow time = 0.1 * (256)^2 = 0.0065536s 
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 1;
    T0CONbits.TMR0ON = 1;  //Turn on timer0
    
    //enable all interrupts 
    INTCONbits.GIE = 1; //GLOBAL INTERRRUPTS
    INTCONbits.PEIE = 1;  //Local interrupts
    INTCONbits.TMR0IE = 1;  //TIMER0 specific interrupt (I think)
}

