 /* Author: Hulbert Zeng
 * Partner(s) Name (if applicable):  
 * Lab Section: 021
 * Assignment: Lab #5  Exercise #1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?reload=9&v=EB_ATcMjlC4&feature=youtu.be
 */ 
#include <avr/io.h>
#include <math.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum CF_States { CF_SMStart, CF_init } CF_State;

unsigned char car_fuel() {
    unsigned char levels = 0x00;
    unsigned char lowfuel = 0x00;

    if((~PINA & 0x0F) > 0) {
        levels = levels | 0x20;
    }
    if((~PINA & 0x0F) > 2) {
        levels = levels | 0x10;
	    }
    if((~PINA & 0x0F) > 4) {
        levels = levels | 0x08;
    }
    if((~PINA & 0x0F) > 6) {
        levels = levels | 0x04;
    }
    if((~PINA & 0x0F) > 9) {
        levels = levels | 0x02;
    }
    if((~PINA & 0x0F) > 12) {
        levels = levels | 0x01;
    }
    lowfuel = ((~PINA & 0x0F) < 5) ? 0x40 : 0x00;

    return levels + lowfuel;
}

void TckFct_Latch() {
    switch(CF_State) {
        case CF_SMStart:
            CF_State = CF_init;
            break;
        case CF_init:
            CF_State = CF_init;
            break;
    }

    switch(CF_State) {
        case CF_SMStart:
            PORTC = 0x00;
            break;
        case CF_init:
            PORTC = car_fuel();
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    CF_State = CF_SMStart;
    /* Insert your solution below */
    while (1) {
        TckFct_Latch();
    }
    return 1;
}
