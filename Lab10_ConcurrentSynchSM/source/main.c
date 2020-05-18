/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #10  Exercise #1
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
 
unsigned char Blink = 0x00;
unsigned char Three = 0x00;
unsigned char temp = 0x00;
unsigned short count = 0x00;
unsigned short cnt = 0x00;


enum Three_States {Start, LED_1, LED_2, LED_3} Three_state;
void TickThree_LEDS()
{
	switch(Three_state) // Transitions
	{
		case Start:
		{
			Three_state = LED_1;
			break;
		}
		case LED_1:
		{
			if(cnt < 1000)
			{
				Three_state = LED_1;
				++cnt;
			}
			else
			{
				Three_state = LED_2;
				cnt = 0;
			}
			break;
		}
		case LED_2:
		{
			if(cnt < 1000)
			{
				Three_state = LED_2;
				++cnt;
			}
			else
			{
				Three_state = LED_3;
				cnt = 0;
			}
			break;
		}
		case LED_3:
		{
			if(cnt < 1000)
			{
				Three_state = LED_3;
				++cnt;
			}
			else
			{
				Three_state = LED_1;
				cnt = 0;
			}
			break;
		}
		default:
			break;	
	}
	
	switch(Three_state) // State Actions
	{
		case Start:
			break;
		case LED_1:
		{
			Three = 0x01;
			break;
		}
		case LED_2:
		{
			Three = 0x02;
			break;
		}
		case LED_3:
		{
			Three = 0x04;
			break;
		}
		default:
			break;
	}
}

enum Blinking_States{BL_Start, ON, OFF} BL_state;
void TickBL()
{
	switch(BL_state) // Transitions
	{
		case BL_Start:
		{
			BL_state = ON;
			break;
		}
		case ON:
		{
			if(count < 1000)
			{
				BL_state = ON;
				++count;
			}
			else
			{
				BL_state = OFF;
				count = 0;
			}
			break;
		}
		case OFF:
		{
			if(count < 1000)
			{
				BL_state = OFF;
				++count;
			}
			else
			{
				BL_state = ON;
				count = 0;
			}
			break;
		}
		default:
			break;
	}
	switch(BL_state) // State Actions
	{
		case BL_Start:
			break;
		case ON:
		{
			Blink = 0x08;
			break;
		}
		case OFF:
		{
			Blink = 0x00;
		}
		default:
			break;
	}
}

enum COMBINE_States{COM_Start, OUTPUT} Combine_State;
void TickCOM()
{
	switch(Combine_State) // Transitions
	{
		case COM_Start:
		{
			Combine_State = OUTPUT;
			break;
		}
		case OUTPUT:
			break;
		default:
			break;
	}
	switch(Combine_State) // State Actions
	{
		case COM_Start:
			break;
		case OUTPUT:
		{
			temp = Blink | Three;
			PORTB = temp;
			break;
		}
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	Three_state = Start;
	BL_state = BL_Start;
	Combine_State = COM_Start;
	cnt = 0;
	count = 0;
	
	TimerSet(1);
	TimerOn();
    while(1)
    {
		TickThree_LEDS();
		TickBL();
		TickCOM();
        while (!TimerFlag);
        TimerFlag = 0;
    }
}
