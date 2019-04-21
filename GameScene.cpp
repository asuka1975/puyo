#define _CRT_SECURE_NO_WARNINGS
#include<cstdlib>
#include<curses.h>
#include"Field.hpp"
#include"FieldControl.hpp"
#include"BaseScene.h"
#include "GameScene.h"

#ifdef __WINDOWS
#define _WAITINGCOUNT 3000;
#else
#define _WAITINGCOUNT 20000
#endif

GameScene::GameScene() : field()
{
	delay = 0;
	waitCount = _WAITINGCOUNT;

	init_pair(1, COLOR_RED, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	init_pair(3, COLOR_GREEN, COLOR_WHITE);
	init_pair(4, COLOR_YELLOW, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);

	field.ChangeSize(LINES / 2, COLS / 2);
	field.GeneratePuyo();

	for (int y = 0; y < LINES; y++) {
		for (int x = 0; x < COLS; x++) {
			attrset(COLOR_PAIR(0));
			mvaddch(y, x, ' ');
		}
	}
}


GameScene::~GameScene()
{
	
}


int GameScene::Update() {
	int ch;
	ch = getch();

	if (ch == 'Q') exit(0);

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
			field.VanishPuyo();
			if (field.LandingPuyo()) field.GeneratePuyo();
		}
	}
	delay++;


	Display();

	return 1;
}

void GameScene::Display()
{
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

	sprintf(msg, "Score: %6d", field.GetScore());
	mvaddstr(5, COLS - 35, msg);

	refresh();
}
