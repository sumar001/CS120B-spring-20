/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #10  Exercise #2
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
 
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char tmpB = 0x00; //combined value will be stored here which will be displayed on PORTB
unsigned short i = 0x00 ;  //counter for ThreeLEDsDM
unsigned short j = 0x00;  //counter for BlinkingLEDSM
unsigned char Speaker = 0x00;

enum ThreeLED_States {Start, Led1, Led2, Led3} ThreeLEDsSM;
void Three_Tick()
{
	switch(ThreeLEDsSM) // Transitions
	{
		case Start:
		{
			ThreeLEDsSM = Led1;
			break;
		}
		case Led1:
		{
			if(i < 300)
			{
				ThreeLEDsSM = Led1;
				++i;
			}
			else
			{
				ThreeLEDsSM = Led2;
				i = 0;
			}
			break;
		}
		case Led2:
		{
			if(i < 300)
			{
				ThreeLEDsSM = Led2;
				++i;
			}
			else
			{
				ThreeLEDsSM = Led3;
				i = 0;
			}
			break;
		}
		case Led3:
		{
			if(i < 300)
			{
				ThreeLEDsSM = Led3;
				++i;
			}
			else
			{
				ThreeLEDsSM = Led1;
				i = 0;
			}
			break;
		}
	}
	
	switch(ThreeLEDsSM) // State Actions
	{
		case Start:
			break;
		case Led1:
		{
			threeLEDs = 0x01;
			break;
		}
		case Led2:
		{
			threeLEDs = 0x02;
			break;
		}
		case Led3:
		{
			threeLEDs = 0x04;
			break;
		}
	}
}

enum BlinkingLEDSM_States{BL_Start, off, on} BL_state;
void Blink_Tick()
{
	switch(BL_state) // Transitions
	{
		case BL_Start:
		{
			BL_state = on;
			break;
		}
		case on:
		{
			if(j < 1000)
			{
				BL_state = on;
				++j;
			}
			else
			{
				BL_state = off;
				j = 0;
			}
			break;
		}
		case off:
		{
			if(j < 1000)
			{
				BL_state = off;
				++j;
			}
			else
			{
				BL_state = on;
				j = 0;
			}
			break;
		}
	}
	
	switch(BL_state) // State Actions
	{
		case BL_Start:
			break;
		case on:
		{
			blinkingLED = 0x08;
			break;
		}
		case off:
		{
			blinkingLED = 0x00;
		}
	}
}

enum CombineLEDsSM_States{display} CombineLED_state;
void Combine_Tick()
{
	switch(CombineLED_state) // Transitions
	{
		case display:
			break;
	}
	switch(CombineLED_state) // State Actions
	{
		case display:
		{
			tmpB = threeLEDs | blinkingLED;
			PORTB = tmpB;
			break;
		}
	}
}

enum Speaker_States{SPEAK_Start, ON_SWITCH, OFF_SWITCH, WAIT} Speaker_state;
void TickSpeaker()
{
	switch(Speaker_state) // Transitions
	{
		case SPEAK_Start:
		{
			Speaker_state = WAIT;
			count = 0;
			break;
		}
		case ON_SWITCH:
		{
			if((count < 2) && ((~PINA & 0x04) == 0x04))
			{
				Speaker_state = ON_SWITCH;
				++count;
				break;
			}
			else if((~PINA & 0x04) == 0x04)
			{
				Speaker_state = OFF_SWITCH;
				count = 0;
				break;
			}
			else
			{
				Speaker_state = WAIT;
				break;
			}
		}
		case OFF_SWITCH:
		{
			if((count < 2) && ((~PINA & 0x04) == 0x04))
			{
				Speaker_state = OFF_SWITCH;
				++count;
				break;
			}
			else if((~PINA & 0x04) == 0x04)
			{
				Speaker_state = ON_SWITCH;
				count = 0;
				break;
			}
			else
			{
				Speaker_state = WAIT;
				break;
			}
		}
		case WAIT:
		{
			if((~PINA & 0x04) == 0x04)
			{
				Speaker_state = ON_SWITCH;
				break;
			}
			else
			{
				Speaker_state = WAIT;
				break;
			}
		}
		default:
			break;
	}
	switch(Speaker_state) // State Actions
	{
		case SPEAK_Start:
			break;
		case ON_SWITCH:
		{
			Speaker = 0x08;
			break;
		}
		case OFF_SWITCH:
		{
			Speaker = 0x00;
			break;
		}
		case WAIT:
		{
			Speaker = 0x00;
			count = 0x00;
			break;
		}
		default:
			break;
	}
}
int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;

	ThreeLEDsSM = Start;
	BL_state = BL_Start;
	CombineLED_state = display;  
	
	TimerSet(1);
	TimerOn();

    while(1)
    {
		Three_Tick();
		Blink_Tick();
		Combine_Tick();

        while (!TimerFlag);
        TimerFlag = 0;
    }
}
