/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #2
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
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
				   //// Initialize output on PORTC to 0x00
     unsigned char cntavail = 0x00; 
     unsigned char park_zero = 0x00;
     unsigned char park_first = 0x00;
     unsigned char park_second= 0x00;
     unsigned char park_third = 0x00;

     while(1)
	    {
	      park_zero   = PINA & 0x01 ;
	      park_first  = PINA & 0x02 ;
	      park_second = PINA & 0x04 ;
	      park_third  = PINA & 0x08 ;

	     if(park_zero &  0x01) {
		cntavail = cntavail + 1 ;
	    }
	if(park_first & 0x02) {
		cntavail = cntavail + 1 ;
	    }
	if(park_second & 0x04) {
		cntavail = cntavail + 1 ;
	    }
	if(park_third & 0x08) {
		cntavail = cntavail + 1 ;
	   }
	
	cntavail = park_zero + park_first + park_second + park_third ;
	cntavail = 0x04 - cntavail ;
	PORTC = cntavail;
  }
}
