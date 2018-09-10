#pragma once

namespace Test
{
	int a, b, c;
};

template <typename T>
class MainGame
{
private:
	//Test::a = 10;
	T data;
public:
	MainGame(T data);
	~MainGame();

	void Print();
};

