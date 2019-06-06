#include <cstdlib>
#include <ctime>

#include "Field.hpp"
#include "PuyoGenerator.hpp"

class Initializer {
public:
	Initializer() {
		PuyoGenerator::Initialize();
	}
};
Initializer initializer;

puyocolor* PuyoGenerator::next1 = NULL;
puyocolor* PuyoGenerator::next2 = NULL;

void PuyoGenerator::Initialize()
{
	Dispose();

	srand(static_cast<unsigned>(time(NULL)));

	next1 = new puyocolor[2];
	next2 = new puyocolor[2];

	for (int i = 0; i < 2; i++) next1[i] = static_cast<puyocolor>(rand() % 4 + 1);
	for (int i = 0; i < 2; i++) next2[i] = static_cast<puyocolor>(rand() % 4 + 1);
}

void PuyoGenerator::GetNext(int idx, puyocolor & puyo1, puyocolor & puyo2)
{
	switch (idx) {
	case 0:
		puyo1 = next1[0];
		puyo2 = next1[1];
		break;
	case 1:
		puyo1 = next2[0];
		puyo2 = next2[1];
		break;
	default:
		break;
	}
}

puyocolor PuyoGenerator::Generate()
{
	puyocolor puyo = next1[0];
	next1[0] = next1[1];
	next1[1] = next2[0];
	next2[0] = next2[1];
	next2[1] = static_cast<puyocolor>(rand() % 4 + 1);
	return puyo;
}

PuyoGenerator::~PuyoGenerator()
{
	Dispose();
}

void PuyoGenerator::Dispose()
{
	if (!next1) {
		delete[] next1;
		next1 = NULL;
	}
	if (!next2) {
		delete[] next2;
		next2 = NULL;
	}
}
