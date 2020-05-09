/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 // Demo: 

#include <avr/io.h>
#include <timer.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

	#define A0 (~PINA & 0x01)
	#define A1 (~PINA & 0x02)

enum states{start, init, inc, dec, reset, click} state;


	unsigned char B = 0x00;
	unsigned char counter = 0;

void Tick() {
	switch(state) {

		case start:
			state = init;
			break;

		case init:
			if(A0 && !A1) {
				state = inc;
				}
			else if(!A0 && A1) {
				state = dec;
				}
			else if(A0 && A1) {
				state = reset;
				}
			else {
				state = init;
				}
				break;

		case inc:
			state = click;
			break;

		case dec:
			state = click;
			 break;

		case reset:
			state = init;
			break;

		case click:
			if(A0 && !A1) {
				state = click;
				if(counter >= 10)
					{
					 state = init;
					 counter = 0;
					}
				}

			else if(!A0 && A1) {
				state = click;
				if(counter >= 10) {
					state = init;
					counter = 0;
					}
				}

			else {
				state = init;
			    }
				break;

		default:
			break;
	    }

	switch(state) {
		case start:
			break;

		 case init:
			break;
		
		case inc:
			if( B < 0x09) {
				B++;
			  }

		 case dec:
			if(B > 0x09) {
				B-- ;
			 }

		 case reset:
			B = 0x00;
			break;

		 case click:
			
			counter++;
			break;

		default:
			break;
		}
	}

int main(void) {
 DDRA = 0x00; PORTA = 0xFF;
 DDRB = 0xFF; PORTB = 0x00;

 B = 0x07;
 state = start;

 TimerSet(100);
 TimerOn();

 while(1) {
	Tick();
        PORTB = B;

	while(!TimerFlag) {}
		TimerFlag = 0;
	}
   return 1;
}

 



