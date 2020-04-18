/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #4  Exercise #1
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

enum States{Start, led2_on, wait, led1_on} state;

unsigned char input;
unsigned char tmpB;


void led_System(){
	switch(state){
		case Start:
			if(input == 1){
				state = led2_on;
			}
			else
				state = Start;
			break;
		
		case led2_on:
			if(input == 1){
				state = led2_on;
			}
			else
				state = wait;
			break;
		
		case wait:
			if(input == 1){
				state = led1_on;
			}
			else
				state = wait;
			break;
		
		case led1_on:
			if(input == 1){
				state = led1_on;
			}
			else
				state = Start;
			break;	
	}
	switch(state){
		case Start:
			tmpB = 0x01;
			break;
		
		case led2_on:
			tmpB = 0x02;
			break;
		
		case wait:
			tmpB = 0x02;
			break;
		
		case led1_on:
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
		input = PINA & 0x01;
		led_System();
		PORTB = tmpB;
	}
}
