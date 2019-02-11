#include "stdafx.h"
#include "Player.h"
#include "./Objects/QuadObject.h"
#include "./Components/Transform.h"
#include "./Components/Animation/Animation.h"


Player::Player()
	: data(NULL), sprite(NULL)
	, position(D3DXVECTOR2(desc.Width / 2.0f, desc.Height / 2.0f))
{	
	data->maxHp = 100.0f;
	
	//sprite = new Sprite(_Texture + L"Maple/avatar_alert(0)_default(0).png");
	Init();
	Idle();
}


Player::~Player()
{
	SAFE_DELETE(quad);
}

void Player::Init()
{
	data->m_Hp = data->maxHp;

	quad = new QuadObject;
	quad->GetComponent<Transform>()->SetWorldPosition(position);
	anim = new Animation(quad);
	quad->PushComponent(anim);
}

void Player::Update()
{
	quad->Update();
}

void Player::Render()
{
	quad->Render();
}

void Player::Idle()
{
	Clip* clip = new Clip(PlayMode::Loop);

	Sprite* sprite = new Sprite(_MapleAvatar + L"avatar_stand1(0)_default(0).png");
	clip->AddFrame(sprite, 0.3f);

	sprite = new Sprite(_MapleAvatar + L"avatar_stand1(1)_default(0).png");
	clip->AddFrame(sprite, 0.3f);

	sprite = new Sprite(_MapleAvatar + L"avatar_stand1(2)_default(0).png");
	clip->AddFrame(sprite, 0.3f);

	anim->AddClip(L"Test", clip);
	anim->Play(0);
}

void Player::Move()
{
	if (Input->GetKey(VK_LEFT))
	{
		position.y--;
	}
	if (Input->GetKey(VK_RIGHT))
	{
		position.y++;
	}
}
