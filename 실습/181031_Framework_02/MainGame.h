#pragma once
#include "./PlaneGame/PlaneMainGame.h"

//Scene -> 
class MainGame
{
private:
	PlaneMainGame * Scene;
public:
	MainGame();
	~MainGame();

	void Init();	//�ʱ�ȭ
	void Release();	//����
	void Update();	//Ű�Է�, ���, ���콺
	void Render();	//���
};

