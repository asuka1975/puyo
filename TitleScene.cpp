#define _CRT_SECURE_NO_WARNINGS
#include<cstdlib>
#include<curses.h>
#include"BaseScene.h"
#include "TitleScene.h"

static int Title[270] = {
	1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0,
	1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0
};

static void(*nextScene)();

TitleScene::TitleScene()
{
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	menu = 0;
}

TitleScene::~TitleScene()
{

}

int TitleScene::Update() {
	int ch = getch();

	if (ch == 'Q') exit(0);

	switch (ch)
	{
	case KEY_LEFT:
		menu = 0;
		break;
	case KEY_RIGHT:
		menu = 1;
		break;
	case 'e':
		if (menu) exit(0);
		return 0;
		break;
	default:
		break;
	}

	Display();
	return 1;
}

void TitleScene::Display()
{
	int x_start = (COLS - 45) / 2;
	int y_start = 2;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 45; x++) {
			if (Title[y * 45 + x]) attrset(COLOR_PAIR(1));
			else attrset(COLOR_PAIR(2));
			mvaddch(y + y_start, x + x_start, ' ');
		}
	}

	if (!menu) attrset(COLOR_PAIR(1));
	else attrset(COLOR_PAIR(2));
	mvaddstr(15, (COLS / 2) - 8, "start");
	if (menu) attrset(COLOR_PAIR(1));
	else attrset(COLOR_PAIR(2));
	mvaddstr(15, (COLS / 2) + 5, "exit");

	refresh();
}
