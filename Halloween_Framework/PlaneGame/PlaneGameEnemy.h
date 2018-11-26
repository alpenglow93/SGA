#pragma once
#include "./Render/Sprite.h"
#include "./Object/Rect.h"
#include "./Bullet.h"
#include "./AirPlane.h"
#include "./Utilities/Intersect.h"
#include "./Object/PrograssBar.h"
//���ʹ� �̹��� + �浹 + �Ѿ� + �÷��̾� 
//AI ->������ -> �̵� -> �߻� -> �״´�. 

//����
enum class STATE
{
	Idle = 0, Move, Attack, Death
};
class BaseEnemy //�⺻ ���ʹ� 
{
protected:
	Sprite * sprite;
	Rect* rect;

	STATE state;

	D3DXVECTOR2 position;
	D3DXVECTOR2 rectPosition;

	D3DXVECTOR2 direction;
	float speed;
	float angle;

	float hp;
	PrograssBar* hpBar;

	UINT prevTime;  //�����̿� 
	UINT currTime;
	UINT delayTime;

	AirPlane* plane;
	float playerToDistance;  //�÷��̾�� �Ÿ�

	bool bFire;
private:

	virtual void Idle(); //idle ���� �϶� 
	virtual void Move(); //move ���� �϶� 
	virtual void Attack(); //attack ���� �϶� 
	virtual void Death();

public:
	BaseEnemy(AirPlane* link);
	virtual ~BaseEnemy();

	void Update();
	void Render();

	Rect* GetRect() { return rect; }
	STATE GetState() { return state; }

	float GetHP() { return hp; }
	void SetHP(float _hp) { hp = _hp; if (hp < 0.0f) { state = STATE::Death; prevTime = GetTickCount(); } }

	void Position(D3DXVECTOR2 vec);
	void Position(float x, float y);

	bool GetFire() { return bFire; }
	void SetFire(bool _bFire);

	D3DXVECTOR2 GetDirection() { return direction; }
	D3DXVECTOR2 GetPosition() { return position; }
	float GetAngle() { return angle; }
};


///////////////////////////////////////////////////////////////////////
//�̹��� ���� �̹��� + ũ�⸦ Ű���.
//AI 
//idle -> ó�� ������ ��� ,���� �ð� ������ ü�� ȸ��
//Run -> ���� ��Ÿ� ���̸� �̵�(ȸ�� x)
//Attack -> ó�� (���߿� ���� )
//Death -> ���� ���� �� ��� 

typedef void(*FP)();
class BossEnemy : public BaseEnemy
{
private:

private:	
	D3DXVECTOR2 respwanPoint;
	static int deathCount;

	vector<FP> vPatten;
public:
	BossEnemy(AirPlane* link);
	~BossEnemy();

	virtual void Idle() override;
	virtual void Move() override;
	virtual void Attack() override;
	virtual void Death() override;

	static int GetDeathCount() { return deathCount; }
	static void SetDeathCount(int count) { deathCount = count; }

	void Push(FP& temp) { vPatten.push_back(temp); }

public:
	void Patten1();
};
