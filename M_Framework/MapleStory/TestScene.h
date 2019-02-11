#pragma once
#include "./Scene/Scene.h"
#include "Player.h"
class TestScene : public Scene
{
private:
	Player* player;

public:
	TestScene();
	~TestScene();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;
};

