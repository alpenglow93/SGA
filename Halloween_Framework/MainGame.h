#pragma once
#include "./Scene/Scene.h"
#include "./Animation/Animation.h"
//Scene -> 
class MainGame
{
private:
public:
	MainGame();
	~MainGame();

	void Init(); //초기화
	void Release(); // 삭제 
	void Update(); //키입력 , 계산, 마우스 

	void PreRender(); //RTT 
	void Render(); //출력 
	void PostRender(); //DriectWirte
};

