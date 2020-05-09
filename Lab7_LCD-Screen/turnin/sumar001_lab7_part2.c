/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 // Demo: https://drive.google.com/file/d/1vg8IX8kjVvhKuyFrT6UqLQrMyoUQ8as1/view?usp=sharing
 
#include <avr/io.h>
#include "io.h"
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
				if(result > 0)
					result--;
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
				if(result < 9)
					result++;
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
				if(result > 0)
					result--;
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
	  DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	  DDRD = 0xFF; PORTD = 0x00; // LCD control lines

	  TimerSet(300);
	  TimerOn();

	  state = start;

	  // Initialize LCD display
	  LCD_init();
	  LCD_ClearScreen();
	  result = 0x05;

	  while(1) {
		LCD_Cursor(1);

		if(result == 9) {
			LCD_DisplayString(1,"Winner!!");
		}
		else {
			LCD_WriteData(result + '0');
		}

		 A = ~PINA & 0x01;
		
		Tick();
		while (!TimerFlag){}
		TimerFlag = 0;
		PORTB = tmpB;
		  
	  }
	  return 0;
  }
