/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

	unsigned char button = 0x00;
	unsigned char tmpB = 0x00;

enum States{Init, Led1, Led2, Led3, hold1, hold2, hold3} state;

void Tick() {
	switch(state) {
		case Init: 
			state = Led1;
			break;

		case Led1:
			if(button)
				state = hold1;
			else
				state = Led2;
			break;

		case hold1:
			if(button)
				state = Led1;
			else
				state = hold1;
			break;

		case Led2:
			if(button)
				state = hold2;
			else
				state = Led3;
			break;

		case hold2:
			if(button)
				state = Led2;
			else
				state = hold2;
			break;

		case Led3:
			if(button)
				state = hold3;
			else
				state = Led1;
			break;

		case hold3:
			if(button)
				state = Led3;
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
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;

	TimerSet(300);
	TimerOn();

	state = Init;

	while(1) {
		button = ~PINA & 0x08;
		Tick();

		while(!TimerFlag);
		TimerFlag = 0;

		PORTB = tmpB;
	}
	return 1;
}
