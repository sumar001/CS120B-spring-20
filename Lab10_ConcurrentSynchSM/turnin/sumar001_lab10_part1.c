/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #10  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo: https://drive.google.com/file/d/11WJhHchyt2oOyKVB9lXqjhdJjDJ4PJcs/view?usp=sharing
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
			if(i < 1000)
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
			if(i < 1000)
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
			if(i < 1000)
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
