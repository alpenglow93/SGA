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

	void Init(); //�ʱ�ȭ
	void Release(); // ���� 
	void Update(); //Ű�Է� , ���, ���콺 

	void PreRender(); //RTT 
	void Render(); //��� 
	void PostRender(); //DriectWirte
};

