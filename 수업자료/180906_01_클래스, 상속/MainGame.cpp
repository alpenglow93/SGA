#include "MainGame.h"

//.cpp (�ҽ� ����) : ����� ����� �������(����) ��
//�Լ��� ����(�����ۼ�)

MainGame::MainGame()
{
	data = 0;
	distance = 1.2f;
	nInt = 20;
	cout << data << " ������ ȣ��" << endl;
	pInt = new int(10);
}

MainGame::~MainGame()
{
	delete pInt;
	cout << distance << "�Ҹ��� ȣ��" << endl;
}

void MainGame::SetDistance(float f)
{
	distance = f;
}

float MainGame::GetDistance()
{
	return distance;
}

void MainGame::SetDamage(MainGame * target)
{
	target->hp -= att;
}
