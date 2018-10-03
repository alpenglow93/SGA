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

	bool IsCheck(Card* card);	//카드가 같은지 틀린지
	void Render(int index);	//출력용
	void ChangeShow() {isShow = !isShow; }
	bool GetBool() { return isShow; }
};

