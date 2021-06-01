#ifndef AI_H_
#define AI_H_

#include "Ball.h"

// const unsigned char AIpattern = 0x01; // AI's Paddle
const unsigned char AIrow[3] = {0xF8, 0xF1, 0xE3}; // AI's Paddle Positions
// static unsigned char j = 1;

enum AI_States {AIWait, AILeft, AIRight};
int TickFct_AI(int state) {
	switch (state) {
		case AIWait:
			if (j == 0) {
				if (ballrows[k] == 0xF7 || ballrows[k] == 0xEF) {
					state = AILeft;
				} else {
					state = AIWait;
				}
			} else if (j == 1) {
				if (ballrows[k] == 0xFE) {
					state = AIRight;
				} else if (ballrows[k] == 0xEF) {
					state = AILeft;
				} else {
					state = AIWait;
				}
			} else if (j == 2) {
				if (ballrows[k] == 0xFD || ballrows[k] == 0xFE) {
					state = AIRight;
				} else {
					state = AIWait;
				}
			} 
			break;
			
		default:
			state = AIWait;
			break;
	}
	
	switch (state) {
		case AIWait:
			break;
		
		case AILeft:
			if (j >= 2) {
				j = 2;
			} else {
				++j;
			}
			break;
		
		case AIRight:
			if (j <= 0) {
				j = 0;
			} else {
				--j;
			}
			break;
		
		default:
			break;
	}
	
	PORTC = AIpattern;
	PORTD = AIrow[j];
	return state;
};

#endif /* AI_H_ */