/*	Author: sumar001
 *  Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

//==================================================================
//starting PART !
//=================================================================
enum States {Init, Led1, Led2, Led3} state;

	unsigned char tmpB = 0x00;

void Tick() {
	switch(state)
	{
		case Init:
			state = Led1;
			break;

		case Led1:
			state = Led2;
			break;

		case Led2:
			state = Led3;
			break;
			
		case Led3:
			state = Led1;
			break;
	}

	switch(state) {
		case Led1:
			tmpB = 0x01;
			break;

		case Led2:
			tmpB = 0x02;
			break;

		case Led3:
			tmpB = 0x04;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0XFF;   //Set PortB to output
	PORTB = 0x00;  //Init portB to 0s

	TimerSet(1000);
	TimerOn();
	
	state = Init;

    /* Insert your solution below */
    while (1) {
	
	  Tick();
	while (!TimerFlag); //Wait 1 sec
	TimerFlag = 0;
	PORTB = tmpB;

    }
    return 1;
}
