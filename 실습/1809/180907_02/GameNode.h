#pragma once
#include <iostream>
using namespace std;

class GameNode	//추상 클래스 (가상함수 클래스)
{
public:
	GameNode();
	~GameNode();

	//가상함수: 
	virtual void Function()
	{
		cout << "GameNode Function" << endl;
	}
	void Function2()
	{
		cout << "GameNode Function" << endl;
	}

	//순수 가상함수: 함수 선언만 있고 정의가 없는 함수
	//내용은 자식 클래스에서 무조건 작성 해야한다
	virtual void Function3() = 0;

	//interface 순수 가상함수로만 이루어진 클래스, 구조체
};

