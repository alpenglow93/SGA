#pragma once
#define PLAYER_HP 5
#include "Object/Rect.h"
#include "./Animation/Clip.h"
#include "./Render/Sprite.h"

enum class STATE
{
	//상태: 기본대기, 공격(1가로, 2세로, 3v, 4^), 스킬(1번개, 2하트), 피격, 죽음, (승리모션)
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

