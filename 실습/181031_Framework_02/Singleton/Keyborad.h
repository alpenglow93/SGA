#pragma once
#include "./Singleton/SingletonBase.h"
#include <bitset>	//비트 단위 변수

#define KEYMAX 256
class Keyborad : public SingletonBase<Keyborad>
{
private:
	bitset<KEYMAX> up;
	bitset<KEYMAX> down;
public:
	Keyborad();
	~Keyborad();

	//눌렀을때 한번
	bool GetKeyDown(int key);
	//누르고 있을때
	bool GetKey(int key);
	//눌렀다 뗄때
	bool GetKeyUp(int key);
	//caps Lock or numLock or scroll Lock
	bool GetToggleKey(int key);
};

#define Input Keyborad::Get()