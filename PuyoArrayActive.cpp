#include "PuyoArrayActive.hpp"

PuyoArrayActive::PuyoArrayActive() : puyorotate(0) { }

int PuyoArrayActive::GetRotation()
{
	return puyorotate;
}

void PuyoArrayActive::RotatePuyo(int direction)
{
	if (-2 < direction && direction < 2) {
		puyorotate += direction;
		if (puyorotate < 0) puyorotate += 4;
		else puyorotate %= 4;
	}
}

void PuyoArrayActive::ResetRotation()
{
	puyorotate = 0;
}
