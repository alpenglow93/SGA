#pragma once
//플레이어 객체
//이미지, 이동(점프, 아래점프, 사다리/줄 타기), 공격
//hp

struct ChData
{
	float m_Hp;	//현재 체력
	float maxHp;	//캐릭터의 최대 체력
};

class Player
{
private:
	ChData* data;
	Sprite* sprite;
	D3DXVECTOR2 position;

	class QuadObject* quad;
	class Animation* anim;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();

	void Idle();
	void Move();
};

