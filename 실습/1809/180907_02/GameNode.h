#pragma once
#include <iostream>
using namespace std;

class GameNode	//�߻� Ŭ���� (�����Լ� Ŭ����)
{
public:
	GameNode();
	~GameNode();

	//�����Լ�: 
	virtual void Function()
	{
		cout << "GameNode Function" << endl;
	}
	void Function2()
	{
		cout << "GameNode Function" << endl;
	}

	//���� �����Լ�: �Լ� ���� �ְ� ���ǰ� ���� �Լ�
	//������ �ڽ� Ŭ�������� ������ �ۼ� �ؾ��Ѵ�
	virtual void Function3() = 0;

	//interface ���� �����Լ��θ� �̷���� Ŭ����, ����ü
};

