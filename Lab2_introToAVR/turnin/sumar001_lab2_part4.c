/*	Author: Saad Umar
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #2  Exercise #4
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
	DDRB = 0x00; PORTB = 0x00; // Configure port B's 8 pins as inputs,
	DDRC = 0x00; PORTC = 0x00; // Configure port C's 8 pins as inputs,
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs,
	
        unsigned char weight_tot = 0x00;
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
	unsigned char tmpD = 0x00; // Temporary variable to hold the value of D
    
    /* Insert your solution below */
          while (1) {
	
		weight_tot = tmpA + tmpB + tmpC;
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;
		tmpD = 0x00;

             
		if(tmpA + tmpB + tmpC > 139)
		   {
			tmpD = tmpD | 0x01;
		   }
  
		if(abs(tmpA - tmpC) > 80)
                   {
			tmpD = tmpD | 0x02;
		   }  

		weight_tot = weight_tot & 0xFC;

		tmpD = weight_tot + tmpD;

		PORTD = tmpD;
	}
	return 0;
}

