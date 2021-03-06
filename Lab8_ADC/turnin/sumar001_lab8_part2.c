/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #8  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo: https://drive.google.com/file/d/1BpNDpewbxlZ_q6js8I2Oq6D5IgRszx5-/view?usp=sharing 
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

	/*Insert your solution below */
	while(1){
	
	unsigned short my_short = ADC; //Storing value of ADC
	PORTB = (char)my_short;
	PORTD = (char)(my_short >> 8);
	
	}
}
