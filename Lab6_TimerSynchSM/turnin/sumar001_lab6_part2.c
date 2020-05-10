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

enum state {Start, Led1, Led2, Led3, dumy_Led, wait, reset}state;
void Tick(){

	A = ~PINA & 0x01;

	switch(state){ //transitions
		case Start:
		{
			tmpB = 0x00;
			state = Led1;
			break;
		}
		case Led1:
		{
			if(A) {
			state = wait; 
			break;
			}
			else{
			state = Led2; 
			break;
			}
		}
		case Led2:
		{
			if(A){		
				state = wait; 
				break;
				
			}
			else{
			state = Led3; 
			break;
			}
		}
		case Led3:
		{
			if(A){
				state = wait; 
				break;
			}
			else{
			state = dumy_Led; 
			break;
			}
		}
		case dumy_Led:
		{
			if(A){
			state = wait; 
			break;
			}
			else{
			state = Led1; 
			break;
			}
		}
		case wait:
			if(A)
			{
				state = wait; 
				break;
			}
			else
			{
				state = reset;
				 break;
			}
		case reset:
			if(A)
			{
				state = Led1; 
				break;
			}
			else
			{
				state = reset; 
				break;
			}
		default:
		break;
	}
	switch(state){ 
		case Start:{
		break;
		}
		case Led1:
		{
			tmpB = 0x01; 
			break;
		}
		case Led2:
		{
			tmpB = 0x02; 
			break;
		}
		case Led3:
		{
			tmpB = 0x04; 
			break;
		}
		case dumy_Led:
		{
			tmpB = 0x02; 
			break;
		}
		default:
		break;
	}
}

int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	state = Start;
	while(1) {
		PORTB = tmpB;
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
