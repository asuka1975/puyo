#define _CRT_SECURE_NO_WARNINGS
#include<curses.h>
#include"Field.hpp"
#include"FieldControl.hpp"

#ifdef __WINDOWS
#define _WAITINGCOUNT 3000;
#else
#define _WAITINGCOUNT 20000
#endif

void Display(FieldControl& field);

int main(int argc, char* argv[]) {
	FieldControl field;

	initscr();
	start_color();

	noecho();
	cbreak();

	curs_set(0);
	keypad(stdscr, TRUE);

	timeout(0);

	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_WHITE);
	init_pair(4, COLOR_YELLOW, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);


	field.ChangeSize(LINES / 2, COLS / 2);	
	field.GeneratePuyo();

	int delay = 0;
	int waitCount = _WAITINGCOUNT;

	int puyostate = 0;


	while (1) {
		int ch;
		ch = getch();

		if (ch == 'Q') break;

		switch (ch) {
		case KEY_LEFT:
			field.MoveLeft();
			break;
		case KEY_RIGHT:
			field.MoveRight();
			break;
		case 'z':
			field.RotatePuyo(RIGHT_ROTATE);
			break;
		case 'x':
			field.RotatePuyo(LEFT_ROTATE);
		default:
			break;
		}


		if (delay%waitCount == 0) {
			field.MoveDown();

			if (field.LandingPuyo()) {
				Display(field);
				field.VanishPuyo();
				if (field.LandingPuyo()) field.GeneratePuyo();
			}
		}
		delay++;

		
		Display(field);
	}

	endwin();

	return 0;
}

void Display(FieldControl& field) {
	for (int y = 0; y < field.GetLine(); y++) {
		for (int x = 0; x < field.GetColumn(); x++) {
			switch (field.GetValue(y, x).color) {
			case NONE:
				attrset(COLOR_PAIR(5));
				mvaddch(y, x, '.');
				break;
			case RED:
				attrset(COLOR_PAIR(1));
				mvaddch(y, x, 'R');
				break;
			case BLUE:
				attrset(COLOR_PAIR(2));
				mvaddch(y, x, 'B');
				break;
			case GREEN:
				attrset(COLOR_PAIR(3));
				mvaddch(y, x, 'G');
				break;
			case YELLOW:
				attrset(COLOR_PAIR(4));
				mvaddch(y, x, 'Y');
				break;
			default:
				mvaddch(y, x, '?');
				break;
			} 
		}
	}


	int count = 0;
	for (int y = 0; y < field.GetLine(); y++) {
		for (int x = 0; x < field.GetColumn(); x++) {
			if (field.GetValue(y, x).color != NONE) count++;
		}
	}

	char msg[256];
	sprintf(msg, "Field: %d x %d, Puyo number: %03d", field.GetLine(), field.GetColumn(), count);
	mvaddstr(2, COLS - 35, msg);

	refresh();
}