#ifndef _FIELD_HPP
#define _FIELD_HPP

enum puyocolor{ NONE, RED, BLUE, GREEN, YELLOW };

struct puyodata {
	puyocolor color;
	bool handling;
	puyodata();
	puyodata(puyocolor color);
};

class Field {
public:
	Field();
	~Field();
	void ChangeSize(unsigned int line, unsigned int column);
	unsigned int GetLine();
	unsigned int GetColumn();
	puyodata GetValue(unsigned int y, unsigned int x);
	void SetValue(unsigned int y, unsigned int x, puyodata value);
private:
	puyodata * data;
	unsigned int data_line;
	unsigned int data_column;
	void Release();
};

#endif