/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #10  Exercise #3
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
unsigned char B = 0x00; //button
unsigned char audio = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char tmpB = 0x00; //combined value will be stored here which will be displayed on PORTB
unsigned short i = 0x00 ;  //counter for ThreeLEDsDM
unsigned short j = 0x00;  //counter for BlinkingLEDSM
unsigned short cnt = 0x00;  //counter for Audio
unsigned short button = 0x01;

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


enum Audio_State {a_Start, a_hold, a_off, a_on} a_state;
void Audio_Tick() {

		B = (~PINA & 0x04);
	switch(a_state) { //transitions

		case a_Start:
			a_state = a_hold;
			cnt = 0;
			break;


		case a_on:
			if((cnt < 2) && B) {
				a_state = a_on;
				++cnt ;
				break;
			}
			else if(B) {
				a_state = a_off;
				cnt = 0;
				break;
			}
			else {
				a_state = a_hold;
				break;
			}

		case a_off:
			if((cnt < 2) && (B)) {
				a_state = a_off;
				++cnt ;
				break;
			}
			else if(B) {
				a_state = a_on;
				cnt = 0;
				break;
			}
			else {
				a_state = a_hold;
				break;
			}

		case a_hold:
			if(B) {
				a_state = a_on;
				break;
			}
			else {
				a_state = a_hold;
				break;
			}
	}

	switch(a_state) { //state actions

		case a_on:
			audio = 0x10;
			break;

		case a_off:
			audio = 0x00;
			break;

		case a_hold:
			audio = 0x00;
			cnt = 0x00;
			break;
		}
}

enum Button_States{BUT_Start, WAIT_2, UP, DOWN} state;
void TickButton()
{
	switch(state)
	{	// Transitions
		case BUT_Start:
		{
			state = WAIT_2;
			break;
		}
		case WAIT_2:
		{
			if((~PINA & 0x01) == 0x01)
			{
				state = UP;
				++button;
				break;
			}
			else if((~PINA & 0x02) == 0x02)
			{
				state = DOWN;
				if((button - 1) < 1)
				{
					button = 1;
				}
				else
				{
					--button;
				}
				break;
			}
			else
			{
				state = WAIT_2;
				break;
			}
		}
		case UP:
		{
			if((~PINA & 0x01) == 0x01)
			{
				state = UP;
				break;
			}
			else
			{
				state = WAIT_2;
				break;
			}
		}
		case DOWN:
		{
			if((~PINA & 0x02) == 0x02)
			{
				state = DOWN;
				break;
			}
			else
			{
				state = WAIT_2;
				break;
			}
		}
		default:
			break;
	}
	switch(state)
	{	// state actions
		case BUT_Start:
			break;
		case WAIT_2:
			break;
		case UP:
			break;
		case DOWN:
			break;
		default:
			break;
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
			tmpB = threeLEDs | blinkingLED | audio;
			PORTB = tmpB;
			break;
		}
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	ThreeLEDsSM = Start;
	BL_state = BL_Start;
	a_state = a_Start;
	CombineLED_state = display;  
	state = BUT_Start;
	
	TimerSet(1);
	TimerOn();

    while(1)
    {
		TickButton();

		Three_Tick();
		Audio_Tick();
		Blink_Tick();
		Combine_Tick();

        while (!TimerFlag);
        TimerFlag = 0;
    }
}
