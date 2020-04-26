/*	Author: sumar001
 *      Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start,init, hold, light} state;

unsigned char tmpB;


void Tick(){
      
	switch(state){//Transitions
		case start:
		tmpB = 0x00;
		state = init;
		break;
		
		case init:
		if((~PINA & 0x01) == 0x01)
		{
			state = light;
			 break;
		}
		else
		{
			state = init;
			 break;
		}
		
		case light:
		state = hold;
		break;
		
		case hold:
		if((~PINA & 0x01) == 0x01)
		{
			state = hold; 
			break;
		}
		else if((~PINA & 0x01) == 0x00)
		{
			state = init; 
			break;
		}
		
		default:
		break;
	}
	
	switch(state){ //State actions
		case start:
		break;
		
		case init:
		break;
		
		case light:
		if(tmpB == 0x00)
		{
			tmpB = 0x01; 
			break;
		}
		else if(tmpB == 0x2A)
		{
			tmpB = 0x00; 
			break;
		}
		else
		{
			tmpB = (tmpB << 1);
			if((tmpB & 0x04) == 0x04)
			{
				tmpB = tmpB | 0x01; 
				break;
			}
			break;
		}
		
		case hold:
		break;
		
		default:
		break;
	}
	
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = start;
	tmpB = 0x00;

	while(1)
	{
		Tick();
		PORTB = tmpB;
	}
}

