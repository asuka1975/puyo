#ifndef _PUYOACTIVE_HPP
#define _PUYOACTIVE_HPP

#include "Field.hpp"
class PuyoArrayActive :
	public PuyoArray
{
public:
	PuyoArrayActive();
	int GetRotation();
	void RotatePuyo(int direction);
	void ResetRotation();
private:
	int puyorotate;
};

#endif

