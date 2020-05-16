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

enum States{waitOff, cFour, dFour, eFour}state;

unsigned char buttonPress = 0x00;

void button_Tick(){
	buttonPress = ~PINA & 0x07;
	switch(state){ // Transitions
		case waitOff:
			if(buttonPress == 1){
				state = cFour;
			}
			else if(buttonPress == 2){
				state = dFour;			
			}
			else if(buttonPress == 4){
				state = eFour;
			}
			else{
				state = waitOff;
			}
			break;
		case cFour:
			if(buttonPress == 1){
				state = cFour;
			}
			else{
				state = waitOff;
			}
			break;
		case dFour:
			if(buttonPress == 2){
				state = dFour;
			}
			else{
				state = waitOff;
			}
			break;
		case eFour:
			if(buttonPress == 4){
				state = eFour;
			}
			else{
				state = waitOff;
			}
			break;
	}
	switch(state){ // State actions
		case waitOff:
			set_PWM(0);
			break;
		case cFour:
			set_PWM(261.63);
			break;
		case dFour:
			set_PWM(293.66);
			break;
		case eFour:
			set_PWM(329.63);
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
      DDRA = 0x00; PORTA = 0xFF; // A input initialized to 0xFF
      DDRB = 0xFF; PORTB = 0x00; // B output initialized to 0x00

	PWM_on();
	state = waitOFF;

    /* Insert your solution below */
    while (1) {
	button_Tick();
    }
    return 1;
}
