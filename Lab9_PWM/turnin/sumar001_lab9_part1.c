/*	Author: sumar001
 *      Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
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

enum States{start, init, c4, d4, e4}state;


void Tick(){
	 unsigned char B0 = (~PINA & 0x01); //button
	 unsigned char B1 = (~PINA & 0x02);
	 unsigned char B2 = (~PINA & 0x04);

	switch(state){ // Transitions
		case start:
			state = init;
			break;

		case init:
			if(B0 && !B1 && !B2){
				state = c4;
			}
			else if(!B0 && B1 && !B2){
				state = d4;			
			}
			else if(!B0 && !B1 && B2){
				state = e4;
			}
			else{
				state = init;
			}
			break;

		case c4:
			if(B0 && !B1 && !B2){
				state = c4;
			}
			else{
				state = init;
			}
			break;

		case d4:
			if(!B0 && B1 && !B2){
				state = d4;
			}
			else{
				state = init;
			}
			break;

		case e4:
			if(!B0 && !B1 && B2){
				state = e4;
			}
			else{
				state = init;
			}
			break;
	}

	switch(state){ // State actions
		case init:
			set_PWM(0);
			break;

		case c4:
			set_PWM(261.63);
			break;

		case d4:
			set_PWM(293.66);
			break;

		case e4:
			set_PWM(329.63);
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
      DDRA = 0x00; PORTA = 0xFF; // A input initialized to 0xFF
      DDRB = 0xFF; PORTB = 0x00; // B output initialized to 0x00

	PWM_on();
	state = start;

    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
