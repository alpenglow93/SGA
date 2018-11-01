#include "stdafx.h"
#include "Keyborad.h"


Keyborad::Keyborad()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		up.set(i, false);
		down.set(i, false);
	}
}


Keyborad::~Keyborad()
{
}

bool Keyborad::GetKeyDown(int key)
{
	//GetKeyState(): 동기, GetAsynKeyState(): 비동기

	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!down[key])
		{
			down.set(key, true);
			return true;
		}
	}
	else
	{
		down.set(key, false);
	}
	return false;
}

bool Keyborad::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bool Keyborad::GetKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		up.set(key, true);
	}
	else
	{
		if (up[key])
		{
			up.set(key, false);
			return true;
		}
	}
	return false;
}

bool Keyborad::GetToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
		return true;
	return false;
}
