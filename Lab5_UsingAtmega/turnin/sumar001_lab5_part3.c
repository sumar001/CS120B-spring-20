/*	Author: sumar001
 *      Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, init, press} state;

unsigned char tmpA = 0;
unsigned char tmpC = 0;

void Tick(){
	
	tmpA = ~PINA;

	switch(state){
		case start: 
			state = init;
			break;
					
		case init: 
			switch(tmpC){
				case 0: 
					PORTC  = 0x00; 
					break;

				case 1: 
					PORTC = 0x2A; 
					break;
  
				case 2: 
					PORTC = 0x15;
					 break;
  
				case 3: 
					PORTC = 0x33; 
					break;
  
				default:
					 PORTC = 0x00; 
					break;
				}
						
				if( tmpA == 1 ) {
					state = press;
					tmpC = (tmpC < 3) ? ++tmpC : 0;
					}
				else{
					state = init;
					}
					break;
						
		case press:	
			state = tmpA  ?  press: init; 
				break;
			default: 
				break;				
	      }
	
	};

int main(void)
{
    /* Replace with your application code */
	DDRA=0x00; PORTA=0xFF;
	DDRC=0xFF; PORTC=0x00;
	
	state=start;
	
    while (1) 
    {
		Tick();
    }
}
