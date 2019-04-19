#include<cstdlib>
#include<ctime>
#include"Field.hpp"
#include"FieldControl.hpp"

FieldControl::FieldControl() : Field() {

}

void FieldControl::GeneratePuyo() {
	srand(static_cast<unsigned>(time(NULL)));
	puyodata newpuyo1(static_cast<puyocolor>(rand() % 4 + 1));
	puyodata newpuyo2(static_cast<puyocolor>(rand() % 4 + 1));

	SetValue(0, 5, newpuyo1);
	SetValue(0, 6, newpuyo2);
}

bool FieldControl::LandingPuyo() {
	bool landed = true;

	for (int y = 0; y < GetLine(); y++) {
		for (int x = 0; x < GetColumn(); x++) {
			if (GetValue(y, x).color != NONE && y < GetLine() - 1) {
				if (GetValue(y + 1, x).color == NONE) {
					landed = false;
					continue;
				}
				else if (GetValue(y, x).handling) {
					puyodata puyo = GetValue(y, x);
					puyo.handling = false;
					SetValue(y, x, puyo);
					puyodata right = GetValue(y, x + 1);
					right.handling = false;
					SetValue(y, x + 1, right);
					puyodata left = GetValue(y, x - 1);
					left.handling = false;
					SetValue(y, x - 1, left);
				}
			}
			else {
				puyodata puyo = GetValue(y, x);
				puyo.handling = false;
				SetValue(y, x, puyo);
			}
		}
	}

	return landed;
}

void FieldControl::MoveLeft() {
	puyodata *puyo_temp = new puyodata[GetLine() * GetColumn()];

	for (int i = 0; i < GetLine()*GetColumn(); i++) puyo_temp[i] = puyodata();

	for (int y = 0; y < GetLine(); y++) {
		for (int x = 0; x < GetColumn(); x++) {
			if (GetValue(y, x).color == NONE) continue;
			if (0 < x && GetValue(y, x - 1).color == NONE) {
				if (!GetValue(y, x).handling) {
					puyo_temp[y * GetColumn() + x] = GetValue(y, x);
					continue;
				}
				puyo_temp[y * GetColumn() + (x - 1)] = GetValue(y, x);

				SetValue(y, x, puyodata());
			}
			else {
				puyo_temp[y*GetColumn() + x] = GetValue(y, x);
			}
		}
	}

	for (int y = 0; y < GetLine(); y++) {
		for (int x = 0; x < GetColumn(); x++) {
			SetValue(y, x, puyo_temp[y * GetColumn() + x]);
		}
	}

	delete[] puyo_temp;
}

void FieldControl::MoveRight() {
	puyodata *puyo_temp = new puyodata[GetLine() * GetColumn()];

	for (int i = 0; i < GetLine() * GetColumn(); i++) puyo_temp[i] = puyodata();

	for (int y = 0; y < GetLine(); y++) {
		for (int x = GetColumn() - 1; x >= 0; x--) {
			if (GetValue(y, x).color == NONE) continue;
			if (x < GetColumn() - 1 && GetValue(y, x + 1).color == NONE) {
				if (!GetValue(y, x).handling) {
					puyo_temp[y * GetColumn() + x] = GetValue(y, x);
					continue;
				}
				puyo_temp[y * GetColumn() + (x + 1)] = GetValue(y, x);

				SetValue(y, x, puyodata());
			}
			else {
				puyo_temp[y * GetColumn() + x] = GetValue(y, x);
			}
		}
	}

	for (int y = 0; y <GetLine(); y++) {
		for (int x = 0; x < GetColumn(); x++) {
			SetValue(y, x, puyo_temp[y * GetColumn() + x]);
		}
	}

	delete[] puyo_temp;
}

void FieldControl::MoveDown() {
	puyodata *puyo_temp = new puyodata[GetLine() * GetColumn()];

	for (int i = 0; i < GetLine() * GetColumn(); i++) puyo_temp[i] = puyodata();

	for (int y = GetLine() - 1; y >= 0; y--) {
		for (int x = 0; x < GetColumn(); x++) {
			if (GetValue(y, x).color == NONE) continue;
			if (y < GetLine() - 1 && GetValue(y + 1, x).color == NONE) {
				puyo_temp[(y + 1) * GetColumn() + x] = GetValue(y, x);

				SetValue(y, x, puyodata());
			}
			else {
				puyo_temp[y * GetColumn() + x] = GetValue(y, x);
			}
		}
	}

	for (int y = 0; y < GetLine(); y++) {
		for (int x = 0; x < GetColumn(); x++) {
			SetValue(y, x, puyo_temp[y * GetColumn() + x]);
		}
	}

	delete[] puyo_temp;
}