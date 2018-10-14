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

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력
};

