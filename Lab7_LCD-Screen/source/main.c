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

enum States {Start, INIT, INC, DEC, WAIT, RESET}state;
unsigned char counter = 0;
void Tick(){
	switch(state){ 
		case Start:
		{
			LCD_Cursor(1);
			LCD_WriteData('0');
			state = INIT;
			break;
		}
		
		case INIT:
		if((~PINA & 0x03) == 0x01)
		{
			state = INC; break;
		}
		else if((~PINA & 0x03) == 0x02)
		{
			state = DEC; break;
		}
		else if((~PINA & 0x03) == 0x03)
		{
			state = RESET; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case INC:
		state = WAIT;
		break;
		
		case DEC:
		state = WAIT;
		break;
		
		case WAIT:
		if((~PINA & 0x03) == 0x01)
			{
				state = INC; break;
			}
			else if((~PINA & 0x03) == 0x02)
			{
				state = DEC; break;
			}
			else if((~PINA & 0x03) == 0x03)
			{
				state = RESET; break;
			}
			else if((~PINA & 0x03) == 0x00)
			{
				state = INIT; break;
			}
			else 
			{
				state = WAIT; break;
			}
		
		case RESET:
		if((~PINA & 0x03) == 0x00)
		{
			state = INIT; break;
		}
			else
		{
			state = RESET; break;
		}
		
		default:
		break;
	}
	
	
	
	switch(state){
		case Start:
		{
		}
		break;
		
		case INIT:
		break;
		
		case INC:
		{
			if(counter >= 0x09)
			{
				counter = 0x09;
			}
			else
			{
				counter = counter + 0x01;
			}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
			
		}
		
		case DEC:
		{
			if(counter <= 0x00)
			{
				counter = 0x00; 
			}
			else
			{
				counter = counter - 0x01;
			
			}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
		}
		
		case WAIT:
		break;
		
		case RESET:
		{
			counter = 0; 
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
		}
		default: 
		break;
	}
}

int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	//DDRB = 0xFF;PORTB = 0x07;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	LCD_init();
	TimerSet(12);
	TimerOn();
	state = Start;
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
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
