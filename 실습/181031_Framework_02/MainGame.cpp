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
	Scene = new PlaneMainGame;
	Scene->Init();
}

void MainGame::Release()
{
	Scene->Release();
	SAFE_DELETE(Scene);
}

void MainGame::Update()
{
	Scene->Update();
}

void MainGame::Render()
{
	Scene->Render();
}
