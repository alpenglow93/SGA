#pragma once
#include "Space.h"
#include "AirPlane.h"
#include "PlaneEnemyManager.h"
#include "MiniMap.h"
#include "./Scene/Scene.h"
#include "./Object/Transform.h"
class PlaneMainGame : public Scene
{
private:
	Space * background;

	vector<AirPlane*> select;
	bool bSelect;
	bool bHovering;
	int index = -1;

	AirPlane * player;
	PlaneEnemyManager* enemy;
	MiniMap* miniMap;

	Sprite* cursorImage;

	Sprite* image;

	Transform* transform;
	Transform* pChild[99];
public:
	PlaneMainGame();
	~PlaneMainGame();

	void Init();
	void Release();
	void Update();
	void Render();

	void ShowInfo();
};

