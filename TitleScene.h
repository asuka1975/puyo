#pragma once

class TitleScene : public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	int Update() override;
private:
	void Display();
	int menu;
};

