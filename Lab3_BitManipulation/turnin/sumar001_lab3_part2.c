/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #3  Exercise #2
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
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char level = 0x00;
	unsigned char light = 0x00;
    /* Insert your solution below */
    while (1) {
	
	 level = PINA ;

	 if((level & 0x00) == 0x00)
	   {
		light = 0x40;
	   }

	if((level & 0x01) == 0x01)
	   {
		light = 0x60;
	   }
	if((level & 0x02) == 0x02)
	   {
		light = 0x60;
	   }
	if((level & 0x03) == 0x03)
	   {
		light = 0x70;
	   }
	if((level & 0x04) == 0x04)
	   {
		light = 0x70;
	   }
	if((level & 0x05) == 0x05)
	   {
		light = 0x38;
	   }
	if((level & 0x06) == 0x06)
	   {
		light = 0x38;
	   }
	if((level & 0x07) == 0x07)
	   {
		light = 0x3C;
	   }
	if((level & 0x08) == 0x08)
	   {
		light = 0x3C;
	   }
	if((level & 0x09) == 0x09)
	   {
		light = 0x3C;
	   }
	if((level & 0x0A) == 0x0A)
	   {
		light = 0x3E;
	   }
	if((level & 0x0B) == 0x0B)
	   {
		light = 0x3E;
	   }
	if((level & 0x0C) == 0x0C)
	   {
		light = 0x3E;
	   }
	if((level & 0x0D) == 0x0D)
	   {
		light = 0x3F;
	   }
	if((level & 0x0E) == 0x0E)
	   {
		light = 0x3F;
	   }
	if((level & 0x0F) == 0x0F)
	   {
		light = 0x3F;
	   }


		PORTC = light;
		light = 0x00;
		level = 0x00;		

    }
    return 1;
}
