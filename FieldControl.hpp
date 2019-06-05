#ifndef _FIELDCONTROL_HPP
#define _FIELDCONTROL_HPP

#include "PuyoArrayStack.hpp"
#include "PuyoArrayActive.hpp"

class PuyoControl {
public:
	PuyoControl(unsigned int line, unsigned int column);
	void GeneratePuyo(PuyoArrayActive& field);
	bool LandingPuyo(PuyoArrayActive& field);
	void MoveLeft(PuyoArrayActive& field);
	void MoveRight(PuyoArrayActive& field);
	void MoveDown(PuyoArrayActive& field);
	puyocolor GetStack(unsigned int y, unsigned int x);
	int VanishPuyo();
	int VanishPuyo(unsigned int y, unsigned int x);
	void Rotate(PuyoArrayActive& puyoactive, int rot_dire);

	void TestCaseStackField();
	void TestGeneratePuyo();
private:
	PuyoArrayStack stackArray;
	void StackingActivePuyo(PuyoArrayActive& field);
	void StackUpdate();
	bool StackLanded();
	void CheckVanishingPuyo(bool* check_field, unsigned int y, unsigned int x);
};

#endif