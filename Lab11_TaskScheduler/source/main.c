/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #11  Exercise #3
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
#include "scheduler.h"
#include "keypad.h"

//--------Shared Variables----------------------------------------------------
unsigned char pressed_char, curr_char;
//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum SM1_States { KeyPress };
enum SM2_States { LCD_W };

// Monitors button connected to PA0. 
// When button is pressed, shared variable "pause" is toggled.
int SMTick1(int state) {

	switch (state){
		case KeyPress:
			state = KeyPress;
		break;
		default:
			state = KeyPress;
	}

	switch (state){
			case KeyPress:
				pressed_char = GetKeypadKey();
			break;
			default:
			break;
		}
	return state;
}

int SMTick2(int state){
	switch(state){
		case LCD_W:
			state = LCD_W;
		default:
			state = LCD_W;
			break;
	}
	switch(state){
		case LCD_W:
			if(curr_char != pressed_char && pressed_char != '\0'){
				LCD_Cursor(1);
				LCD_WriteData(pressed_char);
				curr_char = pressed_char;
			}
		default:
		break;
	}

	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
	// Set Data Direction Registers
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xFF; PORTD = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	// . . . etc
	LCD_init();

	// Period for the tasks
	unsigned long int SMTick1_calc = 50;

	//Calculating GCD
	unsigned long int tmpGCD = 1;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int SMTick1_period = SMTick1_calc/GCD;

	//Declare an array of tasks 
	static task task1,task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = SMTick1_period;//Task Period.
	task1.elapsedTime = SMTick1_period;//Task current elapsed time.
	task1.TickFct = &SMTick1;//Function pointer for the tick.

	task2.state = -1;
	task2.period = SMTick1_period;
	task2.elapsedTime = SMTick1_period;
	task2.TickFct = &SMTick2;

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

	// Error: Program should not exit!
	return 0;
}
