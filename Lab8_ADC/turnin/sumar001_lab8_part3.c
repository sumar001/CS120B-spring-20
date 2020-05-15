/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo: https://drive.google.com/file/d/1ruWLrrWdbhP3ZE4y6g6xBRj4uLF3l5ke/view?usp=sharing 
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

	unsigned char max = 223; //1+2+4+8+16+64+128
// 	unsigned char min = 71;
	unsigned char tmpB = 0x00;

	/*Insert your solution below */
	while(1){
	
	unsigned short my_short = ADC; //Storing value of ADC
		
	 if(my_short >= max/2) {
	 	tmpB = 0x01;
	 }
	 else {
	tmpB = 0x00;
	 }
	  PORTB = tmpB;
	}
}
