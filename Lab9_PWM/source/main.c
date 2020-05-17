/*	Author: sumar001
 *      Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #9  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>
//#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0) ;
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States {Start, WAIT, PLAY, DOWN, PAUSE, WAIT_2}state;
double notes[18] = {220.00, 220.00, 220.00, 174.61, 261.63, 220.00, 174.61, 261.63, 220.00, 329.63, 329.63, 329.63, 349.23, 207.65, 174.61, 261.63, 220.00};
char time[18] = {50, 50, 50, 37, 13, 50, 37, 13, 50, 50, 50, 50, 37, 13, 50, 37, 13, 50};
unsigned char i = 0x00;
unsigned char k = 0x00;
unsigned char r = 0x00;

void Tick()
{
	switch(state) //transitions
	{
		case Start:
		{
			state = WAIT;
			break;
		}
		case WAIT:
		{
			if((~PINA & 0x01) == 0x01)
			{
				state = PLAY; break;
			}
			else
			{
				state = WAIT; break;
			}
		}
		
		case PLAY:
		{
			if(i <= time[k])
			{
				state = PLAY; break;
			}
			else if(i > time[k])
			{
				++r;
				state = DOWN;
				break;
			}
		}
		case DOWN:
		{
			if(r < 20)
			{
				++k;
				state = PLAY;
				break;
			}
			else if(r >= 20)
			{
				state = PAUSE; break;
			}
		}
		
		case PAUSE:
		{
			if((~PINA & 0x01) == 0x01)
			{
				state = WAIT_2; break;
			}
			else
			{
				state = PAUSE; break;
			}
		}
		case WAIT_2:
		{
			if((~PINA & 0x01) == 0x01)
			{
				state = WAIT_2;
				break;
			}
			else
			{
				state = WAIT;
				break;
			}
		}
		default:
			break;
	}
	switch(state) //state actions
	{
		case Start:
			break;
			
		case WAIT:
		{
			i = 0;
			k = 0;
			r = 0;
			break;
		}
		
		case PLAY:
		{
			set_PWM(notes[k]);
			++i;
			break;
		}
		
		case DOWN:
		{
			set_PWM(0); break;
		}
		
		case PAUSE:
			break;
		default:
			break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PWM_on();
	
	TimerSet(50);
	TimerOn();
	state = Start;
    while(1)
    {
		Tick();
        while (!TimerFlag);
        TimerFlag = 0;
    }
}

