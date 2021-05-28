#ifndef PLAYER1SM_H_
#define PLAYER1SM_H_

#include "Player1Buttons.h"

enum Player1_States {Player1_Start, Paddle, PaddleDown, PaddleUp, WaitRelease};
int TickFct_Player1(int state) {
	static unsigned char pattern = 0x1C;
	static unsigned char row = 0xFE;
		
	switch (state) {
		case Player1_Start:
			state = Paddle;
			break;
		
		case Paddle:
			if (player1Down && !player1Up && pattern != 0xE0) {
				state = PaddleDown;
			} else if (!player1Down && player1Up && pattern != 0x07) {
				state = PaddleUp;
			} else {
				state = Paddle;
			}
			break;
		
		case PaddleDown:
			if (!player1Down && !player1Up) {
				state = Paddle;
			} else if (player1Down && !player1Up) { // The opposite will cause the paddle to move until release
				state = WaitRelease;
			}
			break;

		case PaddleUp:
			if (!player1Down && !player1Up) {
				state = Paddle;
			} else if (!player1Down && player1Up) { // The opposite will cause the paddle to move until release
				state = WaitRelease;
			}
			break;
		
		case WaitRelease:
			if (!player1Down && !player1Up) {
				state = Paddle;
			} else {
				state = WaitRelease;
			}
			break;

		default:
			state = Player1_Start;
			break;
	}
	
	switch (state) {
		case Paddle:
		case WaitRelease:		
			PORTC = pattern;
			PORTD = row;
			break;
		
		case PaddleDown:
			if (pattern == 0xE0) {
				PORTC = pattern;
				PORTD = row;
			} else {
				pattern <<= 1;
				PORTC = pattern;
				PORTD = row;
			}
			break;
		
		case PaddleUp:
			if (pattern == 0x07) {
				PORTC = pattern;
				PORTD = row;
			} else {
				pattern >>= 1;
				PORTC = pattern;
				PORTD = row;
			}
			break;
			
		default:
			break;
	}
	
	return state;
}

#endif /* PLAYER1SM_H_ */