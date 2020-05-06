/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #6  Exercise #3
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

enum States{start, inc, dec, reset, hold1,hold2} state;

unsigned char A0; //PA0 --> button0
unsigned char A1; //PA1 --> button1

unsigned char tmpC;


void Tick(){
	A0 = PINA & 0x01;
	A1 = PINA & 0x02;
		
	switch(state){ // Transitions
		case start:
			if(!A0 && !A1){
				state = start;
			}
			else if(A0 && !A1){
				state = inc;
			}
			else if(!A0 && A1){
				state = dec;
			}
			else if(A0 && A1){
				state = reset;
			}
			break;
		
		case inc:
			if(A0 && A1){
				state = reset;
			}
			else{
				state = hold2;
			}
			break;
		
		case dec:
			if(A0 && A1){
				state = reset;
			}
			else{
				state = hold2;
			}
			break;
		
		case reset:
			if(!A0 && !A1){
				state = start;
			}
			else if (A0 && !A1){
				state = inc;
			}
			else if(!A0 && A1){
				state = dec;
			}
			else if(A0 && A1){
				state = reset;
			}
			break;
		
		case hold1:
			if(A0 && A1){
				state = reset;
			}
			else if(A0 && !A1){
				state = inc;
			}
			else if(!A0 && A1){
				state = dec;
			}
			else{
				state = hold1;
			}
			break;
		
		case hold2:
			if(!A0 && !A1){
				state = hold1;
			}
			else if(A0 && A1){
				state = reset;
			}
			else{
				state = hold2;
			}
			break;
			
	}
	switch(state){ // State actions
		case start:
			break;
		case inc:
			if(tmpC < 9){
				tmpC += 1;
			}
			break;
		case dec:
			if(tmpC > 0){
				tmpC -= 1;
			}
			break;
		case reset:
			tmpC = 0;
			break;
	}			
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
										// initialize to 0s
																				
	state = start;
	tmpC = 0x07;

	while (1) 
    {		
		Tick();
		PORTC = tmpC;

	}

	return 0;
}

