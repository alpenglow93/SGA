#pragma once
#include "./SingletonBase.h"
#include <bitset> //비트 단위 변수(0,1)

#define KEYMAX 256
class Keyboard : public SingletonBase<Keyboard>
{
private:
	bitset<KEYMAX> up;
	bitset<KEYMAX> down;

public:
	Keyboard();
	~Keyboard();

	//눌렀을때 1번 
	bool GetKeyDown(int key);
	//누르고 있을때 
	bool GetKey(int key);
	//누르고 있다가 땠을때 
	bool GetKeyUp(int key);
	//caps Lock or numLock or scroll Lock 
	bool GetToggleKey(int key);
};

#define Input Keyboard::Get()

