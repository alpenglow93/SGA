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

	void Init(); //�ʱ�ȭ
	void Release(); // ���� 
	void Update(); //Ű�Է� , ���, ���콺 

	void PreRender(); //RTT 
	void Render(); //��� 
	void PostRender(); //DriectWirte

	void MainMenuBarSetting();
	void ShowInsfacter();
};

