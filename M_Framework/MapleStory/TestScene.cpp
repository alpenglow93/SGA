#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
	player = NULL;
}


TestScene::~TestScene()
{
}

void TestScene::Init()
{
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	player->Update();
}

void TestScene::PreRender()
{
	player->Render();
}

void TestScene::PostRender()
{
}
