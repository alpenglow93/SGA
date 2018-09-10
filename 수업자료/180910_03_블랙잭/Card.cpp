#include "Card.h"

Card::Card(int data)
	: data(data)
{
}

Card::~Card()
{
}

void Card::Print()
{
	int number = (data % 13) + 1;
	cout << number << "\t";
}
