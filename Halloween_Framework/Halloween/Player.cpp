#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	PlayerHp = PLAYER_HP;
	State = STATE::Idle;
	//Idle이 아닌 시작할때 애니메이션으로 변경할 수도 있음
	sprite = NULL;
	rect = NULL;
	position = D3DXVECTOR2(desc.Width / 2.0f, desc.Height / 2.0f);
	Animation = NULL;
}


Player::~Player()
{
}

void Player::GetState()
{
}

void Player::GetSprite()
{
}

void Player::GetPosition()
{
}

void Player::GetRect()
{
}

void Player::SetState()
{
}

void Player::SetSprite()
{
}

void Player::Idle()
{
}

void Player::Atk_1()
{
}

void Player::Atk_2()
{
}

void Player::Atk_3()
{
}

void Player::Atk_4()
{
}

void Player::Skill_1()
{
}

void Player::Skill_2()
{
}

void Player::Dameged()
{
}

void Player::Death()
{
}

void Player::Win()
{
}

void Player::Update()
{
}

void Player::Render()
{
}
