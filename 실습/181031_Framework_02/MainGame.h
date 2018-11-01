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

	void Init();	//초기화
	void Release();	//삭제
	void Update();	//키입력, 계산, 마우스
	void Render();	//출력
};

