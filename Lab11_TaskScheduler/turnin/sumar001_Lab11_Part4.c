/*	Author: sumar001
 *       Partner(s) Name: 
 *	Lab Section: 25
 *	Assignment: Lab #11  Exercise #4
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

unsigned char tmp = 0x00;
unsigned char j = 1;


enum SM1_States{display};

int Tick(int state){
	unsigned char x;
	x = GetKeypadKey();
	switch(state){
		case display:
			switch (x) {
				case '\0': 
					break; 
				case '1': tmp = 0x01;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '2': tmp = 0x02;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '3': tmp = 0x03;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '4': tmp = 0x04; 
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '5': tmp = 0x05;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '6': tmp = 0x06;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '7': tmp = 0x07;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '8': tmp = 0x08;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '9': tmp = 0x09;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case 'A': tmp = 0x0A;
				LCD_Cursor(j); LCD_WriteData(tmp + 0x37); j++; 
					  break;
				case 'B': tmp = 0x0B;
				LCD_Cursor(j); LCD_WriteData(tmp + 0x37); j++; 
					  break;
				case 'C': tmp = 0x0C;
				LCD_Cursor(j); LCD_WriteData(tmp + 0x37); j++; 
					  break;
				case 'D': tmp = 0x0D;
				LCD_Cursor(j); LCD_WriteData(tmp + 0x37); j++; 
					  break;
				case '*': tmp = 0x0E;
				LCD_Cursor(j); LCD_WriteData(tmp + 0x1C); j++; 
					  break;
				case '0': tmp = 0x00;
				LCD_Cursor(j); LCD_WriteData(tmp + '0'); j++; 
					  break;
				case '#': tmp = 0x0F;
				LCD_Cursor(j); LCD_WriteData(tmp + 0x14); j++; 
					  break;
			}
			if(j==17){
				j=1;
			}
			state = display;
			PORTB = tmp;
			break;
		}
		return state;
}


int main()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; 
	DDRD = 0xFF; PORTD = 0x00;
	// Period for the tasks
	unsigned long int Tick_calc = 200;


	//Calculating GCD
	unsigned long int tmpGCD = 1;

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int Tick_period = Tick_calc;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = 0;//Task initial state.
	task1.period = Tick_period;//Task Period.
	task1.elapsedTime = Tick_period;//Task current elapsed time.
	task1.TickFct = &Tick;//Function pointer for the tick.


	TimerSet(GCD);
	TimerOn();
	LCD_init();
	LCD_DisplayString(1,"Congratulations");

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
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
