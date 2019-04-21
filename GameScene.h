#pragma once

class GameScene : public BaseScene
{
public:
	GameScene();
	~GameScene();
	int Update() override;
private:
	int delay;
	int waitCount;
	FieldControl field;
	void Display();
};

