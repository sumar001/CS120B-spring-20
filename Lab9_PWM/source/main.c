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


enum STATES { start, init, press, release, wait, play } state;

unsigned char button_on=0;
double sound_arr[5]={ 261.63, 329.63, 392.00, 493.88, 523.25 };
unsigned char sound_lasting[5]={3, 1, 2, 1, 6 };
unsigned char sound_waiting[5]={1, 2, 1, 2, 0 };
unsigned char i=0;
unsigned char cnt=0;

void Tick(){
	
	unsigned char button1=~PINA & 0x01;
	
	
	
	switch (state){
		
		case start:	
							state = init;
							break;
					
							
		case init:			
			if(B0)
				state = press;
			else
				state = init;
			break;
					
		case press:
			if(B0)
				state = press;
			else 
				state = release;
			break;
		
			
		case release:				state=wait;
							break;

		case wait:				if( cnt < sound_waiting[i] ){
								cnt=cnt+1;
							}else{
							state=play;
							cnt=0;
							}

							break;

		case play:				set_PWM( sound_arr[i] );

							if( cnt < sound_lasting[i] ){
								cnt=cnt+1;
							}else{
							state=release;
							cnt=0;
							++i;
							}

							if( i==5 ){
							state=start;
							i=0;
							set_PWM( 0 );
							}

							break;
					
		default: 
							state=start;
							break;
		}

}

int main(void)
{
    /* Replace with your application code */
	DDRA=0x00; PORTA=0xFF;
	DDRB=0XFF; PORTB=0x00;

	PWM_on();
	TimerSet(100);   
	TimerOn(); 
	
    while (1) 
    {
		Tick();

		while(!TimerFlag);
		TimerFlag=0;
    }
}
