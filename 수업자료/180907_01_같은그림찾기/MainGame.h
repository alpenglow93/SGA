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

	void Init(); //�ʱ�ȭ 
	void Release(); //���� ������ ���� 
	void Update(); //Ű, ���콺 , ��� 
	void Render(); //��¿� 

	void Shuffle(Card* card);
};

