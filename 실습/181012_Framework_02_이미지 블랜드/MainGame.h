#pragma once
#include "./Object/Circle.h"
#include "./Object/Rect.h"
#include "./Render/Sprite.h"

class MainGame
{
private:
	Sprite * mario;
	Sprite* level[4];
	D3DXVECTOR2 position[4];
public:
	MainGame();
	~MainGame();

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력
};

