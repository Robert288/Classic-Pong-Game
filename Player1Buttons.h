#ifndef PLAYER1BUTTONS_H_
#define PLAYER1BUTTONS_H_

unsigned char player1Up = 0x00;
unsigned char player1Down = 0x00;

enum Player1Buttons_States {Player1Buttons_Start, Wait};
int TickFct_Player1Buttons(int state) {
	switch (state) {
		case Player1Buttons_Start:
		case Wait:
			state = Wait;
			break;
		
		default:
			state = Player1Buttons_Start;
			break;
	}
	
	switch (state) {
		case Wait:
			player1Down = ~PINB & 0x01;
			player1Up = ~PINB & 0x02;	
			break;
		
		default:
			break;
	}
	
	return state;
}

#endif /* PLAYER1BUTTONS_H_ */