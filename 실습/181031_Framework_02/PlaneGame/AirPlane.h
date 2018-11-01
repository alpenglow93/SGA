#pragma once
//플레이어
//이미지 + 충돌체 + 이동
#include "./Render/Sprite.h"	//이미지
#include "./Object/Rect.h"	//충돌용
#include "Bullet.h"

//정방선언
//class BaseEnemy;
#define BULLETMAX 10
//총알(bullet)
class AirPlane
{
private:
	Bullet * bullet[BULLETMAX];
	Bomb* bomb;
private:
	Sprite * sprite;
	Rect* rect;

	D3DXVECTOR2 position;	//현 위치
	D3DXVECTOR2 direction;	//이동할 방향
	float speed;	//이동속도

	float angle;	//회전 (이미지 + 방향)

	float hp;
	class PrograssBar* hpBar;
	class PlaneEnemyManager* enemys;	//전방 선언 + 변수 선언
public:
	AirPlane();
	~AirPlane();

	void Update();
	void Render();

	virtual void Move();
	virtual void Attack();

	void Position(D3DXVECTOR2* position);
	void SetLink(class PlaneEnemyManager* link) { enemys = link; }

	Rect* GetRect() { return rect; }
	float GetHp() { return hp; }
	void SetHp(float _hp) { hp = _hp; }
};

