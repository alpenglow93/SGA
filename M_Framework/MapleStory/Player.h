#pragma once
//�÷��̾� ��ü
//�̹���, �̵�(����, �Ʒ�����, ��ٸ�/�� Ÿ��), ����
//hp

struct ChData
{
	float m_Hp;	//���� ü��
	float maxHp;	//ĳ������ �ִ� ü��
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

