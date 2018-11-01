#include "stdafx.h"
#include "AirPlane.h"
#include "PlaneEnemyManager.h"

AirPlane::AirPlane()
	:sprite(NULL)
	, rect(NULL)
	, speed(1.0f)
	, position(D3DXVECTOR2(desc.Width / 2.0f - 25.0f,
		desc.Height / 2.0f - 50.0f))
	, angle(0.0f)
	, direction(0.0f, 1.0f)
	, hp(100.0f)
{
	sprite = new Sprite(L"AirPlane.png");
	sprite->Scale(50, 100);
	sprite->Position(position);

	rect = new Rect;
	rect->Scale(50, 100);
	rect->Position(position);

	hpBar = new PrograssBar(L"progressBarFront.bmp",
		L"progressBarBack.bmp", hp);
	hpBar->Scale(80, 10);


	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i] = new Bullet;
	}
	bomb = new Bomb;
}


AirPlane::~AirPlane()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(rect);
	for (int i = 0; i < BULLETMAX; i++)
	{
		SAFE_DELETE(bullet[i]);
	}
}

void AirPlane::Update()
{
	//기본이동
	Move();
	Attack();
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i]->Update();
	}
	bomb->Update();
}

void AirPlane::Render()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i]->Render();
	}
	sprite->Render();
	hpBar->Render();
	bomb->Render();
	ImGui::Begin("DeathCount");
	{
		ImGui::LabelText(" ",
			"DeathCount : %d", BossEnemy::GetDeathCount());
		ImGui::LabelText(" ",
			"%d / 1000", enemys->GetAllEnemys()[100]->GetHP());
	}
	ImGui::End();
	rect->GizmoRender();
}

void AirPlane::Move()	//기본 이동
{
	//회전에 따라 이동할 방향 계산

	direction = { 0.0f, 1.0f };	//회전시 처음부분
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, angle);

	//coord(위치), normal(방향)
	D3DXVec2TransformNormal(&direction, &direction, &R);

	if (Input->GetKey('W') || Input->GetKey(VK_UP))
	{
		position += direction * speed;
	}
	if (Input->GetKey('A') || Input->GetKey(VK_LEFT))
	{
		angle += D3DXToRadian(1.0f);
	}
	if (Input->GetKey('D') || Input->GetKey(VK_RIGHT))
	{
		angle -= D3DXToRadian(1.0f);
	}

	sprite->Position(position);
	sprite->Rotation(angle);
	sprite->Update();

	rect->Position(position);
	rect->Rotation(angle);
	rect->Update();

	D3DXVECTOR2 hpPos = position + D3DXVECTOR2(-40, 110);
	hpBar->Position(hpPos);
	hpBar->Scale(100, 10);
	hpBar->SetGauge(hp);
	hpBar->Update();

	D3DXVECTOR2 camPos;
	camPos.x = position.x - (desc.Width / 2.0f - 25.0f);
	camPos.y = position.y - (desc.Height / 2.0f - 50.0f);
	mainCamera->Position(camPos);
}

void AirPlane::Attack()	//기본 공격
{
	if (Input->GetKeyDown('B'))
	{
		if (!bomb->IsFire())
		{
			D3DXVECTOR2 start;
			start.x = position.x + 25.0f;
			start.y = position.y + 50.0f;
			bomb->Fire(start, direction, angle, 200.0f, 0.3f);

			for (int i = 0; i < BULLETMAX; i++)
			{
				enemys->GetBullet()[i]->SetFire(false);
			}
		}
	}

	if (Input->GetKey(VK_SPACE))
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (!bullet[i]->IsFire())
			{
				D3DXVECTOR2 start;
				start.x = position.x + 25.0f;
				start.y = position.y + 50.0f;
				bullet[i]->Fire(start, direction, angle);
				break;
			}
		}
	}
	//충돌
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i]->IsFire()) continue;
		for (int j = 0; j < enemys->GetEnemys().size(); j++)
		{
			if (enemys->GetEnemys()[j]->GetState()
				== STATE::Death) continue;

			if (Intersect::IsConstainRect(NULL,
				bullet[i]->GetRect(), enemys->GetEnemys()[j]->GetRect()))
			{
				enemys->GetEnemys()[j]->SetHP(
					enemys->GetEnemys()[j]->GetHP() - 55.0f);
				bullet[i]->SetFire(false);
				if (enemys->GetEnemys()[j]->GetHP() < 0.0f)
				{
					BossEnemy::SetDeathCount(
						BossEnemy::GetDeathCount() + 1);
				}
				break;
			}
		}
	}
}

void AirPlane::Position(D3DXVECTOR2 * position)
{
	*position = this->position;
}
