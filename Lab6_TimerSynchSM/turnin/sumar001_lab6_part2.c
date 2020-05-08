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

enum dummyMachine {Start, Light1, Light2, Light3, Light4, wait,restart}state;
void Tick(){
	switch(state){ //transitions
		case Start:
		{
			PORTB = 0x00;
			state = Light1;
			break;
		}
		case Light1:
		{
			if((~PINA&0x01) == 0x01){
			state = wait; break;
			}
			else{
			state = Light2; break;
			}
		}
		case Light2:
		{
			if((~PINA&0x01) == 0x01){		
				state = wait; break;
				
			}
			else{
			state = Light3; break;
			}
		}
		case Light3:
		{
			if((~PINA&0x01) == 0x01){
				state = wait; break;
			}
			else{
			state = Light4; break;
			}
		}
		case Light4:
		{
			if((~PINA&0x01) == 0x01){
			state = wait; break;
			}
			else{
			state = Light1; break;
			}
		}
		case wait:
			if((~PINA & 0x01) == 0x01)
			{
				state = wait; break;
			}
			else
			{
				state = restart; break;
			}
		case restart:
			if((~PINA & 0x01) == 0x01)
			{
				state = Light1; break;
			}
			else
			{
				state = restart; break;
			}
		default:
		break;
	}
	switch(state){ 
		case Start:{
		break;
		}
		case Light1:
		{
			PORTB = 0x01; break;
		}
		case Light2:
		{
			PORTB = 0x02; break;
		}
		case Light3:
		{
			PORTB = 0x04; break;
		}
		case Light4:
		{
			PORTB = 0x02; break;
		}
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x00;
	TimerSet(50);
	TimerOn();
	state = Start;
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
	}
}
