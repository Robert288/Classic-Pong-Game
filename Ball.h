#ifndef BALL_H_
#define BALL_H_

#include "AI.h"
const unsigned char AIpattern = 0x01; // AI's Paddle
static unsigned char j = 1;

static unsigned char l = 4; // Index for Ballpatterns array
unsigned char ballpatterns[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};	
	
static unsigned char k = 2; // Index for Ballrows array
unsigned char ballrows[5] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF};

enum Ball_States {P1Start, P1BMiddle, P1BLeft, P1BRight, AITurn, AIBMiddle, AIBRight, AIBLeft, P1Turn, GameOver};
int TickFct_Ball(int state) {
	unsigned char computation; // Determines where the ball hits the paddle (left, middle, or right)

	switch (state) {
		case P1Start: // Game starts with ball heading straight towards P1
			if (ballpatterns[l] == P1pattern) { 
				if (i == 1) { // Paddle is in the middle
					computation = (ballrows[k] >> i) & 0x07;
					if (computation == 5) {
						state = P1BMiddle;
					}
				} else if (i == 2) { // Paddle is in the right
					computation = (ballrows[k] >> i) & 0x07;
					if (computation == 6) {
						state = P1BLeft;
					}
				} else if (i == 0) { // Paddle is in the left
					computation = (ballrows[k] >> i) & 0x07;
					if (computation == 3) {
						state = P1BRight;
					}
				}
			} else {
				state = P1Start;
			}
			break;
		
		case P1BMiddle:
			if (ballpatterns[l] == AIpattern) {
				state = AITurn;
			} else {
				state = P1BMiddle;
			}
			break;
		
		case P1BLeft:
			if (ballpatterns[l] == AIpattern) {
				state = AITurn;
				break;
			}
		
			if (ballrows[k] == 0xFE) {
				state = P1BRight;
			} else {
				state = P1BLeft;
			}
			break;
		
		case P1BRight:	
			if (ballpatterns[l] == AIpattern) {
				state = AITurn;
				break;
			}
					
			if (ballrows[k] == 0xEF) {
				state = P1BLeft;
			} else {
				state = P1BRight;
			}
			break;
		
		case AITurn:
			if (j == 1) {
				if (ballrows[k] == 0xFE || ballrows[k] == 0xEF) {
					state = GameOver;
				} else {
					computation = (ballrows[k] >> j) & 0x07;
					if (computation == 3) {
						state = AIBRight;
						} else if (computation == 5) {
						state = AIBMiddle;
						} else if (computation == 6) {
						state = AIBLeft;
					}
				}
			} else if (j == 0) {
				if (ballrows[k] == 0xF7 || ballrows[k] == 0xEF) {
					state = GameOver;
				} else {
					computation = ballrows[k] & 0x07;
					if (computation == 3) {
						state = AIBRight;
						} else if (computation == 5) {
						state = AIBMiddle;
						} else if (computation == 6) {
						state = AIBLeft;
					}
				}
			} else if (j == 2) {
				if (ballrows[k] == 0xFE || ballrows[k] == 0xFD) {
					state = GameOver;
				} else {
					computation = (ballrows[k] >> j) & 0x07;
					if (computation == 3) {
						state = AIBRight;
						} else if (computation == 5) {
						state = AIBMiddle;
						} else if (computation == 6) {
						state = AIBLeft;
					}
				}
			}
			break;
		
		case AIBMiddle:
			if (ballpatterns[l] == P1pattern) {
				state = P1Turn;
			} else {
				state = AIBMiddle;
			}
			break;
		
		case AIBRight:
			if (ballpatterns[l] == P1pattern) {
				state = P1Turn;
				break;
			}
			
			if (ballrows[k] == 0xEF) {
				state = AIBLeft;
			} else {
				state = AIBRight;
			}
			break;
		
		case AIBLeft:
			if (ballpatterns[l] == P1pattern) {
				state = P1Turn;
				break;
			}
			
			if (ballrows[k] == 0xFE) {
				state = AIBRight;
			} else {
				state = AIBLeft;
			}
			break;
			
		case P1Turn:
			if (i == 1) {
				if (ballrows[k] == 0xFE || ballrows[k] == 0xEF) {
					state = GameOver;
				} else {
					computation = (ballrows[k] >> i) & 0x07;
					if (computation == 3) {
						state = P1BRight;
					} else if (computation == 5) {
						state = P1BMiddle;
					} else if (computation == 6) {
						state = P1BLeft;
					}
				}
			} else if (i == 0) {
				if (ballrows[k] == 0xF7 || ballrows[k] == 0xEF) {
					state = GameOver;
				} else {
					computation = ballrows[k] & 0x07;
					if (computation == 3) {
						state = P1BRight;
					} else if (computation == 5) {
						state = P1BMiddle;
					} else if (computation == 6) {
						state = P1BLeft;
					}	
				}
			} else if (i == 2) {
				if (ballrows[k] == 0xFE || ballrows[k] == 0xFD) {
					state = GameOver;
				} else {
					computation = (ballrows[k] >> i) & 0x07;
					if (computation == 3) {
						state = P1BRight;
					} else if (computation == 5) {
						state = P1BMiddle;
					} else if (computation == 6) {
						state = P1BLeft;
					}
				}
			}
			break;
			
		case GameOver:
			if ((~PINB & 0x04) == 0x04) {
				l = 4; k = 2;
				state = P1Start;
			} else {
				state = GameOver;
			}
			break;
		
		default:
			state = P1Start;
			break;
	}
	
	switch (state) {
		case P1Start:
			--l; 
			break;
		
		case P1BMiddle: // Shift ball to the right once. Ball row stays the same
			++l;
			break;
		
		case P1BLeft: // Shift ball to the right once. Shift ball row upward
			++l;
			--k; 
			break;
		
		case P1BRight: // Shift ball to the right once. Shift ball row upward
			++l;
			++k;
			break;
			
		case AITurn:
			break;

		case AIBMiddle:
			--l;
			break;
		
		case AIBRight:
			--l;
			++k;
			break;
		
		case AIBLeft:
			--l;
			--k;
			break;
		
		case P1Turn:
			break;
		
		case GameOver:
			break;

		default:
			break;
	}

	PORTC = ballpatterns[l];
	PORTD = ballrows[k];
	return state;	
};

#endif /* BALL_H_ */