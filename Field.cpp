#include"Field.hpp"

#define NULL 0

puyodata::puyodata() {
	color = NONE;
	handling = false;
}

puyodata::puyodata(puyocolor color) {
	this->color = color;
	handling = true;
}

Field::Field() {
	data = NULL;
	data_line = 0;
	data_column = 0;
}

Field::~Field() {
	delete[] data;
}

void Field::ChangeSize(unsigned int line, unsigned int column) {
	Release();

	data = new puyodata[line * column];
	data_line = line;
	data_column = column;
	for (int i = 0; i < line * column; i++) data[i] = puyodata();
}

unsigned int Field::GetLine() {
	return data_line;
}

unsigned int Field::GetColumn() {
	return data_column;
}

puyodata Field::GetValue(unsigned int y, unsigned int x) {
	if (y >= GetLine() || x >= GetColumn()) return NONE;

	return data[y * GetColumn() + x];
}

void Field::SetValue(unsigned int y, unsigned int x, puyodata value) {
	if (y >= GetLine() || x >= GetColumn()) return;

	data[y * GetColumn() + x] = value;
}

void Field::Release() {
	if (!data) return;

	delete[] data;
	data = NULL;
}