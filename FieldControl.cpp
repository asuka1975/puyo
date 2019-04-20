#include<stdio.h>
#include<cstdlib>
#include<ctime>
#include"Field.hpp"
#include"FieldControl.hpp"

FieldControl::FieldControl() : Field() {
	puyorotate = 0;
}

void FieldControl::GeneratePuyo() {
	puyorotate = 0;
	srand(static_cast<unsigned>(time(NULL)));
	puyodata newpuyo1(static_cast<puyocolor>(rand() % 4 + 1));
	puyodata newpuyo2(static_cast<puyocolor>(rand() % 4 + 1));

	SetValue(0, 5, newpuyo1);
	SetValue(0, 6, newpuyo2);
}

bool FieldControl::LandingPuyo() {
	bool landed = true;

	for (int y = GetLine() - 1; y >= 0; y--) {
		for (int x = 0; x < GetColumn(); x++) {
			if (GetValue(y, x).color != NONE && y < GetLine() - 1) {
				if (GetValue(y + 1, x).color == NONE) {
					landed = false;
					continue;
				}
				else if (GetValue(y, x).handling && !GetValue(y + 1, x).handling) {
					puyodata puyo = GetValue(y, x);
					puyo.handling = false;
					SetValue(y, x, puyo);
					puyodata right = GetValue(y + puyorotate % 2, x + !(puyorotate % 2));
					right.handling = false;
					SetValue(y + puyorotate % 2, x + !(puyorotate % 2), right);
					puyodata left = GetValue(y - puyorotate % 2, x - !(puyorotate % 2));
					left.handling = false;
					SetValue(y - puyorotate % 2, x - !(puyorotate % 2), left);
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

void FieldControl::VanishPuyo() {
	for (int y = 0; y < GetLine(); y++) {
		for (int x = 0; x < GetColumn(); x++) {
			VanishPuyo(y, x);
		}
	}
}

void FieldControl::VanishPuyo(unsigned int y, unsigned int x) {
	if (GetValue(y, x).color == NONE) return;

	bool* check_field = new bool[GetColumn() * GetLine()];
	for (int i = 0; i < GetColumn() * GetLine(); i++) check_field[i] = false;
	if (VanishPuyo_r(y, x, check_field) >= 4) {
		for (int y = 0; y < GetLine(); y++) {
			for (int x = 0; x < GetColumn(); x++) {
				SetValue(y, x, check_field[y * GetColumn() + x] ? puyodata() : GetValue(y, x));
			}
		}
	}
	delete[] check_field;
}

void FieldControl::RotatePuyo(int rot_dire) {
	for (int y = puyorotate == 3 ? GetLine() - 1 : 0; puyorotate == 3 ? y >= 0 : y < GetLine(); puyorotate == 3 ? y-- : y++) {
		for (int x = puyorotate == 2 ? GetColumn() - 1 : 0; puyorotate == 2 ? x >= 0 : x < GetColumn(); puyorotate == 2 ? x-- : x++) {
			if (GetValue(y, x).handling) {
				int old_x = x + ((puyorotate & 0b10) ? -1 : 1) * !(puyorotate & 0b01);
				int old_y = y + ((puyorotate & 0b10) ? -1 : 1) * (puyorotate & 0b01);
				int new_x = x + (((puyorotate + rot_dire) & 0b10) ? -1 : 1) * !((puyorotate + rot_dire) & 0b01);
				int new_y = y + (((puyorotate + rot_dire) & 0b10) ? -1 : 1) * ((puyorotate + rot_dire) & 0b01);
				if ((0 <= new_x && new_x < GetColumn()) && (0 <= new_y && new_y < GetLine()) && GetValue(new_y, new_x).color == NONE) {
					puyodata puyo = GetValue(old_y, old_x);
					SetValue(old_y, old_x, puyodata());
					SetValue(new_y, new_x, puyo);
					puyorotate = (puyorotate + rot_dire) % 4 < 0 ? (puyorotate + rot_dire) % 4 + 4 : (puyorotate + rot_dire) % 4;
				}

				goto ROTATE_END;
			}
		}
	}
ROTATE_END:;
}

int FieldControl::VanishPuyo_r(unsigned int y, unsigned int x, bool* check_field) {
	int vanish_num = 1;
	check_field[y * GetColumn() + x] = true;
	if (x > 0) {
		vanish_num += !check_field[y * GetColumn() + (x - 1)] && (GetValue(y, x).color == GetValue(y, x - 1).color) ? VanishPuyo_r(y, x - 1, check_field) : 0;
	}
	if (x < GetColumn() - 1) {
		vanish_num += !check_field[y * GetColumn() + (x + 1)] && (GetValue(y, x).color == GetValue(y, x + 1).color) ? VanishPuyo_r(y, x + 1, check_field) : 0;
	}
	if (y > 0) {
		vanish_num += !check_field[(y - 1) * GetColumn() + x] && (GetValue(y, x).color == GetValue(y - 1, x).color) ? VanishPuyo_r(y - 1, x, check_field) : 0;
	}
	if(y < GetLine() - 1){
		vanish_num += !check_field[(y + 1) * GetColumn() + x] && (GetValue(y, x).color == GetValue(y + 1, x).color) ? VanishPuyo_r(y + 1, x, check_field) : 0;
	}
	return vanish_num;
}