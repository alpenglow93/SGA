#include "stdafx.h"
#include "MainGame.h"
#include "./Utilities/Intersect.h"


MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}
//�̹��� Ȯ���� gif -> �� ó�� ����� 1�常 ���
//bmp -> ���� ������ �����Ӵ�. (����1. �뷮�� ũ��. ����2. ���İ��� ����)
//png -> 2��°�� ���������� �����Ӵ�. ���İ� ����, �뷮 �߰�
//jpg -> ���� ���������� ����, �뷮�� �۰�, ���İ��� ����.
//dds -> directx ���� �����̶� �ٸ� ���������� ���Ұ�

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
