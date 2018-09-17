#pragma once
#include "Card.h"
#include <string>
#include <vector>
class Player
{
private:
	vector<Card> card;
	int money;
	bool bCheck;
	string name;
public:
	Player();
	Player(string name);
	~Player();

	int sumAllCard();
	void PushCard(Card card) { this->card.push_back(card); }
	int CardCount() { return card.size(); }
	bool GetBool() { return bCheck; }
	void SetBool(bool bCheck) { this->bCheck = bCheck; }
	void SetMoney(int temp) { this->money += temp; }
	void SetClear() { this->card.clear(); }
	void Render();
};

