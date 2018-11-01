#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
	:angle(0.0f)
	, speed(1.0f)
	, distance(1000.0f)
	, direction(0.0f, 1.0f)
	, position(0.0f, 0.0f)
	, startPosition(0.0f, 0.0f)
	, sprite(NULL)
	, rect(NULL)
	, bFire(false)
{
}


Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(rect);
}

void Bullet::Update()
{
	MoveBullet();
}

void Bullet::Render()
{
	if (!bFire) return;
	sprite->Render();
}

void Bullet::Fire(D3DXVECTOR2 startPosition, D3DXVECTOR2 direction, float angle, float distance, float speed)
{
	if (sprite == NULL)
	{
		sprite = new Sprite(L"Empty.png");
		sprite->Scale(10.0f, 10.0f);
		rect = new Rect;
		rect->Scale(10.0f, 10.0f);
	}

	rect->Position(startPosition);
	rect->Update();

	this->startPosition = position = startPosition;
	this->direction = direction;
	this->angle = angle;
	this->distance = distance;
	this->speed = speed;
	this->bFire = true;
}

void Bullet::MoveBullet()
{
	if (!bFire) return;

	if (D3DXVec2Length(&(startPosition - position)) > distance) bFire = false;

	position += direction * speed;

	rect->Position(position);
	rect->Update();

	sprite->Rotation(angle);
	sprite->Position(position);
	sprite->Update();

}

////////////////////////////////////////////////////////////////
Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Fire(D3DXVECTOR2 startPosition, D3DXVECTOR2 direction, float angle, float distance, float speed)
{
	if (sprite == NULL)
	{
		sprite = new Sprite(L"Empty.png");
		sprite->Scale(30.0f, 30.0f);
		rect = new Rect;
		rect->Scale(30.0f, 30.0f);
	}

	rect->Position(startPosition);
	rect->Update();

	this->startPosition = position = startPosition;
	this->direction = direction;
	this->angle = angle;
	this->distance = distance;
	this->speed = speed;
	this->bFire = true;
}
