#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

enum MARK
{
	STAR = 0,
	HEART,
	DIAMOND,
	SPADE,
	CLOVER,
	SQUARE,
	CIRCLE,
	TRIANGLE
};

class CardTable
{
public:
	int m_card_table[16];

	void SaveShuffle();
	void NumgPrint();
	void WordPrint();

	CardTable();
	~CardTable();
};
