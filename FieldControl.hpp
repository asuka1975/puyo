#ifndef _FIELDCONTROL_HPP
#define _FIELDCONTROL_HPP

class FieldControl {
public:
	void GeneratePuyo(FieldArray& field);
	bool LandingPuyo(FieldArray& field);
	void MoveLeft(FieldArray& field);
	void MoveRight(FieldArray& field);
	void MoveDown(FieldArray& field);
};

#endif