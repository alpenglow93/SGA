#include "stdafx.h"
#include "PlaneGameEnemy.h"
int BossEnemy::deathCount = 0;

BaseEnemy::BaseEnemy(AirPlane* link)
	: position(desc.Width - 100.0f, desc.Height - 100.0f)
	, rectPosition(0, 0)
	, speed(1.0f)
	, direction(0.0f, 1.0f)
	, state(STATE::Idle)
	, hp(100.0f)
	, plane(link)
	, delayTime(500)
	, angle(0.0f)
{
	sprite = new Sprite(L"AirplaneEnemy.png");
	sprite->Scale(50, 100);
	sprite->Position(position);

	rect = new Rect;
	rect->Scale(50, 100);
	rect->Position(position);

	hpBar = new PrograssBar(L"progressBarFront.bmp",
		L"progressBarBack.bmp", hp);
	hpBar->Scale(80, 10);

	bFire = false;
}


BaseEnemy::~BaseEnemy()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(rect);
	SAFE_DELETE(hpBar);
}

void BaseEnemy::Update()
{
	D3DXVECTOR2 position;
	plane->Position(&position);
	playerToDistance = D3DXVec2Length(&(position - this->position));

	if (hp < 0.0f) state = STATE::Death;

	switch (state)
	{
	case STATE::Idle:
		Idle();
		break;
	case STATE::Move:
		Move();
		break;
	case STATE::Attack:
		Attack();
		break;
	case STATE::Death:
		Death();
		break;
	}

	rect->Position(this->position + rectPosition);
	rect->Rotation(angle);
	rect->Update();

	sprite->Rotation(angle);
	sprite->Position(this->position);
	sprite->Update();

	D3DXVECTOR2 hpPos = this->position + D3DXVECTOR2(0, 110);

	hpBar->Position(hpPos);
	hpBar->SetGauge(hp);
	hpBar->Update();
}

void BaseEnemy::Render()
{
	sprite->Render();
	hpBar->Render();
	rect->GizmoRender();
}

void BaseEnemy::Idle()
{
	//ex) 주변 배회, 원위치로 돌아간다, 가만히 있는다.
	//idle->move
	if (playerToDistance < 500.0f)
	{
		state = STATE::Move;
	}
}

void BaseEnemy::Move()
{
	//ex) 따라간다, 주변 돈다.
	//angle, direction,
	D3DXVECTOR2 position;
	plane->Position(&position);
	angle = Intersect::GetAngle(this->position, position) - D3DXToRadian(90.0f);

	//D3DXMATRIX R;
	//D3DXMatrixRotationZ(&R, angle);	//회전 행렬
	//direction = { 0.0f, 1.0f };	//기준점
	//D3DXVec2TransformNormal(&direction, &direction, &R);

	direction = position - this->position;	//상대방의 위치 - 내 위치
	D3DXVec2Normalize(&direction, &direction);	//벡터의 길이를 1로

	this->position += direction * speed;

	//move->attack
	if (playerToDistance < 300.0f)
	{
		state = STATE::Attack;
		prevTime = GetTickCount();
		return;
	}
	//move->idle
	if (playerToDistance > 500.0f)
	{
		state = STATE::Idle;
		return;
	}
}

void BaseEnemy::Attack()
{
	D3DXVECTOR2 position;
	plane->Position(&position);
	angle = Intersect::GetAngle(this->position, position) - D3DXToRadian(90.0f);

	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, angle);	//회전 행렬
	direction = { 0.0f, 1.0f };	//기준점
	D3DXVec2TransformNormal(&direction, &direction, &R);

	currTime = GetTickCount();
	if (currTime - prevTime > delayTime)
	{
		bFire = true;
	}
	//attack -> move
	if (playerToDistance > 100.0f)
	{
		state = STATE::Move;
	}
}

void BaseEnemy::Death()
{
}

void BaseEnemy::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void BaseEnemy::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void BaseEnemy::SetFire(bool _bFire)
{
	bFire = _bFire;
	if (bFire == false)
	{
		prevTime = GetTickCount();
	}
}

////////////////////////////////////////////////////////////
BossEnemy::BossEnemy(AirPlane* link)
	: BaseEnemy(link)
{
	position = { desc.Width * 1.5f - 250, desc.Height * 1.5f - 250 };
	sprite->Position(position);
	sprite->Scale(500, 500);

	rectPosition = { 30.f, 40.f };
	rect->Position(position + rectPosition);
	rect->Scale(440, 420);
	rect->Update();

	respwanPoint = position;
	state = STATE::Death;
	hp = 1000.0f;
	speed = 0.5f;
	hpBar->Scale(500, 40);
	hpBar->SetGauge(hp, hp);
}

BossEnemy::~BossEnemy()
{
}

void BossEnemy::Idle()
{
	direction = respwanPoint - position;
	if (VEC2ZERO(direction))
	{
		direction = { 0.0f,0.0f };
	}
	D3DXVec2Normalize(&direction, &direction);
	position += direction * speed;

	currTime = GetTickCount();
	if (currTime - prevTime > delayTime)
	{
		hp += 10;
		if (hp > 1000)
		{
			hp = 1000;
		}
		prevTime = currTime;
	}

	if (playerToDistance < 600)
	{
		state = STATE::Move;
	}
}

void BossEnemy::Move()
{
	D3DXVECTOR2 target;
	plane->Position(&target);
	direction = target - position;
	D3DXVec2Normalize(&direction, &direction);
	position += direction * speed;

	if (playerToDistance > 600)
	{
		state = STATE::Idle;
		prevTime = GetTickCount(); //체력 회복
	}
	if (playerToDistance < 400)
	{
		state = STATE::Attack;
		prevTime = GetTickCount(); //총알 발사 
	}
}

void BossEnemy::Attack()
{
	if (playerToDistance > 400)
	{
		state = STATE::Move;
	}
}

void BossEnemy::Death()
{
	if (deathCount > 2)
	{
		deathCount = 0;
		state = STATE::Idle;
		prevTime = GetTickCount();
	}
}
