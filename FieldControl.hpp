#ifndef _FIELDCONTROL_HPP
#define _FIELDCONTROL_HPP

#define RIGHT_ROTATE	 1
#define LEFT_ROTATE		-1

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
	void RotatePuyo(int rotate_direction);
	int GetScore();
private:
	int score;
	int chain;
	int color_num;
	int vanish_num;
	int puyorotate;
	int VanishPuyo_r(unsigned int y, unsigned int x, bool* check_field);
};

#endif