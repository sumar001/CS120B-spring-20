/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #10  Exercise #2
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
			tmpB = threeLEDs | blinkingLED | soundOutput;
			break;
	}

}
enum bStates{wait, soundOn, soundOff} bState;
void SM_sound(){
	tmpA = ~PINA & 0x04;
	switch(bState){ // Transitions
		case wait:
			if(tmpA){
				bState = soundOn;
			}
			else{
				bState = wait;
			}
			break;
		case soundOn:
			if(tmpA){
				bState = soundOff;
			}
			else{
				bState = wait;
			}
			break;
		case soundOff:
			if(tmpA){
				bState = soundOn;
			}
			else{
				bState = wait;
			}
	}
	switch(bState){ // State actions
		case wait:
			soundOutput = 0x00;
			break;
		case soundOn:
			soundOutput = 0x10;
			break;
		case soundOff:
			soundOutput = 0x00;
			break;
	}
}

enum freqStates{bwait, up, upWait, down, downWait} fstate;
unsigned long freqTime = 2;
void SM_Freq_Tick(){
	unsigned char button0 = ~PINA & 0x01;
	unsigned char button1 = ~PINA & 0x02;
	
	switch(fstate){
		case bwait:
			if(button0 && !button1){
				fstate = up;
			}
			else if(!button0 && button1){
				fstate = down;
			}
			else{
				fstate = bwait;
			}
			break;
		case up:
			fstate = upWait;
			break;
		case upWait:
			if(button0){
				fstate = upWait;
			}
			else
				fstate = bwait;
			break;

		case down:
			fstate = downWait;
			break;
		case downWait:
			if(button1){
				fstate = downWait;
			}
			else
				fstate = bwait;
			break;			
		
	}
	switch(fstate){
		case bwait:
			break;
		case up:
			freqTime += 1;
			break;
		case upWait:
			break;
		case down:
			freqTime -= 1;
			break;
		case downWait:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Set A to input and initialize to 0xFF
	DDRB = 0xFF; PORTB = 0x00; // Set B to output and initialize to 0x00
	//DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	//DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	unsigned long lelapsedTime = 0;
	unsigned long selapsedTime = 0;
	unsigned long soundTime = 0;
	unsigned long largePeriod = 1000;
	unsigned long smallPeriod = 300;
	const unsigned long TimerPeriod = 1;

	TimerSet(TimerPeriod);
	TimerOn();
	
	opState = output;
	threeState = threeInit;
	singleState = on;
	while(1){
		if(lelapsedTime >= largePeriod){
			SM_Single_Tick();
			lelapsedTime = 0;
		}
		if(selapsedTime >= smallPeriod){
			SM_Three_Tick();
			selapsedTime = 0;
		}
		if(soundTime >= freqTime){
			SM_sound();
			soundTime = 0;
		}
		SM_Freq_Tick();
		SM_output();
		PORTB = tmpB;
		while(!TimerFlag){}
		TimerFlag = 0;
		lelapsedTime += TimerPeriod;
		selapsedTime += TimerPeriod;
		soundTime += TimerPeriod;
	}
} 
