#ifndef _FIELDCONTROL_HPP
#define _FIELDCONTROL_HPP

class FieldControl : public Field {
public:
	FieldControl();
	void GeneratePuyo();
	bool LandingPuyo();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
};

#endif