#ifndef _FIELD_HPP
#define _FIELD_HPP

enum puyocolor{ NONE, RED, BLUE, GREEN, YELLOW };

class PuyoArray {
public:
	PuyoArray();
	~PuyoArray();
	void ChangeSize(unsigned int line, unsigned int column);
	unsigned int GetLine();
	unsigned int GetColumn();
	puyocolor GetValue(unsigned int y, unsigned int x);
	void SetValue(unsigned int y, unsigned int x, puyocolor value);
private:
	puyocolor * data;
	unsigned int data_line;
	unsigned int data_column;
	void Release();
};

#endif