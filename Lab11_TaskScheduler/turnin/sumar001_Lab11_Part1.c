/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include <avr/io.h>
//#include <avr/interrupt.h>
//#include "bit.h"
#include "timer.h"
#include <stdio.h>
//#include "io.c"
#include "io.h"
//#include "keypad.h"
#include "scheduler.h"

enum SMTask1_States {start} state;
int Tick_keypad(int state) {
	unsigned char x;
	x = GetKeypadKey();
	switch(state) {
		case start:
		   switch(x) {
			case '\0' : PORTB = 0x1F; break; //All 5 Leds on
			case '1' : PORTB = 0x01; break;
			case '2' : PORTB = 0x02; break;
			case '3' : PORTB = 0x03; break;
			case '4' : PORTB = 0x04; break;
			case '5' : PORTB = 0x05; break;
			case '6' : PORTB = 0x06; break;
			case '7' : PORTB = 0x07; break;
			case '8' : PORTB = 0x08; break;
			case '9' : PORTB = 0x09; break;
			case 'A' : PORTB = 0x0A; break;
			case 'B' : PORTB = 0x0B; break;
			case 'C' : PORTB = 0x0C; break;
			case 'D' : PORTB = 0x0D; break;
			case '*' : PORTB = 0x0E; break;
			case '0' : PORTB = 0x00; break;
			case '#' : PORTB = 0x0F; break;
			default: PORTB = 0x1B; break;
			}
		state = start;
		break;
	     }
	return state;
       }


int main(void) {
   	unsigned char x;
     /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;

    /* Insert your solution below */
	 unsigned long int Tick_keypad_calc = 20;

	//Calculating GCD
	unsigned long int tmpGCD = 10;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int Tick_keypad_period = Tick_keypad_calc/GCD;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = 0;//Task initial state.
	task1.period = Tick_keypad_period;//Task Period.
	task1.elapsedTime = Tick_keypad_period;//Task current elapsed time.
	task1.TickFct = &Tick_keypad;//Function pointer for the tick.


	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
	
