#ifndef AI_H_
#define AI_H_

#include "AIEngine.h"

const unsigned char AIpattern = 0x01; // AI's Paddle
const unsigned char AIrow[3] = {0xF8, 0xF1, 0xE3}; // AI's Paddle Positions
static unsigned char j = 1;

enum AI_States {AIWait};
int TickFct_AI(int state) {
	// const unsigned char AIpattern = 0x01; // AI's Paddle
	// const unsigned char AIrow[3] = {0xF8, 0xF1, 0xE3}; // AI's Paddle Positions
	// static unsigned char j = 1;
	
	switch (state) {
		case AIWait:
			break;
			
		default:
			state = AIWait;
			break;
	}
	
	switch (state) {
		case AIWait:
		default:
			break;
	}
	
	PORTC = AIpattern;
	PORTD = AIrow[j];
	return state;
};

#endif /* AI_H_ */