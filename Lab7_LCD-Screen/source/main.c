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

unsigned char i = 0x00;
unsigned char c = '0' ;
void Tick();
enum States {Start, INIT, INC, DEC, WAIT, RESET}state;


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; //LCD data lines
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines
	
	//Initializes the LCD display
	LCD_init();
	
	TimerSet(500);
	TimerOn();
	
    while(1)
    {
	    Tick();
        while (!TimerFlag);
        TimerFlag = 0;
    }    
}

void Tick()
{
	switch(state) // transitions
	{ 
		case Start:
		{
			LCD_Cursor(1);
			LCD_WriteData('0');
			state = INIT; 
			break;
		}
		
		case INIT:
		{
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
		}
		
		case INC:
		{
			state = WAIT; break;
		}
		
		case DEC:
		{
			state = WAIT; break;
		}
		
		case WAIT:
		{
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
		}
		
		case RESET:
		{
			if((~PINA & 0x03) == 0x00)
			{
				state = INIT; break;
			}
			else
			{
				state = RESET; break;
			}
		}
		
		default:
			break;
	}
	
	switch(state) //state actions
	{
		case Start:
			break;
			
		case INIT:
			break;
			
		case INC:
		{
			if(i >= 9)
			{
				i = 9;
			}
			else
			{
				++i;
			}
			LCD_Cursor(1);
			LCD_WriteData(i + '0');
			break;
		}
		
		case DEC:
		{
			if(i <= 0)
			{
				i = 0;
			}
			else
			{
				--i;
			}
			LCD_Cursor(1);
			LCD_WriteData(i + '0');
			break;
		}
		
		case WAIT:
			break;
			
		case RESET:
		{
			i = 0; 
			LCD_Cursor(1);
			LCD_WriteData(i + '0');
			break;
		}
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
