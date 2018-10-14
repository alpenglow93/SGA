#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"
#include "./Render/Sprite.h"

class MainGame
{
private:
	Sprite * mario;
	
public:
	MainGame();
	~MainGame();

	void Init();	//�ʱ�ȭ
	void Release();	//����
	void Update();	//Ű�Է�, ���, ���콺
	void Render();	//���
};

