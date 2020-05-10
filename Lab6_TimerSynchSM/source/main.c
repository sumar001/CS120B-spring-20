/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 // Demo: https://drive.google.com/file/d/10Q1qbAuI7HnRNWWv9Yeq71VVhnyKABzB/view?usp=sharing 

#include <avr/io.h>
#include <timer.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char A = 0x00; //PA0
	unsigned char tmpB = 0x00;
	unsigned char i = 0x00; 

enum States{start, Led1, Led2, Led3, hold1, hold2, hold3} state;

void Tick() {
	switch(state) {
		case start: 
			state = Led1;
			break;

		case Led1:
			if(A)
				state = hold1;
			else
				state = Led2;
			break;

		case hold1:
			if(A)
				state = Led1;
			else
				state = hold1;
			break;

		case Led2:
			if(A)
				state = hold2;
			else if(i % 2 == 0){
				state = Led1;
				i++ ;
			}
			else {
				state = Led3;
			}
			break;

		case hold2:
			if(A)
				state = Led1;
			else
				state = hold2;
			break;

		case Led3:
			if(A)
				state = hold3;
			else {
				state = Led2;
				i++ ;
			}

			break;

		case hold3:
			if(A)
				state = Led1;
			else
				state = hold3;
			break;
	}

	switch(state) {
		case Led1:
			tmpB = 0x01;
			break;

		case hold1:
			tmpB = 0x01;
			break;

		case Led2:
			tmpB = 0x02;
			break;

		case hold2:
			tmpB = 0x02;
			break;

		case Led3:
			tmpB = 0x04;
			break;
			
		case hold3:
			tmpB = 0x04;
			break;
	}
}

int main()
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	TimerSet(300);
	TimerOn();

	state = start;

	while(1) {
		A = ~PINA & 0x01;
		Tick();

		while(!TimerFlag);
		TimerFlag = 0;

		PORTB = tmpB;
	}
	return 1;
}

