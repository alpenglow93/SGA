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
