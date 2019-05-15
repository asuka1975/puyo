#include<cstdlib>
#include<ctime>
#include"Field.hpp"
#include"FieldControl.hpp"

PuyoControl::PuyoControl(unsigned int line, unsigned int column)
{
	stackArray.ChangeSize(line, column);
}

void PuyoControl::GeneratePuyo(PuyoArrayActive& field) {
	srand(static_cast<unsigned>(time(NULL)));

	field.SetValue(0, 5, static_cast<puyocolor>(rand() % 4 + 1));
	field.SetValue(0, 6, static_cast<puyocolor>(rand() % 4 + 1));
}

bool PuyoControl::LandingPuyo(PuyoArrayActive& field) {
	bool landed = true;

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (field.GetValue(y, x) != NONE) {
				if (y == field.GetLine() - 1 || stackArray.GetValue(y + 1, x) != NONE) {
					StackingActivePuyo(field);
					landed = true;
				}
				else landed = false;
			}
		}
	}
	if (landed && !StackLanded()) {
		StackUpdate();
		landed = false;
	}

	return landed;
}

void PuyoControl::MoveLeft(PuyoArrayActive& field) {

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (field.GetValue(y, x) == NONE) continue;

			if (0 < x && stackArray.GetValue(y, x - 1) == NONE && field.GetValue(y, x - 1) == NONE)
			{
				field.SetValue(y, x - 1, field.GetValue(y, x));
				field.SetValue(y, x, NONE);
			}
		}
	}
}

void PuyoControl::MoveRight(PuyoArrayActive& field) {
	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = field.GetColumn() - 1; x >= 0; x--)
		{
			if (field.GetValue(y, x) == NONE) continue;

			if (x < field.GetColumn() - 1 && stackArray.GetValue(y, x + 1) == NONE && field.GetValue(y, x + 1) == NONE)
			{
				field.SetValue(y, x + 1, field.GetValue(y, x));
				field.SetValue(y, x, NONE);
			}
		}
	}
}

void PuyoControl::MoveDown(PuyoArrayActive& field) {
	for (int y = field.GetLine() - 1; y >= 0; y--)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (field.GetValue(y, x) == NONE) continue;

			if (y < field.GetLine() - 1 && field.GetValue(y + 1, x) == NONE)
			{
				field.SetValue(y + 1, x, field.GetValue(y, x));
				field.SetValue(y, x, NONE);
			}
		}
	}
}

puyocolor PuyoControl::GetStack(unsigned int y, unsigned int x)
{
	return stackArray.GetValue(y, x);
}

void PuyoControl::StackingActivePuyo(PuyoArrayActive& field)
{
	for (int y = 0; y < field.GetLine(); y++) {
		for (int x = 0; x < field.GetColumn(); x++) {
			if (field.GetValue(y, x) != NONE) {
				stackArray.SetValue(y, x, field.GetValue(y, x));
				field.SetValue(y, x, NONE);
			}
		}
	}
}

void PuyoControl::StackUpdate()
{
	for (int y = stackArray.GetLine() - 2; y >= 0; y--) {
		for (int x = 0; x < stackArray.GetColumn(); x++) {
			if (stackArray.GetValue(y, x) != NONE && stackArray.GetValue(y + 1, x) == NONE) {
				stackArray.SetValue(y + 1, x, stackArray.GetValue(y, x));
				stackArray.SetValue(y, x, NONE);
			}
		}
	}
}

bool PuyoControl::StackLanded()
{
	for (int y = 0; y < stackArray.GetLine() - 1; y++) {
		for (int x = 0; x < stackArray.GetColumn(); x++) {
			if (stackArray.GetValue(y, x) != NONE && stackArray.GetValue(y + 1, x) == NONE) 
				return false;
		}
	}
	return true;
}
