/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #10  Exercise #1
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

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char tmpB = 0x00;

enum threeStates{threeInit,first, second, third}threeState;
void SM_Three_Tick(){
	switch(threeState){ // Transitions
		case threeInit:
			threeState = first;
			break;
		case first:
			threeState = second;
			break;
		case second:
			threeState = third;
			break;
		case third:
			threeState = first;
			break;
	}
	switch(threeState){ // State actions
		case threeInit:
			break;
		case first:
			threeLEDs = 0x01;
			break;
		case second:
			threeLEDs = 0x02;
			break;
		case third:
			threeLEDs = 0x04;
			break;
	}
}

enum singleStates{on, off}singleState;
void SM_Single_Tick(){
	switch(singleState){ // Transitions
		case on:
			singleState = off;
			break;
		case off:
			singleState = on;
			break;
	}
	switch(singleState){ // State Actions
		case on:
			blinkingLED = 0x08;
			break;
		case off:
			blinkingLED = 0x00;
			break;

	}
}
enum opStates{output} opState;
void SM_output(){
	switch(opState){ // Transitions
		case output:
			break;
	}
	switch(opState){ // State actions
		case output:
			tmpB = threeLEDs | blinkingLED;
			break;
	}

}
int main(void) {
    /* Insert DDR and PORT initializations */
      DDRB = 0xFF; PORTB = 0x00;

	opState = output;
	threeState = threeInit;
	singleState = on;

    /* Insert your solution below */
    while (1) {
	SM_Single_Tick();
		SM_Three_Tick();
		SM_output();
		PORTB = tmpB;
		while(!TimerFlag){}
		TimerFlag = 0;
    }
    return 1;
}
