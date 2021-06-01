/* Author: Robert Rivera (rrive020)
 * Lab Section: 021
 * Assignment: Lab 11: Basic Requirements
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link:
 */

#include <avr/io.h>
#include "Player1.h"
#include "AI.h"
#include "Ball.h"
#include "scheduler.h"
#include "timer.h"

task tasks[4];

const unsigned char tasksNum = 4;
const unsigned long tasksPeriodGCD = 1;
const unsigned long periodP1 = 5; // 1 ; Originally: 5 (period)
const unsigned long periodP1Buttons = 10; // 2 ; Originally: 10 (period)
const unsigned long periodAI = 10; // 3 ; Originally: 10 (period)
const unsigned long periodBall = 500; // 4 ; Originally: 800 (period)

int main(void) {
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	tasks[0].state = P1Wait;
	tasks[0].period = periodP1;
	tasks[0].elapsedTime = tasks[0].period;
	tasks[0].TickFct = &TickFct_P1;

	tasks[1].state = P1ButtonsWait;
	tasks[1].period = periodP1Buttons;
	tasks[1].elapsedTime = tasks[1].period;
	tasks[1].TickFct = &TickFct_P1Buttons;
	
	tasks[2].state = AIWait;
	tasks[2].period = periodAI;
	tasks[2].elapsedTime = tasks[2].period;
	tasks[2].TickFct = &TickFct_AI;
	
	tasks[3].state = P1Start;
	tasks[3].period = periodBall;
	tasks[3].elapsedTime = tasks[3].period;
	tasks[3].TickFct = &TickFct_Ball;
	
	PORTC = 0x00;
	PORTD = 0x00;
	
	TimerSet(tasksPeriodGCD);
	TimerOn();
		
	unsigned char i;
	while (1) {
		for (i = 0; i < tasksNum; ++i) {
			if (tasks[i].elapsedTime >= tasks[i].period) {
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
			tasks[i].elapsedTime += tasksPeriodGCD;
		}
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
