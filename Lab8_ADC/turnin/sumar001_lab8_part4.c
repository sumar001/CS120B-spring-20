/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #8  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo: https://drive.google.com/file/d/1h3aN4YAVzKQNXt-xZMFrjzkvG4iI1klf/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}


int main(void)
{
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	ADC_init();

// 	unsigned char min = 71;
	unsigned char max  = 223; //1+2+4+8+16+64+128
	unsigned short x    = (max/8) ;
	unsigned short y    = 0x00;
	unsigned char tmpB = 0x00;
//	Insert your solution below 
	while(1){
		y = ADC;

		if(y <= x) {
			tmpB = 0x01;
		  }

		else if(y <= (2*x)) {
			tmpB = 0x03;
		}

		else if(y <= (3*x)) {
			tmpB = 0x07;
		}

		else if(y <= (4*x)) {
			tmpB = 0x0F;
		}

		else if(y <= (5*x)) {
			tmpB = 0x1F;
		}

		else if(y <= (6*x)) {
			tmpB = 0x3F;
		}

		else if(y <= (7*x)) {
			tmpB = 0x7F;
		}

		else {
			tmpB = 0xFF;
		     }

		 PORTB = tmpB;	
	}
}
