#pragma once
#include "./PlaneGame/AirPlane.h"
#include "./PlaneGame/PlaneEnemyManager.h"
#include "./Render/Sprite.h"
class MiniMap
{
private:
	Sprite * sprite;	//배경 이미지
	AirPlane* player;	//플레이어 위치
	PlaneEnemyManager* enemys;	//에너미 위치

	Sprite* miniPlayer;
	Sprite* miniEnemy;
	Sprite* miniBoss;

public:
	MiniMap();
	~MiniMap();

	void Update();
	void Render();

	void SetLink(AirPlane* link1, PlaneEnemyManager* link2);
};

