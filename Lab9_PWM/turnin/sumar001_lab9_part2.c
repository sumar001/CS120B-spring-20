/*	Author: sumar001
 *      Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #9  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo: https://drive.google.com/file/d/1Z4RJHjE-EbadF3sRqY4J_eQeJzJ-Rzf7/view?usp=sharing 
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

enum States{ off, Off2, on, On2, inc, dec, hold1, hold2}state;


 unsigned char cnt = 0x00;
 const double freq[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

void Tick(){

	unsigned char B0 = (~PINA & 0x01); //button1
	unsigned char B1 = (~PINA & 0x02); //button2
	unsigned char B2 = (~PINA & 0x04); //button3

	switch(state){ // Transitions
		case off:
			if(B0 && !B1 && !B2)
				state = on;
			else
				state = off;
			break;

		case Off2:
			if(!B0 && !B1 && !B2)        
				state = off;
			else
				state = Off2;
			break;

		case on:
			if(B0 && !B1 && !B2)
				state = on;
			else
				state = On2;
			break;

		case On2:

			if(!B0 && B1 && !B2){
				if(cnt < 8)
					cnt++;
				state = inc;
			}
			else if(!B0 && !B1 && B2){
				if(cnt > 0)
					cnt--;
				state = dec;
			}
			else if(B0 && !B1 && !B2)
				state = Off2;
			else
				state = On2;
			break;

		case inc:
			state = hold1;
			break;

		case hold1:
			if(!B0 && B1 && !B2)
				state = hold1;
			else
				state = On2;
			break;

		case dec:
			state = hold2;
			break;

		case hold2:
			if(!B0 && !B1 && B2)
				state = hold2;
			else
				state = On2;
			break;
	}

	switch(state){ // State actions
		case off:
			PWM_off();
			break;

		case Off2:
			break;

		case on:
			PWM_on();
			set_PWM(261.63);
			break;

		case On2:
			break;

		case inc:
			set_PWM(freq[cnt]);
			break;

		case hold1:
			break;

		case dec:
			set_PWM(freq[cnt]);
			break;

		case hold2:
			break;

	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A input initialized to 0xFF
	DDRB = 0xFF; PORTB = 0x00; // B output initialized to 0x00

	PWM_on();
	state = off;

	while(1){

		Tick();
	}
}

