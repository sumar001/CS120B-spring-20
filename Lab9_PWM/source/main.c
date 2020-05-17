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

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25

double TETRIS[] = {E4, B4, C4, D4, C4, B4, A4, 
					  A4, C4, E4, D4, C4, B4, C4,
					  D4, E4, C4, A4, A4, D4, F4,
					  A4, G4, F4, E4, C4, E4, D4,
					  C4, B4, B4, C4, D4, E4, C4, A4, A4};

unsigned char tempA, tempB;
unsigned int noteCount;

enum States {init, play_song, pause, wait} state;

void noteTick(){
	//transitions
	switch(state){
		case init:
		tempB = 0x01;
		state = wait;
		break;
		
		case wait:
		tempB = 0x02;
		if(tempA == 0x01)
		{
			noteCount = 1;
			state = play_song;
		}
		else
		{
			set_PWM(0);
			state = wait;
		}
		break;
		
		case play_song:
		tempB = 0x04;
		if(noteCount < 37)
		{
			set_PWM(TETRIS[noteCount]);
			noteCount++;
			state = play_song;
		}
		else
		{
			noteCount = 0;
			set_PWM(0);
			state = wait;
		}
		break;
		
		case pause:
		tempB = 0x08;
		set_PWM(0);
		state = play_song;
		break;
		
		default:
		state = wait;
		break;
	}
	PORTB = tempB;
}

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = init;
	noteCount = 0;
	TimerOn();
	TimerSet(100);
	PWM_on();
	while(1)
	{
		tempA = ~PINA;
		noteTick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
