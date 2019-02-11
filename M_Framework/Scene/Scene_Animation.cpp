#include "stdafx.h"
#include "Scene_Animation.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Animation/Animation.h"

Scene_Animation::Scene_Animation()
{
}


Scene_Animation::~Scene_Animation()
{
}

void Scene_Animation::Init()
{
	quad = new QuadObject;
	quad->GetComponent<Transform>()->SetWorldPosition(
		desc.Width / 2, desc.Height / 2);
	anim = new Animation(quad);
	quad->PushComponent(anim);

	Clip* clip = new Clip(PlayMode::Loop);

	Sprite* sprite = new Sprite(_Texture + L"AllMario.png",
		D3DXVECTOR2(0,0), D3DXVECTOR2(32,64));
	clip->AddFrame(sprite, 0.3f);

	sprite = new Sprite(_Texture + L"AllMario.png",
		D3DXVECTOR2(32, 0), D3DXVECTOR2(64, 64));
	clip->AddFrame(sprite, 0.3f);
	sprite = new Sprite(_Texture + L"AllMario.png",
		D3DXVECTOR2(64, 0), D3DXVECTOR2(96, 64));
	clip->AddFrame(sprite, 0.3f);
	anim->AddClip(L"Test", clip);
	anim->Play(0);
}

void Scene_Animation::Release()
{
	SAFE_DELETE(quad);
}

void Scene_Animation::Update()
{
	quad->Update();
}

void Scene_Animation::PreRender()
{
	quad->Render();
}

void Scene_Animation::PostRender()
{
}
