#include"Field.hpp"

#define NULL 0

FieldArray::FieldArray() {
	data = NULL;
	data_line = 0;
	data_column = 0;
}

FieldArray::~FieldArray() {
	delete[] data;
}

void FieldArray::ChangeSize(unsigned int line, unsigned int column) {
	Release();

	data = new puyocolor[line * column];
	data_line = line;
	data_column = column;
	for (int i = 0; i < line * column; i++) data[i] = NONE;
}

unsigned int FieldArray::GetLine() {
	return data_line;
}

unsigned int FieldArray::GetColumn() {
	return data_column;
}

puyocolor FieldArray::GetValue(unsigned int y, unsigned int x) {
	if (y >= GetLine() || x >= GetColumn()) return NONE;

	return data[y * GetColumn() + x];
}

void FieldArray::SetValue(unsigned int y, unsigned int x, puyocolor value) {
	if (y >= GetLine() || x >= GetColumn()) return;

	data[y * GetColumn() + x] = value;
}

void FieldArray::Release() {
	if (!data) return;

	delete[] data;
	data = NULL;
}