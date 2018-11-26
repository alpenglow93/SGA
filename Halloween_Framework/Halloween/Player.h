#pragma once
#define PLAYER_HP 5
#include "Object/Rect.h"
#include "./Animation/Clip.h"
#include "./Render/Sprite.h"

enum class STATE
{
	//����: �⺻���, ����(1����, 2����, 3v, 4^), ��ų(1����, 2��Ʈ), �ǰ�, ����, (�¸����)
	Idle = 0,
	Atk_1,
	Atk_2,
	Atk_3,
	Atk_4,
	Skill_1,
	Skill_2,
	Dameged,
	Death,
	Win

};
class Player
{
private:
	int PlayerHp;

	STATE State;
	Sprite* sprite;
	Rect* rect;
	D3DXVECTOR2 position;

	Clip* Animation;
public:
	Player();
	~Player();

	int GetPlayerHP() { return PlayerHp; }

	void GetState();
	void GetSprite();
	void GetPosition();
	void GetRect();

	void SetState();
	void SetSprite();
	//void SetPosition();
	//void SetRect();

	void Idle();
	void Atk_1();
	void Atk_2();
	void Atk_3();
	void Atk_4();
	void Skill_1();
	void Skill_2();
	void Dameged();
	void Death();
	void Win();

	void Update();
	void Render();
};

