/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #1
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
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
				// Initialize output on PORTB to 0x00
	unsigned char inp_A = 0x00; // Temporary variable to hold the value of A input
	unsigned char inp_B = 0x00; // Temporary variable to hold the value of B input

    while (1) {
    		inp_A = PINA & 0x01 ;
    	        inp_B = PINA & 0x02;
		
          if ((inp_A == 0x01) && (inp_B == 0x00)) {
		PORTB = 0X01 ; 
		 }
		  else {
			PORTB = 0X00 ;

		      }
         
	}


    return 0;
}
