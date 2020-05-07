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

unsigned char tempB = 0x00;
unsigned char tempA = 0x00;
unsigned char count = 0x00;
unsigned char buttonHeld = 0x00;

unsigned char A0 = 0x00; //button 1
unsigned char A1 = 0x00; //button 2

enum SM_States { SMStart, SM_Init, PRESS_INCR, INCR, PRESS_DECR, DECR, WAIT, RESET } SM_State;

void Tick()
{
		A0 = ~PINA & 0x01;
	 	A1 = ~PINA & 0x02;
	switch(SM_State) {   // Transitions
		case SMStart:  // Initial transition
		SM_State = SM_Init;
		break;

		case SM_Init:
		if (A0 && !A1) {
			if (PORTB < 9) {
				PORTB = PORTB + 1;
				count++;
			}
			SM_State = INCR;
		}
		else if (A0 && A1) {
			SM_State = RESET;
		}
		else if (A1 && !A0) {
			if (PORTB > 0) {
					PORTB = PORTB - 1;
					count--;
			}
			SM_State = DECR;
		}
		break;

		case INCR:
		if ((A0 && !A1) && (buttonHeld <= 10)) { 
			SM_State = INCR;
		}
		else if (!A0) { 
			SM_State = WAIT;
		}
		else if (A0 && A1) {
			SM_State = RESET;
		}
		else if ((A0 && !A1) && (buttonHeld > 10)) { 
			SM_State = WAIT;
		}
		break;
		
		case DECR:
		if ((A1 && !A0) && (buttonHeld <= 10)) {
			SM_State = DECR;
		}
		else if (!A1) {
			SM_State = WAIT;
		}
		else if (A1 && A0) {
			SM_State = RESET;
		}
		else if ((!A0 && A1) && (buttonHeld > 10)) { 
			SM_State = WAIT;
		}
		break;
		
		case WAIT:
		if (!A0 && !A1) {
			SM_State = WAIT;
		}
		else if (A0 && A1) {
			SM_State = RESET;
		}
		else if (A0 && !A1 )  {
			if (PORTB < 9) {
				PORTB = PORTB + 1;
				count++;
			}
			SM_State = INCR;
		}
		else if (A1 && !A0) {
			if (PORTB > 0) {
				PORTB = PORTB - 1;
				count--;
			}
			SM_State = DECR;
		}
		break;
		
		case RESET:
		if (A0 && !A1) {
			if (PORTB < 9) {
				PORTB = PORTB + 1;
				count++;
			}
			SM_State = INCR;
		}
		else if (A1 && !A0) {
			if (PORTB > 0) {
				PORTB = PORTB - 1;
				count--;
			}
			SM_State = DECR;
		}
		else {
			SM_State = RESET;
		}
		break;

		default:
		SM_State = SMStart;
		break;
	} // Transitions

	switch(SM_State) {   // State actions
		case SM_Init:
		PORTB = 7;
		count = 7;
		LCD_Cursor(1);
		LCD_WriteData(count + '0');
		buttonHeld =0;
		break;
		
		case INCR:

		LCD_Cursor(1);
		LCD_WriteData(count + '0');
		buttonHeld++; 
		break;
		
		case DECR:
	
		LCD_Cursor(1);
		LCD_WriteData(count + '0');
		buttonHeld++;
		break;
		
		case WAIT:
		buttonHeld =0;
		break;
		
		case RESET:
		PORTB = 0;
		count = 0;
		LCD_Cursor(1);
		LCD_WriteData(count + '0');
		buttonHeld =0;
		break;
		
		default:
		break;
	} // State actions
			A0 = 0x00; //reset for next round
			A1 = 0x00; //reset for next round
}

int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs,
	
	SM_State = SMStart; // Indicates initial call
	LCD_init();
	TimerSet(100);
	TimerOn();

	unsigned char tempA0 = 0x00; 
	unsigned char tempA1 = 0x00;
	
	while(1)
	{

		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
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
