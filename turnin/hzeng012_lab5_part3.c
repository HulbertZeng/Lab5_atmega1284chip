 /* Author: Hulbert Zeng
 * Partner(s) Name (if applicable):  
 * Lab Section: 021
 * Assignment: Lab #5  Exercise #3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=7KYiBlCBx_M&feature=youtu.be
 */ 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum CL_States { CL_SMStart, CL_state0, CL_state1, CL_state2, CL_state3,
CL_buffer0, CL_buffer1, CL_buffer2, CL_buffer3 } CL_State;

void TickFct() {
    switch(CL_State) {
        case CL_SMStart:
            CL_State = CL_state0;
            break;
        case CL_state0:
            if((~PINA & 0x01) != 0x00) {
                CL_State = CL_buffer0;
            } else {
                CL_State = CL_state0;
            }
            break;
        case CL_buffer0:
            if((~PINA & 0x01) == 0x00) {
                CL_State = CL_state1;
            } else {
                CL_State = CL_buffer0;
            }
            break;
        case CL_state1:
            if((~PINA & 0x01) != 0x00) {
                CL_State = CL_buffer1;
            } else {
                CL_State = CL_state1;
            }
            break;
        case CL_buffer1:
            if((~PINA & 0x01) == 0x00) {
                CL_State = CL_state2;
            } else {
                CL_State = CL_buffer1;
            }
            break;
        case CL_state2:
            if((~PINA & 0x01) != 0x00) {
                CL_State = CL_buffer2;
            } else {
                CL_State = CL_state2;
            }
            break;
        case CL_buffer2:
            if((~PINA & 0x01) == 0x00) {
                CL_State = CL_state3;
            } else {
                CL_State = CL_buffer2;
            }
            break;
        case CL_state3:
            if((~PINA & 0x01) != 0x00) {
                CL_State = CL_buffer3;
            } else {
                CL_State = CL_state3;
            }
            break;
        case CL_buffer3:
            if((~PINA & 0x01) == 0x00) {
                CL_State = CL_state0;
            } else {
                CL_State = CL_buffer3;
            }
            break;
    }
    switch(CL_State) {
        case CL_SMStart:
            PORTC = 0x00;
            break;
        case CL_state0:
            PORTC = 0x15;
            break;
        case CL_state1:
            PORTC = 0x36;
            break;
        case CL_state2:
            PORTC = 0x2A;
            break;
        case CL_state3:
            PORTC = 0x1B;
            break;
        case CL_buffer0:
            break;
        case CL_buffer1:
            break;
        case CL_buffer2:
            break;
        case CL_buffer3:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    CL_State = CL_SMStart;
    /* Insert your solution below */
    while (1) {
        TickFct();
    }
    return 1;
}
