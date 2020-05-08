/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
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
  unsigned char score = 0x00;


  enum States{light1, wait1, light2, wait2, light3, wait3}state;

void lightTick(){
	switch (state) // Transitions
	{
		case light1:
			if(tmpA){
				state = wait1;
				if(score > 0)
					score = score -1;
			}
			else{
				state = light2;
			}
			break;
		case wait1:
			if(tmpA){
				state = light1;
			}
			else{
				state = wait1;
			}
			break;
		case light2:
			if(tmpA){
				state = wait2;
				if(score < 9)
					score = score + 1;
			}
			else{
				state = light3;
			}
			break;
		case wait2:
			if(tmpA){
				state = light2;
			}
			else{
				state = wait2;
			}
			break;
		case light3:
			if(tmpA){
				state = wait3;
				if(score > 0)
					score = score - 1;
			}
			else{
				state = light1;
			}
			break;
		case wait3:
			if(tmpA){
				state = light3;
			}
			else{
				state = wait3;
			}
			break;
	}
	switch (state){ // State actions
		case light1:
			tmpC = 0x01;
			break;
		case wait1:
			tmpC = 0x01;
			break;
		case light2:
			tmpC = 0x02;
			break;
		case wait2:
			tmpC = 0x02;
			break;
		case light3:
			tmpC = 0x04;
			break;
		case wait3:
			tmpC = 0x04;
			break;

	}
  }
  

  int main()
  {
	  DDRB = 0xFF; PORTB = 0x00; // Initiate DDRC to outputs
	  DDRA = 0x00; PORTA = 0xFF; // Initiate DDRA to inputs
	  DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	  DDRD = 0xFF; PORTD = 0x00; // LCD control lines

	  TimerSet(300);
	  TimerOn();
	  state = light1;

	  // Initialize LCD display
	  LCD_init();
	  LCD_ClearScreen();
	  score = 0x05;

	  while(1) {
		LCD_Cursor(1);
		if(score == 9)
			LCD_DisplayString(1,"You Win!!");
		else
			LCD_WriteData(score + '0');
		tmpA = ~PINA & 0x01;
		// User code (i.e. synchSM calls)
		lightTick();
		while (!TimerFlag){}	// Wait 1 sec
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
		PORTB = tmpC;
		  
	  }
	  return 0;
  }
