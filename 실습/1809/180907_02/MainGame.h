#pragma once
#include "GameNode.h"
class MainGame : public GameNode
{
public:
	MainGame();
	~MainGame();

	//overloading: ������ �Լ����� ���ڰ��� �ٸ��� �ۼ��Ͽ� �ٸ� �Լ��� ����°�
	//overrideing: ��Ӱ��迡�� �θ𿡼� virtual�� ����� �Լ��� ������ �����
	//�ٽ� �ۼ�(������) �ϴ� ���� ����
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

