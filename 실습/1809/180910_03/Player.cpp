#include "Player.h"

Player::Player()
{
	
}

Player::Player(string name)
	:name(name)
{
	money = 10000;
	bCheck = false;

}


Player::~Player()
{
}

int Player::sumAllCard()
{
	int total = 0;
	for (Card i : card)
	{
		int num = (i.GetData() % 13) + 1;
		if (num < 10)
			total += num;
		else
			total += 10;

	}
	return total;
}

void Player::Render()
{
	cout << name << "\t";
	for (Card i : card)
	{
		i.Print();
	}
	cout << endl;
}
