#pragma once
#include "./Singleton/SingletonBase.h"
#include <bitset>	//��Ʈ ���� ����

#define KEYMAX 256
class Keyborad : public SingletonBase<Keyborad>
{
private:
	bitset<KEYMAX> up;
	bitset<KEYMAX> down;
public:
	Keyborad();
	~Keyborad();

	//�������� �ѹ�
	bool GetKeyDown(int key);
	//������ ������
	bool GetKey(int key);
	//������ ����
	bool GetKeyUp(int key);
	//caps Lock or numLock or scroll Lock
	bool GetToggleKey(int key);
};

#define Input Keyborad::Get()