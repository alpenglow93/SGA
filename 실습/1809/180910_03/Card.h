#pragma once
#include <iostream>
using namespace std;

class Card
{
private:
	int data;
public:
	Card();
	Card(int data);
	~Card();

	void Print();	//���
	int GetData() {	return data; }
};

