#include"Field.hpp"

#ifndef NULL
#define NULL 0
#endif

PuyoArray::PuyoArray() {
	data = NULL;
	data_line = 0;
	data_column = 0;
}

PuyoArray::~PuyoArray() {
	delete[] data;
}

void PuyoArray::ChangeSize(unsigned int line, unsigned int column) {
	Release();

	data = new puyocolor[line * column];
	data_line = line;
	data_column = column;
	for (int i = 0; i < line * column; i++) data[i] = NONE;
}

unsigned int PuyoArray::GetLine() {
	return data_line;
}

unsigned int PuyoArray::GetColumn() {
	return data_column;
}

puyocolor PuyoArray::GetValue(unsigned int y, unsigned int x) {
	if (y >= GetLine() || x >= GetColumn()) return NONE;

	return data[y * GetColumn() + x];
}

void PuyoArray::SetValue(unsigned int y, unsigned int x, puyocolor value) {
	if (y >= GetLine() || x >= GetColumn()) return;

	data[y * GetColumn() + x] = value;
}

void PuyoArray::Release() {
	if (!data) return;

	delete[] data;
	data = NULL;
}