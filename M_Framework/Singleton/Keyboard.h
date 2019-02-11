#pragma once
#include "./SingletonBase.h"
#include <bitset> //��Ʈ ���� ����(0,1)

#define KEYMAX 256
class Keyboard : public SingletonBase<Keyboard>
{
private:
	bitset<KEYMAX> up;
	bitset<KEYMAX> down;

public:
	Keyboard();
	~Keyboard();

	//�������� 1�� 
	bool GetKeyDown(int key);
	//������ ������ 
	bool GetKey(int key);
	//������ �ִٰ� ������ 
	bool GetKeyUp(int key);
	//caps Lock or numLock or scroll Lock 
	bool GetToggleKey(int key);
};

#define Input Keyboard::Get()

