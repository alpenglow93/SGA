#pragma once
#include "GameNode.h"
class MainGame : public GameNode
{
public:
	MainGame();
	~MainGame();

	//overloading: 동일한 함수명에서 인자값을 다르게 작성하여 다른 함수로 만드는것
	//overrideing: 상속관계에서 부모에서 virtual로 선언된 함수의 내용을 지우고
	//다시 작성(재정의) 하는 것을 말함
	void Function() override
	{
		cout << "MainGame Function" << endl;
	}
	void Function2()
	{
		cout << "MainGame Function" << endl;
	}
	void Function3() override
	{

	}
};

