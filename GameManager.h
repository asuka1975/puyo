#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();
	void Run();
private:
	BaseScene * scene;
	void TransGame();
};

