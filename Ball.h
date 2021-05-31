#ifndef BALL_H_
#define BALL_H_

enum Ball_States {Start, };
int TickFct_Ball(int state) {
	static unsigned char k = 2;
	static unsigned char ballpattern = 0x10; // Ball Starting Position
	const unsigned char ballrows[5] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF}; // Ball's Positions

	switch (state) {
		case Start:
			if (ballpattern == )
			
		default:
			state = Start;
			break;
	}
	
	switch (state) {
		default:
			break;
	}

	PORTC = ballpattern;
	PORTD = ;
	return state;	
};



#endif /* BALL_H_ */