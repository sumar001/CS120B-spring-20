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

unsigned char A = 0x00; //button
  unsigned char tmpB = 0x00;
  unsigned char result = 0x00;
  unsigned char i = 0x00; //counter


enum States{start, led1, led2, led3, hold1, hold2, hold3}state;

void Tick(){
	switch (state) // Transitions
	{
		case start:
			state = led1;
			break;

		case led1:
			if(A){
				state = hold1;
			}
			else{
				state = led2;
			}
			break;

		case hold1:
			if(A){
				state = led1;
			}
			else{
				state = hold1;
			}
			break;

		case led2:
			if(A){
				state = hold2;
			}

			else if(i % 2 == 0){
				state = led1;
				i++;
			}

			else{
				state = led3;
			}
			break;

		case hold2:
			if(A){
				state = led1;
			}
			else{
				state = hold2;
			}
			break;

		case led3:
			if(A){
				state = hold3;
			}

			else{
				state = led2;
				i++;
			}
			break;

		case hold3:
			if(A){
				state = led1;
			}
			else{
				state = hold3;
			}
			break;
	}
	switch (state){ // State actions
		case led1:
			tmpB = 0x01;
			break;

		case hold1:
			tmpB = 0x01;
			break;

		case led2:
			tmpB = 0x02;
			break;

		case hold2:
			tmpB = 0x02;
			break;

		case led3:
			tmpB = 0x04;
			break;

		case hold3:
			tmpB = 0x04;
			break;

	}
  }
  

  int main()
  {
	  DDRA = 0x00; PORTA = 0xFF; // DDRA for input Button
	  DDRB = 0xFF; PORTB = 0x00; // DDRB for Led

	  TimerSet(300);
	  TimerOn();

	  state = start;

	  while(1) {
		 A = ~PINA & 0x01;
		
		Tick();
		while (!TimerFlag){}
		TimerFlag = 0;
		PORTB = tmpB;
		  
	  }
	  return 0;
  }

/*
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
}*/
