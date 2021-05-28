#include <avr/io.h>
#include "scheduler.h"
#include "timer.h"
#include "Player1SM.h"
#include "Player1Buttons.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

task tasks[2];

const unsigned char tasksNum = 2;
const unsigned long tasksPeriodGCD = 10;
const unsigned long periodPlayer1 = 100;
const unsigned long periodPlayer1Buttons = 10;

int main(void) {
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	tasks[0].state = Player1_Start;
	tasks[0].period = periodPlayer1;
	tasks[0].elapsedTime = tasks[0].period;
	tasks[0].TickFct = &TickFct_Player1;

	tasks[1].state = Player1Buttons_Start;
	tasks[1].period = periodPlayer1Buttons;
	tasks[1].elapsedTime = tasks[1].period;
	tasks[1].TickFct = &TickFct_Player1Buttons;

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
	
	return 1;
}

