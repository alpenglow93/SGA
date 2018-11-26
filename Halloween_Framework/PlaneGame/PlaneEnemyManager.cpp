#include "stdafx.h"
#include "PlaneEnemyManager.h"
#include "Space.h"

PlaneEnemyManager::PlaneEnemyManager()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i] = new Bullet;
	}
}


PlaneEnemyManager::~PlaneEnemyManager()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		SAFE_DELETE(enemys[i]);
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		SAFE_DELETE(bullet[i]);
	}
}

void PlaneEnemyManager::Update()
{
	cullingEnemys.clear();
	for (int i = 0; i < enemys.size(); i++)
	{
		//if (enemys[i]->GetState() == STATE::Death) continue;
		enemys[i]->Update();

		if (Intersect::IsConstainRect(NULL,
			enemys[i]->GetRect(), background->GetRect()))
		{
			cullingEnemys.push_back(enemys[i]);
		}
	}
	for (int i = 0; i < BULLETMAX;i++)
	{
		
		if (bullet[i]->IsFire()) continue;
		for (int j = 0; j < cullingEnemys.size(); j++)
		{
			if (cullingEnemys[j]->GetState() == STATE::Death) continue;
			if (cullingEnemys[j]->GetFire() == false) continue;
			D3DXVECTOR2 start;
			start.x = cullingEnemys[j]->GetPosition().x + 25.0f;
			start.y = cullingEnemys[j]->GetPosition().y + 50.0f;
			bullet[i]->Fire(start,
				cullingEnemys[j]->GetDirection(),
				cullingEnemys[j]->GetAngle());
			cullingEnemys[j]->SetFire(false);
			break;
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i]->Update();
		if (!bullet[i]->IsFire()) continue;
		if (Intersect::IsOBB(
			bullet[i]->GetRect(), player->GetRect()))
		{
			player->SetHp(player->GetHp() - 10);
			//bullet[i]->SetFire(false);
		}
	}
}

void PlaneEnemyManager::Render()
{
	for (int i = 0;i < cullingEnemys.size(); i++)
	{
		if (cullingEnemys[i]->GetState() == STATE::Death) continue;
		cullingEnemys[i]->Render();
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i]->IsFire()) continue;
		bullet[i]->Render();
	}
}

void PlaneEnemyManager::SetEnemys(AirPlane* link)
{
	player = link;
	for (int i = 0; i < 10; i++)
	{
		BaseEnemy* newEnemy = new BaseEnemy(link);
		newEnemy->Position(i * 150, desc.Height + 200);
		enemys.push_back(newEnemy);
	}
	BossEnemy* newBoss = new BossEnemy(link);

//	newBoss->Push(newBoss->Patten1);
	//newBoss->Push(newBoss->Patten1);
//	newBoss->Push(newBoss->Patten1);

	enemys.push_back(newBoss);
	
}
