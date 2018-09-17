#pragma once
#include "Player.h"
class MainGame
{
private:
	Player com;
	Player my;
	Card card[52];
public:
	MainGame();
	~MainGame();

	void Init();
	void Update();
	void Render();
	void Shuffle();
};

