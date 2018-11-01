#pragma once
#include "./Render/Sprite.h"
#include "./Object/Rect.h"
//이미지 + 충돌 + 이동
class Bullet
{
protected:
	float angle;
	float speed;
	float distance;

	D3DXVECTOR2 direction;
	D3DXVECTOR2 position;
	D3DXVECTOR2 startPosition;

	Sprite* sprite;
	Rect* rect;

	bool bFire;
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	virtual void Fire(D3DXVECTOR2 startPosition, D3DXVECTOR2 direction, float angle, float distance = 1000.0f, float speed = 1.0f);
	virtual void MoveBullet();

	bool IsFire() { return bFire; }
	void SetFire(bool _bFire) { bFire = _bFire; }

	Rect* GetRect() { return rect; }
};

///////////////////////////////////////////////////////////////////////////////////////////
class Bomb : public Bullet
{
public:
	Bomb();
	~Bomb();
	virtual void Fire(
		D3DXVECTOR2 startPosition,
		D3DXVECTOR2 direction,
		float angle, float distance = 1000.0f, float speed = 1.0f);
};