#pragma once
#include "Space.h"
#include "AirPlane.h"
#include "PlaneEnemyManager.h"
#include "MiniMap.h"

class PlaneMainGame
{
private:
	Space * background;
	AirPlane * player;
	PlaneEnemyManager* enemy;
	MiniMap* miniMap;
public:
	PlaneMainGame();
	~PlaneMainGame();

	void Init();
	void Release();
	void Update();
	void Render();
};

