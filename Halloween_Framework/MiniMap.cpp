#include "stdafx.h"
#include "MiniMap.h"


MiniMap::MiniMap()
{
	sprite = new Sprite(L"Empty.png");
	sprite->Scale(200, 200);
	sprite->Position(0, 0);

	miniPlayer = new Sprite(L"MiniMap_Player.png");
	miniPlayer->Scale(6, 6);
	miniEnemy = new Sprite(L"MiniMap_Enemy.png");
	miniEnemy->Scale(6, 6);
	miniBoss = new Sprite(L"MiniBoss.png");
	miniBoss->Scale(10, 10);
}


MiniMap::~MiniMap()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(miniPlayer);
	SAFE_DELETE(miniEnemy);
	SAFE_DELETE(miniBoss);
}

void MiniMap::Update()
{
}

void MiniMap::Render()
{
	D3DXVECTOR2 camPos;
	mainCamera->Position(&camPos);

	D3DXVECTOR2 start = camPos + D3DXVECTOR2(10, 10);
	sprite->Position(start);
	sprite->Update();
	sprite->Render();

	D3DXVECTOR2 mapScale;
	mapScale.x = 200.0f / (desc.Width * 3);
	mapScale.y = 200.0f / (desc.Height * 3);
	for (int i = 0; i < enemys->GetAllEnemys().size(); i++)
	{
		if(enemys->GetAllEnemys()[i]->GetState() == STATE::Death) continue;
		if (enemys->GetAllEnemys().size() - 1 == i)
		{
			miniBoss->Position(
				start.x + enemys->GetAllEnemys()[i]->GetPosition().x * mapScale.x,
				start.y + enemys->GetAllEnemys()[i]->GetPosition().y * mapScale.y
			);
			miniBoss->Update();
			miniBoss->Render();
		}
		else
		{
			miniEnemy->Position(
				start.x + enemys->GetAllEnemys()[i]->GetPosition().x * mapScale.x,
				start.y + enemys->GetAllEnemys()[i]->GetPosition().y * mapScale.y
			);
			miniEnemy->Update();
			miniEnemy->Render();
		}
	}

	D3DXVECTOR2 playerPosition;
	player->Position(&playerPosition);

	miniPlayer->Position(
		start.x + playerPosition.x * mapScale.x,
		start.y + playerPosition.y * mapScale.y
	);
	miniPlayer->Update();
	miniPlayer->Render();
}

void MiniMap::SetLink(AirPlane * link1, PlaneEnemyManager * link2)
{
	player = link1;
	enemys = link2;
}
