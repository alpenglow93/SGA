#pragma once
#include "./PlaneGame/AirPlane.h"
#include "./PlaneGame/PlaneEnemyManager.h"
#include "./Render/Sprite.h"
class MiniMap
{
private:
	Sprite * sprite;	//��� �̹���
	AirPlane* player;	//�÷��̾� ��ġ
	PlaneEnemyManager* enemys;	//���ʹ� ��ġ

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

