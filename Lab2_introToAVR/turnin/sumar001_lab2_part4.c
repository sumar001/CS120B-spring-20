/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <stdlib.h>
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;

        unsigned char seatA = 0x00;
	unsigned char seatB = 0x00;
	unsigned char seatC = 0x00;
	unsigned short totalWeight = 0x0000;
	unsigned char differenceWeight = 0x00;
	unsigned char tempWeight = 0x00;
	
    while(1)
    {
                seatA = PINA;
		seatB = PINB;
		seatC = PINC;
		
		totalWeight = seatA + seatB + seatC;
		
		if(abs((seatA - seatC)) >= 0x50)
		{
			differenceWeight = 0x02;
		}
		if(totalWeight >= 0x8C)
		{
			tempWeight = 0x01;
		}		
		PORTD = tempWeight | differenceWeight;
		tempWeight = 0x00;
		differenceWeight = 0x00;
		totalWeight = 0x0000;
    }
}	
