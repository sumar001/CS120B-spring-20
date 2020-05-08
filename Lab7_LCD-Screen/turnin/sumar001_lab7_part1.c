/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 // Demo: https://drive.google.com/open?id=1KpEbqHar7_Y-hQs7_RiU6Pznkw__nqI2
 
#include <avr/io.h>
#include "io.h"
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{start, init, inc, dec, reset} state;

	unsigned char A0; //button A0
	unsigned char A1; //button A1
	unsigned char tmpC; //hold temporary value of portC


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
			if(tmpC < 9)
				tmpC++ ;
			break;

		case dec:
			if(tmpC > 0)
				tmpC--;
			break;

		case reset:
			tmpC = 0;
			break;
	
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A input initialize to 0xFF
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines

	TimerSet(1000);
	TimerOn();
	
	// Initializes the LCD display
	LCD_init();	
	LCD_ClearScreen();
	
	state = start;
	tmpC = 0x00;
	
	while(1){
		LCD_Cursor(1);
		Tick();
		LCD_WriteData(tmpC + '0');
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}
