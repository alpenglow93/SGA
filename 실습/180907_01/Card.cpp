#include "Card.h"



Card::Card()
{
}

Card::Card(int data)
	:data(data), isShow(false)
{
	this->data = data;
	//this->isShow = false;
}


Card::~Card()
{
}

bool Card::IsCheck(Card * card)
{
	if (this->data == card->data)
	{
		return true;
	}
	else
	{
		this->ChangeShow();
		card->ChangeShow();
		return false;
	}
}

void Card::Render(int index)
{
	cout << "[";
	if (this->isShow)
	{
		cout << " " << (char)data;
	}
	else
	{
		if (index < 10) cout << " ";
		cout << index;
	}
	cout << "]";
}
