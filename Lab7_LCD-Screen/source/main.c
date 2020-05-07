/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;

enum States{wait, inc, dec, zero} state;

unsigned char button0;
unsigned char button1;

unsigned char tmpC;


void button_Tick(){
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;
	
	switch(state){ // Transitions
		case wait:
			if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
			else
				state = wait;
			break;
		case inc:
			if(button0 && !button1){
				state = inc; 
			}
			else if(button0 && button1){
				state = zero;
			}
			else
				state = wait;
			break;
		case dec:
			if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
			else
				state = wait;
			
			break;
		case zero:
			if(button0 && button1){
				state = zero;
			}
			else
				state = wait;
			break;
	
	}
	switch(state){ // State actions
		case wait:
			break;
		case inc:
			if(tmpC < 9)
				tmpC = tmpC + 1;
			break;
		case dec:
			if(tmpC > 0)
				tmpC = tmpC - 1;
			break;
		case zero:
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
	
	state = wait;
	tmpC = 0x00;
	while(1){
		LCD_Cursor(1);
		button_Tick();
		LCD_WriteData(tmpC + '0');
		while(!TimerFlag){}
		TimerFlag = 0;
	}
	// Starting at position 1 on the LCD screen, writes Hello World
	//LCD_DisplayString(1, "Hello World");
	
	//while(1) {continue;}
}
/*
    int main(void) {
    // Insert DDR and PORT initializations 
	DDRC = 0xFF; PORTC = 0x00; //LCD data Lines
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines

	//Initializes the LCD display
	 LCD_init();

	//starting at position 1 on the LCD screen, writes Hello World
	 LCD_DisplayString(1, "Hello World");
 
    // Insert your solution below
    while (1) {
	continue;
    }
    return 1;
}
*/
