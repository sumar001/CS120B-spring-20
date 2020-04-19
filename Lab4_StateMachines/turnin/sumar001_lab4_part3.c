/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <stdio.h>
#include <stdlib.h>
#endif

enum States{Start,locked, hold, release, unlocked} state;

unsigned char b_X; //button for X
unsigned char b_Y; //button for Y
unsigned char b_Pound; //button for #
unsigned char b_Lock; //button from inside the house

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
