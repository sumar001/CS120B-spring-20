/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section:
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
DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0XFF;
        DDRC = 0xFF; PORTC = 0x00;
 
     unsigned char s_1;
     unsigned char s_2;
     unsigned char tmp_1;
     unsigned char tmp_2;
     unsigned char  i;

	 while(1)
	    {
		tmp_1 = PINA ;
		  s_1 = 0x00 ;
		  s_2 = 0x00 ;

		for(i = 0x00 ; i < 8 ; ++i)
		  {
		    if(tmp_1 & 0x80) {
			s_1 = s_1 + 1 ;
		     }
		   tmp_1 = tmp_1 << 1 ;
		  }

		tmp_2 = PINB ;
		 for(i = 0x00 ; i < 8 ; ++i) {
			if(tmp_2 & 0x80) {
				s_2 = s_2 + 1 ;
			   }
			tmp_2 = tmp_2 << 1 ;
		    }
		PORTC = s_1 + s_2 ;
	
      	    }
}
