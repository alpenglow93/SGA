#include <iostream>
#include "MainGame.h"
using namespace std;

//STL 
//게임엔진 ->

void Print(float f);
void Print(int i);
void print(const char* str);

template <typename T>
void Show(T t)
{
	cout << t << endl;
}

void main()
{
	//Show(10);
	//Show(102.5f);
	//Show('b');
	//Show("String");
	MainGame<int> vInt(10);
}