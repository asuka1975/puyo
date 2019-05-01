#include<cstdlib>
#include<ctime>
#include"Field.hpp"
#include"FieldControl.hpp"

void FieldControl::GeneratePuyo(FieldArray& field) {
	srand(static_cast<unsigned>(time(NULL)));

	field.SetValue(0, 5, static_cast<puyocolor>(rand() % 4 + 1));
	field.SetValue(0, 6, static_cast<puyocolor>(rand() % 4 + 1));
}

bool FieldControl::LandingPuyo(FieldArray& field) {
	bool landed = false;

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (field.GetValue(y, x) != NONE && y == field.GetLine() - 1)
			{
				landed = true;

				field.SetValue(y, x, NONE);
			}
		}
	}

	return landed;
}

void FieldControl::MoveLeft(FieldArray& field) {
	puyocolor *puyo_temp = new puyocolor[field.GetLine() * field.GetColumn()];

	for (int i = 0; i < field.GetLine() * field.GetColumn(); i++) puyo_temp[i] = puyocolor();

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (field.GetValue(y, x) == NONE) continue;

			if (0 < x && field.GetValue(y, x - 1) == NONE)
			{
				puyo_temp[y * field.GetColumn() + (x - 1)] = field.GetValue(y, x);
				
				field.SetValue(y, x, NONE);
			}
			else
			{
				puyo_temp[y * field.GetColumn() + x] = field.GetValue(y, x);
			}
		}
	}

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			field.SetValue(y, x, puyo_temp[y * field.GetColumn() + x]);
		}
	}

	delete[] puyo_temp;
}

void FieldControl::MoveRight(FieldArray& field) {
	puyocolor *puyo_temp = new puyocolor[field.GetLine() * field.GetColumn()];

	for (int i = 0; i < field.GetLine() * field.GetColumn(); i++) puyo_temp[i] = NONE;

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = field.GetColumn() - 1; x >= 0; x--)
		{
			if (field.GetValue(y, x) == NONE) continue;

			if (x < field.GetColumn() - 1 && field.GetValue(y, x + 1) == NONE)
			{
				puyo_temp[y * field.GetColumn() + (x + 1)] = field.GetValue(y, x);

				field.SetValue(y, x, NONE);
			}
			else
			{
				puyo_temp[y * field.GetColumn() + x] = field.GetValue(y, x);
			}
		}
	}

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			field.SetValue(y, x, puyo_temp[y * field.GetColumn() + x]);
		}
	}

	delete[] puyo_temp;
}

void FieldControl::MoveDown(FieldArray& field) {
	puyocolor *puyo_temp = new puyocolor[field.GetLine() * field.GetColumn()];

	for (int i = 0; i < field.GetLine() * field.GetColumn(); i++) puyo_temp[i] = NONE;

	for (int y = field.GetLine() - 1; y >= 0; y--)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			if (field.GetValue(y, x) == NONE) continue;

			if (y < field.GetLine() - 1 && field.GetValue(y + 1, x) == NONE)
			{
				puyo_temp[(y + 1) * field.GetColumn() + x] = field.GetValue(y, x);

				field.SetValue(y, x, NONE);
			}
			else
			{
				puyo_temp[y * field.GetColumn() + x] = field.GetValue(y, x);
			}
		}
	}

	for (int y = 0; y < field.GetLine(); y++)
	{
		for (int x = 0; x < field.GetColumn(); x++)
		{
			field.SetValue(y, x, puyo_temp[y * field.GetColumn() + x]);
		}
	}

	delete[] puyo_temp;
}