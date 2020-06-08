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
 
/*	Partner(s) Name & E-mail: Jeff Trang (jtran094@ucr.edu), Kevin Tsai(ktsai017@ucr.edu), Xiangyu Chang(3750627@qq.com)
 *	Lab Section: 022
 *	Assignment: Lab #11  Exercise #5 
 *	Exercise Description: design a game where the player avoids obstacles on the LCD screen
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "io.c"

// global variables
unsigned char tmpB;
unsigned char lcd_top;
unsigned char lcd_bot;
unsigned char user_position; // 1 = top, 17 = bottom
unsigned char obj_top_position;
unsigned char obj_bot_position;
int paused;

// state machines
enum cursor_States {cursor_start, up, down} cursor_state;
enum obj_States {obj_start, move_obj} obj_state;
enum game_States {game_start, play, lose, wait, reset} game_state;

void move_cursor() {
    switch(cursor_state) { // state transitions
        case cursor_start:
            cursor_state = up;
            break;
        case up:
            if (tmpB == 0x02) {
                cursor_state = down;
            }
            break;
        case down:
            if (tmpB == 0x01) {
                cursor_state = up;
            }
            break;
    }
    switch(cursor_state) { // state actions
        case cursor_start:
            break;
        case up:
            LCD_Cursor(1);
            user_position = 1;
            break;
        case down:
            LCD_Cursor(17);
            user_position = 17;
            break;
    }
}

void create_obstacles() {
    switch(obj_state) { // state transitions
        case obj_start:
            obj_state = move_obj;
            break;
        case move_obj:
            if (lcd_top != 1 && lcd_bot != 17) {
                lcd_top = lcd_top - 1;
                lcd_bot = lcd_bot - 1;
            }
            else if (lcd_top == 1) {
                lcd_top = 16;
            }
            else if (lcd_bot == 17) {
                lcd_bot = 32;
            }
            break;
    }
    switch(obj_state) { // state actions
        case obj_start:
            break;
        case move_obj:
            LCD_ClearScreen();
            LCD_DisplayString(lcd_top, (unsigned char*)"?");
            obj_top_position = lcd_top;
            LCD_Cursor(lcd_bot); // NOTE: problems with using DisplayString() or WriteData() twice
            LCD_WriteData('?');  // top LCD doesn't display '?' properly; temporary fix
            obj_bot_position = lcd_bot;
            break;
    }
}

void game_function() {
    switch(game_state) { // state transitions
        case game_start:
            game_state = wait;
            break;
        case play:
            if (user_position == obj_top_position || user_position == obj_bot_position) {
                game_state = lose;
            }
            break;
        case lose:
            game_state = wait;               
            break;
        case wait:
            if (tmpB == 0x04) {
                game_state = reset;
            }
            break;
        case reset:
            game_state = play;
            break;
    }
    switch(game_state) { // state actions
        case game_start:
            break;
        case play:
            move_cursor();
            break;
        case lose:
            LCD_DisplayString(1, (unsigned char*)"Just dodge them. 4Head");
            paused = 1;
            break;
        case wait:
            break;
        case reset:
            LCD_ClearScreen();
            paused = 0;
            break;
    }
}

int main(void) {
    // initialize ports
    DDRB = 0x00; PORTB = 0xFF;
    DDRA = 0xFF; PORTA = 0x00; // LCD control lines
    DDRD = 0xFF; PORTD = 0x00; // LCD data lines
    
    // initialize global variables
    tmpB = 0x00;
    lcd_top = 15; // random position on top LCD
    lcd_bot = 26; // random position on bottom LCD
    paused = 1;
    // initialize local variables
    unsigned long cursor_time = 50;
    unsigned long obstacle_time = 300;
    const unsigned long timer_period = 50;
    
    // initialize states
    cursor_state = cursor_start;
    obj_state = obj_start;
    game_state = game_start;
    
    // initialize timer
    TimerSet(timer_period);
    TimerOn();
    LCD_init();
    while (1) {
        tmpB = ~PINB & 0x07; // use only PB0-PB2
        if (tmpB == 0x04) { // use PB2 to start/restart the game
            paused = 0;
        }
        if (paused == 0) {
            if (cursor_time >= 50) {
                game_function();
                cursor_time = 0;
            }
            if (obstacle_time >= 300) {
                create_obstacles();
                obstacle_time = 0;
            }
        }        
        while (!TimerFlag) {}  // Wait for timer period
        TimerFlag = 0;        // Lower flag
        cursor_time += timer_period;
        obstacle_time += timer_period;        
    }
}





