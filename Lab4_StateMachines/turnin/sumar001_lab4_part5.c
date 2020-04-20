/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start,locked,hold,release,unlocked,hold2,release2 } state;

unsigned char array[4] = {0x04,0x01, 0x02, 0x01}; //button sequence
unsigned char i = 0;
unsigned char b_X;
unsigned char b_Y;
unsigned char b_Pound;
unsigned char b_Lock;
unsigned char tmpB;


void lock_system_Tick(){
	b_X = PINA & 0x01;
	b_Y = PINA & 0x02;
	b_Pound = PINA & 0x04;
	b_Lock = PINA & 0x80;
		
	switch(state){ // Transitions
		
		case Start:
			state = locked;
			 break;

		case locked:
			if(b_Lock){
				state = locked;
			}
			if(!b_X && !b_Y && b_Pound && !b_Lock){
				state = hold;
			}
			else{
				state = locked;
			}
			break;
		
		case hold:
			if(!b_X && !b_Y && b_Pound && !b_Lock){
				state = hold;
			}
			else if(!b_X && !b_Y && !b_Pound && !b_Lock){
				state = release;
			}
			else{
				state = locked;
			}
			break;
		
		case release:
			if(!b_X && !b_Y && !b_Pound && !b_Lock){
				state = release;
			}
			else if(!b_X && b_Y && !b_Pound && !b_Lock){
				state = unlocked;
			}
			else{
				state = locked;
			}
			break;
		
		case unlocked:
			if(!b_X && !b_Y && !b_Pound && b_Lock){
				state = locked;
			}
			else if(!b_X && !b_Y && b_Pound && !b_Lock){
				state = hold2;
			}
			else {
				state = unlocked;
			}
			 break;

		case hold2:
			if(!b_X && !b_Y && !b_Pound && !b_Lock){
				state = release2;
			}
			else if(!b_X && !b_Y && !b_Pound && b_Lock){
				state = locked;
			}
			else if(!b_X && !b_Y && b_Pound && !b_Lock){
				state = hold2;
			}
			else{
				state = unlocked;
			}
			break;	
		
		case release2:
			if(!b_X && !b_Y && !b_Pound && b_Lock || !b_X && b_Y && !b_Pound && !b_Lock){
				state = locked;
			}
			else if(!b_X && !b_Y && !b_Pound && !b_Lock){
				state = release2;
			}
			else{
				state = unlocked;
			}
			break;
	}
	
	switch(state){ // State actions
		case Start:
			break;

		case locked:
			tmpB = 0x00;
			break;
		
		case hold:
			break;
		
		case release:
			break;
			break;
		
		case hold2:
			break;

		case release2:
			break;
		case unlocked:
			tmpB = 0x01;
			break;
	}			
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
										// initialize to 0s
																				
	state = Start;

	while (1) 
    {		
		lock_system_Tick();
		PORTB = tmpB;

	}

	return 0;
}
