#include "stdafx.h"
#include "MainGame.h"
#include "./Utilities/Intersect.h"


MainGame::MainGame()
{

}


MainGame::~MainGame()
{

}

void MainGame::Init()
{
	mario = new Sprite(L"SingleMario.png");
	mario->Position(100, 100);
	mario->Scale(100, 150);
}

void MainGame::Release()
{
	SAFE_DELETE(mario);
}

void MainGame::Update()
{
	mario->Update();
}

void MainGame::Render()
{
	mario->Render();
}
