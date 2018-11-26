#include "stdafx.h"
#include "AirPlane.h"
#include "PlaneEnemyManager.h"//���ʹ� 

AirPlane::AirPlane(wstring file)
	: sprite(NULL)
	, rect(NULL)
	, speed(200.0f)
	, position(D3DXVECTOR2(
		desc.Width / 2.0f - 25.0f,
		desc.Height / 2.0f - 50.0f))
	, angle(0.0f)
	, direction(0.0f, 1.0f)
	, hp(100.0f)
{
	sprite = new Sprite(file);
	sprite->Scale(100, 100);
	sprite->Position(position);

	rect = new Rect;
	rect->Scale(50, 100);
	rect->Position(position);
	hp = 100;

	hpBar = new PrograssBar(L"progressBarFront.bmp",
		L"progressBarBack.bmp", hp);
	hpBar->Scale(80, 10);

	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i] = new Bullet;
	}
	bomb = new Bomb;

	explosion = new Clip;
	explosion->AddFrame(new Sprite(L"metalslug.png", 3, 313, 46, 407), 0.3f);
	explosion->AddFrame(new Sprite(L"metalslug.png", 55, 313, 99, 407), 0.3f);
	explosion->AddFrame(new Sprite(L"metalslug.png", 104, 313, 158, 407), 0.3f);
	explosion->AddFrame(new Sprite(L"metalslug.png", 164, 313, 216, 407), 0.3f);
	explosion->AddFrame(new Sprite(L"metalslug.png", 227, 313, 318, 407), 0.3f);

	explosion->Scale(1, 0.5f);
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
	if(explosion->IsPlaying())
		explosion->Render();

	rect->GizmoRender();
}

void AirPlane::Move() //�⺻ �̵�
{
	//ȸ���� ���� �̵��� ���� ��� 

	direction = { 0.0f, 1.0f }; //ȸ���� ó���κ� 
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, angle);

	//coord(��ġ) , normal(����)
	D3DXVec2TransformNormal(&direction, &direction, &R);

	if (Input->GetKey('W'))
	{
		position += direction * speed * Time->Elapsed();
	}

	if (Input->GetKey('A'))
	{
		angle += D3DXToRadian(90.0f) * Time->Elapsed();
	}

	if (Input->GetKey('D'))
	{
		angle -= D3DXToRadian(90.0) * Time->Elapsed();
	}

	if (position.x > desc.Width * 3)
	{
		position.x -= desc.Width * 3;
	}
	else if (position.x < 0)
	{
		position.x += desc.Width * 3;
	}
	if (position.y > desc.Height * 3)
	{
		position.y -= desc.Height * 3;
	}
	else if (position.y < 0)
	{
		position.y += desc.Height * 3;
	}


	sprite->Position(position); //�÷��� ������ 
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
	mainCamera->Position(camPos); //ī�޶� �̵� 
}

void AirPlane::Attack() //�⺻ ���� 
{
	if (Input->GetKeyDown('B'))
	{
		if (!bomb->IsFire())
		{
			D3DXVECTOR2 start;
			start.x = position.x + 25.0f;
			start.y = position.y + 50.0f;
			bomb->Fire(start, direction, angle,200.0f,0.3f);

			for (int i = 0; i < BULLETMAX;i++)
			{
				enemys->GetBullet()[i]->SetFire(false);
			}
		}
	}

	if (Input->GetKeyDown(VK_SPACE))
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
	//�浹 
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i]->IsFire()) continue;
		for (int j = 0; j < enemys->GetEnemys().size(); j++)
		{
			if (enemys->GetEnemys()[j]->GetState() 
				== STATE::Death) continue;

			if (Intersect::IsOBB(
				bullet[i]->GetRect(),
				enemys->GetEnemys()[j]->GetRect()))
			{
				enemys->GetEnemys()[j]->SetHP(
					enemys->GetEnemys()[j]->GetHP() - 55.0f);
				bullet[i]->SetFire(false);
				explosion->Position(bullet[i]->GetPosition());
				explosion->Play();
				if (enemys->GetEnemys()[j]->GetHP() < 0.0f)
				{
					BossEnemy::SetDeathCount(
						BossEnemy::GetDeathCount() + 1);
				}
				break;
			}
		}
	}
	explosion->Update();
}

void AirPlane::Position(float x, float y)
{
	position = D3DXVECTOR2(x, y);
}

void AirPlane::Position(D3DXVECTOR2 * position)
{
	*position = this->position;
}

///////////////////////////////////////////////////////////

AirPlane2::AirPlane2(wstring file)
	:AirPlane(file)
{
}

void AirPlane2::Move()
{
	//Elapsed -> �������Ӵ� ��� �ð� 
	//FPS �ʴ� �����Ӽ� 

	sprite->Position(position);
	angle += D3DXToRadian(0.1f);
	sprite->Rotation(angle);
	sprite->Update();
}
