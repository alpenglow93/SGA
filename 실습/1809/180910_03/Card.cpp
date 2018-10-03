#include "Card.h"


Card::Card()
{

}


Card::Card(int data)
	:data(data)	//ÃÊ±âÈ­
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
