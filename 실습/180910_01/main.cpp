#include <iostream>
#include "MainGame.h"
using namespace std;

//STL: standard template libary

void Print(float f);
void Print(int i);
void Print(const char* str);
//출력 함수를 이렇게 많이 만드는것은 힘들다

//템플릿으로 어떤 타입이 들어가든지간에 t라는 것을 출력하겠다
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