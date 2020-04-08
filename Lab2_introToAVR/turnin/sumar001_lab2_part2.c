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
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0XFF ;  //Configure PORT A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0X00 ; //Configure PORT B's 8 pins as outputs, initialized to 0

	unsigned char cntavail = 0x00;
	unsigned char park_1   = 0x00;
	unsigned char park_2   = 0x00;
	unsigned char park_3   = 0x00;
	unsigned char park_4   = 0x00;

    /* Insert your solution below */
    while (1) {
		//Read input
		park_1 = (PINA & 0x01) ? 1: 0;
		park_2 = (PINA & 0x02) ? 1: 0;
		park_3 = (PINA & 0x04) ? 1: 0;
		park_4 = (PINA & 0x08) ? 1: 0;		

		cntavail = 4 - (park_1 + park_2 + park_3 + park_4);
		PORTC = cntavail;
    }
    return 1;
}
