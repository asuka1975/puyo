#define _CRT_SECURE_NO_WARNINGS
#include<curses.h>
#include"Field.hpp"
#include"FieldControl.hpp"
#include"PuyoGenerator.hpp"

#ifdef __WINDOWS
#define _WAITINGCOUNT 1000;
#else
#define _WAITINGCOUNT 20000
#endif

#define DEBUG


void Display(PuyoArrayActive& field, PuyoControl& controller);
void NextPuyoDisplay(PuyoArrayActive& field);

int main(int argc, char* argv[]) {
	initscr();
	start_color();

	noecho();
	cbreak();

	curs_set(0);
	keypad(stdscr, TRUE);

	timeout(0);

	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);


	PuyoArrayActive field;
	PuyoControl controller(LINES / 2, COLS / 2);
	field.ChangeSize(LINES / 2, COLS / 2);
#ifdef DEBUG
	controller.TestCaseStackField();
#endif


	int delay = 0;
	int waitCount = _WAITINGCOUNT;

	int puyostate = 0;


	while (1)
	{
		int ch;
		ch = getch();

		if (ch == 'Q')
		{
			break;
		}

		if (waitCount == 10) waitCount = _WAITINGCOUNT;

		switch (ch)
		{
		case KEY_LEFT:
			controller.MoveLeft(field);
			break;
		case KEY_RIGHT:
			controller.MoveRight(field);
			break;
		case KEY_DOWN:
			waitCount = 10;
			break;
		case 'z':
			controller.Rotate(field, 1);
			break;
		case 'x':
			controller.Rotate(field, -1);
		default:
			break;
		}


		if (delay % waitCount == 0) {

			if (controller.LandingPuyo(field) && !controller.VanishPuyo())
			{
				controller.GeneratePuyo(field);
			}
			controller.MoveDown(field);
		}
		delay++;

		
		Display(field, controller);
	}

	endwin();

	return 0;
}

void Display(PuyoArrayActive& field, PuyoControl& controller) {
	int line = field.GetLine();
	int column = field.GetColumn();

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			puyocolor value = (puyocolor)(controller.GetStack(y, x) | field.GetValue(y, x));
			value = (0x04 & value) ? (puyocolor)(value & (-value)) : value;
			switch (value)
			{
			case NONE:
				attrset(COLOR_PAIR(5));
				mvaddch(y, x, '.');
				break;
			case RED:
				attrset(COLOR_PAIR(1));
				mvaddch(y, x, ' ');
				break;
			case BLUE:
				attrset(COLOR_PAIR(2));
				mvaddch(y, x, ' ');
				break;
			case GREEN:
				attrset(COLOR_PAIR(3));
				mvaddch(y, x, ' ');
				break;
			case YELLOW:
				attrset(COLOR_PAIR(4));
				mvaddch(y, x, ' ');
				break;
			default:
				mvaddch(y, x, '?');
				break;
			}
			int num = 0;
		}
	}

	NextPuyoDisplay(field);

	int count = 0;
	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (controller.GetStack(y, x) != NONE)
			{
				count++;
			}
		}
	}

	char msg[256];
	sprintf(msg, "Field: %d x %d, Puyo number: %03d", field.GetLine(), field.GetColumn(), count);
	attrset(COLOR_PAIR(5));
	mvaddstr(2, COLS - 35, msg);

	refresh();
}

void NextPuyoDisplay(PuyoArrayActive& field)
{
	puyocolor next[4];

	PuyoGenerator::GetNext(0, next[0], next[1]);
	PuyoGenerator::GetNext(1, next[2], next[3]);

	int xpos = field.GetColumn() + 1;
	int ypos = 2;
	int width = 3;
	int height = 7;

	for (int y = ypos; y < ypos + height; y++) {
		for (int x = xpos; x < xpos + width; x++) {
			attrset(COLOR_PAIR(5));
			mvaddch(y, x, ' ');
		}
	}

	for (int i = 0; i < 4; i++) {
		int x = xpos + 1;
		int y = ypos + 1 + i + i / 2;
		switch (next[i])
		{
		case RED:
			attrset(COLOR_PAIR(1));
			mvaddch(y, x, ' ');
			break;
		case BLUE:
			attrset(COLOR_PAIR(2));
			mvaddch(y, x, ' ');
			break;
		case GREEN:
			attrset(COLOR_PAIR(3));
			mvaddch(y, x, ' ');
			break;
		case YELLOW:
			attrset(COLOR_PAIR(4));
			mvaddch(y, x, ' ');
			break;
		default:
			mvaddch(y, x, '?');
			break;
		}
		int num = 0;
	}

	attrset(COLOR_PAIR(0));
	mvaddstr(ypos - 1, xpos, "next");
}
