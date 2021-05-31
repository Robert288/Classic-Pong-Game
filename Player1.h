#ifndef PLAYER1_H_
#define PLAYER1_H_

#include "P1Buttons.h"

const unsigned char P1pattern = 0x80; // P1's Paddle
const unsigned char P1row[3] = {0xF8, 0xF1, 0xE3}; // P1's Paddle Positions
static unsigned char i = 1;

enum P1_States {P1Wait, P1Left, P1Right, P1WaitRelease};
int TickFct_P1(int state) {
	// const unsigned char P1pattern = 0x80; // P1's Paddle
	// const unsigned char P1row[3] = {0xF8, 0xF1, 0xE3}; // P1's Paddle Positions
	// static unsigned char i = 1;
	
	switch (state) {
		case P1Wait:
			if (p1Left && !p1Right) {
				state = P1Left;
			} else if (!p1Left && p1Right) {
				state = P1Right;
			} else {
				state = P1Wait;
			}
			break;
		
		case P1Left:
			if (!p1Left && !p1Right) {
				state = P1Wait;
			} else if (p1Left && !p1Right) { // The opposite will cause the paddle to move until release
				state = P1WaitRelease;
			}
			break;
		
		case P1Right:
			if (!p1Left && !p1Right) {
				state = P1Wait;
			} else if (!p1Left && p1Right) { // The opposite will cause the paddle to move until release
				state = P1WaitRelease;
			}
			break;

		case P1WaitRelease:
			if (!p1Left && !p1Right) {
				state = P1Wait;
			} else {
				state = P1WaitRelease;
			}
			break;
			
		default:
			state = P1Wait;
			break;
	}
	
	switch (state) {
		case P1Wait:
			break;
		
		case P1Left:
			if (i <= 0) {
				i = 0;
			} else {
				--i;
			}
			break;
			
		case P1Right:
			if (i >= 2) {
				i = 2;
			} else {
				++i;
			}
			break;
		
		case P1WaitRelease:
			break;
			
		default:
			break;
	}
	
	PORTC = P1pattern;
	PORTD = P1row[i];
	return state;
}

#endif /* PLAYER1_H_ */