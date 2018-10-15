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
	mario->Position(100.0f, 98.0f);
	mario->Scale(100.0f, 150.0f);

	for (int i = 0; i < 4; i++)
	{
		WCHAR file[10];
		wsprintf(file, L"%d.png", i);
		level[i] = new Sprite(file);
	}
	level[0]->Position(0.0f, 0.0f);
	level[0]->Scale(desc.Width, 100.0f);
	position[0] = { 0.0f, 0.0f };

	////�����̹���1
	//loopImage = new Sprite(L"0.png");
	//loopImage->Scale(desc.Width, 100);
	//offset = { position[0].x + desc.Width, 0 };

	level[1]->Position(200.0f, 98.0f);
	level[1]->Scale(132.0f * 1.5f, 42.0f * 1.5f);
	position[1] = { 200.0f, 98.0f };


	level[2]->Position(600.0f, 98.0f);
	level[2]->Scale(276.0f, 156.0f);
	position[2] = { 600.0f, 98.0f };


	level[3]->Position(400.0f, desc.Height - 150.0f);
	level[3]->Scale(344.0f, 128.0f);
	position[3] = { 400.0f, desc.Height - 150.0f };

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
		for (int i = 2; i < 4; i++)
		{
			position[i].x -= 1.0f;
			level[i]->Position(position[i]);
		}
		position[0].x += 1.0f;
		position[1].x += 1.0f;
	}
	if (Input->GetKey(VK_LEFT))
	{
		for (int i = 2; i < 4; i++)
		{
			position[i].x += 1.0f;
			level[i]->Position(position[i]);
		}
		position[0].x -= 1.0f;
		position[1].x -= 1.0f;
	}
	////�����̹���1
	//if (position[0].x < -desc.Width)
	//	position[0].x = 0;

	//offset.x = position[0].x + desc.Width;
	//loopImage->Position(offset);

	level[0]->Offset(position[0].x / desc.Width, 0.0f);
	level[1]->Offset(position[1].x / desc.Width, 0.0f);

	for (int i = 0; i < 4; i++)
		level[i]->Update();

	//loopImage->Update();
}

void MainGame::Render()
{
	level[0]->Render();
	//loopImage->Render();
	level[2]->Render();
	level[3]->Render();
	mario->Render();
	level[1]->Render();
}
