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
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char weight = 0x00;
	unsigned char airbag = 0x00;



  /* Insert your solution below */
    while (1) {
	
	weight = PIND;
	
	if(weight >69)
	 {
	  airbag = 0x02;
	 }

	if((weight > 5) && (weight < 70))
	 {
	  airbag = 0x04;
	 }
	if(weight < 5)
	 {
	   airbag = 0x00;
	 }	

	 PORTB = airbag;
	 airbag = 0x00;
	 weight = 0x00;	
    }
}
