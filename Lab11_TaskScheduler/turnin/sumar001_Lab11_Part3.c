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

unsigned char prev_press; 
unsigned char current_press;

enum SM1_States { press };
enum SM2_States { display };

int TickSM1(int state) {

	switch (state){
		case press:
			state = press;
		break;
	}

	switch (state){
			case press:
				prev_press = GetKeypadKey();
			break;
		}
	return state;
}

int TickSM2(int state){
	switch(state){
		case display:
			state = display;
	}
	switch(state){
		case display:
			if(current_press != prev_press && prev_press != '\0'){
				LCD_Cursor(1);
				LCD_WriteData(prev_press);
				current_press = prev_press;
			}
	}

	return state;
}

int main()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_init();

	// Period for the tasks
	unsigned long int TickSM1_calc = 50;

	//Calculating GCD
	unsigned long int tmpGCD = 1;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int TickSM1_period = TickSM1_calc/GCD;

	//Declare an array of tasks 
	static task task1,task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = 0;//Task initial state.
	task1.period = TickSM1_period;//Task Period.
	task1.elapsedTime = TickSM1_period;//Task current elapsed time.
	task1.TickFct = &TickSM1;//Function pointer for the tick.

	task2.state = 0;
	task2.period = TickSM1_period;
	task2.elapsedTime = TickSM1_period;
	task2.TickFct = &TickSM2;

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

	return 0;
}
