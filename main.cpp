#include<curses.h>
#include"Field.hpp"
#include"FieldControl.hpp"

#ifdef __WINDOWS
#define _WAITINGCOUNT 1500;
#else
#define _WAITINGCOUNT 20000
#endif

void Display(PuyoArrayActive& field, PuyoControl& controller);

int main(int argc, char* argv[]) {
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


	PuyoArrayActive field;
	PuyoControl controller(LINES / 2, COLS / 2);
	field.ChangeSize(LINES / 2, COLS / 2);
	controller.GeneratePuyo(field);

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

		switch (ch)
		{
		case KEY_LEFT:
			controller.MoveLeft(field);
			break;
		case KEY_RIGHT:
			controller.MoveRight(field);
			break;
		case 'z':
			break;
		default:
			break;
		}


		if (delay % waitCount == 0) {
			controller.MoveDown(field);

			if (controller.LandingPuyo(field))
			{
				controller.GeneratePuyo(field);
			}
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
			puyocolor value = controller.GetStack(y, x) != NONE ?
				controller.GetStack(y, x) :
				field.GetValue(y, x) != NONE ?
				field.GetValue(y, x) :
				NONE;
			switch (value)
			{
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
			int num = 0;
		}
	}


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
	sprintf_s(msg, "Field: %d x %d, Puyo number: %03d", field.GetLine(), field.GetColumn(), count);
	mvaddstr(2, COLS - 35, msg);

	refresh();
}