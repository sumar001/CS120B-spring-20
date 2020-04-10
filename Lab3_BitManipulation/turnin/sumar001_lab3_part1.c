/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

unsigned char count_On_bits(unsigned char tmp_AB) {
	unsigned char number_of_ones = 0;
	unsigned char i;

	for(i = 0; i < 8; ++i) {
	 	number_of_ones = number_of_ones + GetBit(tmp_AB,i);
	   }
		return number_of_ones;
  }

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;

	DDRC = 0xFF; PORTC = 0x00;

     //Initialize the input
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char cnt = 0x00 ; //to compute the number of 1's
	
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	tmpB = PINB;

    //Call function
	cnt = count_On_bits(tmpA) + count_On_bits(tmpB);

    //Write to output
	PORTC = cnt;		
	
    }
    return 1;
}
