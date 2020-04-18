/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <stdio.h>
#include <stdlib.h>
#endif

enum States {Start, OFF, ON } state;
	unsigned char B = 0x01;
	unsigned char tmpA = 0x00;

void Tick() {

	switch(state) { // Transitions
		
		case Start:
			state = OFF;
			break;

		case OFF:
			if(tmpA != 0x01) {
				state = OFF;
			 }
			else {
				state = ON;
			}
			break;

		case ON:
			if(tmpA == 0x01)
			  {
				state = OFF;
			  }
			else {
				state = ON;
			     }
			break;


		   default:
			   state = OFF;
	} // Transitions

	switch(state) { // State actions
   		
		case Start:
			break;

		case OFF:
			B = 0x01;
		   break;

		case ON:
			if(tmpA == 0x00) {
				B = 0x02;
			 }
			 else{
				B = 0x01;
			     }
			  break;

		 default:
			break;
   } // State actions

  }
void main() {
	 DDRA = 0x00; PORTA = 0xFF;
	 DDRB = 0xFF; PORTB = 0x00;

  	B = 0x01; //initialize output 
	state = Start; // Indicates initial call
   	 while(1) { 
		Tick(); 
	}
}
