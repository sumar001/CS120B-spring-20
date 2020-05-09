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

enum States {Start, INIT, INC, DEC, WAIT, RESET}state;

void Tick(){
	switch(state){ //Transitions
		case Start:
		{
			state = INIT;
			break;
		}
		
		case INIT:
		if((~PINA & 0x03) == 0x01)
		{
			state = INC; break;
		}
		else if((~PINA & 0x03) == 0x02)
		{
			state = DEC; break;
		}
		else if((~PINA & 0x03) == 0x03)
		{
			state = RESET; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case INC:
		state = WAIT;
		break;
		
		case DEC:
		state = WAIT;
		break;
		
		case WAIT:
		/*
		if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02))
		{
			state = WAIT; break;
		}
		*/
		if((~PINA & 0x03) == 0x01){
			state = DEC;break;
		}
		else if((~PINA & 0x03) == 0x02){
			state = INC;break;
		}
		else if((~PINA & 0x03) == 0x03)
		{
			state = RESET; break;
		}
		else if ((~PINA & 0x03) == 0x00){
			state = WAIT; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case RESET:
		if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02))
		{
			state = RESET; break;
		}
		else
		{
			state = INIT; break;
		}
		
		default:
		break;
	}
	switch(state){ //State actions
		case Start:
		{
			PORTB = 0x07;
		}
		break;
		
		case INIT:
		break;
		
		case INC:
		{
			if(PORTB >= 0x09)
			{
				PORTB = 0x09; break;
			}
			else
			{
				PORTB = PORTB + 0x01; break;
			}
		}
		
		case DEC:
		{
			if(PORTB <= 0x00)
			{
				PORTB = 0x00; break;
			}
			else
			{
				PORTB = PORTB - 0x01; break;
			}
		}
		
		case WAIT:
		break;
		
		case RESET:
		{
			PORTB = 0x00; break;
		}
	}
}

int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x07;
	TimerSet(10);
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



/*enum states{start, init, inc, dec, reset} state;

	unsigned char A0; //button A0
	unsigned char A1; //button A1
	unsigned char tmpB; //hold temporary value of portC


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
			if(A0 && !A1){
				state = inc; 
			}
			else if(A0 && A1){
				state = reset;
			}
			else
				state = init;
			break;

		case dec:
			if(!A0 && A1){
				state = dec;
			}
			else if(A0 && A1){
				state = reset;
			}
			else
				state = init;
			
			break;

		case reset:
			if(A0 && A1){
				state = reset;
			}
			else
				state = init;
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
*/
