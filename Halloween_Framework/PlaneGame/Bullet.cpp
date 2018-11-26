#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
	: angle(0.0f)
	, speed(1.0f)
	, distance(1000.0f)
	, direction(0.0f, 1.0f)
	, position(0.0f, 0.0f)
	, startPosition(0.0f, 0.0f)
	, rect(NULL)
	, bFire(false)
	, clip(NULL)
{
}


Bullet::~Bullet()
{
	SAFE_DELETE(clip);
	SAFE_DELETE(rect);
}

void Bullet::Update()
{
	MoveBullet();
}

void Bullet::Render()
{
	if (!bFire) return;
	clip->Render();
	rect->GizmoRender();
}

void Bullet::Fire(D3DXVECTOR2 startPosition, D3DXVECTOR2 direction, float angle, float distance, float speed)
{
	if (clip == NULL)
	{
		clip = new Clip(PlayMode::Reverse);
		for (int i = 0; i < 7; i++)
		{
			int x = (float)i * 15 + 173;
			Sprite* sprite = new Sprite(L"Bullets.png", x, 155, x + 11,167);
			//sprite->Scale(10.0f + 10.0f * i,10.0f + 10.f *i);

			clip->AddFrame(sprite, 0.3f);
		}

		rect = new Rect;
		rect->Scale(10.0f, 10.0f);
	}

	//clip->Play();
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

	position += direction * speed * Time->Elapsed();

	rect->Position(position);
	rect->Rotation(angle);
	rect->Update();
	 
	clip->Position(position);
	clip->Rotation(angle);
	clip->Update();
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
	if (clip == 0)
	{
		clip->AddFrame(new Sprite(L"Empty.png"),0.3f);
		clip->Scale(30.0f, 30.0f);
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
