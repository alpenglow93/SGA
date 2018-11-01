#include "stdafx.h"
#include "PlaneMainGame.h"


PlaneMainGame::PlaneMainGame()
{
}


PlaneMainGame::~PlaneMainGame()
{
}

void PlaneMainGame::Init()
{
	player = new AirPlane;	
	background = new Space(player);	//무조건 player를 메모리 할당 받고 넣어줘야한다. 안 그러면 쓰레기값이 들어감.
	enemy = new PlaneEnemyManager();
	enemy->SetEnemys(player);
	enemy->SetBackground(background);
	player->SetLink(enemy);
	miniMap = new MiniMap;
	miniMap->SetLink(player, enemy);	
}

void PlaneMainGame::Release()
{
	SAFE_DELETE(enemy);
	SAFE_DELETE(background);
	SAFE_DELETE(player);
	SAFE_DELETE(miniMap);
}

void PlaneMainGame::Update()
{
	player->Update();
	enemy->Update();
	background->Update();
}

void PlaneMainGame::Render()
{
	background->Render();
	enemy->Render();
	player->Render();
	miniMap->Render();
}
