/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 // Demo: https://drive.google.com/file/d/1GhkuVT9mRl-tu1DEecPLb-ysNX6TS4ZO/view?usp=sharing 

#include <avr/io.h>
#include <timer.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

			

enum states{start, init, inc, dec, reset, b_hold} state;

	unsigned char A0; //button A0
	unsigned char A1; //button A1
	unsigned char tmpB; //hold temporary value of portB
	unsigned char i = 0; //counter => so that if button is held, it will inc/dec at a rate of 1s

void Tick(){
	A0 = ~PINA & 0x01;
	A1 = ~PINA & 0x02;
	
	switch(state){ // Transitions
		case start:
				state = init;
				break;

		case init:
			if(!A0 && A1){
				state = dec;
			}
			else if(A0 && !A1){
				state = inc;
			}
			else if(A0 && A1){
				state = reset;
			}
			else
				state = init;
			break;

		case inc:
		//	if(A0 && !A1){
		//		state = inc; 
		//	}
		//	else if(A0 && A1){
		//		state = reset;
		//	}
		//	else
		//		state = init;
		//	break;
		        state = b_hold;
			break;

		case dec:
			//if(!A0 && A1){
			//	state = dec;
			//}
			//else if(A0 && A1){
			//	state = reset;
		//	}
		//	else
		//		state = init;
			state = b_hold;
			break;

		case reset:
//			if(A0 && A1){
//				state = reset;
//			}
//			else
				state = init;
			break;

		case b_hold:
			if(A0 && !A1) {
				state = b_hold;
				if(i >= 10) {
					state = init;
					i = 0;
				}
			}

			else if(!A0 && A1) {
				state = b_hold;
				if(i >= 10) {
					state = init;
					i = 0;
				}
			}
			else {
				state = init;
			}
			break;

	
	}
	switch(state){ // State actions
		case init:
			break;

		case inc:
			if(tmpB < 9)
				tmpB++ ;
			break;

		case dec:
			if(tmpB > 0)
				tmpB--;
			break;

		case reset:
			tmpB = 0;
			break;

		case b_hold:
			i++;
	
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 

	TimerSet(100);
	TimerOn();
	
	state = start;
	tmpB = 0x07;
	
	while(1){
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
		PORTB = tmpB;
	}
}

