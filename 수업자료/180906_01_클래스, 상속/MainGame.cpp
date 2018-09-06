#include "MainGame.h"

//.cpp (소스 파일) : 헤더에 선언된 변수사용(대입) 및
//함수의 정의(내용작성)

MainGame::MainGame()
{
	data = 0;
	distance = 1.2f;
	nInt = 20;
	cout << data << " 생성자 호출" << endl;
	pInt = new int(10);
}

MainGame::~MainGame()
{
	delete pInt;
	cout << distance << "소멸자 호출" << endl;
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
