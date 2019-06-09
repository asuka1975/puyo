#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<algorithm>
#include<curses.h>
#include"Field.hpp"
#include"FieldControl.hpp"
#include"PuyoGenerator.hpp"

#ifdef __WINDOWS
#define _WAITINGCOUNT 1000
#else
#define _WAITINGCOUNT 20000
#endif



void Display(PuyoArrayActive& field, PuyoControl& controller);
void NextPuyoDisplay(PuyoArrayActive& field);
void GameOverDisplay(PuyoArrayActive& field, PuyoControl& controller);
void PutPuyoYX(unsigned int y, unsigned int x, puyocolor puyo);
void RecordInit();
void Record(int scre, std::vector<int>& record);

static int score = 0;
static double chain = 1.0;
std::vector<int> records(5);
static void(*displayFunc)(PuyoArrayActive& field, PuyoControl& controller) = Display;

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

	RecordInit();

	PuyoArrayActive field;
	PuyoControl controller(LINES / 2, COLS / 2);
	field.ChangeSize(LINES / 2, COLS / 2);

	int delay = 0;
	int waitCount = _WAITINGCOUNT;

	int puyostate = 0;

	bool is_gameover = false;

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
			if (!is_gameover) {
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
			break;
			}
		case 'n':
			if (is_gameover) {
				is_gameover = false;
				attrset(COLOR_PAIR(0));
				for (int y = 0; y < LINES; y++) {
					for (int x = 0; x < COLS; x++) {
						mvaddch(y, x, ' ');
					}
				}
				field.ChangeSize(LINES / 2, COLS / 2);
				controller.Initialize(LINES / 2, COLS / 2);
				score = 0;
				displayFunc = Display;
			}
			break;
		default:
			break;
		}


		if (delay % waitCount == 0) {
			if (!is_gameover && (is_gameover = controller.IsGameOver(field))) {
				displayFunc = GameOverDisplay;
				Record(score, records);
			}
			else if (!is_gameover) {
				int vanishpuyo_num = 0;
				if (controller.LandingPuyo(field) && !(vanishpuyo_num = controller.VanishPuyo()))
				{
					chain = 1.0;
					controller.GeneratePuyo(field);
				}
				score += vanishpuyo_num * 100 * chain;
				if (vanishpuyo_num) chain += 0.5;
				controller.MoveDown(field);
			}
		}
		delay++;
		delay %= waitCount;

		displayFunc(field, controller);
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
			PutPuyoYX(y, x, value);
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

	
	char scre[100];
	sprintf(scre, "Score: %d", score);
	mvaddstr(4, COLS - 35, scre);

	refresh();
}

void NextPuyoDisplay(PuyoArrayActive& field)
{
	puyocolor next[4];

	PuyoGenerator::GetNext(0, next[0], next[1]);
	PuyoGenerator::GetNext(1, next[2], next[3]);

	int xpos = field.GetColumn() + 1;
	int ypos = 7;
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
		PutPuyoYX(y, x, next[i]);
		int num = 0;
	}

	attrset(COLOR_PAIR(0));
	mvaddstr(ypos - 1, xpos, "next");
}

void GameOverDisplay(PuyoArrayActive & field, PuyoControl & controller)
{
	static int delay = 0;
	delay %= _WAITINGCOUNT * 3;

	attrset(COLOR_PAIR(0));
	for (int y = 0; y < LINES; y++) {
		for (int x = 0; x < COLS; x++) {
			mvaddch(y, x, ' ');
		}
	}
	int y = LINES / 4;
	int x = COLS / 2 - 4;
	attrset(COLOR_PAIR(5));
	mvaddstr(y, x, "gameover!");

	char scrmsg[256];
	sprintf(scrmsg, "Your Score : %d", score);
	mvaddstr(y + 2, x - 2, scrmsg);

	char record[256];
	for (int i = 0; i < records.size(); i++) {
		sprintf(record, "%d. %10d", i + 1, records[i]);
		mvaddstr(y + 3 + i, x - 2, record);
	}

	if (0 < delay && delay < _WAITINGCOUNT * 3 / 2) {
		attrset(COLOR_PAIR(5));
	}
	else {
		attrset(COLOR_PAIR(0));
	}
	std::vector<int>::iterator iter = std::find(records.begin(), records.end(), score);
	if (iter == records.end()) {
		char yourscore[256];
		sprintf(yourscore, "*. %10d", score);
		mvaddstr(y + 9, x - 2, yourscore);
	}
	else {
		int idx = std::distance(records.begin(), iter);
		char yourscore[256];
		sprintf(yourscore, "%d. %10d", idx + 1, score);
		mvaddstr(y + 3 + idx, x - 2, yourscore);
	}

	attrset(COLOR_PAIR(0));
	mvaddstr(y + 11, x - 2, "click N-Key to new game.");
	
	delay++;
}

void PutPuyoYX(unsigned int y, unsigned int x, puyocolor puyo)
{
	switch (puyo)
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
		attrset(COLOR_PAIR(0));
		mvaddch(y, x, '?');
		break;
	}
}

void RecordInit()
{
	FILE* fp = fopen("record.txt", "r");
	if (!fp) {
		fp = fopen("record.txt", "w");
		fprintf(fp, "0\n0\n0\n0\n0");
	}
	fclose(fp);
}

void Record(int scre, std::vector<int>& record)
{
	FILE* fp = fopen("record.txt", "r");
	for (int i = 0; i < record.size(); i++) {
		int num = 0;
		fscanf(fp, "%d", &num);
		record[i] = num;
	}
	fclose(fp);

	for (int i = record.size() - 1; i >= 0; i--) {
		if (record[i] < scre) {
			if (i + 1 > 4) {
				record[i] = scre;

				
			}
			else {
				record[i + 1] = record[i];
				record[i] = scre;
			}
		}
	}

	fp = fopen("record.txt", "w");
	for (int i = 0; i < record.size(); i++) {
		fprintf(fp, "%d\n", record[i]);
	}

	fclose(fp);
}
