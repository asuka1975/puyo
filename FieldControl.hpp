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
	void VanishPuyo();
	void VanishPuyo(unsigned int y, unsigned int x);
	void RotatePuyo();
private:
	int puyorotate;
	int VanishPuyo_r(unsigned int y, unsigned int x, bool* check_field);
};

#endif