#pragma once
#include <iostream>
using namespace std;
class Card
{
private:
	int data;
	bool isShow;
public:
	Card();
	Card(int data);
	~Card();

	bool IsCheck(Card* card); //ī�尡 ���� Ʋ����?
	void Render(int index); //��¿�
	void ChangeShow() { isShow = !isShow; }
	bool GetBool() { return isShow; }
};

