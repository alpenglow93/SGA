#pragma once
#include "./Scene/Scene.h"
//Scene -> 
class MainGame
{
private:
	bool bMainWindow;
public:
	MainGame();
	~MainGame();

	void Init(); //초기화
	void Release(); // 삭제 
	void Update(); //키입력 , 계산, 마우스 

	void PreRender(); //RTT 
	void Render(); //출력 
	void PostRender(); //DriectWirte

	void MainMenuBarSetting();
	void ShowInsfacter();
};

