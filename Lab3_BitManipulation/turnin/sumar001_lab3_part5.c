/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #3  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;

	unsigned short weight = 0;
	unsigned char airbag = 0x00;
	unsigned char tmpB = 0x00;	


  /* Insert your solution below */
    while (1) {
	
    //calculate the weight
		tmpB = PINB & 0x01;
		weight = PIND << 1;
		weight +=  tmpB;

		//determine the output
		if(weight >= 70){
			airbag = 0x02;
		}
		else if (weight > 5){
			airbag = 0x04;
		}
		else{
			airbag = 0x00;
		}
		
		//output
		PORTB = airbag;
