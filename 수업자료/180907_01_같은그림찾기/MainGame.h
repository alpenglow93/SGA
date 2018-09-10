#pragma once
#include <time.h>
#include <Windows.h>

#include "Card.h"

class MainGame
{
private:
	Card cards[16];
	int select;
	int saveCard[2];

public:
	MainGame();
	~MainGame();

	void Init(); //초기화 
	void Release(); //삭제 포인터 해제 
	void Update(); //키, 마우스 , 계산 
	void Render(); //출력용 

	void Shuffle(Card* card);
};

