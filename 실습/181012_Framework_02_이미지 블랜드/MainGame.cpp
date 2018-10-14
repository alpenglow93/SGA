#include "stdafx.h"
#include "MainGame.h"
#include "./Utilities/Intersect.h"


MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}
//이미지 확장자 gif -> 맨 처음 저장된 1장만 출력
//bmp -> 포맷 형식이 단조롭다. (단점1. 용량이 크다. 단점2. 알파값이 없다)
//png -> 2번째로 포맷형식이 단조롭다. 알파값 존재, 용량 중간
//jpg -> 가장 포맷형식이 복잡, 용량은 작고, 알파값이 존재.
//dds -> directx 전용 포맷이라 다른 엔진에서는 사용불가

void MainGame::Init()
{
	mario = new Sprite(L"SingleMario.png");
	mario->Position(100, 100);
	mario->Scale(100, 150);

	for (int i = 0; i < 4; i++)
	{
		WCHAR file[10];
		wsprintf(file, L"%d.png", i);
		level[i] = new Sprite(file);
	}
	level[0]->Position(0, 0);
	level[0]->Scale(desc.Width, 100);
	position[0] = { 0, 0 };

	level[1]->Position(200, 100);
	level[1]->Scale(132 * 1.5f, 42 * 1.5f);
	position[1] = { 200, 98 };


	level[2]->Position(600, 98);
	level[2]->Scale(276, 156);
	position[2] = { 600, 98 };


	level[3]->Position(400, desc.Height - 150);
	level[3]->Scale(344, 128);
	position[3] = { 400, desc.Height - 150 };

}

void MainGame::Release()
{
	SAFE_DELETE(mario);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(level[i]);
}

void MainGame::Update()
{
	mario->Update();
	if (Input->GetKey(VK_RIGHT))
	{
		for (int i = 0; i < 4; i++)
		{
			position[i].x -= 1.0f;
			level[i]->Position(position[i]);
		}
	}
	if (Input->GetKey(VK_LEFT))
	{
		for (int i = 0; i < 4; i++)
		{
			position[i].x += 1.0f;
			level[i]->Position(position[i]);
		}
	}
	for (int i = 0; i < 4; i++)
		level[i]->Update();
}

void MainGame::Render()
{
	level[0]->Render();
	level[2]->Render();
	level[3]->Render();
	mario->Render();
	level[1]->Render();
}
